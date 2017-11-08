#include "Interface.h"

void Interface::CreateButtons()
{
    m_ButtonGridInitial = new Button();
    m_ButtonGridVerySmall = new Button();
    m_ButtonGridSmall = new Button();
    m_ButtonGridMedium = new Button();
    m_ButtonGridLarge = new Button();
    m_ButtonGridVeryLarge = new Button();
    m_ButtonDraw = new Button();

    m_ButtonGridInitial->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridVerySmall->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridSmall->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridMedium->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridLarge->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridVeryLarge->Init( m_xmlConstants, m_Renderer );
    m_ButtonDraw->Init( m_xmlConstants, m_Renderer );

    std::string sFont = m_xmlConstants->first_child().child( "Button" ).child( "Font" ).text().as_string();
    int iFont = m_xmlConstants->first_child().child( "Button" ).child( "FontSize" ).text().as_int();
    TTF_Font* font = TTF_OpenFont( sFont.c_str(), iFont );

    m_ButtonGridInitial->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Initial" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridVerySmall->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "VerySmall" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridSmall->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Small" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridMedium->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Medium" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridLarge->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Large" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridVeryLarge->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "VeryLarge" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonDraw->SetText( "Line", font, {0x00, 0x00, 0x00, 0xFF} );

    TTF_CloseFont( font );

    PositionButtons();
}

void Interface::PositionButtons()
{
    int iGridWidth = m_xmlConstants->first_child().child( "Button" ).child( "GridWidth" ).text().as_int();
    int iGridHeight = m_xmlConstants->first_child().child( "Button" ).child( "GridHeight" ).text().as_int();
    m_ButtonGridInitial->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonGridVerySmall->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonGridSmall->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonGridMedium->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonGridLarge->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonGridVeryLarge->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonDraw->SetFieldSize( iGridWidth, iGridHeight );

    int iGridX = m_xmlConstants->first_child().child( "Button" ).child( "GridX" ).text().as_int();
    m_ButtonGridInitial->SetX( iGridX );
    m_ButtonGridVerySmall->SetX( iGridX );
    m_ButtonGridSmall->SetX( iGridX );
    m_ButtonGridMedium->SetX( iGridX );
    m_ButtonGridLarge->SetX( iGridX );
    m_ButtonGridVeryLarge->SetX( iGridX );
    m_ButtonDraw->SetX( iGridX );

    int iGridY = m_xmlConstants->first_child().child( "Button" ).child( "GridY" ).text().as_int();
    m_ButtonGridInitial->SetY( iGridY );
    m_ButtonGridVerySmall->SetY( iGridY + iGridWidth );
    m_ButtonGridSmall->SetY( iGridY + 2 * iGridWidth );
    m_ButtonGridMedium->SetY( iGridY + 3 * iGridWidth );
    m_ButtonGridLarge->SetY( iGridY + 4 * iGridWidth );
    m_ButtonGridVeryLarge->SetY( iGridY + 5 * iGridWidth );
    m_ButtonDraw->SetY( iGridY + 6 * iGridWidth );
}

bool Interface::ButtonEvents( SDL_Event& e )
{
    bool bEventFound = false;

    int x, y;

    if( e.type == SDL_MOUSEBUTTONDOWN )
    {
        SDL_GetMouseState( &x, &y );

        if( m_ButtonGridInitial->IsIn( x, y ) )
        {
            m_ButtonGridInitial->Press();
            bEventFound = true;
        }
        else if( m_ButtonGridVerySmall->IsIn( x, y ) )
        {
            m_ButtonGridVerySmall->Press();
            bEventFound = true;
        }
        else if( m_ButtonGridSmall->IsIn( x, y ) )
        {
            m_ButtonGridSmall->Press();
            bEventFound = true;
        }
        else if( m_ButtonGridMedium->IsIn( x, y ) )
        {
            m_ButtonGridMedium->Press();
            bEventFound = true;
        }
        else if( m_ButtonGridLarge->IsIn( x, y ) )
        {
            m_ButtonGridLarge->Press();
            bEventFound = true;
        }
        else if( m_ButtonGridVeryLarge->IsIn( x, y ) )
        {
            m_ButtonGridVeryLarge->Press();
            bEventFound = true;
        }
        else if( m_ButtonDraw->IsIn( x, y ) )
        {
            m_ButtonDraw->Press();
            bEventFound = true;
        }
    }
    else if(e.type == SDL_MOUSEBUTTONUP)
    {
        SDL_GetMouseState( &x, &y );

        if( m_ButtonGridInitial->IsIn( x, y ) && m_ButtonGridInitial->IsPressed() )
        {
            m_pGrid->SetGridScale( "Initial" );

            bEventFound = true;
        }
        else if( m_ButtonGridVerySmall->IsIn( x, y ) && m_ButtonGridVerySmall->IsPressed() )
        {
            m_pGrid->SetGridScale( "VerySmall" );

            bEventFound = true;
        }
        else if( m_ButtonGridSmall->IsIn( x, y ) && m_ButtonGridSmall->IsPressed() )
        {
            m_pGrid->SetGridScale( "Small" );

            bEventFound = true;
        }
        else if( m_ButtonGridMedium->IsIn( x, y ) && m_ButtonGridMedium->IsPressed() )
        {
            m_pGrid->SetGridScale( "Medium" );

            bEventFound = true;
        }
        else if( m_ButtonGridLarge->IsIn( x, y ) && m_ButtonGridLarge->IsPressed() )
        {
            m_pGrid->SetGridScale( "Large" );

            bEventFound = true;
        }
        else if( m_ButtonGridVeryLarge->IsIn( x, y ) && m_ButtonGridVeryLarge->IsPressed() )
        {
            m_pGrid->SetGridScale( "VeryLarge" );

            bEventFound = true;
        }
        else if( m_ButtonDraw->IsIn( x, y ) && m_ButtonDraw->IsPressed() )
        {
            m_pGrid->ToggleDrawBresenham();

            bEventFound = true;
        }

        ReleaseButtons();
    }

    return bEventFound;
}

void Interface::ReleaseButtons()
{
    m_ButtonGridInitial->Release();
    m_ButtonGridVerySmall->Release();
    m_ButtonGridSmall->Release();
    m_ButtonGridMedium->Release();
    m_ButtonGridLarge->Release();
    m_ButtonGridVeryLarge->Release();
    m_ButtonDraw->Release();
}

void Interface::DrawButtons()
{
    m_ButtonGridInitial->Draw();
    m_ButtonGridVerySmall->Draw();
    m_ButtonGridSmall->Draw();
    m_ButtonGridMedium->Draw();
    m_ButtonGridLarge->Draw();
    m_ButtonGridVeryLarge->Draw();
    m_ButtonDraw->Draw();
}

void Interface::DeleteButtons()
{
    delete m_ButtonGridInitial;
    delete m_ButtonGridVerySmall;
    delete m_ButtonGridSmall;
    delete m_ButtonGridMedium;
    delete m_ButtonGridLarge;
    delete m_ButtonGridVeryLarge;
    delete m_ButtonDraw;

    m_ButtonGridInitial = NULL;
    m_ButtonGridVerySmall = NULL;
    m_ButtonGridSmall = NULL;
    m_ButtonGridMedium = NULL;
    m_ButtonGridLarge = NULL;
    m_ButtonGridVeryLarge = NULL;
    m_ButtonDraw = NULL;
}