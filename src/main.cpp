#include "interface/Interface.h"

#include "utils/SDL/SDL_Singleton.h"

int main( int argc, char* args[] ) {
    // Used to avoid them listed as unused variables
    (void) argc;
    (void) args;

    Interface program;
    SDL_Singleton screen;

    SDL_Event e;

    while( false == program.GetQuit() ) {
        while( screen.getScreenController()->PollEvents( &e ) != 0 ) {
            program.EventHandler( e );
        }

        program.Draw();
    }

    return 0;
}