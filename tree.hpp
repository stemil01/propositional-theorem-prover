#ifndef _TREE_HPP_
#define _TREE_HPP_
using namespace std;

typedef struct node
{
    char symbol;
    struct node *left, *right;
} Node;

Node* create_node(char symbol);

#endif
