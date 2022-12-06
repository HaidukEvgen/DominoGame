#pragma hdrstop
#include "UnitGame.h"
#include "UnitConsts.h"
#include "stdlib.h"
#pragma package(smart_init)

void randomizeTiles(Domino *allTiles){
	srand(time(0));
	for (int i = 0; i < MAX_AMOUNT; i++)
		std::swap(allTiles[i], allTiles[std::rand() % MAX_AMOUNT]);
}

Domino findNextTurn(Player player, bool &placeLeft, int leftNum, int rightNum){
	for (int i = 0; i < player.getTilesAmount(); i++){
		if (canBePlacedLeft(player.getTile(i), leftNum, rightNum)){
			placeLeft = true;
			return player.getTile(i);
		}
		if (canBePlacedRight(player.getTile(i), leftNum, rightNum)){
			placeLeft = false;
			return player.getTile(i);
		}
	}
	Domino noTurn;
	noTurn.setTile(NULL);
	return noTurn;
}

bool canBePlacedLeft(Domino curTile, int leftNum, int rightNum){
	return (curTile.getFNum() == leftNum) || (curTile.getSNum() == leftNum);
}

bool canBePlacedRight(Domino curTile, int leftNum, int rightNum){
	return (curTile.getFNum() == rightNum) || (curTile.getSNum() == rightNum);
}

bool canBePlacedDifferent(Domino curTile, int leftNum, int rightNum){
	if (leftNum == rightNum ||
		(curTile.getFNum() == leftNum && curTile.getSNum() == rightNum) ||
		(curTile.getFNum() == rightNum && curTile.getSNum() == leftNum)){
		return true;
	}
	return false;
}

void placeTile(Domino nextTurn, bool placeLeft, int &leftNum, int &rightNum, int leftDirection, int rightDirection, int *coordinates){
	int &curLeftTileLeft = coordinates[LEFT_LEFT];
	int &curLeftTileTop = coordinates[LEFT_TOP];
	int &curRightTileLeft = coordinates[RIGHT_LEFT];
	int &curRightTileTop = coordinates[RIGHT_TOP];
	TImage *ptTile = (TImage *)(nextTurn.getImage());
	if (placeLeft){
		switch (leftDirection) {
			case LEFT_DIR : {
				rotateImage(nextTurn, rotationDirection(nextTurn, placeLeft, leftDirection, rightDirection, leftNum, rightNum));
				ptTile -> Left = curLeftTileLeft -= HEIGHT;
				ptTile -> Top = curLeftTileTop;
				break;
			}
			case UP_DIR :{
				rotateImage(nextTurn, rotationDirection(nextTurn, placeLeft, leftDirection, rightDirection, leftNum, rightNum));
				ptTile -> Left = curLeftTileLeft -= WIDTH;
				ptTile -> Top = curLeftTileTop = curLeftTileTop + WIDTH - HEIGHT;
				break;
			}
            case RIGHT_DIR_1ST : {
				rotateImage(nextTurn, rotationDirection(nextTurn, placeLeft, leftDirection, rightDirection, leftNum, rightNum));
				ptTile -> Left = curLeftTileLeft;
				ptTile -> Top = curLeftTileTop -= WIDTH;
				break;
			}
			case RIGHT_DIR :{
				rotateImage(nextTurn, rotationDirection(nextTurn, placeLeft, leftDirection, rightDirection, leftNum, rightNum));
				ptTile -> Left = curLeftTileLeft += HEIGHT;
				ptTile -> Top = curLeftTileTop;
				break;
			}
		}
	} else {
		switch (rightDirection) {
			case RIGHT_DIR :{
				rotateImage(nextTurn, rotationDirection(nextTurn, placeLeft, leftDirection, rightDirection, leftNum, rightNum));
				ptTile -> Left = curRightTileLeft += HEIGHT;
				ptTile -> Top = curRightTileTop;
				break;
			}
			case DOWN_DIR :{
				rotateImage(nextTurn, rotationDirection(nextTurn, placeLeft, leftDirection, rightDirection, leftNum, rightNum));
				ptTile -> Left = curRightTileLeft += HEIGHT;
				ptTile -> Top = curRightTileTop;
				break;
			}
			case LEFT_DIR_1ST : {
				rotateImage(nextTurn, rotationDirection(nextTurn, placeLeft, leftDirection, rightDirection, leftNum, rightNum));
				ptTile -> Left = curRightTileLeft = curRightTileLeft + WIDTH - HEIGHT;
				ptTile -> Top = curRightTileTop += HEIGHT;
				break;
			}
			case LEFT_DIR : {
				rotateImage(nextTurn, rotationDirection(nextTurn, placeLeft, leftDirection, rightDirection, leftNum, rightNum));
				ptTile -> Left = curRightTileLeft -= HEIGHT;
				ptTile -> Top = curRightTileTop;
				break;
			}
		}
	}
}

