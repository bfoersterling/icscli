#pragma once

// cut string into two parts and choose one part
// side is 0 or 1
void cut_string(char my_string[], char delimiter, int side);
void remove_nl_and_cr(char raw_string[]);
void remove_whitespace(char raw_string[]);
void remove_until_delim(char raw_string[], char delimiter, int occurence);
