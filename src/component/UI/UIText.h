#ifndef HEXPIP_UITEXT_H
#define HEXPIP_UITEXT_H

#include <string>
#include <cstdint>

struct UIText {
	enum class AlignH : std::uint8_t { Left, Center };
	enum class AlignV : std::uint8_t { Top, Center };

	std::string text;
	int fontFamily = 0;
	float fontSize = 0;
	float r=0, g=0, b=0, a=1;

	AlignH alignH = AlignH::Center;
	AlignV alignV = AlignV::Center;

	float paddingX = 0.0f;
	float paddingY = 0.0f;
};

#endif //HEXPIP_UITEXT_H