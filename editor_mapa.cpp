/* 
 * CREATED BY Lucas Vieira Costa Nicolau - USP
 * Used amoung with SDL2 
 * -- (good tutorial tip : SDL LAZY FOO --there are others, but this was the most used by me on learning)
 *
 * -- Open Source, Open to learn, Open to distribute. 
 * Just don't misrepresent my credits and time spend to make this library. Thanks.
 */
#include "editor_mapa.h"


/* --------      IMPORTANT     -----------       *
 * - IMAGE DIMENSION (SQUARE_SIZE X SQUARE_SIZE)  *
 * - DO NOT REMOVE ANY DEFINE -- JUST EDIT VALUES */

// SIZE OF MATRIZ
#define LIN 25
#define COL 25

// DIMENSION OF IMG (ONE SIDE -- NOTE: IMAGE MUST HAVE A SQUARE DIMENSION)
#define SQUARE_SIZE 20          // TAMANHO DO LADO DO QUADRADO


#define FILE_SOURCE "file/mapa.bin"
#define UNDO_SOURCE "file/undo.bin"
#define REDO_SOURCE "file/redo.bin"

// EMPTY AND SELECT VALUES -- 1 - 9  is the images used by the editor
#define SELECT -1
#define EMPTY 0

// IMAGES SOURCES
#define IMG_EMPTY "img/quad_pont.png"
#define IMG_SELECT "img/sel_quad_pont.png"
#define IMG_1 "img/img_1.png"
#define IMG_2 "img/img_2.png"
#define IMG_3 "img/img_3.png"
#define IMG_4 "img/img_4.png"
#define IMG_5 "img/img_5.png"
#define IMG_6 "img/img_6.png"
#define IMG_7 "img/img_7.png"
#define IMG_8 "img/img_8.png"
#define IMG_9 "img/img_9.png"

// -- GLOBAL VARIABLES --
int mapa[LIN][COL]; // Draw map
SDL_Point mem; // Save mouse point
int mem_value; // Save value to restore

// -- MAIN OF FUNCTION -- 

