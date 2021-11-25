//
// Created by Dharmil Jadav on 4/20/21.
//

#include "function.h"
#include <iostream>

namespace graph {

using std::pair;

PointPairs Function::CalculatePoints() const {
  PointPairs pairs;
  return pairs;
}

size_t Function::GetMaxX() const {
  return max_X_;
}

size_t Function::GetMaxY() const {
  return max_Y_;
}

ci::Color Function::GetColor() const {
  return color_;
}

size_t Function::GetWindowSize() const {
  return window_size_;
}

Function::~Function() = default;

Line::Line(double slope, double y_intercept, size_t max_X, size_t max_Y,
           const ci::Color& color, size_t window_size) {
  slope_ = slope;
  
  if (y_intercept > max_Y) {
    throw std::invalid_argument("Invalid y-intercept");
  }
  
  y_intercept_ = y_intercept;
  max_X_ = max_X;
  max_Y_ = max_Y;
  color_ = color;
  window_size_ = window_size;
}

PointPairs Line::CalculatePoints() const {
  PointPairs points;
  double mid_point = (double) window_size_ / 2, x = 0, y = y_intercept_;
  double x_increment = (double) window_size_ / (double) max_X_;
  double y_increment = (double) window_size_ / (double) max_Y_;
  double curr_x = mid_point;
  double curr_y = mid_point - (y_increment * y_intercept_) + kYAxis;
  // Calculates points if slope is reliant on max_y value.
  if (abs(slope_) > 1) {
    while (y < max_Y_) { // Calculates points to the left of y-intercept.
      pair<double, double> initial(curr_x, curr_y);
      if (slope_ < 1) { y -= slope_; } else { y += slope_; }
      pair<double, double> after((curr_x -= x_increment),
                                 (curr_y += (y_increment * slope_)));
      points[initial] = after;
    }
    // Calculates points to the right of the y-intercept.
    y = y_intercept_, curr_x = mid_point;
    curr_y = mid_point - (y_intercept_ * y_increment) + kYAxis;
    while (y > (-1 * (double) (max_Y_))) {
      pair<double, double> after(curr_x, curr_y);
      if (slope_ < 1) { y += slope_; } else { y -= slope_; }
      pair<double, double> initial((curr_x += x_increment),
                                   (curr_y -= (y_increment * slope_)));
      points[initial] = after;
    }
  // Calculates points if slope is reliant on max_x value.
  } else {
    while (x < max_X_) { // Calculates points on right side of y-intercept.
      pair<double, double> initial(curr_x, curr_y);
      if (slope_ < 0) { x -= (1 / slope_); } else { x += (1 / slope_); }
      pair<double, double> after((curr_x += ((1 / slope_) * x_increment)),
                                 (curr_y -= y_increment));
      points[initial] = after;
    }
    // Calculates points on left side of y-intercept.
    x = 0, curr_x = mid_point;
    curr_y = mid_point - (y_intercept_ * y_increment) + kYAxis;
    while (x > (-1 * (double) (max_X_))) {
      pair<double, double> after(curr_x, curr_y);
      if (slope_ < 0) { x += (1 / slope_); } else { x -= (1 / slope_); }
      pair<double, double> initial((curr_x -= ((1 / slope_) * x_increment)),
                                   (curr_y += y_increment));
      points[initial] = after;
    }
  }

  return points;
}

double Line::GetSlope() const {
  return slope_;
}

size_t Line::GetYIntercept() const {
  return y_intercept_;
}

Polynomial::Polynomial(double exponent, double coeff, double horizontal, 
                       double vertical, size_t max_x, size_t max_y,
                       const ci::Color& color, size_t window_size) {
  exponent_ = exponent;
  coeff_ = coeff;
  horizontal_ = horizontal;
  vertical_ = vertical;
  max_X_ = max_x;
  max_Y_ = max_y;
  color_ = color;
  window_size_ = window_size;
}

PointPairs Polynomial::CalculatePoints() const {
  PointPairs points;
  double mid_point = (double) window_size_ / 2;
  double x_increment = ((double) window_size_ / (double) max_X_);
  double y_increment = ((double) window_size_ / (double) max_Y_);
  double graph_x = (mid_point + (horizontal_ * (x_increment)));
  double x_value = horizontal_;
  double y_value = vertical_;
  double graph_y = (mid_point - (vertical_ * y_increment));
  // Calculates points right of the vertex
  while (abs(x_value) < max_X_ && abs(y_value) < max_Y_) {
    pair<double, double> initial_left(graph_x, graph_y);
    x_value++, graph_x += x_increment;
    y_value = ((coeff_ * (pow(x_value - horizontal_, exponent_))) + vertical_);
    graph_y = mid_point - (y_value * y_increment);
    pair<double, double> after_right(graph_x, graph_y);
    points[initial_left] = after_right;
  }
  
  graph_x = (mid_point + (horizontal_ * x_increment));
  x_value = horizontal_, y_value = vertical_;
  graph_y = (mid_point - (vertical_ * y_increment));
  // Calculates points left of the vertex
  while(abs(x_value) < max_X_ && abs(y_value) < max_Y_) {
    pair<double, double> after_right(graph_x, graph_y);
    x_value--, graph_x -= x_increment;
    y_value = ((coeff_ * (pow(x_value - horizontal_, exponent_))) + vertical_);
    graph_y = mid_point - (y_value * y_increment);
    pair<double, double> initial_left(graph_x, graph_y);
    points[initial_left] = after_right;
  }
  
  return points;
}

double Polynomial::GetExponent() const {
  return exponent_;
}

double Polynomial::GetCoeff() const {
  return coeff_;
}

double Polynomial::GetHorizontalShift() const {
  return horizontal_;
}

double Polynomial::GetVerticalShift() const {
  return vertical_;
}

} // namespace graph