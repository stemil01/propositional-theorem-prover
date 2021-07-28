#include <iostream>
#include <fstream>
#include <vector>
#include "tree.hpp"
#include "well_formed.hpp"
#include "tableaux.hpp"
#include "latex.hpp"
using namespace std;

int main()
{
    char input[MAX_SIZE];
    cin.getline(input, MAX_SIZE - 2);

    Node *root = check_well_form(input);
    if (root)
    {
        Tnode *tableaux = create_tableuax(root);
        if (tableaux)
        {
            print_signed_2D(tableaux, 0);
            find_positions(tableaux, 0, TEXT_WIDTH);
            tex_file(tableaux);
            t_free_tree(tableaux);
        }
        free_tree(root);

    }
    else
        printf("invalid unput\n");


    return 0;
}
