#include "Interface.h"

void Interface::CreateButtons() {
    // Left side
    m_ButtonGridInitial = new Button();
    m_ButtonGridVerySmall = new Button();
    m_ButtonGridSmall = new Button();
    m_ButtonGridMedium = new Button();
    m_ButtonGridLarge = new Button();
    m_ButtonGridVeryLarge = new Button();

    // Right side
    m_ButtonStateBresenham = new Button();
    m_ButtonDraw = new Button();
    m_ButtonStateMichener = new Button();
    m_ButtonStateBoundryFill = new Button();
    m_ButtonStateLiang_Barsky = new Button();
    m_ButtonStateSpline = new Button();
    m_ButtonStateClear = new Button();

    // Left side
    m_ButtonGridInitial->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridVerySmall->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridSmall->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridMedium->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridLarge->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridVeryLarge->Init( m_xmlConstants, m_Renderer );

    //Right side
    m_ButtonStateBresenham->Init( m_xmlConstants, m_Renderer );
    m_ButtonDraw->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateMichener->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateBoundryFill->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateLiang_Barsky->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateSpline->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateClear->Init( m_xmlConstants, m_Renderer );

    // Left side
    m_ButtonGridInitial->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Initial" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridVerySmall->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "VerySmall" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridSmall->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Small" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridMedium->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Medium" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridLarge->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Large" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridVeryLarge->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "VeryLarge" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );

    // Right side
    m_ButtonStateBresenham->SetText( "B", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonDraw->SetText( "> > >", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateMichener->SetText( "M", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateBoundryFill->SetText( "B F", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateLiang_Barsky ->SetText( "L B", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateSpline->SetText( "S", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateClear->SetText( "Clear", m_Font, {0x00, 0x00, 0x00, 0xFF} );

    PositionButtons();
}

void Interface::PositionButtons() {
    int iWidth = m_xmlConstants->first_child().child( "Button" ).child( "Width" ).text().as_int();
    int iHeight = m_xmlConstants->first_child().child( "Button" ).child( "Height" ).text().as_int();

    // Left side
    m_ButtonGridInitial->SetFieldSize( iWidth, iHeight );
    m_ButtonGridVerySmall->SetFieldSize( iWidth, iHeight );
    m_ButtonGridSmall->SetFieldSize( iWidth, iHeight );
    m_ButtonGridMedium->SetFieldSize( iWidth, iHeight );
    m_ButtonGridLarge->SetFieldSize( iWidth, iHeight );
    m_ButtonGridVeryLarge->SetFieldSize( iWidth, iHeight );

    // Right side
    m_ButtonStateBresenham->SetFieldSize( iWidth, iHeight );
    m_ButtonDraw->SetFieldSize( iWidth, iHeight );
    m_ButtonStateMichener->SetFieldSize( iWidth, iHeight );
    m_ButtonStateBoundryFill->SetFieldSize( iWidth, iHeight );
    m_ButtonStateLiang_Barsky->SetFieldSize( iWidth, iHeight );
    m_ButtonStateSpline->SetFieldSize( iWidth, iHeight );
    m_ButtonStateClear->SetFieldSize( iWidth, iHeight );

    // Left side
    int iOffsetX = m_xmlConstants->first_child().child( "Button" ).child( "OffsetX" ).text().as_int();
    m_ButtonGridInitial->SetX( iOffsetX );
    m_ButtonGridVerySmall->SetX( iOffsetX );
    m_ButtonGridSmall->SetX( iOffsetX );
    m_ButtonGridMedium->SetX( iOffsetX );
    m_ButtonGridLarge->SetX( iOffsetX );
    m_ButtonGridVeryLarge->SetX( iOffsetX );

    // Right side
    iOffsetX = m_xmlConstants->first_child().child( "ScreenWidth" ).text().as_int() - iOffsetX - iWidth;
    m_ButtonStateBresenham->SetX( iOffsetX );
    m_ButtonDraw->SetX( iOffsetX );
    m_ButtonStateMichener->SetX( iOffsetX );
    m_ButtonStateBoundryFill->SetX( iOffsetX );
    m_ButtonStateLiang_Barsky->SetX( iOffsetX );
    m_ButtonStateSpline->SetX( iOffsetX );
    m_ButtonStateClear->SetX( iOffsetX );

    // Left side
    int iOffsetY = m_xmlConstants->first_child().child( "Button" ).child( "OffsetY" ).text().as_int();
    int iPaddingY = m_xmlConstants->first_child().child( "Button" ).child( "PaddingY" ).text().as_int();
    m_ButtonGridInitial->SetY( iOffsetY );
    m_ButtonGridVerySmall->SetY( iOffsetY + ( iHeight + iPaddingY ) );
    m_ButtonGridSmall->SetY( iOffsetY + 2 * ( iHeight + iPaddingY ) );
    m_ButtonGridMedium->SetY( iOffsetY + 3 * ( iHeight + iPaddingY ) );
    m_ButtonGridLarge->SetY( iOffsetY + 4 * ( iHeight + iPaddingY ) );
    m_ButtonGridVeryLarge->SetY( iOffsetY + 5 * ( iHeight + iPaddingY ) );

    // Right side
    m_ButtonStateBresenham->SetY( iOffsetY );
    m_ButtonDraw->SetY( iOffsetY + ( iHeight + iPaddingY ) );
    m_ButtonStateMichener->SetY( iOffsetY + 2 * ( iHeight + iPaddingY ) );
    m_ButtonStateBoundryFill->SetY( iOffsetY + 3 * ( iHeight + iPaddingY ) );
    m_ButtonStateLiang_Barsky->SetY( iOffsetY + 4 * ( iHeight + iPaddingY ) );
    m_ButtonStateSpline->SetY( iOffsetY + 5 * ( iHeight + iPaddingY ) );
    m_ButtonStateClear->SetY( iOffsetY + 6 * ( iHeight + iPaddingY ) );
}

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

void Interface::ReleaseButtons() {
    // Left side
    m_ButtonGridInitial->Release();
    m_ButtonGridVerySmall->Release();
    m_ButtonGridSmall->Release();
    m_ButtonGridMedium->Release();
    m_ButtonGridLarge->Release();
    m_ButtonGridVeryLarge->Release();

    // Right side
    m_ButtonStateBresenham->Release();
    m_ButtonDraw->Release();
    m_ButtonStateMichener->Release();
    m_ButtonStateBoundryFill->Release();
    m_ButtonStateLiang_Barsky->Release();
    m_ButtonStateSpline->Release();
    m_ButtonStateClear->Release();
}

void Interface::DrawButtons() {
    // Left side
    m_ButtonGridInitial->Draw();
    m_ButtonGridVerySmall->Draw();
    m_ButtonGridSmall->Draw();
    m_ButtonGridMedium->Draw();
    m_ButtonGridLarge->Draw();
    m_ButtonGridVeryLarge->Draw();

    // Right side
    m_ButtonStateBresenham->Draw();
    m_ButtonDraw->Draw();
    m_ButtonStateMichener->Draw();
    m_ButtonStateBoundryFill->Draw();
    m_ButtonStateLiang_Barsky->Draw();
    m_ButtonStateSpline->Draw();
    m_ButtonStateClear->Draw();
}

void Interface::DeleteButtons() {
    // Left side
    delete m_ButtonGridInitial;
    delete m_ButtonGridVerySmall;
    delete m_ButtonGridSmall;
    delete m_ButtonGridMedium;
    delete m_ButtonGridLarge;
    delete m_ButtonGridVeryLarge;

    m_ButtonGridInitial = NULL;
    m_ButtonGridVerySmall = NULL;
    m_ButtonGridSmall = NULL;
    m_ButtonGridMedium = NULL;
    m_ButtonGridLarge = NULL;
    m_ButtonGridVeryLarge = NULL;

    // Right side
    delete m_ButtonStateBresenham;
    delete m_ButtonDraw;
    delete m_ButtonStateMichener;
    delete m_ButtonStateBoundryFill;
    delete m_ButtonStateLiang_Barsky;
    delete m_ButtonStateSpline;
    delete m_ButtonStateClear;


    m_ButtonStateBresenham = NULL;
    m_ButtonDraw = NULL;
    m_ButtonStateMichener = NULL;
    m_ButtonStateBoundryFill = NULL;
    m_ButtonStateLiang_Barsky = NULL;
    m_ButtonStateSpline = NULL;
    m_ButtonStateClear = NULL;
}