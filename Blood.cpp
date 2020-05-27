#include "Blood.h"

Blood::Blood(){
}

Blood::~Blood(){
}

void Blood::Render(SDL_Renderer* des, const SDL_Rect* clip ){
    rect_.x += BLEED ;
    BaseObj::Render(des);
}

void Blood::PlusB(int plus_){
    if(rect_.x > SCREEN_WIDTH - 882 ){ // khong tang qua thanh mau
        rect_.x -= plus_ ;
    }
}

void Blood::MinusB(int minus_){
    if(rect_.x >= SCREEN_WIDTH - 600){
        rect_.x += (SCREEN_WIDTH - rect_.x) / 2 ; // den mot muc mau nao do cham vao bom chi mat mot nua mau
    }else {
        rect_.x += minus_;
    }
}

bool Blood::Check(SDL_Window* window, Mix_Chunk* s_dead){
    if(rect_.x >= SCREEN_WIDTH - 50){
        int success = 0;
        if(rect_.x >= SCREEN_WIDTH - 50){
            Mix_PlayChannel(-1, s_dead, 0);
            SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
                             "OH NO",
                             "YOU'RE DEAD!!!",
                             window);
            return true;
        }
    }
    return false;
}
