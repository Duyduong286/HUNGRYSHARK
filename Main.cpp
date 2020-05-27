#include "CommonFunc.h"
#include "BaseObj.h"
#include "MainObj.h"
#include "ImpTimer.h"
#include "Food.h"
#include "Text.h"
#include "Mine.h"
#include "Blood.h"

BaseObj g_background;
Text g_text;
Text fish;
Text pearl;

bool InitData();
bool ShowMenu();
bool PlayGame();
bool LoadMedia();
bool LoadBackGr();
bool LoadSound();
bool LoadMenuBackGr();
void ShowScore(int f_fish,int p_pearl);
void Close();

TTF_Font* LoadFont(std::string path, int SIZE);

std::vector<Food*> MakeFoodList();

int main(int argc, char* argv[]){
    if(InitData() == false){return -1;}
    if(LoadSound() == false){return -1;}
    Mix_PlayChannel(-1, s_bgr, -1);
    if(ShowMenu() == false){return -1;}
    Close();
    return 0;
}

bool PlayGame(){
    srand(time(NULL));
    SDL_SetRelativeMouseMode(SDL_TRUE);

    if(LoadBackGr() == false){return false;}

    BaseObj b_blood_back;
    b_blood_back.LoadImg("img//blood_back.png", g_screen);
    b_blood_back.SetXY(SCREEN_WIDTH - 882 - 33, 10);

    BaseObj h_heart;
    h_heart.LoadImg("img//heart.png", g_screen);
    h_heart.SetXY(SCREEN_WIDTH - 116, 0);

    Blood b_blood;
    b_blood.LoadImg("img//blood.png", g_screen);
    b_blood.SetXY(SCREEN_WIDTH - 882 , 20);

    MainObj p_player;
    p_player.LoadImg("img//player_right.png", g_screen);
    p_player.set_clip();
    p_player.Show(g_screen,false);

    Mine m_mine;
    m_mine.LoadImg("img//mine.png", g_screen);
    m_mine.Pos();

    Mermaid m_mermaid;
    m_mermaid.SetAmount(5);
    m_mermaid.SetFile("img//mermaid_");
    m_mermaid.SetName();
    m_mermaid.LoadImg("img//mermaid_right.png", g_screen);
    m_mermaid.SetOrbit("Line");
    m_mermaid.set_status(rand() % 2);
    m_mermaid.set_clip();
    m_mermaid.Pos();

    BaseObj p_pearl;
    p_pearl.LoadImg("img//Pearl.png", g_screen);

    std::vector <Food*> food_list = MakeFoodList();

    int sc_fish = 0; // so ca an
    int sc_pearl = 0; // so ngoc an
    int rand_; // so ngau nhien
    bool is_quit = false;

    while(!is_quit){
        while(SDL_PollEvent(&g_event) != 0){
            switch(g_event.type){
                case SDL_QUIT:
                    SDL_SetRelativeMouseMode(SDL_FALSE);
                    is_quit = true;
                    if(LoadMenuBackGr() == false){return false;}
                    break;
                case SDL_KEYDOWN:
                    if((int)g_event.key.keysym.sym == 27 ){
                        SDL_SetRelativeMouseMode(SDL_FALSE);
                        is_quit = true;
                        if(LoadMenuBackGr() == false){return false;}
                    }
                    break;
            }

            p_player.HandelInputAction(g_event);
        }

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen);

        bool boom = SDLCommonFunc::CheckCollision(p_player.GetRect(), m_mine.BaseObj::GetRect());
        if(boom && m_mine.Ret()){
            m_mine.LoadImg("img//boom.png", g_screen);
            m_mine.Boom(g_screen, s_boom);
            b_blood.MinusB(MINUS_BLOOD);
            m_mine.Free();
        }

        bool eat_ = false;
        for(int i = 0; i < amount_F; i++){
            if(food_list[i] != NULL){
                //xu ly an
                bool success = SDLCommonFunc::CheckCollision(p_player.GetRect_Head(), food_list[i] -> GetRect());
                if(success){
                    p_player.Pos(g_event);
                    p_player.Show(g_screen, success, s_eat);
                    eat_ = true;
                    sc_fish++;
                    b_blood.PlusB(PLUS_BLOOD);
                }
                //chuyen huong di cua food khi gap mine
                bool success_ = SDLCommonFunc::CheckCollision(m_mine.BaseObj::GetRect(), food_list[i] -> GetRect());
                if(success_){
                    food_list[i] -> change_status();
                }
                //kiem tra vi tri va chuyen dong cua food
                food_list[i] -> Positional();
                food_list[i] -> Eat(success);
                food_list[i] -> CheckMap();
                food_list[i] -> Show(g_screen);
            }
        }

        if(m_mine.Ret()){m_mine.Show(g_screen);}

        if(m_mermaid.GetStop() == true){// tao mot mermaind moi
            rand_ = rand()%(1 + 50 + 1) - 50;
            if(rand_ == 1){
                m_mermaid.Sound(s_mermaid);
                m_mermaid.SetStop(false);
                p_pearl.SetRet(true);
            }
        }

        if(m_mermaid.GetStop() == false){
            if(m_mermaid.Check() == false){
                if(p_pearl.Ret() == true){
                    //set vi tri cho ngoc
                    if(m_mermaid.get_status() == 1){
                        p_pearl.SetXY(m_mermaid.MainObj::GetRect().x + 231 - 64,
                                        m_mermaid.MainObj::GetRect().y);
                    }
                    if(m_mermaid.get_status() == 0){
                        p_pearl.SetXY(m_mermaid.MainObj::GetRect().x ,
                                        m_mermaid.MainObj::GetRect().y);
                    }
                    // xu ly an ngoc
                    bool success = SDLCommonFunc::CheckCollision(p_player.GetRect(), p_pearl.GetRect());
                    if(success){
                        p_pearl.SetXY(SCREEN_WIDTH, SCREEN_HEIGHT);
                        p_pearl.SetRet(false);
                        Mix_PlayChannel(-1, s_pearl, 0);
                        sc_pearl++;
                    }
                }
                p_pearl.Render(g_screen);
                m_mermaid.Show(g_screen);
            }else{
                m_mermaid.SetStop(true);
                m_mermaid.set_status(rand() % 2); // randdom status 1(left) 0(right)
                m_mermaid.Pos();
            }
        }


        if(!eat_){
            p_player.Pos(g_event);
            p_player.Show(g_screen, false);
        }

        b_blood_back.Render(g_screen);
        b_blood.Render(g_screen);
        if(b_blood.Check(g_window, s_dead)){
            SDL_SetRelativeMouseMode(SDL_FALSE);
            is_quit = true;
            if(LoadMenuBackGr() == false){return false;}
        }
        h_heart.Render(g_screen);
        ShowScore(sc_fish,sc_pearl);
        SDL_RenderPresent(g_screen);

        SDL_Delay(80); // lam cham de hieu ung chuyen dong muot hon

    }
    return true;
}


