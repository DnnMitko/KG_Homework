#ifndef __TEXTFIELD_H__
#define __TEXTFIELD_H__

#include "Label.h"

class TextField : public Label {
public:
    TextField();
    virtual ~TextField();
public:
    int GetWidth() const;
    int GetHeight() const;

    void SetX( int );
    void SetY( int );

    virtual void SetText( std::string, TTF_Font*, SDL_Color );
    void SetFieldSize( int, int );

    virtual void Draw();
private:
    virtual void Init();
    virtual void Deinit();

    void CalculateTextPosition();
protected:
    SDL_Rect fieldRect;
};

#endif //__TEXTFIELD_H__
