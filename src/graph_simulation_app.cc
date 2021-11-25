//
// Created by Dharmil Jadav on 4/20/21.
//

#include "graph_simulation_app.h"
#include <fstream>

namespace graph {

using std::string;

GraphApp::GraphApp() {
  ci::app::setWindowSize(kWindowSize, kWindowSize);
  std::ifstream graph_file(kFilePath);
  
  if (!graph_file.good()) {
    throw std::invalid_argument("Invalid file path");
  }

  vector<Function*> functions;
  string curr_function;

  while (!graph_file.eof()) {
    // Stores a function for each line in the file.
    std::getline(graph_file, curr_function);
    std::vector<string> parameters;
    string curr_argument;
    size_t index = 0;
    
    // Taken from https://stackoverflow.com/questions/14265581/
    // parse-split-a-string-in-c-using-string-delimiter-standard-c.
    // Splits the string by semi-colon.
    while ((index = curr_function.find(kDelimeter)) != string::npos) {
      curr_argument = curr_function.substr(0, index);
      parameters.push_back(curr_argument);
      curr_function.erase(0, index + kDelimeter.length());
    }
    parameters.push_back(curr_function);
    
    if (parameters[0] == "Line") {
      Line* line = CreateLine(parameters);
      functions.push_back(line);
    } else if (parameters[0] == "Polynomial") {
      Polynomial* poly = CreatePolynomial(parameters);
      functions.push_back(poly);
    }
  }
  
  graph_ = new Graph(functions, kGraph, kWindowSize);
}

GraphApp::~GraphApp() {
  delete graph_;
}

void GraphApp::draw() {
  ci::Color background_color(kColorBlack);
  ci::gl::clear(background_color);
  
  graph_->Display();
}

Line* GraphApp::CreateLine(const vector<string>& parameters) const {
  size_t slope_index = parameters[kOne].find('=') + 1;
  size_t x_index = parameters[kOne].find('x');
  size_t slope_diff = x_index - slope_index;
  double slope = stod(parameters[kOne].substr(slope_index, slope_diff));
  
  size_t y_diff = parameters[kOne].length() - (x_index + 2);
  double y_int = stod(parameters[kOne].substr(x_index + 2, y_diff));
  if (parameters[1].substr(x_index + 1, 1) == "-") { y_int *= kNegativeOne; }
  
  ci::Color color = FindColor(parameters[kFour]);
  return new Line(slope, y_int, stoi(parameters[kTwo]),
                  stoi(parameters[kThree]), color, stoi(parameters[kFive]));
}

Polynomial* GraphApp::CreatePolynomial(const vector<string>& parameters) const {
  size_t equals_index = parameters[kOne].find('=');
  size_t left_par_index = parameters[kOne].find('(');
  size_t coeff_diff = left_par_index - equals_index;
  double coeff = stod(parameters[kOne].substr(equals_index + 1, coeff_diff));
  
  size_t right_par_index = parameters[kOne].find(')');
  size_t hori_diff = right_par_index - (left_par_index + 2);
  double horizontal = stod(parameters[kOne].substr(left_par_index + 2, hori_diff));
  if (parameters[1].substr(left_par_index + 1, 1) == "+") { horizontal *= kNegativeOne; }
  
  size_t left_curly_index = parameters[kOne].find('{');
  size_t right_curly_index = parameters[kOne].find('}');
  size_t exp_diff = right_curly_index - left_curly_index;
  double exp = stod(parameters[kOne].substr(left_curly_index + 1, exp_diff));
  
  size_t vert_diff = parameters[kOne].length() - (right_curly_index + 2);
  double vert = stod(parameters[kOne].substr(right_curly_index + 2, vert_diff));
  if (parameters[1].substr(right_curly_index + 1, 1) == "-") { vert *= kNegativeOne; }
  
  ci::Color color = FindColor(parameters[kFour]);
  return new Polynomial(exp, coeff, horizontal, vert, stoi(parameters[kTwo]), 
                        stoi(parameters[kThree]), color, stoi(parameters[kFive]));
}

ci::Color GraphApp::FindColor(const string& color) const {
  if (color == kGreen) {
    return kColorGreen;
  } else if (color == kOrange) {
    return kColorOrange;
  } else if (color == kBlue) {
    return kColorBlue;
  }
  return kColorYellow;
}

} // namespace graph;