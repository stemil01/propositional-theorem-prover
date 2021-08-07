#include <iostream>
#include <fstream>
#include <vector>
#include "tree.hpp"
#include "well_formed.hpp"
#include "tableaux.hpp"
#include "latex.hpp"
#define M 14.5
using namespace std;

int TEXT_WIDTH = 550;

vector<Tnode*>Level;

void latex_symbol(Node* root, ofstream& file)
{
    if (root->symbol == '&')
        file << "\\land ";
    else if (root->symbol == '|')
        file << "\\lor ";
    else if (root->symbol == '>')
        file << "\\Rightarrow ";
    else if (root->symbol == '*')
        file << "\\neg ";
    else if (root->symbol == '1')
        file << "\\top ";
    else if (root->symbol == '0')
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

void print_signed_file(Tnode* root, ofstream& file) // signed formula with explanation of applied rule
{
    char root_sign = root->sign ? 'T' : 'F';
    file <<"$(" << root->number << ")\\;" << root_sign << "\\;";
    print_formula_file(root->root, file);
    if (is_alpha_rule(root))
    {
        file << "\\;$}\\boldmath{$\\;|\\alpha:\\;";
        int indicator = 0;
        for (int i = 0 ; i < root->Rule_nodes.size() ; i++)
        {
            if (root->Rule_nodes[i]->left)
            {
                indicator = 1;
                file << "(" << root->Rule_nodes[i]->left->number << ",\\;" << root->Rule_nodes[i]->left->left->number << ")";
            }
        }
        if (!indicator) file << "BAC";

        file << "|";
    }

    if (is_beta_rule(root))
    {
        file << "\\;$}\\boldmath{$\\;|\\beta:\\;";
        int indicator = 0;
        for (int i = 0 ; i < root->Rule_nodes.size() ; i++)
        {
            if (root->Rule_nodes[i]->left && root->Rule_nodes[i]->right)
            {
                indicator = 1;
                file << "(" << root->Rule_nodes[i]->left->number << ",\\;" << root->Rule_nodes[i]->right->number << ")";
            }
        }
        if (!indicator) file <<"BAC";

        file << "|";
    }

    file << "$";
}

void print_tableaux_node_file(Tnode* root, ofstream& file)
{
    char root_sign = root->sign ? 'T' : 'F';
    file <<"{$(" << root->number << ")\\;" << root_sign << "\\;";
    print_formula_file(root->root, file);
    file << "$}";
}

void find_positions(Tnode *root, float left, float right)
{
    if (root == NULL)
        return ;

    float middle = (left + right) / 2;
    root->position = middle;

    if (root->right == NULL) find_positions(root->left, left, right);

    else if (root->left)
    {
        find_positions(root->left, left, middle);
        find_positions(root->right, middle, right);
    }
}

void level_i(Tnode *root, int i) // forms vector with elements on i-th level
{
    if (root == NULL)
        return;

    if (i == 1)
    {
        Level.push_back(root);
        return ;
    }

    level_i(root->left, i - 1);
    level_i(root->right, i - 1);
}

int tableaux_depth(Tnode *root)
{
    if (root == NULL)
        return 0;

    int left = tableaux_depth(root->left);
    int right = tableaux_depth(root->right);

    return 1 + (left > right ? left : right);
}

void generate_tex(Tnode* root, ofstream& file)
{
    int depth = tableaux_depth(root);

    for (int i = 1 ; i <= depth; i++)
    {
        level_i(root, i);
        int length = Level.size();

        for (int j = 0 ; j < length ; j++)
        {
            file << "\\begin{adjustwidth}";

            if (Level[j]->position >= TEXT_WIDTH / 2)
                file << "{" << (2 * Level[j]->position) - TEXT_WIDTH << "pt}{0pt}\n";
            else
                file << "{0pt}{" << TEXT_WIDTH - (2 * Level[j]->position) << "pt}";

            if (j)
                file << "\\centering\\vspace{-" << M << "pt}{";
            else
                file << "\\centering{";

            print_signed_file(Level[j], file);
            if (j == length - 1)
                file << "\\\\[2\\baselineskip]";

            file << "}\n\\end{adjustwidth}\n";
        }

        file << "\n";

        Level.clear();
    }
    file <<"\n\\vspace{12pt}\n";
    file <<"\\begin{flushleft}\\Large{Branches:}\\end{flushleft}\n\\flushleft\n";
}

static Tnode* branch[MAX_SIZE]; //store pointers to formulae of current branch

static Tnode* letters[2][MAX_CHAR][MAX_SIZE];

static int number[2][MAX_CHAR], occurence[2][MAX_CHAR];

void print_branch_file(Tnode* branch[], int len, ofstream& file)
{
    for (int i = 0 ; i < len ; i++)
    {
        print_tableaux_node_file(branch[i], file);
        file << "{$\\;>\\;$}";
    }
}

void all_branches_tex(Tnode* node, int len, ofstream& file, Tnode* one, Tnode* two, bool closed_branch)
{
    if (node)
    {
        if (is_letter(node->root->symbol))
        {
            occurence[node->sign][node->root->symbol]++;

            if (occurence[1 - (node->sign)][node->root->symbol] > 0)
            {
                one = letters[1 - node->sign][node->root->symbol][number[1 - node->sign][node->root->symbol] - 1];
                two = node;
                closed_branch = true;
            }
            letters[node->sign][node->root->symbol][number[node->sign][node->root->symbol]++] = node;
            if (occurence[F]['1'] > 0 || occurence[T]['0'] > 0)
            {
                one = node;
                two = NULL;
                closed_branch = true;
            }
        }

        branch[len++] = node;

        if (node->left == NULL && node->right == NULL) // leaf
        {
            print_branch_file(branch, len, file);
            if (closed_branch)
            {
                file <<"{$X\\;\\;\\;$}\\begin{boldmath}{$|$}";
                if (two)
                {
                    print_tableaux_node_file(one, file);
                    file << "{ and }";
                    print_tableaux_node_file(two, file);
                }
                else
                    print_tableaux_node_file(one, file);

                file <<"{$|\\newline$}\\end{boldmath}\n\n";
            }
            else file << "\\textbf{not closed\\newline}\n\n";
        }

        all_branches_tex(node->left, len, file, one, two, closed_branch);
        if (node->left && is_letter(node->left->root->symbol))
        {
            occurence[node->left->sign][node->left->root->symbol]--;
            number[node->left->sign][node->left->root->symbol]--;
        }
        all_branches_tex(node->right, len, file, one, two, closed_branch);
        if (node->right && is_letter(node->right->root->symbol))
        {
            occurence[node->right->sign][node->right->root->symbol]--;
            number[node->right->sign][node->right->root->symbol]--;
        }
    }
}

void meaning(ofstream& file) // abbreviations and their meanings
{
    file <<"\n\\vspace{24pt}\n\\flushleft\\Large{Abbreviations:\\newline}\\vspace{-12pt}\n\\flushleft\\small";
    file <<"{$|\\alpha\\backslash \\beta :\\;BAC|$ - Branch already closed, so no rule applied\\newline}\n";
    file <<"{$|\\alpha\\backslash\\beta:\\;(x_1,y_1)...(x_n,y_n)|$}{ - first part represents applied rule; ";
    file <<"second part shows all pairs of nodes created by that rule\\newline}\n";
    file <<"{$X$}{ - end of closed branch\\newline}\n";
    file <<"{$|(n_1)\\;T\\backslash F\\;a\\;\\;and\\;\\;(n_2)\\;F\\backslash T\\;a|$}{ - reason for closing a branch; $n_1$ and $n_2$ are numbers of nodes\\newline}\n";
    file <<"{$|(n)\\;F\\;\\top|$ or $|(n)\\;T\\;bot|$ - reason for closing a branch; $n$ is number of node}";
}

void tex_file(Tnode* root)
{
    find_positions(root, 0, TEXT_WIDTH);

    ofstream file("tableaux.tex");

    file << "\\documentclass{article}\n\\usepackage[utf8]{inputenc}\n\\usepackage{changepage}\n";

    file << "\\usepackage[left=0.44482502in, right=0.44482502in]{geometry}\n\\begin{document}\n";

    generate_tex(root, file);
    all_branches_tex(root, 0, file, NULL, NULL, false);
    meaning(file);

    file << "\\end{document}\n";
}