bool editor_mapa() {
    bool quit = false;
    bool empty = true;
    bool redo = false;
    bool undo = true;


    // The window we'll be rendering to
    SDL_Window* window = NULL;

    // The surface contained by the window
    SDL_Surface* screen = NULL;

    // Load images surfaces
    SDL_Surface* img = NULL;
    if (!set_sdlSurface(&img, IMG_EMPTY, false)) {
        fprintf(stderr, "Erro na execucao - %s\n", IMG_EMPTY);
        return false;
    }

    SDL_Rect offset;

    if (!load_up(&window, &screen, &img)) {
        fprintf(stderr, "Erro na load\n");
        if (save_mapa()) {
            printf("Erro na load\n");
        }
        return false;
    }

    //Get window surface
    screen = SDL_GetWindowSurface(window);

    // Fill the surface white
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

    // Update the surface
    SDL_UpdateWindowSurface(window);

    // Wait 0.1 seconds
    SDL_Delay(100);

    //Mouse position
    SDL_Point mPosition;
    //Init mPosition
    mPosition.x = 0;	
    mPosition.y = 0;


    // Mouse position to matriz
    SDL_Point mPositionMatriz;
    //Init mPosition
    mPositionMatriz.x = 0;
    mPositionMatriz.y = 0;

    // Initialize event handler
    SDL_Event event;

    while (!quit) {

        if (undo) {
            save_undo();
            undo = false;
        }

        if (empty) {
            save_undo();
            if (!empty_mapa()) {
                fprintf(stderr, "ERRO\n");
                return false;
            }
            save_redo();
            empty = false;
        }



        // clear screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF));

        if (!matrizToImage(&offset, img, screen)) {
            fprintf(stderr, "Error matriz to image\n");
            return false;
        }

        //Update the screen
        SDL_UpdateWindowSurface(window);


        //Handle events on queue 
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_KEYDOWN:
                {
                    switch (event.key.keysym.sym) {

                        // Exit
                        case SDLK_ESCAPE:
                            quit = true;
                            break;

                        // Reset mapa
                        case SDLK_INSERT:
                            empty = true;
                            break;
			
			
                        case SDLK_0:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = EMPTY;
                            redo = true;
                            break;
			
                        case SDLK_1:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 1;
                            redo = true;
                            break;

                        case SDLK_2:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 2;
                            redo = true;
                            break;

                        case SDLK_3:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 3;
                            redo = true;
                            break;

                        case SDLK_4:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 4;
                            redo = true;
                            break;

                        case SDLK_5:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 5;
                            redo = true;
                            break;

                        case SDLK_6:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 6;
                            redo = true;
                            break;

                        case SDLK_7:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 7;
                            redo = true;
                            break;

                        case SDLK_8:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 8;
                            redo = true;
                            break;

                        case SDLK_9:
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = 9;
                            redo = true;
                            break;

                        case SDLK_UP:
                            if (mapa[mPositionMatriz.x][mPositionMatriz.y] == SELECT) {
                                mapa[mPositionMatriz.x][mPositionMatriz.y] = mem_value;
                            }
                            if (mPositionMatriz.y != 0) {
                                mPositionMatriz.y--;
                            }

                            mem_value = mapa[mPositionMatriz.x][mPositionMatriz.y];
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = SELECT;

                            break;

                        case SDLK_DOWN:
                            if (mapa[mPositionMatriz.x][mPositionMatriz.y] == SELECT) {
                                mapa[mPositionMatriz.x][mPositionMatriz.y] = mem_value;
                            }
                            if (mPositionMatriz.y != LIN - 1) {
                                mPositionMatriz.y++;
                            }

                            mem_value = mapa[mPositionMatriz.x][mPositionMatriz.y];
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = SELECT;
                            break;
                        case SDLK_LEFT:
                            if (mapa[mPositionMatriz.x][mPositionMatriz.y] == SELECT) {
                                mapa[mPositionMatriz.x][mPositionMatriz.y] = mem_value;
                            }
                            if (mPositionMatriz.x != 0) {
                                mPositionMatriz.x--;
                            }

                            mem_value = mapa[mPositionMatriz.x][mPositionMatriz.y];
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = SELECT;
                            break;

                        case SDLK_RIGHT:
                            if (mapa[mPositionMatriz.x][mPositionMatriz.y] == SELECT) {
                                mapa[mPositionMatriz.x][mPositionMatriz.y] = mem_value;
                            }
                            if (mPositionMatriz.x != COL - 1) {
                                mPositionMatriz.x++;
                            }

                            mem_value = mapa[mPositionMatriz.x][mPositionMatriz.y];
                            mapa[mPositionMatriz.x][mPositionMatriz.y] = SELECT;
                            break;

                        // special fill line with select img
                        case SDLK_r:
                            save_undo();
                            seta_linha(mPositionMatriz, mem_value);
                            save_redo();
                            break;

                        // special fill line with select img
                        case SDLK_d:
                            save_undo();
                            seta_coluna(mPositionMatriz, mem_value);
                            save_redo();
                            break;
                        
                        case SDLK_f:
                            save_undo();
                            seta_coluna(mPositionMatriz, mem_value);
                            save_redo();
                            break;

                        // Load file
                        case SDLK_l:
                            if (load_mapa()) {
                                printf("Load Image");
                                save_undo();
                            }
                            break;

                            // Save file
                        case SDLK_s:
                            if (save_mapa()) {
                                printf("Save Image");
                            }
                            break;

                            // Undo 
                        case SDLK_z:
                            if (load_undo()) {
                                printf("Load Image");
                            }
                            break;

                            // Redo 
                        case SDLK_y:
                            if (load_redo()) {
                                printf("Load Image");
                            }
                            break;


                    }
                    break;
                }

                case SDL_MOUSEBUTTONDOWN:

                    limpa_selecao();

                    mem_value = mapa[mPositionMatriz.x][mPositionMatriz.y];
                    mPosition.x = event.motion.x;
                    mPosition.y = event.motion.y;

                    mPositionMatriz = toMatrizPosition(mPosition);

                    printf("%d %d\n", mPositionMatriz.x, mPositionMatriz.y);
                    break;

                default:
                    break;
            }
        }
        if (redo) {
            save_redo();
            redo = false;
            undo = true;
        }
    }

    if (save_mapa()) {
        printf("Load Image");
    }

    return clean_up(&window, &screen, &img);
}

// Load everthing

bool load_up(SDL_Window **window, SDL_Surface **screen, SDL_Surface **img) {
    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    //Create window
    *window = SDL_CreateWindow("Editor de Mapas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LIN*SQUARE_SIZE, COL*SQUARE_SIZE, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        fprintf(stderr, "Window could not be created! SDL_Error: %s\n", SDL_GetError());

        return false;
    }

    return true;
}

// Clean everthing

bool clean_up(SDL_Window **window, SDL_Surface **screen, SDL_Surface **img) {

    // Free surfaces
    freeSDL_Surface(img);
    freeSDL_Surface(screen);

    //Destroy window
    SDL_DestroyWindow(*window);

    //Quit SDL subsystems
    SDL_Quit();

    return true;
}

// Clean selection point

void limpa_selecao() {
    for (int i = 0; i < COL; i++) {
        for (int j = 0; j < LIN; j++) {
            if (mapa[i][j] == SELECT) {
                mapa[i][j] = EMPTY;
            }
        }
    }
}

// Set mouse on click point

SDL_Point toMatrizPosition(SDL_Point mPosition) {
    mPosition.x /= SQUARE_SIZE;
    mPosition.y /= SQUARE_SIZE;

    mapa[mem.x][mem.y] = mem_value;
    mem_value = mapa[mPosition.x][mPosition.y];
    mem = mPosition;
    mapa[mPosition.x][mPosition.y] = SELECT;
    return mPosition;
}

