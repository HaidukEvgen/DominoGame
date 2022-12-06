#include <vcl.h>
#pragma hdrstop
#include "UnitGamePC.h"
#include "UnitDomino.h"
#include <cstdlib>
#include <string>
#include "UnitPlayer.h"
#include "UnitMenu.h"
#include "UnitLog.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
#define TILES_IN_LINE 7
#define FORM_WIDTH FormGamePC -> Width

TFormGamePC *FormGamePC;
Domino tilesArr[MAX_AMOUNT];
Domino bazarArr[MAX_AMOUNT / 2];
Player playerPC;
Player playerUser;
int curTurn;
int leftNum;
int rightNum;
bool firstTurn;
bool pcSkipped = false;
int bazarIndex = 0;
int leftDirection = LEFT_DIR;
int rightDirection = RIGHT_DIR;
int round = 1;
int coordinates[4];

__fastcall TFormGamePC::TFormGamePC(TComponent* Owner)
	: TForm(Owner)
{
}

void processFirstTurn();
void fillBazarArr();

void __fastcall TFormGamePC::FormShow(TObject *Sender){
	initGame();
}

void __fastcall TFormGamePC::initGame(){
	FormGamePC -> ControlStyle = FormGamePC -> ControlStyle << csOpaque;
	BazarPanel -> ControlStyle = BazarPanel -> ControlStyle << csOpaque;
	if (gameModeGamePC == CLASSIC)
		GameTypeLabel -> Caption = "Домино Классика";
	else
		if (gameModeGamePC == GOAT)
			GameTypeLabel -> Caption = "Домино Козел";
	AimLabel -> Caption = "(до " + IntToStr(pointsAimGamePC) + ")";
	FormLog -> initLogForm("Компьютер");
	initTiles(tilesArr);
	randomizeTiles(tilesArr);
	playerPC.setTiles(tilesArr);
	playerPC.setLeft(0);
    playerUser.setLeft(0);
	playerUser.setTiles(tilesArr + INITIAL_AMOUNT);
	playerPC.setPoints(0);
    playerUser.setPoints(0);
	fillBazarArr();
	getFirstTurn();
	giveTiles();
}

void __fastcall TFormGamePC::prepareTiles(){
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
	for (int i = 1; i <= MAX_AMOUNT / 2; i++) {
		String name = "Image" + IntToStr(i);
		TImage *ptTile = dynamic_cast<TImage *>(FindComponent(name));
		ptTile -> Visible = true;
	}
}

void __fastcall TFormGamePC::initRound(){
	randomizeTiles(tilesArr);
	playerPC.deleteTiles();
	playerUser.deleteTiles();
	prepareTiles();
	BrainMadImage -> Visible = false;
	BrainHappyImage -> Visible = false;
	PassPCImage -> Visible = false;
	PassUserImage -> Visible = false;
	TilesLeftLabel -> Caption = "14 домино на базаре";
	RoundLabel -> Caption = "Раунд " + IntToStr(++round);
	playerPC.setTiles(tilesArr);
	playerUser.setTiles(tilesArr + INITIAL_AMOUNT);
	fillBazarArr();
	giveTiles();
	leftDirection = LEFT_DIR;
	rightDirection = RIGHT_DIR;
	pcSkipped = false;
	bazarIndex = 0;
	StartButton -> Visible = true;
    StartButton -> SetFocus();
}

