#ifndef MINE_H_INCLUDED
#define MINE_H_INCLUDED

#include "CommonFunc.h"
#include "MainObj.h"

class Mine : public MainObj{
private:

    int Max_y;
    bool Up;

public:

    Mine();
    ~Mine();
    void Pos();
    void Show(SDL_Renderer* des);
    bool Boom(SDL_Renderer* des, Mix_Chunk* s_boom = NULL);
};



#endif // MINE_H_INCLUDED