// Change image

bool tradeImage(SDL_Surface **surface, const char *str) {
    if (!set_sdlSurface(surface, str, false)) {
        fprintf(stderr, "Erro na execucao - %s\n", IMG_EMPTY);
        return false;
    }
    return true;
}

// Set image for every value of mapa[LIN][COL]

bool matrizToImage(SDL_Rect *offset, SDL_Surface *surface, SDL_Surface *screen) {
    bool draw = false;

    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0x00, 0x00, 0x00));

    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {

            if (mapa[i][j] == EMPTY) {

                if (!tradeImage(&surface, IMG_EMPTY)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == SELECT) {

                if (!tradeImage(&surface, IMG_SELECT)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 1) {
                if (!tradeImage(&surface, IMG_1)) {
                    return false;

                }
                draw = true;
            } else if (mapa[i][j] == 2) {
                if (!tradeImage(&surface, IMG_2)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 3) {
                if (!tradeImage(&surface, IMG_3)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 4) {
                if (!tradeImage(&surface, IMG_4)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 5) {
                if (!tradeImage(&surface, IMG_5)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 6) {
                if (!tradeImage(&surface, IMG_6)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 7) {
                if (!tradeImage(&surface, IMG_7)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 8) {
                if (!tradeImage(&surface, IMG_8)) {
                    return false;
                }
                draw = true;
            } else if (mapa[i][j] == 9) {
                if (!tradeImage(&surface, IMG_9)) {
                    return false;
                }
                draw = true;

            }
            if (draw) {
                set_sdlRect(offset, i * SQUARE_SIZE, j * SQUARE_SIZE);
                SDL_BlitSurface(surface, 0, screen, offset);
                draw = false;
            }
        }
    }
    return true;
}

// -- SPECIAL FEATURES --

// Repeat selected image to every point right the selection

void seta_linha(SDL_Point mPoint, int value) {
    for (int i = mPoint.x; i < COL; i++) {
        mapa[i][mPoint.y] = value;
    }
}

// Repeat selected image to every point down the selection

void seta_coluna(SDL_Point mPoint, int value) {
    for (int i = mPoint.y; i < LIN; i++) {
        mapa[mPoint.x][i] = value;
    }
}

// Reset mapa[LIN][COL] with EMPTY

bool empty_mapa() {
    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            mapa[i][j] = EMPTY;
        }
    }
    return true;
}

// Fill mapa[LIN][[COL] with select image

bool fill_mapa() {
    for (int i = 0; i < LIN; i++) {
        for (int j = 0; j < COL; j++) {
            mapa[i][j] = mem_value;
        }
    }
    return true;
}


// -- SAVE --

bool save_mapa() {
    FILE *file = fopen(FILE_SOURCE, "wb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- save\n");
        return false;
    }

    limpa_selecao();

    mapa[mem.x][mem.y] = mem_value;

    fwrite(mapa, LIN * COL * sizeof (int), 1, file);

    fclose(file);
    return true;
}

bool save_undo() {
    FILE *file = fopen(UNDO_SOURCE, "wb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- save\n");
        return false;
    }

    limpa_selecao();

    fwrite(mapa, LIN * COL * sizeof (int), 1, file);

    fclose(file);

    return true;
}

bool save_redo() {
    FILE *file = fopen(REDO_SOURCE, "wb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- save\n");
        return false;
    }

    limpa_selecao();

    fwrite(mapa, LIN * COL * sizeof (int), 1, file);

    fclose(file);
    return true;
}


// -- LOAD --

bool load_mapa() {
    FILE *file = fopen(FILE_SOURCE, "rb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- load\n");
        return false;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) < LIN * COL) {
        fprintf(stderr, "Erro - arquivo corrompido!\n");
        return false;
    }
    fseek(file, 0, SEEK_SET);

    fread(mapa, LIN * COL * sizeof (int), 1, file);

    fclose(file);

    return true;
}

bool load_undo() {
    FILE *file = fopen(UNDO_SOURCE, "rb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- load\n");
        return false;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) < LIN * COL) {
        fprintf(stderr, "Erro - arquivo corrompido!\n");
        return false;
    }
    fseek(file, 0, SEEK_SET);

    fread(mapa, LIN * COL * sizeof (int), 1, file);

    fclose(file);

    return true;
}

bool load_redo() {
    FILE *file = fopen(REDO_SOURCE, "rb+");
    if (file == NULL) {
        fprintf(stderr, "Erro ao carregar arquivo -- load\n");
        return false;
    }
    fseek(file, 0, SEEK_END);
    if (ftell(file) < LIN * COL) {
        fprintf(stderr, "Erro - arquivo corrompido!\n");
        return false;
    }
    fseek(file, 0, SEEK_SET);

    fread(mapa, LIN * COL * sizeof (int), 1, file);

    fclose(file);
    return true;
}
