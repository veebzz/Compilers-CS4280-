/*main.cpp
 * Name: Vibhav Chemarla
 * Date: 3/06/2019
 * Description: P1: This the second project for CS4280-Program Translation.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "testScanner.h"


using namespace std;
string remove_extension(const string& filename);
static void addSpaceToFile(const string& fileName);

int main(int argc, char *argv[]) {
    string base, fileName, token;

    if (argc > 2) {
        cout << "Too many argument given.\n";
        exit(1);
    } else if (argc == 2) { /*file basename given*/
        base = argv[1];
        if(base.substr(base.find_last_of(".") + 1) == "sp19") {
            cout << "File name does have .sp19 extension" << endl; // recognizes that argument has .sp19 extension
            fileName = base;
            base = remove_extension(fileName);
        } else {
            fileName = base + ".sp19";      //adds .sp19 to given file argument, if missing
        }
        addSpaceToFile(fileName); //add space to file for P1
        ifstream fp(fileName.c_str());  //open ifstream file pointer for the input file

        if(fp.is_open()) {                         //check to see if opened successfully
            if (fp.peek() == ifstream::traits_type::eof()) {
                // Empty File check
                cout << "Error! File is empty." << endl;
                exit(1);
            }
        }else{
            cout << "File not found" << endl;
            return 1;
        }

        testScanner(fp);
        fp.close();

    } else if (argc == 1) {
        cout << "Stream enabled" << endl;
        cout << "If you chose to provide a keyboard entry below and use Ctrl-D to simulate EOF:\n";
        base = "out";
        //read from stream until simulated EOF(^D/ ctrl-D)
        istreambuf_iterator<char> begin(cin), end;       //open up stream buffer
        string keyboardEntry(begin, end);               //store in keyboardEntry vector

        //put keyboard stream into file because testScanner only accepts file pointers
        ofstream outfile;
        outfile.open("keyboardinput.txt");
        outfile << keyboardEntry;
        outfile << ' ';
        outfile.close();

        ifstream fp("keyboardinput.txt");
        testScanner(fp);
        fp.close();
        //remove keyboardinput.txt from directory
        remove("keyboardinput.txt");
    }
    return 0;
}

string remove_extension(const string& filename) {
    size_t lastdot = filename.find_last_of(".");
    if (lastdot == std::string::npos) return filename;
    return filename.substr(0, lastdot);
}

void addSpaceToFile(const string& fileName){
    ofstream out;
    out.open(fileName, std::ios::app);
    out << " ";
    out.close();
}
