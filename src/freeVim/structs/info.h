/* vi:set ts=8 sts=4 sw=4 ft=objc:
 *
 * VIM - Vi IMproved		by Bram Moolenaar
 *				freeVim, another GUI under windows, by Davy Kuo
 *
 * Do ":help uganda"  in Vim to read copying and usage conditions.
 * Do ":help credits" in Vim to see a list of people who contributed.
 * See README.txt for an overview of the Vim source code.
 */
/*
 * info.h
 *
 * runtime infomations
 */
 
#include <windows.h>

typedef struct{
    int nLeft;
    int nRight;
    int nTop;
    int nBottom;
} dwm_MARGINS;
typedef HRESULT (WINAPI *TDwmExtendFrameIntoClientArea)(HWND, dwm_MARGINS*);
 
struct Info
{
    OSVERSIONINFOEX os_version;
    bool disableAero;
    HINSTANCE dwmapi_lib;
    TDwmExtendFrameIntoClientArea pDwmExtendFrameIntoClientArea;

};
