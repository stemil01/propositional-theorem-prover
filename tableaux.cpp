#include "tableaux.hpp"
using namespace std;

// napravimo prazno drvo tabloa

static bool used[MAX_SIZE];
static int t_occurrence[26], t_occurrence[26];

vector<Tnode*> find_leaves(Tnode* node)
{
    return NULL;
}

Tnode* find_used(Tnode* root)
{
    if (!root->used)
        return root;
    Tnode *left = find_used(root->left);
    Tnode *right = find_used(root->right);
    return left ? left : right;
}

void check_tableaux(Tnode* node)
{
    if (is_letter(node->formula))
    {
        if (node->sign == 'F')
            if (t_occurence[node->formula] > 0)
                node->used = true;
        else if (f_ooccurence[node->formula] > 0)
            node->used = true;
    }
    check_tableaux(node->left);
    check_tableaux(node->right);
    if (node->left->used && node->right->used)
        node->used = true;
}

Tnode* tableaux(const char* f)
{
    while (!(Tnode *node = find_used()))
    {
        vector<Tnode*> leaves = find_leaves(node);

        for (auto leaf: leaves)
            if (node->sign && node->fomula)
            {
                primeni pravilo
            }

        check_tabeaux(node);
    }
}
