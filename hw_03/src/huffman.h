#pragma once
#include <bits/stdc++.h>
#include <cstdint>

class HuffTree {
public:
    HuffTree(std::vector<int> & frequencies);
    void build_code(int index = -1, std::string s = "");
    std::string get_code_of(int symbol) { return symbol_to_code_[symbol]; }
private:
    struct TreeNode {
        int parent;
        int left;
        int right;
    };
    std::vector<TreeNode> tree_;
    std::size_t root_;
    std::unordered_map<std::size_t, std::string> symbol_to_code_;
};

class BinaryOfstream {
public:
    BinaryOfstream(std::ofstream& ofs) : ofs_(ofs), buffer_(0), counter_(0) {};
    BinaryOfstream& operator<<(std::string s);
    void flush();
private:
    std::ofstream& ofs_;
    std::int8_t buffer_;
    int counter_;
};

void count_frequencies(std::string input_file, std::vector<int> & frequencies);
void compress(std::string input_file, std::string output_file);
void decompress(std::string input_file, std::string output_file);