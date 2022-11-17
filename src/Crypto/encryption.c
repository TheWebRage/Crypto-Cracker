
int validateInput(char input) {
    if (input < 97 || input > 122) {
        return 0;
    }
    return 1;
}

void encryptionAlgorithm(char* encryptionKey, char* fileIn, char* fileOut, int isDecrypt) {
    FILE* fileIn_ptr;
    FILE* fileOut_ptr;

    fileIn_ptr = fopen(fileIn, "r");
    fileOut_ptr = fopen(fileOut, "w");

    if (fileIn_ptr == NULL) {
        printf("\nFile '%s' does not exist.\n", *fileIn_ptr);
        return;
    }

    char c = getc(fileIn_ptr);
    int encryptionKeyIndex = 0;

    while (c != EOF) {

        if (!validateInput(c) || !validateInput(encryptionKey[encryptionKeyIndex])) {
            printf("\nInvalid data in text file. Please remove invalid data and try again.\n");
            fclose(fileOut_ptr);
            remove(fileOut);
            return;
        }

        char encryptValue = encryptionKey[encryptionKeyIndex] - 96;
        char value = 0;

        if (isDecrypt) {
            value = c - encryptValue - 96;

            if (value < 1) {
                value += 26;
            }

        } else {
            value = c + encryptValue - 96;

            if (value > 26) {
                value -= 26;
            }
        }

        fputc(value + 96, fileOut_ptr);
        c = getc(fileIn_ptr);

        encryptionKeyIndex++;
        if (encryptionKey[encryptionKeyIndex] == '\0') {
            encryptionKeyIndex = 0;
        }
    }

    fclose(fileIn_ptr);
    fclose(fileOut_ptr);
}

void encrypt(char* encryptionKey, char* fileIn, char* fileOut) {
    encryptionAlgorithm(encryptionKey, fileIn, fileOut, 0);
}

void decrypt(char* encryptionKey, char* fileIn, char* fileOut) {
    encryptionAlgorithm(encryptionKey, fileIn, fileOut, 0);
}