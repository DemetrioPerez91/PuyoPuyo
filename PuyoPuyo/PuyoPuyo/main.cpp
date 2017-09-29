

//Using SDL and standard IO
#include "defines.h"
#include "Controller.h"
using namespace std;


//SDL INITIALIZATIONS
SDL_Surface * screen = NULL;
SDL_Window * window = NULL;
SDL_Surface* test = NULL;
Mix_Music * bgm = NULL;

//Main View


//Events Controll
bool quit = false;
bool pause = false;
SDL_Event e;

//METHOD DECLARATIONS
bool init();


//initiate screen, window ttf and sound
bool init(){
    bool success =true;
    TTF_Init();
    if(SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO)<0){
        printf("SDL ERROR ");
        success = false;
    }
    else{
        window = SDL_CreateWindow("Puyo Puyo",50,50,SCREEN_W,SCREEN_H,SDL_WINDOW_SHOWN);
        if(window==NULL){
            printf("SDL Window error ");
            success = false;
        }else{
            screen = SDL_GetWindowSurface(window);
            
            if(screen == NULL){
                printf("Screen error");
                success = false;
            }else{
                if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048)<0){
                    
                    printf("SDL audio error !");
                    
                    
                }
                bgm = Mix_LoadMUS(JTHEME);
                Mix_VolumeMusic(MIX_MAX_VOLUME/4);
                
            }
            
        }
    }
    return success;
}
void close()
{
    SDL_FreeSurface(screen);
    screen = NULL;
    SDL_DestroyWindow(window);
    window=NULL;
    
    
}
void handlePause(Controller & controller){
    while( SDL_PollEvent( &e ) != 0 ) { //User requests quit
        if( e.type == SDL_QUIT ) {
            quit = true;
            pause = false;
        }
        else if( e.type == SDL_KEYDOWN ) {
            switch( e.key.keysym.sym ) {
                case SDLK_1:
                    pause = false;
                    printf("pause");
                    break;
                case SDLK_2:
                    controller.reset();
                    pause = false;
                    break;
                case SDLK_3:
                    quit = true;
                    pause = false;
                    break;
                case SDLK_RETURN:
                    pause = false;
                    printf("pause");
                    
                    break;
                default:
                    break;
            }
        }
        SDL_UpdateWindowSurface(window);
        
    }
    
}

int main( int argc, char* args[] )
{
    
    
    
    if(init()){
        
        
        
    }
    
    
    //Mix_PlayMusic(bgm,-1);
    Controller controller = Controller(screen,window);
    while(!quit){
        if(pause){
            controller.pause();
            handlePause(controller);
        }else{
            SDL_BlitSurface(test,NULL,screen,NULL);
            //call controller
            if(!controller.gameover){
                controller.flow();
            }
            else{
                controller.goScreen();
            }
            SDL_UpdateWindowSurface(window);
            SDL_Delay(100);
            //TAKE USER INPUT IN
            while( SDL_PollEvent( &e ) != 0 ) { //User requests quit
                if( e.type == SDL_QUIT ) {
                    quit = true;
                    
                }
                else if( e.type == SDL_KEYDOWN ) {
                    switch( e.key.keysym.sym ) {
                            
                        case SDLK_UP:
                            controller.changePose();
                            break;
                        case SDLK_LEFT:
                            controller.moveLeftPlayer();
                            break;
                        case SDLK_RIGHT: 
                            controller.moveRightPLayer();
                            break; 
                        case SDLK_SPACE:
                            if(controller.gameover){
                                controller.reset();
                            }
                            break;
                        case SDLK_RETURN:
                            pause = true;
                            //printf("pause");
                            controller.pause();
                            
                            break;
                        default: 
                            break; 
                    } 
                }else if( e.type == SDL_MOUSEBUTTONDOWN ) {
                    if( e.button.button == SDL_BUTTON_LEFT ) {
                        //get grid positions
                        int currX = e.button.x;
                        int currY = e.button.y;
                        int xCoord = floor(((float)currX-WMIN)/50);
                        int yCoord = floor(((float)currY-HMIN)/50);
                        if((currX>=WMIN&&currX<=WMIN+(BOARDX*50))&&(currY>=0&&currY<=HMIN+(BOARDY*50))){
                            controller.changeColors(xCoord,yCoord);
                        }
                        
                        
                    }
                    
                }
                SDL_UpdateWindowSurface(window);
                
            }
        }
        
        
        
    }  
    close();
    
    return 0;
}
