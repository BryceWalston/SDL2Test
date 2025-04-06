//#include statements.
#include <SDL2/SDL.h>
#include <stdio.h>

//screen width and height.
const int SCREEN_WIDTH = 241;
const int SCREEN_HEIGHT = 317;
const char image[] = "img/yan_vismok.bmp";

//function prototypes.
bool init(SDL_Window *&, SDL_Surface *&);
bool loadMedia(SDL_Surface *&);
void close(SDL_Window *&, SDL_Surface *&);



int main(int argc, char* args[]){

    //the surfaces we will be using.
    SDL_Window * gWindow = nullptr;

    SDL_Surface * gScreenSurface = nullptr;

    SDL_Surface * gHelloWorld = nullptr;

    //startup SDL and create window.
    if(!init(gWindow, gScreenSurface)){
        printf("Failed to initialize!\n");
    }
    else{

        //load media.
        if(!loadMedia(gHelloWorld)){
                printf("Failed to load media!\n");
        }
        else{
            //apply the image.
            if(SDL_BlitSurface(gHelloWorld, nullptr, gScreenSurface, nullptr)){
                printf("Failed to Blit Surface: SDL Error: %s!", SDL_GetError());
            }
            //update the surface.
            SDL_UpdateWindowSurface(gWindow);
        }

    }

    if(gHelloWorld == nullptr){
        printf("gHelloWorld is null.\n");
    }
    if(gScreenSurface == nullptr){
        printf("gScreenSurface is null.\n");
    }
    if(gWindow == nullptr){
        printf("gWindow is null.\n");
    }

    //mainloop
    SDL_Event e;
    bool quit = false;
    while(quit == false){
            while(SDL_PollEvent(&e)){
                    if(e.type == SDL_QUIT){
                        quit = true;
                    }
            }
    }

    //Free resources and close SDL.
    close(gWindow, gHelloWorld);

    return 0;
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

bool loadMedia(SDL_Surface * &s1){

    //success flag.
    bool success = true;

    //load image.
    s1 = SDL_LoadBMP(image);

    if(s1 == nullptr){
        printf("Unable to load image: %s! SDL Error: %s\n", image, SDL_GetError());        
        success = false;

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