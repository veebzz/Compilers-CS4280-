#ifndef COMPILERS_TREE_H
#define COMPILERS_TREE_H
#include <string>

using namespace std;

struct node
{
    int key;
    vector<string> words;
    struct node *left, *right;
};
struct node* insert(struct node* node, int key, string word);
int buildTree(int input);
void inOrder(struct node *root);
void postOrder(struct node* node);
void preOrder(struct node* node);

#endif //COMPILERS_TREE_H
