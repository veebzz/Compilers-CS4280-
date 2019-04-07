#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include "tree.hpp"


using namespace std;


//blueprint for each node
//struct node
//{
//    int key;
//    std::vector<std::string> words;
//    struct node *left, *right;
//};

struct node *newNode(int item, string)
{
    struct node *temp =  (struct node *)malloc(sizeof(struct node));
    temp->key = token.length();
    temp->words.pushback(token);
    temp->left = temp->right = NULL;
    return temp;
}

int buildTree(int input){
    cout << "Input: " << input <<"\n";
    return 0;

}

void inOrder(struct node *root)
{
    if (root != NULL)
    {
        inOrder(root->left);
//        printf(" %d:%s ", root->key, root->words);
        cout << " " << root->key << " " << root->words;
        inOrder(root->right);
    }
}

void postOrder(struct node* node)
{
    if (node != NULL)
    {
        postOrder(node->left);
        postOrder(node->right);
//        printf(" %d:%s ", node->key, node->words);
        cout << " " << node->key << " " << node->words;

    }
}

void preOrder(struct node* node)
{
    if (node != NULL)
    {
        cout << " " << node->key << " " << node->words;
//        printf(" %d:%s ", node->key, node->words);
        preOrder(node->left);
        preOrder(node->right);
    }
}

struct node* insert(struct node* node, int key, string word) {
    //check if node struct is empty, if it is return newNode with value key
    if (node == NULL) {
        return newNode(word.length(),word);
    }
    //if next number is less than current node, next number becomes left child
    if (key < node->key) {
        node->left = insert(node->left, key, word);
    }
        //else become right child
    else if (key > node->key) {
        node->right = insert(node->right, key, word);
    }
    return node;
}

//struct node *search(struct node* root, int key) {
//    static int count = 0; //depth counter
//    if (root->key == key) //if key is found
//    {
//        printf("\nNumber(%d)found at depth: %d ", key, count);
//        count = 0; //reset depth counter
//        return 0;
//    }
//    //right subtree traversal
//    printf("\n Checking if %d > %d ....", key, root->key);
//    if (key > root->key)
//    {
//        count++;
//        printf("True");
//        printf("\nGo to right sub tree of %d", root->key);
//        if (root->right == NULL)
//        {
//            printf("\nThe right child of %d is NULL, which means", root->key);
//            printf("\nnumber %d is not in this tree.", key);
//            return 0;
//        }
//        return search(root->right, key);
//    }
//    printf("False");
//    //left subtree traversal
//    printf("\n Checking if %d < %d....", key, root->key);
//    if(key < root->key) {
//        count++;
//        printf("True");
//        printf("\nGo to left sub tree of %d", root->key);
//        if (root->left == NULL)
//        {
//            printf("\nThe left child of %d is NULL, which means", root->key);
//            printf("\nnumber %d is not in this tree.", key);
//            return 0;
//        }
//        search(root->left, key);
//    }
//}