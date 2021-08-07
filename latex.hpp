#ifndef LATEX_HPP_
#define LATEX_HPP_

extern int TEXT_WIDTH;

extern vector<Tnode*>Level;

void latex_symbol(Node* root, ofstream& file);

void print_formula_file(Node* root, ofstream& file);

void print_signed_file(Tnode* root, ofstream& file);

void print_tableaux_node_file(Tnode* node, ofstream& file);

void find_positions(Tnode *root, float left, float right);

void level_i(Tnode *root, int i);

int tableaux_depth(Tnode *root);

void generate_tex(Tnode* root, ofstream& file);

void print_branch_file(Tnode* branch[], int len, ofstream& file);

void all_branches_tex(Tnode* node, int len, ofstream& file, Tnode* one, Tnode* two, bool closed_branch);

void tex_file(Tnode* root);

#endif
