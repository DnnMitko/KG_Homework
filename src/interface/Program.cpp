#include "Program.h"

Program::Program() {
    screenController.getInstance()->ClearScreen();
    Init();
}

Program::~Program() {
    DeInit();
}

void Program::Init() {
    interface = new Interface();
}

void Program::DeInit() {
    delete interface;
    interface = NULL;
}

void Program::EventHandler( SDL_Event& event ) {
    if( event.type == SDL_QUIT ) {
        readyToQuit = true;
    }
    else {
        interface->EventHandler( event );
    }
}

bool Program::GetQuit() const {
    return readyToQuit;
}

void Program::Draw() {
    interface->Draw();

    screenController.getInstance()->Present();
}