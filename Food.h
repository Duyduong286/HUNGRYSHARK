#ifndef FOOD_H_INCLUDED
#define FOOD_H_INCLUDED

#include "CommonFunc.h"
#include "MainObj.h"

class Food : public MainObj {
protected:
    int f_right;
    int f_left;
    int f_top;
    int f_bot;

    std::string file_img;
    std::string food_left;
    std::string food_right;

    SDL_Rect rect_food;

    Input input_type_;

    int status_;

public:
    Food();
    ~Food();
    enum Walktype{
        SWIM_RIGHT = 0,
        SWIM_LEFT  = 1,
    };

    void SetName(){
        food_right = file_img + "right.png";
        food_left = file_img + "left.png";
    }

    void SetFile(std::string file_img_){
        file_img = file_img_;
    }

    std::string GetNameLeft(){return food_left;}
    std::string GetNameRight(){return food_right;}
    virtual void Show(SDL_Renderer* des);
    void Move(SDL_Renderer* des);
    void Pos();
    virtual void Orbit();
    void Positional();
    int get_status(){return status_;}
    void set_status(int status){status_ = status;}
    void change_status();
    void CheckMap();
    void Eat(bool success);
};

class Mermaid : public Food {
protected:
    std::string orbit_;
    bool stop_;
public:
    Mermaid();
    ~Mermaid();
    void SetOrbit(std::string orbit){
        orbit_ = orbit;
    }
    void Sound(Mix_Chunk* Sound);
    void Show(SDL_Renderer* des);
    void Pos();
    int GetStop(){return stop_;}
    void SetStop(bool stop){stop_ = stop;}
    bool Check();
};


#endif // FOOD_H_INCLUDED
