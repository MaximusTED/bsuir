// Copyright (c) 2017, reginell. All rights reserved.
// Use of this source code is governed by a BSD license that can be
// found in the LICENSE file.

#include <cstdlib>  // EXIT_SUCCESS
#include <iomanip>
#include <iostream>
#include <memory>  // std::unique_ptr
#include <string>  // std::string
#include <tuple>   // std::tuple, std::tie

struct IStreamable {
  virtual std::ostream& writeTo(std::ostream& stream) const = 0;
  virtual std::istream& readFrom(std::istream& stream) = 0;
};

class Computer : IStreamable {
  friend std::ostream& operator<<(std::ostream& stream, const Computer& c);
  friend std::istream& operator>>(std::istream& stream, Computer& c);

 public:
  Computer(const std::string& model, const std::string& type)
      : model_{model}, type_{type} {}
  virtual ~Computer() { std::cout << "Is Computer: true" << std::endl; }

  std::ostream& writeTo(std::ostream& stream) const override {
    return stream << "Model: " << model_ << std::endl
                  << "Type: " << type_ << std::endl;
  }

  std::istream& readFrom(std::istream& stream) override {
    std::cout << "Model: ";
    return std::getline(stream, model_, '\n');
  }

 private:
  std::string model_;
  std::string type_;

  Computer(Computer& c) = delete;
  Computer& operator=(const Computer& c) = delete;
};

std::ostream& operator<<(std::ostream& stream, const Computer& c) {
  return c.writeTo(stream);
}

std::istream& operator>>(std::istream& stream, Computer& c) {
  return c.readFrom(stream);
}

class Desktop : public Computer {
 public:
  Desktop(const std::string& model, const std::string& type,
          const bool is_upgradeable)
      : Computer{model, type}, is_upgradeable_{is_upgradeable} {}

  std::ostream& writeTo(std::ostream& stream) const override {
    return Computer::writeTo(stream)
           << "Is Upgradeable: " << is_upgradeable_ << std::endl;
  }

  virtual ~Desktop() { std::cout << "Is Desktop: true" << std::endl; }

 private:
  const bool is_upgradeable_;
};

class Monoblock : public Desktop {
 public:
  Monoblock(const std::string& model = "MB", const bool is_compact = false)
      : Desktop{model, "Monoblock", false}, is_compact_{is_compact} {}

  std::ostream& writeTo(std::ostream& stream) const override {
    return Desktop::writeTo(stream)
           << "Is Compact: " << is_compact_ << std::endl;
  }

  std::istream& readFrom(std::istream& stream) override {
    Desktop::readFrom(stream);

    std::cout << "Is Compact: ";
    stream >> is_compact_;

    return stream;
  }

  virtual ~Monoblock() { std::cout << "Is Monoblock: true" << std::endl; }

 private:
  bool is_compact_;
};

class Portable : public Computer {
 public:
  Portable(const std::string& model, const std::string& type,
           const bool has_touchpad)
      : Computer{model, type}, has_touchpad_{has_touchpad} {}

  std::ostream& writeTo(std::ostream& stream) const override {
    return Computer::writeTo(stream)
           << "Has Touchpad: " << has_touchpad_ << std::endl;
  }

  virtual ~Portable() { std::cout << "Is Portable: true" << std::endl; }

 private:
  const bool has_touchpad_;
};

class Notebook : public Portable {
 public:
  Notebook(const std::string& model = "NB",
           const std::string& battery_type = "Li-ion")
      : Portable{model, "Notebook", true}, battery_type_{battery_type} {}

  std::ostream& writeTo(std::ostream& stream) const override {
    return Portable::writeTo(stream)
           << "Battery Type: " << battery_type_ << std::endl;
  }

  std::istream& readFrom(std::istream& stream) override {
    Portable::readFrom(stream);

    std::cout << "Battery Type: ";
    std::getline(stream, battery_type_, '\n');

    return stream;
  }

  virtual ~Notebook() { std::cout << "Is Notebook: true" << std::endl; }

 private:
  std::string battery_type_;
};

enum class ComputerType { kUnknown, kMonoblock, kNotebook };

std::istream& operator>>(std::istream& stream, ComputerType& computer_type) {
  std::cout << "Enter your computer info (1 - Monoblock, 2 - Notebook): ";

  int computer_type_as_int;
  if (!(stream >> computer_type_as_int)) {
    return stream;
  }

  if (computer_type_as_int == 1) {
    computer_type = ComputerType::kMonoblock;
  } else if (computer_type_as_int == 2) {
    computer_type = ComputerType::kNotebook;
  } else {
    computer_type = ComputerType::kUnknown;
  }

  return stream.ignore();  // Skip enter.
}

std::tuple<std::unique_ptr<Computer>, int> make_computer(
    ComputerType computer_type) {
  switch (computer_type) {
    case ComputerType::kMonoblock:
      std::cout << "Selected Monoblock." << std::endl;
      return std::make_tuple(std::make_unique<Monoblock>(), EXIT_SUCCESS);

    case ComputerType::kNotebook:
      std::cout << "Selected Notebook." << std::endl;
      return std::make_tuple(std::make_unique<Notebook>(), EXIT_SUCCESS);

    default:
      std::cerr << "Incorrect computer type. "
                << "Either Monoblock or Notebook are supported." << std::endl;
      return std::make_tuple(nullptr, EINVAL);
  }
}

std::tuple<std::unique_ptr<Computer>, int> create_computer() {
  ComputerType computer_type;
  std::cin >> computer_type;

  auto computer = make_computer(computer_type);
  if (std::get<1>(computer) == EXIT_SUCCESS &&
      !(std::cin >> *std::get<0>(computer))) {
    std::get<1>(computer) = EXIT_FAILURE;
  }

  return computer;
}

int main() {
  std::unique_ptr<Computer> computer;
  int result_code;

  std::tie(computer, result_code) = create_computer();
  if (result_code != EXIT_SUCCESS) return result_code;

  // Print True / False instead of 1 / 0 for bool.
  std::cout.setf(std::ios::boolalpha);
  std::cout << std::endl
            << "Your computer info: " << std::endl
            << *computer << std::endl;

  return result_code;
}