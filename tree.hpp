#ifndef _TREE_HPP_
#define _TREE_HPP_
#include <vector>
using namespace std;

#define MAX_SIZE 1003 // max size is actually MAX_SIZE - 3 because of added brackets
#define MAX_CHAR 128

enum Sign { F, T };

typedef struct node
{
    char symbol;
    struct node *left, *right;
} Node;

typedef struct Tnode
{
    Sign sign;
    Node *root;
    bool used, closed;
    float position;
    int number;
    vector<Tnode*>Rule_nodes;
    struct Tnode *left, *right;

} Tnode;

Node* create_node(char symbol);
Node* copy_tree(Node* root);
void print_tree(Node* root);
void print_formula(Node* root);
void free_tree(Node* root);

Tnode* create_tnode(Sign s, Node *root);
void print_signed_2D(Tnode *troot, int space);
void print_enumerated_2D(Tnode* node);
void t_free_tree(Tnode* root);

#endif
