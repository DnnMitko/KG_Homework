#include "interface/Interface.h"

void unused(int, char**);

int main( int argc, char* args[] )
{
    unused(argc, args);

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

void unused(int argc, char** args)
{
    (void) argc;
    (void) args;
}