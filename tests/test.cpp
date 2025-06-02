#include "gtest/gtest.h"
#include "filter.h"
#include "rotate.h"
#include <chrono>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(One,Two)
{
    std::ifstream infile("source.bmp", std::ios::in | std::ios::binary);
    Bmp bmp;
    infile.read(reinterpret_cast<char*>(&bmp), 54);
    auto start = std::chrono::high_resolution_clock::now();
    rotate(bmp, "clockwise.bmp", true);
    rotate(bmp, "counterclockwise.bmp", false);
    auto end = std::chrono::high_resolution_clock::now();
    auto oldstart = std::chrono::high_resolution_clock::now();
    old_rotate(bmp, "clockwise.bmp", true);
    old_rotate(bmp, "counterclockwise.bmp", false);
    auto oldend = std::chrono::high_resolution_clock::now();

    
    std::chrono::duration<double> duration = end - start;
    std::chrono::duration<double> oldduration = oldend - oldstart;
    std::cout << "Time: " << duration.count()<<oldduration.count() << " seconds\n";
    EXPECT_TRUE(true);
}
