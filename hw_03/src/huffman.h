#include <bits/stdc++.h>
#include <cstdint>

class TreeNode {
public:
    int parent;
    int left;
    int right;
    std::size_t code;
};

class HuffTree {
public:
    void build_code(int index, std::string s);
    std::vector<TreeNode> tree;
    std::size_t root;
    std::unordered_map<int, std::string> symbol_to_code;
};

class HuffmanArchiver {
public:
    HuffmanArchiver(std::string input_file);
    void save(std::string output_file);
private:
    std::string input_file_;
    HuffTree tree_;
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