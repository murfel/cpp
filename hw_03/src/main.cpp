#include "huffman.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <exception>
#include <stdexcept>
#include <string>
#include <cstring>

#include "gtest/gtest.h"

enum action_t { archive, dearchive };

struct CliArguments {
    action_t action;
    std::string input_file;
    std::string output_file;
};

CliArguments parse_args(int argc, char ** argv) {
    CliArguments args;
    bool archiving = false;
    bool dearchiving = false;
    bool input_file_specified = false;
    bool output_file_specified = false;
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
            args.input_file = argv[++i];
        } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
            output_file_specified = true;
            if (i == argc - 1) {
                throw std::runtime_error("No output file is specified.");
            }
            args.output_file = argv[++i];
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

    args.action = archiving ? archive : dearchive;
    return args;
}


int main(int argc, char ** argv) {
    CliArguments args;
    try {
         args = parse_args(argc, argv);
    } catch (std::runtime_error& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    statistics_t statistics;
    try {
        if (args.action == archive) {
                std::ifstream ifs(args.input_file.c_str());
                std::ofstream ofs(args.output_file.c_str());
                compress(ifs, ofs, statistics);
                std::cout << statistics.source_size << std::endl;
                std::cout << statistics.compressed_size << std::endl;
                std::cout << statistics.EXTRA_INFO << std::endl;
        }
        else {
            std::ifstream ifs(args.input_file.c_str());
            std::ofstream ofs(args.output_file.c_str());
            decompress(ifs, ofs, statistics);
            std::cout << statistics.decompressed_size << std::endl;
            std::cout << statistics.compressed_size << std::endl;
            std::cout << statistics.EXTRA_INFO << std::endl;
        }
    } catch (const std::exception & e) {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}






























