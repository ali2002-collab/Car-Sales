#include "./constants.h"
void getStringFromConsole(char* message, char* str) {
    //prompt user
    printf("%s", message);
    //as we're now working with the pointer str, we don't need & here
    scanf("\n%[^\n]s", str);
}



char getCharFromConsole(char* message) {
    char userInput;
    //prompt user using the value of the given message
    printf("%s", message);
    //capture the character
    scanf("\n%c", &userInput);
    //return the captured value
    return userInput;
}



int programOpening() {
    //Menu will be displayed with help of for loop
    printf("\nGreetings! WELCOME TO ALI CAR DEALERSHIP\n");
    for (int i = 0; i < 4; i++) {
        printf("%d. %s", i + 1, options[i]);
        printf("\n");
    }
//Prompt the user to enter their choice
    printf("Enter your choice: ");
    scanf("%d", &user_choice);
//Used a while loop to validate the user's input.
    while (user_choice > 4 || user_choice < 1) {
        printf("INVALID INPUT, ENTER AGAIN: ");
        scanf("%d", &user_choice);
    }
    return user_choice;
}


bool checkIfDiscountNeeded(unsigned short userAge , char nusCard) {
//This function checks if a user is eligible for a discount based on their age and NUS card status.

//Check if the user's age is within the eligible range or if they have an NUS card
    if (userAge >= MINIMUM_AGE && userAge <= MAXIMUM_AGE || nusCard == 'y' ) {
//Prompt the user to enter a valid NUS card option if the current value is invalid
        while ((nusCard != 'y') && (nusCard != 'n')) {
            nusCard = getCharFromConsole("Enter a Valid option: ");
        }
        printf("Congrats! you're eligible for discount\n\n");
        return true;
    }
    else {
        printf("Sorry! you're not eligible for discount\n\n");
        return false;
    }
//returns a boolean value indicating whether the user is eligible for a discount (true) or not (false)
}



double applyDiscount(double currentPrice) {
//This function applies a discount to a given price and returns the discounted price
//The discount percentage is defined by the constant DISCOUNT_PERCENTAGE which is 20%
//Calculates the discounted price by multiplying the original price by the discount percentage (as a decimal)
//Returns the discounted price
    return currentPrice * (1 - DISCOUNT_PERCENTAGE);
}



void initializeStructArray(){
//Initialize cars array with default values
    for (int i = 0; i < 5; i++) {
        strcpy(cars[i].name, carName[i]);
        cars[i].amount = 0;
        cars[i].saleValue = 0;
    }
//Initialize stockCars array with initial stock amounts and sale values
    for (int i = 0; i < 5; i++) {
        strcpy(stockCars[i].name, carName[i]);
        stockCars[i].amount = numberOfCars[i];
        stockCars[i].saleValue = carPrice[i];
    }
}



void stock_Sort(struct Car a[]) {
//Sorts an array of cars in descending order by stock level.
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if (a[j].amount < a[j+1].amount) { //if the current element has less stock than the next element
                struct Car temp = a[j]; //swap the two elements
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }
}



void sale_Sort(struct Car b[]) {
//Sorts an array of cars in descending order based on their sale value.
    struct Car temp;
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (b[i].saleValue < b[j].saleValue) { //If the sale value of the second car is greater than the sale value of the first car
                temp = b[i]; //swap the two cars
                b[i] = b[j];
                b[j] = temp;
            }
        }
    }
}



void fileFunction(double totalPrice, char name[35], int age, bool discount, int noOfCars, char car[5]) {
//This Function writes customer details and purchase information in a CSV format to a file.
    FILE* fileptr = fopen("./Data.csv", "a+");  //appending file cuz writing will overwrite existing data

    //Write customer details and purchase information
    fprintf(fileptr, "Customer Name: %s\n", name);
    fprintf(fileptr, "Customer Age: %d\n", age);
    fprintf(fileptr, "Purchased Car: %s\n", car);
    fprintf(fileptr, "Amount of Cars: %d\n", noOfCars);
//If a discount was applied, write the discount amount and discounted price
    if (discount == true) {
        fprintf(fileptr, "Discount Applied: YES\n");
        fprintf(fileptr, "Discount Amount: %.2f\n", totalPrice * 0.20);
        fprintf(fileptr, "Discounted Price: GBP %.2lf\n", applyDiscount(totalPrice));
    } else { //If no discount was applied, write the price without a discount
        fprintf(fileptr, "Discount Applied: NO\n");
        fprintf(fileptr, "Discount Amount: 0.00\n");
        fprintf(fileptr, "Price: GBP %.2lf\n", totalPrice);
    }
    fprintf(fileptr,"\n\n");
    fclose(fileptr);
}



