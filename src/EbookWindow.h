/* Copyright 2013 the SumatraPDF project authors (see AUTHORS file).
   License: GPLv3 */

#ifndef EbookWindow_h
#define EbookWindow_h

#include "Doc.h"
#include "SumatraWindow.h"
#include "ThreadUtil.h"
#include "UITask.h"
#include "WindowInfo.h"

struct EbookControls;
class  EbookController;

class ThreadLoadEbook : public ThreadBase, public UITask {
    ScopedMem<WCHAR>    fileName;
    EbookController *   controller;
    SumatraWindow       win;
    Doc                 doc;

public:
    ThreadLoadEbook(const WCHAR *fileName, EbookController *controller, const SumatraWindow& sumWin);

    virtual void Run();
    virtual void Execute();
};

namespace mui { class HwndWrapper; }

class EbookWindow {
public:
    EbookWindow() : hwndFrame(NULL), ebookControls(NULL),
        hwndWrapper(NULL), ebookController(NULL) {
        touchState.panStarted = false;
    }
    ~EbookWindow() { }

    HWND                hwndFrame;
    EbookControls *     ebookControls;
    mui::HwndWrapper *  hwndWrapper;
    EbookController *   ebookController;
    TouchState          touchState;
    const WCHAR *       LoadedFilePath() const;
};

EbookWindow* FindEbookWindowByController(EbookController *controller);
void   OpenMobiInWindow(Doc doc, SumatraWindow& winToReplace);
void   RegisterMobiWinClass(HINSTANCE hinst);
void   RebuildMenuBarForEbookWindows();
void   DeleteEbookWindow(EbookWindow *win, bool forceDelete = false);
bool   IsEbookFile(const WCHAR *fileName);
void   RestartLayoutTimer(EbookController *controller);

Doc    GetDocForWindow(SumatraWindow& win);

#endif
