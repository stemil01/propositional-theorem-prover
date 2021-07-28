#ifndef _TABLEAUX_HPP_
#define _TABLEAUX_HPP_

void find_leaves(Tnode *node);

Tnode* find_root(Tnode* root);

void apply_rules(Tnode* tnode, Tnode* leaf);

Tnode* create_tableuax(Node* root_formula);

#endif