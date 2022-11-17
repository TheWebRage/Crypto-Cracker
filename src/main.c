
#include "./Crypto/simpleCrypto.c"
#include "./EmployeeDirectory/employeeInput.c"
#include "./CryptoCracker/cryptoCrackerMain.c"

int main() {

    int choice = 0;

    while (choice != 9) {
        printf("\n\n----- Main Menu -----\n1. Simple Crypto\n2. Employee Directory\n3. Crypto Cracker\n9. Quit\n\n");

        printf("Choose an option: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            simpleCryptoStart();
            break;
        case 2:
            employeeDirectoryStart();
            break;
        case 3:
            cryptoCrackerStart();
            break;
        case 9:
            printf("\nThanks for using the app!");
            break;

        default:
            printf("\nInvalid Option. Choose a number shown.\n");
            break;
        }
    }

    printf("\n\n");
}
