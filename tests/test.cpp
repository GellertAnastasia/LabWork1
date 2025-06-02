#include "gtest/gtest.h"
#include "filter.h"
#include "rotate.h"
#include <chrono>
#include <fstream>
#include <filesystem>
#include <cmath>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


double FileDiffPercent(const std::string& file1, const std::string& file2) {
    std::ifstream f1(file1, std::ios::binary);
    std::ifstream f2(file2, std::ios::binary);
    f1.seekg(0, std::ios::end);
    f2.seekg(0, std::ios::end);
    const size_t size1 = f1.tellg();
    const size_t size2 = f2.tellg();
    if (size1 != size2) {
        return 100.0;
    }
    f1.seekg(0);
    f2.seekg(0);
    size_t total_bytes = size1;
    size_t diff_count = 0;
    char byte1, byte2;
    while (f1.get(byte1) && f2.get(byte2)) {
        if (static_cast<unsigned char>(byte1) != static_cast<unsigned char>(byte2)) {
            diff_count++;
        }
    }
    return (static_cast<double>(diff_count) / total_bytes) * 100.0;
}


TEST(AllTest, ResultsIdentical) {
    std::ifstream infile("source.bmp", std::ios::in | std::ios::binary);
    Bmp bmp;
    infile.read(reinterpret_cast<char*>(&bmp), 54);
    rotate(bmp, "clockwise1.bmp", true);
    old_rotate(bmp, "clockwise2.bmp", true);
    EXPECT_EQ(FileDiffPercent("clockwise1.bmp", "clockwise2.bmp"), 0);
    std::filesystem::remove("clockwise1.bmp");
    std::filesystem::remove("clockwise2.bmp");
    
    rotate(bmp, "counterclockwise1.bmp", false);
    old_rotate(bmp, "counterclockwise2.bmp", false);
    EXPECT_EQ(FileDiffPercent("counterclockwise1.bmp", "counterclockwise2.bmp"), 0);
    std::filesystem::remove("counterclockwise1.bmp");
    std::filesystem::remove("counterclockwise2.bmp");

    apply_gaussian_blur("source.bmp",5,1.0f);
    old_apply_gaussian_blur("source.bmp",5,1.0f);
    EXPECT_LT(FileDiffPercent("filter_old.bmp", "filter_new.bmp"), 0.1);
    std::filesystem::remove("filter_old.bmp");
    std::filesystem::remove("filter_new.bmp");
}


TEST(RotateTest, Clockwise)
{
    std::ifstream infile("source.bmp", std::ios::in | std::ios::binary);
    Bmp bmp;
    infile.read(reinterpret_cast<char*>(&bmp), 54);
    auto start = std::chrono::high_resolution_clock::now();
    rotate(bmp, "clockwise.bmp", true);
    auto end = std::chrono::high_resolution_clock::now();
    auto oldstart = std::chrono::high_resolution_clock::now();
    old_rotate(bmp, "clockwise.bmp", true);
    auto oldend = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::chrono::duration<double> oldduration = oldend - oldstart;
    std::cout << "Time: " << duration.count()<<" " <<oldduration.count() << " seconds\n";
    std::filesystem::remove("clockwise.bmp");
    EXPECT_TRUE(true);
}

TEST(RotateTest, Counterclockwise)
{
    std::ifstream infile("source.bmp", std::ios::in | std::ios::binary);
    Bmp bmp;
    infile.read(reinterpret_cast<char*>(&bmp), 54);
    auto start = std::chrono::high_resolution_clock::now();
    rotate(bmp, "counterclockwise.bmp", false);
    auto end = std::chrono::high_resolution_clock::now();
    auto oldstart = std::chrono::high_resolution_clock::now();
    old_rotate(bmp, "counterclockwise.bmp", false);
    auto oldend = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::chrono::duration<double> oldduration = oldend - oldstart;
    std::cout << "Time: " << duration.count()<< " " <<oldduration.count() << " seconds\n";
    std::filesystem::remove("counterclockwise.bmp");
    EXPECT_TRUE(true);
}

TEST(GaussTest, Gauss)
{
    std::ifstream infile("source.bmp", std::ios::in | std::ios::binary);
    Bmp bmp;
    infile.read(reinterpret_cast<char*>(&bmp), 54);
    auto start = std::chrono::high_resolution_clock::now();
    apply_gaussian_blur("source.bmp",5,1.0f);
    auto end = std::chrono::high_resolution_clock::now();
    auto oldstart = std::chrono::high_resolution_clock::now();
    old_apply_gaussian_blur("source.bmp",5,1.0f);
    auto oldend = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::chrono::duration<double> oldduration = oldend - oldstart;
    std::cout << "Time: " << duration.count()<<" " <<oldduration.count() << " seconds\n";
    std::filesystem::remove("filter.bmp");
    EXPECT_TRUE(true);
}
