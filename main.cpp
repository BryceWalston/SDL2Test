//#include statements.
#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

//using statements
using std::string;

//screen width and height.
const int SCREEN_WIDTH = 500;
const int SCREEN_HEIGHT = 500;
const char image[] = "img/yan_vismok.bmp";

//function prototypes.
bool init(SDL_Window *&, SDL_Surface *&);
SDL_Surface * loadSurface(string);
void close(SDL_Window *&, SDL_Surface *&);
bool loadMedia();

//key press surfaces
enum KeyPressSurfaces{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP, 
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

SDL_Surface * gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

int main(int argc, char* args[]){

    //the window and two surfaces we will be using.
    SDL_Window * gWindow = nullptr;

    SDL_Surface * gScreenSurface = nullptr;

    SDL_Surface * gCurrentSurface = nullptr;

    //startup SDL and create window.
    if(!init(gWindow, gScreenSurface)){
        printf("Failed to initialize!\n");
        exit(-1);
    }

    if(!loadMedia()){
        printf("Failed to load media!\n");
        exit(-1);
    }

    //mainloop
    SDL_Event e;
    bool quit = false;
    while(quit == false){
            while(SDL_PollEvent(&e)){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN){

                        switch(e.key.keysym.sym){
                            case SDLK_UP:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                            break;

                            case SDLK_DOWN:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                            break;

                            case SDLK_LEFT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                            break;

                            case SDLK_RIGHT:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                            break;

                            default:
                            gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                            break;

                        }
                        
                        SDL_BlitSurface(gCurrentSurface,nullptr,gScreenSurface,nullptr);
                        SDL_UpdateWindowSurface(gWindow);

                    }

            }

    }

    //Free resources and close SDL.
    close(gWindow, gCurrentSurface);

    return 0;
}

SDL_Surface * loadSurface(string path){

    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if(loadedSurface == nullptr){
        printf("Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }

    return loadedSurface;

}

bool init(SDL_Window * &w1, SDL_Surface * &s1){

    //success flag.
    bool success = true;

    //initalize sdl.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
            printf("SDL could not initialize: SDL_Error: %s\n",SDL_GetError());
            success = false;
    }
    else{

        ///create the window.
        w1 = SDL_CreateWindow("Yan Vismok", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(w1 == nullptr){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        else{
                //get window surface.
                s1 = SDL_GetWindowSurface(w1);
        }

    }

    return success;
}


void close(SDL_Window * &w1, SDL_Surface * &s1){

    //deallocate surface.
    SDL_FreeSurface(s1);
    s1 = nullptr;

    //destroy window.
    SDL_DestroyWindow(w1);
    w1 = nullptr;

    //quit sdl subsytems.
    SDL_Quit();

}

bool loadMedia(){

        bool success = true;
        gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("img/default.bmp");

        if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr){
            printf("failed to load default image");
            return false;
        }

        gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("img/u.bmp");
        
        if(gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr){
            printf("failed to load up image");
            return false;
        }
        gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("img/d.bmp");
        
        if(gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr){
            printf("failed to load down image");
            return false;
        }

        gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("img/l.bmp");
        
        if(gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr){
            printf("failed to load left image");
            return false;
        }


        gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("img/r.bmp");
        
        if(gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr){
            printf("failed to load right image");
            return false;
        }

        return true;
}