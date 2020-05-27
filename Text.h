#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include "CommonFunc.h"
#include "BaseObj.h"

class Text : public BaseObj{

protected:
    std::string textureText;
    SDL_Color textColor;
	int t_width;
	int t_height;

public:
	Text();
	~Text();
    void SetText(std::string textureText_){
        textureText = textureText_;
    }
    void SetColor(SDL_Color textColor_){
        textColor = textColor_;
    }
	bool LoadFromRenderedText(TTF_Font* font, SDL_Renderer* screen);
	void ChangeColor(SDL_Rect point_);
	void Render(SDL_Renderer* screen, int x, int y, const SDL_Rect* clip = NULL);
};

#endif // TEXT_H_INCLUDED
