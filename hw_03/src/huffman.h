#pragma once
#include <bits/stdc++.h>
#include <cstdint>

class HuffTree {
public:
    size_t get_root() const { return root; }
    void set_root(size_t new_root) { root = new_root; }
    void insert_node(std::size_t parent, std::size_t left, std::size_t right, std::size_t symbol) {
        std::cerr << std::max(std::max(parent, left), std::max(right, symbol)) << std::endl;
        tree.reserve(std::max(std::max(parent, left), std::max(right, symbol)));
        tree[symbol] = {parent, left, right, symbol};
        tree[left].parent = symbol;
        tree[right].parent = symbol;
        if (parent == static_cast<std::size_t >(-1)) {
            root = symbol;
        }
    }
    size_t get_left_of(std::size_t symbol) { return tree[symbol].left; }
    size_t get_right_of(std::size_t symbol) { return tree[symbol].right; }
    std::string get_code_of(std::size_t symbol) { return symbol_to_code[symbol]; }
    void build_code(size_t index = -1, std::string s = "");
private:
    struct TreeNode {
        std::size_t parent;
        std::size_t left;
        std::size_t right;
        std::size_t symbol;
    };
    std::vector<TreeNode> tree;
    std::size_t root;
    std::unordered_map<std::size_t, std::string> symbol_to_code;

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

void compress(std::string input_file, std::string output_file);
void decompress(std::string input_file, std::string output_file);