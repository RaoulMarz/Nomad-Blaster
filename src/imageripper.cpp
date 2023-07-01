#include "imageripper.h"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

ImageRipper::ImageRipper() {
	imageNoiseMakerFluff = std::make_unique<FastNoise>();
	pixelData = std::make_unique<std::vector<uint>>();
	mapNoiseTypes["static"] = ImageNoiseType::STATIC_NOISE;
	mapNoiseTypes["value"] = ImageNoiseType::VALUE_NOISE;
	mapNoiseTypes["value_fractal"] = ImageNoiseType::VALUEFRACTAL_NOISE;
	mapNoiseTypes["perlin"] = ImageNoiseType::PERLIN_NOISE;
	mapNoiseTypes["perlin_fractal"] = ImageNoiseType::PERLINFRACTAL_NOISE;
}

ImageRipper::~ImageRipper() {
}

String ImageRipper::_to_string() const {
	return "[ GDExtension::ImageRipper <--> Instance ID:" + uitos(get_instance_id()) + " ]";
}

void ImageRipper::simple_func() {
	UtilityFunctions::print("  Simple func called.");
}

void ImageRipper::set_image_path(String path) {
	UtilityFunctions::print("set_image_path called.");
}

void ImageRipper::set_size(Vector2 imgSize) {
	UtilityFunctions::print("set_size called, size = " + imgSize);
	irSize = imgSize;
	pixelData->resize(irSize.x * irSize.y);
}

void ImageRipper::create_noise_image_textparam(String noiseParam, int seed, float frequency, int fractalOctaves) {
	if (noiseParam.length())
	{
		ImageNoiseType noiseTp = ImageNoiseType::PERLINFRACTAL_NOISE;// _getNoiseTypeFromString(noiseParam.utf16());
		create_noise_image(noiseTp, seed, frequency, fractalOctaves);
	}
}

void ImageRipper::create_noise_image(ImageNoiseType noiseValue, int seed, float frequency, int fractalOctaves) {
	pixelData->clear();
	_setNoiseType(noiseValue);
	imageNoiseMakerFluff->SetFractalLacunarity(1.75f);
	imageNoiseMakerFluff->SetFrequency(frequency);
	imageNoiseMakerFluff->SetFractalGain(0.45f);
	imageNoiseMakerFluff->SetFractalOctaves(fractalOctaves);
	imageNoiseMakerFluff->SetFractalType(FastNoise::FractalType::FBM);
	imageNoiseMakerFluff->SetInterp(FastNoise::Interp::Hermite);
	UtilityFunctions::print("create_noise_image called, frequency = " + rtos(frequency) + " , gain = " + rtos(0.45f) + " , octaves = " + uitos(fractalOctaves));
	if (imageNoiseMakerFluff->GetNoiseType() == FastNoise::NoiseType::Cellular) {
		imageNoiseMakerFluff->SetCellularDistanceFunction(FastNoise::CellularDistanceFunction::Euclidean);
		imageNoiseMakerFluff->SetCellularJitter(1.0f);
		imageNoiseMakerFluff->SetCellularReturnType(FastNoise::CellularReturnType::Distance2);
	}
	for (int xp = 0; xp < irSize.x; xp++) {
		for (int yp = 0; yp < irSize.y; yp++) {
			(*pixelData)[xp + (yp * irSize.x)] = imageNoiseMakerFluff->GetNoise(xp, yp);
		}
	}
}

TypedArray<uint> ImageRipper::get_pixels_raw() const {
	TypedArray<uint> arr;

	arr.resize(irSize.x * irSize.y);
	//arr[0] = Vector2(1, 2);
	//arr[1] = Vector2(2, 3);
	for (int xp = 0; xp < irSize.x; xp++) {
		for (int yp = 0; yp < irSize.y; yp++) {
			arr[xp + (yp * irSize.x)] = (*pixelData)[xp + (yp * irSize.x)];
		}
	}

	return arr;
}

