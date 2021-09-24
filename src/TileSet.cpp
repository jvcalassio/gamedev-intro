#include "../include/TileSet.hpp"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) {
    this->tileWidth = tileWidth;
    this->tileHeight = tileHeight;
    // empty gameobject since sprite requires a gameobject
    GameObject* go = new GameObject(); 
    tileSet = new Sprite(file, *go);

    if(tileSet->IsOpen()) {
        this->rows = tileSet->GetWidth() / tileWidth;
        this->columns = tileSet->GetHeight() / tileHeight;
    }
}

/**
 * Renders the tile number {index}
 * at screen position x,y
 * */
void TileSet::RenderTile(int index, float x, float y) {
    int total_tiles = rows * columns;
    if(index >= 0 && index < total_tiles) {
        int tx = (index % rows) * tileWidth;
        int ty = (index / rows) * tileHeight;
        tileSet->SetClip(tx, ty, tileWidth, tileHeight);
        tileSet->Render(x, y);
    }
}

int TileSet::GetTileWidth() {
    return tileWidth;
}

int TileSet::GetTileHeight() {
    return tileHeight;
}