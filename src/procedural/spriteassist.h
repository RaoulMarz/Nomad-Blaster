#ifndef SPRITE_ASSIST_CLASS_H
#define SPRITE_ASSIST_CLASS_H

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/texture2d.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/rect2i.hpp>
#include <map>
#include <string>
#include <optional>
#include <iomanip>
#include "pathutilities.h"
#include "resourceutilities.h"

class SpriteAssist {
private:
	godot::Sprite2D spriteImageCapture;
	std::string saveImagePath;
	std::map<std::string, godot::Ref<godot::Texture2D>> mapSpriteCache;
	std::map<std::string, int> mapSlicedSubTiles;
public:
	std::optional<godot::Ref<godot::Texture2D>> load_sprite_fromcache(godot::String folderspec, godot::String spriteRes);
	std::optional<godot::Ref<godot::Texture2D>> get_texture(godot::String spriteResourcePath, int columnIndex, int rowIndex);
	void slice_regions_tileset_image(godot::String spriteResourcePath, int columns, int rows);
};

#endif