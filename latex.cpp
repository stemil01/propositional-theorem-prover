#include <iostream>
#include <fstream>
#include <vector>
#include "tree.hpp"
#include "well_formed.hpp"
#include "tableaux.hpp"
#include "latex.hpp"
using namespace std;

int TEXT_WIDTH = 345; // default writing space width is 345pt
int TEXT_FONT = 14;
vector<Tnode*>Level;

void latex_symbol(Node* root, ofstream& file)
{
    if(root->symbol == '&')
        file << "\\land ";
    else if(root->symbol == '|')
        file << "\\lor ";
    else if(root->symbol == '>')
        file << "\\Rightarrow ";
    else if(root->symbol == '*')
        file << "\\neg ";
    else if(root->symbol == '1')
        file << "\\top ";
    else if(root->symbol == '0')
        file << "\\bot ";
    else file << root->symbol;
}

void print_formula_file(Node* root, ofstream& file) // customized print_formula
{
    if (root)
    {
        bool left_brackets = root->left && is_bin_symbol(root->left->symbol);
        bool right_brackets = root->right && is_bin_symbol(root->right->symbol);

        if (left_brackets) file << "(";
        print_formula_file(root->left, file);
        if (left_brackets) file<< ")";

        if (root->left) file << ' ';

        latex_symbol(root, file);

        if (root->right && root->symbol != '*') file << ' ';

        if (right_brackets) file << "(";
        print_formula_file(root->right, file);
        if (right_brackets) file << ")";
    }
}

void print_signed_file(Tnode* root, ofstream& file)
{
    char root_sign = root->sign ? 'T' : 'F';
    file <<"$" << root_sign << "\\;";
    print_formula_file(root->root, file);
    file << "$";
}

void find_positions(Tnode *root, float left, float right)
{
    if(root == NULL)
        return ;

    float middle = (left + right) / 2;
    root->position = middle;

    if(root->right == NULL) find_positions(root->left, left, right);

    else if(root->left)
    {
        find_positions(root->left, left, middle);
        find_positions(root->right, middle, right);
    }
}

void level_i(Tnode *root, int i)//forms vector with elements on i-th level
{
    if(root == NULL)
        return;

    if(i == 1)
    {
        Level.push_back(root);
        return ;
    }

    level_i(root->left, i - 1);
    level_i(root->right, i - 1);
}

int tableaux_depth(Tnode *root)
{
    if(root == NULL)
        return 0;

    int left = tableaux_depth(root->left);
    int right = tableaux_depth(root->right);

    return 1 + (left > right ? left : right);
}

void generate_tex(Tnode* root, ofstream& file)
{
    int depth = tableaux_depth(root);

    for(int i = 1 ; i <= depth; i++)
    {
        level_i(root, i);

        for(int j = 0 ; j < Level.size(); j++)
        {
            file << "\\begin{adjustwidth}";

            if(Level[j]->position >= TEXT_WIDTH / 2)
                file << "{" << (2 * Level[j]->position) - TEXT_WIDTH << "pt}{0pt}\n";
            else
                file << "{0pt}{" << TEXT_WIDTH - (2 * Level[j]->position) << "pt}";

            if(j)
                file << "\\begin{center}\n\\vspace*{-" << TEXT_FONT << "pt}{";
            else
                file << "\\begin{center}\n{";

            print_signed_file(Level[j], file);
            file << "}\n\\end{center}\n" << "\\end{adjustwidth}\n";
        }

        file << "\n";

        Level.clear();
    }
}

void tex_file(Tnode* root)
{
    find_positions(root, 0, TEXT_WIDTH);

    ofstream file("tableaux.tex");

    file << "\\documentclass{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage{changepage}\n\\begin{document}\n";

    generate_tex(root, file);

    file << "\\end{document}\n";
}
