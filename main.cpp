#include <iostream>

using namespace std;

const int MAX_USER_INPUT_LENGTH = 100;
const int MAX_ARG_LENGTH = 100;
const char WHITESPACE = ' ';

typedef enum {
    PASS,
    INVALID_USER_INPUT,
    INVALID_ARGS,
    INVALID_OP,
    OUT_OF_RANGE,
    DIVISION_BY_ZERO,
} validation;

//---------Processing Input ---------//
bool compare(char a[], char b[]); // Compare 2 char arrays
void trim(char charArr[]); //Delete all whitespaces before and after user arguments
void promptUserInput(char userInput[]); //take user input
bool userWantExit(char userInput[]); // Exit or not ?
void readNextArgument(char target[], char userInput[], int* currentIndex); //read the next argument from input
void argumentsToCharArr(char userInput[], char arg1CharArr[], char opCharArr[], char arg2CharArr[]); // Convert input to 3 char arrays arguments

//----------Validation-----------//
bool isValidArgs(char userInput[]); // check valid input arguments
bool isValidOpChar(char opCharArr[]); // check valid input opChar
bool isValidInt(char number[]); // check valid input integer
bool isInRange(char arg[]); // check if input integer is in range
validation validate(char userInput[], char arg1CharArr[], char opCharArr[], char arg2CharArr[]); // Validation process
void printErrorMessage(validation val); //print error message to console

//----------Calculation-----------//
int add(int arg1, int arg2); // addition
int subtract(int arg1, int arg2); // subtraction
int multiply(int arg1, int arg2); // multiplication
int divide(int arg1, int arg2); // division
int remainder(int arg1, int arg2); // Taking remainder
void printResult(int result); //Print result to console
bool isDividingByZero(int arg); //Check division by 0 error
void parseUserInput(int* arg1, char* op, int* arg2, char arg1CharArr[], char opCharArr[], char arg2CharArr[]);
void operateCalculation(int arg1, char op, int arg2);

//----------Exit------------//
void printExitMessage();

int main() {
    while (true)
    {
        char userInput[MAX_USER_INPUT_LENGTH] = {};
        char arg1CharArr[MAX_ARG_LENGTH] = {};
        char opCharArr[MAX_ARG_LENGTH] = {};
        char arg2CharArr[MAX_ARG_LENGTH] = {};

        char op;
        int arg1, arg2;
        validation validationResult;

        promptUserInput(userInput); //Taking input
        if (userWantExit(userInput)) { //Exit?
            break;
        }
        argumentsToCharArr(userInput, arg1CharArr, opCharArr, arg2CharArr); //Convert input to each arguments
        validationResult = validate(userInput, arg1CharArr, opCharArr, arg2CharArr);      // Validation
        if (validationResult != PASS) {
            printErrorMessage(validationResult);
            continue;
        }
        parseUserInput(&arg1, &op, &arg2, arg1CharArr, opCharArr, arg2CharArr);
        operateCalculation(arg1, op, arg2);
    }
    printExitMessage();
    return 0;
}


//---------------------------------- Processing Input --------------------------------//

