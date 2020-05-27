#ifndef BLOOD_H_INCLUDED
#define BLOOD_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObj.h"

class Blood : public BaseObj{
protected:
    int plus_B;
    int minus_B;
public:
    Blood();
    ~Blood();
    void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
    void PlusB(int plus_);
    void MinusB(int minus_);
    bool Check(SDL_Window* window = NULL, Mix_Chunk* s_dead = NULL);
};


#endif // BLOOD_H_INCLUDED
