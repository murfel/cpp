#pragma once
#include <bits/stdc++.h>
#include <cstdint>

class HuffTree {
public:
    HuffTree(std::vector<int> & frequencies);
    void build_code(int index = -1, std::vector<bool> code = std::vector<bool>());
    std::vector<bool> get_code_of(int symbol) const;
    std::string get_string_code_of(int symbol) const;
    int get_child(int index, bool right) const;
    int get_root() const { return root_; }
private:
    struct TreeNode {
        int parent;
        int left;
        int right;
    };
    std::vector<TreeNode> tree_;
    int root_;
    std::unordered_map<int, std::vector<bool>> symbol_to_code_;
};

class BinaryOfstream {
public:
    BinaryOfstream(std::ofstream& ofs) : ofs_(ofs), buffer_(0), counter_(0) {};
    ~BinaryOfstream();
    BinaryOfstream& operator<<(std::vector<bool> output);
private:
    std::ofstream& ofs_;
    std::int8_t buffer_;
    int counter_;
};

class BinaryIfstream {
public:
    BinaryIfstream(std::ifstream& ifs) : ifs_(ifs), buffer_(0), counter_(0), eof_(0) {};
    BinaryIfstream& operator>>(bool & input);
    operator bool() { return !eof_; }
private:
    std::ifstream& ifs_;
    std::int8_t buffer_;
    int counter_;
    bool eof_;
};


void compress(std::string input_file, std::string output_file);
void decompress(std::string input_file, std::string output_file);