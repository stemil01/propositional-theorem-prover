#include <bits/stdc++.h>
#include "tree.hpp"
#include "well_formed.hpp"

using namespace std;

typedef struct Tnode
{
    char sign;
    Node *root;
    bool used;
    struct Tnode *left, *right;

}Tnode;

Tnode* create_tnode(char s, Node *root)
{
    Tnode *tnode = new Tnode;
    if(tnode == NULL)
        return NULL;

    tnode->sign = s;
    tnode->root = root;
    tnode->left = NULL;
    tnode->right = NULL;
    tnode->used = false;

    return tnode;
}

static vector<Tnode*> leaves;

void find_leaves(Tnode *node)
{
    if(node == NULL)
        return ;

    if(node->left == NULL && node->right == NULL)
        leaves.push_back(node);

    find_leaves(node->left);
    find_leaves(node->right);
}

Tnode* find_root(Tnode* root)
{
    Tnode *left, *right;

    if(root && !(root->used))
        return root;

    if(root && root->left == NULL)
        left =  NULL;
    else
        left = find_root(root->left);

    if(root && root->right == NULL)
        right = NULL;
    else
        right = find_root(root->right);

    return left ? left : right;

}

//customized print2DUtil for signed formula
static const int COUNT = 7;

void print_signed_2D(Tnode *troot, int space)
{
    if(troot == NULL)
        return ;

    space += COUNT;

    print_signed_2D(troot->right, space);

    printf("\n");

    for(int i = COUNT; i < space ; i++)
        printf(" ");

    cout<<troot->sign<< " ";
    print_tree(troot->root);
    cout<<'\n';

    print_signed_2D(troot->left, space);

}

void tableuax(Tnode *root)//moze manje ruzno da izgleda, ali sam gmaz
{
    while(Tnode *tnode = find_root(root))
    {
        tnode->used = true;

        find_leaves(tnode);

        //ALFA FORMULAS

        if(tnode->sign == 'T' && tnode->root->symbol == '&') // T A&B
            {
                for(Tnode *leaf : leaves)
                {
                    Tnode *tnode1 = create_tnode('T', tnode->root->left);
                    Tnode *tnode2 = create_tnode('T', tnode->root->right);
                    leaf->left = tnode1;
                    tnode1->left = tnode2;
                }
            }
        if(tnode->sign == 'F' && tnode->root->symbol == '|') // F A|B
            {
                for(Tnode *leaf : leaves)
                {
                    Tnode *tnode1 = create_tnode('F', tnode->root->left);
                    Tnode *tnode2 = create_tnode('F', tnode->root->right);
                    leaf->left = tnode1;
                    tnode1->left = tnode2;
                }
            }
        if(tnode->sign == 'F' && tnode->root->symbol == '>') // F A>B
            {
                for(Tnode *leaf : leaves)
                {
                    Tnode *tnode1 = create_tnode('T', tnode->root->left);
                    Tnode *tnode2 = create_tnode('F', tnode->root->right);
                    leaf->left = tnode1;
                    tnode1->left = tnode2;
                }
            }
        if(tnode->sign == 'F' && tnode->root->symbol == '*') // F *A
            {
                for(Tnode *leaf : leaves)
                {
                    Tnode *tnode1 = create_tnode('T', tnode->root->right);
                    Tnode *tnode2 = create_tnode('T', tnode->root->right);
                    leaf->left = tnode1;
                    tnode1->left = tnode2;
                }
            }
        if(tnode->sign == 'T' && tnode->root->symbol == '*') // T *A
            {
                for(Tnode *leaf : leaves)
                {
                    Tnode *tnode1 = create_tnode('F', tnode->root->right);
                    Tnode *tnode2 = create_tnode('F', tnode->root->right);
                    leaf->left = tnode1;
                    tnode1->left = tnode2;
                }
            }

        //BETA FORMULAS

        if(tnode->sign == 'F' && tnode->root->symbol == '&') // F A&B
            {
                for(Tnode *leaf : leaves)
                {
                    Tnode *tnode1 = create_tnode('F', tnode->root->left);
                    Tnode *tnode2 = create_tnode('F', tnode->root->right);
                    leaf->left = tnode1;
                    leaf->right = tnode2;
                }
            }
        if(tnode->sign == 'T' && tnode->root->symbol == '|') // T A|B
            {
                for(Tnode *leaf : leaves)
                {
                    Tnode *tnode1 = create_tnode('T', tnode->root->left);
                    Tnode *tnode2 = create_tnode('T', tnode->root->right);
                    leaf->left = tnode1;
                    leaf->right = tnode2;
                }
            }
        if(tnode->sign == 'T' && tnode->root->symbol == '>') // T A>B
            {
                for(Tnode *leaf : leaves)
                {
                    Tnode *tnode1 = create_tnode('F', tnode->root->left);
                    Tnode *tnode2 = create_tnode('T', tnode->root->right);
                    leaf->left = tnode1;
                    leaf->right = tnode2;
                }
            }

        leaves.clear();//empty the vector for leaves of next unused signed node
    }
}

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

    Tnode *troot = create_tnode('F', root);//starting tableaux with F "formula"

    tableuax(troot);

    print_signed_2D(troot, 0);


    return 0;
}
