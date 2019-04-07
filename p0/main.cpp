#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
#include "tree.hpp"

using namespace std;

int main(int argc, char *argv[]) {
    struct node *root = NULL;
    string base, token;
    int count;

    if (argc > 2) {
        cout << "Too many argument given.\n";
    } else if (argc == 2) { /*file basename given*/
        base = argv[1];
        base = base + ".sp19";

        cout << base << "\n";
    } else if (argc == 1){
        cout << "Keyboard Enabled, Type your keyboard entry below:\n";
        //read from stream until simulated EOF(^D/ ctrl-D)
        istreambuf_iterator<char> begin(cin), end;
        string keyboardEntry(begin, end);               //store in keyboardEntry vector
        cout << keyboardEntry;

        stringstream ss(keyboardEntry);
        while(ss >> token ){
            count++;
            if (count == 1){
                buildTree(count);
//                root = insert(root, token.length(), token);
            }
            else{
//                insert(root, token.length(), token);
            }
            cout << token << " = " << token.length();


        }

        cout << "\nCount: " << count << "\n";
//        inOrder(root);
//        preOrder(root);
//        postOrder(root);

    }

    return 0;
}


/*int main()
{
    struct node *root = NULL;
    int numberList [10] = {30,10,45,38,20,50,25,33,8,12};
    int choice1;
    int choice2;

    for(int i = 0; i <= 10; i++)
    {
        if (i == 0)
        {
            root = insert(root, numberList[0]);
        }
        insert(root, numberList[i]);
    }
    */