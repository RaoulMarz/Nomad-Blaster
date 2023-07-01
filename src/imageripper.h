#ifndef IMAGERIPPER_CLASS_H
#define IMAGERIPPER_CLASS_H

// We don't need windows.h in this example plugin but many others do, and it can
// lead to annoying situations due to the ton of macros it defines.
// So we include it and make sure CI warns us if we use something that conflicts
// with a Windows define.
#ifdef WIN32
#include <windows.h>
#endif

#include <thread>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <vector>
#include <memory>
#include <map>
#include "FastNoise.h"

using namespace godot;

enum ImageNoiseType {
		STATIC_NOISE,
		VALUE_NOISE,
		VALUEFRACTAL_NOISE,
		PERLIN_NOISE,
		PERLINFRACTAL_NOISE,
		SIMPLEX_NOISE,
		SIMPLEXFRACTAL_NOISE,
		CELLULAR_NOISE,
	};

class ImageRipper : public Control {
	GDCLASS(ImageRipper, Control);

protected:
	static void _bind_methods();
	String _to_string() const;

public:
	// -- enum ImageNoiseType
	ImageRipper();
	~ImageRipper();

    void simple_func();
	void set_image_path(String path);
	void set_size(Vector2 imgSize);
	void create_noise_image(ImageNoiseType noiseValue, int seed, float frequency, int fractalOctaves);
	void create_noise_image_textparam(String noiseParam, int seed, float frequency, int fractalOctaves);
	TypedArray</*Vector2*/uint> get_pixels_raw() const;
	TypedArray<Color> get_pixels() const;
	PackedByteArray get_data() const;

private:
	Vector2 custom_position;
	Vector2 irSize;
	Vector2 dprop[3];
	std::unique_ptr<std::vector<uint>> pixelData;
	std::unique_ptr<FastNoise> imageNoiseMakerFluff;
	std::unique_ptr<std::thread> threadObject;
	std::map<std::string, ImageNoiseType> mapNoiseTypes;

	ImageNoiseType _getNoiseTypeFromString(std::string noiseParam);
	void _setNoiseType(ImageNoiseType noiseValue);
	Color _generate_color(uint rawvalue) const;
};

//VARIANT_ENUM_CAST(ImageRipper, ImageRipper::ImageNoiseType);

#endif
