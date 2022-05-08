#ifndef __RESOURCES__
#define __RESOURCES__
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#define INCLUDE_SDL_TTF
#include <unordered_map>
#include <string>
#include <memory>
#include "SDL_include.h"

/**
 * Game resource manager
 * Loads all game resources (sprites, sounds) and keep them on record
 * 
 * It makes sure that the game won't load the same resource twice
 * */
class Resources {
    private:
        static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
        static std::unordered_map<std::string, Mix_Music*> musicTable;
        static std::unordered_map<std::string, Mix_Chunk*> soundTable;
        static std::unordered_map<std::string, TTF_Font*> fontTable;

    public:
        static std::shared_ptr<SDL_Texture> GetImage(std::string file);
        static void ClearImages();
        static Mix_Music* GetMusic(std::string file);
        static void ClearMusics();
        static Mix_Chunk* GetSound(std::string file);
        static void ClearSounds();
        static TTF_Font* GetFont(std::string file, int size);
        static void ClearFonts();
};

#endif