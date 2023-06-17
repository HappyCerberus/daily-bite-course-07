#include "rational.h"
#include <iostream>
#include <numeric>
#include <stdexcept>

namespace Numbers {
Rational::Rational(int64_t numerator, int64_t denominator)
    : numerator_(numerator), denominator_(denominator) {
  if (denominator == 0)
    throw std::domain_error("Denominator cannot be zero.");
  normalize();
}

Rational::Rational(int64_t integer) : numerator_(integer), denominator_(1) {}

const Rational &Rational::normalized() const { return *this; }

int64_t Rational::numerator() const { return numerator_; }

int64_t Rational::denominator() const { return denominator_; }

std::ostream &operator<<(std::ostream &s, const Rational &v) {
  return s << v.numerator_ << "/" << v.denominator_;
}

std::istream &operator>>(std::istream &s, Rational &v) {
  char delim;
  int64_t num;
  int64_t denom;
  if (!(s >> num >> delim >> denom))
    return s; // Couldn't read
  if (denom == 0)
    throw std::domain_error("Denominator cannot be zero.");
  // Only when everything is OK, mutate the state of v
  v.numerator_ = num;
  v.denominator_ = denom;
  v.normalize();
  return s;
}

auto operator<=>(const Rational &left, const Rational &right) {
  return left.numerator_ * right.denominator_ <=>
         right.numerator_ * left.denominator_;
}
bool operator==(const Rational &left, const Rational &right) {
  return left.numerator_ * right.denominator_ ==
         right.numerator_ * left.denominator_;
}

Rational operator+(const Rational &left, const Rational &right) {
  return Rational{left.numerator_ * right.denominator_ +
                      right.numerator_ * left.denominator_,
                  left.denominator_ * right.denominator_};
}
Rational operator-(const Rational &left, const Rational &right) {
  return Rational{left.numerator_ * right.denominator_ -
                      right.numerator_ * left.denominator_,
                  left.denominator_ * right.denominator_};
}
Rational operator*(const Rational &left, const Rational &right) {
  return Rational{left.numerator_ * right.numerator_,
                  left.denominator_ * right.denominator_};
}
Rational operator/(const Rational &left, const Rational &right) {
  if (right.numerator_ == 0)
    throw std::domain_error("Cannot divide by zero.");
  return Rational{left.numerator_ * right.denominator_,
                  left.denominator_ * right.numerator_};
}

Rational &Rational::operator+=(const Rational &other) {
  numerator_ =
      numerator_ * other.denominator_ + other.numerator_ * denominator_;
  denominator_ *= other.denominator_;
  normalize();
  return *this;
}

Rational &Rational::operator-=(const Rational &other) {
  numerator_ =
      numerator_ * other.denominator_ - other.numerator_ * denominator_;
  denominator_ *= other.denominator_;
  normalize();
  return *this;
}

Rational &Rational::operator*=(const Rational &other) {
  numerator_ *= other.numerator_;
  denominator_ *= other.denominator_;
  normalize();
  return *this;
}

Rational &Rational::operator/=(const Rational &other) {
  if (other.numerator_ == 0)
    throw std::domain_error("Cannot divide by zero.");
  numerator_ *= other.denominator_;
  denominator_ *= other.numerator_;
  normalize();
  return *this;
}

void Rational::normalize() {
  int64_t gcd = std::gcd(numerator_, denominator_);
  numerator_ /= gcd;
  denominator_ /= gcd;

  // Normalize sign
  if (denominator_ < 0) {
    numerator_ *= -1;
    denominator_ *= -1;
  }
}

} // namespace Numbers