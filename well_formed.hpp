#ifndef _WELL_FORMED_HPP_
#define _WELL_FORMED_HPP_

void format(char* input);

bool is_bin_symbol(char c);

bool is_letter(char c);

bool check_brackets(const char *input, int start, int end);

bool embraced_brackets(const char* input, int start, int end);

bool blank(const char* input, int start, int end);

Node* create_tree(const char* input, int start, int end);

// checks well form of input and creates a tree with it
Node *check_well_form(char *input);

#endif
