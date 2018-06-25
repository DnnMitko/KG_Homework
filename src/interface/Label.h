#ifndef __LABEL_H__
#define __LABEL_H__

#include "../utils/Global.h"
#include <string>

class Label {
public:
    Label();
    virtual ~Label();
public:
    virtual int GetWidth() const;
    virtual int GetHeight() const;

    virtual void SetX( int );
    virtual void SetY( int );

    virtual void Draw();

    virtual void SetText( std::string, TTF_Font*, SDL_Color );
private:
    virtual void Init();
    virtual void Deinit();
protected:
    SDL_Rect textRect;
    SDL_Texture* textTexture;

    bool hasChanged;
};

#endif //__LABEL_H__