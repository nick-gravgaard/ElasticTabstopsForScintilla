# Elastic tabstops for Scintilla

This is an implementation of elastic tabstops for Scintilla.
It was originally based on a port by [David Kinder](http://www.davidkinder.co.uk/) of [my old Gedit implementation](http://nickgravgaard.com/elastic-tabstops/gedit/).

The work consisted of 2 main parts:
* extending Scintilla's API to support explicit tabstop positions
* implementing elastic tabstops using the extended API

## Extending Scintilla's API to support explicit tabstop positions

In August 2014, code from this repo was added to Scintilla's main branch (see [this commit](http://sourceforge.net/p/scintilla/code/ci/3f3ae214c626d7276aee35a14d1ffa1ad848c9cd/)) and released as part of version 3.5.0. 
This makes it possible to set explicit tabstop positions in Scintilla (using SCI_CLEARTABSTOPS, SCI_ADDTABSTOP, and SCI_GETNEXTTABSTOP as [documented here](http://www.scintilla.org/ScintillaDoc.html#TabsAndIndentationGuides)), which is a prerequisite for implementing elastic tabstops.

## Implementing elastic tabstops using the extended API

Most of the interesting code is in [ElasticTabstops.cpp](https://github.com/nickgravgaard/ElasticTabstopsForScintilla/blob/master/ElasticTabstops.cpp).
Currently this is not a very efficient implementation as it rescans the entire buffer every time a change is made, rather than caching everything and only rescanning the parts that have changed.
Unless performance is not an issue, those wishing to reimplement elastic tabstops should find a way to cache cell widths per line.
For a discussion about possible ways to do this in Scintilla see [here](https://groups.google.com/forum/#!topic/scintilla-interest/Z-gSieCdbyM).

Visit http://nickgravgaard.com/elastic-tabstops/ for more information.
