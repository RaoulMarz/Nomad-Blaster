#include "spriteassist.h"

//std::optional<godot::Texture2D *> SpriteAssist::load_sprite_fromcache(godot::String folderspec, godot::String spriteRes) {
std::optional<godot::Ref<godot::Texture2D>> SpriteAssist::load_sprite_fromcache(godot::String folderspec, godot::String spriteRes) {
	//std::optional<godot::Texture2D *> res = std::nullopt;
	std::optional<godot::Ref<godot::Texture2D>> res = std::nullopt;
	std::string spriteKey = std::string(spriteRes.utf8().get_data());
	std::string folderKey = std::string(folderspec.utf8().get_data());
	if (mapSpriteCache.find(folderspec.utf8().get_data()) != mapSpriteCache.end()) {
		res = mapSpriteCache[spriteKey];
		return res;
	}
	if (folderspec.length()) {
		godot::String spriteResourcePath = folderspec + PathUtilities::directorySeparator() + spriteRes;
		std::optional<godot::Ref<godot::Texture2D>> spriteImageOptional = ResourceUtilities::getExternalTexture(spriteResourcePath);
		//std::optional<godot::Texture2D*> spriteImage = ResourceUtilities::getExternalTexture(spriteResourcePath);
		godot::Ref<godot::Texture2D> spriteRef = spriteImageOptional.value_or(nullptr);
		//godot::Texture2D* spriteTexture = &(spriteRef);
		mapSpriteCache[spriteKey] = spriteRef;
		res = spriteRef;
	}
	return res;
}

//std::optional<godot::Texture2D *> SpriteAssist::get_texture(godot::String spriteResourcePath, int columnIndex, int rowIndex) {
std::optional<godot::Ref<godot::Texture2D>> SpriteAssist::get_texture(godot::String spriteResourcePath, int columnIndex, int rowIndex) {
	/*
			string imageName = resourceWithoutExt + $"#C{columnIndex:00}_R{rowIndex:00}.png";
			Texture2D subTileCached = LoadSpriteFromCache(SaveImagePath, imageName);
			return subTileCached;
	*/
	std::stringstream imgBaseStream;
	imgBaseStream << "#C" << std::setw(10) << std::setfill('0') << std::setiosflags(std::ios::right) << columnIndex;
	imgBaseStream << "#R" << std::setw(10) << std::setfill('0') << std::setiosflags(std::ios::right) << rowIndex;
	imgBaseStream << ".png";
	std::optional<godot::Ref<godot::Texture2D>> res = std::nullopt;
	godot::String spriteRes = PathUtilities::getFileName(spriteResourcePath);
	godot::String extension = PathUtilities::getExtension(spriteRes);
	godot::String resourceWithoutExt = PathUtilities::getFileWithoutExtension(spriteRes);
	godot::String dressedFileBase = godot::String(imgBaseStream.str().c_str());
	godot::String imageName = resourceWithoutExt + dressedFileBase;
	res = load_sprite_fromcache(godot::String(saveImagePath.c_str()), imageName);
	return res;
}

