#ifndef UnitGameH
#define UnitGameH
#include "UnitDomino.h"
#include "UnitPlayer.h"
#include <Vcl.ExtCtrls.hpp>

void randomizeTiles(Domino *allTiles);
Domino findNextTurn(Player player, bool &placeLeft, int leftNum, int rightNum);
bool canBePlacedLeft(Domino curTile, int leftNum, int rightNum);
bool canBePlacedRight(Domino curTile, int leftNum, int rightNum);
bool canBePlacedDifferent(Domino curTile, int leftNum, int rightNum);
void placeTile(Domino nextTurn,
			   bool placeLeft,
			   int &leftNum,
			   int &rightNum,
			   int leftDirection,
			   int rightDirection,
			   int *coordinates);
void rotateImage(Domino curTile, int direction);
int rotationDirection(Domino curTile,
					  bool placeLeft,
					  int leftDirection,
					  int rightDirection,
					  int &leftNum,
					  int &rightNum);
void changeDirection(int *coordinates, int &leftDirection, int &rightDirection, int tilesInLine);
void redrawTiles(Player player, int width);
String toRus(int points);
void showHiddenTiles(Player player);

#endif
