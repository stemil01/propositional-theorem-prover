#ifndef LATEX_HPP_
#define LATEX_HPP_

extern int TEXT_WIDTH, TEXT_FONT;

extern vector<Tnode*>Level;

void latex_symbol(Node* root, ofstream& file);

void print_formula_file(Node* root, ofstream& file);

void print_signed_file(Tnode* root, ofstream& file);

void find_positions(Tnode *root, float left, float right);

void level_i(Tnode *root, int i);

int tableaux_depth(Tnode *root);

void generate_tex(Tnode* root, ofstream& file);

void tex_file(Tnode* root);

#endif
