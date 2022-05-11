#ifndef __TEXT__
#define __TEXT__
#define INCLUDE_SDL
#define INCLUDE_SDL_TTF
#include <string>
#include "SDL_include.hpp"
#include "Component.hpp"
#include "Timer.hpp"
#define BLINK_TIME 1

class Text : public Component {
    public:
        enum TextStyle { SOLID, SHADED, BLENDED }; 

    private:
        std::shared_ptr<TTF_Font> font;
        SDL_Texture* texture;

        std::string fontFile;
        int fontSize;
        TextStyle style;
        std::string text;
        SDL_Color color;
        Timer blinkTimer;
        bool blinkFlag;
        bool blink;

        void RemakeTexture();

    public:
        Text(GameObject& associated, std::string fontFile, 
            int fontSize, TextStyle style, std::string text, 
            SDL_Color color, bool blink = false);
        ~Text();
        void Update(float dt);
        void Render();
        bool Is(std::string type);

        void SetFontFile(std::string fontFile);
        void SetFontSize(int fontSize);
        void SetStyle(TextStyle style);
        void SetText(std::string text);
        void SetColor(SDL_Color color);
};

#endif