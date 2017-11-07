#include "Homework.h"

Homework::Homework()
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

Homework::~Homework()
{
    delete m_xmlConstants;
    delete m_pGrid;
    SDL_DestroyRenderer(m_Renderer);
    SDL_DestroyWindow(m_Window);

    m_xmlConstants = NULL;
    m_pGrid = NULL;
    m_Renderer = NULL;
    m_Window = NULL;

    DeleteButtons();

    DeInitSDL();
}

void Homework::EventHandler( SDL_Event& e )
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

bool Homework::GetQuit() const
{
    return m_bQuit;
}

void Homework::Draw()
{
    m_pGrid->Draw();

    m_ButtonGridInitial->Draw();
    m_ButtonGridVerySmall->Draw();
    m_ButtonGridSmall->Draw();
    m_ButtonGridMedium->Draw();
    m_ButtonGridLarge->Draw();
    m_ButtonGridVeryLarge->Draw();

    SDL_RenderPresent( m_Renderer );
}

bool Homework::InitSDL()
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

void Homework::DeInitSDL()
{
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void Homework::Create()
{
    m_pGrid = new Grid();
    m_pGrid->Init( m_xmlConstants, m_Renderer );

    CreateButtons();
}