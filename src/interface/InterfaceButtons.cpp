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
    m_ButtonStateBresenham = new Button();
    m_ButtonStateTemp2 = new Button();
    m_ButtonStateTemp3 = new Button();
    m_ButtonStateTemp4 = new Button();
    m_ButtonStateTemp5 = new Button();
    m_ButtonStateTemp6 = new Button();
    m_ButtonStateClear = new Button();

    // Left side
    m_ButtonGridInitial->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridVerySmall->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridSmall->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridMedium->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridLarge->Init( m_xmlConstants, m_Renderer );
    m_ButtonGridVeryLarge->Init( m_xmlConstants, m_Renderer );
    m_ButtonDraw->Init( m_xmlConstants, m_Renderer );

    //Right side
    m_ButtonStateBresenham->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp2->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp3->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp4->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp5->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateTemp6->Init( m_xmlConstants, m_Renderer );
    m_ButtonStateClear->Init( m_xmlConstants, m_Renderer );

    // Left side
    m_ButtonGridInitial->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Initial" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridVerySmall->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "VerySmall" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridSmall->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Small" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridMedium->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Medium" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridLarge->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "Large" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonGridVeryLarge->SetText( m_xmlConstants->first_child().child( "GridScale" ).child( "VeryLarge" ).text().as_string(), m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonDraw->SetText( "> > >", m_Font, {0x00, 0x00, 0x00, 0xFF} );

    // Right side
    m_ButtonStateBresenham->SetText( "B", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp2->SetText( "X", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp3->SetText( "X", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp4->SetText( "X", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp5->SetText( "X", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateTemp6->SetText( "X", m_Font, {0x00, 0x00, 0x00, 0xFF} );
    m_ButtonStateClear->SetText( "Clear", m_Font, {0x00, 0x00, 0x00, 0xFF} );

    PositionButtons();
}

void Interface::PositionButtons()
{
    int iWidth = m_xmlConstants->first_child().child( "Button" ).child( "Width" ).text().as_int();
    int iHeight = m_xmlConstants->first_child().child( "Button" ).child( "Height" ).text().as_int();

    // Left side
    m_ButtonGridInitial->SetFieldSize( iWidth, iHeight );
    m_ButtonGridVerySmall->SetFieldSize( iWidth, iHeight );
    m_ButtonGridSmall->SetFieldSize( iWidth, iHeight );
    m_ButtonGridMedium->SetFieldSize( iWidth, iHeight );
    m_ButtonGridLarge->SetFieldSize( iWidth, iHeight );
    m_ButtonGridVeryLarge->SetFieldSize( iWidth, iHeight );
    m_ButtonDraw->SetFieldSize( iWidth, iHeight );

    // Right side
    m_ButtonStateBresenham->SetFieldSize( iWidth, iHeight );
    m_ButtonStateTemp2->SetFieldSize( iWidth, iHeight );
    m_ButtonStateTemp3->SetFieldSize( iWidth, iHeight );
    m_ButtonStateTemp4->SetFieldSize( iWidth, iHeight );
    m_ButtonStateTemp5->SetFieldSize( iWidth, iHeight );
    m_ButtonStateTemp6->SetFieldSize( iWidth, iHeight );
    m_ButtonStateClear->SetFieldSize( iWidth, iHeight );

    // Left side
    int iOffsetX = m_xmlConstants->first_child().child( "Button" ).child( "OffsetX" ).text().as_int();
    m_ButtonGridInitial->SetX( iOffsetX );
    m_ButtonGridVerySmall->SetX( iOffsetX );
    m_ButtonGridSmall->SetX( iOffsetX );
    m_ButtonGridMedium->SetX( iOffsetX );
    m_ButtonGridLarge->SetX( iOffsetX );
    m_ButtonGridVeryLarge->SetX( iOffsetX );
    m_ButtonDraw->SetX( iOffsetX );

    // Right side
    iOffsetX = m_xmlConstants->first_child().child( "ScreenWidth" ).text().as_int() - iOffsetX - iWidth;
    m_ButtonStateBresenham->SetX( iOffsetX );
    m_ButtonStateTemp2->SetX( iOffsetX );
    m_ButtonStateTemp3->SetX( iOffsetX );
    m_ButtonStateTemp4->SetX( iOffsetX );
    m_ButtonStateTemp5->SetX( iOffsetX );
    m_ButtonStateTemp6->SetX( iOffsetX );
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
    m_ButtonDraw->SetY( iOffsetY + 6 * ( iHeight + iPaddingY ) );

    // Right side
    m_ButtonStateBresenham->SetY( iOffsetY );
    m_ButtonStateTemp2->SetY( iOffsetY + ( iHeight + iPaddingY ) );
    m_ButtonStateTemp3->SetY( iOffsetY + 2 * ( iHeight + iPaddingY ) );
    m_ButtonStateTemp4->SetY( iOffsetY + 3 * ( iHeight + iPaddingY ) );
    m_ButtonStateTemp5->SetY( iOffsetY + 4 * ( iHeight + iPaddingY ) );
    m_ButtonStateTemp6->SetY( iOffsetY + 5 * ( iHeight + iPaddingY ) );
    m_ButtonStateClear->SetY( iOffsetY + 6 * ( iHeight + iPaddingY ) );
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
        else if( m_ButtonStateBresenham->IsIn( x, y ) )
        {
            m_ButtonStateBresenham->Press();
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
        else if( m_ButtonStateClear->IsIn( x, y ) )
        {
            m_ButtonStateClear->Press();
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
            if( m_pGrid->ToggleDrawBresenham() )
            {
                m_ButtonDraw->SetText( "> > >", m_Font, {0x00, 0x00, 0x00, 0xFF} );
            }
            else
            {
                m_ButtonDraw->SetText( ">> <<", m_Font, {0x00, 0x00, 0x00, 0xFF} );
            }

            bEventFound = true;
        }
        else if( m_ButtonStateBresenham->IsIn( x, y ) && m_ButtonStateBresenham->IsPressed() )
        {
            m_pGrid->SetState( Grid::Bresenham );

            m_TextFieldTitle->SetText( "Bresenham", m_Font, {0xFF, 0xFF, 0xFF, 0xFF} );

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
        else if( m_ButtonStateClear->IsIn( x, y ) && m_ButtonStateClear->IsPressed() )
        {
            m_pGrid->ClearGrid();
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
    m_ButtonStateBresenham->Release();
    m_ButtonStateTemp2->Release();
    m_ButtonStateTemp3->Release();
    m_ButtonStateTemp4->Release();
    m_ButtonStateTemp5->Release();
    m_ButtonStateTemp6->Release();
    m_ButtonStateClear->Release();
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
    m_ButtonStateBresenham->Draw();
    m_ButtonStateTemp2->Draw();
    m_ButtonStateTemp3->Draw();
    m_ButtonStateTemp4->Draw();
    m_ButtonStateTemp5->Draw();
    m_ButtonStateTemp6->Draw();
    m_ButtonStateClear->Draw();
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
    delete m_ButtonStateBresenham;
    delete m_ButtonStateTemp2;
    delete m_ButtonStateTemp3;
    delete m_ButtonStateTemp4;
    delete m_ButtonStateTemp5;
    delete m_ButtonStateTemp6;
    delete m_ButtonStateClear;


    m_ButtonStateBresenham = NULL;
    m_ButtonStateTemp2 = NULL;
    m_ButtonStateTemp3 = NULL;
    m_ButtonStateTemp4 = NULL;
    m_ButtonStateTemp5 = NULL;
    m_ButtonStateTemp6 = NULL;
    m_ButtonStateClear = NULL;
}