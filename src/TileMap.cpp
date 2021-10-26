#include <fstream>
#include "../include/TileMap.hpp"
#include "../include/Camera.hpp"

TileMap::TileMap(std::string file, TileSet* tileSet, GameObject&  associated) : Component(associated) {
    this->tileSet = tileSet;
    this->Load(file);
}

void TileMap::Start() {}

/**
 * Loads tilemap specified file and saves it into tilematrix
 * Files must define width, height and depth in first 3 items
 * */
void TileMap::Load(std::string file) {
    std::string file_str, tmp;
    std::ifstream tfile(file);

    // reads from file
    if(tfile.is_open()) {    
        while(std::getline(tfile, tmp)) {
            file_str += tmp;
        }
        tfile.close();
    }

    // transforms input into an int type
    size_t pos = 0;
    while((pos = file_str.find(",")) != std::string::npos) {
        std::string vl = file_str.substr(0, pos);
        tileMatrix.push_back( std::stoi(vl) - 1 );
        file_str.erase(0, pos + 1);
    }

    mapWidth = tileMatrix[0] + 1;
    mapHeight = tileMatrix[1] + 1;
    mapDepth = tileMatrix[2] + 1;

    tileMatrix.erase(tileMatrix.begin(), tileMatrix.begin() + 3);
}

void TileMap::SetTileSet(TileSet* tileSet) {
    this->tileSet = tileSet;
}

/**
 * Transforms 3D coordinates to 1D coordinates
 * (x,y,z) -> (index)
 * */
int TileMap::At(int x, int y, int z) {
    int index = (z * mapWidth * mapHeight) + (y * mapWidth) + x;
    return index;
}

/**
 * Renders specified tilemap layer
 * Layer corresponds to z axis, starting at 0
 * */
void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for(int i=0;i<mapHeight;i++) {
        for(int j=0;j<mapWidth;j++) {
            int block = tileMatrix[ this->At(j,i,layer) ];
            float xpos = (tileSet->GetTileWidth() * j) - cameraX;
            float ypos = (tileSet->GetTileHeight() * i) - cameraY;
            tileSet->RenderTile(block, xpos, ypos);
        }
    }
}

/**
 * Renders all tilemap layers
 * */
void TileMap::Render() {
    for(int i=0;i<mapDepth;i++) {
        // multiply camera position by depth for the parallax effect
        this->RenderLayer(i, Camera::pos.x * (i+1), Camera::pos.y * (i+1));
    }
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Update(float dt)  {}

bool TileMap::Is(std::string type) {
    return (type == "TileMap");
}