	#pragma once
	#ifndef UnitGamePCH
	#define UnitGamePCH
	#include <System.Classes.hpp>
	#include <Vcl.Controls.hpp>
	#include <Vcl.StdCtrls.hpp>
	#include <Vcl.Forms.hpp>
	#include <Vcl.ExtCtrls.hpp>
	#include <Vcl.Imaging.pngimage.hpp>
	#include <Vcl.Menus.hpp>
	#include <Vcl.Imaging.GIFImg.hpp>
	#include <Vcl.Imaging.jpeg.hpp>
	#include "UnitDomino.h"
	#include "UnitPlayer.h"
	#include <Vcl.ComCtrls.hpp>
	#include "UnitConsts.h"
	#include "UnitGame.h"

	class TFormGamePC :public TForm
	{
	__published:
		TMainMenu *MainMenu;
		TMenuItem *RulesMenuItem;
		TMenuItem *DeveloperMenuItem;
		TImage *Tile0_0;
		TImage *Tile0_1;
		TImage *Tile0_2;
		TImage *Tile0_3;
		TImage *Tile0_4;
		TImage *Tile0_5;
		TImage *Tile0_6;
		TImage *Tile1_1;
		TImage *Tile1_2;
		TImage *Tile1_3;
		TImage *Tile1_4;
		TImage *Tile1_5;
		TImage *Tile1_6;
		TImage *Tile2_2;
		TImage *Tile2_3;
		TImage *Tile2_4;
		TImage *Tile2_5;
		TImage *Tile2_6;
		TImage *Tile3_3;
		TImage *Tile3_4;
		TImage *Tile3_5;
		TImage *Tile3_6;
		TImage *Tile4_4;
		TImage *Tile4_5;
		TImage *Tile4_6;
		TImage *Tile5_5;
		TImage *Tile5_6;
		TImage *Tile6_6;
		TPanel *BazarPanel;
		TLabel *BazarLabel;
		TImage *Image1;
		TImage *Image2;
		TImage *Image3;
		TImage *Image4;
		TImage *Image5;
		TImage *Image6;
		TImage *Image7;
		TImage *Image8;
		TImage *Image9;
		TImage *Image10;
		TImage *Image11;
		TImage *Image12;
		TImage *Image13;
		TImage *Image14;
		TImage *BrainImage;
		TImage *TableImage;
		TTimer *Timer;
		TButton *StartButton;
		TImage *CloudImage;
		TImage *BrainHappyImage;
		TImage *PassPCImage;
		TImage *PassUserImage;
		TImage *BrainMadImage;
		TPanel *InfoPanel;
		TLabel *RoundLabel;
		TPanel *ScorePanel;
		TLabel *ScoreLabel;
		TLabel *PointsLabel;
		TPanel *TilesLeftPanel;
		TLabel *TilesLeftLabel;
		TLabel *GameTypeLabel;
		TLabel *AimLabel;
		TMenuItem *LogMenuItem;
		void __fastcall FormShow(TObject *Sender);
		void __fastcall initGame();
		void __fastcall initRound();
		void __fastcall ImageClick(TObject *Sender);
		void __fastcall initTiles(Domino *allTiles);
		void __fastcall prepareTiles();
		void __fastcall getFirstTurn();
		void __fastcall giveTiles();
		void __fastcall processFirstTurn();
		void __fastcall setTilesState(boolean state);
		void __fastcall makeTurnPC();
		void __fastcall TileClick(TObject *Sender);
		void __fastcall StartButtonClick(TObject *Sender);
		void __fastcall makeFirstTurnPC();
		void __fastcall makeFirstTurnUser(TObject *Sender);
		void __fastcall makeTurnUser(TObject *Sender);
		void __fastcall enableUserTiles();
		void __fastcall getBazarTileUser();
		Domino __fastcall getBazarTilePC();
		bool __fastcall isRoundOver();
		void __fastcall PCWonRound();
		void __fastcall userWonRound();
		void __fastcall fishWonRound();
		void __fastcall endOfRound(int winner);
		void __fastcall isGameOver();
		void __fastcall TimerTimer(TObject *Sender);
		void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
		void __fastcall DeveloperMenuItemClick(TObject *Sender);
		void __fastcall RulesMenuItemClick(TObject *Sender);
		void __fastcall LogMenuItemClick(TObject *Sender);
		void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	private:
	public:
		int gameModeGamePC;
		int pointsAimGamePC;
		__fastcall TFormGamePC(TComponent* Owner);
	};

	extern PACKAGE TFormGamePC *FormGamePC;

	#endif
