#include "inverted-index.h"
#include <iostream>
#include <string>
#include <vector>

void error(const char* text) {
    ELOG(text);
    exit(-1);
}

int getMax(FILE * inputStream) {
    int max = 0, test, trash;
    while (fscanf(inputStream, "%d:%d", &test, &trash) != EOF) {
        if (test > max) {
            max = test;
        }
    }
    return max;
}

void readTextFile(FILE* inputStream, std::vector<data_t>* dest) {
    int currCat, currFreq, currTerm;
    char cBuff;

    for (int currDoc = 1; fscanf(inputStream, "%d", &currCat) != EOF; currDoc++) {
        do {
            fscanf(inputStream, "%d:%d%c", &currTerm, &currFreq, &cBuff);
            dest[currTerm].push_back({currDoc, currFreq, currCat});
        } while (cBuff != '\n');
    }
}

void createBinFile(FILE *outputStream, std::vector<data_t>* source, int maxTerm) {
    fwrite(&maxTerm, sizeof(int), 1, outputStream);
    for (int i = 0; i <= maxTerm; i++) {
        int size = source[i].size();
        fwrite(&size, sizeof(int), 1, outputStream);
        for (data_t d : source[i]) {
            fwrite(&d.document, sizeof(int), 1, outputStream);
            fwrite(&d.frequency,sizeof(int), 1, outputStream);
            fwrite(&d.category, sizeof(int), 1, outputStream);
        }
    }
}

void readBinFile(FILE *sourceStream, std::vector<data_t> **dest, int *maxTerm) {
    fread(maxTerm, sizeof(int), 1, sourceStream);
    data_t buffer;
    *dest = new std::vector<data_t>[*maxTerm + 1];
    for (int i = 0; i <= *maxTerm; i++) {
        int currTermSize;
        fread(&currTermSize, sizeof(int), 1, sourceStream);
        for (int j = 0; j < currTermSize; j++) {
            fread(&buffer.document, sizeof(int), 1, sourceStream);
            fread(&buffer.frequency,sizeof(int), 1, sourceStream);
            fread(&buffer.category, sizeof(int), 1, sourceStream);
            (*dest)[i].push_back(buffer);
        }
    }
}

std::vector<int> searchIntersec(std::vector<data_t> *data, int size) {
    int term1, term2;
    LOG("Insert the two terms for search");

    std::cin >> term1;
    std::cin >> term2;

    std::vector<int> intersection;

    int index1 = 0, index2 = 0;
    while(index1 < data[term1].size() && index2 < data[term2].size()) {
             if (data[term1].at(index1).document == data[term2].at(index2).document) 
            intersection.push_back(data[term1].at(index1).document);
        else if (data[term1].at(index1).document >  data[term2].at(index2).document)
            index2++;
        else if (data[term1].at(index1).document >  data[term2].at(index2).document)
            index1++;
    }

    return intersection;
}