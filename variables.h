int user_choice;
struct customer {
    double total_Price;
    char customer_name[100];
    int customer_Age;
    bool discount;
};
struct customer information;

char options[5][15] = {"View Stock","Buy Car","Sales Stats","Exit" };
char carName[5][10] = { "TESLA", "FORD","LOTUS","BMW","AUDI" };
int numberOfCars[5] = { 28,21,15,11,9 };
double carPrice[5] = {55000,6500,10000,7000,8000 };
struct Car {
    char name[10];
    int amount;
    double saleValue;
};

struct Car cars[5];
struct Car stockCars[5];