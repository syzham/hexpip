#ifndef HEXPIP_POSITIONDICESYSTEM_H
#define HEXPIP_POSITIONDICESYSTEM_H

class Registry;
class Graphics;

inline float playingDiceY = 200;
inline float dicePadding = 10;
inline float diceWidth = 100;
inline float diceHeight = 100;

void PositionDiceSystem(Registry& R, Graphics& graphics, int numberOfDice) ;

#endif //HEXPIP_POSITIONDICESYSTEM_H