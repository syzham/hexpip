#include "FontAtlas.h"

#include <cstdio>
#include <fstream>
#include <vector>

#define STB_TRUETYPE_IMPLEMENTATION
#include "stb/stb_truetype.h"

static bool readFileBytes(const std::string& path, std::vector<unsigned char>& out)
{
	std::ifstream f(path, std::ios::binary);
	if (!f) return false;
	f.seekg(0, std::ios::end);
	const std::streamsize size = f.tellg();
	f.seekg(0, std::ios::beg);
	out.resize(static_cast<size_t>(size));
	return static_cast<bool>(f.read(reinterpret_cast<char *>(out.data()), size));
}

bool FontAtlas::LoadFromTTF(const std::string& ttfPath, const float px,
							const int atlasW, const int atlasH)
{
	Destroy();

	std::vector<unsigned char> ttf;
	if (!readFileBytes(ttfPath, ttf)) {
		std::fprintf(stderr, "Failed to read TTF: %s\n", ttfPath.c_str());
		return false;
	}

	std::vector<unsigned char> bitmap(static_cast<size_t>(atlasW) * static_cast<size_t>(atlasH));
	const int res = stbtt_BakeFontBitmap(ttf.data(), 0, px,
										 bitmap.data(), atlasW, atlasH,
										 32, 96, baked);
	if (res <= 0) {
		std::fprintf(stderr, "stbtt_BakeFontBitmap failed for: %s\n", ttfPath.c_str());
		return false;
	}

	GLuint tex = 0;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, atlasW, atlasH, 0, GL_RED, GL_UNSIGNED_BYTE, bitmap.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	constexpr GLint swizzle[4] = { GL_ONE, GL_ONE, GL_ONE, GL_RED };
	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_SWIZZLE_RGBA, swizzle);

	textureID = tex;
	texW = atlasW;
	texH = atlasH;
	pixelHeight = px;
	return true;
}

void FontAtlas::Destroy()
{
	if (textureID != 0) {
		glDeleteTextures(1, &textureID);
		textureID = 0;
	}
}