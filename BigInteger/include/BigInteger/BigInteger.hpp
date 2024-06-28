#ifndef BIGINTEGER_HPP_
#define BIGINTEGER_HPP_

#include <string>
#include <vector>

/*
████████╗██╗  ██╗███████╗
╚══██╔══╝██║  ██║██╔════╝
   ██║   ███████║█████╗
   ██║   ██╔══██║██╔══╝
   ██║   ██║  ██║███████╗
   ╚═╝   ╚═╝  ╚═╝╚══════╝
██████╗ ██╗ ██████╗  ██████╗ ███████╗███████╗████████╗
██╔══██╗██║██╔════╝ ██╔════╝ ██╔════╝██╔════╝╚══██╔══╝
██████╔╝██║██║  ███╗██║  ███╗█████╗  ███████╗   ██║
██╔══██╗██║██║   ██║██║   ██║██╔══╝  ╚════██║   ██║
██████╔╝██║╚██████╔╝╚██████╔╝███████╗███████║   ██║
╚═════╝ ╚═╝ ╚═════╝  ╚═════╝ ╚══════╝╚══════╝   ╚═╝
██╗███╗   ██╗████████╗    ██╗███╗   ██╗    ████████╗██╗  ██╗███████╗
██║████╗  ██║╚══██╔══╝    ██║████╗  ██║    ╚══██╔══╝██║  ██║██╔════╝
██║██╔██╗ ██║   ██║       ██║██╔██╗ ██║       ██║   ███████║█████╗
██║██║╚██╗██║   ██║       ██║██║╚██╗██║       ██║   ██╔══██║██╔══╝
██║██║ ╚████║   ██║       ██║██║ ╚████║       ██║   ██║  ██║███████╗
╚═╝╚═╝  ╚═══╝   ╚═╝       ╚═╝╚═╝  ╚═══╝       ╚═╝   ╚═╝  ╚═╝╚══════╝
██╗    ██╗██╗██╗     ██████╗     ██╗    ██╗███████╗███████╗████████╗
██║    ██║██║██║     ██╔══██╗    ██║    ██║██╔════╝██╔════╝╚══██╔══╝
██║ █╗ ██║██║██║     ██║  ██║    ██║ █╗ ██║█████╗  ███████╗   ██║
██║███╗██║██║██║     ██║  ██║    ██║███╗██║██╔══╝  ╚════██║   ██║
╚███╔███╔╝██║███████╗██████╔╝    ╚███╔███╔╝███████╗███████║   ██║
 ╚══╝╚══╝ ╚═╝╚══════╝╚═════╝      ╚══╝╚══╝ ╚══════╝╚══════╝   ╚═╝
 */

class BigInt {
 private:
  explicit BigInt(size_t size, int num);
  static std::string GetIntAsStringWithLeadingZeros(int x);
  void RemoveLeadingZeros();
  static int ConvertStringToDigit(const std::string& str, size_t start_pos,
                                  size_t end_pos);
  void AddWithSameSign(const BigInt& b);
  void AddWithDifferentSign(const BigInt& b);
  void AdjustSignIfZero();
  static BigInt KaratsubaMultiply(const BigInt& a, const BigInt& b);
  static BigInt SimpleMultiply(const BigInt& a, const BigInt& b);

 public:
  static const int kNumberSystemBase = 10;
  static const int kMaxDigitsInElement = 1;

  /*should be explicit, but delete this for tests*/
  BigInt(int64_t number = 0);
  explicit BigInt(const std::string& str);
  BigInt(const BigInt& copy) = default;
  BigInt& operator=(BigInt other) &;

  std::string ToString() const;
  size_t CountDigits() const;
  bool IsNegative() const;
  const int& GetDigit(size_t index) const;
  void Swap(BigInt& other);
  bool IsLessAbsolute(const BigInt& b) const;
  BigInt Abs() const;
  BigInt& operator+=(const BigInt& b);
  BigInt& operator-=(const BigInt& b);
  BigInt& operator*=(const BigInt& b);
  BigInt& operator/=(const BigInt& divisor);
  BigInt& operator%=(const BigInt& divisor);
  BigInt operator-() const;
  BigInt& operator++();
  BigInt operator++(int);
  BigInt& operator--();
  BigInt operator--(int);

 private:
  std::vector<int> digits_;
  bool is_negative_;
};

bool operator==(const BigInt& a, const BigInt& b);
bool operator!=(const BigInt& a, const BigInt& b);
bool operator<(const BigInt& a, const BigInt& b);
bool operator>(const BigInt& a, const BigInt& b);
bool operator<=(const BigInt& a, const BigInt& b);
bool operator>=(const BigInt& a, const BigInt& b);
BigInt operator""_bi(const char* number, size_t);
BigInt operator+(const BigInt& a, const BigInt& b);
BigInt operator-(const BigInt& a, const BigInt& b);
BigInt operator*(const BigInt& a, const BigInt& b);
BigInt operator/(const BigInt& a, const BigInt& b);
BigInt operator%(const BigInt& a, const BigInt& b);
std::ostream& operator<<(std::ostream& out, const BigInt& number);
std::istream& operator>>(std::istream& in, BigInt& number);

#endif
