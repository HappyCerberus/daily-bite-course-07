#pragma once

#include <algorithm>
#include <concepts>
#include <cstdint>
#include <iosfwd>
#include <stdexcept>
#include <utility>

namespace Numbers {

struct Rational {
  Rational(int64_t numerator, int64_t denominator);
  explicit Rational(int64_t integer);

  const Rational &normalized() const;
  int64_t numerator() const;
  int64_t denominator() const;

  // Generic version of integral conversion.
  // We have to check whether the target type can represent the value
  // and if not report an error.
  template <std::integral T> explicit operator T() const {
    int64_t value = numerator_ / denominator_;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"
    if (std::in_range<T>(value))
      return T{value};
#pragma GCC diagnostic pop
    throw std::domain_error("Cannot represent the value using this type.");
  }
  template <std::floating_point T> explicit operator T() const {
    return T(numerator_) / T(denominator_);
  }

  friend auto operator<=>(const Rational &left, const Rational &right);
  friend bool operator==(const Rational &left, const Rational &right);

  friend Rational operator+(const Rational &left, const Rational &right);
  friend Rational operator-(const Rational &left, const Rational &right);
  friend Rational operator*(const Rational &left, const Rational &right);
  friend Rational operator/(const Rational &left, const Rational &right);

  Rational &operator+=(const Rational &other);
  Rational &operator-=(const Rational &other);
  Rational &operator*=(const Rational &other);
  Rational &operator/=(const Rational &other);

  friend std::ostream &operator<<(std::ostream &s, const Rational &v);
  friend std::istream &operator>>(std::istream &s, Rational &v);

private:
  int64_t numerator_;
  int64_t denominator_;
  void normalize();
};

} // namespace Numbers