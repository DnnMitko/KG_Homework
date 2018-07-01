#include "Program.h"

#include "ScreenController.h"

int main( int argc, char* args[] ) {
    // Used to avoid them listed as unused variables
    (void) argc;
    (void) args;

    Program demo;
    ScreenController screen;

    SDL_Event event;

    while( false == demo.GetQuit() ) {
        while( screen.getInstance()->PollEvents( &event ) != 0 ) {
            demo.EventHandler( event );
        }

        demo.Draw();
    }

    return 0;
}