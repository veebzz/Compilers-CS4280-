#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"
#include <map>
#include <fstream>

using namespace std;

Token scan(ifstream& fp, int &lineNumber);

#endif