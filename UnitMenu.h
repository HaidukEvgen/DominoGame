#pragma once
#ifndef UnitMenuH
#define UnitMenuH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>

class TFormMenu : public TForm
{
__published:
	TImage *BackgroundImage;
	TImage *CaptionImage;
	TImage *GamemodeImage;
	TButton *PCModeButton;
	TButton *TeamModeButton;
	void __fastcall PCModeButtonClick(TObject *Sender);
	void __fastcall TeamModeButtonClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
private:
public:
	__fastcall TFormMenu(TComponent* Owner);
};

extern PACKAGE TFormMenu *FormMenu;
#endif
