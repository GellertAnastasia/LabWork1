#include "gtest/gtest.h"
#include "filter.h"
#include "rotate.h"
#include <chrono>
#include <fstream>
#include <filesystem>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
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
    std::cout << "Time: " << duration.count()<<oldduration.count() << " seconds\n";
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
    std::cout << "Time: " << duration.count()<<oldduration.count() << " seconds\n";
    EXPECT_TRUE(true);
}

TEST(GaussTest, Gauss)
{
    std::ifstream infile("source.bmp", std::ios::in | std::ios::binary);
    Bmp bmp;
    infile.read(reinterpret_cast<char*>(&bmp), 54);
    auto start = std::chrono::high_resolution_clock::now();
    apply_gaussian_blur(5,1.0f);
    auto end = std::chrono::high_resolution_clock::now();
    auto oldstart = std::chrono::high_resolution_clock::now();
    old_apply_gaussian_blur(5,1.0f);
    auto oldend = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::chrono::duration<double> oldduration = oldend - oldstart;
    std::cout << "Time: " << duration.count()<<oldduration.count() << " seconds\n";
    EXPECT_TRUE(true);
}
