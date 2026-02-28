#ifndef HEXPIP_FONTATLAS_H
#define HEXPIP_FONTATLAS_H

#include <glad/glad.h>
#include <string>

#include "stb/stb_truetype.h"

class FontAtlas {
public:
	GLuint textureID = 0;
	int texW = 0;
	int texH = 0;
	float pixelHeight = 0.0f;

	stbtt_bakedchar baked[96]{};

	bool LoadFromTTF(const std::string& ttfPath, float px,
					 int atlasW = 512, int atlasH = 512);

	void Destroy();
};


#endif //HEXPIP_FONTATLAS_H