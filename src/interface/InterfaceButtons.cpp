#include "Interface.h"

bool Interface::ButtonEvents( SDL_Event& e ) {
    bool bEventFound = false;

    int x, y;

    if( e.type == SDL_MOUSEBUTTONDOWN ) {
        SDL_GetMouseState( &x, &y );

        if( m_ButtonGridInitial->IsIn( x, y ) ) {
            m_ButtonGridInitial->Press();
            bEventFound = true;
        }
        else if( m_ButtonGridVerySmall->IsIn( x, y ) ) {
            m_ButtonGridVerySmall->Press();
            bEventFound = true;
        }
        else if( m_ButtonGridSmall->IsIn( x, y ) ) {
            m_ButtonGridSmall->Press();
            bEventFound = true;
        }
        else if( m_ButtonGridMedium->IsIn( x, y ) ) {
            m_ButtonGridMedium->Press();
            bEventFound = true;
        }
        else if( m_ButtonGridLarge->IsIn( x, y ) ) {
            m_ButtonGridLarge->Press();
            bEventFound = true;
        }
        else if( m_ButtonGridVeryLarge->IsIn( x, y ) ) {
            m_ButtonGridVeryLarge->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateBresenham->IsIn( x, y ) ) {
            m_ButtonStateBresenham->Press();
            bEventFound = true;
        }
        else if( m_ButtonDraw->IsIn( x, y ) ) {
            m_ButtonDraw->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateMichener->IsIn( x, y ) ) {
            m_ButtonStateMichener->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateBoundryFill->IsIn( x, y ) ) {
            m_ButtonStateBoundryFill->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateLiang_Barsky->IsIn( x, y ) ) {
            m_ButtonStateLiang_Barsky->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateSpline->IsIn( x, y ) ) {
            m_ButtonStateSpline->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateClear->IsIn( x, y ) ) {
            m_ButtonStateClear->Press();
            bEventFound = true;
        }
    }
    else if(e.type == SDL_MOUSEBUTTONUP) {
        SDL_GetMouseState( &x, &y );

        if( m_ButtonGridInitial->IsIn( x, y ) && m_ButtonGridInitial->IsPressed() ) {
            m_pGrid->SetGridScale( "Initial" );

            bEventFound = true;
        }
        else if( m_ButtonGridVerySmall->IsIn( x, y ) && m_ButtonGridVerySmall->IsPressed() ) {
            m_pGrid->SetGridScale( "VerySmall" );

            bEventFound = true;
        }
        else if( m_ButtonGridSmall->IsIn( x, y ) && m_ButtonGridSmall->IsPressed() ) {
            m_pGrid->SetGridScale( "Small" );

            bEventFound = true;
        }
        else if( m_ButtonGridMedium->IsIn( x, y ) && m_ButtonGridMedium->IsPressed() ) {
            m_pGrid->SetGridScale( "Medium" );

            bEventFound = true;
        }
        else if( m_ButtonGridLarge->IsIn( x, y ) && m_ButtonGridLarge->IsPressed() ) {
            m_pGrid->SetGridScale( "Large" );

            bEventFound = true;
        }
        else if( m_ButtonGridVeryLarge->IsIn( x, y ) && m_ButtonGridVeryLarge->IsPressed() ) {
            m_pGrid->SetGridScale( "VeryLarge" );

            bEventFound = true;
        }
        else if( m_ButtonStateBresenham->IsIn( x, y ) && m_ButtonStateBresenham->IsPressed() ) {
            m_pGrid->SetState( Grid::Bresenham );

            m_TextFieldTitle->SetText( "Bresenham", m_Font, {0xFF, 0xFF, 0xFF, 0xFF} );

            m_ButtonDraw->Enable();

            m_ButtonGridInitial->Enable();
            m_ButtonGridVerySmall->Enable();
            m_ButtonGridSmall->Enable();
            m_ButtonGridMedium->Enable();
            m_ButtonGridLarge->Enable();
            m_ButtonGridVeryLarge->Enable();

            bEventFound = true;
        }
        else if( m_ButtonDraw->IsIn( x, y ) && m_ButtonDraw->IsPressed() ) {
            if( m_pGrid->ToggleDrawBresenham() ) {
                m_ButtonDraw->SetText( "> > >", m_Font, {0x00, 0x00, 0x00, 0xFF} );
            }
            else {
                m_ButtonDraw->SetText( ">> <<", m_Font, {0x00, 0x00, 0x00, 0xFF} );
            }

            bEventFound = true;
        }
        else if( m_ButtonStateMichener->IsIn( x, y ) && m_ButtonStateMichener->IsPressed() ) {
            m_pGrid->SetState( Grid::Michener );

            m_TextFieldTitle->SetText( "Michener", m_Font, {0xFF, 0xFF, 0xFF, 0xFF} );

            m_ButtonDraw->Disable();

            m_ButtonGridInitial->Enable();
            m_ButtonGridVerySmall->Enable();
            m_ButtonGridSmall->Enable();
            m_ButtonGridMedium->Enable();
            m_ButtonGridLarge->Enable();
            m_ButtonGridVeryLarge->Enable();

            bEventFound = true;
        }
        else if( m_ButtonStateBoundryFill->IsIn( x, y ) && m_ButtonStateBoundryFill->IsPressed() ) {
            m_pGrid->SetGridScale( "Small" );
            
            m_pGrid->SetState( Grid::BoundryFill );

            m_TextFieldTitle->SetText( "Boundry Fill", m_Font, {0xFF, 0xFF, 0xFF, 0xFF} );

            m_ButtonDraw->Disable();

            m_ButtonGridInitial->Disable();
            m_ButtonGridVerySmall->Disable();
            m_ButtonGridSmall->Disable();
            m_ButtonGridMedium->Disable();
            m_ButtonGridLarge->Disable();
            m_ButtonGridVeryLarge->Disable();

            bEventFound = true;
        }
        else if( m_ButtonStateLiang_Barsky->IsIn( x, y ) && m_ButtonStateLiang_Barsky->IsPressed() ) {
            m_pGrid->SetGridScale( "Initial" );

            m_pGrid->SetState( Grid::Liang_Barsky );

            m_TextFieldTitle->SetText( "Liang-Barsky", m_Font, {0xFF, 0xFF, 0xFF, 0xFF} );

            m_ButtonDraw->Disable();

            m_ButtonGridInitial->Disable();
            m_ButtonGridVerySmall->Disable();
            m_ButtonGridSmall->Disable();
            m_ButtonGridMedium->Disable();
            m_ButtonGridLarge->Disable();
            m_ButtonGridVeryLarge->Disable();
            
            bEventFound = true;
        }
        else if( m_ButtonStateSpline->IsIn( x, y ) && m_ButtonStateSpline->IsPressed() ) {
            m_pGrid->SetGridScale( "Initial" );

            m_pGrid->SetState( Grid::Spline );

            m_TextFieldTitle->SetText( "Cubic Spline", m_Font, {0xFF, 0xFF, 0xFF, 0xFF} );

            m_ButtonDraw->Disable();

            m_ButtonGridInitial->Disable();
            m_ButtonGridVerySmall->Disable();
            m_ButtonGridSmall->Disable();
            m_ButtonGridMedium->Disable();
            m_ButtonGridLarge->Disable();
            m_ButtonGridVeryLarge->Disable();
            
            bEventFound = true;
        }
        else if( m_ButtonStateClear->IsIn( x, y ) && m_ButtonStateClear->IsPressed() ) {
            m_pGrid->ClearGrid();
            bEventFound = true;
        }

        ReleaseButtons();
    }

    return bEventFound;
}