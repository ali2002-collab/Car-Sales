//including necessary header files to import required libraries, functions, variables and constants, ensuring a well-organized and structured program.
#include "./library.h"
#include "./variables.h"
#include "./funtions.h"
#include "./constants.h"
int main() {
    initializeStructArray();
    do {
        programOpening(); //Displaying the opening screen of the program
        switch (user_choice) {
            case VIEW_STOCK:
                stock();  //Function call to view Car stock Available
                break;
            case BUY_CARS:
                buyCars(); //Function call to buy cars
                break;
            case SALES_STATS:
                salesStats(); //Function call to view sales statistics
                break;
            case OPTION_EXIT:
                programExit(); //Function call to exit the program
                break;
            default:
                break;
        }
    } while (user_choice != OPTION_EXIT);  //Looping till the user wants to exit


    return  0; //Returning 0 to indicate successful execution of the program
    
}
