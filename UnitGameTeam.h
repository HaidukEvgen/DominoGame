#ifndef UnitGameTeamH
#define UnitGameTeamH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.Menus.hpp>
#include "UnitGame.h"

class TFormGameTeam : public TForm
{
__published:
	TImage *TableImage;
	TImage *Tile0_0;
	TImage *Tile0_1;
	TImage *Tile0_2;
	TImage *Tile0_3;
	TImage *Tile0_4;
	TImage *Tile0_5;
	TImage *Tile0_6;
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
	TImage *Tile6_6;
	TImage *Tile1_2;
	TImage *Tile1_3;
	TImage *Tile1_4;
	TImage *Tile1_5;
	TImage *Tile1_6;
	TImage *Tile5_6;
	TImage *Tile1_1;
	TImage *Brain1Image;
	TImage *Cloud1Image;
	TImage *Brain1HappyImage;
	TImage *PassPC1Image;
	TImage *PassUserDownImage;
	TImage *Brain1MadImage;
	TButton *StartButton;
	TPanel *InfoPanel;
	TLabel *RoundLabel;
	TLabel *GameTypeLabel;
	TPanel *ScorePanel;
	TLabel *ScoreLabel;
	TLabel *PointsLabel;
	TLabel *AimLabel;
	TMainMenu *MainMenu;
	TMenuItem *RulesMenuItem;
	TMenuItem *DeveloperMenuItem;
	TMenuItem *LogMenuItem;
	TTimer *Timer;
	TImage *Brain2Image;
	TImage *Brain2HappyImage;
	TImage *Brain2MadImage;
	TImage *Cloud2Image;
	TImage *PassUserUpImage;
	TImage *PassPC2Image;
	TPanel *UserUpPanel;
	TLabel *TurnUpLabel;
	TPanel *UserDownPanel;
	TLabel *TurnDownLabel;
	void __fastcall FormShow(TObject *Sender);
	void __fastcall initGame();
    void __fastcall initRound();
	void __fastcall initTiles(Domino *allTiles);
    void __fastcall prepareTiles();
	void __fastcall getFirstTurn();
    void __fastcall giveTiles();
	void __fastcall StartButtonClick(TObject *Sender);
	void __fastcall processFirstTurn();
	void __fastcall makeFirstTurnPC(Player &playerPC);
	void __fastcall setTilesState(boolean stateForUserUp);
    void __fastcall disableTiles();
	void __fastcall enableUserTiles(Player playerUser);
	void __fastcall makeTurnPC(Player &playerPC);
	void __fastcall TileClick(TObject *Sender);
	void __fastcall TimerTimer(TObject *Sender);
	void __fastcall makeFirstTurnUser(TObject *Sender, Player &playerUser);
	void __fastcall makeTurnUser(TObject *Sender, Player &playerUser);
	bool __fastcall isRoundOver();
	void __fastcall PCWonRound();
	void __fastcall userWonRound();
    void __fastcall fishWonRound();
	void __fastcall endOfRound(int winner);
	void __fastcall isGameOver();
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall LogMenuItemClick(TObject *Sender);
	void __fastcall RulesMenuItemClick(TObject *Sender);
	void __fastcall DeveloperMenuItemClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
private:
public:
	int gameModeGameTeam;
	int pointsAimGameTeam;
	__fastcall TFormGameTeam(TComponent* Owner);
};

extern PACKAGE TFormGameTeam *FormGameTeam;

#endif
