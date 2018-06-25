#include "Interface.h"

#include "ScreenController.h"

int main( int argc, char* args[] ) {
    // Used to avoid them listed as unused variables
    (void) argc;
    (void) args;

    Interface program;
    ScreenController screen;

    SDL_Event event;

    while( false == program.GetQuit() ) {
        while( screen.getInstance()->PollEvents( &event ) != 0 ) {
            program.EventHandler( event );
        }

        program.Draw();
    }

    return 0;
}