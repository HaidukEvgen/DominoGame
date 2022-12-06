#include <vcl.h>
#pragma hdrstop
#include "UnitMenu.h"
#include "UnitGamePC.h"
#include "UnitGameMode.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormMenu *FormMenu;
extern bool gamePC;
__fastcall TFormMenu::TFormMenu(TComponent* Owner)
	: TForm(Owner)
{

}

void __fastcall TFormMenu::PCModeButtonClick(TObject *Sender)
{
	gamePC = true;
	FormGameMode -> Position = poScreenCenter;
	FormGameMode -> ShowModal();
}

void __fastcall TFormMenu::TeamModeButtonClick(TObject *Sender)
{
	gamePC = false;
	FormGameMode -> Position = poScreenCenter;
	FormGameMode -> ShowModal();
}

void __fastcall TFormMenu::FormCreate(TObject *Sender)
{
	FormMenu -> ControlStyle = FormMenu -> ControlStyle << csOpaque;
}
