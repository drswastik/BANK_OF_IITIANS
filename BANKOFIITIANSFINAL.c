 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void new_user();
void existing_user();
void admin_user();
void deposit(char *acc_id);
void withdraw(char *acc_id);
float balance_check(char *acc_id);
void fund_transfer();
void neft();
void rtgs();
void imps();
void fixed_deposit(char *acc_id);
void loan(char*acc_id);
void loan_approval();
void repay_loan(char *acc_id);
void add_insurance(char *acc_id);
void check_insurance(char *acc_id);
void display_schemes();
void select_scheme(int scheme_choice);
void cheque(char * acc_id);
char* verify_card_details(long long int card_number, int pin);
void atm_use();
void card_info(char *acc_id, long long int card_number, int pin);
void atm(char *acc_id);
void approve_transactions();
void car(char *acc_id);
void house(char *acc_id);
void educ(char *acc_id);
void check_account_balance();


typedef struct {
    char name[50];
    float premium;
    char benefits[100];
} Scheme;

typedef struct {
    char policy_number[15];
    float premium;
    char provider[50];
} Insurance;

Scheme schemes[2] = {{"Scheme A", 5000, "Accidental insurance"},
                     {"Scheme B", 7000, "Health insurance"}};
int main() {
    int choice;
    FILE *fp1;
    while (1) {
        printf("\nWelcome To The Bank Of IITians\n");
        printf("1. New User\n");
        printf("2. Existing User\n");
        printf("3. Admin User\n");
        printf("4. Exit\n");
        printf("Please Enter Your Choice:");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                new_user();
                break;
            case 2:
                existing_user();
                break;
            case 3:
                admin_user();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
    
    return 0;
}
void new_user() {
    FILE *fp;
    char name[50], gender, address[100], roll_no[15], aadhar[15];
    
    printf("\nEnter Name: ");
    scanf(" %[^\n]", name);
    printf("Enter Age: ");
    int age;
    scanf("%d", &age);
    printf("Enter Gender (M/F): ");
    scanf(" %c", &gender);
    printf("Enter Address: ");
    scanf(" %[^\n]", address);
    printf("Enter Institute Roll No.: ");
    scanf("%s", roll_no);
    printf("Enter Aadhar Number: ");
    scanf("%s", aadhar);
    
    char acc_id[15], login_id[15], password[] = "SWAS123";
    strcpy(acc_id, roll_no);
    strcpy(login_id, roll_no);
    
    fp = fopen("iitbank.txt", "a");
    fprintf(fp, "\n%s\t%s\t%d\t%c\t%s\t%s\t%s\n", acc_id, name, age, gender, address, roll_no, aadhar);
    fclose(fp);
    
    printf("\nAccount created successfully!!!\n");
    printf("Your Account ID is: %s\n", acc_id);
    printf("Your Login ID is: %s\n", login_id);
    printf("Your Password is: %s\n", password);
}

 
 void existing_user() {
    char acc_id[15];
    char pass[8];
    char oripass[] = "SWAS123";
    int choice;

    t:
    printf("\nEnter YOUR Account ID: ");
    scanf("%s", acc_id);
    printf("\nEnter YOUR Password : ");
    scanf("%s", pass);

    if(strcmp(pass, oripass) != 0){
        printf("\nINVALID CREDENTIALS....TRY AGAIN\n");
        goto t;
    }
    
    while (1) {
        printf("\nExisting User Menu\n");
        printf("1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Balance Check\n");
        printf("4. Fund Transfer\n");
        printf("5. Card Services\n");
        printf("6. Loan\n");
        printf("7. Cheque Book Issue\n");
        printf("8. Fixed Deposit\n");
        printf("9. Buy Insurance\n");
        printf("10. Check Insurance\n");
        printf("11. Withdraw Using Card\n");
        printf("0. Back to Main Menu\n"); 
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                deposit(acc_id);
                break;
            case 2:
                withdraw(acc_id);
                break;
            case 3:
                balance_check(acc_id);
                break;
            case 4:
                fund_transfer(acc_id);
                break;
            case 5:
                atm(acc_id);
                break;
            case 6:
                loan(acc_id);
                break;
            case 7:
                cheque(acc_id);
                break;
            case 8:
                fixed_deposit(acc_id);
                break;
            case 9:
                add_insurance(acc_id);
                break;
            case 10:
                check_insurance(acc_id);
                break;
            case 11:
                atm_use();
                break;
            case 0: 
                return;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}

void add_insurance(char *acc_id) {
 
    Insurance insurance;

    printf("\nSelect a scheme:\n");
    display_schemes();
    printf("Enter the number of the schemes you want to select: ");
    int scheme_choice;
    scanf("%d", &scheme_choice);
    if (scheme_choice < 1 || scheme_choice > 2) {
        printf("Invalid scheme choice!\n");
        return;
    } else {
        insurance.premium = schemes[scheme_choice - 1].premium;
        strcpy(insurance.provider, "IIT BANK");
        printf("Premium: %.2f\n", insurance.premium);
    }

   
    FILE *acc_fp;
    char acc_filename[20];
    sprintf(acc_filename, "%s.txt", acc_id);
    acc_fp = fopen(acc_filename, "r+");
    if (acc_fp == NULL) {
        printf("Error in opening account file!\n");
        return;
    }
    float balance;
    fscanf(acc_fp, "%f", &balance);
    if (balance < insurance.premium) {
        printf("Insufficient balance to purchase insurance!\n");
        fclose(acc_fp);
        return;
    }
    balance -= insurance.premium;
    rewind(acc_fp);
    fprintf(acc_fp, "%.2f", balance);
    fclose(acc_fp);

    
    srand(time(NULL));
    int random_number = rand() % 900000 + 100000; 
    sprintf(insurance.policy_number, "%d", random_number);

    FILE *fp;
    char filename[30];
    sprintf(filename, "%s_insurance.txt", acc_id);
    fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Error in opening insurance file!\n");
        return;
    }
    fprintf(fp, "%s\t%.2f\t%s\n", insurance.policy_number, insurance.premium, insurance.provider);
    fclose(fp);

    printf("Insurance added successfully!\n");
}


void check_insurance(char *acc_id) {
    
    FILE *fp;
    char filename[30];
    char policy_number[15];
    float premium;
    char provider[50];

    sprintf(filename, "%s_insurance.txt", acc_id);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("No insurance details found for this account.\n");
        return;
    }
    printf("\nInsurance Details for Account ID: %s\n", acc_id);
    printf("Policy Number\tPremium\tProvider\n");
    while (fscanf(fp, "%s %f %s", policy_number, &premium, provider) != EOF) {
        printf("%s (%.2f)\t%s\n", policy_number, premium, provider);
    }
    fclose(fp);
}

