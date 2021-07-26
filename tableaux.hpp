#ifndef _TABLEAUX_HPP_
#define _TABLEAUX_HPP_
using namespace std;

void find_leaves(Tnode* node, vector<Tnode*> &leaves);

Tnode* find_unused(Tnode* root);

void apply_rule(Tnode* leaf, Sign sign, char symbol);

void check_tableaux(Tnode* node);

Tnode* create_tableaux(Node* formula);

#endif
