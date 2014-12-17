/**
Choisir une License
 */

#include <stdio.h>
#include <stdlib.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void cleanup()
{
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    const unsigned int windowWidth = 640;
    const unsigned int windowHeight = 480;

    SDL_Window* pWindow = NULL; // Ecran principal
    SDL_Surface* pImage = NULL; // Logo
    SDL_Surface* pImageSalameche = NULL; // Salameche
    char mustContinue = 1; // Indicateur boolean pour la boucle principale

    int imgFlags = IMG_INIT_PNG; // Flags pour charger le support PNG
    const char* SalamechePath = "./data/4.png";
    const char *LogoPath = "./data/Logo Pokémon.png";

    SDL_Rect logoPos, salamechePos;

    TTF_Font* pFont = NULL;
    const char* fontPath = "./data/font.ttf";
    SDL_Color fontColor = {99, 140, 222};
    SDL_Surface* pFontSurface = NULL;
    SDL_Rect textePos;

    // Demarre SDL
    if ( SDL_Init(SDL_INIT_VIDEO) == -1 )
    {
        fprintf(stderr, "Erreur lors de l'initialisation de la SDL\n");
        return -1;
    }

    if ( IMG_Init(imgFlags) != imgFlags )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL_image : '%s'\n", IMG_GetError());
        cleanup();
        return -1;
    }

    if ( TTF_Init() == -1 )
    {
        fprintf(stderr,"Erreur lors de l'initialisation de la SDL_TTF : '%s'\n", TTF_GetError());
        cleanup();
        return -1;
    }

    /* Création de la fenêtre */
    pWindow = SDL_CreateWindow("Pokemon", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if ( pWindow != NULL )
    {
        pImage = IMG_Load(LogoPath); // Chargement du logo
        if ( pImage == NULL )
        {
            fprintf(stderr,"Erreur de chargement de l'image %s : %s\n", LogoPath, IMG_GetError());
            SDL_DestroyWindow(pWindow);
            cleanup();
            return -3;
        }

        pImageSalameche = IMG_Load(SalamechePath); // Chargement du png salameche
        if ( pImageSalameche == NULL )
        {
            fprintf(stderr,"Erreur de chargement de l'image %s : %s\n", SalamechePath, IMG_GetError());
            SDL_DestroyWindow(pWindow);
            cleanup();
            return -3;
        }

        pFont = TTF_OpenFont(fontPath, 32); // Chargement Police
        if ( pFont == NULL )
        {
            fprintf(stderr, "Erreur de chargement de la police %s : %s\n", fontPath, TTF_GetError());
            SDL_DestroyWindow(pWindow);
            cleanup();
            return -3;
        }

        // Genere la SDL_Surface a partir de la police
        pFontSurface = TTF_RenderText_Solid(pFont, "Developpement du projet Pokemon", fontColor);
        if ( !pFontSurface )
        {
            fprintf(stderr, "Erreur pour generer le texte '%s'\n", TTF_GetError());
            SDL_DestroyWindow(pWindow);
            cleanup();
            return -4;
        }

        /* Positions */

        // Nous centrons le logo dans la fenêtre
        logoPos.x = windowWidth/2 - pImage->w/2;
        logoPos.y = windowHeight/2 - pImage->h/2;
        logoPos.w = pImage->w;
        logoPos.h = pImage->h;

        // Nous appliquons salameche dans la fenêtre
        salamechePos.x = 0;
        salamechePos.y = 0;

        // Le texte est aux deux tiers de la hauteur de l'ecran
        textePos.x = windowWidth/2 - pFontSurface->w/2;
        textePos.y = 2*windowHeight/3;
        textePos.w = pFontSurface->w;
        textePos.h = pFontSurface->h;

        // Boucle principale
        while ( mustContinue )
        {
            // Affiche le logo à la position indiquée
            if ( SDL_BlitSurface(pImage, NULL, SDL_GetWindowSurface(pWindow), &logoPos) != 0 )
            {
                fprintf(stderr, "Erreur de copie de la surface sur l'écran\n");
                mustContinue=0;
            }
            // Affiche salamèche à la position indiquée
            if ( SDL_BlitSurface(pImageSalameche, NULL, SDL_GetWindowSurface(pWindow), &salamechePos) != 0 )
            {
                fprintf(stderr, "Erreur de copie de la surface sur l'écran\n");
                mustContinue=0;
            }
            // Affiche le texte
            if ( SDL_BlitSurface(pFontSurface, NULL, SDL_GetWindowSurface(pWindow), &textePos) != 0 )
            {
                fprintf(stderr, "Erreur de copie du texte sur l'écran\n");
                mustContinue=0;
            }
            SDL_UpdateWindowSurface(pWindow);

            SDL_Event event;
            SDL_WaitEvent(&event);

            // Detecte si on clique sur la croix
            if( event.type == SDL_QUIT )
            {
                //On quitte le programme
                mustContinue = 0;
            }
            // Detecte si une touche est appuyee
            else if( event.type == SDL_KEYDOWN )
            {
                if ( event.key.keysym.sym == SDLK_ESCAPE )
                {
                    mustContinue = 0;
                }
            }
        }

        SDL_DestroyWindow(pWindow);
        SDL_FreeSurface(pFontSurface);
        TTF_CloseFont(pFont);
        SDL_FreeSurface(pImage);
    }
    else
    {
        fprintf(stderr,"Erreur de création de la fenêtre: %s\n", SDL_GetError());
        cleanup();
        return -3;
    }

    cleanup();

    return 0;
}