void display_schemes() {
    
    printf("\nOUR BANK OFFERS THE FOLLOWING SCHEMES FOR INSURANCE:\n");
    for (int i = 0; i < 2; ++i) {
        printf("%d. %s (Premium: %.2f, Benefits: %s)\n", i + 1, schemes[i].name, schemes[i].premium, schemes[i].benefits);
    }
}

void select_scheme(int scheme_choice) {
    
    printf("\nYou have selected the scheme: %s\n", schemes[scheme_choice].name);
    printf("Premium: %.2f\n", schemes[scheme_choice].premium);
    printf("Benefits: %s\n", schemes[scheme_choice].benefits);
    
}


void deposit(char *acc_id) {
    FILE *temp_fp;
    float amount;
    
    printf("\nEnter Amount to Deposit: ");
    scanf("%f", &amount);
    
    char ref_num[30];
    srand((unsigned int)time(NULL));
    sprintf(ref_num, "%sD%d", acc_id, rand());
    
    temp_fp = fopen("iitbanktemp.txt", "a");
    fprintf(temp_fp, "%s Deposit %.2f %s\n", acc_id, amount, ref_num);
    fclose(temp_fp);
    
    printf("\nTemporary Reference Number for Deposit: %s\n", ref_num);
    
}

void withdraw(char *acc_id) {
    FILE *temp_fp;
    float amount;
    t:
    printf("\nEnter Amount to Withdraw: ");
    scanf("%f", &amount);
    float amt=balance_check(acc_id);
    
    char ref_num[30];
    srand((unsigned int)time(NULL));
    sprintf(ref_num, "%sW%d", acc_id, rand());

    if(amt<amount){
        printf("\nINSUFFICIENT BALANCE......CANNOT WITHDRAW MONEY");
        goto t;
    }
    
    temp_fp = fopen("iitbanktemp.txt", "a");
    fprintf(temp_fp, "%s Withdraw %.2f %s\n", acc_id, amount, ref_num);
    fclose(temp_fp);
    
    printf("\nTemporary Reference Number for Withdrawal: %s\n", ref_num);
}

float balance_check(char *acc_id) {
    FILE *acc_fp;
    float amount = 0, temp;


    char filename[20];
    sprintf(filename, "%s.txt", acc_id);
                
    acc_fp = fopen(filename, "r");
    
    while (fscanf(acc_fp, "%f", &temp) != EOF) {
        amount += temp;
    }
    fclose(acc_fp);
    
    printf("\nYOUR CURRENT BALANCE IS: %.2f\n", amount);
    return amount;
}

