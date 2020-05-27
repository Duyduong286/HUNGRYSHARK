#include "Text.h"

Text::Text(){
    t_width = 0;
    t_height = 0;

    p_obj_ = NULL;

    textColor = color;
    textureText = "NULL";
}

Text::~Text(){

}

bool Text::LoadFromRenderedText(TTF_Font* font, SDL_Renderer* screen){
   //Free();
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);

    p_obj_ = SDL_CreateTextureFromSurface(screen, textSurface);
    t_width  = textSurface -> w;
    t_height = textSurface -> h;
    SDL_FreeSurface(textSurface);
    return p_obj_ != NULL;
}

void Text::ChangeColor(SDL_Rect point_){
    if(SDLCommonFunc::CheckCollision(point_, rect_)){
        textColor = color1;
    }else{
        textColor = color;
    }
}

void Text::Render(SDL_Renderer* screen, int x, int y, const SDL_Rect* clip){
    rect_ = { x, y, t_width, t_height };
    if (clip != NULL)
    {
        rect_.w = clip -> w;
        rect_.h = clip -> h;
    }
    SDL_RenderCopyEx(screen, p_obj_, clip, &rect_, 0.0, NULL, SDL_FLIP_NONE);
}
