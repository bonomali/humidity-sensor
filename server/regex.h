#include <regex.h>
#include <stdio.h>

int compile_regex (regex_t * r, const char * regex_text);
int match_regex (regex_t * r, const char * to_match);