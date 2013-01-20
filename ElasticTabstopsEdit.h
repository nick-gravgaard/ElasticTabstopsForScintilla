// Scintilla derived class implementing elastic tabstops

#pragma once

#include "Platform.h"
#include "Scintilla.h"

class ElasticTabstopsEdit : public CWnd
{
	DECLARE_DYNAMIC(ElasticTabstopsEdit)

public:
	void Setup(void);
	void SetText(const char* text);

protected:
	DECLARE_MESSAGE_MAP()

	afx_msg void OnModified(NMHDR*, LRESULT*);
};
