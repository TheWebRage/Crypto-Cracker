#include<stdio.h>
#include<string.h>
#include <stdlib.h>

char getMostCommonChar1(char* str) {
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

char* strAppend1(char* str, char c) {
    size_t len = strlen(str);
   
    /* one for extra char, one for trailing zero */
    char *str2 = malloc(len + 1 + 1);

    strcpy(str2, str);
    str2[len] = c;
    str2[len + 1] = '\0';

    return str2;
}


char* ceasarDecryptMsg(char message[], int key){

    for (int i = 0; message[i] != '\0'; ++i) {
        char ch = message[i];
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - key;
            if (ch < 'a') {
                ch = ch + 'z' - 'a' + 1;
            }
            message[i] = ch;
        } else if (ch >= 'A' && ch <= 'Z') {
            ch = ch - key;
            if (ch < 'A') {
                ch = ch + 'Z' - 'A' + 1;
            }
            message[i] = ch;
        }
    }

    return message;
}

char* transposeDecryptMsg(char* enMsg, int key){

    char** workingSpace = malloc(sizeof(char*) * key);

    for (int i = 0; i < key; i++) {
        workingSpace[i] = malloc(sizeof(char));
    }

    for (int i = 0; i < key; i++) {
        for (int j = 0; j < strlen(enMsg) / key; j++) {
            workingSpace[i] = strAppend1(workingSpace[i], enMsg[(key * i) + j]);            
        }
    }

    char* decryptedStr = malloc(strlen(enMsg));

    for (int i = 0; i < key; i++) {
        for (int j = 0; j < strlen(enMsg) / key; j++) {
            decryptedStr = strAppend1(decryptedStr, workingSpace[j][i]);            
        }
    }

    return decryptedStr;
}

char* unSplitStr(char** splitStr, int keyLen) {
    char* connectedStr = malloc(sizeof(char));

    int index = 0;

    while (splitStr[0][index] != '\0') {
        for (int i = 0; i < keyLen; i++) {
            connectedStr = strAppend1(connectedStr, splitStr[i][index]);
        }
        index++;
    }

    return connectedStr;
}

void recordKey(char* fileOutPath, char* key) {

    char* fOut = malloc(sizeof(char)*7);
    strcpy(fOut, "key.txt");

    FILE* fOutPtr = fopen(fileOutPath, "w");
    fprintf(fOutPtr, "Key: %s\n\n", key);
    fclose(fOutPtr);
    printf("key: %s\n", key);
}

char* decryptVignere(char** message, int keyLen, char* fileOut) {
    char* key = malloc(sizeof(char) * keyLen);

    for (int i = 0; i < keyLen; i++) {
        int offset = getMostCommonChar1(message[i]) - 'E';
        message[i] = ceasarDecryptMsg(message[i], offset);
        key[i] = offset + 'A';
    }

    recordKey(fileOut, key);

    return unSplitStr(message, keyLen);
}

char* decryptCeasar(char* message, char* offset, char* fileOut) {
    offset[0] = offset[0] + 'A';
    recordKey(fileOut, offset);
    return ceasarDecryptMsg(message, (int)offset[0] - 'A');
}

int isValidBiGram(char* decryptedStr) {
    return 1;
}

char* decryptTranspose(char* message) {

    char* decryptedMsg[30000] = {0};

    for (int i = 0; i < 15; i++) {
        if (strlen(message) % i != 0) {
            continue;
        }

        char* decryptedStr = transposeDecryptMsg(message, i);

        /* Check the distrobution of n-grams to check they are actual words */

        if (!isValidBiGram(decryptedStr)) {
            continue;
        }

        /*TODO: RECORD KEY*/

        return decryptedStr;
    }

}