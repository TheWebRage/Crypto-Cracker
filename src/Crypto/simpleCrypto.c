#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "encryption.c"

void simpleCryptoStart() {
    
    int choice = 0;

    while (choice != 9) {
        char* encryptionKey = malloc(sizeof(char)*8);
        char* fileIn = malloc(sizeof(char)*8);
        char* fileOut = malloc(sizeof(char)*8);

        printf("\n\n----- Simple Crypto -----\n1. Encrypt\n2. Decrypt\n3. Main Menu\n\n");

        printf("Choose an option: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\n\nEncrypt");
            printf("\n\nEncryption Key: ");
            scanf("%s", encryptionKey);

            printf("\nInput File: ");
            scanf("%s", fileIn);

            printf("\nOutput File: ");
            scanf("%s", fileOut);

            encrypt(encryptionKey, fileIn, fileOut);
            break;
        case 2:
            printf("\n\nDecrypt");
            printf("\n\nDecryption Key: ");
            scanf("%s", encryptionKey);

            printf("\nInput File: ");
            scanf("%s", fileIn);

            printf("\nOutput File: ");
            scanf("%s", fileOut);

            decrypt(encryptionKey, fileIn, fileOut);
            break;
        case 3:
            return;
        
        default:
            printf("Invalid Option. Choose a number shown.\n");
            break;
        }

        free(encryptionKey);
        free(fileIn);
        free(fileOut);
    }

}
