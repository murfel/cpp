#include "huffman.h"
#include "gtest/gtest.h"

TEST(huffman_test, basic) {
    std::stringstream input;
    input << "abacabad";
    std::stringstream compressed;
    std::stringstream decompressed;

    statistics_t statistics;
    compress(input, compressed, statistics);
    decompress(compressed, decompressed, statistics);
    EXPECT_EQ(input.str(), decompressed.str());
}

TEST(huffman_test, boundary) {
    std::stringstream input;
    input << "a";
    std::stringstream compressed;
    std::stringstream decompressed;

    statistics_t statistics;
    compress(input, compressed, statistics);
    decompress(compressed, decompressed, statistics);
    EXPECT_EQ(input.str(), decompressed.str());
}

TEST(huffman_test, empty_stream) {
    std::stringstream input;
    std::stringstream compressed;
    std::stringstream decompressed;

    statistics_t statistics;
    compress(input, compressed, statistics);
    decompress(compressed, decompressed, statistics);
    EXPECT_EQ(input.str(), decompressed.str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}