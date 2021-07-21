#ifndef _WELL_FORMED_HPP_
#define _WELL_FORMED_HPP_

#define MAX_SIZE 1001

bool is_bin_symbol(char c);

bool is_letter(char c);

bool check_brackets(const char *input);

Node* create_tree(const char* input, int start, int end);

// checks well form of input and creates a tree with it
Node *check_well_form(const char *input);

#endif
