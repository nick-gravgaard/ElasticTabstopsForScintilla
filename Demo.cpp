// Elastic tabstops for Scintilla demo application

#define VC_EXTRALEAN
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#undef WINVER
#define WINVER 0x0501
#define NTDDI_VERSION 0x05010300

#include <afxwin.h>

#include "SciLexer.h"

#include "ElasticTabstopsEdit.h"
#include "resource.h"

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class DemoDialog : public CDialog
{
public:
	DemoDialog() : CDialog(IDD_TEST_DIALOG)
	{
	}

protected:
	BOOL OnInitDialog()
	{
		CDialog::OnInitDialog();

		m_edit.SubclassDlgItem(IDC_EDIT, this);
		m_edit.Setup();
		m_edit.SendMessage(SCI_SETWRAPMODE, 1);

		HMODULE hModule = GetModuleHandle(NULL);
		HRSRC hRes = FindResource(hModule, MAKEINTRESOURCE(IDR_TEXTFILE), L"BUFFER_CONTENTS");
		HGLOBAL hMem = LoadResource(hModule, hRes);
		DWORD size = SizeofResource(hModule, hRes);
		char *res_text = (char*) LockResource(hMem);
		char *text = (char*) malloc(size + 1);
		memcpy(text, res_text, size);
		text[size] = 0;
		FreeResource(hMem);
		m_edit.SetText(text);
		free(text);

		// set default and C++ comment styles
		m_edit.SendMessage(SCI_STYLESETFONT, STYLE_DEFAULT, reinterpret_cast<LPARAM>("verdana"));
		m_edit.SendMessage(SCI_STYLESETSIZE, STYLE_DEFAULT, 8);
		m_edit.SendMessage(SCI_STYLECLEARALL, 0, 0);
		m_edit.SendMessage(SCI_SETLEXER, SCLEX_CPP);
		m_edit.SendMessage(SCI_STYLESETFONT, SCE_C_COMMENT, reinterpret_cast<LPARAM>("georgia"));
		m_edit.SendMessage(SCI_STYLESETSIZE, SCE_C_COMMENT, 10);
		m_edit.SendMessage(SCI_STYLESETFORE, SCE_C_COMMENT, 0x008000);

		return TRUE;
	}

	void DemoDialog::PostNcDestroy()
	{
		m_edit.CleanUp();
		CDialog::PostNcDestroy();
	}

	ElasticTabstopsEdit m_edit;
};

class DemoApp : public CWinApp
{
public:
	BOOL InitInstance()
	{
		INITCOMMONCONTROLSEX InitCtrls;
		InitCtrls.dwSize = sizeof(InitCtrls);
		InitCtrls.dwICC = ICC_WIN95_CLASSES;
		::InitCommonControlsEx(&InitCtrls);

		CWinApp::InitInstance();

		// Set up Scintilla
		if (Scintilla_RegisterClasses(AfxGetInstanceHandle()))
		{
			// Show the test editor dialog
			DemoDialog dialog;
			dialog.DoModal();
		}
		return FALSE;
	}
};

DemoApp theApp;
