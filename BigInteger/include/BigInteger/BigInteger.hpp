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
  static std::string GetIntAsStringWithLeadingZeros(int x);
  static int ConvertStringToDigit(const std::string& str, size_t start_pos,
                                  size_t end_pos);

 public:
  static const int kNumberSystemBase = 10;
  static const int kMaxDigitsInElement = 1;

  BigInt(int64_t number = 0);
  BigInt(const std::string& str);

  std::string ToString() const;
  size_t CountDigits() const;
  bool IsNegative() const;
  const int& GetDigit(size_t index) const;

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
std::ostream& operator<<(std::ostream& out, const BigInt& number);

#endif
