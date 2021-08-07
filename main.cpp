#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "tree.hpp"
#include "well_formed.hpp"
#include "tableaux.hpp"
#include "latex.hpp"
using namespace std;

int main()
{
    char input[MAX_SIZE];
    cout << "Propositional formula: ";
    cin.getline(input, MAX_SIZE - 2);

    Node *root = check_well_form(input);
    if (root)
    {
        Tnode *tableaux = create_tableaux(root);
        if (tableaux)
        {
            print_enumerated_2D(tableaux); cout << '\n';
            tex_file(tableaux);
            if (tableaux->closed)
                cout << "formula is tautology\n";
            else
            {
                cout << "formula is not tautology\n";
                cout << "Countermodels? [y/N]: ";
                char answer = cin.get();
                if (answer == 'Y' || answer == 'y')
                    print_countermodels(tableaux);
            }
            t_free_tree(tableaux);
        }
        free_tree(root);
    }
    else
        printf("invalid unput\n");


    return 0;
}
