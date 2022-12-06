#pragma once
#ifndef UnitConstsH
#define UnitConstsH

const int MAX_AMOUNT = 28;
const int MAX_SUM = 12;
const int INITIAL_AMOUNT = 7;
const int MAX_NUM = 6;

enum turnsGamePC{
   PC_TURN,
   USER_TURN
};

enum turnsGameTeam{
	PC1_TURN,
	USER_UP_TURN,
	PC2_TURN,
	USER_DOWN_TURN
};

enum rotations{
	RLEFT,
	RRIGHT,
	RDOWN,
	RUP,
};

enum directions{
	LEFT_DIR,
	RIGHT_DIR,
	UP_DIR,
	DOWN_DIR,
	LEFT_DIR_1ST,
	RIGHT_DIR_1ST
};

enum winners{
	PC_WON,
	USER_WON,
	FISH_WON
};

enum coords{
	LEFT_LEFT,
	LEFT_TOP,
	RIGHT_LEFT,
	RIGHT_TOP
};

enum mode{
	CLASSIC,
	GOAT
};

enum initalCoordsPC{
	LEFT_USER = 575,
	TOP_USER = 510,
	LEFT_PC = 575,
	TOP_PC = 160
};

enum initialCoordsTeam{
	LEFT_USER_UP = 575,
	TOP_USER_UP = 10,
	LEFT_PC1 = 10,
	TOP_PC1 = 450,
	PC1_LEFT = 180,
	PC2_LEFT = 195,
	LEFT_USER_DOWN = 575,
	TOP_USER_DOWN = 690,
	LEFT_PC2 = 1080,
	TOP_PC2 = 450,
};

const int DELTA = 50;
const int SPACE = 10;
const int WIDTH = 41;
const int HEIGHT = 84;

const int FIRST_LEFT = 680;
const int FIRST_TOP = 340;

const int MIN_TIMER = 500;
const int MAX_TIMER = 2000;

#endif
