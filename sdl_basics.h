//#ifdef TARGET_OS_MAC
//  // Mac Includes Here
//#endif
//
//#ifdef __linux__
//  // Linux Includes Here
//  #error Can't be compiled on Linux yet
//#endif
//
//#ifdef _WIN32 || _WIN64
//  // Windows Includes Here
//  #error Can't be compiled on Windows yet
//#endif

#ifndef _SDL_BASICS
#define _SDL_BASICS

#define DEVMODE true        /// ATIVA TESTE DE POSICAO (true atico, false inativo)

#include <stdio.h>
#include <stdlib.h> 
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

/* SET VALUE TO OFFSET */
bool set_sdlRect(SDL_Rect *offset, int x, int y);

/* SET VALUE TO SURFACE */
bool set_sdlSurface(SDL_Surface** surface, const char *str, bool bmp);


bool set_sdlFont(TTF_Font **font, const char *font_type, int font_size);

/* FREE SURFACE */
bool freeSDL_Surface(SDL_Surface** surface);

/* FREE MIX_MUSIC */
bool freeSDL_Mix_Music(Mix_Music **music);

/* CLEAN UP EVERTHING */
bool clean_up(SDL_Surface **surface, int *ptr, int qtde);

/* LOAD UP EVERTHING */
bool load_files(SDL_Surface **surface, const char **str, int qtde);
#endif
