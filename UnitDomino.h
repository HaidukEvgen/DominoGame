#ifndef UnitDominoH
#define UnitDominoH
#pragma once
#include <string>

class Domino {
	public:
    	Domino();
		Domino(int firstNum, int secondNum);
		void setFNum(int firstNum);
		void setSNum(int secondNum);
		void setDouble(int firstNum, int secondNum);
		void setTile(void *ptTile);
		int getFNum();
		int getSNum();
		bool getDouble();
        void* getImage();
	private:
		int fNum;
		int sNum;
		bool isDouble;
		void *tile;
};
#endif
