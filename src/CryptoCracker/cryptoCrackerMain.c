#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ceasar.c"

int* findFrequncy(char S[])
{
    int i = 0;
    int* freq = malloc(sizeof(int) * 26);

    while (S[i] != '\0') {
        freq[S[i] - 'A']++;
        i++;
    }

    return freq;
}

char getMostCommonChar(char* str) {
    int array[255] = {0};
    int i, max, index;

    for (i = 0; str[i] != 0; i++) {
        ++array[str[i]];
    }

    max = array[0];
    index = 0;
    for (i = 0; str[i] != 0; i++) {
        if (array[str[i]] > max) {
            max = array[str[i]];
            index = i;
        }
    }

    return str[index];
}

char* getMostCommonCharSplit(char* str, int keyLength) {
    char* keyResult[255] = {0};

    for (int j = 0; j < keyLength; j++) {
        int array[255] = {0};
        int i, max, index;

        for (i = j; str[i] != 0; i += keyLength) {
            ++array[str[i]];
        }

        max = array[0];
        index = 0;
        for (i = j; str[i] != 0; i += keyLength) {
            if (array[str[i]] > max) {
                max = array[str[i]];
                index = i;
            }
        }

        keyResult[j] = str[index];
    }


    return keyResult;
}

char getDistOffset(char* message) {
    char mostCommon = getMostCommonChar(message);
    return mostCommon - 'E'; /*The provided examples only use capitol letters for now*/
}

float getDistPercent(char* message) {
    int* freq = findFrequncy(message);

    float total = 0;
    int max = 0;
    int second = 0;

    for (int i = 0; i < 26; i++) {
        if (freq[i] > max) {
            second = max;
            max = freq[i];
        }
        else if (freq[i] > second) {
            second = freq[i];
        }

        total += freq[i];
    }

    return ((max/total) - (second/total)) * 100;
}

int getEncryptionType(char* message) {

    if (getDistPercent(message) < 2) {
        return -1;
    }

    if (getMostCommonChar(message) - 'E' == 0) {
        return 0;
    }

    return 1;
}

char* strAppend(char* str, char c) {
    size_t len = strlen(str);
   
    /* one for extra char, one for trailing zero */
    char *str2 = malloc(len + 1 + 1);

    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';

    return str2;
}

char* strAppendNullByte(char* str) {
    size_t len = strlen(str);
   
    /* one for extra char, one for trailing zero */
    char *str2 = malloc(len + 1);

    strcpy(str2, str);
    str2[len] = '\0';

    return str2;
}

/* Splits the array every xth item (for finding multi-char key symmetric cyphers) */
char** splitStr(char* message, int keyLength) {
    char** splitString = malloc(keyLength * sizeof(char*));

    for (int i = 0; i < keyLength; i++) {
        splitString[i] = malloc(sizeof(char));
    }

    for (int i = 0; i < strlen(message); i++) {
        int spot = i % keyLength;
        splitString[spot] = strAppend(splitString[spot], message[i]);
    }

    for (int i = 0; i < keyLength; i++) {
        splitString[i] = strAppendNullByte(splitString[i]);
    }

    return splitString;
}

char* crackMessage(char* msg, char* fileOut) {
    int encryptionType = getEncryptionType(msg);

    if (encryptionType == 0) {
        printf("\nCracking using Transposition Decoder\n");
        return decryptTranspose(msg);
    }

    else if (encryptionType == -1) {
        int keyLen = 2;

        while (keyLen < 15) {
            char** splitString = splitStr(msg, keyLen);

            if (getDistPercent(splitString[0]) < 2) {
                keyLen++;
                continue;
            }

            printf("\nCracking using Vigenere Decoder\n");
            return decryptVignere(splitString, keyLen, fileOut);
        }
    }

    else if (encryptionType == 1) {
        char* distOffset = malloc(sizeof(char));
        distOffset[0] = getDistOffset(msg);

        printf("\nCracking using Ceaser Decoder\n");
        return decryptCeasar(msg, distOffset, fileOut);
    }

    return "Could not decrypt message. Other encryption method used.";
}

void startCracking(char* fileInPath, char* fileOutPath) {
    
    if (fileInPath == fileOutPath) {
        printf("\nError: In and Out files are the same\n");
        return;
    }

    FILE* fileIn_ptr;
    FILE* fileOut_ptr;

    fileIn_ptr = fopen(fileInPath, "r");


    if (fileIn_ptr == NULL) {
        printf("\nFile '%s' does not exist.\n", *fileIn_ptr);
        return;
    }

    char* encryptMsg[30000] = {0};

    fgets(encryptMsg, 30000, fileIn_ptr);

    fclose(fileIn_ptr);

    char* decryptedMsg = crackMessage(encryptMsg, fileOutPath);

    fileOut_ptr = fopen(fileOutPath, "a+");
    fprintf(fileOut_ptr, "%s\n", decryptedMsg);
    fclose(fileOut_ptr);
}

void cryptoCrackerStart() {

    int choice = 0;

    while (choice != 3) {
        printf("\n\n----- Crypto Cracker -----\n1. Crack message\n3. Main Menu\n\n");

        printf("Choose an option: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:;
            char* fileIn[1024] = {0};
            char* fileOut[1024] = {0};

            printf("\n\nPlease enter a file to decrypt: ");
            scanf("%s", fileIn);

            printf("\nPlease enter a file to output: ");
            scanf("%s", fileOut);

            startCracking(fileIn, fileOut);
            break;
        case 3:
            return;
        
        default:
            printf("\nInvalid Option. Choose a number shown.\n");
            break;
        }
    }

    printf("\n\n");

}