TypedArray<Color> ImageRipper::get_pixels() const {
	TypedArray<Color> arr;

	arr.resize(irSize.x * irSize.y);
	for (int xp = 0; xp < irSize.x; xp++) {
		for (int yp = 0; yp < irSize.y; yp++) {
			arr[xp + (yp * irSize.x)] = _generate_color( (*pixelData)[xp + (yp * irSize.x)]);
		}
	}
	return arr;
}

PackedByteArray ImageRipper::get_data() const {
	PackedByteArray result;
	result.resize(irSize.x * irSize.y);
	for (int xp = 0; xp < irSize.x; xp++) {
		for (int yp = 0; yp < irSize.y; yp++) {
			result[xp + (yp * irSize.x)] = (*pixelData)[xp + (yp * irSize.x)];
		}
	}
	return result;
}

Color ImageRipper::_generate_color(uint rawvalue) const {
	Color result;// = Color
	return result;
}

void ImageRipper::_setNoiseType(ImageNoiseType noiseValue) {
	switch (noiseValue) {
		case STATIC_NOISE:
			imageNoiseMakerFluff->SetNoiseType(FastNoise::NoiseType::WhiteNoise);
			break;
		case VALUE_NOISE:
			imageNoiseMakerFluff->SetNoiseType(FastNoise::NoiseType::Value);
			break;
		case VALUEFRACTAL_NOISE:
			imageNoiseMakerFluff->SetNoiseType(FastNoise::NoiseType::ValueFractal);
			break;
		case PERLIN_NOISE:
			imageNoiseMakerFluff->SetNoiseType(FastNoise::NoiseType::Perlin);
			break;
		case PERLINFRACTAL_NOISE:
			imageNoiseMakerFluff->SetNoiseType(FastNoise::NoiseType::PerlinFractal);
			break;
		case SIMPLEX_NOISE:
			imageNoiseMakerFluff->SetNoiseType(FastNoise::NoiseType::Simplex);
			break;
		case SIMPLEXFRACTAL_NOISE:
			imageNoiseMakerFluff->SetNoiseType(FastNoise::NoiseType::SimplexFractal);
			break;
		case CELLULAR_NOISE:
			imageNoiseMakerFluff->SetNoiseType(FastNoise::NoiseType::Cellular);
			break;

		default:
			break;
	}
}

ImageNoiseType ImageRipper::_getNoiseTypeFromString(std::string noiseParam) {
	ImageNoiseType res = ImageNoiseType::CELLULAR_NOISE;
	if (!mapNoiseTypes.empty()) {
		res = mapNoiseTypes[noiseParam];
	}
	return res;
}

void ImageRipper::_bind_methods() {
	// Methods.
	ClassDB::bind_method(D_METHOD("simple_func"), &ImageRipper::simple_func);
	ClassDB::bind_method(D_METHOD("set_image_path"), &ImageRipper::set_image_path);
	ClassDB::bind_method(D_METHOD("set_size"), &ImageRipper::set_size);
	//ClassDB::bind_method(D_METHOD("create_noise_image"), &ImageRipper::create_noise_image);
	ClassDB::bind_method(D_METHOD("create_noise_image_textparam"), &ImageRipper::create_noise_image_textparam);
	ClassDB::bind_method(D_METHOD("get_pixels_raw"), &ImageRipper::get_pixels_raw);
	ClassDB::bind_method(D_METHOD("get_pixels"), &ImageRipper::get_pixels);
	ClassDB::bind_method(D_METHOD("get_data"), &ImageRipper::get_data);

	/*
	BIND_ENUM_CONSTANT(STATIC_NOISE);
	BIND_ENUM_CONSTANT(VALUE_NOISE);
	BIND_ENUM_CONSTANT(VALUEFRACTAL_NOISE);
	BIND_ENUM_CONSTANT(PERLIN_NOISE);
	BIND_ENUM_CONSTANT(PERLINFRACTAL_NOISE);
	BIND_ENUM_CONSTANT(SIMPLEX_NOISE);
	BIND_ENUM_CONSTANT(SIMPLEXFRACTAL_NOISE);
	BIND_ENUM_CONSTANT(CELLULAR_NOISE);
	*/
}
