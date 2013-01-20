// Scintilla derived class implementing elastic tabstops

#define VC_EXTRALEAN
#define _WIN32_WINNT 0x0500
#include <afxwin.h>

#include "ElasticTabstopsEdit.h"

// Function that calculates and sets the elastic tabstops
void ElasticTabstops_OnModify(sptr_t edit, int start, int end);

IMPLEMENT_DYNAMIC(ElasticTabstopsEdit, CWnd)

BEGIN_MESSAGE_MAP(ElasticTabstopsEdit, CWnd)
	ON_NOTIFY_REFLECT(SCN_MODIFIED, OnModified)
END_MESSAGE_MAP()

void ElasticTabstopsEdit::Setup(void)
{
	// Listen for changes to the editor's document
	SendMessage(SCI_SETMODEVENTMASK,SC_MOD_INSERTTEXT|SC_MOD_DELETETEXT);
}

void ElasticTabstopsEdit::SetText(const char* text)
{
	// Set the text in the editor
	SendMessage(SCI_SETTEXT,0,(LPARAM)text);
}

void ElasticTabstopsEdit::OnModified(NMHDR* hdr, LRESULT*)
{
	if (hdr->code == SCN_MODIFIED)
	{
		// If text has been added or removed, update the tabstops
		SCNotification* notify = (SCNotification*)hdr;
		if (notify->modificationType & SC_MOD_INSERTTEXT)
		{
			ElasticTabstops_OnModify(SendMessage(SCI_GETDIRECTPOINTER),notify->position,notify->position+notify->length);
		}
		else if (notify->modificationType & SC_MOD_DELETETEXT)
		{
			ElasticTabstops_OnModify(SendMessage(SCI_GETDIRECTPOINTER),notify->position,notify->position);
		}
	}
}