bool LoadBackGr(){

    bool ret = g_background.LoadImg("img/bg2.jpg", g_screen);
    if(ret == false){
        return false;
    }

    return true;
}

bool LoadMenuBackGr(){
    bool ret = g_background.LoadImg("img/bg1.jpg", g_screen);
    if(ret == false){
        return false;
    }
    return true;
}

bool ShowMenu(){
    if(LoadMenuBackGr() == false){return false;}

    SDL_Rect point = {0, 0, 0, 0};// vi tri tro chuot

    Text playnow, exit;
    TTF_Font* g_font = LoadFont("font/font.ttf", SIZE_TEXT);

	playnow.SetText("Play Now");
	playnow.LoadFromRenderedText(g_font, g_screen);

	exit.SetText("Exit");
	exit.LoadFromRenderedText(g_font, g_screen);

    bool is_quit = false;
    while(!is_quit){
		while(SDL_PollEvent(&g_event) != 0){
            switch(g_event.type){
                case SDL_QUIT:
                    is_quit = true;
                    break;
                case SDL_MOUSEMOTION:
                    SDL_GetMouseState(&point.x, &point.y);
                    playnow.ChangeColor(point);
                    exit.ChangeColor(point);
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(g_event.button.button == SDL_BUTTON_LEFT){
						SDL_GetMouseState(&point.x, &point.y);
                        Mix_PlayChannel(-1, s_push, 0); //am thanh khi an playnow va exit
						if(SDLCommonFunc::CheckCollision(point, playnow.GetRect())){
							PlayGame();
						}else{
							if(SDLCommonFunc::CheckCollision(point, exit.GetRect())){
								is_quit = true;
							}
						}

					}
			}
		}

        SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

        g_background.Render(g_screen);

		playnow.LoadFromRenderedText(g_font, g_screen);
		playnow.Render(g_screen, SCREEN_WIDTH/3 , 2*SCREEN_HEIGHT/5);

		exit.LoadFromRenderedText(g_font, g_screen);
		exit.Render(g_screen, SCREEN_WIDTH/3 + 150, 3*SCREEN_HEIGHT/5);

		SDL_RenderPresent(g_screen);
	}
    return true;
}

