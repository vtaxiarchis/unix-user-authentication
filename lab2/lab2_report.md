# Report for Assignment 2 in Computer Security - Group 19 (Vaios Taxiarchis, Surafel Meheret Alamneh) #

-----------------------------------------------------------------

1. Vaios Taxiarchis - 19910309-8514
   Surafel Meheret Alamneh - 19881219-4176
   Group Number: 19

2. The key's fingerprint is: 60F5 CE3B AF3E 1AF8 BB4A 738C 05FC 7AAF D448 F56B

3. The mail client we used is Mozilla Thunderbird

4. We are using GPG for the future specially for email clients due to the following reasons.
·       There is no complicated legal issues to when we are using GPG.
·       It can be used for free.
·       Emails that use GPG are compatible with PGP.
·       It can be used easily on Linux.

5. Digital signatures will allow the recipient of information to verify the authenticity of the information’s origin which provides authentication in terms of confidentiality and it also verify that the information is intact which ensures the data integrity. A digital signature also provides non-repudiation, which means that it prevents the sender from claiming that he or she did not actually send the information.
The signing works in PGP with the following important steps
On sender’s side:
Step 1: User has to write the message he wants to send.
Step 2: PGP uses a cryptographically strong hash function on the plaintext the user is signing. This generates a fixed-length data item known as a message digest
Step 3: Then PGP uses the digest and the private key to create the signature.
Step 4: Finally, PGP transmits the signature and the plaintext together to the recipient.
On recipient’s side:
Step 1: On receiving the message, recipient uses the PGP to recompute the message digest, for verifying the signature.
N.B If the signature is decrypted with the appropriate public key, it must have came from the person who have the matching  private key.
Hash is used mainly with the following reasons:
·       If anything within the message changes by even the slightest amount, the number calculated by the hash function will change fairly dramatically.
·       It's impossible to alter a message in order to have it generate a specific, desired hash value.
·       Given a hash value, you can tell nothing about the message that produced it.

6. The purpose of encryption is to convert a message to unreadable form so that unauthorized person in the middle can not read it. PGP is a hybrid cryptosystem. When a user encrypts plaintext with PGP, PGP first compresses the plaintext. PGP then creates a session key, which is a one-time-only secret key. This key is a random number generated from the random movements of your mouse and the keystrokes you type. This session key works with a very secure, fast conventional encryption algorithm to encrypt the plaintext; the result is ciphertext.
PGP encryption and decryption  works with the following manner first We need to start with a concept: public key encryption. With this type of encryption, you generate a key pair. Call them "A" and "B". Something encrypted using key "A" can only be decrypted with key "B", and something encrypted with key "B" can only be decrypted with key "A". Then Now, if we create a pair of those keys, we can make one public and keep the other one a closely guarded private/secret key.
Someone can take my public key and use it to encrypt something. Once encrypted only I can decrypt it using my matching private key. Even the person who encrypted it cannot decrypt it. It's a secure way to encrypt data such that it can be seen only by the intended recipient.
I can encrypt something with my private key, that then anyone can decrypt with my public key. Now, that seems kinda silly, if anyone can decrypt it. Except that if it can be decrypted using my public key, then only I could have encrypted it using my private key. It validates that the encryption could only have been performed by me.

Here is the general steps how the encryption and decryption is processed and also how the session key is transmitted.
Encryption in PGP
Step 1: PGP first compresses the plaintext which we want to send.
Step 2: By compressing the plain text PGP creates a session key (one-time-only secret key). This key is a random number generated from the random movements of our mouse and the keystrokes we type. This session key works with a very secure, fast conventional encryption algorithm to encrypt the plaintext which results is ciphertext.
Step 3: Once the data is encrypted, the session key is then encrypted to the recipient’s public key.
Step 4: This public key-encrypted session key is transmitted along with the ciphertext to the recipient.
Decryption in PGP
Step 1: Decryption works in the reverse. The recipient’s copy of PGP recovers the temporary session key using his or her private key.
Step 2: PGP then uses the recovered temporary session key to decrypt the conventionally-encrypted ciphertext.
Step 3: after decrypting conventionally-encrypted ciphertext the recipient will be able to see the plain text we send.

7.  GPG uses digital signatures as its form of introduction. When any user signs another’s key, he or she becomes an introducer of that key. As this process goes on, it establishes a web of trust. We can validate a key belonging to a person we do not know personally by checking their certificate’s fingerprint. By checking the fingerprint we can be sure that the key belong to him. And more specifically, we trust people to validate other people’s certificates.
If the signature can be decrypted using the appropriate public key, it must have come from the person who holds the matching private key. If using my public key you can decrypt the signature of a message I sign, then it must have come from me.

8.  A. Elena trust: UNKNOWN, validity: UNKNOWN
    B. Elena trust: UNKNOWN, validity: FULL

9.
-----BEGIN PGP PUBLIC KEY BLOCK-----
Version: GnuPG v1

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
xKoiyvVGY5+7WC7yWD8JmAdE9xQH6ufGAEzB
=rKYR

-----END PGP PUBLIC KEY BLOCK-----
