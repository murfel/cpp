#include "huffman.h"
#include <bits/stdc++.h>
#include <ios>

BinaryOfstream::~BinaryOfstream() {
    if (counter_) {
        ofs_.write(reinterpret_cast<char *>(&buffer_), 1);
    }
}

BinaryOfstream& BinaryOfstream::operator<<(std::vector<bool> output) {
    for (std::size_t i = 0; i < output.size(); ++i) {
        if (counter_ == 8) {
            ofs_.write(reinterpret_cast<char *>(&buffer_), 1);
            counter_ = 0;
            buffer_ = 0;
        }
        buffer_ |= (output[i] << counter_++);
    }
    return *this;
}

BinaryIfstream& BinaryIfstream::operator>>(bool & input) {
    if (counter_ == 8) {
        ifs_.read(reinterpret_cast<char *>(&buffer_), 1);
        counter_ = 0;
        if (ifs_.eof()) {
            eof_ = 1;
        }
    }
    input = (buffer_ >> counter_) & 1;
    ++counter_;
    return *this;
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

void HuffTree::build_code(int index, std::vector<bool> code) {
    if (index == -1) { index = root_; code = std::vector<bool>(); }
    if (tree_[index].left == -1) {
        symbol_to_code_[index] = code;
    }
    else {
        code.push_back(0);
        build_code(tree_[index].left, code);
        code.pop_back();
        code.push_back(1);
        build_code(tree_[index].right, code);
        code.pop_back();
    }
}

int HuffTree::get_child(int index, bool right) const {
    if (static_cast<std::size_t>(index) >= tree_.size()) {
        throw std::runtime_error("Index out-of-bound.");
    }
    return right ? tree_[index].right : tree_[index].left;
}

std::vector<bool> HuffTree::get_code_of(int symbol) const {
    if (symbol_to_code_.find(symbol) == symbol_to_code_.end()) {
        throw std::runtime_error("A code for non-existent symbol requested.");
    }
    return (*symbol_to_code_.find(symbol)).second;
}

std::string HuffTree::get_string_code_of(int symbol) const {
    std::string code = "";
    for (auto i : (*symbol_to_code_.find(symbol)).second) {
        code += (i ? "1" : "0");
    }
    return code;
}


void compress(std::string input_file, std::string output_file) {
    std::vector<int> frequencies(256, 0);
    std::ifstream ifs(input_file.c_str());
    char c;
    std::size_t file_size = 0;
    while (ifs.get(c)) {
        frequencies[static_cast<unsigned char>(c)]++;
        ++file_size;
    }
    std::ofstream ofs(output_file.c_str());
    for (auto i : frequencies) {
        ofs.write(reinterpret_cast<char *>(&i), sizeof(int));
    }
    ofs.write(reinterpret_cast<char *>(&file_size), sizeof(int));

    HuffTree tree(frequencies);
    tree.build_code();

    ifs.clear();
    ifs.seekg(0, std::ios::beg);
    BinaryOfstream bofs(ofs);
    while (ifs.get(c)) {
        bofs << tree.get_code_of(c);
    }
}


void decompress(std::string input_file, std::string output_file) {
    std::ifstream ifs(input_file.c_str());
    std::vector<int> frequencies(256);
    for (std::size_t i = 0; i < frequencies.size(); ++i) {
        ifs.read(reinterpret_cast<char *>(&frequencies[i]), sizeof(int));
    }
    int count;
    ifs.read(reinterpret_cast<char *>(&count), sizeof(int));
    HuffTree tree(frequencies);
    tree.build_code();
    BinaryIfstream bifs(ifs);
    std::ofstream ofs(output_file.c_str());
    int cur = tree.get_root();
    while (bifs && count) {
        bool bit;
        bifs >> bit;
        if (tree.get_child(cur, bit) == -1) {
            ofs.write(reinterpret_cast<char *>(&cur), 1);
            cur = tree.get_root();
            --count;
        }
        cur = tree.get_child(cur, bit);
    }
}