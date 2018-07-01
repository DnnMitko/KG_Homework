#include "Interface.h"

Interface::Interface() {
    Init();
}

Interface::~Interface() {
    Deinit();
}

void Interface::Init() {
    grid = new Grid();

    OpenFont();

    CreateTitle();

    CreateButtons();
    PositionButtons();
}

void Interface::Deinit() {
    delete grid;
    grid = NULL;

    screenController.getInstance()->CloseFont( font );
    font = NULL;

    delete textFieldTitle;
    textFieldTitle = NULL;

    DestroyButtons();
}

void Interface::OpenFont() {
    font = NULL;

    std::string newFont = settings.getInstance()->ReadString( "Button", "Font" );
    int fontSize = settings.getInstance()->ReadInt( "Button", "FontSize" );

    font = screenController.getInstance()->OpenFont( newFont, fontSize );
}

void Interface::CreateTitle() {
    textFieldTitle = new TextField();

    textFieldTitle->SetText( "Bresenham", font, {0xFF, 0xFF, 0xFF, 0xFF} );

    int screenWidth = settings.getInstance()->ReadInt( "ScreenWidth" );
    int gridOffsetY = settings.getInstance()->ReadInt( "GridPos", "y" );
    int titleWidth = settings.getInstance()->ReadInt( "TitleWidth" );

    textFieldTitle->SetFieldSize( titleWidth, gridOffsetY );
    textFieldTitle->SetX( ( screenWidth - titleWidth ) / 2 );
    textFieldTitle->SetY( 0 );
}

void Interface::CreateButtons() {
    // Left side
    buttonGridInitial = new Button();
    buttonGridVerySmall = new Button();
    buttonGridSmall = new Button();
    buttonGridMedium = new Button();
    buttonGridLarge = new Button();
    buttonGridVeryLarge = new Button();

    // Right side
    buttonStateBresenham = new Button();
    buttonBresenhamDrawType = new Button();
    buttonStateMichener = new Button();
    buttonStateBoundryFill = new Button();
    buttonStateLiangBarsky = new Button();
    buttonStateSpline = new Button();
    buttonStateClear = new Button();

    SDL_Color color = {0x00, 0x00, 0x00, 0xFF};
    // Left side
    buttonGridInitial->SetText( settings.getInstance()->ReadString( "GridScale", "Initial" ), font, color );
    buttonGridVerySmall->SetText( settings.getInstance()->ReadString( "GridScale", "VerySmall" ), font, color );
    buttonGridSmall->SetText( settings.getInstance()->ReadString( "GridScale", "Small" ), font, color );
    buttonGridMedium->SetText( settings.getInstance()->ReadString( "GridScale", "Medium" ), font, color );
    buttonGridLarge->SetText( settings.getInstance()->ReadString( "GridScale", "Large" ), font, color );
    buttonGridVeryLarge->SetText( settings.getInstance()->ReadString( "GridScale", "VeryLarge" ), font, color );

    // Right side
    buttonStateBresenham->SetText( settings.getInstance()->ReadString( "Button", "Bresenham" ), font, color );
    buttonBresenhamDrawType->SetText( settings.getInstance()->ReadString( "Button", "BresenhamDrawType_1" ), font, color );
    buttonStateMichener->SetText( settings.getInstance()->ReadString( "Button", "Michener" ), font, color );
    buttonStateBoundryFill->SetText( settings.getInstance()->ReadString( "Button", "BoundryFill" ), font, color );
    buttonStateLiangBarsky ->SetText( settings.getInstance()->ReadString( "Button", "LiangBarsky" ), font, color );
    buttonStateSpline->SetText( settings.getInstance()->ReadString( "Button", "Spline" ), font, color );
    buttonStateClear->SetText( settings.getInstance()->ReadString( "Button", "Clear" ), font, color );
}

