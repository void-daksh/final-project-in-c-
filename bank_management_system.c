#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Account {
    int account_number;
    char name[100];
    float balance;
};
void create_account();
void deposit_withdraw(int account_number, int operation);
void check_balance();
void list_accounts();
void main_menu();

int main() {
    main_menu();
    return 0;
}
void main_menu() {
    int choice;
    while (1) {
        printf("\n\n** Bank Account Management System **\n");
        printf("1. Create New Account\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Account Balance\n");
        printf("5. List All Accounts\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create_account();
                break;
            case 2:
                deposit_withdraw(0, 1); 
                break;
            case 3:
                deposit_withdraw(0, 2); 
                break;
            case 4:
                check_balance();
                break;
            case 5:
                list_accounts();
                break;
            case 6:
                printf("Thank you for using the system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
}
}
}

void create_account() 
{
    struct Account new_acc;
    FILE *fp;

    fp = fopen("accounts.dat", "ab"); 
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\n** Create New Account **\n");

    printf("Enter account number: ");
    scanf("%d", &new_acc.account_number);
    printf("Enter name: ");
    getchar();
    fgets(new_acc.name, 100, stdin);
    new_acc.name[strcspn(new_acc.name, "\n")] = 0;
    printf("Enter initial deposit amount: ");
    scanf("%f", &new_acc.balance);
    fwrite(&new_acc, sizeof(struct Account), 1, fp);
    fclose(fp);
    printf("\nAccount created successfully!\n");
}
void deposit_withdraw(int account_number, int operation) 
{
    struct Account acc;
    FILE *fp, *ft;
    int found = 0;
    float amount;

    if (account_number == 0) 
    {
        printf("\nEnter account number: ");
        scanf("%d", &account_number);
    }

    fp = fopen("accounts.dat", "rb"); 
    ft = fopen("temp.dat", "wb");    

    if (fp == NULL || ft == NULL) 
    {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp)) 
    {
        if (acc.account_number == account_number) 
        {
            if (operation == 1) 
            {
                printf("Enter amount to deposit: ");
                scanf("%f", &amount);
                acc.balance += amount;
                printf("\nDeposit successful.\nNew balance: %.2f\n", acc.balance);
            } 
            else if (operation == 2) 
            {
                printf("Enter amount to withdraw: ");
                scanf("%f", &amount);
                if (acc.balance >= amount) 
                {
                    acc.balance -= amount;
                    printf("\nWithdrawal successful.\nNew balance: %.2f\n", acc.balance);
                }
                 else 
                {
                    printf("\nInsufficient balance.\n");
                }
            }
            found = 1;
        }
        fwrite(&acc, sizeof(struct Account), 1, ft); 
    }

    fclose(fp);
    fclose(ft);

    remove("accounts.dat");           
    rename("temp.dat", "accounts.dat"); 
    if (!found) {
        printf("\nAccount not found.\n");
    }
}


void check_balance() {
    struct Account acc;
    FILE *fp;
    int account_number, found = 0;

    printf("\nEnter account number: ");
    scanf("%d", &account_number);

    fp = fopen("accounts.dat", "rb"); 

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.account_number == account_number) {
            printf("\nAccount Details:\n");
            printf("Account Number: %d\n", acc.account_number);
            printf("Name: %s\n", acc.name);
            printf("Balance: %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found) {
        printf("\nAccount not found.\n");
    }
}
void list_accounts() {
    struct Account acc;
    FILE *fp;

    fp = fopen("accounts.dat", "rb"); 

    if (fp == NULL) {
        printf("\nNo accounts found.\n");
        return;
    }

    printf("\n\n** All Accounts **\n");
    printf("%-15s %-20s %-10s\n", "Account No", "Name", "Balance");
    printf("-----------------------------------------------\n");

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        printf("%-15d %-20s %-10.2f\n",
               acc.account_number,
               acc.name,
               acc.balance);
    }

    fclose(fp);
}