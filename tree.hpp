#ifndef _TREE_HPP_
#define _TREE_HPP_
using namespace std;

#define MAX_SIZE 1003   // ogranicenje je zapravo MAX_SIZE - 3 jer dodajemo
                        // zagrade na krajeve i imamo \0 na kraju

typedef struct node
{
    char symbol;
    struct node *left, *right;
} Node;

typedef struct tnode
{
    char sign;
    char formula[MAX_SIZE];
    bool used;
    struct tnode *left, *right;
} Tnode;

Node* create_node(char symbol);

void print_tree(Node* root);

void print2D(Node *root);

#endif
