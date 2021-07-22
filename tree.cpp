#include <iostream>
#include <string>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

Node* create_node(char symbol)
{
    Node *new_node = new Node;
    if (new_node == NULL)
        return NULL;
    new_node->symbol = symbol;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void print_tree(Node* root)
{
    if (root)
    {
        print_tree(root->left);
        cout << root->symbol << " ";
        print_tree(root->right);
    }
}


// GeeksforGeeks code for printing binary tree vertically
static const int COUNT = 4;

void print2DUtil(Node *root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->right, space);
 
    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    cout << root->symbol << '\n';
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(Node *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}
