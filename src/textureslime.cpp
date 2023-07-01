#include "textureslime.h"

SlimeTexture::SlimeTexture() {
}

SlimeTexture::SlimeTexture(int width, int height) {
}

void SlimeTexture::drawTextureImageToFiles(std::string planeImg, std::string planarImg, std::string sphereImg) {
	module::Billow largeSlime;
	largeSlime.SetSeed(0);
	largeSlime.SetFrequency(4.0);
	largeSlime.SetLacunarity(2.12109375);
	largeSlime.SetOctaveCount(1);
	largeSlime.SetNoiseQuality(QUALITY_BEST);

	// Base of the small slime bubble texture.  This texture will eventually
	// appear inside cracks in the large slime bubble texture.
	module::Billow smallSlimeBase;
	smallSlimeBase.SetSeed(1);
	smallSlimeBase.SetFrequency(24.0);
	smallSlimeBase.SetLacunarity(2.14453125);
	smallSlimeBase.SetOctaveCount(1);
	smallSlimeBase.SetNoiseQuality(QUALITY_BEST);

	// Scale and lower the small slime bubble values.
	module::ScaleBias smallSlime;
	smallSlime.SetSourceModule(0, smallSlimeBase);
	smallSlime.SetScale(0.5);
	smallSlime.SetBias(-0.5);

	// Create a map that specifies where the large and small slime bubble
	// textures will appear in the final texture map.
	module::RidgedMulti slimeMap;
	slimeMap.SetSeed(0);
	slimeMap.SetFrequency(2.0);
	slimeMap.SetLacunarity(2.20703125);
	slimeMap.SetOctaveCount(3);
	slimeMap.SetNoiseQuality(QUALITY_STD);

	// Choose between the large or small slime bubble textures depending on the
	// corresponding value from the slime map.  Choose the small slime bubble
	// texture if the slime map value is within a narrow range of values,
	// otherwise choose the large slime bubble texture.  The edge falloff is
	// non-zero so that there is a smooth transition between the two textures.
	module::Select slimeChooser;
	slimeChooser.SetSourceModule(0, largeSlime);
	slimeChooser.SetSourceModule(1, smallSlime);
	slimeChooser.SetControlModule(slimeMap);
	slimeChooser.SetBounds(-0.375, 0.375);
	slimeChooser.SetEdgeFalloff(0.5);

	// Finally, perturb the slime texture to add realism.
	module::Turbulence finalSlime;
	finalSlime.SetSourceModule(0, slimeChooser);
	finalSlime.SetSeed(2);
	finalSlime.SetFrequency(8.0);
	finalSlime.SetPower(1.0 / 32.0);
	finalSlime.SetRoughness(2);

	if (planeImg.length() > 0)
		CreatePlanarTexture(finalSlime, false, TEXTURE_HEIGHT,
				planeImg.c_str());
	if (planarImg.length() > 0)
		CreatePlanarTexture(finalSlime, true, TEXTURE_HEIGHT,
				planarImg.c_str());
	if (sphereImg.length() > 0)
		CreateSphericalTexture(finalSlime, TEXTURE_HEIGHT,
				sphereImg.c_str());
}

// Creates the color gradients for the texture.
void SlimeTexture::CreateTextureColor(utils::RendererImage &renderer) {
	renderer.ClearGradient();
	renderer.AddGradientPoint(-1.0000, utils::Color(160, 64, 42, 255));
	renderer.AddGradientPoint(0.0000, utils::Color(64, 192, 64, 255));
	renderer.AddGradientPoint(1.0000, utils::Color(128, 255, 128, 255));
}

void SlimeTexture::CreatePlanarTexture(const module::Module &noiseModule, bool seamless,
		int height, const char *filename) {
	// Map the output values from the noise module onto a plane.  This will
	// create a two-dimensional noise map which can be rendered as a flat
	// texture map.
	utils::NoiseMapBuilderPlane plane;
	utils::NoiseMap noiseMap;
	plane.SetBounds(-1.0, 1.0, -1.0, 1.0);
	plane.SetDestSize(height, height);
	plane.SetSourceModule(noiseModule);
	plane.SetDestNoiseMap(noiseMap);
	plane.EnableSeamless(seamless);
	plane.Build();

	RenderTexture(noiseMap, filename);
}

void SlimeTexture::CreateSphericalTexture(const module::Module &noiseModule, int height,
		const char *filename) {
	// Map the output values from the noise module onto a sphere.  This will
	// create a two-dimensional noise map which can be rendered as a spherical
	// texture map.
	utils::NoiseMapBuilderSphere sphere;
	utils::NoiseMap noiseMap;
	sphere.SetBounds(-90.0, 90.0, -180.0, 180.0); // degrees
	sphere.SetDestSize(height * 2, height);
	sphere.SetSourceModule(noiseModule);
	sphere.SetDestNoiseMap(noiseMap);
	sphere.Build();

	RenderTexture(noiseMap, filename);
}

void SlimeTexture::RenderTexture(const utils::NoiseMap &noiseMap, const char *filename) {
	// Create the color gradients for the texture.
	utils::RendererImage textureRenderer;
	CreateTextureColor(textureRenderer);

	// Set up us the texture renderer and pass the noise map to it.
	utils::Image destTexture;
	textureRenderer.SetSourceNoiseMap(noiseMap);
	textureRenderer.SetDestImage(destTexture);
	textureRenderer.EnableLight(true);
	textureRenderer.SetLightAzimuth(135.0);
	textureRenderer.SetLightElev(60.0);
	textureRenderer.SetLightContrast(2.0);
	textureRenderer.SetLightColor(utils::Color(255, 255, 255, 0));

	// Render the texture.
	textureRenderer.Render();

	// Write the texture as a Windows bitmap file (*.bmp).
	utils::WriterBMP textureWriter;
	textureWriter.SetSourceImage(destTexture);
	textureWriter.SetDestFilename(filename);
	textureWriter.WriteDestFile();
}