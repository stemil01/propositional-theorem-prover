#include <iostream>
#include <string>
#include <cstring>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

int main()
{
    char input[MAX_SIZE];
    cin.getline(input, MAX_SIZE - 2);

    Node *root = check_well_form(input);
    if (root)
    {
        cout << "valid form: ";
        print2D(root);
        cout << '\n';
    }
    else
        cout << "invalid form\n";

    return 0;
}
