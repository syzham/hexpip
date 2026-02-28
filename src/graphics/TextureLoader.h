#ifndef HEXPIP_TEXTURELOADER_H
#define HEXPIP_TEXTURELOADER_H

#include <glad/glad.h>
#include <string>

class TextureLoader {
public:
	static GLuint LoadTexture2D(const std::string& filePath, bool flipVertically = false);
	static void DestroyTexture(GLuint& tex);

private:
	static GLenum chooseFormat(int channels);
};


#endif //HEXPIP_TEXTURELOADER_H