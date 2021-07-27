#ifndef _TREE_HPP_
#define _TREE_HPP_
using namespace std;

#define MAX_SIZE 1003   // ogranicenje je zapravo MAX_SIZE - 3 jer dodajemo
                        // zagrade na krajeve i imamo \0 na kraju

enum Sign { F, T };

typedef struct node
{
    char symbol;
    struct node *left, *right;
} Node;

typedef struct tnode
{
    Sign sign;
    Node *formula;
    bool used, closed;
    struct tnode *left, *right;
} Tnode;

Node* create_node(char symbol);
void print_tree(Node* root);
void print_formula(Node* root);
Node* copy_tree(Node* root);
void free_tree(Node* root);
void print2D(Node *root);


Tnode* create_tnode(Node* formula);
void t_free_tree(Tnode* root);
void t_print2D(Tnode *root);

#endif
