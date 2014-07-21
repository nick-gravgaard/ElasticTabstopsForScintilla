// Elastic tabstops for Scintilla demo application

#define VC_EXTRALEAN
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501
#undef WINVER
#define WINVER 0x0501
#define NTDDI_VERSION 0x05010300

#include <afxwin.h>

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

		HMODULE hModule = GetModuleHandle(NULL);
		HRSRC hRes = FindResource(hModule, MAKEINTRESOURCE(IDR_TEXTFILE), L"BUFFER_CONTENTS");
		HGLOBAL hMem = LoadResource(hModule, hRes);
		DWORD size = SizeofResource(hModule, hRes);
		char *res_text = (char*)LockResource(hMem);
		char *text = (char*)malloc(size + 1);
		memcpy(text, res_text, size);
		text[size] = 0;
		FreeResource(hMem);

		m_edit.SubclassDlgItem(IDC_EDIT, this);
		m_edit.Setup();
		m_edit.SendMessage(SCI_SETWRAPMODE, 1);
		m_edit.SetText(text);

		return TRUE;
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
