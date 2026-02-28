#include "DiceSpriteSystem.h"

#include "core/Registry.h"
#include "component/UI/UIDiceSprites.h"
#include "component/Gameplay/Dice.h"

void DiceSpriteSystem(Registry& R) {
	R.forEach<UIDiceSprites, UISprite, Dice>([&](Entity e, UIDiceSprites& diceSprite, UISprite& sprite, Dice& dice) {
		switch (dice.upperFace) {
			case 2: sprite.textureID = diceSprite.two.textureID; break;
			case 3: sprite.textureID = diceSprite.three.textureID; break;
			case 4: sprite.textureID = diceSprite.four.textureID; break;
			case 5: sprite.textureID = diceSprite.five.textureID; break;
			case 6: sprite.textureID = diceSprite.six.textureID; break;
			default: sprite.textureID = diceSprite.one.textureID; break;
		}
	});
}