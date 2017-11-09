#include "Interface.h"

Interface::Interface()
{
    m_xmlConstants = new pugi::xml_document();
    if( !m_xmlConstants->load_file( "constants/Constants.xml" ) )
    {
        printf( "Couldn't load constants from xml!\n" );
        m_bQuit = true;
    }
    else
    {
        m_Window = NULL;
        m_Renderer = NULL;

        if( !InitSDL() )
        {
            m_bQuit = true;
        }
        else
        {
            m_bQuit = false;
            
            SDL_SetRenderDrawColor( m_Renderer, 0x00, 0x00, 0x00, 0xFF );
            SDL_RenderClear( m_Renderer );
            
            Create();
        }
    }
}

Interface::~Interface()
{
    delete m_xmlConstants;
    delete m_pGrid;
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);
    TTF_CloseFont( m_Font );
    
    m_xmlConstants = NULL;
    m_pGrid = NULL;
    m_Renderer = NULL;
    m_Window = NULL;
    m_Font = NULL;


    delete m_TextFieldTitle;
    m_TextFieldTitle = NULL;

    DeleteButtons();

    DeInitSDL();
}

void Interface::EventHandler( SDL_Event& e )
{
    if( e.type == SDL_QUIT )
    {
        m_bQuit = true;
    }
    else
    {
        if( !ButtonEvents( e ) )
        {
            m_pGrid->EventHandler( e );
        }
    }
}

bool Interface::GetQuit() const
{
    return m_bQuit;
}

void Interface::Draw()
{
    m_pGrid->Draw();

    m_TextFieldTitle->Draw();

    DrawButtons();

    SDL_RenderPresent( m_Renderer );
}

bool Interface::InitSDL()
{
    bool bSuccess = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Couldn't initialize SDL! Error: %s\n", SDL_GetError() );
        bSuccess = false;
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!\n" );
        }

        int iScreenHeight = m_xmlConstants->first_child().child( "ScreenHeight" ).text().as_int();
        int iScreenWidth = m_xmlConstants->first_child().child( "ScreenWidth" ).text().as_int();
        std::string sWindowName = m_xmlConstants->first_child().child( "WindowName" ).text().as_string();

        m_Window = SDL_CreateWindow( sWindowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, iScreenWidth, iScreenHeight, SDL_WINDOW_SHOWN );
        if( m_Window == NULL )
        {
            printf( "Couldn't create window! Error: %s\n", SDL_GetError() );
            bSuccess = false;
        }
        else
        {
            m_Renderer = SDL_CreateRenderer( m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( m_Renderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                bSuccess = false;
            }
            else
            {
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    bSuccess = false;
                }

                int iFormatFlags = IMG_INIT_PNG;
                if( !( IMG_Init( iFormatFlags ) & iFormatFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    bSuccess = false;
                }
            }
        }
    }

    return bSuccess;
}

void Interface::DeInitSDL()
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Interface::Create()
{
    m_pGrid = new Grid();
    m_pGrid->Init( m_xmlConstants, m_Renderer );

    std::string sFont = m_xmlConstants->first_child().child( "Button" ).child( "Font" ).text().as_string();
    int iFont = m_xmlConstants->first_child().child( "Button" ).child( "FontSize" ).text().as_int();
    m_Font = TTF_OpenFont( sFont.c_str(), iFont );

    CreateTitle();

    CreateButtons();
}

void Interface::CreateTitle()
{
    m_TextFieldTitle = new TextField();
    m_TextFieldTitle->Init( m_Renderer );

    m_TextFieldTitle->SetText( "Bresenham", m_Font, {0xFF, 0xFF, 0xFF, 0xFF} );

    int iScreenWidth = m_xmlConstants->first_child().child( "ScreenWidth" ).text().as_int();
    int iGridOffsetY = m_xmlConstants->first_child().child( "GridPos" ).child( "y" ).text().as_int();
    int iWidth = m_xmlConstants->first_child().child( "TitleWidth" ).text().as_int();

    m_TextFieldTitle->SetFieldSize( iWidth, iGridOffsetY );
    m_TextFieldTitle->SetX( ( iScreenWidth - iWidth ) / 2 );
    m_TextFieldTitle->SetY( 0 );
}