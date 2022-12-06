#ifndef UnitPlayerH
#define UnitPlayerH
#include "UnitDomino.h"
#include "UnitConsts.h"

class Player {
	public:
		Player();
		void setTiles(Domino initialTilesArr[]);
		void addTile(Domino curTile);
		void setPoints(int num);
		void setLeft(int num);
		void addPoints(int addition);
		void deleteTile(int index);
		int getPoints();
		int getFNum(index);
		int getSNum(index);
        int getLeft();
		int getMaxDoublesSum();
		int getMaxSum();
		int getTilesAmount();
		Domino *getTilesArr();
		Domino getTile(int index);
		Domino getTile(void* image);
		void* getImage(int index);
		int getIndex(Domino curTile);
		int getNumsSum();
        void deleteTiles();
	private:
		Domino tilesArr[MAX_AMOUNT];
		int points;
		int curTilesAmount;
		int left;
};
#endif
