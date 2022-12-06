#ifndef UnitLogH
#define UnitLogH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>

class TFormLog : public TForm
{
__published:
	TStringGrid *LogSG;
	void __fastcall FormCreate(TObject *Sender);
private:
public:
	__fastcall TFormLog(TComponent* Owner);
    void __fastcall initLogForm(String s);
};

extern PACKAGE TFormLog *FormLog;

#endif
