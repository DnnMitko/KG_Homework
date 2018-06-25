#include "interface/Interface.h"

#include "utils/pugixml/XML_Wrapper.h"
#include "utils/SDL/SDL_Wrapper.h"

XML_Wrapper Settings;
SDL_Wrapper ScreenController;

int main( int argc, char* args[] ) {
    // Used to avoid them listed as unused variables
    (void) argc;
    (void) args;

    Interface program;

    SDL_Event e;

    while( false == program.GetQuit() ) {
        while( ScreenController.PollEvents( &e ) != 0 ) {
            program.EventHandler( e );
        }

        program.Draw();
    }

    return 0;
}