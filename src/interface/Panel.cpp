#include "Panel.h"

Panel::Panel() {
    Init();
}

Panel::~Panel() {
    Deinit();
}

Panel::Init() {
    grid = new Grid();

    OpenFont();

    CreateTitle();

    CreateButtons();
    PositionButtons();
}

Panel::Deinit() {
    delete grid;
    grid = NULL;

    ScreenController.CloseFont( font );
    font = NULL;

    delete textFieldTitle;
    textFieldTitle = NULL;

    DestroyButtons();
}

void Panel::OpenFont() {
    font = NULL;

    std::string newFont = Settings.ReadString( "Button", "Font" );
    int fontSize = Settings.ReadInt( "Button", "FontSize" );

    font = ScreenController.OpenFont( newFont, fontSize );
}

void Panel::CreateTitle() {
    textFieldTitle = new TextField();

    textFieldTitle->SetText( "Bresenham", font, {0xFF, 0xFF, 0xFF, 0xFF} );

    int screenWidth = Settings.ReadInt( "ScreenWidth" );
    int gridOffsetY = Settings.ReadInt( "GridPos", "y" );
    int titleWidth = Settings.ReadInt( "TitleWidth" );

    textFieldTitle->SetFieldSize( titleWidth, gridOffsetY );
    textFieldTitle->SetX( ( screenWidth - titleWidth ) / 2 );
    textFieldTitle->SetY( 0 );
}

void Panel::CreateButtons() {
    // Left side
    m_ButtonGridInitial = new Button();
    m_ButtonGridVerySmall = new Button();
    m_ButtonGridSmall = new Button();
    m_ButtonGridMedium = new Button();
    m_ButtonGridLarge = new Button();
    m_ButtonGridVeryLarge = new Button();

    // Right side
    m_ButtonStateBresenham = new Button();
    m_ButtonBresenhamDrawType = new Button();
    m_ButtonStateMichener = new Button();
    m_ButtonStateBoundryFill = new Button();
    m_ButtonStateLiangBarsky = new Button();
    m_ButtonStateSpline = new Button();
    m_ButtonStateClear = new Button();

    SDL_Color color = {0x00, 0x00, 0x00, 0xFF};
    // Left side
    m_ButtonGridInitial->SetText( Settings.ReadString( "GridScale", "Initial" ), font, color );
    m_ButtonGridVerySmall->SetText( Settings.ReadString( "GridScale", "VerySmall" ), font, color );
    m_ButtonGridSmall->SetText( Settings.ReadString( "GridScale", "Small" ), font, color );
    m_ButtonGridMedium->SetText( Settings.ReadString( "GridScale", "Medium" ), font, color );
    m_ButtonGridLarge->SetText( Settings.ReadString( "GridScale", "Large" ), font, color );
    m_ButtonGridVeryLarge->SetText( Settings.ReadString( "GridScale", "VeryLarge" ), font, color );

    Settings.ReadString( "Button", "Clear" )
    // Right side
    m_ButtonStateBresenham->SetText( Settings.ReadString( "Button", "Bresenham" ), font, color );
    m_ButtonBresenhamDrawType->SetText( Settings.ReadString( "Button", "BresenhamDrawType_1" ), font, color );
    m_ButtonStateMichener->SetText( Settings.ReadString( "Button", "Michener" ), font, color );
    m_ButtonStateBoundryFill->SetText( Settings.ReadString( "Button", "BoundryFill" ), font, color );
    m_ButtonStateLiangBarsky ->SetText( Settings.ReadString( "Button", "LiangBarsky" ), font, color );
    m_ButtonStateSpline->SetText( Settings.ReadString( "Button", "Spline" ), font, color );
    m_ButtonStateClear->SetText( Settings.ReadString( "Button", "Clear" ), font, color );
}

