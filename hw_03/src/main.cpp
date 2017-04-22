#include "huffman.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <cstring>

struct CLI_Arguments {
    CLI_Arguments() {};
    CLI_Arguments(bool archive, std::string input_file, std::string output_file)
            : archive(archive), input_file(input_file), output_file(output_file) {};
    bool archive;
    std::string input_file;
    std::string output_file;
};

CLI_Arguments parse_args(int argc, char ** argv) {
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
            throw std::runtime_error("Unknown argument: " + std::string(argv[i]));
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
    return CLI_Arguments(archiving, input_file, output_file);
}


int main(int argc, char ** argv) {
    CLI_Arguments args;
    try {
         args = parse_args(argc, argv);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }

    if (args.archive) {
        compress(args.input_file, args.output_file);
    }
    else {
        decompress(args.input_file, args.output_file);
    }

    return 0;
}
































