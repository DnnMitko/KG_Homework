#include "Global.h"

Global::Global() {
    Init();
}

Global::~Global() {
    Deinit();
}

void Global::Init() {
    Settings = new XML_Wrapper();
    ScreenController = new SDL_Wrapper();
}

void Global::Deinit() {
    delete ScreenController;
    ScreenController = NULL;

    delete Settings;
    Settings = NULL;
}

static SDL_Wrapper* GetScreenController() {
    return ScreenController;
}

static XML_Wrapper* GetSettings() {
    return Settings;
}

Global global;