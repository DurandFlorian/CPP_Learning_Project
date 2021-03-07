#include "texture_pool.hpp"
#include <memory>

const GL::Texture2D& TexturePool::get_texture(const MediaPath& path,int num_tiles){
            auto texture = textures.find(path);
            if(texture!=textures.end()){
                return *(texture->second.get());
            }

            return *(textures.emplace(path,std::make_unique<GL::Texture2D> ( new img::Image { path.get_full_path() }, num_tiles )).first->second.get());
                    }