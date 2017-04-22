#include "huffman.h"
#include <bits/stdc++.h>

BinaryOfstream& BinaryOfstream::operator<<(std::string s) {
    for (std::size_t i = 0; i < s.length(); ++i) {
        if (counter_ == 8) {
            ofs_ << buffer_;
            counter_ = 0;
            buffer_ = 0;
        }
        int8_t bit = s[i] - '0';
        buffer_ |= bit << counter_++;
    }
    return *this;
}

void BinaryOfstream::flush() {
    ofs_ << buffer_;
    counter_ = 0;
    buffer_ = 0;
}

HuffTree::HuffTree(std::vector<int> & frequencies) {
    tree_.resize(frequencies.size());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> new_frequencies;
    for (size_t i = 0; i < frequencies.size(); ++i) {
        if (frequencies[i]) {
            tree_[i] = {-1, -1, -1};
            new_frequencies.push({frequencies[i], i});
        }
    }
    while (new_frequencies.size() != 1) {
        std::pair<int, int> min1 = new_frequencies.top();
        new_frequencies.pop();
        std::pair<int, int> min2 = new_frequencies.top();
        new_frequencies.pop();
        tree_.push_back({-1, min1.second, min2.second});
        new_frequencies.push({min1.first + min2.first, frequencies.size()});
        frequencies.push_back(min1.first + min2.first);
    }
    root_ = new_frequencies.top().second;
}

void HuffTree::build_code(int index, std::string s) {
    if (index == -1) { index = root_; s = ""; }
    if (tree_[index].left == -1) {
        symbol_to_code_[index] = s;
    }
    else {
        build_code(tree_[index].left, s + "0");
        build_code(tree_[index].right, s + "1");
    }
}

void count_frequencies(std::string input_file, std::vector<int> & frequencies) {
    std::ifstream ifs(input_file.c_str());
    char c;
    while (ifs.get(c)) {
        frequencies[static_cast<unsigned char>(c)]++;
    }
}

void compress(std::string input_file, std::string output_file) {
    std::vector<int> frequencies(256, 0);
    count_frequencies(input_file, frequencies);
//    for (auto f : frequencies) {
//        if (f) std::cerr << f << "\n";
//    }
    HuffTree tree(frequencies);
    tree.build_code();
//    std::cerr << tree.get_code_of('a') << "\n";
//    std::cerr << tree.get_code_of('b') << "\n";
//    std::cerr << tree.get_code_of('c') << "\n";
//    std::cerr << tree.get_code_of('d') << "\n";

//    std::ofstream ofs(output_file.c_str());
//    BinaryOfstream bofs(ofs);
//
//    std::ifstream ifs(input_file.c_str());
//    while (ifs.get(c)) {
//        bofs << tree_.symbol_to_code[static_cast<unsigned char>(c)];
//        std::cerr << tree_.symbol_to_code[static_cast<unsigned char>(c)] << " ";
//    }
//    std::cerr << std::endl;
//    bofs.flush();
//    ifs.close();
//    ofs.close();
}


void decompress(std::string input_file, std::string output_file) {
    ;
}


















