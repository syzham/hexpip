#include "ButtonSystem.h"
#include "core/Registry.h"
#include "component/UI/UIButton.h"
#include "component/UI/UIInteractable.h"

void ButtonSystem(Registry& R)
{
  R.forEach<UIInteractable, UIButton>([&](Entity e, UIInteractable& ui, UIButton& button) {
      if (ui.wasClickedThisFrame)
        button.onClick();
  });
}
