/**
* ENGG1110 Problem Solving by Programming
*
* Course Project
*
* I declare that the project here submitted is original
* except for source material explicitly acknowledged,
* and that the same or closely related material has not been
* previously submitted for another course.
* I also acknowledge that I am aware of University policy and
* regulations on honesty in academic work, and of the disciplinary
* guidelines and procedures applicable to breaches of such
* policy and regulations, as contained in the website.
*
* University Guideline on Academic Honesty:
* https://www.cuhk.edu.hk/policy/academichonesty/
*
* Student Name : Jihun, HAN
* Student ID : 1155128719
* Class/Section : ENGG1110A
* Date : 02/01/2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct product {
    char productCode;
	char productName[20];
	int productPrice;
	int numOfGoods;
} product;

struct machine {
	product products[5];
    char productAvailability[5]; // 'X' = Not available, 'O' = Available.
	int revenueRaised;
	int insertedCoin;
    int password;
};
typedef struct machine* machineADT;


void printMachineOnCLI(machineADT machine, char productCodeOut) {
    printf("\n");
    printf("*---------------------------*\n");
    printf("|      Vending Machine      |\n");
    printf("*---------------------------*\n");
    printf("|   A    B    C    D    E   |\n");
    printf("|  ");
    for (int i = 0; i < 5; i++) {
        printf("$%2d  ", machine->products[i].productPrice);
    }
    printf("|\n");
    printf("|  ");
    for (int i = 0; i < 5; i++) {
        printf("[%c]  ", machine->productAvailability[i]);
    }
    printf("|\n");
    printf("*---------------------------*\n");
    printf("|                    [$ %2d] |\n", machine->insertedCoin);
    printf("|                           |\n");
    printf("|           [=%c=]           |\n", productCodeOut);
    printf("*---------------------------*\n");
}

void readProductsInfo(machineADT machine) {
    printf("\n");
    printf("(1) The displayed products are:\n");
    for (int i = 0; i < 5; i++) {
        printf(
            "%c. %s ($%d)\n", 
            machine->products[i].productCode, machine->products[i].productName, machine->products[i].productPrice
        );
    }
}

void insertCoinToMachine(machineADT machine, int choice) {
    int coin;
    switch (choice) 
    {
    case 1: coin = 1; break;
    case 2: coin = 2; break;
    case 3: coin = 5; break;
    case 4: coin = 10; break;
    }
    printf("You have inserted $%d.\n", coin);
    machine->insertedCoin += coin;
    for (int i = 0; i < 5; i++) {
        if (machine->productAvailability[i] == 'X') {
            continue;
        }
        else if (machine->insertedCoin >= machine->products[i].productPrice) {
            if (machine->productAvailability[i] == 'O') {
                continue;
            }
            else {
                machine->productAvailability[i] = 'O';
            }
        }
    }
}

void checkAvailability(machineADT machine) {
    for (int i = 0; i < 5; i++) {
        if (machine->products[i].numOfGoods == 0) {
            machine->productAvailability[i] = 'X';
            continue;
        }
        else if (machine->insertedCoin < machine->products[i].productPrice) {
            machine->productAvailability[i] = ' ';
        }
    }
}

void dispenseProduct(machineADT machine, int choice) {
    printf("You have pressed button %c.\n", machine->products[choice-1].productCode);
    if (machine->insertedCoin >= machine->products[choice-1].productPrice && machine->productAvailability[choice-1] == 'O') {
        machine->insertedCoin -= machine->products[choice-1].productPrice;
        machine->revenueRaised += machine->products[choice-1].productPrice;
        machine->products[choice-1].numOfGoods -= 1;
        checkAvailability(machine);
        printMachineOnCLI(machine, machine->products[choice-1].productCode);
    }
    else {
        // '=' = Nothing to dispense.
        printMachineOnCLI(machine, '=');
    }
}

int checkAdmin() {
    printf("\n");
    printf("(9) Opening service menu. Access code is required.\n");
    printf("Enter access code: ");
    int code;
    scanf("%d", &code);
    return code;
}

void inspectMachineStatus(machineADT machine) {
    printf("\n");
    printf("(9-1) Machine status\n");
    printf("Amount of revenue: $%d\n", machine->revenueRaised);
    printf("Amount of inserted coins: $%d\n", machine->insertedCoin);
    printf("Product information:\n");
    for (int i = 0; i < 5; i++) {
        if (machine->products[i].numOfGoods == 0) {
            // sold out
            printf("%c. %s ($%d) (sold out)\n", 
            machine->products[i].productCode, machine->products[i].productName, machine->products[i].productPrice);
        }
        else {
            printf("%c. %s ($%d) (%d left)\n", 
            machine->products[i].productCode, machine->products[i].productName, machine->products[i].productPrice, machine->products[i].numOfGoods);
        }
    }
}

int printMainMenu() {
    printf("\n");
    printf("What would you like to do?\n");
    printf("1. Read product information\n");
    printf("2. Insert coin\n");
    printf("3. Press product button\n");
    printf("4. Press return button\n");
    printf("9. Open service menu (code required)\n");
    printf("0. Quit\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

int printCoinMenu() {
    printf("\n");
    printf("(2) Which coin would you like to insert?\n");
    printf("1. $1\n");
    printf("2. $2\n");
    printf("3. $5\n");
    printf("4. $10\n");
    printf("0. Go back\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

int printProductMenu() {
    printf("\n");
    printf("(3) Which product button would you like to press?\n");
    printf("1. A\n");
    printf("2. B\n");
    printf("3. C\n");
    printf("4. D\n");
    printf("5. E\n");
    printf("0. Go back\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

int printServiceMenu() {
    printf("\n");
    printf("(9) What would you like to do?\n");
    printf("1. Inspect machine status\n");
    printf("2. Withdraw all money\n");
    printf("3. Refill product\n");
    printf("4. Change product\n");
    printf("0. Go back\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

int printRefillMenu() {
    printf("\n");
    printf("(9-3) Which product would you like to refill?\n");
    printf("1. A\n");
    printf("2. B\n");
    printf("3. C\n");
    printf("4. D\n");
    printf("5. E\n");
    printf("0. Go back\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

int printProductChangeMenu() {
    printf("\n");
    printf("(9-4) Which product would you like to change?\n");
    printf("1. A\n");
    printf("2. B\n");
    printf("3. C\n");
    printf("4. D\n");
    printf("5. E\n");
    printf("0. Go back\n");
    printf("Your choice: ");
    int choice;
    scanf("%d", &choice);
    return choice;
}

int main() {
    machineADT machine = (machineADT)malloc(sizeof(*machine));
    product products[5];
    char productCode[5] = {'A', 'B', 'C', 'D', 'E'};
    char productName[5][20] = {"Juice", "Cola", "Tea", "Water", "Coffee"};
    int productPrice[5] = {10, 6, 5, 8, 7};
    int numOfGoods[5] = {5, 1, 2, 1, 9};
    for (int i = 0; i < 5; i++) {
        products[i].productCode = productCode[i];
        strcpy(products[i].productName, productName[i]);
        products[i].productPrice = productPrice[i];
        products[i].numOfGoods = numOfGoods[i];
        machine->products[i] = products[i];
        machine->productAvailability[i] = ' '; // ' ' = Default.
    }
    machine->revenueRaised = 0;
    machine->insertedCoin = 0;
    machine->password = 1110;
    
    // Start running.
    printMachineOnCLI(machine, '=');
    bool RUN_MAINMENU = true;
    while (RUN_MAINMENU != false) {
        int mainChoice = printMainMenu();
        switch (mainChoice)
        {
        case 1: {
            readProductsInfo(machine);
            break;
        }
        case 2: {
            bool RUN_COINMENU = true;
            while (RUN_COINMENU != false) {
                int coinChoice = printCoinMenu();
                if (coinChoice > 4 || coinChoice < 0) {
                    printf("Invalid choice!\n");
                }
                else {
                    if (coinChoice == 0) {
                        printf("Going back!\n");
                        RUN_COINMENU = false;
                    }
                    else {
                        insertCoinToMachine(machine, coinChoice);
                    }
                    printMachineOnCLI(machine, '=');
                }
            }
            break;
        }
        case 3: {
            bool RUN_PRODUCTMENU = true;
            while (RUN_PRODUCTMENU != false) {
                int productChoice = printProductMenu();
                if (productChoice == 0) {
                    printf("Going back!\n");
                    printMachineOnCLI(machine, '=');
                    RUN_PRODUCTMENU = false;
                }
                else if (productChoice > 5 || productChoice < 0) {
                    printf("Invalid choice!\n");
                }
                else {
                    dispenseProduct(machine, productChoice);
                    RUN_PRODUCTMENU = false;
                }
            }
            break;
        }
        case 4: {
            printf("(4) Return button is pressed.\n");
            printf("$%d has been returned.\n", machine->insertedCoin);
            machine->insertedCoin = 0;
            checkAvailability(machine);
            printMachineOnCLI(machine, '=');
            break;
        }
        case 9: {
            int password = checkAdmin();
            if (password != machine->password) {
                printf("Incorrect code!\n");
                printMachineOnCLI(machine, '=');
            }
            else { 
                printf("Correct code!\n");
                // Enter service menu.
                bool RUN_SERVICEMENU = false;
                while (RUN_SERVICEMENU != true) {
                    int serviceChoice = printServiceMenu();
                    switch (serviceChoice)
                    {
                    case 0: {
                        printf("Going back!\n");
                        printMachineOnCLI(machine, '=');
                        RUN_SERVICEMENU = true;
                        break;
                    }
                    case 1: {
                        inspectMachineStatus(machine);
                        break;
                    }
                    case 2: {
                        printf("(9-2) All money is being withdrawn.\n");
                        printf("$%d is withdrawn.\n", machine->insertedCoin + machine->revenueRaised);
                        machine->insertedCoin = 0;
                        machine->revenueRaised = 0;
                        checkAvailability(machine);
                        break;
                    }
                    case 3: {
                        int refillChoice = printRefillMenu();
                        if (refillChoice == 0) {
                            printf("Going back!\n");
                        }
                        else {
                            printf("You have refilled product %c to full.\n", machine->products[refillChoice-1].productCode);
                            machine->products[refillChoice-1].numOfGoods = 10;
                            checkAvailability(machine);
                        }
                        break;
                    }
                    case 4: {
                        int productChangeChoice = printProductChangeMenu();
                        if (productChangeChoice == 0) {
                            printf("Going back!\n");
                        }
                        else if (productChangeChoice > 5 || productChangeChoice < 0) {
                            printf("Invalid choice!\n");
                        }
                        else {
                            char productName[20];
                            int productPrice;
                            printf("You are changing product %c.\n", machine->products[productChangeChoice-1].productCode);
                            printf("Enter new product name: ");
                            scanf("%s", productName);
                            printf("Enter new product price: ");
                            scanf("%d", &productPrice);
                            printf("The new product %c has been filled to full.\n", machine->products[productChangeChoice-1].productCode);
                            strcpy(machine->products[productChangeChoice-1].productName, productName);
                            machine->products[productChangeChoice-1].productPrice = productPrice;
                            machine->products[productChangeChoice-1].numOfGoods = 10;
                            checkAvailability(machine);
                        }
                        break;
                    }
                    default:
                        printf("Invalid chocie!\n");
                    }
                }
            }
            break;
        }
        case 0: {
            RUN_MAINMENU = false;
            printf("\n");
            printf("----------------------------------");
            printf("END OF VENDING MACHINE SIMULATION!\n");
            break;
        }
        default:
            printf("Invalid choice!\n");
        }
    }
}
