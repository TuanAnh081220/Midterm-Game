#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;

bool init(SDL_Window* &Window, SDL_Renderer* &Renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		cout << "Error: " << SDL_GetError() ;
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			cout << "Warning: Linear texture filtering not enabled!";
		}
		Window = SDL_CreateWindow( "CarwithSDLL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( Window == NULL )
		{
			cout << "Window could not be created! SDL Error: " << SDL_GetError();
			success = false;
		}
		else
		{
			Renderer = SDL_CreateRenderer( Window, -1, SDL_RENDERER_ACCELERATED );
			if( Renderer == NULL )
			{
				cout << "Renderer could not be created! SDL Error:" << SDL_GetError();
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					cout << "SDL_image could not initialize! SDL_image Error:" <<  IMG_GetError();
					success = false;
				}
				else{
                    if(TTF_Init() == -1){
                        cout << "Fail to init TFF";
                        success = false;
                    }
                    else{
                        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
                        {
                            cout << "Fail to int Mixer" << Mix_GetError();
                            success = false;
                        }
                    }
				}
			}
		}
	}

	return success;
}

SDL_Texture* loadTexture( std::string path , SDL_Renderer* &renderer)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 123, 123, 123));
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}
