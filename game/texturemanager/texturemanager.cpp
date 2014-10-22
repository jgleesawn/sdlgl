#include "texturemanager.h"

TextureManager * TextureManager::mSingleton = 0;

TextureManager::TextureManager() {}
TextureManager::~TextureManager() {}

TextureManager * TextureManager::getSingleton() {
	if( mSingleton == 0 )
		mSingleton = new TextureManager();
	return mSingleton;
}

//Would like to remove if statement, opting for safer route
//that doesn't require batch packing of textures to use them.
TextureLocation TextureManager::getTexture(AtlasLocation al) {
	TextureLocation tl;
	if( al.atlas < textures.size() ) {
		tl.texture = textures[al.atlas].getTexture();
		tl.location = textures[al.atlas].getPlacement(al.index);
	} else {
		tl.texture = unpacked[al.index];
		tl.location = rects[al.index];
	}
	return tl;
}

AtlasLocation TextureManager::addTexture(const std::string & file, SDL_Renderer * ren) {
	return addTexture(loadTexture(file, ren));
}

AtlasLocation TextureManager::addTexture(SDL_Texture * newTex) {
	SDL_Rect tRect;
	SDL_QueryTexture(newTex, NULL, NULL, &tRect.w, &tRect.h);
	tRect.x = tRect.y = 0;

	unpacked.push_back(newTex);
	rects.push_back(tRect);
	AtlasLocation al;
	al.atlas = textures.size();
	al.index = unpacked.size()-1;
	return al;
}

AtlasLocation TextureManager::addTexture(SDL_Texture * newTex, SDL_Rect srcRect) {
	unpacked.push_back(newTex);
	rects.push_back(srcRect);
	AtlasLocation al;
	al.atlas = textures.size();
	al.index = unpacked.size()-1;
	return al;
}

void TextureManager::packTextures(SDL_Renderer * ren) {
	textures.emplace_back(ren, unpacked, rects);
	unpacked.clear();
}



