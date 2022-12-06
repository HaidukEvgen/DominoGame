#pragma hdrstop
#include "UnitPlayer.h"
#pragma package(smart_init)

Player::Player() {
	Player::points = 0;
}

void Player::setTiles(Domino initialTilesArr[]){
	curTilesAmount = 0;
	for (int i = 0; i < INITIAL_AMOUNT; i++) {
		Player::addTile(initialTilesArr[i]);
	}
}

void Player::setPoints(int num){
	Player::points = num;
}

void Player::setLeft(int num){
	Player::left = num;
}

void Player::addPoints(int addition){
	Player::points += addition;
}

int Player::getPoints(){
	return Player::points;
}

int Player::getFNum(index) {
	return Player::tilesArr[index].getFNum();
}

int Player::getSNum(index) {
	return Player::tilesArr[index].getSNum();
}

int Player::getLeft() {
	return Player::left;
}

int Player::getNumsSum(){
	int sum = 0;
	for (int i = 0; i < Player::getTilesAmount(); i++)
		sum += Player::getTile(i).getFNum() + Player::getTile(i).getSNum();
	return sum;
}

void Player::addTile(Domino curTile){
	Player::tilesArr[curTilesAmount].setFNum(curTile.getFNum());
	Player::tilesArr[curTilesAmount].setSNum(curTile.getSNum());
	Player::tilesArr[curTilesAmount].setTile(curTile.getImage());
	Player::tilesArr[curTilesAmount].setDouble(curTile.getFNum(), curTile.getSNum());
	curTilesAmount++;
}

void Player::deleteTile(int index){
	for (int i = index; i < curTilesAmount; i++) {
		Player::tilesArr[i].setFNum(Player::tilesArr[i + 1].getFNum());
		Player::tilesArr[i].setSNum(Player::tilesArr[i + 1].getSNum());
		Player::tilesArr[i].setTile(Player::tilesArr[i + 1].getImage());
	}
	curTilesAmount--;
}

int Player::getMaxDoublesSum(){
	int numsSum = -1;
	for (int i = 0; i < curTilesAmount; i++)
		if (Player::getFNum(i) == Player::getSNum(i) && 2 * Player::getFNum(i) > numsSum)
			numsSum = 2 * Player::getFNum(i);
	return numsSum;
}

int Player::getMaxSum(){
	int numsSum = 0;
	for (int i = 0; i < curTilesAmount; i++)
		if (Player::getFNum(i) + Player::getSNum(i) > numsSum)
			numsSum = Player::getFNum(i) + Player::getSNum(i);
	return numsSum;
}

int Player::getTilesAmount(){
	return Player::curTilesAmount;
}

Domino *Player::getTilesArr(){
	return Player::tilesArr;
}

Domino Player::getTile(int index){
	return Player::tilesArr[index];
}

void* Player::getImage(int index){
	return Player::tilesArr[index].getImage();
}

Domino Player::getTile(void* image){
	for (int i = 0; i < Player::curTilesAmount; i++)
		if (Player::tilesArr[i].getImage() == image)
			return Player::tilesArr[i];
}

int Player::getIndex(Domino curTile){
	for (int i = 0; i < Player::curTilesAmount; i++)
		if (Player::tilesArr[i].getImage() == curTile.getImage())
			return i;
}

void Player::deleteTiles(){
	for (int i = 0; i < Player::getTilesAmount(); i++)
		Player::deleteTile(i);
}