void Panel::PositionButtons() {
    int width = Settings.ReadInt( "Button", "Width" );
    int height = Settings.ReadInt( "Button", "Height" );

    // Left side
    m_ButtonGridInitial->SetFieldSize( width, height );
    m_ButtonGridVerySmall->SetFieldSize( width, height );
    m_ButtonGridSmall->SetFieldSize( width, height );
    m_ButtonGridMedium->SetFieldSize( width, height );
    m_ButtonGridLarge->SetFieldSize( width, height );
    m_ButtonGridVeryLarge->SetFieldSize( width, height );

    // Right side
    m_ButtonStateBresenham->SetFieldSize( width, height );
    m_ButtonBresenhamDrawType->SetFieldSize( width, height );
    m_ButtonStateMichener->SetFieldSize( width, height );
    m_ButtonStateBoundryFill->SetFieldSize( width, height );
    m_ButtonStateLiangBarsky->SetFieldSize( width, height );
    m_ButtonStateSpline->SetFieldSize( width, height );
    m_ButtonStateClear->SetFieldSize( width, height );

    // Left side
    int offsetX = Settings.ReadInt( "Button", "OffsetX" );
    m_ButtonGridInitial->SetX( offsetX );
    m_ButtonGridVerySmall->SetX( offsetX );
    m_ButtonGridSmall->SetX( offsetX );
    m_ButtonGridMedium->SetX( offsetX );
    m_ButtonGridLarge->SetX( offsetX );
    m_ButtonGridVeryLarge->SetX( offsetX );

    // Right side
    offsetX = Settings.ReadInt( "ScreenWidth" ) - offsetX - width;
    m_ButtonStateBresenham->SetX( offsetX );
    m_ButtonBresenhamDrawType->SetX( offsetX );
    m_ButtonStateMichener->SetX( offsetX );
    m_ButtonStateBoundryFill->SetX( offsetX );
    m_ButtonStateLiangBarsky->SetX( offsetX );
    m_ButtonStateSpline->SetX( offsetX );
    m_ButtonStateClear->SetX( offsetX );

    // Left side
    int offsetY = Settings.ReadInt( "Button", "OffsetY" );
    int paddingY = Settings.ReadInt( "Button", "PaddingY" );
    m_ButtonGridInitial->SetY( offsetY );
    m_ButtonGridVerySmall->SetY( offsetY + ( height + paddingY ) );
    m_ButtonGridSmall->SetY( offsetY + 2 * ( height + paddingY ) );
    m_ButtonGridMedium->SetY( offsetY + 3 * ( height + paddingY ) );
    m_ButtonGridLarge->SetY( offsetY + 4 * ( height + paddingY ) );
    m_ButtonGridVeryLarge->SetY( offsetY + 5 * ( height + paddingY ) );

    // Right side
    m_ButtonStateBresenham->SetY( offsetY );
    m_ButtonBresenhamDrawType->SetY( offsetY + ( height + paddingY ) );
    m_ButtonStateMichener->SetY( offsetY + 2 * ( height + paddingY ) );
    m_ButtonStateBoundryFill->SetY( offsetY + 3 * ( height + paddingY ) );
    m_ButtonStateLiangBarsky->SetY( offsetY + 4 * ( height + paddingY ) );
    m_ButtonStateSpline->SetY( offsetY + 5 * ( height + paddingY ) );
    m_ButtonStateClear->SetY( offsetY + 6 * ( height + paddingY ) );
}

void Panel::DestroyButtons() {
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
    delete m_ButtonBresenhamDrawType;
    delete m_ButtonStateMichener;
    delete m_ButtonStateBoundryFill;
    delete m_ButtonStateLiangBarsky;
    delete m_ButtonStateSpline;
    delete m_ButtonStateClear;

    m_ButtonStateBresenham = NULL;
    m_ButtonBresenhamDrawType = NULL;
    m_ButtonStateMichener = NULL;
    m_ButtonStateBoundryFill = NULL;
    m_ButtonStateLiangBarsky = NULL;
    m_ButtonStateSpline = NULL;
    m_ButtonStateClear = NULL;
}

bool Panel::ButtonEvents( SDL_Event& ) {
    
}

void Panel::ReleaseButtons() {
    // Left side
    m_ButtonGridInitial->Release();
    m_ButtonGridVerySmall->Release();
    m_ButtonGridSmall->Release();
    m_ButtonGridMedium->Release();
    m_ButtonGridLarge->Release();
    m_ButtonGridVeryLarge->Release();

    // Right side
    m_ButtonStateBresenham->Release();
    m_ButtonBresenhamDrawType->Release();
    m_ButtonStateMichener->Release();
    m_ButtonStateBoundryFill->Release();
    m_ButtonStateLiang_Barsky->Release();
    m_ButtonStateSpline->Release();
    m_ButtonStateClear->Release();
}

