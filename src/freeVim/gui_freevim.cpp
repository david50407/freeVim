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
 * gui_freevim.cpp
 *
 * Hooks for the Vim gui code.  Mainly passes control on to MMBackend.
 */

#ifdef __cplusplus
extern "C" {
#endif
#include "vim.h"

#include "freeVim.h"
#include <Windows.h>

struct Info info;
HWND s_hwnd = NULL;
// -- Initialization --------------------------------------------------------

/*
 * Parse the GUI related command-line arguments.  Any arguments used are
 * deleted from argv, and *argc is decremented accordingly.  This is called
 * when vim is started, whether or not the GUI has been started.
 * NOTE: This function will be called twice if the Vim process forks.
 */
    void
gui_mch_prepare(int *argc, char **argv)
{
    int i = 0;
    while (i < *argc) {
        bool delarg = false;

#ifdef FEAT_NETBEANS_INTG
        if (strncmp(argv[i], "-nb", 3) == 0) {
            // TODO: Can this be used without -f?  If so, should not del arg.
            netbeansArg = argv[i];
            delarg = true;
        }
#endif
        if (strncmp(argv[i], "--noaero", 7) == 0) {
            // Can be used without -f, do not delete from arg list!
            info.disableAero = true;
        }

        if (delarg) {
            // NOTE: See comment above about when to delete arguments!
            --*argc;
            if (*argc > i)
                mch_memmove(&argv[i], &argv[i+1], (*argc-i) * sizeof(char*));
        } else
            ++i;
    }
    
    /* get the OS version info */
    info.os_version.dwOSVersionInfoSize = sizeof(info.os_version);
    GetVersionEx((LPOSVERSIONINFOA)&info.os_version); /* this call works on Win32s, Win95 and WinNT */
    
    info.dwmapi_lib = NULL;
    if (info.os_version.dwMajorVersion >= 6)
        if ((info.dwmapi_lib = vimLoadLib("dwmapi.dll")) != NULL)
        {
            info.pDwmExtendFrameIntoClientArea = (TDwmExtendFrameIntoClientArea)GetProcAddress(info.dwmapi_lib,
							 "DwmExtendFrameIntoClientArea");
        }
}

/*
 * Check if the GUI can be started.  Called before gvimrc is sourced.
 * Return OK or FAIL.
 */
    int
gui_mch_init_check(void)
{
    return OK;
}

/*
 * Initialise the GUI.	Create all the windows, set up all the call-backs
 * etc.
 */
    int
gui_mch_init(void)
{
    return OK;
}

    void
gui_mch_exit(int rc)
{
}

/*
 * Open the GUI window which was created by a call to gui_mch_init().
 */
    int
gui_mch_open(void)
{
    return OK;
}

// -- Updating --------------------------------------------------------------

/*
 * Catch up with any queued events.  This may put keyboard input into the
 * input buffer, call resize call-backs, trigger timers etc.  If there is
 * nothing in the event queue (& no timers pending), then we return
 * immediately.
 */
    void
gui_mch_update(void)
{
}

/*
 * GUI input routine called by gui_wait_for_chars().  Waits for a character
 * from the keyboard.
 *  wtime == -1	    Wait forever.
 *  wtime == 0	    This should never happen.
 *  wtime > 0	    Wait wtime milliseconds for a character.
 * Returns OK if a character was found to be available within the given time,
 * or FAIL otherwise.
 */
    int
gui_mch_wait_for_chars(int wtime)
{
    return OK;
}

// -- Drawing ---------------------------------------------------------------

/* Flush any output to the screen */
    void
gui_mch_flush(void)
{
    // This function is called way too often to be useful as a hint for
    // flushing.  If we were to flush every time it was called the screen would
    // flicker.
}

// -- Drawing -- Removing ---------------------------------------------------

/*
 * Clear the whole text window.
 */
    void
gui_mch_clear_all(void)
{
}

/*
 * Clear a rectangular region of the screen from text pos (row1, col1) to
 * (row2, col2) inclusive.
 */
    void
gui_mch_clear_block(
    int		row1,
    int		col1,
    int		row2,
    int		col2)
{
}

/*
 * Delete the given number of lines from the given row, scrolling up any
 * text further down within the scroll region.
 */
    void
gui_mch_delete_lines(
    int	    row,
    int	    num_lines)
{
}

// -- Drawing -- Adding -----------------------------------------------------

    void
gui_mch_draw_string(
    int		row,
    int		col,
    char_u	*text,
    int		len,
    int		flags)
{
}

/*
 * Insert the given number of lines before the given row, scrolling down any
 * following text within the scroll region.
 */
    void
gui_mch_insert_lines(
    int		row,
    int		num_lines)
{
}

// -- Drawing -- Coloring ---------------------------------------------------

/*
 * Set the current text foreground color.
 */
    void
gui_mch_set_fg_color(guicolor_T color)
{
}

/*
 * Set the current text background color.
 */
    void
gui_mch_set_bg_color(guicolor_T color)
{
}

/*
 * Set the current text special color.
 */
    void
gui_mch_set_sp_color(guicolor_T color)
{
}

/*
 * Set the colors to their default values.
 */
    void
gui_mch_def_colors()
{
}

/*
 * Called when the foreground or background color has been changed.
 */
    void
gui_mch_new_colors(void)
{
    /* nothing to do? */
}

/*
 * Invert a rectangle from row r, column c, for nr rows and nc columns.
 */
    void
gui_mch_invert_rectangle(
    int	    r,
    int	    c,
    int	    nr,
    int	    nc)
{
}

// -- Tabline ---------------------------------------------------------------

/*
 * Set the current tab to "nr".  First tab is 1.
 */
    void
gui_mch_set_curtab(int nr)
{
}

/*
 * Return TRUE when tabline is displayed.
 */
    int
gui_mch_showing_tabline(void)
{
    return TRUE;
}

/*
 * Update the labels of the tabline.
 */
    void
gui_mch_update_tabline(void)
{
}

/*
 * Show or hide the tabline.
 */
    void
gui_mch_show_tabline(int showit)
{
}

// -- Menu ------------------------------------------------------------------

/*
 * Add a sub menu to the menu bar.
 */
    void
gui_mch_add_menu(
    vimmenu_T *menu,
    int pos)
{
}

/*
 * Add a menu item to a menu
 */
    void
gui_mch_add_menu_item(
    vimmenu_T *menu,
    int idx)
{
}

/*
 * Destroy the machine specific menu widget.
 */
    void
gui_mch_destroy_menu(vimmenu_T *menu)
{
}

/*
 * Make a menu either grey or not grey.
 */
    void
gui_mch_menu_grey(
    vimmenu_T *menu,
    int grey)
{
}

/*
 * Make menu item hidden or not hidden
 */
    void
gui_mch_menu_hidden(
    vimmenu_T *menu,
    int hidden)
{
}

    static void
gui_mch_show_popupmenu_at(vimmenu_T *menu, int x, int y)
{
}

/*
 * This is called when user right clicks.
 */
    void
gui_mch_show_popupmenu(vimmenu_T *menu)
{
}

/*
 * This is called when a :popup command is executed.
 */
    void
gui_make_popup(char_u *path_name, int mouse_pos)
{
}

/*
 * This is called after setting all the menus to grey/hidden or not.
 */
    void
gui_mch_draw_menubar(void)
{
}

    void
gui_mch_enable_menu(int flag)
{
}

    void
gui_mch_set_menu_pos(int x, int y, int w, int h)
{
    /* It will be in the right place anyway */
}

    void
gui_mch_show_toolbar(int showit)
{
}

// -- Fonts -----------------------------------------------------------------

/*
 * If a font is not going to be used, free its structure.
 */
    void
gui_mch_free_font(GuiFont font)
{
}

/*
 * Get a font structure for highlighting.
 */
    GuiFont
gui_mch_get_font(char_u *name, int giveErrorIfMissing)
{
    GuiFont	font = NOFONT;
    return font;
}

#if defined(FEAT_EVAL) || defined(PROTO)
/*
 * Return the name of font "font" in allocated memory.
 * Don't know how to get the actual name, thus use the provided name.
 */
    char_u *
gui_mch_get_fontname(GuiFont font, char_u *name)
{
    if (name == NULL)
        return NULL;
    return vim_strsave(name);
}
#endif

/*
 * Initialise vim to use the font with the given name.
 * Return FAIL if the font could not be loaded, OK otherwise.
 */
    int
gui_mch_init_font(char_u *font_name, int fontset)
{
    return OK;
}

/*
 * Set the current text font.
 */
    void
gui_mch_set_font(GuiFont font)
{
}

// -- Scrollbars ------------------------------------------------------------

    void
gui_mch_create_scrollbar(
    scrollbar_T *sb,
    int orient)	/* SBAR_VERT or SBAR_HORIZ */
{
}

    void
gui_mch_destroy_scrollbar(scrollbar_T *sb)
{
}

    void
gui_mch_enable_scrollbar(scrollbar_T *sb, int flag)
{
}

    void
gui_mch_set_scrollbar_pos(scrollbar_T *sb, int x, int y, int w, int h)
{
}

    void
gui_mch_set_scrollbar_thumb(scrollbar_T *sb, long val, long size, long max)
{
}

// -- Cursor ----------------------------------------------------------------

/*
 * Draw a cursor without focus.
 */
    void
gui_mch_draw_hollow_cursor(guicolor_T color)
{
}

/*
 * Draw part of a cursor, "w" pixels wide, and "h" pixels high, using
 * color "color".
 */
    void
gui_mch_draw_part_cursor(int w, int h, guicolor_T color)
{
}

/*
 * Cursor blink functions.
 *
 * This is a simple state machine:
 * BLINK_NONE   not blinking at all
 * BLINK_OFF    blinking, cursor is not shown
 * BLINK_ON     blinking, cursor is shown
 */
    void
gui_mch_set_blinking(long wait, long on, long off)
{
}

/*
 * Start the cursor blinking.  If it was already blinking, this restarts the
 * waiting time and shows the cursor.
 */
    void
gui_mch_start_blink(void)
{
}

/*
 * Stop the cursor blinking.  Show the cursor if it wasn't shown.
 */
    void
gui_mch_stop_blink(void)
{
}

// -- Mouse -----------------------------------------------------------------

/*
 * Get current mouse coordinates in text window.
 */
    void
gui_mch_getmouse(int *x, int *y)
{
}

/*
 * Move mouse pointer to character at (x, y).
 */
    void
gui_mch_setmouse(int x, int y)
{
}

/*
 * Set visibility of the pointer.
 */
    void
gui_mch_mousehide(int hide)
{
}

    void
mch_set_mouse_shape(int shape)
{
}

// -- Input Method ----------------------------------------------------------

/* For global functions we need prototypes. */
#if (defined(FEAT_MBYTE) && defined(FEAT_MBYTE_IME)) || defined(PROTO)

/*
 * set font to IM.
 */
    void
im_set_font(LOGFONT *lf)
{
}

/*
 * Notify cursor position to IM.
 */
    void
im_set_position(int row, int col)
{
}

/*
 * Set IM status on ("active" is TRUE) or off ("active" is FALSE).
 */
    void
im_set_active(int active)
{
}

/*
 * Get IM status.  When IM is on, return not 0.  Else return 0.
 */
    int
im_get_status()
{
    int		status = 0;
    return status;
}

#endif /* FEAT_MBYTE && FEAT_MBYTE_IME */

// -- Find & Replace dialog -------------------------------------------------
    void
gui_mch_find_dialog(exarg_T *eap)
{
}

    void
gui_mch_replace_dialog(exarg_T *eap)
{
}

// -- Unsorted --------------------------------------------------------------

/*
 * Return TRUE if the GUI window is maximized, filling the whole screen.
 */
    int
gui_mch_maximized()
{
    return 0;
}

/*
 * Called when the font changed while the window is maximized.  Compute the
 * new Rows and Columns.  This is like resizing the window.
 */
    void
gui_mch_newfont()
{
}

/*
 * Adjust gui.char_height (after 'linespace' was changed).
 */
    int
gui_mch_adjust_charheight(void)
{
    return 1;
}

    void
gui_mch_beep(void)
{
}

#if defined(FEAT_BROWSE)
    char_u *
gui_mch_browse(
	int saving,
	char_u *title,
	char_u *dflt,
	char_u *ext,
	char_u *initdir,
	char_u *filter)
{
    return NULL;
}
#endif

    int
gui_mch_dialog(
    int		 type,
    char_u	*title,
    char_u	*message,
    char_u	*buttons,
    int		 dfltbutton,
    char_u	*textfield)
{
    return 0;
}

    void
gui_mch_flash(int msec)
{
}

/*
 * Return the Pixel value (color) for the given color name.
 * Return INVALCOLOR for error.
 */
    guicolor_T
gui_mch_get_color(char_u *name)
{
    return INVALCOLOR;
}

/*
 * Return the RGB value of a pixel as a long.
 */
    long_u
gui_mch_get_rgb(guicolor_T pixel)
{
    return (GetRValue(pixel) << 16) + (GetGValue(pixel) << 8)
							   + GetBValue(pixel);
}

    void
gui_mch_get_screen_dimensions(int *screen_w, int *screen_h)
{
}

/*
 * Return OK if the key with the termcap name "name" is supported.
 */
    int
gui_mch_haskey(char_u *name)
{
    return OK;
}

/*
 * Iconify the GUI window.
 */
    void
gui_mch_iconify(void)
{
}

/*
 * Bring the Vim window to the foreground.
 */
    void
gui_mch_set_foreground(void)
{
}

/*
 * Set the size of the window to the given width and height in pixels.
 */
    void
gui_mch_set_shellsize(
    int		width,
    int		height,
    int		min_width,
    int		min_height,
    int		base_width,
    int		base_height,
    int		direction)
{
}

/*
 * Set the position of the top left corner of the window to the given
 * coordinates.
 */
    void
gui_mch_set_winpos(int x, int y)
{
}

/*
 * Get the position of the top left corner of the window.
 */
    int
gui_mch_get_winpos(int *x, int *y)
{
    return OK;
}

    void
gui_mch_set_text_area_pos(int x, int y, int w, int h)
{
}

#ifdef FEAT_TITLE
/*
 * Set the window title and icon.
 * (The icon is not taken care of).
 */
    void
gui_mch_settitle(char_u *title, char_u *icon)
{
}
#endif

    void
gui_mch_enter_fullscreen(int fuoptions_flags, guicolor_T bg)
{
}

    void
gui_mch_leave_fullscreen()
{
}

    void
gui_mch_fuopt_update()
{
}

// -- Graphical Sign Support ------------------------------------------------

#if defined(FEAT_SIGN_ICONS)
    void
gui_mch_drawsign(int row, int col, int typenr)
{
}

    void *
gui_mch_register_sign(char_u *signfile)
{
}

    void
gui_mch_destroy_sign(void *sign)
{
}

#endif // FEAT_SIGN_ICONS


// -- Balloon Eval Support ---------------------------------------------------

#ifdef FEAT_BEVAL

    BalloonEval *
gui_mch_create_beval_area(void *target, char_u *mesg, void (*mesgCB)__ARGS((BalloonEval *, int)), void *clientData)
{
    BalloonEval	*beval;

    beval = (BalloonEval *)calloc(1, sizeof(BalloonEval));
    if (NULL == beval)
        return NULL;

    beval->msg = mesg;
    beval->msgCB = mesgCB;
    beval->clientData = clientData;

    return beval;
}

    void
gui_mch_enable_beval_area(BalloonEval *beval)
{
}

    void
gui_mch_disable_beval_area(BalloonEval *beval)
{
}

/*
 * Show a balloon with "mesg".
 */
    void
gui_mch_post_balloon(BalloonEval *beval, char_u *mesg)
{
}

#endif // FEAT_BEVAL


#ifdef __cplusplus
} /* extern "C" */
#endif