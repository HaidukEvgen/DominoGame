#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
USEFORM("UnitGameMode.cpp", FormGameMode);
USEFORM("UnitGamePC.cpp", FormGamePC);
USEFORM("UnitLog.cpp", FormLog);
USEFORM("UnitMenu.cpp", FormMenu);
USEFORM("UnitGameTeam.cpp", FormGameTeam);
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		TStyleManager::TrySetStyle("Aqua Light Slate");
		Application->CreateForm(__classid(TFormMenu), &FormMenu);
		Application->CreateForm(__classid(TFormGamePC), &FormGamePC);
		Application->CreateForm(__classid(TFormGameMode), &FormGameMode);
		Application->CreateForm(__classid(TFormLog), &FormLog);
		Application->CreateForm(__classid(TFormGameTeam), &FormGameTeam);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
