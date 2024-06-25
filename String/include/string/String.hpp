#ifndef STRING_STRING_HPP_
#define STRING_STRING_HPP_
#include <cstring>
#include <iostream>
#include <limits>
#include <vector>

//----------------------------------------------------------------------------------------------------------------------
/*
██████╗  █████╗ ███████╗███████╗
██╔══██╗██╔══██╗██╔════╝██╔════╝
██████╔╝███████║███████╗█████╗
██╔══██╗██╔══██║╚════██║██╔══╝
██████╔╝██║  ██║███████║███████╗
╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝
*/
//----------------------------------------------------------------------------------------------------------------------

class String;

String operator""_s(const char* str, size_t);

class String {
 private:
  explicit String(size_t size);

 public:
  static const size_t kNpos = std::numeric_limits<size_t>::max();

  String();
  String(size_t size, char character);
  explicit String(const char* str);
  String(const String& other);
  String& operator=(String other) &;
  ~String();

  size_t Size() const;
  size_t Capacity() const;

  char* Data();
  const char* Data() const;
  char& Front();
  const char& Front() const;
  char& Back();
  const char& Back() const;

  const char& operator[](size_t index) const;
  char& operator[](size_t index);

  void Swap(String& other) noexcept;

  bool Empty() const;

  void PushBack(char character);
  void PopBack();

  void Reserve(size_t new_capacity);

  void Resize(size_t new_size);
  void Resize(size_t new_size, char character);

  void ShrinkToFit();

  void Clear();

  String& operator+=(const String& other);
  String& operator*=(size_t n);

  size_t Find(const String& substring, size_t start_position) const;
  String Substring(size_t start_position, size_t count_characters) const;
  std::vector<String> Split(const String& delimiter = " "_s) const;
  String Join(const std::vector<String>& strings) const;

 private:
  size_t size_;
  size_t capacity_;
  char* data_;
};

bool operator<(const String& str1, const String& str2);
bool operator>(const String& str1, const String& str2);
bool operator<=(const String& str1, const String& str2);
bool operator>=(const String& str1, const String& str2);
bool operator==(const String& str1, const String& str2);
bool operator!=(const String& str1, const String& str2);

String operator+(const String& str1, const String& str2);
String operator*(const String& str1, size_t n);

std::ostream& operator<<(std::ostream& out, const String& string);
std::istream& operator>>(std::istream& in, String& string);

#endif
