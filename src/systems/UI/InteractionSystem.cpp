#include "InteractionSystem.h"
#include "core/Registry.h"
#include "component/UI/UIInteractable.h"
#include "component/UI/UITransform.h"

void InteractionSystem(Registry& R, float mx, float my, bool isM1Down) {
  R.forEach<UIInteractable, UITransform>([&](Entity e, UIInteractable& ui, UITransform& trans) {
    if (ui.wasClickedThisFrame) ui.wasClickedThisFrame = false;
    if (!ui.enabled) return;
    if (mx > trans.x && mx < (trans.x + trans.width) &&
        my > trans.y && my < (trans.y + trans.height)) {
      if (ui.state == UIInteractState::Hovered && isM1Down) {
        ui.state = UIInteractState::Pressed;
        ui.wasPressedThisFrame = true;
      } else if (ui.state == UIInteractState::Idle) {
        ui.state = UIInteractState::Hovered;
      } else if (ui.state == UIInteractState::Pressed && !isM1Down) {
        ui.state = UIInteractState::Hovered;
        ui.wasPressedThisFrame = false;
        ui.wasClickedThisFrame = true;
      }
    } else if (ui.state == UIInteractState::Hovered ||
        (ui.state == UIInteractState::Pressed && !isM1Down)) {
      ui.state = UIInteractState::Idle;
    }
  });
}
