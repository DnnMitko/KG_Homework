#include "interface/Homework.h"

int main( int argc, char* args[] )
{
    Homework hw;

    SDL_Event e;

    while( !hw.GetQuit() )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            hw.EventHandler( e );
        }

        hw.Draw();
    }

    return 0;
}