#include "Interface.h"

Interface::Interface() {
    screenController.getInstance()->ClearScreen();
    Init();
}

Interface::~Interface() {
    DeInit();
}

void Interface::Init() {
    panel = new Panel();
}

void Interface::DeInit() {
    delete panel;
    panel = NULL;
}

void Interface::EventHandler( SDL_Event& event ) {
    if( event.type == SDL_QUIT ) {
        readyToQuit = true;
    }
    else {
        panel->EventHandler( event );
    }
}

bool Interface::GetQuit() const {
    return readyToQuit;
}

void Interface::Draw() {
    panel->Draw();

    screenController.getInstance()->Present();
}