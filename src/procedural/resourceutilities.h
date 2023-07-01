#ifndef RESOURCE_UTILITIES_CLASS_H
#define RESOURCE_UTILITIES_CLASS_H

#include <filesystem>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <string>
#include <vector>
#include <optional>

class ResourceUtilities {
    public:
    static std::optional<godot::Ref<godot::Texture2D>> getExternalTexture(godot::String resPath) {
        /*
        Image img = new Image();
            img.Load(imagePath);
            ImageTexture texture = ImageTexture.CreateFromImage(img);
            return texture;
        */
        std::optional<godot::Ref<godot::Texture2D>> res = std::nullopt;
        if (resPath.length() > 0) {
            godot::Ref<godot::Image> imageTex = godot::Image::load_from_file(resPath);
            //godot::Ref<godot::ImageTexture> textureBuf = godot::ImageTexture::create_from_image(imageTex);
            godot::Ref<godot::Texture2D> textureBuf = godot::ImageTexture::create_from_image(imageTex);
            if (textureBuf.is_valid()) {
                //godot::Texture2D textureValue = *textureBuf;
                res = textureBuf;
            }
        }
        return res;
    }
};

#endif