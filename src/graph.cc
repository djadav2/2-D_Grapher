//
// Created by Dharmil Jadav on 4/20/21.
//

#include "graph.h"
#include <string>

namespace graph {

using glm::vec2;
using std::pair;
using std::to_string;
using ci::gl::drawLine;

typedef pair<pair<double, double>, pair<double, double>> Point;

Graph::Graph() {
  vector<Function*> vector;
  functions_ = vector;
  graph_size_ = 0;
  window_size_ = 0;
}

Graph::Graph(const vector<Function*>& functions, 
             size_t graph_size, size_t window_size) {
  if (functions.empty()) {
    throw std::invalid_argument("Empty vector");
  }
  
  functions_ = functions;
  graph_size_ = graph_size;
  window_size_ = window_size;
}

Graph::~Graph() {
  for (Function* function: functions_) {
    delete function;
  }
}

void Graph::Display() const {
  ci::gl::color(ci::Color(kColorWhite));
  DrawAxes();
  DrawFunctions();
}

void Graph::DrawAxes() const {
  int mid_board = (int) window_size_ / 2;
  int mid_board_value = (int) graph_size_ / 2;
  int marker = ((int) window_size_ / kNumMarkers);
  int marker_value = ((int) graph_size_ / kNumMarkers);
  size_t x_height = (window_size_ / 2) - kXStringHeight;

  // Draws physical x and y axes lines.
  drawLine(vec2(mid_board, kBuffer), 
           vec2(mid_board, window_size_ - kBuffer));
  drawLine(vec2(kBuffer, mid_board),
           vec2(window_size_ - kBuffer, mid_board));
  
  // Draws each individual marker.
  for (int index = 0; index < kNumMarkers; index++) {
    if (index == kNumMarkers / 2) {
      continue;
    }
    // Draws the x or y value associated with each marker.
    ci::gl::drawString(std::to_string((index * marker_value) - mid_board_value),
                       vec2((index * marker), x_height),
                       kColorCyan, ci::Font(kFontName, kFontSize));
    ci::gl::drawString(std::to_string((index * marker_value) - mid_board_value),
                       vec2(mid_board, 
                            (window_size_ + kYString) - (index * marker)),
                       kColorCyan, ci::Font(kFontName, kFontSize));
    
    // Draws the physical marker on the graph.
    drawLine(vec2((index * marker) + kNumMarkers, mid_board - kXBuffer), 
             vec2((index * marker) + kNumMarkers, mid_board + kXBuffer));
    drawLine(vec2(mid_board - kYBuffer, (index * marker) + kNumMarkers),
             vec2(mid_board + kYBuffer, (index * marker) + kNumMarkers));
  }
}

void Graph::DrawFunctions() const {
  // Loops through each function and draws lines from each pair of points.
  for (const Function* function: functions_) {
    PointPairs points = function->CalculatePoints();
    ci::Color color = function->GetColor();
    ci::gl::color(color);
    
    // Draws a line from each point to point
    for (const Point point : points) {
      ci::gl::drawLine(vec2(point.first.first, point.first.second),
                       vec2(point.second.first, point.second.second));
    }
  }
}

} // namespace graph