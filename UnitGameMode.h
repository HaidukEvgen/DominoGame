#pragma once
#ifndef UnitGameModeH
#define UnitGameModeH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Samples.Spin.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.pngimage.hpp>

class TFormGameMode : public TForm
{
__published:
	TSpinEdit *SpinEdit;
	TRadioGroup *RadioGroup;
	TLabel *PointsLabel;
	TButton *PlayButton;
	void __fastcall PlayButtonClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
private:
public:
	__fastcall TFormGameMode(TComponent* Owner);
};
extern PACKAGE TFormGameMode *FormGameMode;

#endif