void receipt(double totalPrice, char name[35], int age, bool discount, int noOfCars, char car[5]) {
//This function generates a receipt for a car purchase, displaying relevant information about the customer and their purchase.
    printf("RECEIPT \n \n"); //Display receipt heading
//Display customer name and age
    printf("Customer Name: %s \n", name);
    printf("Customer Age: %d \n", age);
    if (discount == true) { //Display discount information, if applicable
        double discountPrice = applyDiscount(totalPrice);
        printf("Discount Applied: YES\n");
        printf("Discounted Price: GBP %.2lf\n", discountPrice);
    }
    else if (discount == false) {
        printf("Discount Applied: NO\n");
        printf("Sir Your Bill is GBP %.2lf\n", totalPrice);
    }
    printf("Car Purchased: %s\n", car);
    printf("Amount of Cars: %d \n", noOfCars);//Display number of cars purchased

    printf("\n\n");//Add spacing for visual clarity
    printf("THANKS FOR BUYING CARS FROM US :) \n\n");//Display thank you message

}



void stock() {
//This function sorts the array of cars by their stock level using the stock_Sort function.
//It then prints out the sorted list of cars with their model names, the number of cars available in stock,and their respective sale prices

    stock_Sort(stockCars);
    printf("Car Models:      In Stock:   Car Price:\n");
    printf("\n");
    for (int i = 0; i < 5; i++) { //loop through the array and print the details of each car
        printf("%d: %-15s %5d       GBP %.2lf\n", i + 1, stockCars[i].name, stockCars[i].amount, stockCars[i].saleValue);
    }
    printf("\n");
}



void salesStats(){
//This function displays the overall sales stats by model and customer data
//It reads the sales data from a CSV file and displays it in a readable format
//It also sorts the car models based on their sales in descending order
    int c;
    FILE* f = fopen("./Data.csv", "r");
    if (f == NULL) { //Check if the file exists and is readable
        perror("[DATA NOT FOUND]\n");
        exit(1);
    } else {
        printf("---------- OVERALL SALES ----------- \n\n");
        printf("\n");

        sale_Sort(cars);
        printf("Car Models:      Car Amount:   Revenue:\n");
        for (int i = 0; i < 5; i++) { //Display the sorted car models with their sales value and amount
            printf("%d: %-15s %5d       GBP %.2lf\n", i + 1, cars[i].name, cars[i].amount, cars[i].saleValue);
        }
        printf("\n\n");

        printf("CUSTOMER SALES DATA \n");
        printf("-------------------- \n");

        while (!feof(f)) { //Display the customer sales data from the CSV file
            c = fgetc(f);
            printf("%c", c);
        }

        printf("\n");
    }

    fclose(f);
}




void buyCars() {
    //Function to allow customers to purchase cars and generate a receipt and save the data to a file.

    stock();
    int choice, amountOfCars;
    do { //Get a valid car choice from the user
        printf("Enter an option you want to purchase: ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 5);
    printf("%s is selected\n\n", stockCars[choice - 1].name);

    do { //Get the amount of cars to purchase
        printf("Enter the amount of cars you want to purchase: ");
        scanf("%d", &amountOfCars);
    } while (amountOfCars > stockCars[choice -1].amount);
    //Get customer information
    getStringFromConsole("What is your name: ", information.customer_name);
    printf("\n");
    printf("Enter your age: ");
    scanf("%d", &information.customer_Age);
    printf("\n");
    char nusCardSelection = getCharFromConsole("Do you have a NUS card? (y/n): ");
    //Check if the customer is eligible for a discount
    information.discount = checkIfDiscountNeeded(information.customer_Age, nusCardSelection);

    information.total_Price = stockCars[choice - 1].saleValue * amountOfCars;
    stockCars[choice -1].amount -= amountOfCars; //Calculate the total purchase price and update the stock

    if (information.discount == true) { //Discount applied
        cars[choice -1].saleValue += applyDiscount(information.total_Price);
    }
    else { //Discount not applied
        cars[choice -1].saleValue += information.total_Price;
    }
    cars[choice - 1].amount += amountOfCars; //Update the stock of the chosen car
//Generating a receipt for the purchase and save the data to a file
    receipt(information.total_Price, information.customer_name, information.customer_Age, information.discount, amountOfCars, carName[choice -1]);
    fileFunction(information.total_Price, information.customer_name, information.customer_Age, information.discount, amountOfCars, carName[choice - 1]);
}



void programExit() { //This function is responsible for printing a goodbye message when the user exits the program.
    printf("\nThanks For using my Car Sales Program\n");
    printf("Hope to see you again :)\n");
}