#include "BigInteger.hpp"

#include <iomanip>
#include <sstream>

BigInt::BigInt(int64_t number) : is_negative_(number < 0) {
  if (number == 0) {
    digits_.push_back(0);
  }
  number = std::abs(number);
  while (number > 0) {
    digits_.push_back(number % kNumberSystemBase);
    number /= kNumberSystemBase;
  }
}

BigInt::BigInt(const std::string& str) : is_negative_(str[0] == '-') {
  ssize_t digit_end = str.size() - 1;
  ssize_t digit_start = digit_end - kMaxDigitsInElement + 1;
  ssize_t finish_pos = is_negative_ ? 1 : 0;
  while (digit_start >= finish_pos) {
    digits_.push_back(ConvertStringToDigit(str, digit_start, digit_end));
    digit_end = digit_start - 1;
    digit_start = digit_end - kMaxDigitsInElement + 1;
  }

  if (digit_end >= finish_pos) {
    digits_.push_back(ConvertStringToDigit(str, finish_pos, digit_end));
  }

  if (str == "-0") {
    is_negative_ = false;
  }
}

std::string BigInt::ToString() const {
  std::string number;
  number.reserve(kMaxDigitsInElement * digits_.size());
  if (is_negative_) {
    number += '-';
  }
  number += std::to_string(digits_.back());
  for (ssize_t i = digits_.size() - 2; i >= 0; --i) {
    number += GetIntAsStringWithLeadingZeros(digits_[i]);
  }
  return number;
}

std::string BigInt::GetIntAsStringWithLeadingZeros(int x) {
  std::ostringstream result;
  result << std::setfill('0') << std::setw(kMaxDigitsInElement) << x;
  return result.str();
}

int BigInt::ConvertStringToDigit(const std::string& str, size_t start_pos,
                                 size_t end_pos) {
  const int kBase = 10;
  int result = 0;
  for (size_t i = start_pos; i <= end_pos; ++i) {
    result = result * kBase + (str[i] - '0');
  }
  return result;
}

size_t BigInt::CountDigits() const {
  return digits_.size();
}

bool BigInt::IsNegative() const {
  return is_negative_;
}

const int& BigInt::GetDigit(size_t index) const {
  return digits_[index];
}

std::ostream& operator<<(std::ostream& out, const BigInt& number) {
  out << number.ToString();
  return out;
}

bool operator==(const BigInt& a, const BigInt& b) {
  size_t a_size = a.CountDigits();
  size_t b_size = b.CountDigits();

  if (a_size != b_size || a.IsNegative() != b.IsNegative()) {
    return false;
  }

  for (size_t i = 0; i < a_size; ++i) {
    if (a.GetDigit(i) != b.GetDigit(i)) {
      return false;
    }
  }
  return true;
}

bool operator!=(const BigInt& a, const BigInt& b) {
  return !(a == b);
}

bool operator<(const BigInt& a, const BigInt& b) {
  if (a.IsNegative() && !b.IsNegative()) {
    return true;
  }
  if (!a.IsNegative() && b.IsNegative()) {
    return false;
  }

  bool common_sign_is_negative = a.IsNegative();

  size_t a_count_digits = a.CountDigits();
  size_t b_count_digits = b.CountDigits();

  if (a_count_digits != b_count_digits) {
    return common_sign_is_negative ? (a_count_digits > b_count_digits)
                                   : (a_count_digits < b_count_digits);
  }

  size_t common_size = a_count_digits;
  for (size_t i = 0; i < common_size; ++i) {
    if (a.GetDigit(i) < b.GetDigit(i)) {
      return (!common_sign_is_negative);
    }
    if (a.GetDigit(i) > b.GetDigit(i)) {
      return (common_sign_is_negative);
    }
  }

  return false;
}

bool operator>(const BigInt& a, const BigInt& b) {
  return b < a;
}

bool operator<=(const BigInt& a, const BigInt& b) {
  return !(a > b);
}

bool operator>=(const BigInt& a, const BigInt& b) {
  return !(a < b);
}

BigInt operator""_bi(const char* number, size_t /*unused*/) {
  return BigInt(std::string(number));
}
