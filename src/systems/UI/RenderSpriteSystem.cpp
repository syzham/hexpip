#include "RenderSpriteSystem.h"
#include "graphics/Graphics.h"
#include "component/UI/UISprite.h"
#include "component/UI/UITransform.h"
#include "component/UI/UILayout.h"
#include "core/Registry.h"

void RenderSpriteSystem(Registry& R, Graphics& G) {
	R.forEach<UILayout, UITransform>([&](Entity e, UILayout& layout, UITransform& trans) {
		trans.x = ((layout.anchorX * G.getWidth()) + layout.offsetX) - (layout.pivotX * trans.width);
		trans.y = ((layout.anchorY * G.getHeight()) + layout.offsetY) - (layout.pivotY * trans.height);
	});

	R.forEach<UITransform, UISprite>([&](Entity e, UITransform& trans, UISprite& sprite) {
	G.DrawSprite(trans.x, trans.y, trans.width, trans.height, sprite.textureID,
		sprite.u0, sprite.v0, sprite.u1, sprite.v1,
		sprite.r, sprite.g, sprite.b, sprite.a);
	  });
}
