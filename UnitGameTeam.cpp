#include <vcl.h>
#pragma hdrstop
#include "UnitGameTeam.h"
#include "UnitLog.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
#define FORM_WIDTH FormGameTeam -> Width
#define TILES_IN_LINE 4

TFormGameTeam *FormGameTeam;
Domino tilesArr[MAX_AMOUNT];
Player playerPC1;
Player playerPC2;
Player playerUserUp;
Player playerUserDown;
int currentTurn;
int leftNum;
int rightNum;
bool firstTurn;
int leftDirection = LEFT_DIR;
int rightDirection = RIGHT_DIR;
int round = 1;
int coordinates[4];

void changeTurn();

__fastcall TFormGameTeam::TFormGameTeam(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TFormGameTeam::FormShow(TObject *Sender)
{
	initGame();
}

void __fastcall TFormGameTeam::initGame(){
	FormGameTeam -> ControlStyle = FormGameTeam -> ControlStyle << csOpaque;
	if (gameModeGameTeam == CLASSIC)
		GameTypeLabel -> Caption = "Домино Классика";
	else
		if (gameModeGameTeam == GOAT)
			GameTypeLabel -> Caption = "Домино Козел";
	AimLabel -> Caption = "(до " + IntToStr(pointsAimGameTeam) + ")";
	FormLog -> initLogForm("Компьютеры");
	initTiles(tilesArr);
	randomizeTiles(tilesArr);
	playerPC1.setTiles(tilesArr);
	playerPC2.setTiles(tilesArr + INITIAL_AMOUNT);
	playerUserUp.setTiles(tilesArr + 2 * INITIAL_AMOUNT);
	playerUserDown.setTiles(tilesArr + 3 * INITIAL_AMOUNT);
	playerPC1.setPoints(0);
	playerPC2.setPoints(0);
	playerUserUp.setPoints(0);
	playerUserDown.setPoints(0);
	playerPC1.setLeft((-1 * FORM_WIDTH / 2)  + PC1_LEFT);
	playerPC2.setLeft((FORM_WIDTH / 2) - PC2_LEFT);
	playerUserUp.setLeft(0);
	playerUserDown.setLeft(0);
	getFirstTurn();
	giveTiles();
}

void __fastcall TFormGameTeam::prepareTiles(){
    for (int i = 0; i <= MAX_NUM; i++) {
		for (int j = i; j <= MAX_NUM; j++) {
			String name = "Tile" + IntToStr(i) + "_" + IntToStr(j);
			TImage *ptTile = dynamic_cast<TImage *>(FindComponent(name));
			ptTile -> Visible = false;
			ptTile -> Width = WIDTH;
			ptTile -> Height = HEIGHT;
			String fileName = "BlackDominoes/Up/Black" + IntToStr(i) + "-" + IntToStr(j) + ".png";
			ptTile -> Picture -> LoadFromFile(fileName);
		}
	}
}

void __fastcall TFormGameTeam::initRound(){
	randomizeTiles(tilesArr);
	playerPC1.deleteTiles();
	playerPC2.deleteTiles();
	playerUserUp.deleteTiles();
	playerUserDown.deleteTiles();
    prepareTiles();
	Brain1MadImage -> Visible = false;
	Brain1HappyImage -> Visible = false;
	PassPC1Image -> Visible = false;
	PassUserUpImage -> Visible = false;
	Brain2MadImage -> Visible = false;
	Brain2HappyImage -> Visible = false;
	PassPC2Image -> Visible = false;
	PassUserDownImage -> Visible = false;
	RoundLabel -> Caption = "Раунд " + IntToStr(++round);
	playerPC1.setTiles(tilesArr);
	playerPC2.setTiles(tilesArr + INITIAL_AMOUNT);
	playerUserUp.setTiles(tilesArr + 2 * INITIAL_AMOUNT);
	playerUserDown.setTiles(tilesArr + 3 * INITIAL_AMOUNT);
	giveTiles();
	leftDirection = LEFT_DIR;
	rightDirection = RIGHT_DIR;
	StartButton -> Visible = true;
    StartButton -> SetFocus();
}

void __fastcall TFormGameTeam::initTiles(Domino *allTiles){
	int index = 0;
	for (int i = 0; i <= MAX_NUM; i++) {
		for (int j = i; j <= MAX_NUM; j++) {
			allTiles[index].setFNum(i);
			allTiles[index].setSNum(j);
			allTiles[index].setDouble(i, j);
			String name = "Tile" + IntToStr(i) + "_" + IntToStr(j);
			allTiles[index].setTile(dynamic_cast<TImage *>(FindComponent(name)));
			index++;
		}
	}
}

void __fastcall TFormGameTeam::getFirstTurn(){
	int pc1Sum = playerPC1.getMaxDoublesSum();
	int pc2Sum = playerPC2.getMaxDoublesSum();
	int userUpSum = playerUserUp.getMaxDoublesSum();
	int userDownSum = playerUserDown.getMaxDoublesSum();
	if (pc1Sum == MAX_SUM)
		currentTurn = PC1_TURN;
	else
		if (pc2Sum == MAX_SUM)
			currentTurn = PC2_TURN;
		else
			if (userUpSum == MAX_SUM)
				currentTurn = USER_UP_TURN;
			else
				currentTurn = USER_DOWN_TURN;
}

void __fastcall TFormGameTeam::giveTiles(){
	for (int i = 0; i < INITIAL_AMOUNT; i++) {
		TImage *ptTile = (TImage *)(playerPC1.getImage(i));
		ptTile -> Visible = true;
		ptTile -> Top = TOP_PC1;
		ptTile -> Left = LEFT_PC1 + i * DELTA;
		ptTile -> Enabled = false;
		ptTile -> Picture = Tile0_0 -> Picture;

		ptTile = (TImage *)(playerPC2.getImage(i));
		ptTile -> Visible = true;
		ptTile -> Top = TOP_PC2;
		ptTile -> Left = LEFT_PC2 + i * DELTA;
		ptTile -> Enabled = false;
		ptTile -> Picture = Tile0_0 -> Picture;

		ptTile = (TImage *)(playerUserUp.getImage(i));
		ptTile -> Visible = true;
		ptTile -> Top = TOP_USER_UP;
		ptTile -> Left = LEFT_USER_UP + i * DELTA;

		ptTile = (TImage *)(playerUserDown.getImage(i));
		ptTile -> Visible = true;
		ptTile -> Top = TOP_USER_DOWN;
		ptTile -> Left = LEFT_USER_DOWN + i * DELTA;
	}
	redrawTiles(playerPC1, FORM_WIDTH);
	redrawTiles(playerUserUp, FORM_WIDTH);
	redrawTiles(playerPC2, FORM_WIDTH);
	redrawTiles(playerUserDown, FORM_WIDTH);
}

void __fastcall TFormGameTeam::processFirstTurn(){
	switch(currentTurn){
		case PC1_TURN: {
			makeFirstTurnPC(playerPC1);
			break;
		}
		case PC2_TURN: {
			makeFirstTurnPC(playerPC2);
			break;
		}
		case USER_UP_TURN: {
			firstTurn = true;
			UserUpPanel -> Visible = true;
			setTilesState(true);
			break;
		}
		case USER_DOWN_TURN: {
			firstTurn = true;
			UserDownPanel -> Visible = true;
			setTilesState(false);
			break;
		}
	}
}

void __fastcall TFormGameTeam::makeFirstTurnPC(Player &playerPC){
	Domino curTurn = playerPC.getTile(0);
	leftNum = curTurn.getFNum();
	rightNum = curTurn.getSNum();
	TImage *ptTile = (TImage *)(playerPC.getImage(0));
	playerPC.deleteTile(0);
	rotateImage(curTurn, RLEFT);
	String fileName = "BlackDominoes/Left/Black" + IntToStr(curTurn.getFNum()) + "-" + IntToStr(curTurn.getSNum()) + ".png";
	ptTile -> Picture -> LoadFromFile(fileName);
	ptTile -> Width = HEIGHT;
	ptTile -> Height = WIDTH;
	ptTile -> Left = coordinates[LEFT_LEFT] = coordinates[RIGHT_LEFT] = FIRST_LEFT;
	ptTile -> Top = coordinates[LEFT_TOP] = coordinates[RIGHT_TOP] = FIRST_TOP;
	redrawTiles(playerPC, FORM_WIDTH);
	if (currentTurn == PC1_TURN){
		changeTurn();
		enableUserTiles(playerUserUp);
	}
	else {
		changeTurn();
		enableUserTiles(playerUserDown);
	}
}

void __fastcall TFormGameTeam::setTilesState(boolean stateForUserUp){
	TImage *ptTile;
	for (int i = 0; i < playerUserUp.getTilesAmount(); i++) {
		ptTile = (TImage *)(playerUserUp.getImage(i));
		ptTile -> Enabled = stateForUserUp;
	}
	for (int i = 0; i < playerUserDown.getTilesAmount(); i++) {
		ptTile = (TImage *)(playerUserDown.getImage(i));
		ptTile -> Enabled = !stateForUserUp;
	}
}

void __fastcall TFormGameTeam::disableTiles(){
	TImage *ptTile;
	for (int i = 0; i < playerUserUp.getTilesAmount(); i++) {
		ptTile = (TImage *)(playerUserUp.getImage(i));
		ptTile -> Enabled = false;
	}
	for (int i = 0; i < playerUserDown.getTilesAmount(); i++) {
		ptTile = (TImage *)(playerUserDown.getImage(i));
		ptTile -> Enabled = false;
	}
}

void __fastcall TFormGameTeam::enableUserTiles(Player playerUser){
	TImage *ptTile;
	int count = 0;
	for (int i = 0; i < playerUser.getTilesAmount(); i++){
		if (canBePlacedLeft(playerUser.getTile(i), leftNum, rightNum)){
			ptTile = (TImage *)(playerUser.getImage(i));
			ptTile -> Enabled = true;
			count++;
		} else if (canBePlacedRight(playerUser.getTile(i), leftNum, rightNum)){
			ptTile = (TImage *)(playerUser.getImage(i));
			ptTile -> Enabled = true;
			count++;
		}
	}
	if (count == 0) {
		if(currentTurn == USER_UP_TURN)
			PassUserUpImage -> Visible = true;
		else
			PassUserDownImage -> Visible = true;
		if(currentTurn == USER_DOWN_TURN){
			Cloud1Image -> Visible = true;
			Brain1HappyImage -> Visible = false;
		} else {
			Cloud2Image -> Visible = true;
			Brain2HappyImage -> Visible = false;
		}
		changeTurn();
		Timer -> Enabled = true;
	} else {
		if(currentTurn == USER_DOWN_TURN){
			UserDownPanel -> Visible = true;
			PassUserDownImage -> Visible = false;
		}
		else {
			UserUpPanel -> Visible = true;
			PassUserUpImage -> Visible = false;
		}
    }
}

void __fastcall TFormGameTeam::makeTurnPC(Player &playerPC){
	bool placeLeft;
	Domino nextTurn = findNextTurn(playerPC, placeLeft, leftNum, rightNum);
	PassPC1Image -> Visible = false;
	PassPC2Image -> Visible = false;
	PassUserUpImage -> Visible = false;
	PassUserDownImage -> Visible = false;
	if (nextTurn.getImage() == NULL) {
		if(currentTurn == PC1_TURN)
			PassPC1Image -> Visible = true;
		else
			PassPC2Image -> Visible = true;
		if (currentTurn == PC1_TURN){
			PassUserUpImage -> Visible = false;
			changeTurn();
			enableUserTiles(playerUserUp);
		}
		else {
            PassUserDownImage -> Visible = false;
			changeTurn();
			enableUserTiles(playerUserDown);
		}
		return;
	}
	playerPC.deleteTile(playerPC.getIndex(nextTurn));
	placeTile(nextTurn, placeLeft, leftNum, rightNum, leftDirection, rightDirection, coordinates);
	changeDirection(coordinates, leftDirection, rightDirection, TILES_IN_LINE);
	if (isRoundOver())
		return;
	redrawTiles(playerPC, FORM_WIDTH);
	if (currentTurn == PC1_TURN){
		changeTurn();
		enableUserTiles(playerUserUp);
	}
	else {
		changeTurn();
		enableUserTiles(playerUserDown);
	}
}

void __fastcall TFormGameTeam::TileClick(TObject *Sender){
	if (currentTurn == USER_UP_TURN){
		UserUpPanel -> Visible = false;
		if (firstTurn)
			makeFirstTurnUser(Sender, playerUserUp);
		else
			makeTurnUser(Sender, playerUserUp);
	} else {
		UserDownPanel -> Visible = false;
		if (firstTurn)
			makeFirstTurnUser(Sender, playerUserDown);
		else
			makeTurnUser(Sender, playerUserDown);
	}
}

void __fastcall TFormGameTeam::makeFirstTurnUser(TObject *Sender, Player &playerUser){
	Domino curTurn = playerUser.getTile(Sender);
	leftNum = curTurn.getFNum();
	rightNum = curTurn.getSNum();
	TImage *ptTile = dynamic_cast<TImage *>(Sender);
	playerUser.deleteTile(playerUser.getIndex(curTurn));
	rotateImage(curTurn, RLEFT);
	ptTile -> Left = coordinates[LEFT_LEFT] = coordinates[RIGHT_LEFT] = FIRST_LEFT;
	ptTile -> Top = coordinates[LEFT_TOP] = coordinates[RIGHT_TOP] = FIRST_TOP;
	ptTile -> Enabled = false;
	redrawTiles(playerUser, FORM_WIDTH);
	disableTiles();
	firstTurn = false;
	srand(time(0));
	Timer -> Interval = std::rand() % MAX_TIMER + MIN_TIMER;
	if(currentTurn == USER_DOWN_TURN){
		Cloud1Image -> Visible = true;
		Brain1HappyImage -> Visible = false;
	} else {
		Cloud2Image -> Visible = true;
		Brain2HappyImage -> Visible = false;
	}
	changeTurn();
	Timer -> Enabled = true;
}

void __fastcall TFormGameTeam::makeTurnUser(TObject *Sender, Player &playerUser){
	Domino nextTurn = playerUser.getTile(Sender);
	PassUserUpImage -> Visible = false;
	PassUserDownImage -> Visible = false;
	PassPC1Image -> Visible = false;
	PassPC2Image -> Visible = false;
	bool placeLeft;
	if (canBePlacedDifferent(nextTurn, leftNum, rightNum)) {
		if (MessageDlgPos("Положить домино слева?", mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0, 815, 335) == IDYES)
			placeLeft = true;
		else
			placeLeft = false;
	} else {
		if (canBePlacedLeft(nextTurn, leftNum, rightNum))
			placeLeft = true;
		else
			placeLeft = false;
	}
	TImage *ptTile = dynamic_cast<TImage *>(Sender);
	playerUser.deleteTile(playerUser.getIndex(nextTurn));
	placeTile(nextTurn, placeLeft, leftNum, rightNum, leftDirection, rightDirection, coordinates);
	changeDirection(coordinates, leftDirection, rightDirection, TILES_IN_LINE);
	ptTile -> Enabled = false;
	if (isRoundOver())
		return;
	redrawTiles(playerUser, FORM_WIDTH);
	disableTiles();
	srand(time(0));
	Timer -> Interval = std::rand() % MAX_TIMER + MIN_TIMER;
	if(currentTurn == USER_DOWN_TURN){
		Cloud1Image -> Visible = true;
		Brain1HappyImage -> Visible = false;
	} else {
		Cloud2Image -> Visible = true;
		Brain2HappyImage -> Visible = false;
	}
	changeTurn();
	Timer -> Enabled = true;
}

void __fastcall TFormGameTeam::StartButtonClick(TObject *Sender)
{
	StartButton -> Visible = false;
	processFirstTurn();
}

void changeTurn(){
	switch(currentTurn){
		case PC1_TURN: {
			currentTurn = USER_UP_TURN;
			break;
		}
		case USER_UP_TURN: {
			currentTurn = PC2_TURN;
			break;
		}
		case PC2_TURN: {
			currentTurn = USER_DOWN_TURN;
			break;
		}
		case USER_DOWN_TURN: {
			currentTurn = PC1_TURN;
			break;
		}
	}
}

void __fastcall TFormGameTeam::TimerTimer(TObject *Sender)
{
	Timer -> Enabled = false;
	if (currentTurn == PC1_TURN) {
		Cloud1Image -> Visible = false;
		Brain1HappyImage -> Visible = true;
	} else {
		Cloud2Image -> Visible = false;
		Brain2HappyImage -> Visible = true;
	}
	if(currentTurn == PC1_TURN)
		makeTurnPC(playerPC1);
	else
		makeTurnPC(playerPC2);
}

bool __fastcall TFormGameTeam::isRoundOver(){
	if (playerPC1.getTilesAmount() == 0 || playerPC2.getTilesAmount() == 0){
		endOfRound(PC_WON);
		return true;
	}
	if (playerUserUp.getTilesAmount() == 0 || playerUserDown.getTilesAmount() == 0){
		showHiddenTiles(playerPC1);
		showHiddenTiles(playerPC2);
		Brain1MadImage -> Visible = true;
		Brain1HappyImage -> Visible = false;
		Brain2MadImage -> Visible = true;
		Brain2HappyImage -> Visible = false;
		endOfRound(USER_WON);
		return true;
	}
	bool placeLeft;
	if(findNextTurn(playerUserUp, placeLeft, leftNum, rightNum).getImage() == NULL &&
	   findNextTurn(playerUserDown, placeLeft, leftNum, rightNum).getImage() == NULL &&
	   findNextTurn(playerPC1, placeLeft, leftNum, rightNum).getImage() == NULL &&
	   findNextTurn(playerPC2, placeLeft, leftNum, rightNum).getImage() == NULL){
		showHiddenTiles(playerPC1);
		showHiddenTiles(playerPC2);
		redrawTiles(playerPC1, FORM_WIDTH);
		redrawTiles(playerPC2, FORM_WIDTH);
		endOfRound(FISH_WON);
		return true;
	}
	return false;
}

void __fastcall TFormGameTeam::PCWonRound(){
	int points = playerUserUp.getNumsSum() + playerUserDown.getNumsSum();
	if (FormLog -> LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] != "")
		FormLog -> LogSG -> RowCount++;
	if (gameModeGameTeam == CLASSIC) {
		playerPC1.addPoints(points);
		PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
		FormLog -> LogSG -> Cells[1][FormLog -> LogSG -> RowCount - 1] = IntToStr(points);
		FormLog -> LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = "0";
		ShowMessage("Компьютеры выйграли раунд и заработали " + IntToStr(points) + " " + toRus(points));
	} else if (gameModeGameTeam == GOAT) {
		playerUserUp.addPoints(points);
		PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
		FormLog -> LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = IntToStr(points);
		FormLog -> LogSG -> Cells[1][FormLog -> LogSG -> RowCount - 1] = "0";
		ShowMessage("Компьютеры выйграли раунд. \nВашей команде начисленно " + IntToStr(points) + " штрафных " + toRus(points));
	}
	currentTurn = PC1_TURN;
}

