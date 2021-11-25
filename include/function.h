//
// Created by Dharmil Jadav on 4/20/21.
//

#pragma once

#include <cstdlib>
#include <stdexcept>
#include <utility>
#include <map>
#include "cinder/gl/gl.h"

namespace graph {

using std::pair;
using std::map;

typedef map<pair<double, double>, pair<double, double>> PointPairs;

/**
 * This is an abstract class that provides the layout for
 * types of functions to graph.
 */
class Function {
  public:
    /**
     * This function acts as the main function for drawing on the graph.
     * It utilizies pairs of points that is used to then draw from one point
     * to another to another to another, etc.
     * @return A PointPairs representing a map of point pairs.
     */
    virtual PointPairs CalculatePoints() const;
    
    /**
     * Getter for max-x value on graph.
     * @return A size_t representing min and max x-value.
     */
    size_t GetMaxX() const;
    
    /**
     * Getter for max-y value on graph.
     * @return A size_t representing min and max y-value.
     */
    size_t GetMaxY() const;
    
    /**
     * Getter for color of the function to be drawn.
     * @return A color represented by a cinder Color object.
     */
    ci::Color GetColor() const;
    
    /**
     * A Getter for the window size of the Cinder App.
     * @return A size_t representing window size.
     */
    size_t GetWindowSize() const;
    
    /**
     * Destructor needed for compilation.
     */
    virtual ~Function();
    
  protected:
    size_t max_X_;
    size_t max_Y_;
    ci::Color color_;
    size_t window_size_;
};

/**
 * This is the Line class inherited from the Function abstract
 * class used for graphing linear lines.
 */
class Line: public Function {
  public:
    /**
     * Main constructor for Line object.
     * @param slope Slope of linear line.
     * @param y_intercept Y-intercept of linear line.
     * @param max_X Max X-value of graph.
     * @param max_Y Max Y-value of graph.
     * @param color Color of function.
     * @param window_size Size of Cinder App.
     */
    Line(double slope, double y_intercept, size_t max_X, size_t max_Y,
         const ci::Color& color, size_t window_size);
    
    /**
     * Overriden virtual function. 
     * @return PointPairs with map of pairs of points.
     */
    PointPairs CalculatePoints() const override;
    
    /**
     * Getter for slope of linear line.
     * @return A double representing slope of line.
     */
    double GetSlope() const;
    
    /**
     * Getter for the y-intercept of linear line.
     * @return A size_t representing y-intercept of line.
     */
    size_t GetYIntercept() const;
    
  private:
    double slope_;
    double y_intercept_;

    static constexpr size_t kYAxis = 20;
};

/**
 * This is the Polynomial class inherited from the Function abstract
 * class used to draw polynomial lines on graph.
 */
class Polynomial: public Function {
  public:
    /**
     * Main constructor for Polynomial object (uses standard form).
     * @param exponent exponent of (x-a).
     * @param coeff coefficient of (x-a).
     * @param horizontal shift representing a.
     * @param vertical shift representing b.
     * @param max_x Max x-value of graph.
     * @param max_y Max y-value of graph.
     * @param color Color of function.
     * @param window_size Window size of Cinder app.
     */
    Polynomial(double exponent, double coeff, double horizontal, 
               double vertical, size_t max_x, size_t max_y,
               const ci::Color& color, size_t window_size);
    
    /**
     * Overriden virtual method.
     * @return PointPairs representing a map with pairs of point.
     */
    PointPairs CalculatePoints() const override;
    
    /**
     * Getter for exponent of (x-a).
     * @return double representing exponent.
     */
    double GetExponent() const; 
    
    /**
     * Getter for coefficient of (x-a).
     * @return double representing coefficient.
     */
    double GetCoeff() const;
    
    /**
     * Getter for horizontal shift representing a.
     * @return double representing horizontal shift.
     */
    double GetHorizontalShift() const;
    
    /**
     * Getter for vertical shift representing b.
     * @return double representing vertical shift.
     */
    double GetVerticalShift() const;
  
  private:
    double exponent_;
    double coeff_;
    double horizontal_;
    double vertical_;
};

} // namespace 2D_graph