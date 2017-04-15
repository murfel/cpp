#include "huffman.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <cstring>

int main(int argc, char ** argv) {
    bool archiving = false;
    bool dearchiving = false;
    bool input_file_specified = false;
    bool output_file_specified = false;
    std::string input_file;
    std::string output_file;
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-c") == 0) {
            archiving = true;
        } else if (strcmp(argv[i], "-u") == 0) {
            dearchiving = true;
        } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
            input_file_specified = true;
            if (i == argc - 1) {
                throw std::runtime_error("No input file is specified.");
            }
            input_file = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            output_file_specified = true;
            if (i == argc - 1) {
                throw std::runtime_error("No output file is specified.");
            }
            output_file = argv[++i];
        } else {
            std::cerr << "Ignoring unknown argument: " << argv[i] << std::endl;
        }
    }

    if (archiving && dearchiving) {
        throw std::runtime_error("Both archiving and dearchiving options are specified.");
    }
    if (!archiving && !dearchiving) {
        throw std::runtime_error("No action (archiving, dearchiving) is specified.");
    }
    if (!input_file_specified) {
        throw std::runtime_error("No input file is specified.");
    }
    if (!output_file_specified) {
        throw std::runtime_error("No output file is specified.");
    }

    if (archiving) {
        ;
    }

    HuffmanArchiver ha(input_file);
    ha.save("output.txt");

















    return 0;
}
