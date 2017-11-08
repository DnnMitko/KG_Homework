#include "Interface.h"

void Interface::CreateButtons()
{
    // Left side
    m_ButtonGridInitial = new Button();
    m_ButtonGridVerySmall = new Button();
    m_ButtonGridSmall = new Button();
    m_ButtonGridMedium = new Button();
    m_ButtonGridLarge = new Button();
    m_ButtonGridVeryLarge = new Button();
    m_ButtonDraw = new Button();

    // Right side
    m_ButtonStateTemp1 = new Button();
    m_ButtonStateTemp2 = new Button();
    m_ButtonStateTemp3 = new Button();
    m_ButtonStateTemp4 = new Button();
    m_ButtonStateTemp5 = new Button();
    m_ButtonStateTemp6 = new Button();
    m_ButtonStateTemp7 = new Button();

    // Left side
    m_ButtonGridInitial->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridVerySmall->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridSmall->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridMedium->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridLarge->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridVeryLarge->Init( m_xmlConstants, m_Renderer );
    m_ButtonDraw->Init( m_xmlConstants, m_Renderer );

    //Right side
    m_ButtonStateTemp1->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp2->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp3->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp4->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp5->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp6->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp7->Init( m_xmlConstants, m_Renderer );

    std::string sFont = m_xmlConstants->first_child().child( "Button" ).child( "Font" ).text().as_string();
    int iFont = m_xmlConstants->first_child().child( "Button" ).child( "FontSize" ).text().as_int();
    TTF_Font* font = TTF_OpenFont( sFont.c_str(), iFont );

    // Left side
    m_ButtonGridInitial->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Initial" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridVerySmall->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "VerySmall" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridSmall->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Small" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridMedium->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Medium" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridLarge->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Large" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridVeryLarge->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "VeryLarge" ).text().as_string(), font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonDraw->SetText( "Line", font, {0x00, 0x00, 0x00, 0xFF} );

    // Right side
    m_ButtonStateTemp1->SetText( "NaN", font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp2->SetText( "NaN", font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp3->SetText( "NaN", font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp4->SetText( "NaN", font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp5->SetText( "NaN", font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp6->SetText( "NaN", font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp7->SetText( "NaN", font, {0x00, 0x00, 0x00, 0xFF} );

    TTF_CloseFont( font );

    PositionButtons();
}

void Interface::PositionButtons()
{
    int iGridWidth = m_xmlConstants->first_child().child( "Button" ).child( "GridWidth" ).text().as_int();
    int iGridHeight = m_xmlConstants->first_child().child( "Button" ).child( "GridHeight" ).text().as_int();

    // Left side
    m_ButtonGridInitial->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonGridVerySmall->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonGridSmall->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonGridMedium->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonGridLarge->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonGridVeryLarge->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonDraw->SetFieldSize( iGridWidth, iGridHeight );

    // Right side
    m_ButtonStateTemp1->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonStateTemp2->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonStateTemp3->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonStateTemp4->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonStateTemp5->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonStateTemp6->SetFieldSize( iGridWidth, iGridHeight );
    m_ButtonStateTemp7->SetFieldSize( iGridWidth, iGridHeight );
    
    // Left side
    int iGridX = m_xmlConstants->first_child().child( "Button" ).child( "GridX" ).text().as_int();
    m_ButtonGridInitial->SetX( iGridX );
    m_ButtonGridVerySmall->SetX( iGridX );
    m_ButtonGridSmall->SetX( iGridX );
    m_ButtonGridMedium->SetX( iGridX );
    m_ButtonGridLarge->SetX( iGridX );
    m_ButtonGridVeryLarge->SetX( iGridX );
    m_ButtonDraw->SetX( iGridX );
    
    // Right side
    iGridX = m_xmlConstants->first_child().child( "ScreenWidth" ).text().as_int() - iGridX - iGridWidth;
    m_ButtonStateTemp1->SetX( iGridX );
    m_ButtonStateTemp2->SetX( iGridX );
    m_ButtonStateTemp3->SetX( iGridX );
    m_ButtonStateTemp4->SetX( iGridX );
    m_ButtonStateTemp5->SetX( iGridX );
    m_ButtonStateTemp6->SetX( iGridX );
    m_ButtonStateTemp7->SetX( iGridX );

    // Left side
    int iGridY = m_xmlConstants->first_child().child( "Button" ).child( "GridY" ).text().as_int();
    m_ButtonGridInitial->SetY( iGridY );
    m_ButtonGridVerySmall->SetY( iGridY + iGridHeight );
    m_ButtonGridSmall->SetY( iGridY + 2 * iGridHeight );
    m_ButtonGridMedium->SetY( iGridY + 3 * iGridHeight );
    m_ButtonGridLarge->SetY( iGridY + 4 * iGridHeight );
    m_ButtonGridVeryLarge->SetY( iGridY + 5 * iGridHeight );
    m_ButtonDraw->SetY( iGridY + 6 * iGridHeight );

    // Right side
    m_ButtonStateTemp1->SetY( iGridY );
    m_ButtonStateTemp2->SetY( iGridY + iGridHeight );
    m_ButtonStateTemp3->SetY( iGridY + 2 * iGridHeight );
    m_ButtonStateTemp4->SetY( iGridY + 3 * iGridHeight );
    m_ButtonStateTemp5->SetY( iGridY + 4 * iGridHeight );
    m_ButtonStateTemp6->SetY( iGridY + 5 * iGridHeight );
    m_ButtonStateTemp7->SetY( iGridY + 6 * iGridHeight );
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
        else if( m_ButtonStateTemp1->IsIn( x, y ) )
        {
            m_ButtonStateTemp1->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateTemp2->IsIn( x, y ) )
        {
            m_ButtonStateTemp2->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateTemp3->IsIn( x, y ) )
        {
            m_ButtonStateTemp3->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateTemp4->IsIn( x, y ) )
        {
            m_ButtonStateTemp4->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateTemp5->IsIn( x, y ) )
        {
            m_ButtonStateTemp5->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateTemp6->IsIn( x, y ) )
        {
            m_ButtonStateTemp6->Press();
            bEventFound = true;
        }
        else if( m_ButtonStateTemp7->IsIn( x, y ) )
        {
            m_ButtonStateTemp7->Press();
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
        else if( m_ButtonStateTemp1->IsIn( x, y ) && m_ButtonStateTemp1->IsPressed() )
        {
            //TODO
            bEventFound = true;
        }
        else if( m_ButtonStateTemp2->IsIn( x, y ) && m_ButtonStateTemp2->IsPressed() )
        {
            //TODO
            bEventFound = true;
        }
        else if( m_ButtonStateTemp3->IsIn( x, y ) && m_ButtonStateTemp3->IsPressed() )
        {
            //TODO
            bEventFound = true;
        }
        else if( m_ButtonStateTemp4->IsIn( x, y ) && m_ButtonStateTemp4->IsPressed() )
        {
            //TODO
            bEventFound = true;
        }
        else if( m_ButtonStateTemp5->IsIn( x, y ) && m_ButtonStateTemp5->IsPressed() )
        {
            //TODO
            bEventFound = true;
        }
        else if( m_ButtonStateTemp6->IsIn( x, y ) && m_ButtonStateTemp6->IsPressed() )
        {
            //TODO
            bEventFound = true;
        }
        else if( m_ButtonStateTemp7->IsIn( x, y ) && m_ButtonStateTemp7->IsPressed() )
        {
            //TODO
            bEventFound = true;
        }

        ReleaseButtons();
    }

    return bEventFound;
}

void Interface::ReleaseButtons()
{
    // Left side
    m_ButtonGridInitial->Release();
    m_ButtonGridVerySmall->Release();
    m_ButtonGridSmall->Release();
    m_ButtonGridMedium->Release();
    m_ButtonGridLarge->Release();
    m_ButtonGridVeryLarge->Release();
    m_ButtonDraw->Release();

    // Right side
    m_ButtonStateTemp1->Release();
    m_ButtonStateTemp2->Release();
    m_ButtonStateTemp3->Release();
    m_ButtonStateTemp4->Release();
    m_ButtonStateTemp5->Release();
    m_ButtonStateTemp6->Release();
    m_ButtonStateTemp7->Release();
}

void Interface::DrawButtons()
{
    // Left side
    m_ButtonGridInitial->Draw();
    m_ButtonGridVerySmall->Draw();
    m_ButtonGridSmall->Draw();
    m_ButtonGridMedium->Draw();
    m_ButtonGridLarge->Draw();
    m_ButtonGridVeryLarge->Draw();
    m_ButtonDraw->Draw();

    // Right side
    m_ButtonStateTemp1->Draw();
    m_ButtonStateTemp2->Draw();
    m_ButtonStateTemp3->Draw();
    m_ButtonStateTemp4->Draw();
    m_ButtonStateTemp5->Draw();
    m_ButtonStateTemp6->Draw();
    m_ButtonStateTemp7->Draw();
}

void Interface::DeleteButtons()
{
    // Left side
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

    // Right side
    delete m_ButtonStateTemp1;
    delete m_ButtonStateTemp2;
    delete m_ButtonStateTemp3;
    delete m_ButtonStateTemp4;
    delete m_ButtonStateTemp5;
    delete m_ButtonStateTemp6;
    delete m_ButtonStateTemp7;


    m_ButtonStateTemp1 = NULL;
    m_ButtonStateTemp2 = NULL;
    m_ButtonStateTemp3 = NULL;
    m_ButtonStateTemp4 = NULL;
    m_ButtonStateTemp5 = NULL;
    m_ButtonStateTemp6 = NULL;
    m_ButtonStateTemp7 = NULL;
}