// Elastic tabstops for Scintilla demo application

#define VC_EXTRALEAN
#define _WIN32_WINNT 0x0500
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

		m_edit.SubclassDlgItem(IDC_EDIT,this);
		m_edit.Setup();
		m_edit.SendMessage(SCI_SETWRAPMODE,1);
		m_edit.SetText(
		"/* Hopefully this program should demonstrate how elastic tabstops work.\t*/\n"
		"/* Try inserting and deleting different parts of the text and watch as the tabstops move.\t*/\n"
		"/* If you like this, please ask the writers of your text editor to implement it.\t*/\n"
		"\n"
		"#include <stdio.h>\n"
		"\n"
		"struct ipc_perm\n"
		"{\n"
		"\tkey_t\tkey;\n"
		"\tushort\tuid;\t/* owner euid and egid\t*/\n"
		"\tushort\tgid;\t/* group id\t*/\n"
		"\tushort\tcuid;\t/* creator euid and egid\t*/\n"
		"\tcell-missing\t\t/* for test purposes\t*/\n"
		"\tushort\tmode;\t/* access modes\t*/\n"
		"\tushort\tseq;\t/* sequence number\t*/\n"
		"};\n"
		"\n"
		"int someDemoCode(\tint fred,\n"
		"\tint wilma)\n"
		"{\n"
		"\tx();\t/* try making\t*/\n"
		"\tprintf(\"hello!\\n\");\t/* this comment\t*/\n"
		"\tdoSomethingComplicated();\t/* a bit longer\t*/\n"
		"\tfor (i = start; i < end; ++i)\n"
		"\t{\n"
		"\t\tif (isPrime(i))\n"
		"\t\t{\n"
		"\t\t\t++numPrimes;\n"
		"\t\t}\n"
		"\t}\n"
		"\treturn numPrimes;\n"
		"}\n"
		"\n"
		"---- and now for something completely different: a table ----\n"
		"\n"
		"Title\tAuthor\tPublisher\tYear\n"
		"Generation X\tDouglas Coupland\tAbacus\t1995\n"
		"Informagic\tJean-Pierre Petit\tJohn Murray Ltd\t1982\n"
		"The Cyberiad\tStanislaw Lem\tHarcourt Publishers Ltd\t1985\n"
		"The Selfish Gene\tRichard Dawkins\tOxford University Press\t2006\n");

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
