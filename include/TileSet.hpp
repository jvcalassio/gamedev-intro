#ifndef __TILESET__
#define __TILESET__
#include <string>
#include "Sprite.hpp"

/**
 * TileSet used by TileMap
 * Loads tileset sprite, and defines each tile width, height
 * number of columns and number of rows
 * */
class TileSet {
    private:
        Sprite* tileSet;
        int rows;
        int columns;
        int tileWidth;
        int tileHeight;

    public:
        TileSet(int tileWidth, int tileHeight, std::string file);
        void RenderTile(int index, float x, float y);
        int GetTileWidth();
        int GetTileHeight();
};

#endif