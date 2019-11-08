#include <iostream>
// #define MAX_CHARACTER_PER_LINE  50 // uncomment if you intended to use getline()

typedef enum {
    PASS,
    INVALID_FORMAT,
    INVALID_ARGS,
    INVALID_OP,
    OUT_OF_RANGE,
    DIVISION_BY_ZERO,
} validation;

void promptUserInput(std::string* userInput);
bool userWantExit(std::string userInput);
void parseUserInput(std::string userInput, int* arg1, char* op, int* arg2);
validation validate(std::string userInput);
void operateCalculation(int arg1, char op, int arg2);
void printErrorMessage(validation val);
void printExitMessage();
bool isValidArgs(std::string userInput);
bool isValidOperator(std::string userInput);
bool isValidFormat(std::string userInput);
int add(int arg1, int arg2);
int subtract(int arg1, int arg2);
int multiply(int arg1, int arg2);
int divide(int arg1, int arg2);
int remainder(int arg1, int arg2);
void printResult(int result);
bool isDividingByZero(int arg);

int main() {
    std::string userInput;
    char op;
    int arg1, arg2;
    validation validationResult;

    while (true) {
        promptUserInput(&userInput);
        if (userWantExit(userInput)) {
            break;
        }
        validationResult = validate(userInput);
        if (validationResult != PASS) {
            printErrorMessage(validationResult);
            continue;
        }
        parseUserInput(userInput, &arg1, &op, &arg2);
        operateCalculation(arg1, op, arg2);
    };
    printExitMessage();
    return 0;
}

void promptUserInput(std::string* userInput) {
    //implement this
}
bool userWantExit(std::string userInput) {
    if (userInput.compare("Exit") == 0) { //should be working, review this later
        return true;
    }
    return false;
}
void parseUserInput(std::string userInput, int* arg1, char* op, int* arg2) {
    //implement this
}
validation validate(std::string userInput) {
    //change is acceptable
    if (!isValidArgs(userInput)) {
        return INVALID_ARGS;
    }
    if (!isValidOperator(userInput)) {
        return INVALID_OP;
    }
    if (!isValidFormat(userInput)) {
        return INVALID_FORMAT;
    }
    return PASS;
}
void operateCalculation(int arg1, char op, int arg2) {
    //change is acceptable
    int result;
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
            result = divide(arg1, arg2);
            break;
        }
        case '*': {
            result = multiply(arg1, arg2);
            break;
        }
        case '%': {
            if (isDividingByZero(arg2)) {
                printErrorMessage(DIVISION_BY_ZERO);
                return;
            }
            result = remainder(arg1, arg2);
            break;
        }
    }
    printResult(result);
}
void printErrorMessage(validation val) {
    //add more cases as you wish
    switch (val) {
        case INVALID_ARGS: {
            printf("You entered invalid args value!\n");
            break;
        }
        case INVALID_OP: {
            printf("You entered invalid operator!\n");
            break;
        }
        case OUT_OF_RANGE: {
            printf("Your number is out of range [-32,768 to 32,768]!\n");
            break;
        }
        case DIVISION_BY_ZERO: {
            printf("You can't divide by 0!\n");
            break;
        }
        case INVALID_FORMAT: {
            printf("You entered the wrong format for the equation!\n");
            break;
        }
        default: {
            break;
        }
    }
}
void printExitMessage() {
    //no change
    const char* exitMessage =
                "LABORATORY GROUP 1\n"
                "s3748575,s3748575@rmit.edu.vn,ThanhLong,Bui\n"
                "s3742774,s3742774@rmit.edu.vn,QuangTrung,Ngo\n"
                "s3757281,s3757281@rmit.edu.vn,MinhQuang,Tran\n";
    printf(exitMessage);
}
bool isValidArgs(std::string userInput) {
    //implement this
}
bool isValidOperator(std::string userInput) {
    //implement this
}
bool isValidFormat(std::string userInput) {
    //implement this
}
int add(int arg1, int arg2) {
    //implement this
}
int subtract(int arg1, int arg2) {
    //implement this
}
int multiply(int arg1, int arg2) {
    //implement this
}
int divide(int arg1, int arg2) {
    //implement this
}
int remainder(int arg1, int arg2) {
    //implement this
}
void printResult(int result) {
    //no change
    printf("Result of the equation is: %d\n", result);
}
bool isDividingByZero(int arg) {
    //change is acceptable
    if (arg == 0) {
        return true;
    }
    return false;
}