void rotateImage(Domino curTile, int direction){
	switch (direction) {
		case RLEFT:{
			TImage *ptTile = (TImage *)(curTile.getImage());
			ptTile -> Width = HEIGHT;
			ptTile -> Height = WIDTH;
			String fileName = "BlackDominoes/Left/Black" + IntToStr(curTile.getFNum()) + "-" + IntToStr(curTile.getSNum()) + ".png";
			ptTile -> Picture -> LoadFromFile(fileName);
			break;
		}
		case RRIGHT:{
			TImage *ptTile = (TImage *)(curTile.getImage());
			ptTile -> Width = HEIGHT;
			ptTile -> Height = WIDTH;
			String fileName = "BlackDominoes/Right/Black" + IntToStr(curTile.getFNum()) + "-" + IntToStr(curTile.getSNum()) + ".png";
			ptTile -> Picture -> LoadFromFile(fileName);
			break;
		}
		case RUP:{
			TImage *ptTile = (TImage *)(curTile.getImage());
			ptTile -> Width = WIDTH;
			ptTile -> Height = HEIGHT;
			String fileName = "BlackDominoes/Up/Black" + IntToStr(curTile.getFNum()) + "-" + IntToStr(curTile.getSNum()) + ".png";
			ptTile -> Picture -> LoadFromFile(fileName);
			break;
		}
		case RDOWN:{
			TImage *ptTile = (TImage *)(curTile.getImage());
			ptTile -> Width = WIDTH;
			ptTile -> Height = HEIGHT;
			String fileName = "BlackDominoes/Down/Black" + IntToStr(curTile.getFNum()) + "-" + IntToStr(curTile.getSNum()) + ".png";
			ptTile -> Picture -> LoadFromFile(fileName);
			break;
		}
	}
}

int rotationDirection(Domino curTile, bool placeLeft, int leftDirection, int rightDirection, int &leftNum, int &rightNum){
	if (placeLeft){
		switch (leftDirection) {
			case LEFT_DIR : {
				if (curTile.getFNum() == leftNum){
					leftNum = curTile.getSNum();
					return RRIGHT;
				}
				leftNum = curTile.getFNum();
				return RLEFT;
			}
			case UP_DIR :{
				if (curTile.getFNum() == leftNum){
					leftNum = curTile.getSNum();
					return RDOWN;
				}
				leftNum = curTile.getFNum();
				return RUP;
			}
			case RIGHT_DIR_1ST :
			case RIGHT_DIR :{
				if (curTile.getFNum() == leftNum){
					leftNum = curTile.getSNum();
					return RLEFT;
				}
				leftNum = curTile.getFNum();
				return RRIGHT;
			}
		}
	} else {
		switch (rightDirection) {
			case RIGHT_DIR :{
				if (curTile.getFNum() == rightNum){
					rightNum = curTile.getSNum();
					return RLEFT;
				}
				rightNum = curTile.getFNum();
				return RRIGHT;
			}
			case DOWN_DIR :{
				if (curTile.getFNum() == rightNum){
					rightNum = curTile.getSNum();
					return RUP;
				}
				rightNum = curTile.getFNum();
				return RDOWN;
			}
			case LEFT_DIR_1ST :
			case LEFT_DIR : {
				if (curTile.getFNum() == rightNum){
					rightNum = curTile.getSNum();
					return RRIGHT;
				}
				rightNum = curTile.getFNum();
				return RLEFT;
			}
		}
	}
}

void changeDirection(int *coordinates, int &leftDirection, int &rightDirection, int tilesInLine){
	int &leftTileLeft = coordinates[LEFT_LEFT];
	int &leftTileTop = coordinates[LEFT_TOP];
	int &rightTileLeft = coordinates[RIGHT_LEFT];
	if ((leftTileLeft == FIRST_LEFT - (HEIGHT * tilesInLine)) && leftDirection == LEFT_DIR)
		leftDirection = UP_DIR;
	else{
		if ((leftTileLeft == FIRST_LEFT - (HEIGHT * tilesInLine) - WIDTH) && leftDirection == UP_DIR)
			leftDirection = RIGHT_DIR_1ST;
		else{
			if ((leftTileTop == FIRST_TOP - HEIGHT) && leftDirection == RIGHT_DIR_1ST)
				leftDirection = RIGHT_DIR;
		}
	}
	if ((rightTileLeft == FIRST_LEFT + (HEIGHT * tilesInLine)) && rightDirection == RIGHT_DIR)
		rightDirection = DOWN_DIR;
	else{
		if ((rightTileLeft == FIRST_LEFT + (HEIGHT * tilesInLine) + HEIGHT) && rightDirection == DOWN_DIR)
			rightDirection = LEFT_DIR_1ST;
		else {
			if ((rightTileLeft == FIRST_LEFT + (HEIGHT * tilesInLine) + WIDTH) && rightDirection == LEFT_DIR_1ST)
				rightDirection = LEFT_DIR;
		}
	}
}

void redrawTiles(Player player, int width){
	int left = ((width - (player.getTilesAmount() * (WIDTH + SPACE) - SPACE)) / 2) + player.getLeft();
	for (int i = 0; i < player.getTilesAmount(); i++) {
		TImage *ptTile = (TImage *)(player.getImage(i));
		ptTile -> Left = left;
		left += WIDTH + SPACE;
	}
}

String toRus(int points){
	if (points > 5 && points < 21)
		return "очков";
	if (points % 10 == 1)
		return "очко";
	if (points % 10 > 1 && points % 10 < 5)
		return "очка";
	return "очков";
}

void showHiddenTiles(Player player){
	for (int i = 0; i < player.getTilesAmount(); i++) {
		TImage *ptTile = (TImage *)(player.getImage(i));
		String fileName = "BlackDominoes/Up/Black" + IntToStr(player.getTile(i).getFNum()) + "-" + IntToStr(player.getTile(i).getSNum()) + ".png";
		ptTile -> Picture -> LoadFromFile(fileName);
	}
}
