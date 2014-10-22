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
		tl.lrect = textures[al.atlas].getPlacement(al.index);
	} else {
		tl.texture = unpacked[al.index];
		tl.lrect = rects[al.index];
	}
	return tl;
}

AtlasLocation TextureManager::addTexture(const std::string & file, SDL_Renderer * ren) {
	return addTexture(loadTexture(file, ren), true);
}

AtlasLocation TextureManager::addTexture(SDL_Texture * newTex, bool giveOwnership) {
	SDL_Rect tRect;
	SDL_QueryTexture(newTex, NULL, NULL, &tRect.w, &tRect.h);
	tRect.x = tRect.y = 0;

	unpacked.push_back(newTex);
	rects.push_back(tRect);
	owns.push_back(giveOwnership);
	AtlasLocation al;
	al.atlas = textures.size();
	al.index = unpacked.size()-1;
	return al;
}

AtlasLocation TextureManager::addTexture(SDL_Texture * newTex, SDL_Rect srcRect, bool giveOwnership) {
	unpacked.push_back(newTex);
	rects.push_back(srcRect);
	owns.push_back(giveOwnership);
	AtlasLocation al;
	al.atlas = textures.size();
	al.index = unpacked.size()-1;
	return al;
}

void TextureManager::packTextures(SDL_Renderer * ren) {
	textures.emplace_back(ren, unpacked, rects);
	for( int i=0; i<unpacked.size(); i++ ) {
		if( owns[i] )
			SDL_DestroyTexture(unpacked[i]);
	}
	unpacked.clear();
	rects.clear();
	owns.clear();
}