void fixed_deposit(char *acc_id) {
    printf("\nOUR BANK PROVIDES THE FOLLOWING SCHEMES FOR FIXED DEPOSIT!!!");
    printf("\nIF THE AMOUNT IS LESS THAN Rs100000 & TENURE IS LESS THAN 1YEAR THEN WE PROVIDE A RATE OF INTEREST OF 4.5%");
    printf("\nIF THE AMOUNT IS LESS THAN Rs100000 & TENURE IS LESS THAN 3YEARS THEN WE PROVIDE A RATE OF INTEREST OF 5%");
    printf("\nIF THE AMOUNT IS LESS THAN Rs100000 & TENURE IS GREATER THAN 3YEARS THEN WE PROVIDE A RATE OF INTEREST OF 5.5%");
    printf("\nIF THE AMOUNT IS GREATER THAN Rs100000 & TENURE IS LESS THAN 1YEAR THEN WE PROVIDE A RATE OF INTEREST OF 5%");
    printf("\nIF THE AMOUNT IS GREATER THAN Rs100000 & TENURE IS LESS THAN 3YEARS THEN WE PROVIDE A RATE OF INTEREST OF 5.5%");
    printf("\nIF THE AMOUNT IS GREATER THAN Rs100000 & TENURE IS GREATER THAN 3YEARS THEN WE PROVIDE A RATE OF INTEREST OF 6%");
    float amount;
    int tenure;
    float amt=balance_check(acc_id);
    printf("\nTHE MINIMUM AMOUNT FOR FIXED DEPOSIT IS RS 20000");
    printf("\nTHE MINIMUM TENURE IS 0.5 years(6 months)");
    t:
    printf("\nEnter Amount for Fixed Deposit: ");
    scanf("%f", &amount);
    if(amt<amount){
        printf("\nINSUFFICIENT BALANCE......NOT ELIGIBLE FOR FIXED DEPOSIT");
        goto t;
    }
    printf("\nEnter Tenure (in years): ");
    scanf("%d", &tenure);
    if((amount<20000)||(tenure<0.5)){
        char ch;
        printf("\nNOT ELIGIBLE FOR FIXED DEPOSIT......PLEASE ENTER A VALID AMOUNT OR TENURE");
        printf("\nDo you want to continue Y or y for Yes and N or n for no");
        scanf(" %c",&ch);
        if(ch=='Y'||ch=='y'){
            goto t;
        }
        else{
            printf("\nYOU ARE DIRECTED BACK TO MAIN-MENU");
        }
        
    }
    float interest_rate = 0;
    
    if (amount < 100000) {
        if (tenure <= 1) {
            interest_rate = 4.5;
        } else if (tenure <= 3) {
            interest_rate = 5.0;
        } else {
            interest_rate = 5.5;
        }
    } else {
        if (tenure <= 1) {
            interest_rate = 5.0;
        } else if (tenure <= 3) {
            interest_rate = 5.5;
        } else {
            interest_rate = 6.0;
        }
    }
    
    float maturity_amount = amount + ((amount * interest_rate * tenure) / 100);
    printf("YOUR MATURITY AMOUNT IS:Rs%.2f",maturity_amount);
    

    FILE *temp_fp;
    float amount1;
    
    amount1=amount;
    
    char ref_num[30];
    sprintf(ref_num, "%sFD%d", acc_id, rand());
    
    temp_fp = fopen("iitbanktemp.txt", "a");
    fprintf(temp_fp, "%s Withdraw %.2f %s\n", acc_id, amount1, ref_num);
    fclose(temp_fp);
    
    printf("\nTemporary Reference Number for Withdrawal: %s\n", ref_num);

}

