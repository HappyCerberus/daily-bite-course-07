#include "catch2/catch_test_macros.hpp"
#include "catch2/matchers/catch_matchers_floating_point.hpp"
#include "rational.h"
#include <sstream>

TEST_CASE("Construction, querying and normalization") {
  Numbers::Rational v{10, 20};
  REQUIRE(v.normalized().numerator() == 1);
  REQUIRE(v.normalized().denominator() == 2);

  Numbers::Rational w{10};
  REQUIRE(w.numerator() == 10);
  REQUIRE(w.denominator() == 1);

  REQUIRE_THROWS([]() { Numbers::Rational x{1, 0}; }());
}

TEST_CASE("I/O") {
  SECTION("stream extraction") {
    std::stringstream str("7/3");
    Numbers::Rational x{1, 1};

    REQUIRE_NOTHROW(str >> x);
    REQUIRE(x.numerator() == 7);
    REQUIRE(x.denominator() == 3);
  }
  SECTION("stream extraction with exception") {
    std::stringstream str("7/0");
    Numbers::Rational x{1, 1};

    REQUIRE_THROWS(str >> x);
    REQUIRE(x.numerator() == 1);
    REQUIRE(x.denominator() == 1);
  }
  SECTION("stream insertion") {
    std::stringstream str;
    Numbers::Rational x{7, 3};

    REQUIRE_NOTHROW(str << x);
    REQUIRE(str.str() == "7/3");
  }
}

TEST_CASE("Conversions") {
  Numbers::Rational x{7, 3};
  REQUIRE(int64_t{x} == 2);
  REQUIRE_THAT(double{x}, Catch::Matchers::WithinAbs(2.333, 0.01));
}

TEST_CASE("Addition") {
  using Numbers::Rational;
  REQUIRE(Rational{0, 1} + Rational{0, 1} == Rational{0, 1});
  REQUIRE(Rational{0, 1} + Rational{1, 2} == Rational{1, 2});
  REQUIRE(Rational{1, 2} + Rational{1, 2} == Rational{1, 1});
  REQUIRE(Rational{0, 1} + Rational{-1, 1} == Rational{-1, 1});
  REQUIRE(Rational{1, 1} + Rational{-1, 1} == Rational{0, 1});
  REQUIRE(Rational{1, 2} + Rational{1, 4} == Rational{3, 4});
}

TEST_CASE("Substraction") {
  using Numbers::Rational;
  REQUIRE(Rational{0, 1} - Rational{0, 1} == Rational{0, 1});
  REQUIRE(Rational{0, 1} - Rational{1, 2} == Rational{-1, 2});
  REQUIRE(Rational{1, 2} - Rational{1, 2} == Rational{0, 1});
  REQUIRE(Rational{0, 1} - Rational{-1, 1} == Rational{1, 1});
  REQUIRE(Rational{1, 1} - Rational{-1, 1} == Rational{2, 1});
  REQUIRE(Rational{1, 2} - Rational{1, 4} == Rational{1, 4});
}

TEST_CASE("Multiplication") {
  using Numbers::Rational;
  REQUIRE(Rational{0, 1} * Rational{0, 1} == Rational{0, 1});
  REQUIRE(Rational{0, 1} * Rational{1, 2} == Rational{0, 1});
  REQUIRE(Rational{1, 2} * Rational{1, 2} == Rational{1, 4});
  REQUIRE(Rational{0, 1} * Rational{-1, 1} == Rational{0, 1});
  REQUIRE(Rational{1, 1} * Rational{-1, 1} == Rational{-1, 1});
  REQUIRE(Rational{1, 2} * Rational{1, 4} == Rational{1, 8});
}

TEST_CASE("Division") {
  using Numbers::Rational;
  REQUIRE_THROWS(Rational{0, 1} / Rational{0, 1});
  REQUIRE(Rational{0, 1} / Rational{1, 2} == Rational{0, 1});
  REQUIRE(Rational{1, 2} / Rational{1, 2} == Rational{1, 1});
  REQUIRE(Rational{0, 1} / Rational{-1, 1} == Rational{0, 1});
  REQUIRE(Rational{1, 1} / Rational{-1, 1} == Rational{-1, 1});
  REQUIRE(Rational{1, 2} / Rational{1, 4} == Rational{2, 1});
}

TEST_CASE("Compound Addition") {
  using Numbers::Rational;
  Rational a{0, 1};
  a += a;
  REQUIRE(a == Rational{0, 1});
  a += Rational{1, 2};
  REQUIRE(a == Rational{1, 2});
  a += Rational{1, 2};
  REQUIRE(a == Rational{1, 1});
  Rational b{0, 1};
  b += Rational{-1, 1};
  REQUIRE(b == Rational{-1, 1});
  b += Rational{1, 1};
  REQUIRE(b == Rational{0, 1});
  Rational c{1, 2};
  c += Rational{1, 4};
  REQUIRE(c == Rational{3, 4});
}

TEST_CASE("Compound Substraction") {
  using Numbers::Rational;
  Rational a{0, 1};
  a -= a;
  REQUIRE(a == Rational{0, 1});
  a -= Rational{1, 2};
  REQUIRE(a == Rational{-1, 2});
  Rational b{1, 2};
  b -= Rational{1, 2};
  REQUIRE(b == Rational{0, 1});
  b -= Rational{-1, 1};
  REQUIRE(b == Rational{1, 1});
  Rational c{1, 1};
  c -= Rational{-1, 1};
  REQUIRE(c == Rational{2, 1});
  Rational d{1, 2};
  d -= Rational{1, 4};
  REQUIRE(d == Rational{1, 4});
}

TEST_CASE("Compound Multiplication") {
  using Numbers::Rational;
  Rational a{0, 1};
  a *= Rational{0, 1};
  REQUIRE(a == Rational{0, 1});
  a *= Rational{1, 2};
  REQUIRE(a == Rational{0, 1});
  Rational b{1, 2};
  b *= Rational{1, 2};
  REQUIRE(b == Rational{1, 4});
  Rational c{0, 1};
  c *= Rational{-1, 1};
  REQUIRE(c == Rational{0, 1});
  Rational d{1, 1};
  d *= Rational{-1, 1};
  REQUIRE(d == Rational{-1, 1});
  Rational e{1, 2};
  e *= Rational{1, 4};
  REQUIRE(e == Rational{1, 8});
}

TEST_CASE("Compound Division") {
  using Numbers::Rational;
  Rational a{0, 1};
  REQUIRE_THROWS(a /= Rational{0, 1});
  a /= Rational{1, 2};
  REQUIRE(a == Rational{0, 1});
  Rational b{1, 2};
  b /= Rational{1, 2};
  REQUIRE(b == Rational{1, 1});
  Rational c{0, 1};
  c /= Rational{-1, 1};
  REQUIRE(c == Rational{0, 1});
  Rational d{1, 1};
  d /= Rational{-1, 1};
  REQUIRE(d == Rational{-1, 1});
  Rational e{1, 2};
  e /= Rational{1, 4};
  REQUIRE(e == Rational{2, 1});
}