#include "String.hpp"

String::String(size_t size)
    : size_(size), capacity_(size_), data_(new char[capacity_]) {
}

String::String() : size_(0), capacity_(size_), data_(nullptr) {
}

String::String(size_t size, char character) : String(size) {
  std::fill(data_, data_ + size_, character);
}

size_t String::Size() const {
  return size_;
}

const char& String::operator[](size_t index) const {
  return data_[index];
}

String::~String() {
  delete[] data_;
}

char& String::operator[](size_t index) {
  return data_[index];
}

String::String(const char* str) : String(strlen(str)) {
  std::copy(str, str + size_, data_);
}

String::String(const String& other) : String(other.size_) {
  std::copy(other.data_, other.data_ + other.size_, data_);
}

void String::Swap(String& other) noexcept {
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
  std::swap(data_, other.data_);
}

String& String::operator=(String other) & {
  Swap(other);
  return *this;
}

void String::Clear() {
  size_ = 0;
}

void String::PushBack(char character) {
  if (size_ == capacity_) {
    Reserve(size_ == 0 ? 1 : 2 * capacity_);
  }
  ++size_;
  data_[size_ - 1] = character;
}

void String::Reserve(size_t new_capacity) {
  if (new_capacity <= capacity_) {
    return;
  }

  char* new_data = new char[new_capacity];
  std::copy(data_, data_ + size_, new_data);
  delete[] data_;

  data_ = new_data;
  capacity_ = new_capacity;
}

bool String::Empty() const {
  return size_ == 0;
}

const char* String::Data() const {
  return data_;
}

char* String::Data() {
  return data_;
}

void String::PopBack() {
  if (size_ == 0) {
    return;
  }
  --size_;
}

void String::Resize(size_t new_size) {
  if (new_size >= capacity_) {
    Reserve(new_size);
  }
  size_ = new_size;
}

void String::Resize(size_t new_size, char character) {
  size_t previous_size = Size();
  Resize(new_size);
  if (new_size > previous_size) {
    std::fill(data_ + previous_size, data_ + new_size, character);
  }
}

void String::ShrinkToFit() {
  if (capacity_ > size_) {
    char* new_data = new char[size_];
    std::copy(data_, data_ + size_, new_data);
    delete[] data_;

    data_ = new_data;
    capacity_ = size_;
  }
}

size_t String::Capacity() const {
  return capacity_;
}

const char& String::Front() const {
  return *data_;
}

char& String::Front() {
  return *data_;
}

const char& String::Back() const {
  return data_[size_ - 1];
}

char& String::Back() {
  return data_[size_ - 1];
}

String& String::operator+=(const String& other) {
  if (size_ + other.size_ > capacity_) {
    Reserve(2 * (size_ + other.size_));
  }
  std::copy(other.data_, other.data_ + other.size_, data_ + size_);
  size_ += other.size_;
  return *this;
}

String& String::operator*=(size_t n) {
  if (size_ * n > capacity_) {
    Reserve(2 * n * size_);
  }
  for (size_t i = 0; i < n; ++i) {
    std::copy(data_, data_ + size_, data_ + size_ * i);
  }
  size_ *= n;
  return *this;
}

std::vector<String> String::Split(const String& delimiter) const {
  std::vector<String> result;
  size_t start_position = 0;
  size_t finish_position = 0;
  size_t delimiter_size = delimiter.Size();

  while ((finish_position = this->Find(delimiter, finish_position)) !=
         String::kNpos) {
    result.push_back(
        this->Substring(start_position, finish_position - start_position));
    start_position = finish_position + delimiter_size;
    finish_position += delimiter_size;
  }

  result.push_back(this->Substring(start_position, size_ - start_position));
  return result;
}

size_t String::Find(const String& substring, size_t start_position) const {
  if (size_ == 0) {
    return String::kNpos;
  }
  size_t count_equals_characters;

  for (size_t i = start_position; i < size_; ++i) {
    count_equals_characters = 0;
    while (count_equals_characters < substring.size_ &&
           (i + count_equals_characters) < size_ &&
           data_[i + count_equals_characters] ==
               substring[count_equals_characters]) {
      count_equals_characters++;
    }
    if (count_equals_characters == substring.Size()) {
      return i;
    }
  }
  return String::kNpos;
}

String String::Substring(size_t start_position, size_t count_characters) const {
  if (count_characters + start_position > size_) {
    count_characters = size_ - start_position;
  }
  String result(count_characters);
  std::copy(data_ + start_position, data_ + start_position + count_characters,
            result.data_);
  return result;
}

String String::Join(const std::vector<String>& strings) const {
  if (strings.empty()) {
    return String("");
  }

  String result;
  size_t full_length = 0;
  for (const auto& string : strings) {
    full_length += string.Size();
  }
  result.Reserve(full_length + this->Size() * (strings.size() - 1));
  String delimiter = *this;
  for (size_t i = 0; i < strings.size(); ++i) {
    if (i > 0) {
      result += delimiter;
    }
    result += strings[i];
  }
  return result;
}

bool operator<(const String& str1, const String& str2) {
  size_t str1_size = str1.Size();
  size_t str2_size = str2.Size();

  if (str1_size < str2_size) {
    return true;
  }
  if (str1_size > str2_size) {
    return false;
  }

  for (size_t i = 0; i < str1_size; ++i) {
    if (str1[i] < str2[i]) {
      return true;
    }
    if (str1[i] > str2[i]) {
      return false;
    }
  }
  return false;
}

bool operator>(const String& str1, const String& str2) {
  return str2 < str1;
}

bool operator<=(const String& str1, const String& str2) {
  return !(str1 > str2);
}

bool operator>=(const String& str1, const String& str2) {
  return !(str1 < str2);
}

bool operator==(const String& str1, const String& str2) {
  size_t str1_size = str1.Size();
  size_t str2_size = str2.Size();

  if (str1_size != str2_size) {
    return false;
  }

  for (size_t i = 0; i < str1_size; ++i) {
    if (str1[i] != str2[i]) {
      return false;
    }
  }
  return true;
}

bool operator!=(const String& str1, const String& str2) {
  return !(str1 == str2);
}

std::istream& operator>>(std::istream& in, String& string) {
  string.Clear();
  char symbol;
  while ((in.get(symbol))) {
    if (symbol == '\n') {
      break;
    }
    string.PushBack(symbol);
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const String& string) {
  size_t size = string.Size();

  for (size_t i = 0; i < size; ++i) {
    out << string[i];
  }
  return out;
}

String operator+(const String& str1, const String& str2) {
  String result = str1;
  result += str2;
  return result;
}

String operator*(const String& str1, size_t n) {
  String result = str1;
  result *= n;
  return result;
}

String operator""_s(const char* str, size_t /*unused*/) {
  return String(str);
}
