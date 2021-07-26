#include <iostream>
#include "tree.hpp"
#include "well_formed.hpp"
#include "tableaux.hpp"
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
            t_free_tree(tableaux);
        }
        free_tree(root);
    }
    else
        printf("invalid unput\n");

    return 0;
}
