#ifndef HEXPIP_UIINTERACTABLE_H
#define HEXPIP_UIINTERACTABLE_H

enum class UIInteractState { Idle, Hovered, Pressed };

struct UIInteractable {
    bool enabled{true};
    UIInteractState state{UIInteractState::Idle};
    bool wasPressedThisFrame{false};
    bool wasClickedThisFrame{false};
};

#endif //HEXPIP_UIINTERACTABLE_H