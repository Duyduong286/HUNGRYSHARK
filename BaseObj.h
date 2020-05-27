#ifndef BASEOBJ_H_INCLUDED
#define BASEOBJ_H_INCLUDED

#include "CommonFunc.h"

class BaseObj{

protected:
    SDL_Texture* p_obj_;
    SDL_Rect rect_;
    bool ret;
public:
    BaseObj();
    ~BaseObj();
    void SetRect(const int& x, const int& y){
        rect_.x = x;
        rect_.y = y;
    }
    SDL_Texture* GetObject() const {return p_obj_;}
    virtual SDL_Rect GetRect(){return rect_;}
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    virtual void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    bool Ret(){return ret;}
    void SetRet(bool ret_){ret = ret_;}
    void SetXY(int x, int y){
        rect_.x = x;
        rect_.y = y;
    }
    void Free();
};


#endif // BASEOBJ_H_INCLUDED