void SpriteAssist::slice_regions_tileset_image(godot::String spriteResourcePath, int columns, int rows) {
	godot::Sprite2D spriteImageCapture; // = new Sprite2D();
	//if (spriteImageCapture != null)
	//{
	godot::String folderspec = PathUtilities::getDirectoryName(spriteResourcePath);
	godot::String spriteRes = PathUtilities::getFileName(spriteResourcePath);
	auto spriteCachedOptional = load_sprite_fromcache(folderspec, spriteRes);
	godot::Ref<godot::Texture2D> spriteCached = spriteCachedOptional.value_or(nullptr);
	//GD.Print($"[SpriteAssist], SliceRegionsTilesetImage(), folderspec = {folderspec}, spriteRes = {spriteRes}");
	if (spriteCached.is_valid()) {
		//GD.Print($"[SpriteAssist], SliceRegionsTilesetImage(), columns = {columns}, rows = {rows}, spriteRes = {spriteRes}");
		spriteImageCapture.set_texture(spriteCached);
		spriteImageCapture.set_visible(true);
		int spriteHeight = spriteCached->get_height() / rows;
		int spriteWidth = spriteCached->get_width() / columns;
		std::stringstream imgBaseStream;
		godot::Ref<godot::Image> spriteCacheImage = spriteCached->get_image();
		for (int icol = 0; icol < columns; icol++) {
			for (int irow = 0; irow < rows; irow++) {
				godot::Rect2i captureRegion(icol * spriteWidth, irow * spriteHeight, spriteWidth, spriteHeight);				
				godot::Ref<godot::Image> subRegionImage = spriteCacheImage->get_region(captureRegion);
				godot::String extension = PathUtilities::getExtension(spriteRes);
				godot::String resourceWithoutExt = PathUtilities::getFileWithoutExtension(spriteRes); //spriteRes.Substring(0, spriteRes.Length - extension.Length);
				imgBaseStream.clear();
				imgBaseStream << "#C" << std::setw(10) << std::setfill('0') << std::setiosflags(std::ios::right) << icol;
				imgBaseStream << "#R" << std::setw(10) << std::setfill('0') << std::setiosflags(std::ios::right) << irow;
				imgBaseStream << ".png";
				godot::String dressedFileBase = godot::String(imgBaseStream.str().c_str());
				godot::String imageName = resourceWithoutExt + dressedFileBase; // + $"#C{icol:00}_R{irow:00}.png";
				subRegionImage->save_png(godot::String(saveImagePath.c_str()) + imageName);
				//GD.Print($"[SpriteAssist] --- Region = {subRegionImage}, save-image = {imageName}, irow = {irow}, icol = {icol}");
			}
		}
		mapSlicedSubTiles[std::string(spriteRes.utf8().get_data())] = rows * columns;
	}
	//}
}
/*
public void SliceRegionsTilesetImage(String spriteResourcePath, int columns, int rows)
		{
			spriteImageCapture = new Sprite2D();
			if (spriteImageCapture != null)
			{
				String folderspec = SIO.Path.GetDirectoryName(spriteResourcePath);
				String spriteRes = SIO.Path.GetFileName(spriteResourcePath);
				Texture2D spriteCached = LoadSpriteFromCache(folderspec, spriteRes);
				GD.Print($"[SpriteAssist], SliceRegionsTilesetImage(), folderspec = {folderspec}, spriteRes = {spriteRes}");
				if (spriteCached != null)
				{
					GD.Print($"[SpriteAssist], SliceRegionsTilesetImage(), columns = {columns}, rows = {rows}, spriteRes = {spriteRes}");
					spriteImageCapture.Texture = spriteCached;
					spriteImageCapture.Visible = true;
					int spriteHeight = spriteCached.GetHeight() / rows;
					int spriteWidth = spriteCached.GetWidth() / columns;
					for (int icol = 0; icol < columns; icol++)
					{
						for (int irow = 0; irow < rows; irow++)
						{
							Rect2I captureRegion = new Rect2I(icol * spriteWidth, irow * spriteHeight, spriteWidth, spriteHeight);
							Image subRegionImage = spriteCached.GetImage().GetRegion(captureRegion);
							string extension = SIO.Path.GetExtension(spriteRes);
							string resourceWithoutExt = spriteRes.Substring(0, spriteRes.Length - extension.Length);
							string imageName = resourceWithoutExt + $"#C{icol:00}_R{irow:00}.png";
							subRegionImage.SavePng(SaveImagePath + imageName);
							GD.Print($"[SpriteAssist] --- Region = {subRegionImage}, save-image = {imageName}, irow = {irow}, icol = {icol}");
						}
					}
					mapSlicedSubTiles.Add(spriteRes, rows * columns);
				}
			}
		}
	}
*/