void __fastcall TFormGamePC::initTiles(Domino *allTiles){
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

void fillBazarArr(){
	for (int i = 0; i < MAX_AMOUNT / 2; i++)
		bazarArr[i] = tilesArr[i + MAX_AMOUNT / 2];
}

void __fastcall TFormGamePC::getFirstTurn(){
	int pcSum = playerPC.getMaxDoublesSum();
	int userSum = playerUser.getMaxDoublesSum();
	if (pcSum != userSum){
		if (pcSum > userSum)
			curTurn = PC_TURN;
		else
			curTurn = USER_TURN;
	} else {
		if (playerPC.getMaxSum() > playerUser.getMaxSum())
			curTurn = PC_TURN;
		else
			curTurn = USER_TURN;
	}
}

void __fastcall TFormGamePC::giveTiles(){
	for (int i = 0; i < INITIAL_AMOUNT; i++) {
		TImage *ptTile = (TImage *)(playerPC.getImage(i));
		ptTile -> Visible = true;
		ptTile -> Top = TOP_PC;
		ptTile -> Left = LEFT_PC + i * DELTA;
		ptTile -> Enabled = false;
		ptTile -> Picture = Tile0_0 -> Picture;
		ptTile = (TImage *)(playerUser.getImage(i));
		ptTile -> Visible = true;
		ptTile -> Top = TOP_USER;
		ptTile -> Left = LEFT_USER + i * DELTA;
	}
	redrawTiles(playerPC, FORM_WIDTH);
	redrawTiles(playerUser, FORM_WIDTH);
}

void __fastcall TFormGamePC::processFirstTurn(){
	if (curTurn == PC_TURN) {
		makeFirstTurnPC();
	} else {
		firstTurn = true;
		setTilesState(true);
	}
}

void __fastcall TFormGamePC::setTilesState(boolean state){
	TImage *ptTile;
	for (int i = 0; i < playerUser.getTilesAmount(); i++) {
		ptTile = (TImage *)(playerUser.getImage(i));
		ptTile -> Enabled = state;
	}
}

void __fastcall TFormGamePC::makeFirstTurnPC(){
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
	enableUserTiles();
}

void __fastcall TFormGamePC::makeTurnPC(){
	bool placeLeft;
	Domino nextTurn = findNextTurn(playerPC, placeLeft, leftNum, rightNum);
	PassPCImage -> Visible = false;
	if (nextTurn.getImage() == NULL && (bazarIndex == MAX_AMOUNT / 2)) {
		PassPCImage -> Visible = true;
		pcSkipped = true;
		enableUserTiles();
		return;
	}
	while (nextTurn.getImage() == NULL && bazarIndex < MAX_AMOUNT / 2){
		playerPC.addTile(getBazarTilePC());
		nextTurn = findNextTurn(playerPC, placeLeft, leftNum, rightNum);
		redrawTiles(playerPC, FORM_WIDTH);
	}
	if (nextTurn.getImage() == NULL) {
		pcSkipped = true;
		PassPCImage -> Visible = true;
        enableUserTiles();
		return;
	}
	pcSkipped = false;
	playerPC.deleteTile(playerPC.getIndex(nextTurn));
	placeTile(nextTurn, placeLeft, leftNum, rightNum, leftDirection, rightDirection, coordinates);
	changeDirection(coordinates, leftDirection, rightDirection, TILES_IN_LINE);
	if (isRoundOver())
		return;
	redrawTiles(playerPC, FORM_WIDTH);
	enableUserTiles();
}

void __fastcall TFormGamePC::makeFirstTurnUser(TObject *Sender){
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
	setTilesState(false);
	firstTurn = false;
	srand(time(0));
	Timer -> Interval = std::rand() % MAX_TIMER + MIN_TIMER;
	CloudImage -> Visible = true;
	BrainHappyImage -> Visible = false;
	Timer -> Enabled = true;
}

void __fastcall TFormGamePC::makeTurnUser(TObject *Sender){
	Domino nextTurn = playerUser.getTile(Sender);
	PassUserImage -> Visible = false;
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
	setTilesState(false);
	srand(time(0));
	Timer -> Interval = std::rand() % MAX_TIMER + MIN_TIMER;
	CloudImage -> Visible = true;
	BrainHappyImage -> Visible = false;
    PassPCImage -> Visible = false;
	Timer -> Enabled = true;
}

void __fastcall TFormGamePC::enableUserTiles(){
	TImage *ptTile;
	int count = 0;
	for (int i = 0; i < playerUser.getTilesAmount(); i++){
		if (canBePlacedLeft(playerUser.getTile(i), leftNum, rightNum)){
			ptTile = (TImage *)(playerUser.getImage(i));
			ptTile -> Enabled = true;
			count++;
		}
		else if (canBePlacedRight(playerUser.getTile(i), leftNum, rightNum)){
			ptTile = (TImage *)(playerUser.getImage(i));
			ptTile -> Enabled = true;
			count++;
		}
	}
	if (count == 0) {
		if (bazarIndex == MAX_AMOUNT / 2){
			PassUserImage -> Visible = true;
			if (pcSkipped) {
				isRoundOver();
			} else {
				PassUserImage -> Visible = true;
				makeTurnPC();
			}
		}
		else
			getBazarTileUser();
    }
}

Domino __fastcall TFormGamePC::getBazarTilePC(){
	bool isGoing = true;
	int i = 1;
	String name;
	while (isGoing && (i < MAX_AMOUNT / 2)){
		name = "Image" + IntToStr(i);
		TImage *ptTile = dynamic_cast<TImage *>(FindComponent(name));
		if (ptTile -> Visible){
			isGoing = false;
			ptTile -> Visible = false;
			TilesLeftLabel -> Caption = IntToStr(MAX_AMOUNT / 2 - 1 - bazarIndex) + " домино на базаре";
		}
		i++;
	}
	if (bazarIndex == MAX_AMOUNT / 2 - 1)
			TilesLeftLabel -> Caption = "0 домино на базаре";
	TImage *ptTile = (TImage *)bazarArr[bazarIndex].getImage();
	ptTile -> Visible = true;
	ptTile -> Picture -> LoadFromFile("BlackDominoes/Up/Black0-0.png");;
	ptTile -> Top = TOP_PC;
	return bazarArr[bazarIndex++];
}

void __fastcall TFormGamePC::getBazarTileUser(){
	BazarPanel -> Visible = true;
}

void __fastcall TFormGamePC::ImageClick(TObject *Sender){
	TImage *ptTile = dynamic_cast<TImage *>(Sender);
	ptTile -> Visible = false;
	TilesLeftLabel -> Caption = IntToStr(MAX_AMOUNT / 2 - 1 - bazarIndex) + " домино на базаре";
	playerUser.addTile(bazarArr[bazarIndex]);
	ptTile = (TImage *)bazarArr[bazarIndex].getImage();
	ptTile -> Top = TOP_USER;
	ptTile -> Visible = true;
	redrawTiles(playerUser, FORM_WIDTH);
	bazarIndex++;
	bool placeLeft;
	if (bazarIndex == 14 || findNextTurn(playerUser, placeLeft, leftNum, rightNum).getImage() != NULL)
		BazarPanel -> Visible = false;
	enableUserTiles();
}

void __fastcall TFormGamePC::TileClick(TObject *Sender){
	if (firstTurn)
		makeFirstTurnUser(Sender);
	else
		makeTurnUser(Sender);
}

bool __fastcall TFormGamePC::isRoundOver(){
	if (playerPC.getTilesAmount() == 0){
		endOfRound(PC_WON);
		return true;
	}
	if (playerUser.getTilesAmount() == 0){
		showHiddenTiles(playerPC);
		BrainMadImage -> Visible = true;
		BrainHappyImage -> Visible = false;
		endOfRound(USER_WON);
		return true;
	}
	bool placeLeft;
	if (bazarIndex == MAX_AMOUNT / 2 && findNextTurn(playerUser, placeLeft, leftNum, rightNum).getImage() == findNextTurn(playerPC, placeLeft, leftNum, rightNum).getImage()){
		showHiddenTiles(playerPC);
		redrawTiles(playerPC, FORM_WIDTH);
		endOfRound(FISH_WON);
		return true;
	}
	return false;
}

void __fastcall TFormGamePC::PCWonRound(){
	int points = playerUser.getNumsSum();
	if (FormLog -> LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] != "")
		FormLog -> LogSG -> RowCount++;
	if (gameModeGamePC == CLASSIC) {
		playerPC.addPoints(points);
		PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
		FormLog -> LogSG -> Cells[1][FormLog -> LogSG -> RowCount - 1] = IntToStr(points);
		FormLog -> LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = "0";
		ShowMessage("Компьютер выйграл раунд и заработал " + IntToStr(points) + " " + toRus(points));
	} else if (gameModeGamePC == GOAT) {
		playerUser.addPoints(points);
		PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
		FormLog -> LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = IntToStr(points);
		FormLog -> LogSG -> Cells[1][FormLog -> LogSG -> RowCount - 1] = "0";
		ShowMessage("Компьютер выйграл раунд. \nВам начисленно " + IntToStr(points) + " штрафных " + toRus(points));
	}
	curTurn = PC_TURN;
}

