#include "MainObj.h"

MainObj::MainObj(){
    frame_ = 0;
    amount_frame_ = 6;

    plus_frame = true;

    pos_x_ = SCREEN_WIDTH/2;
    pos_y_ = SCREEN_HEIGHT/2;

    rect_head.x = 0;
    rect_head.y = 0;
    rect_head.w = 0;
    rect_head.h = 0;

    width_frame_  = 0;
    height_frame_ = 0;

    status_ = -1;

    input_type_.left_ = 1;
    input_type_.right_ = 0;

}

MainObj::~MainObj(){
}

bool MainObj::LoadImg(std::string path, SDL_Renderer* screen){
    bool ret = BaseObj::LoadImg(path,screen);

    if(ret == true){
        width_frame_  = rect_.w / amount_frame_;
        height_frame_ = rect_.h;
    }

    return ret;
}

void MainObj::set_clip(){
    if(width_frame_ > 0 && height_frame_ >0){
        for(int i = 0; i < amount_frame_; i++){
            frame_clip_[i].x = i*width_frame_;
            frame_clip_[i].y = 0;
            frame_clip_[i].w = width_frame_;
            frame_clip_[i].h = height_frame_;
        }
    }
}

void MainObj::HandelInputAction(SDL_Event events){
        switch(events.type){
            case SDL_MOUSEMOTION :
                if(events.motion.xrel >= 0){
                    status_ = SWIM_RIGHT;
                    input_type_.right_ = 1;
                    input_type_.left_ = 0;
                }else{
                    status_ = SWIM_LEFT;
                    input_type_.left_ = 1;
                    input_type_.right_ = 0;
                }
                break;
            default :
                break;
    }
}

void MainObj::Pos(SDL_Event events){
    switch(events.type){
        case SDL_MOUSEMOTION :
            pos_x_ = events.motion.x;
            pos_y_ = events.motion.y;
            break;
        default :
            break;
    }
}

void MainObj::Show(SDL_Renderer* des, bool eat, Mix_Chunk* s_eat[4]){
    if(status_ == SWIM_LEFT){
        LoadImg("img/player_left.png", des);
    }else{
        LoadImg("img/player_right.png", des);
    }

    if(input_type_.left_ == 1 || input_type_.right_ == 1){
        if(plus_frame){frame_++;}else{frame_--;}
    }else{
        frame_ =0;
    }

    if(frame_ >= 4){
        plus_frame = false;
        frame_ = 4;
    }

    if(frame_ <= 0){
        plus_frame = true;
    }

    if(eat){
        frame_ = 5;
        Mix_PlayChannel(-1, s_eat[rand()%4], 0);
    }
    rect_.x = pos_x_;
    rect_.y = pos_y_;
    SDL_Rect* current_clip = &frame_clip_[frame_];
    SDL_Rect renderQuad = {rect_.x, rect_.y, width_frame_, height_frame_};
    SDL_RenderCopy(des, p_obj_, current_clip, &renderQuad);
}

SDL_Rect MainObj::GetRect_Head(){
    if(status_ == SWIM_LEFT){
        rect_head.x = rect_.x;
    }else{
        rect_head.x = rect_.x + width_frame_ * 4 / 5 ;
    }
    rect_head.y = rect_.y;
    rect_head.w = width_frame_ / 5;
    rect_head.h = rect_.h;

    return rect_head;
}

SDL_Rect MainObj::GetRect(){
    rect_full = BaseObj::GetRect();
    rect_full.w = rect_.w/amount_frame_;

    return rect_full;
}


