#ifndef ASSET_H
#define ASSET_H

#include <iostream>
#include <map>

namespace Assets
{

    enum AssetType { SHADER, TEXTURE, SPRITE_SHEET, TILE_SHEET };

    class Asset
    {
        AssetType type;
        std::string url;

    public:
      Asset(AssetType type, std::string url);
      AssetType getType();
      std::string getUrl();

    };

}

#endif
