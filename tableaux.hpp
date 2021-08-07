#ifndef _TABLEAUX_HPP_
#define _TABLEAUX_HPP_

void find_leaves(Tnode *node);

Tnode* find_root(Tnode* root);

bool is_alpha_rule(Tnode *node);

bool is_beta_rule(Tnode *node);

void apply_rules(Tnode* tnode, Tnode* leaf);

void find_numbers(Tnode* node);

Tnode* create_tableaux(Node* root);

void print_countermodels(Tnode* root);

#endif
