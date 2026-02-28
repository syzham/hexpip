#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"


GLenum TextureLoader::chooseFormat(const int channels)
{
	switch (channels) {
		case 1: return GL_RED;
		case 2: return GL_RG;
		case 3: return GL_RGB;
		case 4:;
		default: return GL_RGBA;
	}
}

GLuint TextureLoader::LoadTexture2D(const std::string& filePath, const bool flipVertically)
{
	stbi_set_flip_vertically_on_load(flipVertically ? 1 : 0);

	int w = 0, h = 0, channels = 0;
	unsigned char* pixels = stbi_load(filePath.c_str(), &w, &h, &channels, 0);
	if (!pixels) {
		std::fprintf(stderr, "Failed to load image: %s\n", filePath.c_str());
		return 0;
	}

	const GLenum format = chooseFormat(channels);

	GLuint tex = 0;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, static_cast<GLint>(format), w, h, 0, format, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(pixels);
	return tex;
}

void TextureLoader::DestroyTexture(GLuint& tex)
{
	if (tex != 0) {
		glDeleteTextures(1, &tex);
		tex = 0;
	}
}