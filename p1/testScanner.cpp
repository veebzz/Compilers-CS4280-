#include "scanner.h"
#include <iostream>

using namespace std;

void testScanner(ifstream &input);
void printToken(Token token);

string tokenNames[] = {
      "ITER_TK: Keyword[iter]",
      "VOID_TK: Keyword[void]",
      "VAR_TK: Keyword[var]",
      "RETURN_TK: Keyword[return]",
      "SCAN_TK: Keyword[scan]",
      "PRINT_TK: Keyword[print]",
      "PROGRAM_TK: Keyword[program]",
      "COND_TK: Keyword[cond]",
      "THEN_TK: Keyword[then]",
      "LET_TK: Keyword[let]",
      "INTL_TK: Keyword[int]",
      "EQUALS_TK: Operator[=]",
      "LESS_THAN_TK: Operator[<]",
      "GREATER_THAN_TK: Operator[>]",
      "COLON_TK: Operator[:]",
      "PLUS_TK: Operator[+]",
      "MINUS_TK: Operator[-]",
      "ASTERISK_TK: Operator[*]",
      "SLASH_TK: Operator[/]",
      "PERCENT_TK: Operator[%]",
      "PERIOD_TK: Delimiter[.]",
      "LEFT_PAREN_TK: Delimiter[(]",
      "RIGHT_PAREN_TK: Delimiter[)]",
      "LEFT_BRACKET_TK: Delimiter[{]",
      "RIGHT_BRACKET_TK: Delimiter[}]",
      "LEFT_BRACE_TK: Delimiter([)",
      "RIGHT_BRACE_TK: Delimiter(])",
      "SEMI_COLON_TK: Delimiter[;]",
      "COMMA_TK: Delimiter[,]",
      "ID_TK: Identifier",
      "INT_TK: Number",
      "OP_TK: Operator",
      "DEL_TK: Delimiter token",
      "EOF_TK: End Of File",
      "ERROR_TK: Error"
};

void testScanner(ifstream &input)
{
    Token currentToken;
    int line_number = 1;
    while(input){
        currentToken = scan(input, line_number);
        //if scanner encountered an error
        if (currentToken.tokenID == ERROR_TK)
        {
            //if scannner returned a termination condition, then exit program
            exit(-1);
        }else{
            printToken(currentToken);
        }

    }

}

void printToken(Token token)
{
    //Token: (tokenNames[]) | Token Instance: (String) | Line: (int)
    cout << "\nToken: " << tokenNames[token.tokenID] << " | Token Instance: (" << token.tokenInstance << ")" << " | Line: " << token.lineNumber << endl;
}