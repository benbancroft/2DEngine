#include "asset.h"

using namespace Assets;

Asset::Asset(AssetType type, std::string url)
{
  this->type = type;
  this->url = url;
}

AssetType Asset::getType()
{
  return this->type;
}

std::string Asset::getUrl()
{
  return this->url;
}