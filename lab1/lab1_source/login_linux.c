/* $Header: https://svn.ita.chalmers.se/repos/security/edu/course/computer_security/trunk/lab/login_linux/login_linux.c 585 2013-01-19 10:31:04Z pk@CHALMERS.SE $ */

/* gcc -Wall -g -o mylogin login.linux.c -lcrypt */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <string.h>
#include <signal.h>
#include <pwd.h>
#include <sys/types.h>
#include <crypt.h>
#include "pwent.h"

#define _XOPEN_SOURCE
#define TRUE 1
#define FALSE 0
#define LENGTH 16
#define SUCCESS 0
#define FAILED 1

/* Extra utilities */
void sighandler(int sig_num);
void set_no_attempts(char us[LENGTH], mypwent *structpsw, int mode);

int main(int argc, char *argv[]) {

	mypwent *passwddata; /* this has to be redefined in step 2 */
	/* see pwent.h */

	char important[LENGTH] = "***IMPORTANT***";

	char user[LENGTH];
	char *c_pass;
	char prompt[] = "password: ";
	char *user_pass;

	/* Signal handling routines  */
	if (signal(SIGINT, sighandler) == SIG_ERR)
        printf("\nCan't catch SIGINT\n");
  if (signal(SIGTSTP, sighandler) == SIG_ERR)
        printf("\nCan't catch SIGTSTP\n");
  if (signal(SIGQUIT, sighandler) == SIG_ERR)
        printf("\nCan't catch SIGQUIT\n");

	while (TRUE) {
		/* check what important variable contains - do not remove, part of buffer overflow test */
		printf("Value of variable 'important' before input of login name: %s\n",
				important);

		printf("login: ");
		fflush(NULL); /* Flush all  output buffers */
		__fpurge(stdin); /* Purge any data in stdin buffer */

		if (fgets(user, LENGTH, stdin) == NULL)  /* gets() is vulnerable to buffer */
			exit(0); /*  overflow attacks.  */

		/* If fgets is used instead of gets we will get a ”\n” at the end of the string so we replaced it with a ”\0”. */
        char *pos;
        if ((pos=strchr(user, '\n')) != NULL)
        *pos = '\0';
		/* check to see if important variable is intact after input of login name - do not remove */
		printf("Value of variable 'important' after input of login name: %*.*s\n",
				LENGTH - 1, LENGTH - 1, important);

		user_pass = getpass(prompt);
		passwddata = mygetpwnam(user);

		if (passwddata != NULL) {

			if((c_pass = crypt(user_pass,"fG"))!= NULL){

				if (!strcmp(user_pass, passwddata->passwd)) {

					/*check the age of the password if the password if old, the program alerts the user*/
        	if(passwddata->pwage >=3 )
          	printf("The password is old, please change it\n");

					printf(" You're in !\n");
					/* set_no_attemps function is called with mode SUCCESS which resets the number of failed_attempts and increments the age */
        	set_no_attempts(user, passwddata, SUCCESS);
        	/* At a successful login attempt a command interpreter (/bin/sh) should be started with the correct user rights. */
        	int status = setuid(passwddata->uid);
        	/*chek the status*/
	        if(status == 0){
	        	int ret;
	          char *envp[] = { NULL };
	          /*some arguments just for debug */
	          char *argv[] = {"/bin/sh", "hello", NULL};
	          /*execve is used for start the new shell */
	          ret = execve("/bin/sh", argv, envp);
	          printf("%d",ret);
	        }

					/*  check UID, see setuid(2) */
					/*  start a shell, use execve(2) */

				}
				else {
	        /*if the password is wrong we alert the user */
	        printf("Wrong password\n");

					if(passwddata->pwfailed>=3){
	          /*if the user failed for more than 3 times we introduced a significant delay for avoid bruteforce attack */
	          printf("Password wrong for more than 3 times\n");
	          usleep(10000000);
	        }
	        else {
	          /*otherwise we called again the function set_no_attempts with the mode FAILED the number of failed_attempts is incremented.*/
	          set_no_attempts(user,passwddata,FAILED);
	        }
	      }
			}
			else {
				printf("Login Incorrect\n");
			}

		} /*close the main if */

	} 	/*close the While loop */
	return 0;
} /*close the main function */

/* This function resets the number of failed_attempts and increments the age*/
void set_no_attempts(char us[LENGTH],mypwent *structpsw, int mode){

	if (mode == SUCCESS){

		/*set to zero the no_of_failed_attempts and increment the age*/
		structpsw->pwfailed = 0;
		++structpsw->pwage;

		/*check if the user is founded*/
		if(mysetpwent(us, structpsw) == -1)
		printf("Error, user not found");
		}

		else if(mode == FAILED){
			++structpsw->pwfailed;

			if(mysetpwent(us, structpsw) == -1)
				printf("Error, user not found");
	}
}
/* Signal handling routines are listed below, with a message for the user */
void sighandler(int sig_num) {

	if (sig_num == SIGINT)
        printf("Received signal SIGINT\n");
    else if (sig_num == SIGKILL)
        printf("Received signal SIGTSTP\n");
    else if (sig_num == SIGSTOP)
        printf("Received signal SIGQUIT\n");
}
