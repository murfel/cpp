#include "huffman.h"
#include <bits/stdc++.h>

void HuffTree::build_code(int index, std::string s) {
    if (tree[index].code < 256) {
        symbol_to_code[tree[index].code] = s;
    }
    else {
        s += "0";
        build_code(tree[index].left, s);
        s.pop_back();
        s += "1";
        build_code(tree[index].right, s);
        s.pop_back();
    }
}

HuffmanArchiver::HuffmanArchiver(std::string input_file) : input_file_(input_file) {
    std::vector<int> frequncy_count(256, 0);
    std::ifstream ifs(input_file.c_str());
    char c;
    while (ifs.get(c)) {
        frequncy_count[static_cast<unsigned char>(c)]++;
    }
    ifs.close();
    tree_.tree.resize(frequncy_count.size());
    for (size_t i = 0; i < frequncy_count.size(); ++i) {
        if (frequncy_count[i]) {
            tree_.tree[i] = {-1, -1, -1, i};
        }
    }
    std::set<std::pair<int, int>> s;
    for (size_t i = 0; i < frequncy_count.size(); ++i) {
        if (frequncy_count[i]) {
            s.insert({frequncy_count[i], i});
        }
    }
    while (s.size() != 1) {
        std::pair<int, int> min1 = *s.begin();
        s.erase(s.begin());
        std::pair<int, int> min2 = *s.begin();
        s.erase(s.begin());
        TreeNode node = {-1, min1.second, min2.second, frequncy_count.size()};
        tree_.tree.push_back(node);
        tree_.tree[node.left].parent = node.code;
        tree_.tree[node.right].parent = node.code;
        s.insert({min1.first + min2.first, node.code});
        frequncy_count.push_back(min1.first + min2.first);
    }
    tree_.root = (*s.begin()).second;
    tree_.build_code(tree_.root, "");
    for (auto i : tree_.symbol_to_code) {
        std::cerr << i.first << " " << i.second << std::endl;
    }
}

void HuffmanArchiver::save(std::string output_file) {
    std::ofstream ofs(output_file.c_str());
    BinaryOfstream bofs(ofs);

    std::ifstream ifs(input_file_.c_str());
    char c;
    while (ifs.get(c)) {
        bofs << tree_.symbol_to_code[static_cast<unsigned char>(c)];
        std::cerr << tree_.symbol_to_code[static_cast<unsigned char>(c)] << " ";
    }
    std::cerr << std::endl;
    bofs.flush();
    ifs.close();
    ofs.close();
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





