bool InitData(){

    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0){return false;}

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY,"1");
    g_window = SDL_CreateWindow("HUNGRY SHARK",
                                SDL_WINDOWPOS_CENTERED ,
                                SDL_WINDOWPOS_CENTERED ,
                                SCREEN_WIDTH,
                                SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN);
    if(g_window == NULL){
        success = false;
    }else{
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL){
            success = false;
        }else{
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags) && imgFlags)){
                success = false;
            }
            if(TTF_Init() == -1){
                success = false;
            }
            if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0){
                success = false;
            }
        }
    }
    return success;
}

std::vector<Food*> MakeFoodList(){
    std::vector <Food*> list_food;

    Food* food_objs = new Food[amount_F];
    Food* p_food = food_objs;
    int rand_;
    char file_img[30];
    for(int i = 0; i < amount_F; i++){
        rand_ = rand() % 4 + 1;
        sprintf(file_img, "img//food%d_", rand_);

        p_food = food_objs + i;
        p_food -> SetFile(file_img);
        p_food -> SetName();
        switch(rand_){
            case 1:
                p_food -> SetAmount(6);
                break;
            case 2:
                p_food -> SetAmount(8);
                break;
            case 3:
                p_food -> SetAmount(4);
                break;
            case 4:
                p_food -> SetAmount(8);
                break;
        }

        if(p_food != NULL){
            int rand_F = rand() % 2;
            if(rand_F == 0){
                p_food -> LoadImg(p_food -> GetNameRight(), g_screen);
                p_food -> set_status(0);
            }else{
                p_food -> LoadImg(p_food -> GetNameLeft(), g_screen);
                p_food -> set_status(1);
            }
            p_food -> set_clip();
            p_food -> Pos();
            list_food.push_back(p_food);
        }
    }
    return list_food;
}

TTF_Font* LoadFont(std::string path, int SIZE){
    TTF_Font*g_font = TTF_OpenFont("font//font.ttf", SIZE);
	return g_font;
}

bool LoadSound(){
    bool success = true;

    s_boom = Mix_LoadWAV("sound/Boom.wav");
	if (s_boom == NULL){success = false;}

    s_bgr = Mix_LoadWAV("sound/sound_bgr.wav");
    if (s_bgr == NULL){success = false;}

    s_eat[0] = Mix_LoadWAV("sound/eat1.wav");
    s_eat[1] = Mix_LoadWAV("sound/eat2.wav");
    s_eat[2] = Mix_LoadWAV("sound/eat3.wav");
    s_eat[3] = Mix_LoadWAV("sound/eat4.wav");
    if (s_eat[0] == NULL||
        s_eat[1] == NULL||
        s_eat[2] == NULL||
        s_eat[3] == NULL
        ){
        success = false;
    }

    s_push = Mix_LoadWAV("sound/push.wav");
    if (s_push == NULL){
        success = false;
    }

    s_mermaid = Mix_LoadWAV("sound/mermaid.wav");
    if (s_mermaid == NULL){
        success = false;
    }

    s_pearl = Mix_LoadWAV("sound/pearl.wav");
    if (s_pearl == NULL){
        success = false;
    }

    s_dead = Mix_LoadWAV("sound/dead.wav");
    if (s_dead == NULL){
        success = false;
    }

    return success;
}

void ShowScore(int f,int p)
{
    int x_f = SCREEN_WIDTH - 90;
    char sc_fish[10];
    itoa(f,sc_fish,10);
    while(f >= 10){ //dieu chinh vi tri in diem
        f/=10;
        x_f -= SIZE_SRORE;
	}

	SDL_Color textColor = { 255, 200,0 };
	TTF_Font* g_font = LoadFont("font//font.ttf",SIZE_SRORE);

	fish.SetColor(textColor);
	fish.SetText(sc_fish);
	fish.LoadFromRenderedText(g_font, g_screen);
	fish.Render(g_screen, x_f, 95);

    int x_p = SCREEN_WIDTH - 90;
    char sc_pearl[10];
    itoa(p,sc_pearl,10);

    while(p >= 10){ //dieu chinh vi tri in diem
        p/=10;
        x_p -= SIZE_SRORE;
	}

	pearl.SetColor(textColor);
	pearl.SetText(sc_pearl);
	pearl.LoadFromRenderedText(g_font, g_screen);
	pearl.Render(g_screen, x_p, 150);
}

void Close(){
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    Mix_Quit ();
    TTF_Quit();
    SDL_Quit();
}
