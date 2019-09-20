#pragma once

#include <iostream>
#include <vector>

#define LOG(content) std::cout << content << std::endl
#define ELOG(content) std::cerr << content << std::endl

typedef struct d {
    int document;
    int frequency;
    int category;
} data_t;

void error(const char*);
int getMax(FILE*);
void readTextFile(FILE*, std::vector<data_t>*);
void readBinFile(FILE*, std::vector<data_t>**, int*);
void createBinFile(FILE*, std::vector<data_t>*, int);
std::vector<int> searchIntersec(std::vector<data_t>*, int);