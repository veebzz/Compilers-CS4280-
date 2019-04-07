#include "scanner.h"
#include "token.h"
#include <map>
#include <fstream>
#include <iostream>

Token shouldTerminate(int state, int lineNumber, char currentChar);
tokenIdentifier isKeyword(int state, string tokenInstance);
int getFsaColumn(char currentChar, int lineNumber);
Token sendToken(tokenIdentifier tokenID, string tokenInstance, int lineNumber);
//Finite State Automaton Table
/*column number decides which state[rows>0] to go to next,
each row after 0th row is a recognized token state,
only id token/num token can change states*/

int fsaTable[22][23] = {
        //ws    l    d    =    <    >    :    +    -    *    /    %    .    (    )    ,    {    }    ;    [    ]  eof error
        {  0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  -1,  -2},
        {100,   1,   1, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 101}, //id token
        {101, 120,   2, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101, 101}, //num token
        {102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102, 102}, //equal token
        {103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103, 103}, //less than token
        {104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104, 104}, //greater than token
        {105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105, 105}, //colon token
        {106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106, 106}, //plus token
        {107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107, 107}, //minus token
        {108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108, 108}, //asterisk token
        {109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109}, //forward slash token
        {110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110, 110}, //percent token
        {111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111, 111}, //period token
        {112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112, 112}, //L parenthesis token
        {113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113, 113}, //R parenthesis token
        {114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114, 114}, //comma token
        {115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115, 115}, //L curly bracket token
        {116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116, 116}, //R curly bracket token
        {117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117, 117}, //semi colon bracket
        {118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118, 118}, //L square bracket token
        {119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119, 119}, //R square bracket token
        {120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120, 120} //Error Token

};
//Mapping number to their tokens
map<int, tokenIdentifier> stateMap = {
        {100, ID_TK},
        {101, INT_TK},
        {102, EQUALS_TK},
        {103, LESS_THAN_TK},
        {104, GREATER_THAN_TK},
        {105, COLON_TK},
        {106, PLUS_TK},
        {107, MINUS_TK},
        {108, ASTERISK_TK},
        {109, SLASH_TK},
        {110, PERCENT_TK},
        {111, PERIOD_TK},
        {112, LEFT_PAREN_TK},
        {113, RIGHT_PAREN_TK},
        {114, COMMA_TK},
        {115, LEFT_BRACE_TK},
        {116, RIGHT_BRACE_TK},
        {117, SEMI_COLON_TK},
        {118, LEFT_BRACKET_TK},
        {119, RIGHT_BRACKET_TK},
        {120, ERROR_TK},
        {-1,  EOF_TK}
};
//Preset keywords
static map<string, tokenIdentifier> keywordMap = {
        {"iter",    ITER_TK},
        {"void",    VOID_TK},
        {"var",     VAR_TK},
        {"return",  RETURN_TK},
        {"scan",    SCAN_TK},
        {"print",   PRINT_TK},
        {"program", PROGRAM_TK},
        {"cond",    COND_TK},
        {"then",    THEN_TK},
        {"let",     LET_TK},
        {"int",     INTL_TK}
};
//Symbol Map
map<char, int> symbolMap = {
        {'=', 3},
        {'<', 4},
        {'>', 5},
        {':', 6},
        {'+', 7},
        {'-', 8},
        {'*', 9},
        {'/', 10},
        {'%', 11},
        {'.', 12},
        {'(', 13},
        {')', 14},
        {',', 15},
        {'{', 16},
        {'}', 17},
        {';', 18},
        {'[', 19},
        {']', 20}
};

