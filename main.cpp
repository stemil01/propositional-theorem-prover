#include <iostream>
#include "tree.hpp"
#include "well_formed.hpp"
using namespace std;

int main()
{
    string input;
    cin >> input;

    Node *root = create_node('a');
    if (root == NULL)
        cout << "error\n";
    else
        cout << (*root).symbol << '\n';

    return 0;
}
