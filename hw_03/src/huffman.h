#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdint>

struct statistics_t {
    int32_t source_size;
    int32_t compressed_size;
    int32_t decompressed_size;
    static const int32_t EXTRA_INFO = 256 * sizeof(int32_t) + sizeof(int32_t);
};


class BinaryOstream {
public:
    BinaryOstream(std::ostream& os) : os_(os), buffer_(0), counter_(0) {};
    ~BinaryOstream();
    BinaryOstream& operator<<(std::vector<bool> output);
private:
    std::ostream& os_;
    std::int8_t buffer_;
    int counter_;
};


class BinaryIstream {
public:
    BinaryIstream(std::istream& is) : is_(is), counter_(8), eof_(0) {};
    BinaryIstream& operator>>(bool & input);
    operator bool() { return !eof_; }
private:
    std::istream& is_;
    std::int8_t buffer_;
    int counter_;
    bool eof_;
};


class HuffTree {
public:
    HuffTree(std::vector<int32_t> frequencies);
    int get_child(int index, bool right) const;
    int get_root() const { return root_; }
    std::vector<bool> get_code_of(int symbol) const;
private:
    void start_building_codes();
    void build_code(int index, std::vector<bool> code);
    struct TreeNode {
        TreeNode() {};
        TreeNode(int left, int right) : left(left), right(right) {};
        int left;
        int right;
    };
    std::vector<TreeNode> tree_;
    int root_;
    std::unordered_map<int, std::vector<bool>> symbol_to_code_;
};


void compress(std::istream & is, std::ostream & os, statistics_t & statistics);
void decompress(std::istream & is, std::ostream & os, statistics_t & statistics);