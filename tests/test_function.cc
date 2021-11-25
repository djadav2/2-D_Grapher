//
// Created by Dharmil Jadav on 4/20/21.
//

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <function.h>

using graph::Function;
using graph::Line;
using graph::Polynomial;
using graph::PointPairs;
using std::pair;

TEST_CASE("Invalid constructor declarations") {
  SECTION("Line: Y-intercept out of bounds") {
    REQUIRE_THROWS_AS(Line(1, 30, 20, 20, ci::Color("green"), 1000), std::invalid_argument);
  }
}

TEST_CASE("Testing getters") {
  Line line = Line(1, 5, 20, 20, ci::Color("green"), 1000);
  
  SECTION("Line getters") {
    SECTION("Slope getter") {
      REQUIRE(1 == line.GetSlope());
    }

    SECTION("Y-intercept getter") {
      REQUIRE(5 == line.GetYIntercept());
    }
  }
  
  Polynomial poly = Polynomial(2, 1, 2, 2, 20, 20, ci::Color("blue"), 1000);
  SECTION("Polynomial getters") {
    SECTION("Exponent getter") {
      REQUIRE(2 == poly.GetExponent());
    }
    
    SECTION("Coefficient getter") {
      REQUIRE(1 == poly.GetCoeff());
    }
    
    SECTION("Horizontal shift getter") {
      REQUIRE(2 == poly.GetHorizontalShift());
    }
    
    SECTION("Vertical shift getter") {
      REQUIRE(2 == poly.GetVerticalShift());
    }
  }
  
  SECTION("Function getters") {
    SECTION("Max X getters") {
      REQUIRE((20 == line.GetMaxX()) == (20 == poly.GetMaxX()));
    }
    
    SECTION("Max Y getters") {
      REQUIRE((20 == line.GetMaxY()) == (20 == poly.GetMaxY()));
    }
    
    SECTION("Color getters") {
      REQUIRE((ci::Color("green") == line.GetColor()) == (ci::Color("blue") == poly.GetColor()));
    }
    
    SECTION("Window size getters") {
      REQUIRE((1000 == line.GetWindowSize()) == (1000 == poly.GetWindowSize()));
    }
  }
}

/**
 * This function checks to see if the Line objects' points are calculated correctly.
 * @param line Line object.
 * @return Returns true if points are calculated correctly.
 */
bool CheckLinePoints(const Line& line) {
  double w_size = line.GetWindowSize();
  double x_interval = w_size / line.GetMaxX();
  double y_interval = w_size / line.GetMaxY();
  PointPairs pairs = line.CalculatePoints();
  double slope = line.GetSlope();
  for (const pair<pair<double, double>, pair<double, double>> pair : pairs) {
    std::pair<double, double> p_one = pair.first;
    std::pair<double, double> p_two = pair.second;
    
    if (abs(slope) > 1) {
      if ((p_two.first + x_interval) != p_one.first) {
        return false;
      }
      if (p_two.second - (slope * y_interval) != p_one.second) {
        return false;
      }
    } else {
      if (p_two.first - ((1 / slope) * x_interval) != p_one.first) {
        return false;
      }
      if ((p_two.second + y_interval) != p_one.second) {
        return false;
      }
    }
  }
  
  return true;
}

/**
 * This function checks to see if the Polynomials' points are calculated correctly.
 * @param poly Polynomial object.
 * @return Returns true if points are calculated correctly.
 */
bool CheckPolynomialPoints(const Polynomial& poly) {
  double mid = (double) poly.GetWindowSize() / 2;
  double x_inc = (double) poly.GetWindowSize() / (double) poly.GetMaxX();
  double y_inc = (double) poly.GetWindowSize() / (double) poly.GetMaxY();
  PointPairs pairs = poly.CalculatePoints();
  
  for (const pair<pair<double, double>, pair<double, double>> pair : pairs) {
    std::pair<double, double> p_one = pair.first;
    std::pair<double, double> p_two = pair.second;
    
    double y_one = (mid - (((poly.GetCoeff() * pow(((p_one.first - mid) / x_inc) - poly.GetHorizontalShift(), poly.GetExponent()))) + poly.GetVerticalShift()) * y_inc);
    double y_two = (mid - (((poly.GetCoeff() * pow(((p_two.first - mid) / x_inc) - poly.GetHorizontalShift(), poly.GetExponent()))) + poly.GetVerticalShift()) * y_inc);
    
    if ((y_two - y_one) != (p_two.second - p_one.second)) {
      return false;
    }
  }
  
  return true;
}

TEST_CASE("Point calculations") {
  Line line = Line(2, 5, 20, 20, ci::Color("blue"), 1000);
  Line line4 = Line(0.5, 3, 20, 20, ci::Color("blue"), 1000);
  Line line2 = Line(-5, 2, 20, 20, ci::Color("blue"), 1000);
  Line line3 = Line(-.25, 1, 20, 20, ci::Color("blue"), 1000);
  Polynomial poly = Polynomial(2, 1, 2, 2, 20, 20, ci::Color("blue"), 1000);
  Polynomial poly2 = Polynomial(4, 4, 2, 3, 20, 20, ci::Color("green"), 1000);

  SECTION("Line point calculations") {
    SECTION("Positive slope m > 1") {
      REQUIRE(true == CheckLinePoints(line));
    }
    
    SECTION("Negative slope m < -1") {
      REQUIRE(true == CheckLinePoints(line2));
    }
    
    SECTION("Negative slope m > -1") {
      REQUIRE(true == CheckLinePoints(line3));
    }
    
    SECTION("Positive slope m < 1") {
      REQUIRE(true == CheckLinePoints(line4));
    }
  }
  
  SECTION("Polynomial point calculations") {
    SECTION("Quadratic polynomial") {
      REQUIRE(true == CheckPolynomialPoints(poly));
    }
    
    SECTION("Cubic polynomial") {
      REQUIRE(true == CheckPolynomialPoints(poly2));
    }
  }
}