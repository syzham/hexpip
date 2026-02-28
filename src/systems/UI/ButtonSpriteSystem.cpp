#include "ButtonSpriteSystem.h"
#include "component/UI/UISprite.h"
#include "component/UI/UIButtonSprites.h"
#include "component/UI/UIInteractable.h"
#include "core/Registry.h"

void ButtonSpriteSystem(Registry& R) {
  R.forEach<UISprite, UIButtonSprites, UIInteractable>([&](Entity e, UISprite& sprite, UIButtonSprites& butSprite, UIInteractable& ui) {
        if (ui.state == UIInteractState::Pressed) {
          sprite.textureID = butSprite.pressed.textureID;
          sprite.r = butSprite.pressed.r;
          sprite.g = butSprite.pressed.g;
          sprite.b = butSprite.pressed.b;
        } else {
          sprite.textureID = butSprite.idle.textureID;
          sprite.r = butSprite.idle.r;
          sprite.g = butSprite.idle.g;
          sprite.b = butSprite.idle.b;
        }
      });
}
