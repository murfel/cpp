#include "huffman.h"
#include <bits/stdc++.h>

void HuffTree::build_code(size_t index, std::string s) {
    if (index == static_cast<std::size_t>(-1)) { index = root; s = ""; }
    if (tree[index].left == static_cast<std::size_t>(-1)) {
        symbol_to_code[tree[index].symbol] = s;
    }
    else {
        build_code(tree[index].left, s + "0");
        build_code(tree[index].right, s + "1");
    }
}

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

void compress(std::string input_file, std::string output_file) {
    std::vector<int> frequencies(256, 0);
    std::ifstream ifs(input_file.c_str());
    char c;
    while (ifs.get(c)) {
        frequencies[static_cast<unsigned char>(c)]++;
    }
    ifs.close();
    HuffTree tree;
    std::priority_queue<std::pair<int, int>> new_frequencies;
    for (size_t i = 0; i < frequencies.size(); ++i) {
        if (frequencies[i]) {
            tree.insert_node(-1, -1, -1, i);
            new_frequencies.push({frequencies[i], i});
        }
    }
    while (new_frequencies.size() != 1) {
        std::pair<int, int> min1 = new_frequencies.top();
        new_frequencies.pop();
        std::pair<int, int> min2 = new_frequencies.top();
        new_frequencies.pop();
        tree.insert_node(-1, min1.second, min2.second, frequencies.size());
        new_frequencies.push({min1.first + min2.first, frequencies.size()});
        frequencies.push_back(min1.first + min2.first);
    }
    tree.set_root(new_frequencies.top().second);
    tree.build_code();





//    for (auto i : tree_.symbol_to_code) {
//        std::cerr << i.first << " " << i.second << std::endl;
//    }
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


