void Interface::PositionButtons() {
    int width = settings.getInstance()->ReadInt( "Button", "Width" );
    int height = settings.getInstance()->ReadInt( "Button", "Height" );

    // Left side
    buttonGridInitial->SetFieldSize( width, height );
    buttonGridVerySmall->SetFieldSize( width, height );
    buttonGridSmall->SetFieldSize( width, height );
    buttonGridMedium->SetFieldSize( width, height );
    buttonGridLarge->SetFieldSize( width, height );
    buttonGridVeryLarge->SetFieldSize( width, height );

    // Right side
    buttonStateBresenham->SetFieldSize( width, height );
    buttonBresenhamDrawType->SetFieldSize( width, height );
    buttonStateMichener->SetFieldSize( width, height );
    buttonStateBoundryFill->SetFieldSize( width, height );
    buttonStateLiangBarsky->SetFieldSize( width, height );
    buttonStateSpline->SetFieldSize( width, height );
    buttonStateClear->SetFieldSize( width, height );

    // Left side
    int offsetX = settings.getInstance()->ReadInt( "Button", "OffsetX" );
    buttonGridInitial->SetX( offsetX );
    buttonGridVerySmall->SetX( offsetX );
    buttonGridSmall->SetX( offsetX );
    buttonGridMedium->SetX( offsetX );
    buttonGridLarge->SetX( offsetX );
    buttonGridVeryLarge->SetX( offsetX );

    // Right side
    offsetX = settings.getInstance()->ReadInt( "ScreenWidth" ) - offsetX - width;
    buttonStateBresenham->SetX( offsetX );
    buttonBresenhamDrawType->SetX( offsetX );
    buttonStateMichener->SetX( offsetX );
    buttonStateBoundryFill->SetX( offsetX );
    buttonStateLiangBarsky->SetX( offsetX );
    buttonStateSpline->SetX( offsetX );
    buttonStateClear->SetX( offsetX );

    // Left side
    int offsetY = settings.getInstance()->ReadInt( "Button", "OffsetY" );
    int paddingY = settings.getInstance()->ReadInt( "Button", "PaddingY" );
    buttonGridInitial->SetY( offsetY );
    buttonGridVerySmall->SetY( offsetY + ( height + paddingY ) );
    buttonGridSmall->SetY( offsetY + 2 * ( height + paddingY ) );
    buttonGridMedium->SetY( offsetY + 3 * ( height + paddingY ) );
    buttonGridLarge->SetY( offsetY + 4 * ( height + paddingY ) );
    buttonGridVeryLarge->SetY( offsetY + 5 * ( height + paddingY ) );

    // Right side
    buttonStateBresenham->SetY( offsetY );
    buttonBresenhamDrawType->SetY( offsetY + ( height + paddingY ) );
    buttonStateMichener->SetY( offsetY + 2 * ( height + paddingY ) );
    buttonStateBoundryFill->SetY( offsetY + 3 * ( height + paddingY ) );
    buttonStateLiangBarsky->SetY( offsetY + 4 * ( height + paddingY ) );
    buttonStateSpline->SetY( offsetY + 5 * ( height + paddingY ) );
    buttonStateClear->SetY( offsetY + 6 * ( height + paddingY ) );
}

void Interface::DestroyButtons() {
    // Left side
    delete buttonGridInitial;
    delete buttonGridVerySmall;
    delete buttonGridSmall;
    delete buttonGridMedium;
    delete buttonGridLarge;
    delete buttonGridVeryLarge;

    buttonGridInitial = NULL;
    buttonGridVerySmall = NULL;
    buttonGridSmall = NULL;
    buttonGridMedium = NULL;
    buttonGridLarge = NULL;
    buttonGridVeryLarge = NULL;

    // Right side
    delete buttonStateBresenham;
    delete buttonBresenhamDrawType;
    delete buttonStateMichener;
    delete buttonStateBoundryFill;
    delete buttonStateLiangBarsky;
    delete buttonStateSpline;
    delete buttonStateClear;

    buttonStateBresenham = NULL;
    buttonBresenhamDrawType = NULL;
    buttonStateMichener = NULL;
    buttonStateBoundryFill = NULL;
    buttonStateLiangBarsky = NULL;
    buttonStateSpline = NULL;
    buttonStateClear = NULL;
}

