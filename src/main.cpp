#include "interface/Interface.h"

int main( int argc, char* args[] )
{
    Interface controller;

    SDL_Event e;

    while( !controller.GetQuit() )
    {
        while( SDL_PollEvent( &e ) != 0 )
        {
            controller.EventHandler( e );
        }

        controller.Draw();
    }

    return 0;
}