//Driver
Token scan(ifstream &fp, int &lineNumber) {
    //start at state 0
    Token token;
    int currentState = 0, nextState = 0;
    char currentChar = ' ';
    string currentWord;

    while (currentState >= 0 && currentState < 100) {
        fp.get(currentChar);
        //skip comments from & to \n
        if (currentChar == '&') {
            while (currentChar != '\n') {
                fp.get(currentChar);
            }
            //get next character after newline
            fp.get(currentChar);
        }
        //get the column number of current character
        int fsaColumn = getFsaColumn(currentChar, lineNumber);
        //check if file pointer is pointing to EOF
        if (fp.eof()) {
            fsaColumn = 21;
        }
        // check if current character is an unrecognized invalid symbol
        if (fsaColumn == -2) {
            return sendToken(ERROR_TK, "Invalid Character", lineNumber);
        }
        //get next state [row]
        nextState = fsaTable[currentState][fsaColumn];
        //check TERMINATION STATES [EOF/Error]
        if(nextState < 0) {
           return shouldTerminate(nextState, lineNumber, currentChar);
        }
        //send Final States
        if (nextState >= 100) {
            //check if first letter of token is lowercase if this is ID_TK
            if (nextState == 100){
                if (isalpha(currentWord[0]) && isupper(currentWord[0])) {
                    cout << "Scanner Error: ID_TK [" << currentWord << "] Must start with lowercase letter [Line "
                         << lineNumber << "]" << endl;
                    return sendToken(ERROR_TK, "ID_TK must start with lowercase letter", lineNumber);
                }
            }
            //If there is token that starts with numbers and also has letters
            if(nextState == 120){
                currentWord += currentChar;
                cout << "Scanner Error: Scan Function: [" << currentWord << "] is an invalid set of characters [Line "
                     << lineNumber << "]" << endl;
                return sendToken(ERROR_TK,"Number Tokens cannot have letters in them", lineNumber);

            }
            token.tokenID = isKeyword(nextState, currentWord);
            //if no problems return correct token
            return sendToken(token.tokenID, currentWord, lineNumber);
        } else {
            //eliminate whitespace and newline from tokenInstance string(below as currentWord)
            if (currentChar != ' ' && currentChar != '\n') {
                currentWord += currentChar;
            }
            //check if current word exceeds 8 character limit
            if (currentWord.length() > 8) {
                cout << "Scanner Error: scan Function: [Line " << lineNumber << "][" << currentWord
                     << "] exceeds 8 characters";
                return sendToken(ERROR_TK, "Invalid Length", lineNumber);
            }
            //increment number if newline is detected
            if (currentChar == '\n') {
                lineNumber++;
            }
            //update currentState with nextState for next iteration of while loop
            currentState = nextState;
        }
    }
    //should never reach here unless something super wierd happens
    return sendToken(ERROR_TK, "Scanner Error: scan Function reached an weird error", lineNumber);
}

int getFsaColumn(char currentChar, int lineNumber) {
    //check ws
    if (isspace(currentChar)) {
        return 0;
    }
    //check if current character is letter
    else if (isalpha(currentChar)) {
        return 1;
    }
    //check if digit
    else if (isdigit(currentChar)) {
        return 2;
    }
    //check if character is part of symbol map
    else if (symbolMap.find(currentChar) != symbolMap.end()) {
        //return unique column number using symbolMap
        return symbolMap[currentChar];
    }
    // return -2 if current character is not part of the recognized symbols
    else {
        cout << "\nScanner Error: getFsaColumn Function: [Line " << lineNumber << "][" << currentChar
             << "] exceeds 8 characters";
        return -2;
    }
}

tokenIdentifier isKeyword(int state, string tokenInstance) {
    tokenIdentifier tokenID;
    //search stateMap using tokenID key to find its value[tokenIdentifier from token]
    if (stateMap.find(state) != stateMap.end()) {
        tokenID = stateMap[state];
    }
    //before returning the token check if tokenInstance matches a keywordMap key and return its value[tokenIdentifier from token]
    if (keywordMap.find(tokenInstance) != keywordMap.end()) {
        //update tokenID from above
        tokenID = keywordMap[tokenInstance];
    }
    return tokenID;
}

Token shouldTerminate(int state, int lineNumber, char currentChar){
    Token token;
    //check if EOF[only hits this if current state is 0]
    //Meaning every file must have a space at the end of file
    if (state == -1) {
        return sendToken(EOF_TK, "EOF", lineNumber);
    }
    //if unrecognized character return error token
    if (state == -2) {
        cout << "Scanner Error: shouldTerminate function: [Line " << lineNumber << "] Invalid Character [" << currentChar
             << "]" << endl;
        return sendToken(ERROR_TK, "Invalid ID", lineNumber);
    }
}

Token sendToken(tokenIdentifier tokenID, string tokenInstance, int lineNumber){
    Token token;
    token.tokenID = tokenID;
    token.tokenInstance = tokenInstance;
    token.lineNumber = lineNumber;
    return token;
}