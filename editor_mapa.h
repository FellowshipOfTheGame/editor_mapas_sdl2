/* 
* CREATED BY Lucas Vieira Costa Nicolau - USP
* Used amoung with SDL2 
* -- (good tutorial tip : SDL LAZY FOO --there's other, but this was the most 
* used by me on learning)
*
* -- Open Source, Open to learn, Open to distribute. 
* Just don't misrepresent my credits and time spend to make this library. Thanks.
*/

#ifndef EDITOR_MAPA_H
#define	EDITOR_MAPA_H

#include "sdl_basics.h"

bool editor_mapa();

bool empty_mapa();

bool tradeImage(SDL_Surface **surface, const char *str);

SDL_Point toMatrizPosition(SDL_Point mPosition);

bool matrizToImage(SDL_Rect *offset, SDL_Surface *surface, SDL_Surface *screen);

bool load_up(SDL_Window **window, SDL_Surface **screen, SDL_Surface **img);

bool clean_up(SDL_Window **window, SDL_Surface **screen, SDL_Surface **img);

bool load_mapa();

bool save_mapa();

bool save_undo();

bool save_redo();

bool load_undo();

bool load_redo();

void limpa_selecao();

void seta_linha(SDL_Point mPoint, int value);

void seta_coluna(SDL_Point mPoint, int value);

//void retorna_valor_anterior(SDL_Point mPositionMatriz);
                    
#endif	/* EDITOR_MAPA_H */

