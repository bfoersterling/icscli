// the same as read_until_string, but this function not only truncates but fills remaining chars with null characters
// this function is cleaner and nicer to work with, but not as fast as "read_until_string"
// ct means "clean truncate"

#pragma once

void read_until_string(int fd, char buffer[], char search_string[]);
