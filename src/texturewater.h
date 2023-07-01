#ifndef TEXTUREWATER_CLASS_H
#define TEXTUREWATER_CLASS_H

#include "noiseutils.h"
#include <noise/noise.h>

using namespace noise;

class WaterTexture {
private:
	// Height of the texture.
	const int TEXTURE_HEIGHT = 256;
	int textureWidth;
	int textureHeight;

public:
	WaterTexture();
	WaterTexture(int width, int height);
	// Creates the color gradients for the texture.
	void CreateTextureColor(utils::RendererImage &renderer);

	// Given a noise module, this function renders a flat square texture map and
	// writes it to a Windows bitmap (*.bmp) file.  Because the texture map is
	// square, its width is equal to its height.  The texture map can be seamless
	// (tileable) or non-seamless.
	void CreatePlanarTexture(const module::Module &noiseModule, bool seamless,
			int height, const char *filename);

	// Given a noise module, this function renders a spherical texture map and
	// writes it to a Windows bitmap (*.bmp) file.  The texture map's width is
	// double its height.
	void CreateSphericalTexture(const module::Module &noiseModule, int height,
			const char *filename);

	// Given a noise map, this function renders a texture map and writes it to a
	// Windows bitmap (*.bmp) file.
	void RenderTexture(const utils::NoiseMap &noiseMap, const char *filename);
	void drawTextureImage();
	void drawTextureImageToFile(std::string planeImg);
	void drawTextureImageToFiles(std::string planeImg, std::string planarImg, std::string sphereImg);
};

#endif