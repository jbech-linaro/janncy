#include "gtest/gtest.h"
#include "include/Ciphertext.hpp"

using namespace std::complex_literals;

double epsilon = 10e-5;

TEST(Ciphertext, Add) {
  auto ct0 = janncy::encrypt(std::vector(8, std::complex<double>(1)));
  auto ct1 = janncy::encrypt(std::vector(8, std::complex<double>(1)));
  auto result = (ct0 + ct1).decrypt();
  EXPECT_LT(std::abs(result[0].real() - 2), epsilon);
}

TEST(Ciphertext, Multiply) {
  auto ct0 = janncy::encrypt(std::vector(8, std::complex<double>(2)));
  auto ct1 = janncy::encrypt(std::vector(8, std::complex<double>(2)));
  auto result = (ct0 * ct1).decrypt();
  EXPECT_LT(std::abs(result[0].real() - 4), epsilon);
}

TEST(Ciphertext, PlaintextMultiply) {
  auto ct0 = janncy::encrypt(std::vector(8, std::complex<double>(2)));
  auto pt_vec = std::vector(8, std::complex<double>(3));
  auto result = (ct0.multPtVec(pt_vec)).decrypt();
  EXPECT_LT(std::abs(result[0].real() - 6), epsilon);
}

TEST(Ciphertext, PlaintextAdd) {
  auto ct0 = janncy::encrypt(std::vector(8, std::complex<double>(5)));
  auto pt_vec = std::vector(8, std::complex<double>(8));
  auto result = (ct0.addPtVec(pt_vec)).decrypt();
  EXPECT_LT(std::abs(result[0].real() - 13), epsilon);
}

TEST(Ciphertext, Subtract) {
  auto ct0 = janncy::encrypt(std::vector(8, std::complex<double>(1)));
  auto ct1 = janncy::encrypt(std::vector(8, std::complex<double>(2)));
  auto result = (ct0 - ct1).decrypt();
  EXPECT_LT(std::abs(result[0].real() - (-1)), epsilon);
}