void Interface::ReleaseButtons() {
    // Left side
    buttonGridInitial->Release();
    buttonGridVerySmall->Release();
    buttonGridSmall->Release();
    buttonGridMedium->Release();
    buttonGridLarge->Release();
    buttonGridVeryLarge->Release();

    // Right side
    buttonStateBresenham->Release();
    buttonBresenhamDrawType->Release();
    buttonStateMichener->Release();
    buttonStateBoundryFill->Release();
    buttonStateLiangBarsky->Release();
    buttonStateSpline->Release();
    buttonStateClear->Release();
}

void Interface::Draw() {
    DrawButtons();

    grid->Draw();

    textFieldTitle->Draw();
}

void Interface::DrawButtons() {
    // Left side
    buttonGridInitial->Draw();
    buttonGridVerySmall->Draw();
    buttonGridSmall->Draw();
    buttonGridMedium->Draw();
    buttonGridLarge->Draw();
    buttonGridVeryLarge->Draw();

    // Right side
    buttonStateBresenham->Draw();
    buttonBresenhamDrawType->Draw();
    buttonStateMichener->Draw();
    buttonStateBoundryFill->Draw();
    buttonStateLiangBarsky->Draw();
    buttonStateSpline->Draw();
    buttonStateClear->Draw();
}