void __fastcall TFormGameTeam::userWonRound(){
	int points = playerPC1.getNumsSum() + playerPC2.getNumsSum();
	if (FormLog->LogSG->Cells[0][FormLog->LogSG->RowCount - 1] != "")
		FormLog->LogSG->RowCount++;
	if (gameModeGameTeam == CLASSIC) {
		playerUserUp.addPoints(points);
		PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
		FormLog->LogSG->Cells[0][FormLog -> LogSG -> RowCount - 1] = IntToStr(points);
		FormLog->LogSG->Cells[1][FormLog -> LogSG -> RowCount - 1] = "0";
		ShowMessage("Ваша команда выйграла раунд и заработала " + IntToStr(points) + " " + toRus(points));
	} else if (gameModeGameTeam == GOAT) {
		playerPC1.addPoints(points);
		PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
		FormLog->LogSG->Cells[1][FormLog -> LogSG -> RowCount - 1] = IntToStr(points);
		FormLog->LogSG->Cells[0][FormLog -> LogSG -> RowCount - 1] = "0";
		ShowMessage("Ваша команда выйграла раунд.\nКомпьютерам начисленно " + IntToStr(points) + " штрафных " + toRus(points));
	}
	currentTurn = USER_DOWN_TURN;
}

void __fastcall TFormGameTeam::fishWonRound(){
	int pointsPC = playerPC1.getNumsSum() + playerPC2.getNumsSum();
	int pointsUser = playerUserUp.getNumsSum() + playerUserDown.getNumsSum();
	if (FormLog -> LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] != "")
		FormLog -> LogSG -> RowCount++;
	if (pointsUser < pointsPC) {
		pointsUser = pointsPC - pointsUser;
		currentTurn = USER_DOWN_TURN;
		Brain1MadImage -> Visible = true;
		Brain2MadImage -> Visible = true;
		if (gameModeGameTeam == CLASSIC) {
			playerUserUp.addPoints(pointsUser);
			PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
			FormLog->LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = IntToStr(pointsUser) + " (рыба)";
			FormLog->LogSG -> Cells[1][FormLog -> LogSG->RowCount - 1] = "0";
			ShowMessage("Ваша команда выйграла раунд и заработала " + IntToStr(pointsUser) + " " + toRus(pointsUser));
		} else
			if (gameModeGameTeam == GOAT) {
				playerPC1.addPoints(pointsUser);
				PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
				FormLog->LogSG -> Cells[1][FormLog -> LogSG -> RowCount - 1] = IntToStr(pointsUser) + " (рыба)";
				FormLog->LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = "0";
				ShowMessage("Ваша команда выйграла раунд.\nКомпьютерам начисленно " + IntToStr(pointsUser) + " штрафных " + toRus(pointsUser));
		}
	} else {
		if (pointsUser > pointsPC) {
			pointsPC = pointsUser - pointsPC;
			currentTurn = PC1_TURN;
			if (gameModeGameTeam == CLASSIC) {
				playerPC1.addPoints(pointsPC);
				PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
				FormLog->LogSG -> Cells[1][FormLog -> LogSG -> RowCount - 1] = IntToStr(pointsPC) + " (рыба)";
				FormLog->LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = "0";
				ShowMessage("Компьютеры выйграли раунд и заработали " + IntToStr(pointsPC) + " " + toRus(pointsPC));
		} else
			if (gameModeGameTeam == GOAT) {
				playerUserUp.addPoints(pointsPC);
				PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
				FormLog->LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = IntToStr(pointsPC) + " (рыба)";
				FormLog->LogSG->Cells[1][FormLog -> LogSG -> RowCount - 1] = "0";
				ShowMessage("Компьютеры выйграли раунд. \nВашей команде начисленно " + IntToStr(pointsPC) + " штрафных " + toRus(pointsPC));
			}
		} else{
			ShowMessage("Ничья");
			getFirstTurn();
		}
	}
}

