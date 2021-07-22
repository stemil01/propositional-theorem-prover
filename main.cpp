#include <iostream>
#include <string>
#include <cstring>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

int main()
{
    // get input string and add parenthesis at both ends
    char input[MAX_SIZE];
    cin.getline(input, MAX_SIZE - 2);
    format(input);

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
