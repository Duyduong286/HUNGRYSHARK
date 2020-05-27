#include "Mine.h"

Mine::Mine(){
    Max_y = rand() % (SCREEN_HEIGHT - 100 + 1) + 0;
    Up = true;
}

Mine::~Mine(){
}

void Mine::Pos(){
    rect_.x = rand() % (SCREEN_WIDTH - 100 + 1) + 0;
    rect_.y = SCREEN_HEIGHT;
}

void Mine::Show(SDL_Renderer* des){
    if(rect_.y > Max_y){rect_.y -= speed_M;}
    if(rect_.y <= Max_y){
        if(Up){
            rect_.y --;
        }else{
            rect_.y ++;
        }
        if(rect_.y == Max_y - 5){
            Up = false;
        }
        if(rect_.y == Max_y){
            Up = true;
        }
    }

    BaseObj::Render(des);
}

bool Mine::Boom(SDL_Renderer* des, Mix_Chunk* s_boom){
    Mix_PlayChannel(-1, s_boom, 0);
    BaseObj::Render(des);
}