void __fastcall TFormGameTeam::endOfRound(int winner){
	switch (winner) {
		case PC_WON: {
			PCWonRound();
			break;
		}
		case USER_WON: {
			userWonRound();
			break;
		}
		case FISH_WON: {
			fishWonRound();
			break;
		}
	}
	isGameOver();
	initRound();
}

void __fastcall TFormGameTeam::isGameOver(){
	if (gameModeGameTeam == CLASSIC){
		if (playerPC1.getPoints() >= pointsAimGameTeam){
			PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
			ShowMessage("К сожалению ваша команда проиграла.\nУдачи в другой раз!");
			FormGameTeam -> Close();
		} else
			if (playerUserUp.getPoints() >= pointsAimGameTeam){
				PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
				ShowMessage("Поздравляю, ваша команада победила!\nУдача на вашей стороне!");
				FormGameTeam -> Close();
			}
	} else
		if (gameModeGameTeam == GOAT) {
			if (playerUserUp.getPoints() >= pointsAimGameTeam){
				PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
				ShowMessage("К сожалению ваша команада проиграла.\nУдачи в другой раз!");
				FormGameTeam -> Close();
			} else
				if (playerPC1.getPoints() >= pointsAimGameTeam){
					PointsLabel -> Caption = IntToStr(playerUserUp.getPoints()) + " : " + IntToStr(playerPC1.getPoints());
					ShowMessage("Поздравляю, ваша команда победила!\nУдача на вашей стороне!");
				FormGameTeam -> Close();
				}
		}
}

