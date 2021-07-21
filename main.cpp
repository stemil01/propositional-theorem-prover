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
    cin.getline(input + 1, MAX_SIZE - 3);
    input[0] = '(';
    int length = strlen(input);
    input[length] = ')';
    input[length + 1] = '\0';

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