void __fastcall TFormGamePC::userWonRound(){
	int points = playerPC.getNumsSum();
	if (FormLog->LogSG->Cells[0][FormLog->LogSG->RowCount - 1] != "")
		FormLog->LogSG->RowCount++;
	if (gameModeGamePC == CLASSIC) {
		playerUser.addPoints(points);
		PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
		FormLog->LogSG->Cells[0][FormLog -> LogSG -> RowCount - 1] = IntToStr(points);
		FormLog->LogSG->Cells[1][FormLog -> LogSG -> RowCount - 1] = "0";
		ShowMessage("Вы выйграли раунд и заработали " + IntToStr(points) + " " + toRus(points));
	} else if (gameModeGamePC == GOAT) {
		playerPC.addPoints(points);
		PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
		FormLog->LogSG->Cells[1][FormLog -> LogSG -> RowCount - 1] = IntToStr(points);
		FormLog->LogSG->Cells[0][FormLog -> LogSG -> RowCount - 1] = "0";
		ShowMessage("Вы выйграли раунд.\nКомпьютеру начисленно " + IntToStr(points) + " штрафных " + toRus(points));
	}
	curTurn = USER_TURN;
}

void __fastcall TFormGamePC::fishWonRound(){
	int pointsPC = playerPC.getNumsSum();
	int pointsUser = playerUser.getNumsSum();
	if (FormLog -> LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] != "")
		FormLog -> LogSG -> RowCount++;
	if (pointsUser < pointsPC) {
		pointsUser = pointsPC - pointsUser;
		curTurn = USER_TURN;
		BrainMadImage -> Visible = true;
		if (gameModeGamePC == CLASSIC) {
			playerUser.addPoints(pointsUser);
			PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
			FormLog->LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = IntToStr(pointsUser) + " (рыба)";
			FormLog->LogSG -> Cells[1][FormLog -> LogSG->RowCount - 1] = "0";
			ShowMessage("Вы выйграли раунд и заработали " + IntToStr(pointsUser) + " " + toRus(pointsUser));
		} else
			if (gameModeGamePC == GOAT) {
				playerPC.addPoints(pointsUser);
				PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
				FormLog->LogSG -> Cells[1][FormLog -> LogSG -> RowCount - 1] = IntToStr(pointsUser) + " (рыба)";
				FormLog->LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = "0";
				ShowMessage("Вы выйграли раунд.\nКомпьютеру начисленно " + IntToStr(pointsUser) + " штрафных " + toRus(pointsUser));
		}
	} else {
		if (pointsUser > pointsPC) {
			pointsPC = pointsUser - pointsPC;
			curTurn = PC_TURN;
			if (gameModeGamePC == CLASSIC) {
				playerPC.addPoints(pointsPC);
				PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
				FormLog->LogSG -> Cells[1][FormLog -> LogSG -> RowCount - 1] = IntToStr(pointsPC) + " (рыба)";
				FormLog->LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = "0";
				ShowMessage("Компьютер выйграл раунд и заработал " + IntToStr(pointsPC) + " " + toRus(pointsPC));
		} else
			if (gameModeGamePC == GOAT) {
				playerUser.addPoints(pointsPC);
				PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
				FormLog->LogSG -> Cells[0][FormLog -> LogSG -> RowCount - 1] = IntToStr(pointsPC) + " (рыба)";
				FormLog->LogSG->Cells[1][FormLog -> LogSG -> RowCount - 1] = "0";
				ShowMessage("Компьютер выйграл раунд. \nВам начисленно " + IntToStr(pointsPC) + " штрафных " + toRus(pointsPC));
			}
		} else{
			ShowMessage("Ничья");
			getFirstTurn();
		}
	}
}

