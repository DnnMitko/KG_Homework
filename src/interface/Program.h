#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "ScreenController.h"

#include "Interface.h"

class Program {
public:
    Program();
    ~Program();
public:
    void EventHandler( SDL_Event& );
    bool GetQuit() const;
    void Draw();
private:
    void Init();
    void DeInit();
private:
    bool readyToQuit;

    ScreenController screenController;

    Interface* interface;
};

#endif //__PROGRAM_H__