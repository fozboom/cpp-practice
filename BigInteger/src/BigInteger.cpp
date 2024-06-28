#include "BigInteger.hpp"

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <sstream>

BigInt::BigInt(int64_t number) : is_negative_(number < 0) {
  if (number == 0) {
    digits_.push_back(0);
    return;
  }
  // if not unsigned,here will be an overflow when
  // std::numeric_limits<int64_t>::min()
  uint64_t result = std::abs(number);
  while (result > 0) {
    digits_.push_back(result % BigInt::kNumberSystemBase);
    result /= kNumberSystemBase;
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

void BigInt::Swap(BigInt& other) {
  std::swap(is_negative_, other.is_negative_);
  std::swap(digits_, other.digits_);
}

BigInt& BigInt::operator=(BigInt other) & {
  Swap(other);
  return *this;
}

BigInt& BigInt::operator+=(const BigInt& b) {
  digits_.reserve(std::max(digits_.size(), b.digits_.size()) + 1);
  if (is_negative_ == b.is_negative_) {
    AddWithSameSign(b);
  } else {
    AddWithDifferentSign(b);
    AdjustSignIfZero();
  }
  RemoveLeadingZeros();
  return *this;
}

void BigInt::AddWithDifferentSign(const BigInt& b) {
  int carry = 0;
  BigInt copy = b;
  if (IsLessAbsolute(*this, b)) {
    Swap(copy);
  }
  size_t a_count_digits = digits_.size();
  size_t b_count_digits = copy.digits_.size();
  for (size_t i = 0; i < std::max(a_count_digits, b_count_digits); ++i) {
    long long current_digit =
        digits_[i] - (i < b_count_digits ? copy.digits_[i] : 0) - carry;
    digits_[i] = current_digit;
    if (current_digit < 0) {
      digits_[i] += BigInt::kNumberSystemBase;
    }
    carry = current_digit < 0 ? 1 : 0;
  }
}

void BigInt::AddWithSameSign(const BigInt& b) {
  int carry = 0;
  for (size_t i = 0; i < std::max(digits_.size(), b.digits_.size()); ++i) {
    int result = (i < digits_.size() ? digits_[i] : 0) +
                 (i < b.digits_.size() ? b.digits_[i] : 0) + carry;
    digits_[i] = result % kNumberSystemBase;
    carry = result / kNumberSystemBase;
  }
  if (carry != 0) {
    digits_.push_back(carry);
  }
}

bool BigInt::IsLessAbsolute(const BigInt& a, const BigInt& b) {
  size_t a_count_digits = a.CountDigits();
  size_t b_count_digits = b.CountDigits();

  if (a_count_digits < b_count_digits) {
    return true;
  }
  if (a_count_digits > b_count_digits) {
    return false;
  }

  size_t common_count_digits = a_count_digits;
  for (ssize_t i = common_count_digits - 1; i >= 0; --i) {
    if (a.digits_[i] < b.digits_[i]) {
      return true;
    }
    if (a.digits_[i] > b.digits_[i]) {
      return false;
    }
  }
  return false;
}

void BigInt::RemoveLeadingZeros() {
  while (digits_.size() > 1 && digits_.back() == 0) {
    digits_.pop_back();
  }
}
BigInt& BigInt::operator-=(const BigInt& b) {
  if (!this->IsNegative() && !b.IsNegative() && *this > b) {
    BigInt b_copy = b;
    b_copy.is_negative_ = true;
    *this += b_copy;
  } else {
    is_negative_ = !is_negative_;
    *this += b;
    is_negative_ = !is_negative_;
    AdjustSignIfZero();
  }
  return *this;
}

BigInt BigInt::KaratsubaMultiply(const BigInt& a, const BigInt& b) {
  return BigInt();
}

BigInt BigInt::SimpleMultiply(const BigInt& a, const BigInt& b) {
  size_t a_count_digits = a.CountDigits();
  size_t b_count_digits = b.CountDigits();
  BigInt result(a_count_digits + b_count_digits + 1, 0);
  result.is_negative_ = (a.IsNegative() != b.IsNegative());
  int carry;
  for (size_t i = 0; i < a_count_digits; ++i) {
    carry = 0;
    for (size_t j = 0; j < b_count_digits || (carry != 0); ++j) {
      long long current_digit =
          result.digits_[i + j] + carry +
          (j < b_count_digits ? a.digits_[i] * b.digits_[j] : 0);
      result.digits_[i + j] = current_digit % BigInt::kNumberSystemBase;
      carry = current_digit / BigInt::kNumberSystemBase;
    }
  }
  result.RemoveLeadingZeros();
  result.AdjustSignIfZero();
  return result;
}
void BigInt::AdjustSignIfZero() {
  if (digits_[0] == 0) {
    is_negative_ = false;
  }
}

BigInt::BigInt(size_t size, int num) : digits_(size, num), is_negative_(false) {
}
BigInt& BigInt::operator*=(const BigInt& b) {
  *this = SimpleMultiply(*this, b);
  return *this;
}
BigInt& BigInt::operator/=(const BigInt& divisor) {
  BigInt quotient(0);

  BigInt one(1);
  BigInt b_abs = divisor.Abs();
  BigInt remainder = this->Abs();

  while (remainder >= b_abs) {
    quotient += one;
    remainder -= b_abs;
  }
  quotient.is_negative_ = this->IsNegative() != divisor.IsNegative();

  AdjustSignIfZero();
  *this = quotient;
  return *this;
}

bool BigInt::IsGreaterOrEqualAbsolute(const BigInt& a, const BigInt& b) {
  return !(IsLessAbsolute(a, b));
}
BigInt BigInt::Abs() const {
  BigInt result = *this;
  result.is_negative_ = false;
  return result;
}

BigInt& BigInt::operator%=(const BigInt& divisor){
    return *this -= *this/divisor*divisor;
}
BigInt BigInt::operator-() const {
  BigInt result = *this;
  result.is_negative_ = !this->IsNegative();
  result.AdjustSignIfZero();
  return result;
}

BigInt& BigInt::operator++(){
  return (*this += 1);
}
BigInt BigInt::operator++(int) {
  BigInt copy = *this;
  ++(*this);
  return copy;
}

BigInt& BigInt::operator--(){
    return (*this -= 1);
}
BigInt BigInt::operator--(int) {
  BigInt copy = *this;
  --(*this);
  return copy;
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
  for (ssize_t i = common_size - 1; i >= 0; --i) {
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

BigInt operator+(const BigInt& a, const BigInt& b) {
  BigInt result = a;
  result += b;
  return result;
}

BigInt operator-(const BigInt& a, const BigInt& b) {
  BigInt copy = a;
  copy -= b;
  return copy;
}

BigInt operator*(const BigInt& a, const BigInt& b) {
  BigInt result = a;
  result *= b;
  return result;
}

BigInt operator/(const BigInt& a, const BigInt& b) {
  BigInt result = a;
  result /= b;
  return result;
}
BigInt operator%(const BigInt& a, const BigInt& b) {
  BigInt result = a;
  result %= b;
  return result;
}
std::istream& operator>>(std::istream& in, BigInt& number) {
  std::string s;
  in >> s;
  number = BigInt(s);
  return in;
}