void __fastcall TFormGamePC::endOfRound(int winner){
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

void __fastcall TFormGamePC::isGameOver(){
	if (gameModeGamePC == CLASSIC){
		if (playerPC.getPoints() >= pointsAimGamePC){
			PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
			ShowMessage("К сожалению вы проиграли.\nУдачи в другой раз!");
			FormGamePC -> Close();
		} else
			if (playerUser.getPoints() >= pointsAimGamePC){
				PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
				ShowMessage("Поздравляю, вы выйграли!\nУдача на вашей стороне!");
				FormGamePC -> Close();
			}
	} else
		if (gameModeGamePC == GOAT) {
			if (playerUser.getPoints() >= pointsAimGamePC){
				PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());

				ShowMessage("К сожалению вы проиграли.\nУдачи в другой раз!");
				FormGamePC -> Close();
			} else
				if (playerPC.getPoints() >= pointsAimGamePC){
					PointsLabel -> Caption = IntToStr(playerUser.getPoints()) + " : " + IntToStr(playerPC.getPoints());
					ShowMessage("Поздравляю, вы выйграли!\nУдача на вашей стороне!");
					FormGamePC -> Close();
				}
		}
}

void __fastcall TFormGamePC::StartButtonClick(TObject *Sender)
{
	StartButton -> Visible = false;
	processFirstTurn();
}

