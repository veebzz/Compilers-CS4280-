#ifndef TESTSCANNER_H
#define TESTSCANNER_H

#include <fstream>
#include "token.h"
using namespace std;

void testScanner(ifstream& input);

void printToken(Token token);

#endif