void __fastcall TFormGameTeam::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}
void __fastcall TFormGameTeam::LogMenuItemClick(TObject *Sender)
{
    FormLog -> ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TFormGameTeam::RulesMenuItemClick(TObject *Sender)
{
	String s1, s2, s3, s4, s5, s6, s7;
	if (gameModeGameTeam == CLASSIC) {
		s1 = "Правила Игры Классика";
		s5 = "Команде-победителю в качестве выигрыша записывается сумма очков всех камней на руках проигравших. При блокировке («рыбе») выигрыш принадлежит тем, у кого на руках ";
		s6 = "меньше очков. В выигрыш им записывается разность очков противника и их собственных.";
	} else if (gameModeGameTeam == GOAT) {
		s1 = "Правила Игры Козёл";
		s5 = "Проигравшей команде записывается на счет сумма очков всех камней на их руках. При блокировке («рыбе») выигрыш принадлежит тем, у кого на руках ";
		s6 = "меньше очков. Проигравшим записывается разность их очков и противника.";
	}
	s2 = "Участники играют в командах, сидя напротив друг друга. Цель игры - избавиться от всех домино хотя бы одному из членов команды. Игрокам сдают по семь доминошек. Начинает игрок, у которого на руках находится старший дубль. Если же на руках нет ни ";
	s3 = "одного дубля, то начинает тот, кто имеет камень с наибольшим значением (например, 6-5). Следующий игрок выставляет камень с соответствующими очками. Если подходящих камней нет, то ";
	s4 = "он вынужден пропустить ход. Игра заканчивается, когда один из игроков выложит последний камень. Возможно окончание игры «рыбой» - так называется блокировка выкладки, когда на руках ещё есть камни, но доложить нечего. ";
	s7 = "Игра продолжается до " + IntToStr(pointsAimGameTeam) + " очков.";
	ShowMessage(s1 + sLineBreak + s2 + s3 + s4 + s5 + s6 + sLineBreak + s7);
}

void __fastcall TFormGameTeam::DeveloperMenuItemClick(TObject *Sender)
{
	String message = "Курсовая работа Гайдука Евгения, студента группы 151002";
	ShowMessage(message);
}

void __fastcall TFormGameTeam::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if (MessageDlgPos("Вы уверены, что хотите выйти?\nИгра будет завершена", mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0, 815, 335) == IDYES)
		CanClose = true;
	else
		CanClose = false;
}
