#include "RenderTextSystem.h"
#include "graphics/Graphics.h"
#include "graphics/FontAtlas.h"
#include "component/UI/UIText.h"
#include "component/UI/UITransform.h"
#include "core/Registry.h"
#include "core/Path.h"

#include <algorithm>
#include <string_view>
#include <vector>

static float MeasureLineWidth(FontAtlas& font, std::string_view line)
{
    float penX = 0.0f;
    float penY = 0.0f;

    for (unsigned char c : line) {
        if (c < 32 || c > 126) continue;
        stbtt_aligned_quad q{};
        stbtt_GetBakedQuad(font.baked, font.texW, font.texH, c - 32, &penX, &penY, &q, 1);
    }
    return penX; // penX advanced by the glyphs
}

static std::vector<std::string_view> SplitLines(const std::string& s)
{
    std::vector<std::string_view> lines;
    std::size_t start = 0;

    for (std::size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\n') {
            lines.emplace_back(s.data() + start, i - start);
            start = i + 1;
        }
    }
    lines.emplace_back(s.data() + start, s.size() - start);
    return lines;
}

void RenderTextSystem(Registry& R, Graphics& G)
{
    static FontAtlas font;
    static bool loaded = false;
    if (!loaded) {
        loaded = font.LoadFromTTF(Path::GetAssetPath("assets/fonts/JetBrains.ttf").c_str(), 24.0f);
    }
    if (!loaded || font.textureID == 0) return;

    R.forEach<UITransform, UIText>([&](Entity, UITransform& t, UIText& txt)
    {
        const float boxX = t.x;
        const float boxY = t.y;

        const float lineHeight = std::max(1.0f, txt.fontSize) * 1.2f;

        const auto lines = SplitLines(txt.text);
        const float blockH = lineHeight * static_cast<float>(lines.size());

        float penY = 0.0f;
        if (txt.alignV == UIText::AlignV::Top) {
            penY = boxY + txt.paddingY + lineHeight;
        } else {
            penY = boxY + (t.height - blockH) * 0.5f + lineHeight;
        }

        for (auto line : lines) {
            const float lineW = MeasureLineWidth(font, line);

            float penX = 0.0f;
            if (txt.alignH == UIText::AlignH::Left) {
                penX = boxX + txt.paddingX;
            } else {
                penX = boxX + (t.width - lineW) * 0.5f;
            }

            for (unsigned char c : line) {
                if (c < 32 || c > 126) continue;

                stbtt_aligned_quad q{};
                stbtt_GetBakedQuad(font.baked, font.texW, font.texH,
                                   c - 32, &penX, &penY, &q, 1);

                G.DrawSprite(q.x0, q.y0, (q.x1 - q.x0), (q.y1 - q.y0),
                             font.textureID, q.s0, q.t0, q.s1, q.t1,
                             txt.r, txt.g, txt.b, txt.a);
            }

            penY += lineHeight;
        }
    });
}