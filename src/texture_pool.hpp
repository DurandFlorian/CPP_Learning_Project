#pragma once
#include "GL/texture.hpp"

#include <map>

class TexturePool
{
private:
    std::map<MediaPath, std::unique_ptr<GL::Texture2D>> textures;

public:
    const GL::Texture2D& get_texture(const MediaPath& path, int num_tiles);
};