void __fastcall TFormGamePC::TimerTimer(TObject *Sender)
{
	Timer -> Enabled = false;
	CloudImage -> Visible = false;
	BrainHappyImage -> Visible = true;
	makeTurnPC();
}

void __fastcall TFormGamePC::FormClose(TObject *Sender, TCloseAction &Action)
{
	Action = caFree;
}

void __fastcall TFormGamePC::DeveloperMenuItemClick(TObject *Sender)
{
	String message = "Курсовая работа Гайдука Евгения, студента группы 151002";
	ShowMessage(message);
}

void __fastcall TFormGamePC::RulesMenuItemClick(TObject *Sender)
{
	String s1, s2, s3, s4, s5, s6, s7;
	if (gameModeGamePC == CLASSIC) {
		s1 = "Правила Игры Классика";
		s5 = "Победителю в качестве выигрыша записывается сумма очков всех камней на руках проигравшего. При блокировке («рыбе») выигрыш принадлежит тому, у кого на руках ";
		s6 = "меньше очков. В выигрыш ему записывается разность очков противника и его собственных.";
	} else if (gameModeGamePC == GOAT) {
		s1 = "Правила Игры Козёл";
		s5 = "Проигравшему записывается на счет сумма очков всех камней на его руках. При блокировке («рыбе») выигрыш принадлежит тому, у кого на руках ";
		s6 = "меньше очков. Проигравшему записывается разность его очков и противника.";
	}
	s2 = "Игрокам сдают по семь доминошек. Остальные размещаются в резерве («базаре»). Начинает игрок, у которого на руках находится старший дубль. Если же на руках нет ни ";
	s3 = "одного дубля, то начинает тот, кто имеет камень с наибольшим значением (например, 6-5). Следующий игрок выставляет камень с соответствующими очками. Если подходящих камней нет, то ";
	s4 = "приходится добирать из резерва. Игра заканчивается, когда один из игроков выложит последний камень. Возможно окончание игры «рыбой» - так называется блокировка выкладки, когда на руках ещё есть камни, но доложить нечего. ";
	s7 = "Игра продолжается до " + IntToStr(pointsAimGamePC) + " очков.";
	ShowMessage(s1 + sLineBreak + s2 + s3 + s4 + s5 + s6 + sLineBreak + s7);
}

void __fastcall TFormGamePC::LogMenuItemClick(TObject *Sender)
{
	FormLog -> ShowModal();
}


void __fastcall TFormGamePC::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	if (MessageDlgPos("Вы уверены, что хотите выйти?\nИгра будет завершена", mtInformation, TMsgDlgButtons() << mbYes << mbNo, 0, 815, 335) == IDYES)
		CanClose = true;
	else
		CanClose = false;
}
