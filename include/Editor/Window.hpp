#pragma once

#include <FL/Fl_Double_Window.H>
#include <FL/Fl.H>

// ======= Main Window ======= //
// This is the main window for the editor´

namespace Editor {

class Window {
public:
    Window();
    ~Window();

    void start()

private:

    Fl_Double_Window *win;

};

};