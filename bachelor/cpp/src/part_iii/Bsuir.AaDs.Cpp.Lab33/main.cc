// Lab 3: String as class.

#include <algorithm>
#include <iostream> 
#include <string.h> 

class String {
  friend std::ostream& operator << (std::ostream& stream, const String& string);

  friend void swap(String &l, String& r) noexcept;

 public:
  explicit String(const char *s = "") {
    content_ = new char[strlen(s) + 1];
    strcpy(content_, s);
  }

  String(const String& ob) : String(ob.content_) {
  }

  inline String& operator = (String) noexcept;

  ~String() {
    delete[] content_;
    content_ = nullptr;
  }

  String operator + (const String&) const;
  String& operator += (const String&);

  bool operator <= (const String& ob) const noexcept;
  bool operator >= (const String& ob) const noexcept;

  const char operator [] (const size_t i) const noexcept {
    return content_[i];
  }

 private:
  char *content_;
};

String String::operator + (const String& ob) const {
  String obj;
  obj.content_ = new char[strlen(content_) + strlen(ob.content_) + 1];
  strcpy(obj.content_, content_);
  strcat(obj.content_, ob.content_);
  return obj;
}

String& String::operator += (const String& ob) {
  *this = *this + ob;
  return *this;
}

String& String::operator = (String ob) noexcept {
  swap(*this, ob);
  return *this;
}

bool String::operator <= (const String& ob) const noexcept {
  return strlen(ob.content_) <= strlen(content_);
}

bool String::operator >= (const String& ob) const noexcept {
  return strlen(ob.content_) >= strlen(content_);
}

std::ostream& operator <<(std::ostream& stream, const String& string) {
  return stream << string.content_;
}

inline void swap(String& l, String& r) noexcept {
  std::swap(l.content_, r.content_);
}

int main() {
  constexpr char first_line[40]{"Line 1; "};
  constexpr char second_line[40]{"Line 2; "};

  String story{first_line};
  std::cout << "First line: " << story << std::endl;

  String story2{second_line};
  std::cout << "Second line: " << story2 << std::endl;

  String story3{story2 + story};
  std::cout << "Second line + First line: " << story3 << std::endl;

  String story4;
  story4 = story3;
  std::cout << "Third line = Second line + First line: " << story4 << std::endl;

  String story5;
  story5 += story3;

  std::cout << std::endl;

  if (story <= story2) {
    std::cout << story << " <= " << story2 << std::endl;
  } else {
    std::cout << story << " > " << story2 << std::endl;
  }

  if (story5 >= story3) {
    std::cout << story5 << " >= " << story3 << std::endl;
  } else {
    std::cout << story5 << " < " << story3 << std::endl;
  }

  std::cout << std::endl;

  String story6{first_line};
  std::cout << "Character at zero-based index " << 5 << " of \"" << story6
    << "\" is '" << story6[5] << "'" << std::endl;

  return 0;
}
