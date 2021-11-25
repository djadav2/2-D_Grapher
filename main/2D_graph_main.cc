//
// Created by Dharmil Jadav on 4/20/21.
//

#include <iostream>
#include "graph_simulation_app.h"

using graph::GraphApp;

void prepareSettings(GraphApp::Settings* settings) {
  settings->setResizable(false);
}

// This is a macro for graphing the functions.
CINDER_APP(GraphApp, ci::app::RendererGl, prepareSettings);