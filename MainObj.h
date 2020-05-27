#ifndef MAINOBJ_H_INCLUDED
#define MAINOBJ_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObj.h"

class MainObj : public BaseObj {
protected:
    int frame_;
    int amount_frame_;

    int width_frame_;
    int height_frame_;

    bool plus_frame;

    int pos_x_;
    int pos_y_;

    SDL_Rect frame_clip_[10];
    SDL_Rect rect_head;
    SDL_Rect rect_full;

    Input input_type_;

    int status_;

public:
    MainObj();
    ~MainObj();

    enum Walktype{
        SWIM_RIGHT = 0,
        SWIM_LEFT  = 1,
    };

    bool LoadImg(std::string path, SDL_Renderer* screen);
    virtual void Show(SDL_Renderer* des, bool eat, Mix_Chunk* s_eat[4] = NULL);
    virtual void Pos(SDL_Event events);
    void HandelInputAction(SDL_Event);
    void set_clip();
    void SetAmount(int amount_frame){
        amount_frame_ = amount_frame;
    }
    SDL_Rect GetRect_Head();
    SDL_Rect GetRect();
};


#endif // MAINOBJ_H_INCLUDED
