//
// Created by Dharmil Jadav on 4/20/21.
//

#pragma once

#include "function.h"
#include <vector>
#include "graph.h"
#include "cinder/gl/gl.h"

namespace graph {

using std::vector;

/**
 * Graph class used to represent graph in Cinder app.
 */
class Graph {
  public:
    /**
     * Default empty constructor.
     */
    Graph();

    /**
     * Destructor for Graph object to destroy the vector of
     * Function pointers.
     */
    ~Graph();

    /**
     * Main constructor that passes in vector of functions.
     * @param functions vector with functions stored in them.
     * @param graph_size size_t representing size of graph.
     * @param window_size size_t representing window size.
     */
    Graph(const vector<Function*>& functions, size_t graph_size,
          size_t window_size);
    
    /**
     * Method to display everything on the graph.
     */
    void Display() const;
    
  private:
    vector<Function*> functions_;
    size_t graph_size_;
    size_t window_size_;
    
    /**
     * Helper method to draw axes of graph.
     */
    void DrawAxes() const;
    
    /**
     * Helper method to draw each function.
     */
    void DrawFunctions() const;
    
    
    // Constants used for drawing axes and markers.
    ci::Color kColorBlue = "blue";
    ci::Color kColorWhite = "white";
    ci::Color kColorCyan = "cyan";
    static constexpr size_t kBuffer = 0;
    static constexpr int kNumMarkers = 20;
    static constexpr size_t kYString = 7;
    std::string kFontName = "Arial";
    static constexpr size_t kFontSize = 16;
    static constexpr size_t kXStringHeight = 50;
    static constexpr size_t kXBuffer = 25;
    static constexpr size_t kYBuffer = 25;
};

} // namespace 2D-graph