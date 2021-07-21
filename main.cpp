#include <iostream>
#include <string>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

int main()
{
    char input[MAX_SIZE];
    cin.getline(input, MAX_SIZE);

    Node *root = check_well_form(input);
    if (root)
    {
        cout << "valid form: ";
        print_tree(root);
        cout << '\n';
    }
    else
        cout << "invalid form\n";

    return 0;
}
