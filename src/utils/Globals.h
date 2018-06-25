#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "SDL/SDL_Wrapper.h"
#include "pugixml/XML_Wrapper.h"

class Global {
public:
    Global();
    ~Global();
public:
    static XML_Wrapper* GetSettings();
    static SDL_Wrapper* GetScreenController();
private:
    void Init();
    void Deinit();
private:
    static XML_Wrapper* Settings;
    static SDL_Wrapper* ScreenController;
};

extern Global global;

#endif //__GLOBAL_H__