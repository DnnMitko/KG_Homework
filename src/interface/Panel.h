#ifndef __PANEL_H__
#define __PANEL_H__

#include "Button.h"

#include "../grid/Grid.h"

class Panel {
public:
    Panel();
    ~Panel();
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
    Grid* grid;

    TTF_Font* font;
    TextField* textFieldTitle;

    // Left side
    Button* m_ButtonGridInitial;
    Button* m_ButtonGridVerySmall;
    Button* m_ButtonGridSmall;
    Button* m_ButtonGridMedium;
    Button* m_ButtonGridLarge;
    Button* m_ButtonGridVeryLarge;

    // Right side
    Button* m_ButtonStateBresenham;
    Button* m_ButtonBresenhamDrawType;
    Button* m_ButtonStateMichener;
    Button* m_ButtonStateBoundryFill;
    Button* m_ButtonStateLiangBarsky;
    Button* m_ButtonStateSpline;
    Button* m_ButtonStateClear;
};

#endif //__PANEL_H__