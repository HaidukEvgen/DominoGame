#pragma hdrstop
#include "UnitDomino.h"
#include "UnitGamePC.h"
#pragma package(smart_init)

Domino::Domino(){
}

Domino::Domino(int firstNum, int secondNum){
	Domino::setFNum(firstNum);
	Domino::setSNum(secondNum);
	Domino::setDouble(firstNum, secondNum);
}

void Domino::setFNum(int firstNum){
	Domino::fNum = firstNum;
}

void Domino::setSNum(int secondNum){
	Domino::sNum = secondNum;
}

void Domino::setDouble(int firstNum, int secondNum){
	Domino::isDouble = firstNum == secondNum;
}

int Domino::getFNum() {
	return Domino::fNum;
}

int Domino::getSNum() {
	return Domino::sNum;
}

bool Domino::getDouble(){
	return Domino::isDouble;
}

void Domino::setTile(void *ptTile) {
	Domino::tile = ptTile;
}

void* Domino::getImage() {
	return Domino::tile;
}