bool compare(char a[], char b[]) {
    for (int i = 0; a[i] != '\0'; i++) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

void trim(char charArr[]) {
    int start = 0; // number of leading spaces
    char* buffer = charArr;

    //find index of the first non-whitespace char
    while (*charArr && *charArr++ == ' ') ++start;

    // move to end of string
    while (*charArr++);
    int end = charArr - buffer - 1;
    while (end > 0 && buffer[end - 1] == ' ') --end; // backup over trailing spaces
    buffer[end] = 0; // remove trailing spaces
    if (end <= start || start == 0) return; // exit if no leading spaces or string is now empty
    charArr = buffer + start;
    while ((*buffer++ = *charArr++));  // remove leading spaces: K&R

}

void promptUserInput(char userInput[]) {
    printf("Enter your equation: ");
    cin.getline(userInput, MAX_USER_INPUT_LENGTH);
    trim(userInput);
}

bool userWantExit(char userInput[]) {
    char Exit[] = "Exit";
    return compare(userInput, Exit);
}

void readNextArgument(char target[], char userInput[], int* currentIndex) {
    int newIndex = *currentIndex;

    //Find the next index of whitespace (nexIndex) from the current index
    while ( *(userInput + newIndex) && *(userInput + newIndex) != ' ') newIndex++;

    //Get the word from currentIndex to nextIndex
    int j = *currentIndex;
    int i = 0;
    while ( j != newIndex )
    {
        *(target +i) = userInput[j];
        i++; j++;
    }

    *currentIndex = newIndex + 1;
}

void argumentsToCharArr(char userInput[], char arg1CharArrCharArr[], char opCharArr[], char arg2CharArr[]) {
    int currentIndex = 0;
    readNextArgument(arg1CharArrCharArr, userInput, &currentIndex);
    readNextArgument(opCharArr, userInput, &currentIndex);
    readNextArgument(arg2CharArr, userInput, &currentIndex);
}

//---------------------------------- End Processing Input --------------------------------//


//---------------------------------- Validation --------------------------------//
bool isValidArgs(char userInput[]) {
    int whitespaceCount = 0;

    while (*userInput) {
        if (*userInput == WHITESPACE) whitespaceCount++;
        userInput++;
    }

    return (whitespaceCount == 2);
}

bool isValidOpChar(char opCharArr[]) {
    int size = 0;
    int index = 0;
    while ( *(opCharArr + index) ) { size++; index++; }
    if (size > 1) return false;
    else {
        if (opCharArr[0] == '+' ||
            opCharArr[0] == '-' ||
            opCharArr[0] == '*' ||
            opCharArr[0] == '/' ||
            opCharArr[0] == '%')
            return true;
    }
    return false;
}

bool isValidDecimalPoints(char decimalPoints[], int index) {
    while ( *(decimalPoints + index) )
    {
        if (*(decimalPoints + index) != '0') return false;
        index++;
    }

    return true;
}

bool isValidInt(char number[]) {
    if (!isdigit(number[0])) {
        if (number[0] != '+' && number[0] != '-') return false;
    }

    int index = 1;
    while ( *(number + index) )
    {
        if (isdigit(*(number + index))) { index++; continue;  }
        else {
            if (*(number + index) == '.') return isValidDecimalPoints(number, index+1);
            else return false;
        }
    }
    return true;
}

bool isInRange(char arg[]) {
    int argInt;
    try {
        argInt = atoi(arg);
    }
    catch (out_of_range e) {
        //unable to convert to int due to
        //the arg (as type string) being
        //too big to store as int
        return false;
    }
    return (argInt >= -32768 && argInt <= 32767);
}

validation validate(char userInput[], char arg1CharArr[], char opCharArr[], char arg2CharArr[]) {
    if (!isValidArgs(userInput)) {
        return INVALID_ARGS;
    }
    if (!isValidOpChar(opCharArr)) {
        return INVALID_OP;
    }
    if (!isValidInt(arg1CharArr) || !isValidInt(arg2CharArr)) {
        return INVALID_USER_INPUT;
    }
    if (!isInRange(arg1CharArr) || !isInRange(arg2CharArr)) {
        return OUT_OF_RANGE;
    }
    return PASS;
}

void printErrorMessage(validation val) {
    switch (val) {
        case INVALID_ARGS: {
            printf("%s.\n%s\n", "You entered an invalid expression",
                   "The expression should looks like: <operand1>[whitespace]<operator>[whitespace]<operand2>");
            break;
        }
        case INVALID_OP: {
            printf("You entered invalid operator!\n");
            break;
        }
        case OUT_OF_RANGE: {
            printf("Your operand(s) is out of range [-32,768 to 32,767]!\n");
            break;
        }
        case DIVISION_BY_ZERO: {
            printf("You can't divide a number by 0!\n");
            break;
        }
        case INVALID_USER_INPUT: {
            printf("You entered the wrong format for the integer operands!\n");
            break;
        }
        default: {
            break;
        }
    }
}

//---------------------------------- End Validation --------------------------------//
int add(int arg1, int arg2) {
    return arg1 + arg2;
}

int subtract(int arg1, int arg2) {
    return arg1 - arg2;
}

int multiply(int arg1, int arg2) {
    return arg1 * arg2;
}

int divide(int arg1, int arg2) {
    return arg1 / arg2;
}

int remainder(int arg1, int arg2) {
    return arg1 % arg2;
}

void printResult(int result) {
    printf("Result of the equation is: %d\n", result);
}

bool isDividingByZero(int arg) {
    return (arg == 0);
}

void parseUserInput(int* arg1, char* op, int* arg2, char arg1CharArr[], char opCharArr[], char arg2CharArr[]) {
    *arg1 = atoi(arg1CharArr);
    *op = opCharArr[0];
    *arg2 = atoi(arg2CharArr);
}

void operateCalculation(int arg1, char op, int arg2) {
    int result = 0;
    switch (op) {
        case '+': {
            result = add(arg1, arg2);
            break;
        }
        case '-': {
            result = subtract(arg1, arg2);
            break;
        }
        case '/': {
            if (isDividingByZero(arg2)) {
                printErrorMessage(DIVISION_BY_ZERO);
                return;
            }
            result = divide(arg1, arg2);
            break;
        }
        case '*': {
            result = multiply(arg1, arg2);
            break;
        }
        case '%': {
            result = remainder(arg1, arg2);
            break;
        }
        default: {
            break;
        }
    }
    printResult(result);
}

//---------Exit---------//
void printExitMessage() {
    const char* exitMessage =
            "LABORATORY GROUP 1\n"
            "s3748575,s3748575@rmit.edu.vn,ThanhLong,Bui\n"
            "s3742774,s3742774@rmit.edu.vn,QuangTrung,Ngo\n"
            "s3757281,s3757281@rmit.edu.vn,MinhQuang,Tran\n";
    printf("%s", exitMessage);
}
