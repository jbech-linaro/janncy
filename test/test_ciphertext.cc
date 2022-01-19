#include <algorithm>
#include <complex>
#include <vector>

#include "gtest/gtest.h"
#include "include/ciphertext.h"

using namespace std::complex_literals;

namespace {

double epsilon = 10e-5;

void TestCloseEnough(std::vector<std::complex<double>> v0,
                     std::vector<std::complex<double>> v1) {
  std::vector<std::complex<double>> diff;
  std::transform(v0.begin(), v0.end(), v1.begin(), std::back_inserter(diff),
                 std::minus<std::complex<double>>());

  for (auto val : diff) {
    EXPECT_LT(std::norm(val), epsilon);
  }
}

}  // namespace

TEST(Ciphertext, Add) {
  auto in0 = std::vector<std::complex<double>>{0, 1, 2, 3, 4, 5, 6, 7};
  auto in1 = in0;
  auto ct0 = janncy::Encrypt(in0);
  auto ct1 = janncy::Encrypt(in1);
  auto result = (ct0 + ct1).Decrypt();
  std::vector<std::complex<double>> expected;
  std::transform(in0.begin(), in0.end(), in1.begin(),
                 std::back_inserter(expected),
                 std::plus<std::complex<double>>());
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, Multiply) {
  auto in0 = std::vector<std::complex<double>>{0, 1, 2, 3, 4, 5, 6, 7};
  auto in1 = in0;
  auto ct0 = janncy::Encrypt(in0);
  auto ct1 = janncy::Encrypt(in1);
  auto result = (ct0 * ct1).Decrypt();
  std::vector<std::complex<double>> expected;
  std::transform(in0.begin(), in0.end(), in1.begin(),
                 std::back_inserter(expected),
                 std::multiplies<std::complex<double>>());
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, PlaintextMultiply) {
  auto in0 = std::vector<std::complex<double>>{0, 1, 2, 3, 4, 5, 6, 7};
  auto in1 = in0;
  auto ct0 = janncy::Encrypt(in0);
  auto pt_vec = in1;
  auto result = (ct0.MultPtVec(pt_vec)).Decrypt();
  std::vector<std::complex<double>> expected;
  std::transform(in0.begin(), in0.end(), in1.begin(),
                 std::back_inserter(expected),
                 std::multiplies<std::complex<double>>());
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, PlaintextAdd) {
  auto in0 = std::vector<std::complex<double>>{0, 1, 2, 3, 4, 5, 6, 7};
  auto in1 = in0;
  auto ct0 = janncy::Encrypt(in0);
  auto pt_vec = in1;
  std::vector<std::complex<double>> expected;
  std::transform(in0.begin(), in0.end(), in1.begin(),
                 std::back_inserter(expected),
                 std::plus<std::complex<double>>());
  auto result = (ct0.AddPtVec(pt_vec)).Decrypt();
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, Subtract) {
  auto in0 = std::vector<std::complex<double>>{0, 1, 2, 3, 4, 5, 6, 7};
  auto in1 = in0;
  auto ct0 = janncy::Encrypt(in0);
  auto ct1 = janncy::Encrypt(in1);
  auto result = (ct0 - ct1).Decrypt();
  std::vector<std::complex<double>> expected;
  std::transform(in0.begin(), in0.end(), in1.begin(),
                 std::back_inserter(expected),
                 std::minus<std::complex<double>>());
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, Rotate) {
  auto in0 = std::vector<std::complex<double>>{0, 1, 2, 3, 4, 5, 6, 7};
  auto ct = janncy::Encrypt(in0);
  auto rotate_amount = 2;
  auto result = ct.Rotate(rotate_amount).Decrypt();
  auto expected = in0;
  std::rotate(expected.begin(), expected.begin() + rotate_amount,
              expected.end());
  TestCloseEnough(result, expected);
}

TEST(Ciphertext, Bootstrap) {
  auto in0 = std::vector<std::complex<double>>{0, 1, 2, 3, 4, 5, 6, 7};
  auto ct = janncy::Encrypt(in0);
  auto result = ct.Bootstrap().Decrypt();
  TestCloseEnough(result, in0);
}
