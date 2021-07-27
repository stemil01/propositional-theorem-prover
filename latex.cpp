#include <iostream>
#include <fstream>
#include "tree.hpp"
#include "latex.hpp"
using namespace std;

// check type of arguments !!
void generate_tex(Tnode* root, ofstream& file)
{

}

ofstream tex_file(Tnode* root)
{
    ofstream file("tableaux.tex");
    // insert header for latex file
    file << "\\documentclass{article}\n\\begin{document}\n";
    // ...
    file << "\node{F , }"
    generate_tex(root, file);

    file << "\end{document}\n"; // file footer here
    return file;
}
