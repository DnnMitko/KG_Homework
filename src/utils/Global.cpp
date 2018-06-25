#include "Global.h"

XML_Wrapper* Global::Settings = NULL;
SDL_Wrapper* Global::ScreenController = NULL;

Global::Global() {
    Init();
}

Global::~Global() {
    Deinit();
}

void Global::Init() {
    Settings = new XML_Wrapper();
    ScreenController = new SDL_Wrapper( Settings );
}

void Global::Deinit() {
    delete ScreenController;
    ScreenController = NULL;

    delete Settings;
    Settings = NULL;
}

SDL_Wrapper* Global::GetScreenController() {
    return ScreenController;
}

XML_Wrapper* Global::GetSettings() {
    return Settings;
}

Global global;