#include <vcl.h>
#pragma hdrstop
#include "UnitGameMode.h"
#include "UnitGamePC.h"
#include "UnitMenu.h"
#include "UnitGameTeam.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormGameMode *FormGameMode;
bool gamePC;

__fastcall TFormGameMode::TFormGameMode(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TFormGameMode::PlayButtonClick(TObject *Sender)
{
	if (gamePC) {
		Application-> CreateForm(__classid(TFormGamePC), &FormGamePC);
		if (RadioGroup -> ItemIndex == 0)
			FormGamePC -> gameModeGamePC = CLASSIC;
		else if (RadioGroup -> ItemIndex == 1)
			FormGamePC -> gameModeGamePC = GOAT;
		FormGamePC -> pointsAimGamePC = SpinEdit -> Value;
		FormGamePC -> ShowModal();
	} else {
		Application-> CreateForm(__classid(TFormGameTeam), &FormGameTeam);
		if (RadioGroup -> ItemIndex == 0)
			FormGameTeam -> gameModeGameTeam = CLASSIC;
		else if (RadioGroup -> ItemIndex == 1)
			FormGameTeam -> gameModeGameTeam = GOAT;
		FormGameTeam -> pointsAimGameTeam = SpinEdit -> Value;
		FormGameTeam -> ShowModal();
	}
	this -> Close();
}

void __fastcall TFormGameMode::FormShow(TObject *Sender){
	RadioGroup -> ItemIndex = 0;
	SpinEdit -> Value = 100;
}

