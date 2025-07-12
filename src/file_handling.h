#pragma once

int read_until_nl(int fd, char line[]);
void read_until_string(int fd, char buffer[], char search_string[]);
void seek_string_a(int fd, char search_string[]);
