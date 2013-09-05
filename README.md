# Elastic tabstops for Scintilla #

This is an implementation of elastic tabstops for Scintilla by [David Kinder](http://www.davidkinder.co.uk/) that was ported from an implementation for Gedit by Nick Gravgaard.

Visit http://nickgravgaard.com/elastic-tabstops/ for more information.

## TODO ##

Before the author of Scintilla will merge these changes into the main codebase some changes need to be made. If anyone has time to do these please feel free. Here's an email where he discusses them:

> There may be uses for explicit tab stops in other cases than elastic tabstops.

> There are a couple of problems with the changes to Scintilla. The main one is that the tab stop positions are held by the document instead of the view, Editor. When there are multiple views on a document, each view may have different visual choices - fonts, sizes and magnification may differ between views so the tab positions will be at different pixel positions. Tab stops should be stored by Editor but it does not have the 'per-line' infrastructure implemented in Document so Editor would need an additional data structure to hold each line's tab stops and code to maintain that when lines are added and deleted.

> Scintilla's external interface is described in include/Scintilla.iface which only allows a few argument types which do not include int\*. A pair of APIs could be used: TabStopsClear(line) and TabStopAdd(line, xStop).

> The elastic tabs implementation calls SCI\_TEXTWIDTH(0, ...) which returns the width measured in style 0. Multiple styles may be used in Scintilla with different widths: for example a monospaced font for identifiers, and a proportional italic font for comments. Measuring only in style 0 may lead to the columns being the wrong width and text appearing in a different column than desired.

> Neil

For the full email see http://permalink.gmane.org/gmane.comp.lib.scintilla.devel/12733

