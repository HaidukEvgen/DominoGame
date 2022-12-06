#include <vcl.h>
#pragma hdrstop
#include "UnitLog.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormLog *FormLog;

__fastcall TFormLog::TFormLog(TComponent* Owner)
	: TForm(Owner)
{
}

void __fastcall TFormLog::FormCreate(TObject *Sender)
{
	initLogForm("Компьютер");
}

void __fastcall TFormLog::initLogForm(String s){
	for (int i = 0; i < LogSG -> RowCount; i++) {
		LogSG -> Cells[0][i] = "";
		LogSG -> Cells[1][i] = "";
	}
	LogSG -> RowCount = 2;
	LogSG -> Cells[0][0] = "Вы";
	LogSG -> Cells[1][0] = s;
}
