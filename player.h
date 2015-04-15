#ifndef PLAYER_H
#define PLAYER_H

extern int acceleration;

void changeAcceleration();
void accelerateNextUpdate();
void decelerateNextUpdate();
void moveLeft();
void moveRight();
void jump();

#endif
