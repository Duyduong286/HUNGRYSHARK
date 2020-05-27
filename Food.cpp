#include "Food.h"

Food::Food(){

    f_right = 0;
    f_left  = 0;
    f_top   = 0;
    f_bot   = 0;

    status_ = -1;

}

Food::~Food(){
}

void Food::Pos(){
    rect_.x = rand() % (SCREEN_WIDTH - 0 + 1) + 0;
    rect_.y = rand() % (SCREEN_HEIGHT - 0 + 1) + 0;
}

void Food::Orbit(){
    if(status_ == SWIM_LEFT){
        rect_.x -= rand() % (5) + 1;
        rect_.y -= rand() % (5) + 1;
    }
    if(status_ == SWIM_RIGHT){
        rect_.x += rand() % (5) + 1;
        rect_.y += rand() % (5) + 1;
    }
}

void Food::Show(SDL_Renderer* des){

    if(status_ == SWIM_LEFT){LoadImg(food_left, des);}
    if(status_ == SWIM_RIGHT){LoadImg(food_right, des);}
    Orbit();

    frame_++;

    if(frame_ >= amount_frame_){
        frame_ = 0;
    }

    SDL_Rect* current_clip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};

    SDL_RenderCopy(des, p_obj_, current_clip, &renderQuad);

}

void Food::Positional(){
    f_right = rect_.x + width_frame_;
    f_left  = rect_.x;
    f_top   = rect_.y;
    f_bot   = rect_.y + height_frame_;
}

void Food::CheckMap(){
    if(f_bot <= 0){
        rect_.x = rand() % (SCREEN_WIDTH - 200 + 1) + 100;
        rect_.y = SCREEN_HEIGHT;
    }

    if(f_top >= SCREEN_HEIGHT){
        rect_.x = rand() % (SCREEN_WIDTH - 200 + 1) + 100;
        rect_.y = -height_frame_;
    }

    if(f_right <= 0){
        rect_.x = SCREEN_WIDTH;
        rect_.y = rand() % (SCREEN_HEIGHT - 200 + 1) + 100;
    }

    if(f_left >= SCREEN_WIDTH){
        rect_.x = -width_frame_;
        rect_.y = rand() % (SCREEN_HEIGHT - 200 + 1) + 100;
    }

}

void Food::Eat(bool success){
    if(success){
        int const_E = rand() % 4;
        switch(const_E){
            case 0:
                f_bot = -10;
                status_ = SWIM_LEFT;
                break;

            case 1:
                f_bot = SCREEN_HEIGHT + 10;
                status_ = SWIM_RIGHT;
                break;

            case 2:
                f_right = -10;
                status_ = SWIM_LEFT;
                break;

            case 3:
                f_right = SCREEN_WIDTH + 10;
                status_ = SWIM_RIGHT;
                break;
        }
    }
}

void Food::change_status(){
    if(status_ == SWIM_LEFT){
        status_ = SWIM_RIGHT;
    }
    if(status_ == SWIM_RIGHT){
        status_ = SWIM_LEFT;
    }
}

Mermaid::Mermaid(){
    stop_ = true;
}
Mermaid::~Mermaid(){
}

void Mermaid::Pos(){
    // randdom vi tri cua mermaid
    if(status_ == SWIM_RIGHT){
        rect_.x = - width_frame_;
    }else{
        rect_.x = SCREEN_WIDTH;
    }
    rect_.y = rand()%(SCREEN_HEIGHT/2 - SCREEN_HEIGHT/5 +1) + SCREEN_HEIGHT/5;
}


bool Mermaid::Check(){
    if(rect_.x > SCREEN_WIDTH || rect_.x < -width_frame_ ){
        return true;
    }
    return false;
}

void Mermaid::Sound(Mix_Chunk* Sound){
    Mix_PlayChannel(-1, Sound, 0);
}

void Mermaid::Show(SDL_Renderer* des){
    if(status_ == SWIM_LEFT){
        LoadImg(food_left, des);
        rect_.x -= speed_line;
    }
    if(status_ == SWIM_RIGHT){
        LoadImg(food_right, des);
        rect_.x += speed_line;
    }

    frame_++;
    if(frame_ >= amount_frame_){
        frame_ = 0;
    }

    SDL_Rect* current_clip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
    SDL_RenderCopy(des, p_obj_, current_clip, &renderQuad);
}