void Panel::Draw() {
    DrawButtons();

    grid->Draw();

    textFieldTitle->Draw();
}

void Panel::DrawButtons() {
    // Left side
    m_ButtonGridInitial->Draw();
    m_ButtonGridVerySmall->Draw();
    m_ButtonGridSmall->Draw();
    m_ButtonGridMedium->Draw();
    m_ButtonGridLarge->Draw();
    m_ButtonGridVeryLarge->Draw();

    // Right side
    m_ButtonStateBresenham->Draw();
    m_ButtonBresenhamDrawType->Draw();
    m_ButtonStateMichener->Draw();
    m_ButtonStateBoundryFill->Draw();
    m_ButtonStateLiang_Barsky->Draw();
    m_ButtonStateSpline->Draw();
    m_ButtonStateClear->Draw();
}

void Interface::EventHandler( SDL_Event& event ) {
    int x, y;

    if( event.type == SDL_MOUSEBUTTONDOWN ) {
        SDL_GetMouseState( &x, &y );

        if( m_ButtonGridInitial->IsIn( x, y ) ) {
            m_ButtonGridInitial->Press();
        }
        else if( m_ButtonGridVerySmall->IsIn( x, y ) ) {
            m_ButtonGridVerySmall->Press();
        }
        else if( m_ButtonGridSmall->IsIn( x, y ) ) {
            m_ButtonGridSmall->Press();
        }
        else if( m_ButtonGridMedium->IsIn( x, y ) ) {
            m_ButtonGridMedium->Press();
        }
        else if( m_ButtonGridLarge->IsIn( x, y ) ) {
            m_ButtonGridLarge->Press();
        }
        else if( m_ButtonGridVeryLarge->IsIn( x, y ) ) {
            m_ButtonGridVeryLarge->Press();
        }
        else if( m_ButtonStateBresenham->IsIn( x, y ) ) {
            m_ButtonStateBresenham->Press();
        }
        else if( m_ButtonBresenhamDrawType->IsIn( x, y ) ) {
            m_ButtonBresenhamDrawType->Press();
        }
        else if( m_ButtonStateMichener->IsIn( x, y ) ) {
            m_ButtonStateMichener->Press();
        }
        else if( m_ButtonStateBoundryFill->IsIn( x, y ) ) {
            m_ButtonStateBoundryFill->Press();
        }
        else if( m_ButtonStateLiang_Barsky->IsIn( x, y ) ) {
            m_ButtonStateLiang_Barsky->Press();
        }
        else if( m_ButtonStateSpline->IsIn( x, y ) ) {
            m_ButtonStateSpline->Press();
        }
        else if( m_ButtonStateClear->IsIn( x, y ) ) {
            m_ButtonStateClear->Press();
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP) {
        SDL_GetMouseState( &x, &y );

        if( m_ButtonGridInitial->IsIn( x, y ) && m_ButtonGridInitial->IsPressed() ) {
            grid->SetGridScale( "Initial" );
        }
        else if( m_ButtonGridVerySmall->IsIn( x, y ) && m_ButtonGridVerySmall->IsPressed() ) {
            grid->SetGridScale( "VerySmall" );
        }
        else if( m_ButtonGridSmall->IsIn( x, y ) && m_ButtonGridSmall->IsPressed() ) {
            grid->SetGridScale( "Small" );
        }
        else if( m_ButtonGridMedium->IsIn( x, y ) && m_ButtonGridMedium->IsPressed() ) {
            grid->SetGridScale( "Medium" );
        }
        else if( m_ButtonGridLarge->IsIn( x, y ) && m_ButtonGridLarge->IsPressed() ) {
            grid->SetGridScale( "Large" );
        }
        else if( m_ButtonGridVeryLarge->IsIn( x, y ) && m_ButtonGridVeryLarge->IsPressed() ) {
            grid->SetGridScale( "VeryLarge" );
        }
        else if( m_ButtonStateBresenham->IsIn( x, y ) && m_ButtonStateBresenham->IsPressed() ) {
            grid->SetState( Grid::Bresenham );

            textFieldTitle->SetText( "Bresenham", font, {0xFF, 0xFF, 0xFF, 0xFF} );

            m_ButtonBresenhamDrawType->Enable();

            m_ButtonGridInitial->Enable();
            m_ButtonGridVerySmall->Enable();
            m_ButtonGridSmall->Enable();
            m_ButtonGridMedium->Enable();
            m_ButtonGridLarge->Enable();
            m_ButtonGridVeryLarge->Enable();
        }
        else if( m_ButtonBresenhamDrawType->IsIn( x, y ) && m_ButtonBresenhamDrawType->IsPressed() ) {
            if( grid->ToggleDrawBresenham() ) {
                m_ButtonBresenhamDrawType->SetText( Settings.ReadString( "Button", "BresenhamDrawType_1" ), font, {0x00, 0x00, 0x00, 0xFF} );
            }
            else {
                m_ButtonBresenhamDrawType->SetText( Settings.ReadString( "Button", "BresenhamDrawType_2" ), font, {0x00, 0x00, 0x00, 0xFF} );
            }

        }
        else if( m_ButtonStateMichener->IsIn( x, y ) && m_ButtonStateMichener->IsPressed() ) {
            grid->SetState( Grid::Michener );

            textFieldTitle->SetText( "Michener", font, {0xFF, 0xFF, 0xFF, 0xFF} );

            m_ButtonBresenhamDrawType->Disable();

            m_ButtonGridInitial->Enable();
            m_ButtonGridVerySmall->Enable();
            m_ButtonGridSmall->Enable();
            m_ButtonGridMedium->Enable();
            m_ButtonGridLarge->Enable();
            m_ButtonGridVeryLarge->Enable();

        }
        else if( m_ButtonStateBoundryFill->IsIn( x, y ) && m_ButtonStateBoundryFill->IsPressed() ) {
            grid->SetGridScale( "Small" );
            
            grid->SetState( Grid::BoundryFill );

            textFieldTitle->SetText( "Boundry Fill", font, {0xFF, 0xFF, 0xFF, 0xFF} );

            m_ButtonBresenhamDrawType->Disable();

            m_ButtonGridInitial->Disable();
            m_ButtonGridVerySmall->Disable();
            m_ButtonGridSmall->Disable();
            m_ButtonGridMedium->Disable();
            m_ButtonGridLarge->Disable();
            m_ButtonGridVeryLarge->Disable();

        }
        else if( m_ButtonStateLiang_Barsky->IsIn( x, y ) && m_ButtonStateLiang_Barsky->IsPressed() ) {
            grid->SetGridScale( "Initial" );

            grid->SetState( Grid::Liang_Barsky );

            textFieldTitle->SetText( "Liang-Barsky", font, {0xFF, 0xFF, 0xFF, 0xFF} );

            m_ButtonBresenhamDrawType->Disable();

            m_ButtonGridInitial->Disable();
            m_ButtonGridVerySmall->Disable();
            m_ButtonGridSmall->Disable();
            m_ButtonGridMedium->Disable();
            m_ButtonGridLarge->Disable();
            m_ButtonGridVeryLarge->Disable();
            
        }
        else if( m_ButtonStateSpline->IsIn( x, y ) && m_ButtonStateSpline->IsPressed() ) {
            grid->SetGridScale( "Initial" );

            grid->SetState( Grid::Spline );

            textFieldTitle->SetText( "Cubic Spline", font, {0xFF, 0xFF, 0xFF, 0xFF} );

            m_ButtonBresenhamDrawType->Disable();

            m_ButtonGridInitial->Disable();
            m_ButtonGridVerySmall->Disable();
            m_ButtonGridSmall->Disable();
            m_ButtonGridMedium->Disable();
            m_ButtonGridLarge->Disable();
            m_ButtonGridVeryLarge->Disable();
            
        }
        else if( m_ButtonStateClear->IsIn( x, y ) && m_ButtonStateClear->IsPressed() ) {
            grid->ClearGrid();
        }

        ReleaseButtons();
    }
}