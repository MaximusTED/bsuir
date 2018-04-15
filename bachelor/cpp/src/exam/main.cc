// полиморфизм
// класс родитель(виртуальный метод) + класс наследник(override метода).

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Unit {
 public:
  Unit(std::string name, unsigned health) noexcept
    : name_{std::move(name)}, health_{health} {}

  virtual void reportState(std::ostream &out) const noexcept {
    out << name_ << " health: " << health_;
  }

  virtual void roarBattle(std::ostream &out) const noexcept {
    out << name_ << " attacks: ";
  }

 protected:
  const std::string name_;
  const unsigned health_;
};

class Civil : public Unit {
 public:
  Civil(std::string name, unsigned health) noexcept : Unit{name, health} {}

  void reportState(std::ostream &out) const noexcept override {
	Unit::reportState(out);
	out << "." << std::endl;
  }

  void roarBattle(std::ostream &out) const noexcept override {
    Unit::roarBattle(out);
    out << "AAAAAAA, excuse me!" << std::endl;
  }
};

class Soldier : public Unit {
 public:
  Soldier(std::string name, unsigned health, unsigned damage) noexcept
    : Unit{name, health}, damage_{damage} {}

  void reportState(std::ostream &out) const noexcept override {
	  Unit::reportState(out);
	  out << ", damage: " << damage_ << "." << std::endl;
  }

  void roarBattle(std::ostream &out) const noexcept override {
	Unit::roarBattle(out);
	out << "Don't move!" << std::endl;
  }

 private:
  const unsigned damage_;
};

int main() {
  std::vector<std::unique_ptr<Unit>> units;

  units.emplace_back(std::make_unique<Civil>(Civil{"Magnus", 20}));
  units.emplace_back(std::make_unique<Soldier>(Soldier{"Khan", 50, 40}));

  for (auto &unit : units) {
	unit->reportState(std::cout);
	unit->roarBattle(std::cout);
  }

  return 0;
}