void admin_user() {
    char admin_id[15] = "admin";
    char admin_password[15] = "admin123";
    char entered_id[15], entered_password[15];
    
    printf("\nEnter Admin ID: ");
    scanf("%s", entered_id);
    printf("Enter Admin Password: ");
    scanf("%s", entered_password);
    
    if (strcmp(admin_id, entered_id) != 0 || strcmp(admin_password, entered_password) != 0) {
        printf("Invalid Admin ID or Password!\n");
        return;
    }
    while (1) {
        int l;
        printf("\nAdmin Menu\n");
        printf("1. Approve Transactions\n");
        printf("2. Check Account Balance\n");
        printf("3. Add New Account\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&l);
        
        switch (l) {
            case 1:
                approve_transactions();
                break;
            case 2:
                check_account_balance();
                break;
            case 3:
                new_user();
                break;
            case 0:
                return;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
}

void approve_transactions() {
    FILE *temp_fp, *acc_fp, *temp_fp_new;
        char ref_num[30], acc_id[15], type[10];
        float amount;
        int found = 0;
        
        printf("\nEnter Reference Number (or 0 to exit): ");
        scanf("%s", ref_num);
        
        if (strcmp(ref_num, "0") == 0) {
            return;
        }
        
        temp_fp = fopen("iitbanktemp.txt", "r");
        if (temp_fp == NULL) {
            printf("Error in opening temporary file!\n");
            return;
        }
        
        temp_fp_new = fopen("iitbanktempnew.txt", "w");
        
        while (fscanf(temp_fp, "%s %s %f %s", acc_id, type, &amount, ref_num) != EOF) {
            if (strcmp(ref_num, ref_num) == 0) {
                found = 1;
                
                char filename[20];
                sprintf(filename, "%s.txt", acc_id);
                
                acc_fp = fopen(filename, "a");
                if (acc_fp == NULL) {
                    printf("Error in opening account file!\n");
                    fclose(temp_fp);
                    fclose(temp_fp_new);
                    return;
                }
                
                if (strcmp(type, "Deposit") == 0) {
                    fprintf(acc_fp, "+%.2f\t", amount);
                } else if (strcmp(type, "Withdraw") == 0) {
                    fprintf(acc_fp, "-%.2f\t", amount);
                }
                
                fclose(acc_fp);
            } else {
                fprintf(temp_fp_new, "%s %s %.2f %s\n", acc_id, type, amount, ref_num);
            }
        }
        
        fclose(temp_fp);
        fclose(temp_fp_new);
        
        remove("iitbanktemp.txt");
        rename("iitbanktempnew.txt", "iitbanktemp.txt");
        
        if (found) {
            printf("\nTransaction completed successfully!!!\n");
        } else {
            printf("No such reference number found!\n");
        }
}

void check_account_balance() {
    char acc_id[15];
    printf("\nEnter  your Account ID to check balance: ");
    scanf("%s", acc_id);

    FILE *acc_fp;
    float amount = 0, temp;
    char filename[20];
    sprintf(filename, "%s.txt", acc_id);
                
    acc_fp = fopen(filename, "r");
    

    if (acc_fp == NULL) {
        printf("\nAccount ID not found!\n");
        return;
    }

    while (fscanf(acc_fp, "%f", &temp) != EOF) {
        amount += temp;
    }
    fclose(acc_fp);

    printf("\nCurrent Balance for Account ID %s: %.2f\n", acc_id, amount);
}


void fund_transfer(char *acc_id){
    int ch;
    FILE *ft;
    printf("Welcome To The Account Fund Transfer Section Of Bank Of IITians\n");
    printf("We Offer The Following Types Of Fund Transfer\n");

    while (1) {
        printf("Kindly Choose The Desired Option:\n");
        printf("1. NEFT\n2. IMPS\n3. RTGS\n4. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Using This Service The Fund Transfer Will Take Upto 4 Hours To Get Settled\n");
                printf("There Is No Maximum Transaction Limit Associated With This Service\n");
                
                while (1) {
                    int d;
                    printf("Press 1 To Continue Or 2 To Return To The Previous Menu: ");
                    scanf("%d", &d);
                    
                    switch (d) {
                        case 1:
                            neft(acc_id);
                            break;
                        case 2:
                            break; 
                        default:
                            printf("Invalid Choice!! Kindly Enter A Valid Option\n");
                    }
                    
                    if (d == 2) {
                        break; 
                    }
                }
                break;

            case 2:
                printf("Using This Service You Can Transfer Funds 24/7\nMaximum Transaction Amount=Rs 5,00,000\n");
                
                while (1) {
                    int e;
                    printf("Press 1 To Continue Or 2 To Return To The Previous Menu: ");
                    scanf("%d", &e);
                    
                    switch (e) {
                        case 1:
                            imps(acc_id);
                            break;
                        case 2:
                            break; 
                        default:
                            printf("Invalid Choice!! Kindly Enter A Valid Option\n");
                    }
                    
                    if (e == 2) {
                       break; 
                    }
                }
                break;

            case 3:
                printf("Using This Service You Can Transfer Funds 24/7\nMaximum Transaction Amount=Rs 2,00,00,000\n");
                
                while (1) {
                    int f;
                    printf("Press 1 To Continue Or 2 To Return To The Previous Menu: ");
                    scanf("%d", &f);
                    
                    switch (f) {
                        case 1:
                            rtgs(acc_id);
                            break;
                        case 2:
                            break; 
                        default:
                            printf("Invalid Choice!! Kindly Enter A Valid Option\n");
                    }
                    
                    if (f == 2) {
                        break; 
                    }
                }
                break;

            case 4:
                printf("\nYOU ARE DIRECTED BACK TO MAIN-MENU");
                return;
                break;
                
            
            default:
                printf("\nInvalid Choice!! Kindly Enter A Valid Option");
                break;
        }
    }
    return ;
}
void neft(char* acc_id) {
    struct f_t {
        int ran;
        char acct[15];
        float a;
    } ftt;

    FILE *ft;
    ft = fopen("iitbanktemp.txt", "a");
    if (ft == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    srand((unsigned int)time(NULL));

    printf("Thank You For Choosing NEFT Option\n");

    printf("Enter the Account ID To Which You Want To Deposit The Amount:");
    fgets(ftt.acct, 15, stdin);
    ftt.acct[strcspn(ftt.acct, "\n")] = '\0';
    while (getchar() != '\n');

    float current_balance = balance_check(acc_id);
    printf("Your current account balance is %.2f\n", current_balance);

    while (1) {
        printf("Enter The Amount To Be Transferred: ");
        scanf("%f", &ftt.a);

        if (ftt.a <= 0) {
            printf("Invalid amount. Please enter a positive value.\n");
            continue;
        }

        if (ftt.a > current_balance) {
            printf("Insufficient balance!");
            printf("Please enter an amount which is less than or equal to your current balance or 0 to cancel: ");
            float new_amount;
            scanf("%f", &new_amount);
            if (new_amount == 0) {
                printf("Transaction cancelled.\n");
                fclose(ft);
                return;
            }
            ftt.a = new_amount;
            continue;
        }

        break;
    }

    printf("Your Transaction Has Been Posted Successfully!!\n");

    char ref[20]; 
    sprintf(ref, "%sFTN%d", acc_id, rand()); 
    printf("Your TRANSACTION ID : %s\n", ref); 
    fprintf(ft, "%s NEFT %.2f %s\n", acc_id, ftt.a, ref);
    fclose(ft);
    char filename[20];
    sprintf(filename, "%s.txt", acc_id);
    FILE *acc_fp;
    acc_fp = fopen(filename, "a");
    fprintf(acc_fp, "-%.2f\t", ftt.a);
    fclose(acc_fp);
    char filename1[20];
    sprintf(filename1, "%s.txt", ftt.acct);
    FILE *acc_fp1;
    acc_fp1 = fopen(filename1, "a");
    fprintf(acc_fp1, "+%.2f\t", ftt.a);
    fclose(acc_fp1);

    return;
}


void imps(char* acc_id) {
    struct f_t {
        int ran;
        char acct[15];
        float a;
    } ftt;

    FILE *ft;
    ft = fopen("iitbanktemp.txt", "a");
    if (ft == NULL) {
        printf("Error in opening file!\n");
        return;
    }

    srand((unsigned int)time(NULL));

    printf("Thank You For Choosing IMPS Option\n");

    printf("Enter the Account ID To Which You Want To Deposit The Amount:");
    fgets(ftt.acct, 15, stdin);
    ftt.acct[strcspn(ftt.acct, "\n")] = '\0';
    while (getchar() != '\n');

    float current_balance = balance_check(acc_id);
    printf("Your current account balance is %.2f\n", current_balance);

    while (1) {
        printf("Enter The Amount To Be Transferred (Less Than Rs 500000): ");
        scanf("%f", &ftt.a);

        if (ftt.a <= 0) {
            printf("Invalid amount. Please enter a positive value.\n");
            continue;
        }

        if (ftt.a > current_balance) {
            printf("Insufficient balance! ");
            printf("Please enter an amount which is less than or equal to your current balance or 0 to cancel: ");
            float new_amount;
            scanf("%f", &new_amount);
            if (new_amount == 0) {
                printf("Transaction cancelled.\n");
                fclose(ft);
                return;
            }
            ftt.a = new_amount;
            continue;
        }

        break;
    }

    printf("Your Transaction Has Been Posted Successfully!!\n");

    char ref[20];
    sprintf(ref, "%sFTI%d", acc_id, rand());

    printf("Your Reference Number Is: %s\n", ref);

    fprintf(ft, "%s IMPS %.2f %s\n", acc_id, ftt.a, ref);

    fclose(ft);
    char filename[20];
    sprintf(filename, "%s.txt", acc_id);
    FILE *acc_fp;
    acc_fp = fopen(filename, "a");
    fprintf(acc_fp, "-%.2f\t", ftt.a);
    fclose(acc_fp);
    char filename1[20];
    sprintf(filename1, "%s.txt", ftt.acct);
    FILE *acc_fp1;
    acc_fp1 = fopen(filename1, "a");
    fprintf(acc_fp1, "+%.2f\t", ftt.a);
    fclose(acc_fp1);

    return;
}


 void rtgs(char* acc_id) {
    struct f_t {
        int ran;
        char acct[15];
        float a;
    } ftt;

    FILE *ft;
    ft = fopen("iitbanktemp.txt", "a");
    if (ft == NULL) {
        printf("Error in opening file!\n");
        return;
    }

    srand((unsigned int)time(NULL));

    printf("Thank You For Choosing RTGS Option\n");

    printf("Enter the Account ID To Which You Want To Deposit The Amount:");
    fgets(ftt.acct, 15, stdin);
    ftt.acct[strcspn(ftt.acct, "\n")] = '\0';
    while (getchar() != '\n');

    float current_balance = balance_check(acc_id);
    printf("Your current account balance is %.2f\n", current_balance);

    while (1) {
        printf("Enter The Amount To Be Transferred (Less Than Rs 2000000): ");
        scanf("%f", &ftt.a);

        if (ftt.a <= 0) {
            printf("Invalid amount. Please enter a positive value.\n");
            continue;
        }

        if (ftt.a > current_balance) {
            printf("Insufficient balance! ");
            printf("Please enter an amount which is less than or equal to your current balance or 0 to cancel: ");
            float new_amount;
            scanf("%f", &new_amount);
            if (new_amount == 0) {
                printf("Transaction cancelled.\n");
                fclose(ft);
                return;
            }
            ftt.a = new_amount;
            continue;
        }

        break;
    }

    printf("Your Transaction Has Been Posted Successfully!!\n");

    char ref[20];
    sprintf(ref, "%sFTR%d", acc_id, rand());

    printf("Your TRANSACTION ID is: %s\n", ref);
    fprintf(ft, "%s RTGS %.2f %s\n", acc_id, ftt.a, ref);

    fclose(ft);
    char filename[20];
    sprintf(filename, "%s.txt", acc_id);
    FILE *acc_fp;
    acc_fp = fopen(filename, "a");
    fprintf(acc_fp, "-%.2f\t", ftt.a);
    fclose(acc_fp);
    char filename1[20];
    sprintf(filename1, "%s.txt", ftt.acct);
    FILE *acc_fp1;
    acc_fp1 = fopen(filename1, "a");
    fprintf(acc_fp1, "+%.2f\t", ftt.a);
    fclose(acc_fp1);

    return;
}

void loan(char *acc_id) {
    int ch;
    printf("Welcome To The Loan Section Of Bank Of IITians\n");
    printf("We Offer The Following Types Of Loans To Our Customers\n");

    while (1) {
        printf("Kindly Choose The Desired Option:\n");
        printf("1. Housing Loan\n2. Educational Loan\n3. Car Loan\n4. Exit\n");
        printf("Enter Your Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                printf("Welcome to our Housing Loan Program!\n");
                printf("Find your dream home with ease with our competitive loan terms.\n");
                printf("---------------------------------------------\n");
                printf("Loan Amount: Upto Rs 20000000\n"); 
                printf("Interest Rate: 8.12 Percent per annum\n"); 
                printf("Loan Term: Upto 30 years\n"); 
                printf("Monthly Installment: Will Vary\n");
                printf("Total Interest Payable: Will Vary\n"); 
                printf("Total Payment Amount: Will Vary\n"); 
                printf("Additional Processing Fees:4000 \n"); 
                printf("Loan Approval Criteria: Should Be A Salaried Or A Business Owner\n"); 
                printf("Collateral Requirement: Funds Or Properties Equivalent To Rs10000000\n"); 
                printf("Loan Repayment Schedule: Monthly\n"); 
                printf("Early Repayment Penalty: No\n"); 
                printf("Contact Admin for further information!\n");
                
                while (1) {
                    int d;
                    printf("Press 1 To Continue Or 2 To Return To The Previous Menu: ");
                    scanf("%d", &d);
                    
                    switch (d) {
                        case 1:
                            house(acc_id);
                            break;
                        case 2:
                            break; 
                        default:
                            printf("Invalid Choice!! Kindly Enter A Valid Option\n");
                    }
                    
                    if (d == 2) {
                        break; 
                    }
                }
                break;

            case 2:
                printf("Welcome to our Educational Loan Program!\n");
                printf("Fullfill your dreams with ease with our competitive loan terms.\n");
                printf("---------------------------------------------\n");
                printf("Loan Amount: Upto Rs 2000000\n"); 
                printf("Interest Rate: 5.12 Percent per annum\n"); 
                printf("Loan Term: Upto 10 years (Including Study Period)\n"); 
                printf("Monthly Installment: Will Vary\n");
                printf("Total Interest Payable: Will Vary\n"); 
                printf("Total Payment Amount: Will Vary\n"); 
                printf("Additional Processing Fees:NIL \n"); 
                printf("Loan Approval Criteria: must Have secured admission into an institute\n"); 
                printf("Collateral Requirement: No\n"); 
                printf("Loan Repayment Schedule: Monthly After Graduation\n"); 
                printf("Early Repayment Penalty: No\n"); 
                printf("Contact Admin for further information!\n");
                
                while (1) {
                    int e;
                    printf("Press 1 To Continue Or 2 To Return To The Previous Menu: ");
                    scanf("%d", &e);
                    
                    switch (e) {
                        case 1:
                            educ(acc_id);
                            break;
                        case 2:
                            break; 
                        default:
                            printf("Invalid Choice!! Kindly Enter A Valid Option\n");
                    }
                    
                    if (e == 2) {
                       break; 
                    }
                }
                break;

            case 3:
                printf("Welcome to our Housing Loan Program!\n");
                printf("Find your dream home with ease with our competitive loan terms.\n");
                printf("---------------------------------------------\n");
                printf("Loan Amount: Upto Rs 5000000\n"); 
                printf("Interest Rate: 11.12 Percent per annum\n"); 
                printf("Loan Term: Upto 5 years\n"); 
                printf("Monthly Installment: Will Vary\n");
                printf("Total Interest Payable: Will Vary\n"); 
                printf("Total Payment Amount: Will Vary\n"); 
                printf("Additional Processing Fees:4000 \n"); 
                printf("Loan Approval Criteria: Should Be Salaried Or ABusiness Owner\n"); 
                printf("Collateral Requirement: Funds Or Properties Equivalent To The Car Value\n"); 
                printf("Loan Repayment Schedule: Monthly\n"); 
                printf("Early Repayment Penalty: No\n"); 
                printf("Contact Admin for more information!\n");
                
                while (1) {
                    int f;
                    printf("Press 1 To Continue Or 2 To Return To The Previous Menu: ");
                    scanf("%d", &f);
                    
                    switch (f) {
                        case 1:
                            car(acc_id);
                            break;
                        case 2:
                            break; 
                        default:
                            printf("Invalid Choice!! Kindly Enter A Valid Option\n");
                    }
                    
                    if (f == 2) {
                        break; 
                    }
                }
                break;

            case 4:
                printf("YOU ARE BEING DIRECTED BACK TO MAIN-MENU\n");
                return;
                break;
                

            default:
                printf("Invalid Choice!! Kindly Enter A Valid Option\n");
        }
    }
    return ;
}
     void house(char* acc_id) {
    struct f_t {
        int ran; 
        char acct[15];
        float a;
    } ftt;

    FILE *ft;
    ft = fopen("iitbanktemp.txt", "a");
    if (ft == NULL) {
        printf("Error in opening file!\n");
        return;
    }

    srand((unsigned int)time(NULL));

    printf("Thank You For Choosing Our Loan Option\n");

    printf("Enter the Amount Of Loan: ");
    scanf("%f", &ftt.a);
    printf("Enter The Repayment Period (in months): ");
    scanf("%d", &ftt.ran); 
    getchar(); 

    printf("Your Application Has Been Submitted Successfully!!\n");

    char ref[20];
    sprintf(ref, "%sLOANH%d", acc_id, rand());

    printf("Your Reference Number Is: %s\n", ref);

    fprintf(ft, "%s Deposit %.2f %s\n", acc_id, ftt.a, ref); 

    fclose(ft);

    return;
}
 void educ(char* acc_id) {
    struct f_t {
        int ran;
        char acct[15];
        float a;
    } ftt;

    FILE *ft;
    ft = fopen("iitbanktemp.txt", "a");
    if (ft == NULL) {
        printf("Error in opening file!\n");
        return;
    }

    srand((unsigned int)time(NULL));

    printf("Thank You For Choosing Our Loan Option\n");

    printf("Enter the Amount Of Loan: ");
    scanf("%f", &ftt.a);
    printf("Enter The Repayment Period (in months): ");
    scanf("%d", &ftt.ran); 
    getchar(); 
    printf("Your Application Has Been Submitted Successfully!!\n");

    char ref[20];
    sprintf(ref, "%sLOANC%d", acc_id, rand()); 
    printf("Your Reference Number Is: %s\n", ref); 
    fprintf(ft, "%s Deposit %.2f %s\n", acc_id, ftt.a, ref);

    fclose(ft);

    return;
}
 void car(char* acc_id) {
    struct f_t {
        int ran;
        char acct[15];
        float a;
    } ftt;

    FILE *ft;
    ft = fopen("iitbanktemp.txt", "a");
    if (ft == NULL) {
        printf("Error in opening file!\n");
        return;
    }

    srand((unsigned int)time(NULL));

    printf("Thank You For Choosing Our Loan Option\n");

    printf("Enter the Amount Of Loan: ");
    scanf("%f", &ftt.a);
    printf("Enter The Repayment Period (in months): ");
    scanf("%d", &ftt.ran); 
    getchar(); 
    printf("Your Application Has Been Submitted Successfully!!\n");

    char ref[20]; 
    sprintf(ref, "%sLOANE%d", acc_id, rand()); 

    printf("Your Reference Number Is: %s\n", ref); 

    fprintf(ft, "%s Deposit %.2f %s\n", acc_id, ftt.a, ref);

    fclose(ft);

    return;
}
void cheque(char *acc_id) {
    printf("\nDO YOU WANT TO ISSUE A CHECK BOOK? Y FOR YES AND N FOR NO\n");
    char ch;
    printf("Enter a choice:");
    scanf(" %c", &ch);
    char filename[100];
    sprintf(filename, "%s.txt", acc_id);

    if (ch == 'Y' || ch == 'y') {
        printf("\n20 pages for Rs70");
        printf("\n50 pages for Rs120");

        int c;
        do {
            printf("\nChoice is 1 for 20 pages and 2 for 50 pages\n");
            printf("Enter your choice:");
            scanf("%d", &c);

            switch (c) {
                case 1: {
                    int amount = 70;
                    
                    FILE *acc_fp = fopen(filename, "a");
                    if (acc_fp != NULL) {
                        fprintf(acc_fp, "-%.2f\t", (float)amount);
                        printf("\nYOUR CHEQUE BOOK WILL BE DELIVERED WITHIN SEVEN DAYS\n");
                        fclose(acc_fp); 
                    } else {
                        printf("Error in opening file for writing.\n");
                    }
                    break;
                }
                case 2: {
                    int amount = 120;
                    
                    FILE *acc_fp = fopen(filename, "a");
                    if (acc_fp != NULL) {
                        fprintf(acc_fp, "-%.2f\t", (float)amount);
                        printf("\nYOUR CHEQUE BOOK WILL BE DELIVERED WITHIN SEVEN DAYS\n");
                        fclose(acc_fp); 
                    } else {
                        printf("Error in opening file for writing.\n");
                    }
                    break;
                }
                default:
                    printf("\nINVALID CHOICE....TRY AGAIN.\n");
            }
        } while (c != 1 && c != 2); 
    } else {
        printf("\nNo cheque book issued.\n");}
    return;}
void atm(char *acc_id) {
    printf("Our Bank Offers following Debit Card Services For Its Customers:\n");    
    int ch;
    printf("Please choose 1 to continue\n");
    while (1) {
        if (scanf("%d", &ch) != 1) {
            printf("Invalid input. Please enter 1. ");
            while (getchar() != '\n'); 
            continue;
        }
        
        switch (ch) {
            case 1: {
                float balance = balance_check(acc_id);
                if (balance >= 3250.00) {
                    printf("You have sufficient balance to issue the Domestic Debit Card.\n");
                    printf("The Domestic Debit Card allows you to withdraw cash from any ATM within the country along with cashless transactions at POS.\n");
                    printf("Minimum account balance for using this card is Rs. 3250\n");
                    printf("The annual maintenance charges for this card is Rs 250.\n");

                    printf("Would you like to issue the Domestic Debit Card?\n");
                    printf("1. Yes\n");
                    printf("2. No\n");

                    int choice;
                    printf("Enter your choice: ");
                    while (1) {
                        if (scanf("%d", &choice) != 1) {
                            printf("Invalid input. Please enter a valid choice: ");
                            while (getchar() != '\n'); 
                            continue;
                        }
                        if (choice == 1) {
                            printf("Your card will be delivered to your registered address within 15 days of approval from the admin.\n");
                            printf("YOU ARE DIRECTED BACK TO MAIN-MENU.\n");
                            char filename[20];
                            sprintf(filename, "%s.txt", acc_id);
                            FILE *acc_fp;
                            acc_fp = fopen(filename, "a");
                            fprintf(acc_fp, "-%.2f\t", 250.0);
                            fclose(acc_fp);

                            srand((unsigned int)time(NULL));
                            long long int card_number = 1000000000000000 + rand() % (9999999999999999 - 1000000000000000 + 1);
                            int pin = 1000 + rand() % (9999 - 1000 + 1);
                            card_info(acc_id, card_number, pin);

                            printf("Your card has been issued with the following details:\n");
                            printf("Card Number: %lld\n", card_number);
                            printf("PIN: %04d\n", pin);
                            printf("Your card will be delivered to your registered address within 15 days of approval from the admin.\n");
                            
                        } else if (choice == 2) {
                            printf("No card issued.\n");
                        } else {
                            printf("Invalid choice! Please enter 1 for Yes or 2 for No: ");
                            continue;
                        }
                        break;
                    }
                } else {
                    printf("Insufficient balance to issue the Domestic Debit Card. Minimum balance required is Rs. 3250.\n");
                }
                break;
            }
            default:
                printf("Invalid choice! Please choose 1 for Debit Cards: ");
                break;
        }
        break;
    }
}
void card_info(char *acc_id, long long int card_number, int pin) {
    FILE *atm_file = fopen("atm.txt", "a");
    if (atm_file != NULL) {
        fprintf(atm_file, "%s %lld %04d\n", acc_id, card_number, pin);
        fclose(atm_file);
    } else {
        printf("Error: Unable to open ATM file for writing.\n");
    }
}
 char* verify_card_details(long long int card_number, int pin) {
    FILE *atm_file = fopen("atm.txt", "r");
    if (atm_file != NULL) {
        char* acc_id = malloc(15 * sizeof(char)); // Allocate memory dynamically
        if (acc_id == NULL) {
            printf("Error: Memory allocation failed.\n");
            fclose(atm_file);
            return NULL;
        }

        long long int stored_card_number;
        int stored_pin;
        while (fscanf(atm_file, "%s %lld %d", acc_id, &stored_card_number, &stored_pin) != EOF) {
            if (card_number == stored_card_number && pin == stored_pin) {
                fclose(atm_file);
                return acc_id;
            }
        }
        free(acc_id);
        fclose(atm_file);
    } else {
        printf("Error: Unable to open ATM file for reading.\n");
    }
    return NULL;
}

void atm_use() {
    long long int card_number;
    int pin;

    printf("Enter the debit card number (16 digits): ");
    scanf("%lld", &card_number);

     
    printf("Enter the PIN (4 digits): ");
    scanf("%d", &pin);

     
    char *acc_id = verify_card_details(card_number, pin);

     
    if (acc_id != NULL) {
        printf("Card details verified.\n");
        printf("Account ID associated with the card: %s\n", acc_id);
        float a;
        printf("Enter The Amount You Want to Withdraw:");
        scanf("%f",&a);
        char filename[20];
        sprintf(filename, "%s.txt", acc_id);
        FILE *acc_fp;
        acc_fp = fopen(filename, "a");
        fprintf(acc_fp, "-%.2f\t", a);
        fclose(acc_fp);

    } else {
        printf("Invalid card details.\n");
    }
    return;
}