void Interface::EventHandler( SDL_Event& event ) {
    int x, y;

    if( event.type == SDL_MOUSEBUTTONDOWN ) {
        SDL_GetMouseState( &x, &y );

        if( buttonGridInitial->IsIn( x, y ) ) {
            buttonGridInitial->Press();
        }
        else if( buttonGridVerySmall->IsIn( x, y ) ) {
            buttonGridVerySmall->Press();
        }
        else if( buttonGridSmall->IsIn( x, y ) ) {
            buttonGridSmall->Press();
        }
        else if( buttonGridMedium->IsIn( x, y ) ) {
            buttonGridMedium->Press();
        }
        else if( buttonGridLarge->IsIn( x, y ) ) {
            buttonGridLarge->Press();
        }
        else if( buttonGridVeryLarge->IsIn( x, y ) ) {
            buttonGridVeryLarge->Press();
        }
        else if( buttonStateBresenham->IsIn( x, y ) ) {
            buttonStateBresenham->Press();
        }
        else if( buttonBresenhamDrawType->IsIn( x, y ) ) {
            buttonBresenhamDrawType->Press();
        }
        else if( buttonStateMichener->IsIn( x, y ) ) {
            buttonStateMichener->Press();
        }
        else if( buttonStateBoundryFill->IsIn( x, y ) ) {
            buttonStateBoundryFill->Press();
        }
        else if( buttonStateLiangBarsky->IsIn( x, y ) ) {
            buttonStateLiangBarsky->Press();
        }
        else if( buttonStateSpline->IsIn( x, y ) ) {
            buttonStateSpline->Press();
        }
        else if( buttonStateClear->IsIn( x, y ) ) {
            buttonStateClear->Press();
        }
    }
    else if(event.type == SDL_MOUSEBUTTONUP) {
        SDL_GetMouseState( &x, &y );

        if( buttonGridInitial->IsIn( x, y ) && buttonGridInitial->IsPressed() ) {
            grid->SetGridScale( "Initial" );
        }
        else if( buttonGridVerySmall->IsIn( x, y ) && buttonGridVerySmall->IsPressed() ) {
            grid->SetGridScale( "VerySmall" );
        }
        else if( buttonGridSmall->IsIn( x, y ) && buttonGridSmall->IsPressed() ) {
            grid->SetGridScale( "Small" );
        }
        else if( buttonGridMedium->IsIn( x, y ) && buttonGridMedium->IsPressed() ) {
            grid->SetGridScale( "Medium" );
        }
        else if( buttonGridLarge->IsIn( x, y ) && buttonGridLarge->IsPressed() ) {
            grid->SetGridScale( "Large" );
        }
        else if( buttonGridVeryLarge->IsIn( x, y ) && buttonGridVeryLarge->IsPressed() ) {
            grid->SetGridScale( "VeryLarge" );
        }
        else if( buttonStateBresenham->IsIn( x, y ) && buttonStateBresenham->IsPressed() ) {
            grid->SetState( Grid::Bresenham );

            textFieldTitle->SetText( "Bresenham", font, {0xFF, 0xFF, 0xFF, 0xFF} );

            buttonBresenhamDrawType->Enable();

            buttonGridInitial->Enable();
            buttonGridVerySmall->Enable();
            buttonGridSmall->Enable();
            buttonGridMedium->Enable();
            buttonGridLarge->Enable();
            buttonGridVeryLarge->Enable();
        }
        else if( buttonBresenhamDrawType->IsIn( x, y ) && buttonBresenhamDrawType->IsPressed() ) {
            if( grid->ToggleDrawBresenham() ) {
                buttonBresenhamDrawType->SetText( settings.getInstance()->ReadString( "Button", "BresenhamDrawType_1" ), font, {0x00, 0x00, 0x00, 0xFF} );
            }
            else {
                buttonBresenhamDrawType->SetText( settings.getInstance()->ReadString( "Button", "BresenhamDrawType_2" ), font, {0x00, 0x00, 0x00, 0xFF} );
            }

        }
        else if( buttonStateMichener->IsIn( x, y ) && buttonStateMichener->IsPressed() ) {
            grid->SetState( Grid::Michener );

            textFieldTitle->SetText( "Michener", font, {0xFF, 0xFF, 0xFF, 0xFF} );

            buttonBresenhamDrawType->Disable();

            buttonGridInitial->Enable();
            buttonGridVerySmall->Enable();
            buttonGridSmall->Enable();
            buttonGridMedium->Enable();
            buttonGridLarge->Enable();
            buttonGridVeryLarge->Enable();

        }
        else if( buttonStateBoundryFill->IsIn( x, y ) && buttonStateBoundryFill->IsPressed() ) {
            grid->SetGridScale( "Small" );
            
            grid->SetState( Grid::BoundryFill );

            textFieldTitle->SetText( "Boundry Fill", font, {0xFF, 0xFF, 0xFF, 0xFF} );

            buttonBresenhamDrawType->Disable();

            buttonGridInitial->Disable();
            buttonGridVerySmall->Disable();
            buttonGridSmall->Disable();
            buttonGridMedium->Disable();
            buttonGridLarge->Disable();
            buttonGridVeryLarge->Disable();

        }
        else if( buttonStateLiangBarsky->IsIn( x, y ) && buttonStateLiangBarsky->IsPressed() ) {
            grid->SetGridScale( "Initial" );

            grid->SetState( Grid::LiangBarsky );

            textFieldTitle->SetText( "Liang-Barsky", font, {0xFF, 0xFF, 0xFF, 0xFF} );

            buttonBresenhamDrawType->Disable();

            buttonGridInitial->Disable();
            buttonGridVerySmall->Disable();
            buttonGridSmall->Disable();
            buttonGridMedium->Disable();
            buttonGridLarge->Disable();
            buttonGridVeryLarge->Disable();
            
        }
        else if( buttonStateSpline->IsIn( x, y ) && buttonStateSpline->IsPressed() ) {
            grid->SetGridScale( "Initial" );

            grid->SetState( Grid::Spline );

            textFieldTitle->SetText( "Cubic Spline", font, {0xFF, 0xFF, 0xFF, 0xFF} );

            buttonBresenhamDrawType->Disable();

            buttonGridInitial->Disable();
            buttonGridVerySmall->Disable();
            buttonGridSmall->Disable();
            buttonGridMedium->Disable();
            buttonGridLarge->Disable();
            buttonGridVeryLarge->Disable();
            
        }
        else if( buttonStateClear->IsIn( x, y ) && buttonStateClear->IsPressed() ) {
            grid->ClearGrid();
        }

        ReleaseButtons();
    }
}