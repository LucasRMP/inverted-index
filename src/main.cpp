/**
 * Inverted index for lazy machine learning
 * by: Lucas R. M. Pessone
 * The program creates a inverted index based on a formatted text file,
 * saves it into a binary file and makes a intersection search.
 * If the binary file alredy exists, the program loads it and make the search
*/

#include "inverted-index.h"
#include <iostream>
#include <string>
#include <vector>

std::string getDirectory();
bool shouldCreateBinFile();

int main() {
    
    std::string directory = getDirectory();
    FILE * inputStream;

    if (shouldCreateBinFile()) {
        inputStream = fopen(directory.c_str(), "rt");
        if (!inputStream) {
            error("Couldn't open input file");
        }

        int MAX = getMax(inputStream);
        LOG("Biggest term found as: " << MAX);
        fclose(inputStream);
        inputStream = fopen(directory.c_str(), "rt");
        if (!inputStream) {
            error("Couldn't open input file");
        }

        std::vector<data_t> *data = new std::vector<data_t>[MAX];
        readTextFile(inputStream, data);
        fclose(inputStream);

        FILE * outputStream = fopen("inverted-index-data.bin", "wb");
        if (!outputStream) {
            error("Couldn't create the output file");
        }

        createBinFile(outputStream, data, MAX);
        LOG("Binary file successfully created as 'inverted-index-data.bin' on your current directory");
        directory = "inverted-index-data.bin";
        
        fclose(outputStream);
        delete[] data;
    }

    inputStream = fopen(directory.c_str(), "rb");
    if (!inputStream) {
        error("Couldn't open input binary file");
    }

    std::vector<data_t> *data;
    int MAX;
    readBinFile(inputStream, &data, &MAX);
    fclose(inputStream);
    LOG("Binary file successfully opened"); 

    while (true) {
        std::vector<int> result = searchIntersec(data, MAX);
        LOG("Both terms occured in documments: ");
        for (auto i : result) {
            std::cout << "D" << i << ' ';
        }
        LOG("Press enter to do it again or ctrl+c to exit");
    }

    delete[] data;
    return 0;
}

std::string getDirectory() {
    std::string directory;
    std::cout << "Insert the file directory here: ";
    std::cin >> directory;
    return directory;
}

bool shouldCreateBinFile() {
    char should;
    std::cout << "Do you want to create the binary file? [y/n] ";
    std::cin >> should;
    return (should == 'y' || should == 'Y');
}