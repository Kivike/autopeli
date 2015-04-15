#ifndef SCREEN_H
#define SCREEN_H

//Vehicle Characters
extern const char CAR;
extern const char FAST_CAR;
extern const char RUBBLE;
extern const char PLAYER;
extern const char FLYING;

//Characters in first row of the screen
extern char screenTop[16];
//Characters in second row of the screen
extern char screenBottom[16];
extern int selection;

void initializeScreen();
void updateScreen();
void updateMenu();

#endif

