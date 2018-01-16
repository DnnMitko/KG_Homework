#ifndef __TEXTFIELD_H__
#define __TEXTFIELD_H__

#include "Label.h"

class TextField : public Label {
public:
    TextField();
    virtual ~TextField();
public:
    void Init( SDL_Renderer* );

    int GetWidth() const;
    int GetHeight() const;
    
    void SetX( int );
    void SetY( int );
    
    virtual void Draw();

    virtual void SetText( std::string, TTF_Font*, SDL_Color );

    void SetFieldSize( int, int );
protected:
    SDL_Rect m_FieldRect;
};

#endif //__TEXTFIELD_H__
