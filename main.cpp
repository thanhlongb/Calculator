#include <iostream>

using namespace std;

typedef enum {
    PASS,
    INVALID_USER_INPUT,
    INVALID_ARGS,
    INVALID_OP,
    OUT_OF_RANGE,
    DIVISION_BY_ZERO,
} validation;

void promptUserInput(string* userInput);
bool userWantExit(string userInput);
string readNextWord(string str, int* currentIndex);
void argumentsToString(string userInput, string* arg1_str, string* op_str, string* arg2_str);
void parseUserInput(int* arg1, char* op, int* arg2, string arg1_str, string op_str, string arg2_str);
bool isValidDecimalPoints(string decimalPoints);
validation validate(string userInput, string arg1_str, string op_str, string arg2_str);
void operateCalculation(int arg1, char op, int arg2);
void printErrorMessage(validation val);
void printExitMessage();
bool isValidArgs(string userInput);
bool isValidOperator(string op_str);
bool isValidInt(string number);
bool isInRange(string arg);
int add(int arg1, int arg2);
int subtract(int arg1, int arg2);
int multiply(int arg1, int arg2);
int divide(int arg1, int arg2);
int remainder(int arg1, int arg2);
void printResult(int result);
bool isDividingByZero(int arg);

int main() {
    string userInput;
    string arg1_str, arg2_str, op_str;
    char op;
    int arg1, arg2;
    validation validationResult;

    while (true) {
        promptUserInput(&userInput);
        if (userWantExit(userInput)) {
            break;
        }
        argumentsToString(userInput, &arg1_str, &op_str, &arg2_str);
        validationResult = validate(userInput, arg1_str, op_str ,arg2_str);
        if (validationResult != PASS) {
            printErrorMessage(validationResult);
            continue;
        }
        parseUserInput(&arg1, &op, &arg2, arg1_str, op_str, arg2_str);
        operateCalculation(arg1, op, arg2);
    };
    printExitMessage();
    return 0;
}

void promptUserInput(string* userInput) {
    //no change
    printf("Enter your equation: ");
    getline(cin, *userInput);
}
bool userWantExit(string userInput) {
    //no change
    return userInput == "Exit";
}
string readNextWord(string str, int* currentIndex) {
    //no change
    int newIndex = 0;
    string whitespace = " ";
    string word = "";

    newIndex = str.find(whitespace, *currentIndex);
    word = str.substr(*currentIndex, newIndex - *currentIndex);
    *currentIndex = newIndex + 1;

    return word;
}

void argumentsToString(string userInput, string* arg1_str, string* op_str, string* arg2_str) {
    int currentIndex = 0;
    *arg1_str = readNextWord(userInput, &currentIndex);
    *op_str = readNextWord(userInput, &currentIndex);
    *arg2_str = readNextWord(userInput, &currentIndex);
}

void parseUserInput(int* arg1, char* op, int* arg2, string arg1_str, string op_str, string arg2_str) {
    //no change
    *arg1 = stoi(arg1_str);
    *op = op_str.c_str()[0];
    *arg2 = stoi(arg2_str);
}

validation validate(string userInput, string arg1_str, string op_str, string arg2_str) {
    //change is acceptable
    if (!isValidArgs(userInput)) {
        return INVALID_ARGS;
    }
    if (!isValidOperator(op_str)) {
        return INVALID_OP;
    }
    if (!isValidInt(arg1_str) || !isValidInt(arg2_str)) {
        return INVALID_USER_INPUT;
    }
    if (!isInRange(arg1_str) || !isInRange(arg2_str)) {
        return OUT_OF_RANGE;
    }
    return PASS;
}

void operateCalculation(int arg1, char op, int arg2) {
    //change is acceptable
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
    }
    printResult(result);
}

void printErrorMessage(validation val) {
    //add more cases as you wish
    switch (val) {
        case INVALID_ARGS: {
            printf("%s.\n%s\n", "You entered an invalid expression",
                   "The expression should looks like: <operand1> <operator> <operand2>");
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

void printExitMessage() {
    //no change
    const char* exitMessage =
            "LABORATORY GROUP 1\n"
            "s3748575,s3748575@rmit.edu.vn,ThanhLong,Bui\n"
            "s3742774,s3742774@rmit.edu.vn,QuangTrung,Ngo\n"
            "s3757281,s3757281@rmit.edu.vn,MinhQuang,Tran\n";
    printf("%s", exitMessage);
}

bool isValidArgs(string userInput) {
    //implement this
    string delimiter = " ";
    size_t pos = 0;
    int no_WhitespaceChar = 0, no_Args = 0;

    while ((pos = userInput.find(delimiter)) != string::npos) {
        userInput.erase(0, pos + delimiter.length());
        no_WhitespaceChar++;
        no_Args++;
    }
    no_Args++;

    return no_WhitespaceChar == 2 && no_Args == 3;
}

bool isValidOperator(string op_str) {
    //implement this
    if (op_str.size() > 1) return false;
    else {
        if (op_str[0] == '+' ||
            op_str[0] == '-' ||
            op_str[0] == '*' ||
            op_str[0] == '/' ||
            op_str[0] == '%')
            return true;
    }
    return false;
}

bool isValidDecimalPoints(string decimalPoints) {
    for (int i = 0; i < decimalPoints.size(); i++)
    {
        if (decimalPoints[i] != '0') return false;
    }

    return true;
}

bool isValidInt(string number) {
    //implement this
    if (!isdigit(number[0])) {
        if (number[0] != '+' && number[0] != '-') return false;
    }

    for (int i = 1; i < number.size(); i++)
    {
        if (isdigit(number[i])) continue;
        else {
            if (number[i] == '.') return isValidDecimalPoints(number.erase(0, i + 1));
            else return false;
        }
    }
    return true;
}
bool isInRange(string arg) {
    int argInt;
    try {
        argInt = stoi(arg);
    } catch (out_of_range e) {
        //unable to convert to int due to
        //the arg (as type string) being
        //too big to store as int
        return false;
    }
    if (argInt >= -32768 && argInt <= 32767) {
        return true;
    }
    return false;
}
int add(int arg1, int arg2) {
    //no change
    return arg1 + arg2;
}
int subtract(int arg1, int arg2) {
    //no change
    return arg1 - arg2;
}
int multiply(int arg1, int arg2) {
    //no change
    return arg1 * arg2;
}
int divide(int arg1, int arg2) {
    //no change
    return arg1 / arg2;
}
int remainder(int arg1, int arg2) {
    //no change
    return arg1 % arg2;
}
void printResult(int result) {
    //no change
    printf("Result of the equation is: %d\n", result);
}
bool isDividingByZero(int arg) {
    //change is acceptable
    return arg == 0;
}

