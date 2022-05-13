#ifndef __TILEMAP__
#define __TILEMAP__
#include <vector>
#include "Component.hpp"
#include "TileSet.hpp"

/**
 * Game TileMap
 * 
 * Loads tilemap file, and maps each number to a 
 * specified tile loaded from tileset
 * */
class TileMap : public Component {
    private:
        std::vector<int> tileMatrix;
        TileSet* tileSet;
        int mapWidth;
        int mapHeight;
        int mapDepth;

    public:
        TileMap(GameObject& associated, std::string file, TileSet* tileSet);
        void Start();
        void Load(std::string file);
        void SetTileSet(TileSet* tileSet);
        int At(int x, int y, int z = 0);
        void Render();
        void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
        int GetWidth();
        int GetHeight();
        int GetDepth();
        void Update(float dt);
        bool Is(std::string type);
};

#endif