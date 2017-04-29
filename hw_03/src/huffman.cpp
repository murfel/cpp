#include "huffman.h"
#include <ios>
#include <queue>

using std::cerr;
using std::endl;

BinaryOstream::~BinaryOstream() {
    if (counter_) {
        os_.write(reinterpret_cast<char *>(&buffer_), 1);
    }
}

BinaryOstream& BinaryOstream::operator<<(std::vector<bool> output) {
    for (bool bit : output) {
        if (counter_ == 8) {
            os_.write(reinterpret_cast<char *>(&buffer_), 1);
            counter_ = 0;
            buffer_ = 0;
        }
        buffer_ |= (bit << counter_++);
    }
    return *this;
}

BinaryIstream& BinaryIstream::operator>>(bool & input) {
    if (counter_ == 8) {
        is_.read(reinterpret_cast<char *>(&buffer_), 1);
        counter_ = 0;
        if (is_.eof()) {
            eof_ = 1;
        }
    }
    input = (buffer_ >> counter_) & 1;
    ++counter_;
    return *this;
}


HuffTree::HuffTree(std::vector<int32_t> frequencies) {
    tree_.resize(frequencies.size());
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> new_frequencies;
    for (size_t i = 0; i < frequencies.size(); ++i) {
        if (frequencies[i]) {
            tree_[i] = TreeNode(-1, -1);
            new_frequencies.push({frequencies[i], i});
        }
    }
    while (new_frequencies.size() != 1) {
        std::pair<int, int> min1 = new_frequencies.top();
        new_frequencies.pop();
        std::pair<int, int> min2 = new_frequencies.top();
        new_frequencies.pop();
        tree_.push_back(TreeNode(min1.second, min2.second));
        frequencies.push_back(min1.first + min2.first);
        new_frequencies.push({frequencies.back(), tree_.size() - 1});

    }
    root_ = new_frequencies.top().second;
    start_building_codes();
}

int HuffTree::get_child(int index, bool right) const {
    return right ? tree_.at(index).right : tree_.at(index).left;
}

std::vector<bool> HuffTree::get_code_of(int symbol) const {
    auto it = symbol_to_code_.find(symbol);
    if (it == symbol_to_code_.end()) {
        throw std::runtime_error("A code for non-existent symbol requested.");
    }
    return it->second;
}

void HuffTree::start_building_codes() {
    build_code(root_, std::vector<bool>());
}

void HuffTree::build_code(int index, std::vector<bool> code) {
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


void compress(std::istream & is, std::ostream & os, statistics_t & statistics) {
    std::vector<int32_t> frequencies(256, 0);
    char c;
    int32_t file_size = 0;
    while (is.get(c)) {
        frequencies[static_cast<unsigned char>(c)]++;
        ++file_size;
    }
    for (int32_t freq : frequencies) {
        os.write(reinterpret_cast<char *>(&freq), sizeof(int32_t));
    }
    os.write(reinterpret_cast<char *>(&file_size), sizeof(int32_t));
    HuffTree tree(std::move(frequencies));
    is.clear();
    is.seekg(0, std::ios::beg);
    BinaryOstream bos(os);
    while (is.get(c)) {
        bos << tree.get_code_of(c);
    }
    statistics.source_size = file_size;
    statistics.compressed_size = static_cast<int32_t>(os.tellp()) + 1;
}


void decompress(std::istream & is, std::ostream & os, statistics_t & statistics) {
    std::vector<int32_t> frequencies(256);
    for (int32_t & freq : frequencies) {
        is.read(reinterpret_cast<char *>(&freq), sizeof(int32_t));
    }
    int32_t count;
    is.read(reinterpret_cast<char *>(&count), sizeof(int32_t));
    HuffTree tree(std::move(frequencies));
    BinaryIstream bis(is);
    int cur = tree.get_root();
    while (bis && count) {
        bool bit;
        bis >> bit;
        if (tree.get_child(cur, bit) == -1) {
            os.write(reinterpret_cast<char *>(&cur), 1);
            cur = tree.get_root();
            --count;
        }
        cur = tree.get_child(cur, bit);
    }
    statistics.decompressed_size = static_cast<int32_t>(is.tellg()) - statistics.EXTRA_INFO;
    statistics.compressed_size = os.tellp();
}



























