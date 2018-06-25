#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "TextField.h"
#include "ScreenController.h"
#include "Settings.h"

class Button: public TextField {
public:
    Button();
    virtual ~Button();
public:
    void Draw();

    void SetText( std::string, TTF_Font*, SDL_Color );

    bool IsIn( int, int ) const;

    void Enable();
    void Disable();

    void Press();
    void Release();

    bool IsPressed() const;
private:
    void Init();
    void Deinit();
private:
    // ScreenController screenController;
    Settings settings;

    bool isPressed;
    bool isEnabled;

    SDL_Texture* textTexturePressed;
    static SDL_Texture* buttonTexture;
};

#endif //__BUTTON_H__