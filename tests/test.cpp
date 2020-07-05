#include <gtest/gtest.h>
#include "PINBruteForce.hpp"

TEST(BruteForceTest, PIN00000000) {
    const MD5Utils::MD5Array md{std::string{"dd4b21e9ef71e1291183a46b913ae6f2"}, MD5Utils::MD5Array::COMPRESS};
    const std::array<unsigned char, 8> truePin = {'0', '0', '0', '0', '0', '0', '0', '0'},
                                       pin     = MD5Utils::PINBruteForcer<8>::force(md);
    ASSERT_TRUE(truePin == pin);
}

TEST(BruteForceTest, PIN99999999) {
    const MD5Utils::MD5Array md{std::string{"ef775988943825d2871e1cfa75473ec0"}, MD5Utils::MD5Array::COMPRESS};
    const std::array<unsigned char, 8> truePin = {'9', '9', '9', '9', '9', '9', '9', '9'},
                                       pin     = MD5Utils::PINBruteForcer<8>::force(md);
    ASSERT_TRUE(truePin == pin);
}

TEST(BruteForceTest, PIN12345678) {
    const MD5Utils::MD5Array md{std::string{"25d55ad283aa400af464c76d713c07ad"}, MD5Utils::MD5Array::COMPRESS};
    const std::array<unsigned char, 8> truePin = {'1', '2', '3', '4', '5', '6', '7', '8'},
                                       pin     = MD5Utils::PINBruteForcer<8>::force(md);
    ASSERT_TRUE(truePin == pin);
}

TEST(BruteForceTest, PIN87654321) {
    const MD5Utils::MD5Array md{std::string{"5e8667a439c68f5145dd2fcbecf02209"}, MD5Utils::MD5Array::COMPRESS};
    const std::array<unsigned char, 8> truePin = {'8', '7', '6', '5', '4', '3', '2', '1'},
                                       pin     = MD5Utils::PINBruteForcer<8>::force(md);
    ASSERT_TRUE(truePin == pin);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}