#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "Button.h"

#include "Grid.h"

#include "Settings.h"
#include "ScreenController.h"

class Interface {
public:
    Interface();
    ~Interface();
public:
    void EventHandler( SDL_Event& );
    void ReleaseButtons();
    void Draw();
private:
    void Init();
    void OpenFont();
    void CreateTitle();
    void CreateButtons();
    void PositionButtons();

    void Deinit();
    void DestroyButtons();

    void DrawButtons();
private:
    Settings settings;
    ScreenController screenController;

    Grid* grid;

    TTF_Font* font;
    TextField* textFieldTitle;

    // Left side
    Button* buttonGridInitial;
    Button* buttonGridVerySmall;
    Button* buttonGridSmall;
    Button* buttonGridMedium;
    Button* buttonGridLarge;
    Button* buttonGridVeryLarge;

    // Right side
    Button* buttonStateBresenham;
    Button* buttonBresenhamDrawType;
    Button* buttonStateMichener;
    Button* buttonStateBoundryFill;
    Button* buttonStateLiangBarsky;
    Button* buttonStateSpline;
    Button* buttonStateClear;
};

#endif //__INTERFACE_H__