//
// Created by Dharmil Jadav on 4/20/21.
//

#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "function.h"
#include "graph.h"

namespace graph {

/**
 * An app used to graph.
 */
class GraphApp : public ci::app::App {
  public:
    /**
     * Default constructor for graph app.
     */
    GraphApp();
    
    /**
     * Destructor used to delete the graph object.
     */
    ~GraphApp();
    
    /**
     * Draws the graph in the window.
     */
    void draw() override;
    
  private:
    Graph* graph_;

    /**
     * Function used to take in a vector of strings and convert them
     * into a Line object.
     * @param parameters Vector of strings.
     * @return A Line pointer that represents the Line object.
     */
    Line* CreateLine(const vector<std::string>& parameters) const;
  
    /**
     * Function used to take in a vector of strings and convert them
     * into a Polynomial object.
     * @param parameters Vector of strings.
     * @return A Polynomial pointer that represents the Polynomial object.
     */
    Polynomial* CreatePolynomial(const vector<std::string>& parameters) const;
  
    /**
     * Function used to convert string to ci::Color.
     * @param color A string representing the color to be chosen.
     * @return A cinder color object.
     */
    ci::Color FindColor(const std::string& color) const;

    const size_t kWindowSize = 1000;
    const size_t kGraph = 20;
    const size_t kOne = 1;
    const size_t kTwo = 2;
    const size_t kThree = 3;
    const size_t kFour = 4;
    const size_t kFive = 5;
    const int kNegativeOne = -1;
    std::string kGreen = "green";
    std::string kOrange = "orange";
    std::string kYellow = "yellow";
    std::string kBlue = "blue";
    ci::Color kColorBlack = "black";
    ci::Color kColorGreen = "green";
    ci::Color kColorYellow = "yellow";
    ci::Color kColorBlue = "blue";
    ci::Color kColorOrange = "orange";
    std::string kFilePath = "/Users/djadav/Desktop/Cinder/my-projects/final-project-djadav2/input_graphs.txt";
    std::string kDelimeter = ";";
};

} // namespace 2D-graph