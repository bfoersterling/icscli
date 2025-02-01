#pragma once

// this function will read until the next newline character
// and save the characters in a string you provide in arg2
int read_until_nl(int fd, char line[]);
