/*
-------------------------------------------------------------------
 Dinfio Programming Language
 Version: 3.2
-------------------------------------------------------------------
 By: Muhammad Faruq Nuruddinsyah
 Copyright (C) 2014-2026. All Rights Reserved.
-------------------------------------------------------------------
 Platform: Linux, macOS, Windows
-------------------------------------------------------------------
 Module - GUI using wxWidgets
-------------------------------------------------------------------
*/

#include <map>
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/filedlg.h>
#include <wx/dirdlg.h>
#include <wx/clipbrd.h>

#include <sstream>

#include "dinfio_module.h"

#define __GUI_WINDOW__ 1
#define __GUI_PANEL__ 2
#define __GUI_LABELED_PANEL__ 3
#define __GUI_TAB__ 4
#define __GUI_BUTTON__ 5
#define __GUI_LABEL__ 6
#define __GUI_TEXTBOX__ 7
#define __GUI_TEXTAREA__ 8
#define __GUI_RADIOBOX__ 9
#define __GUI_CHECKBOX__ 10
#define __GUI_LISTBOX__ 11
#define __GUI_COMBOBOX__ 12
#define __GUI_TIMER__ 13
#define __GUI_IMAGEBOX__ 14
#define __GUI_STACK__ 15
#define __GUI_GRID__ 16
#define __GUI_MENUBAR__ 17
#define __GUI_MENU__ 18

#define __GUI_EVENT_TAB_CHANGE__ 1
#define __GUI_EVENT_CLICK__ 2
#define __GUI_EVENT_DOUBLE_CLICK__ 3
#define __GUI_EVENT_CHANGE__ 4
#define __GUI_EVENT_ACTIVATE__ 5
#define __GUI_EVENT_DEACTIVATE__ 6
#define __GUI_EVENT_RESIZE__ 7
#define __GUI_EVENT_MINIMIZE__ 8
#define __GUI_EVENT_MAXIMIZE__ 9
#define __GUI_EVENT_CLOSE__ 10
#define __GUI_EVENT_MOUSE_LEFT_UP__ 11
#define __GUI_EVENT_MOUSE_LEFT_DOWN__ 12
#define __GUI_EVENT_MOUSE_RIGHT_UP__ 13
#define __GUI_EVENT_MOUSE_RIGHT_DOWN__ 14
#define __GUI_EVENT_MOUSE_ENTER__ 15
#define __GUI_EVENT_MOUSE_LEAVE__ 16
#define __GUI_EVENT_MOUSE_OVER__ 17
#define __GUI_EVENT_KEY_UP__ 18
#define __GUI_EVENT_KEY_DOWN__ 19

#define __GUI_DRAW_PEN__ 1
#define __GUI_DRAW_BRUSH__ 2
#define __GUI_DRAW_FONT__ 3
#define __GUI_DRAW_LINE__ 4
#define __GUI_DRAW_RECT__ 5
#define __GUI_DRAW_POINT__ 6
#define __GUI_DRAW_CIRCLE__ 7
#define __GUI_DRAW_ELLIPSE__ 8
#define __GUI_DRAW_ARC__ 9
#define __GUI_DRAW_ELLIPTICARC__ 10
#define __GUI_DRAW_POLYGON__ 11
#define __GUI_DRAW_ROUNDEDRECT__ 12
#define __GUI_DRAW_SPLINE__ 13
#define __GUI_DRAW_TEXT__ 14
#define __GUI_DRAW_TEXTCOLOUR__ 15
#define __GUI_DRAW_LINES__ 16
#define __GUI_DRAW_BACKGROUND__ 17
#define __GUI_DRAW_IMAGE_DATA__ 18
#define __GUI_DRAW_IMAGE__ 19

Connector* connector;

uint_fast16_t __gui_start, __gui_messagebox, __gui_keycode;
uint_fast16_t __gui_window, __gui_panel, __gui_labeled_panel, __gui_tab, __gui_button, __gui_label, __gui_textbox, __gui_textarea;
uint_fast16_t __gui_radiobox, __gui_checkbox, __gui_listbox, __gui_combobox, __gui_timer;
uint_fast16_t __gui_stack, __gui_grid, __gui_imagebox;
uint_fast16_t __gui_menubar, __gui_menu;
uint_fast16_t __gui_image_data, __gui_image;

uint_fast16_t __gui_window_show, __gui_window_close, __gui_window_settitle, __gui_window_gettitle;
uint_fast16_t __gui_window_isminimised, __gui_window_ismaximised, __gui_window_setfullscreen, __gui_window_isfullscreen;

uint_fast16_t __gui_tab_addpage, __gui_tab_removepage, __gui_tab_getpage, __gui_tab_setpage;

uint_fast16_t __gui_textbox_appendtext;
uint_fast16_t __gui_textbox_setlocked, __gui_textbox_islocked, __gui_textbox_setmaxlength;
uint_fast16_t __gui_textbox_setsel, __gui_textbox_getselbegin, __gui_textbox_getselend;
uint_fast16_t __gui_textbox_setseltext, __gui_textbox_getseltext;

uint_fast16_t __gui_radiobox_ischecked, __gui_radiobox_setchecked, __gui_checkbox_ischecked, __gui_checkbox_setchecked;

uint_fast16_t __gui_listbox_add, __gui_listbox_remove, __gui_listbox_clear, __gui_listbox_size;
uint_fast16_t __gui_listbox_get, __gui_listbox_set, __gui_listbox_getindex, __gui_listbox_setindex, __gui_listbox_getselections;
uint_fast16_t __gui_combobox_add, __gui_combobox_remove, __gui_combobox_clear, __gui_combobox_size;
uint_fast16_t __gui_combobox_get, __gui_combobox_set, __gui_combobox_getindex, __gui_combobox_setindex;

uint_fast16_t __gui_timer_run, __gui_timer_pause, __gui_timer_isrunning, __gui_timer_setinterval, __gui_timer_getinterval;
uint_fast16_t __gui_colour_rgba, __gui_colour_rgb, __gui_colour_hex;

uint_fast16_t __gui_imagebox_setimage, __gui_imagebox_getimage, __gui_imagebox_setscalemode;
uint_fast16_t __gui_imagebox_getoriginalwidth, __gui_imagebox_getoriginalheight;

uint_fast16_t __gui_image_data_setdata, __gui_image_data_savetofile;

uint_fast16_t __gui_stack_add, __gui_stack_addspacer;
uint_fast16_t __gui_grid_add, __gui_grid_addgrowablecol, __gui_grid_addgrowablerow;

uint_fast16_t __gui_menubar_append, __gui_menubar_insert, __gui_menubar_remove;
uint_fast16_t __gui_menu_append, __gui_menu_appendseparator, __gui_menu_appendsubmenu;
uint_fast16_t __gui_menu_insert, __gui_menu_insertseparator, __gui_menu_insertsubmenu;
uint_fast16_t __gui_menu_remove, __gui_menu_setlabel, __gui_menu_getlabel;
uint_fast16_t __gui_menu_setenable, __gui_menu_isenable;
uint_fast16_t __gui_menu_setchecked, __gui_menu_ischecked;

uint_fast16_t __gui_gettext, __gui_settext, __gui_getx, __gui_gety, __gui_setx, __gui_sety, __gui_getheight, __gui_getwidth;
uint_fast16_t __gui_setheight, __gui_setwidth, __gui_getinnerheight, __gui_getinnerwidth;
uint_fast16_t __gui_setvisible, __gui_isvisible, __gui_setenable, __gui_isenable;
uint_fast16_t __gui_add_event;
uint_fast16_t __gui_getoverx, __gui_getovery;
uint_fast16_t __gui_setbackgroundcolour, __gui_getbackgroundcolour, __gui_setforegroundcolour, __gui_getforegroundcolour;
uint_fast16_t __gui_setfont, __gui_setfontsize, __gui_setfontbold, __gui_setfontlight, __gui_setfontitalic, __gui_setfontunderline, __gui_setfontstrikethrough;
uint_fast16_t __gui_getfont, __gui_getfontsize, __gui_isfontbold, __gui_isfontlight, __gui_isfontitalic, __gui_isfontunderline, __gui_isfontstrikethrough;
uint_fast16_t __gui_setfocus, __gui_settooltip, __gui_gettooltip;
uint_fast16_t __gui_center, __gui_centerhorizontal, __gui_centervertical, __gui_right, __gui_bottom;
uint_fast16_t __gui_stretch, __gui_stretchwidth, __gui_stretchheight;
uint_fast16_t __gui_refresh, __gui_panel_update;

uint_fast16_t __gui_draw_setpen, __gui_draw_setbrush, __gui_draw_setfont, __gui_draw_settextcolour, __gui_draw_setbackgroundcolour;
uint_fast16_t __gui_draw_line, __gui_draw_lines, __gui_draw_rectangle, __gui_draw_point, __gui_draw_circle, __gui_draw_ellipse;
uint_fast16_t __gui_draw_arc, __gui_draw_ellipticarc, __gui_draw_polygon, __gui_draw_roundedrectangle;
uint_fast16_t __gui_draw_spline, __gui_draw_text, __gui_draw_gettextwidth, __gui_draw_gettextheight;
uint_fast16_t __gui_draw_image_data, __gui_draw_image;
uint_fast16_t __gui_draw_clear, __gui_draw_save, __gui_draw_now;

uint_fast16_t __gui_dialog_open, __gui_dialog_save, __gui_dialog_multiple, __gui_dialog_directory;
uint_fast16_t __gui_clipboard_available, __gui_clipboard_get, __gui_clipboard_set, __gui_clipboard_clear;

int __key_code;
int __screen_width, __screen_height, __screen_innerwidth, __screen_innerheight;
double __scale_factor = 1.0, __dpi_factor = 1.0;
bool __factor_set = false;

class GUI_App: public wxApp {
public:
    virtual bool OnInit();
    
    DECLARE_EVENT_TABLE()
    void OnAbout(wxCommandEvent &event);
    void OnPref(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
};

bool GUI_App::OnInit() {
    return true;
}

class GUI: public Base {
public:
    uint_fast8_t __type;
    int __index;
    uint_fast32_t __caller_id;

    wxWindow* __parent;

    AST* __event_click;
    AST* __event_double_click;
    AST* __event_mouse_left_up;
    AST* __event_mouse_left_down;
    AST* __event_mouse_right_up;
    AST* __event_mouse_right_down;
    AST* __event_mouse_enter;
    AST* __event_mouse_leave;
    AST* __event_mouse_over;
    AST* __event_key_up;
    AST* __event_key_down;

    GUI(uint_fast8_t type) {
        __type = type;
        __parent = NULL;
        
        __event_click = NULL;
        __event_double_click = NULL;
        __event_mouse_left_up = NULL;
        __event_mouse_left_down = NULL;
        __event_mouse_right_up = NULL;
        __event_mouse_right_down = NULL;
        __event_mouse_enter = NULL;
        __event_mouse_leave = NULL;
        __event_mouse_over = NULL;
        __event_key_up = NULL;
        __event_key_down = NULL;
    }
};

class GUI_Window: public GUI {
public:
    wxFrame* __holder;
    wxPanel* __panel_holder;

    AST* __event_loaded;
    AST* __event_activated;
    AST* __event_deactivated;
    AST* __event_closed;
    AST* __event_resized;
    AST* __event_minimized;
    AST* __event_maximized;

    GUI_Window(): GUI(__GUI_WINDOW__) {
        __event_loaded = NULL;
        __event_activated = NULL;
        __event_deactivated = NULL;
        __event_closed = NULL;
        __event_resized = NULL;
        __event_minimized = NULL;
        __event_maximized = NULL;
    }
};

class GUI_Stack: public GUI {
public:
    wxBoxSizer* __holder;
    bool __is_vertical;

    GUI_Stack(): GUI(__GUI_STACK__) {
        __is_vertical = true;
    }
};

class GUI_Grid: public GUI {
public:
    wxFlexGridSizer* __holder;

    GUI_Grid(): GUI(__GUI_GRID__) {}
};

class GUI_MenuBar: public GUI {
public:
    wxMenuBar* __holder;

    GUI_MenuBar(): GUI(__GUI_MENUBAR__) {}
};

class GUI_Menu: public GUI {
public:
    wxMenu* __holder;

    GUI_Menu(): GUI(__GUI_MENU__) {}
};

class GUI_ImageData: public Base {
public:
    int __w;
    int __h;
    bool __is_loaded;
    unsigned char* __bytes;
    int __size;

    GUI_ImageData(int w, int h) {
        __w = w;
        __h = h;
        __is_loaded = false;
        __size = 0;
    }
};

class GUI_Image: public Base {
public:
    wxBitmap __bmp;

    GUI_Image() {}
};

class DrawingCommand {
public:
    uint_fast8_t __type;

    DrawingCommand(uint_fast8_t type) {
        __type = type;
    }

    ~DrawingCommand() {}
};

class DrawingPen: public DrawingCommand {
public:
    int __red, __green, __blue, __w, __s;

    DrawingPen(int red, int green, int blue, int w, int s): DrawingCommand(__GUI_DRAW_PEN__) {
        __red = red;
        __green = green;
        __blue = blue;
        __w = w;
        __s = s;
    }
};

class DrawingBrush: public DrawingCommand {
public:
    int __red, __green, __blue, __s;

    DrawingBrush(int red, int green, int blue, int s): DrawingCommand(__GUI_DRAW_BRUSH__) {
        __red = red;
        __green = green;
        __blue = blue;
        __s = s;
    }
};

class DrawingFont: public DrawingCommand {
public:
    string __f;
    bool __b, __i;
    int __s;

    DrawingFont(int s, string f, bool b, bool i): DrawingCommand(__GUI_DRAW_FONT__) {
        __f = f;
        __s = s;
        __b = b;
        __i = i;
    }
};

class DrawingTextColour: public DrawingCommand {
public:
    int __red, __green, __blue;

    DrawingTextColour(int red, int green, int blue): DrawingCommand(__GUI_DRAW_TEXTCOLOUR__) {
        __red = red;
        __green = green;
        __blue = blue;
    }
};

class DrawingBackColour: public DrawingCommand {
public:
    int __red, __green, __blue;

    DrawingBackColour(int red, int green, int blue): DrawingCommand(__GUI_DRAW_BACKGROUND__) {
        __red = red;
        __green = green;
        __blue = blue;
    }
};

class DrawingLine: public DrawingCommand {
public:
    int __x1, __x2, __y1, __y2;

    DrawingLine(int x1, int y1, int x2, int y2): DrawingCommand(__GUI_DRAW_LINE__) {
        __x1 = x1;
        __x2 = x2;
        __y1 = y1;
        __y2 = y2;
    }
};

class DrawingRect: public DrawingCommand {
public:
    int __x, __y, __w, __h;

    DrawingRect(int x, int y, int w, int h): DrawingCommand(__GUI_DRAW_RECT__) {
        __x = x;
        __y = y;
        __w = w;
        __h = h;
    }
};

class DrawingRoundedRect: public DrawingCommand {
public:
    int __x, __y, __w, __h;
    double __r;

    DrawingRoundedRect(int x, int y, int w, int h, double r): DrawingCommand(__GUI_DRAW_ROUNDEDRECT__) {
        __x = x;
        __y = y;
        __w = w;
        __h = h;
        __r = r;
    }
};

class DrawingPoint: public DrawingCommand {
public:
    int __x, __y;

    DrawingPoint(int x, int y): DrawingCommand(__GUI_DRAW_POINT__) {
        __x = x;
        __y = y;
    }
};

class DrawingCircle: public DrawingCommand {
public:
    int __x, __y, __r;

    DrawingCircle(int x, int y, int r): DrawingCommand(__GUI_DRAW_CIRCLE__) {
        __x = x;
        __y = y;
        __r = r;
    }
};

class DrawingEllipse: public DrawingCommand {
public:
    int __x, __y, __w, __h;

    DrawingEllipse(int x, int y, int w, int h): DrawingCommand(__GUI_DRAW_ELLIPSE__) {
        __x = x;
        __y = y;
        __w = w;
        __h = h;
    }
};

class DrawingArc: public DrawingCommand {
public:
    int __xs, __ys, __xe, __ye, __xc, __yc;

    DrawingArc(int xs, int ys, int xe, int ye, int xc, int yc): DrawingCommand(__GUI_DRAW_ARC__) {
        __xs = xs;
        __ys = ys;
        __xe = xe;
        __ye = ye;
        __xc = xc;
        __yc = yc;
    }
};

class DrawingEllipticArc: public DrawingCommand {
public:
    int __x, __y, __w, __h;
    double __s, __e;

    DrawingEllipticArc(int x, int y, int w, int h, double s, double e): DrawingCommand(__GUI_DRAW_ELLIPTICARC__) {
        __x = x;
        __y = y;
        __w = w;
        __h = h;
        __s = s;
        __e = e;
    }
};

struct DrawingPointData {
    int x;
    int y;
};

class DrawingPolygon: public DrawingCommand {
public:
    vector<DrawingPointData> __p;
    int __n, __xo, __yo, __s;

    DrawingPolygon(vector<DrawingPointData> p, int n, int xo, int yo, int s): DrawingCommand(__GUI_DRAW_POLYGON__) {
        __p = p;
        __n = n;
        __xo = xo;
        __yo = yo;
        __s = s;
    }
};

class DrawingSpline: public DrawingCommand {
public:
    vector<DrawingPointData> __p;
    int __n;

    DrawingSpline(vector<DrawingPointData> p, int n): DrawingCommand(__GUI_DRAW_SPLINE__) {
        __p = p;
        __n = n;
    }
};

class DrawingLines: public DrawingCommand {
public:
    vector<DrawingPointData> __p;
    int __n;

    DrawingLines(vector<DrawingPointData> p, int n): DrawingCommand(__GUI_DRAW_LINES__) {
        __p = p;
        __n = n;
    }
};

class DrawingText: public DrawingCommand {
public:
    string __t;
    int __x, __y;
    double __a;

    DrawingText(string t, int x, int y, double a): DrawingCommand(__GUI_DRAW_TEXT__) {
        __t = t;
        __x = x;
        __y = y;
        __a = a;
    }
};

class DrawingImageData: public DrawingCommand {
public:
    int __x, __y, __w, __h;
    bool __use_mask;
    GUI_ImageData* __image_data;

    DrawingImageData(GUI_ImageData* image_data, int x, int y, int w, int h, bool use_mask): DrawingCommand(__GUI_DRAW_IMAGE_DATA__) {
        __image_data = image_data;
        __x = x;
        __y = y;
        __w = w;
        __h = h;
        __use_mask = use_mask;
    }
};

class DrawingImage: public DrawingCommand {
public:
    int __x, __y;
    GUI_Image* __img;

    DrawingImage(GUI_Image* img, int x, int y): DrawingCommand(__GUI_DRAW_IMAGE__) {
        __img = img;
        __x = x;
        __y = y;
    }
};

class GUI_Panel: public GUI {
public:
    wxPanel* __holder;
    bool __canvas_mode;
    vector<DrawingCommand*> __drawing;
    string __current_font_face;
    bool __current_font_bold, __current_font_italic;
    int __current_font_size;

    GUI_Panel(): GUI(__GUI_PANEL__) {
        __current_font_size = 0;
    }
};

class GUI_LabeledPanel: public GUI {
public:
    wxStaticBox* __holder;

    GUI_LabeledPanel(): GUI(__GUI_LABELED_PANEL__) {}
};

class GUI_Tab: public GUI {
public:
    wxNotebook* __holder;

    int __tab_index;
    AST* __event_tab_changed;

    GUI_Tab(): GUI(__GUI_TAB__) {
        __tab_index = 0;
        __event_tab_changed = NULL;
    }
};

class GUI_Button: public GUI {
public:
    wxButton* __holder;

    GUI_Button(): GUI(__GUI_BUTTON__) {}
};

class GUI_Label: public GUI {
public:
    wxStaticText* __holder;

    GUI_Label(): GUI(__GUI_LABEL__) {}
};

class GUI_TextBox: public GUI {
public:
    wxTextCtrl* __holder;

    AST* __event_changed;

    GUI_TextBox(): GUI(__GUI_TEXTBOX__) {
        __event_changed = NULL;
    }
};

class GUI_TextArea: public GUI {
public:
    wxTextCtrl* __holder;

    AST* __event_changed;

    GUI_TextArea(): GUI(__GUI_TEXTAREA__) {
        __event_changed = NULL;
    }
};

class GUI_RadioBox: public GUI {
public:
    wxRadioButton* __holder;

    AST* __event_changed;

    GUI_RadioBox(): GUI(__GUI_RADIOBOX__) {
        __event_changed = NULL;
    }
};

class GUI_CheckBox: public GUI {
public:
    wxCheckBox* __holder;

    AST* __event_changed;

    GUI_CheckBox(): GUI(__GUI_CHECKBOX__) {
        __event_changed = NULL;
    }
};

class GUI_ListBox: public GUI {
public:
    wxListBox* __holder;
    wxWindow* __parent;

    GUI_ListBox(): GUI(__GUI_LISTBOX__) {}
};

class GUI_ComboBox: public GUI {
public:
    wxComboBox* __holder;
    wxChoice* __holder_choice;

    bool __editable;
    AST* __event_changed;

    GUI_ComboBox(bool editable): GUI(__GUI_COMBOBOX__) {
        __editable = editable;
        __event_changed = NULL;
    }
};

class TimerHandler: public wxTimer {
public:
    AST* __event_ticked;
    uint_fast32_t __caller_id;

    TimerHandler(AST* event, uint_fast32_t caller_id): wxTimer() {
        __event_ticked = event;
        __caller_id = caller_id;
    }

    void Notify() {
        connector->__call_function(__event_ticked, __caller_id);
    }
};

class GUI_Timer: public GUI {
public:
    TimerHandler* __holder;
    int __interval;

    GUI_Timer(int interval): GUI(__GUI_TIMER__) {
        __interval = interval;
    }
};

class GUI_ImageBox: public GUI {
public:
    wxStaticBitmap* __holder;
    string __path;
    int __original_width;
    int __original_height;

    GUI_ImageBox(): GUI(__GUI_IMAGEBOX__) {}
};

class GUI_Colour: public Base {
public:
    int __red;
    int __green;
    int __blue;
    int __alpha;

    GUI_Colour(int red, int green, int blue, int alpha) {
        __red = red;
        __green = green;
        __blue = blue;
        __alpha = alpha;
    }
};

unordered_map<int, GUI*> __gui_map;
unordered_map<int, AST*> __menu_action;
unordered_map<int, uint_fast32_t> __menu_action_caller_id;

int __gui_n = 1;
int __menu_n = 1;

wxIMPLEMENT_APP_NO_MAIN(GUI_App);
wxIMPLEMENT_WX_THEME_SUPPORT;

BEGIN_EVENT_TABLE(GUI_App, wxApp)
    EVT_MENU(wxID_ABOUT, GUI_App::OnAbout)
    EVT_MENU(wxID_PREFERENCES, GUI_App::OnPref)
    EVT_MENU(wxID_EXIT, GUI_App::OnExit)
END_EVENT_TABLE()

void __add_constant_double(string name, double value) {
    gc<DataType> d = new_gc<DataType>(__TYPE_DOUBLE__);
    d->__value_double = value;
    connector->__add_constant(name, d);
}

void __add_constant_string(string name, string value) {
    gc<DataType> d = new_gc<DataType>(__TYPE_STRING__);
    d->__value_string = value;
    connector->__add_constant(name, d);
}

gc<DataType> __new_double(double v) {
    gc<DataType> d = new_gc<DataType>(__TYPE_DOUBLE__);
    d->__value_double = v;

    return d;
}

gc<DataType> __new_string(string v) {
    gc<DataType> d = new_gc<DataType>(__TYPE_STRING__);
    d->__value_string = v;

    return d;
}

gc<DataType> __new_colour(int red, int green, int blue, int alpha) {
    gc<DataType> result = connector->__create_object("gui_colour");
    gc<Object> obj = result->__value_object;

    GUI_Colour* c = new GUI_Colour(red, green, blue, alpha);
    obj->__holder_pointer = c;

    return result;
}

gc<DataType> __new_image_data(int w, int h) {
    gc<DataType> result = connector->__create_object("image_data");
    gc<Object> obj = result->__value_object;

    connector->__object_set_function(result, "setdata", __gui_image_data_setdata);
    connector->__object_set_function(result, "savetofile", __gui_image_data_savetofile);

    GUI_ImageData* c = new GUI_ImageData(w, h);
    obj->__holder_pointer = c;

    return result;
}

gc<DataType> __new_image(string filename) {
    gc<DataType> result = connector->__create_object("image");
    gc<Object> obj = result->__value_object;

    GUI_Image* c = new GUI_Image();
    wxBitmap bmp = wxBitmap(filename, wxBITMAP_TYPE_ANY);
    c->__bmp = bmp;

    obj->__holder_pointer = c;

    return result;
}

void __add_constant_event() {
    gc<DataType> d = connector->__create_object("event");

    connector->__object_set_attribute(d, "tabchange", __new_double(__GUI_EVENT_TAB_CHANGE__));
    connector->__object_set_attribute(d, "click", __new_double(__GUI_EVENT_CLICK__));
    connector->__object_set_attribute(d, "doubleclick", __new_double(__GUI_EVENT_DOUBLE_CLICK__));
    connector->__object_set_attribute(d, "change", __new_double(__GUI_EVENT_CHANGE__));
    connector->__object_set_attribute(d, "activate", __new_double(__GUI_EVENT_ACTIVATE__));
    connector->__object_set_attribute(d, "deactivate", __new_double(__GUI_EVENT_DEACTIVATE__));
    connector->__object_set_attribute(d, "resize", __new_double(__GUI_EVENT_RESIZE__));
    connector->__object_set_attribute(d, "minimise", __new_double(__GUI_EVENT_MINIMIZE__));
    connector->__object_set_attribute(d, "maximise", __new_double(__GUI_EVENT_MAXIMIZE__));
    connector->__object_set_attribute(d, "close", __new_double(__GUI_EVENT_CLOSE__));
    connector->__object_set_attribute(d, "mouseleftup", __new_double(__GUI_EVENT_MOUSE_LEFT_UP__));
    connector->__object_set_attribute(d, "mouseleftdown", __new_double(__GUI_EVENT_MOUSE_LEFT_DOWN__));
    connector->__object_set_attribute(d, "mouserightup", __new_double(__GUI_EVENT_MOUSE_RIGHT_UP__));
    connector->__object_set_attribute(d, "mouserightdown", __new_double(__GUI_EVENT_MOUSE_RIGHT_DOWN__));
    connector->__object_set_attribute(d, "mouseenter", __new_double(__GUI_EVENT_MOUSE_ENTER__));
    connector->__object_set_attribute(d, "mouseleave", __new_double(__GUI_EVENT_MOUSE_LEAVE__));
    connector->__object_set_attribute(d, "mouseover", __new_double(__GUI_EVENT_MOUSE_OVER__));
    connector->__object_set_attribute(d, "keyup", __new_double(__GUI_EVENT_KEY_UP__));
    connector->__object_set_attribute(d, "keydown", __new_double(__GUI_EVENT_KEY_DOWN__));

    connector->__add_constant("event", d);
}

void __add_constant_message() {
    gc<DataType> d = connector->__create_object("message");

    connector->__object_set_attribute(d, "ok", __new_double(wxOK));
    connector->__object_set_attribute(d, "yes", __new_double(wxYES));
    connector->__object_set_attribute(d, "no", __new_double(wxNO));
    connector->__object_set_attribute(d, "yesno", __new_double(wxYES_NO));
    connector->__object_set_attribute(d, "cancel", __new_double(wxCANCEL));
    connector->__object_set_attribute(d, "yesnocancel", __new_double(wxYES_NO + wxCANCEL));
    connector->__object_set_attribute(d, "nodefault", __new_double(wxNO_DEFAULT));
    connector->__object_set_attribute(d, "info", __new_double(wxICON_INFORMATION));
    connector->__object_set_attribute(d, "warning", __new_double(wxICON_EXCLAMATION));
    connector->__object_set_attribute(d, "question", __new_double(wxICON_QUESTION));
    connector->__object_set_attribute(d, "error", __new_double(wxICON_ERROR));

    connector->__object_set_function(d, "show", __gui_messagebox);

    connector->__add_constant("message", d);
}

void __add_constant_keycode() {
    gc<DataType> d = connector->__create_object("keycode");

    connector->__object_set_attribute(d, "backspace", __new_double(WXK_BACK));
    connector->__object_set_attribute(d, "tab", __new_double(WXK_TAB));
    connector->__object_set_attribute(d, "return", __new_double(WXK_RETURN));
    connector->__object_set_attribute(d, "escape", __new_double(WXK_ESCAPE));
    connector->__object_set_attribute(d, "space", __new_double(WXK_SPACE));
    connector->__object_set_attribute(d, "delete", __new_double(WXK_DELETE));
    connector->__object_set_attribute(d, "shift", __new_double(WXK_SHIFT));
    connector->__object_set_attribute(d, "alt", __new_double(WXK_ALT));
    connector->__object_set_attribute(d, "control", __new_double(WXK_CONTROL));
    connector->__object_set_attribute(d, "left", __new_double(WXK_LEFT));
    connector->__object_set_attribute(d, "right", __new_double(WXK_RIGHT));
    connector->__object_set_attribute(d, "up", __new_double(WXK_UP));
    connector->__object_set_attribute(d, "down", __new_double(WXK_DOWN));
    connector->__object_set_attribute(d, "f1", __new_double(WXK_F1));
    connector->__object_set_attribute(d, "f2", __new_double(WXK_F2));
    connector->__object_set_attribute(d, "f3", __new_double(WXK_F3));
    connector->__object_set_attribute(d, "f4", __new_double(WXK_F4));
    connector->__object_set_attribute(d, "f5", __new_double(WXK_F5));
    connector->__object_set_attribute(d, "f6", __new_double(WXK_F6));
    connector->__object_set_attribute(d, "f7", __new_double(WXK_F7));
    connector->__object_set_attribute(d, "f8", __new_double(WXK_F8));
    connector->__object_set_attribute(d, "f9", __new_double(WXK_F9));
    connector->__object_set_attribute(d, "f10", __new_double(WXK_F10));
    connector->__object_set_attribute(d, "f11", __new_double(WXK_F11));
    connector->__object_set_attribute(d, "f12", __new_double(WXK_F12));

    connector->__object_set_function(d, "get", __gui_keycode);

    connector->__add_constant("keycode", d);
}

void __add_constant_colour() {
    gc<DataType> d = connector->__create_object("gui_colours");

    connector->__object_set_attribute(d, "red", __new_colour(255, 0, 0, 255));
    connector->__object_set_attribute(d, "green", __new_colour(0, 255, 0, 255));
    connector->__object_set_attribute(d, "blue", __new_colour(0, 0, 255, 255));
    connector->__object_set_attribute(d, "white", __new_colour(255, 255, 255, 255));
    connector->__object_set_attribute(d, "black", __new_colour(0, 0, 0, 255));
    connector->__object_set_attribute(d, "transparent", __new_colour(0, 0, 0, 0));

    connector->__object_set_function(d, "rgba", __gui_colour_rgba);
    connector->__object_set_function(d, "rgb", __gui_colour_rgb);
    connector->__object_set_function(d, "hex", __gui_colour_hex);

    connector->__add_constant("colour", d);
}

void __add_constant_menu() {
    gc<DataType> d = connector->__create_object("menu_type");

    connector->__object_set_attribute(d, "normal", __new_double(wxITEM_NORMAL));
    connector->__object_set_attribute(d, "check", __new_double(wxITEM_CHECK));
    connector->__object_set_attribute(d, "radio", __new_double(wxITEM_RADIO));
    connector->__object_set_attribute(d, "exit", __new_double(wxID_EXIT));
    connector->__object_set_attribute(d, "about", __new_double(wxID_ABOUT));
    connector->__object_set_attribute(d, "preferences", __new_double(wxID_PREFERENCES));

    connector->__add_constant("menu", d);
}

void __add_constant_stack() {
    connector->__add_constant("vertical", __new_double(0));
    connector->__add_constant("horizontal", __new_double(1));
}

void __add_constant_alignment() {
    gc<DataType> d = connector->__create_object("alignment");

    connector->__object_set_attribute(d, "left", __new_double(wxALIGN_LEFT));
    connector->__object_set_attribute(d, "right", __new_double(wxALIGN_RIGHT));
    connector->__object_set_attribute(d, "centre", __new_double(wxALIGN_CENTER));
    connector->__object_set_attribute(d, "top", __new_double(wxALIGN_TOP));
    connector->__object_set_attribute(d, "bottom", __new_double(wxALIGN_BOTTOM));
    connector->__object_set_attribute(d, "centre_horizontal", __new_double(wxALIGN_CENTER_HORIZONTAL));
    connector->__object_set_attribute(d, "centre_vertical", __new_double(wxALIGN_CENTER_VERTICAL));

    connector->__add_constant("align", d);
}

void __add_constant_padding() {
    gc<DataType> d = connector->__create_object("padding");

    connector->__object_set_attribute(d, "left", __new_double(wxLEFT));
    connector->__object_set_attribute(d, "right", __new_double(wxRIGHT));
    connector->__object_set_attribute(d, "top", __new_double(wxTOP));
    connector->__object_set_attribute(d, "bottom", __new_double(wxBOTTOM));
    connector->__object_set_attribute(d, "all", __new_double(wxALL));

    connector->__add_constant("padding", d);
}

void __add_constant_scale_mode() {
    gc<DataType> d = connector->__create_object("scale_mode");
    
    #ifndef __RPI__
        connector->__object_set_attribute(d, "none", __new_double(wxStaticBitmapBase::Scale_None));
        connector->__object_set_attribute(d, "fill", __new_double(wxStaticBitmapBase::Scale_Fill));
        connector->__object_set_attribute(d, "aspectfit", __new_double(wxStaticBitmapBase::Scale_AspectFit));
        connector->__object_set_attribute(d, "aspectfill", __new_double(wxStaticBitmapBase::Scale_AspectFill));
    #else
        connector->__object_set_attribute(d, "none", __new_double(-1));
        connector->__object_set_attribute(d, "fill", __new_double(-1));
        connector->__object_set_attribute(d, "aspectfit", __new_double(-1));
        connector->__object_set_attribute(d, "aspectfill", __new_double(-1));
    #endif
    
    connector->__add_constant("scale", d);
}

void __add_constant_pen_style() {
    gc<DataType> d = connector->__create_object("pen_style");

    connector->__object_set_attribute(d, "solid", __new_double(0));
    connector->__object_set_attribute(d, "dot", __new_double(1));
    connector->__object_set_attribute(d, "dash", __new_double(2));
    connector->__object_set_attribute(d, "shortdash", __new_double(3));
    connector->__object_set_attribute(d, "dotdash", __new_double(4));

    connector->__add_constant("pen", d);
}

void __add_constant_brush_style() {
    gc<DataType> d = connector->__create_object("brush_style");

    connector->__object_set_attribute(d, "solid", __new_double(0));
    connector->__object_set_attribute(d, "bdiagonal", __new_double(1));
    connector->__object_set_attribute(d, "cdiagonal", __new_double(2));
    connector->__object_set_attribute(d, "fdiagonal", __new_double(3));
    connector->__object_set_attribute(d, "cross", __new_double(4));
    connector->__object_set_attribute(d, "horizontal", __new_double(5));
    connector->__object_set_attribute(d, "vertical", __new_double(6));
    connector->__object_set_attribute(d, "transparent", __new_double(7));

    connector->__add_constant("brush", d);
}

void __add_constant_image_type() {
    gc<DataType> d = connector->__create_object("image_type");

    connector->__object_set_attribute(d, "jpeg", __new_double(0));
    connector->__object_set_attribute(d, "png", __new_double(1));

    connector->__add_constant("image_type", d);
}

void __add_constant_dialog() {
    gc<DataType> d = connector->__create_object("dialog");

    connector->__object_set_function(d, "open", __gui_dialog_open);
    connector->__object_set_function(d, "save", __gui_dialog_save);
    connector->__object_set_function(d, "open_multiple", __gui_dialog_multiple);
    connector->__object_set_function(d, "directory", __gui_dialog_directory);

    connector->__add_constant("dialog", d);
}

void __add_constant_clipboard() {
    gc<DataType> d = connector->__create_object("clipboard");

    connector->__object_set_function(d, "available", __gui_clipboard_available);
    connector->__object_set_function(d, "get", __gui_clipboard_get);
    connector->__object_set_function(d, "set", __gui_clipboard_set);
    connector->__object_set_function(d, "clear", __gui_clipboard_clear);

    connector->__add_constant("clipboard", d);
}

extern "C" Module* create_module() {
    return new Module();
}

extern "C" void destroy_module(Module* object) {
    delete object;
}

void Module::__init(Connector* c) {
    connector = c;


    // Register functions

    __gui_messagebox = connector->__register_function("messagebox");
    __gui_keycode = connector->__register_function("getkeycode");

    __gui_window = connector->__register_function("gui_window");

    __gui_menubar = connector->__register_function("gui_menubar");
    __gui_menu = connector->__register_function("gui_menu");
    __gui_stack = connector->__register_function("gui_stack");
    __gui_grid = connector->__register_function("gui_grid");

    __gui_panel = connector->__register_function("gui_panel");
    __gui_labeled_panel = connector->__register_function("gui_labeled_panel");
    __gui_tab = connector->__register_function("gui_tab");
    __gui_button = connector->__register_function("gui_button");
    __gui_label = connector->__register_function("gui_label");
    __gui_textbox = connector->__register_function("gui_textbox");
    __gui_textarea = connector->__register_function("gui_textarea");
    __gui_radiobox = connector->__register_function("gui_radiobox");
    __gui_checkbox = connector->__register_function("gui_checkbox");
    __gui_listbox = connector->__register_function("gui_listbox");
    __gui_combobox = connector->__register_function("gui_combobox");
    __gui_timer = connector->__register_function("gui_timer");
    __gui_imagebox = connector->__register_function("gui_imagebox");

    __gui_image_data = connector->__register_function("image_data");
    __gui_image = connector->__register_function("image");

    __gui_colour_rgba = connector->__register_function("gui_colours::rgba");
    __gui_colour_rgb = connector->__register_function("gui_colours::rgb");
    __gui_colour_hex = connector->__register_function("gui_colours::hex");

    __gui_image_data_setdata = connector->__register_function("image_data::setdata");
    __gui_image_data_savetofile = connector->__register_function("image_data::savetofile");

    __gui_window_show = connector->__register_function("gui_window::show");
    __gui_window_close = connector->__register_function("gui_window::close");
    __gui_window_settitle = connector->__register_function("gui_window::settitle");
    __gui_window_gettitle = connector->__register_function("gui_window::gettitle");
    __gui_window_isminimised = connector->__register_function("gui_window::isminimised");
    __gui_window_ismaximised = connector->__register_function("gui_window::ismaximised");
    __gui_window_setfullscreen = connector->__register_function("gui_window::setfullscreen");
    __gui_window_isfullscreen = connector->__register_function("gui_window::isfullscreen");

    __gui_menubar_append = connector->__register_function("gui_menubar::append");
    __gui_menubar_insert = connector->__register_function("gui_menubar::insert");
    __gui_menubar_remove = connector->__register_function("gui_menubar::remove");
    
    __gui_menu_append = connector->__register_function("gui_menu::append");
    __gui_menu_appendseparator = connector->__register_function("gui_menu::appendseparator");
    __gui_menu_appendsubmenu = connector->__register_function("gui_menu::appendsubmenu");
    __gui_menu_insert = connector->__register_function("gui_menu::insert");
    __gui_menu_insertseparator = connector->__register_function("gui_menu::insertseparator");
    __gui_menu_insertsubmenu = connector->__register_function("gui_menu::insertsubmenu");
    __gui_menu_remove = connector->__register_function("gui_menu::remove");
    __gui_menu_setlabel = connector->__register_function("gui_menu::setlabel");
    __gui_menu_getlabel = connector->__register_function("gui_menu::getlabel");
    __gui_menu_setenable = connector->__register_function("gui_menu::setenable");
    __gui_menu_isenable = connector->__register_function("gui_menu::isenable");
    __gui_menu_setchecked = connector->__register_function("gui_menu::setchecked");
    __gui_menu_ischecked = connector->__register_function("gui_menu::ischecked");

    __gui_tab_addpage = connector->__register_function("gui_tab::addpage");
    __gui_tab_removepage = connector->__register_function("gui_tab::removepage");
    __gui_tab_getpage = connector->__register_function("gui_tab::getpage");
    __gui_tab_setpage = connector->__register_function("gui_tab::setpage");

    __gui_textbox_appendtext = connector->__register_function("gui_textbox::appendtext");
    __gui_textbox_setlocked = connector->__register_function("gui_textbox::setlocked");
    __gui_textbox_islocked = connector->__register_function("gui_textbox::islocked");
    __gui_textbox_setmaxlength = connector->__register_function("gui_textbox::setmaxlength");
    __gui_textbox_setsel = connector->__register_function("gui_textbox::setsel");
    __gui_textbox_getselbegin = connector->__register_function("gui_textbox::getselbegin");
    __gui_textbox_getselend = connector->__register_function("gui_textbox::getselend");
    __gui_textbox_setseltext = connector->__register_function("gui_textbox::setseltext");
    __gui_textbox_getseltext = connector->__register_function("gui_textbox::getseltext");

    __gui_radiobox_ischecked = connector->__register_function("gui_radiobox::ischecked");
    __gui_radiobox_setchecked = connector->__register_function("gui_radiobox::setchecked");
    __gui_checkbox_ischecked = connector->__register_function("gui_checkbox::ischecked");
    __gui_checkbox_setchecked = connector->__register_function("gui_checkbox::setchecked");

    __gui_listbox_add = connector->__register_function("gui_listbox::add");
    __gui_listbox_remove = connector->__register_function("gui_listbox::remove");
    __gui_listbox_clear = connector->__register_function("gui_listbox::clear");
    __gui_listbox_size = connector->__register_function("gui_listbox::size");
    __gui_listbox_get = connector->__register_function("gui_listbox::get");
    __gui_listbox_set = connector->__register_function("gui_listbox::set");
    __gui_listbox_getindex = connector->__register_function("gui_listbox::getindex");
    __gui_listbox_setindex = connector->__register_function("gui_listbox::setindex");
    __gui_listbox_getselections = connector->__register_function("gui_listbox::getselections");

    __gui_combobox_add = connector->__register_function("gui_combobox::add");
    __gui_combobox_remove = connector->__register_function("gui_combobox::remove");
    __gui_combobox_clear = connector->__register_function("gui_combobox::clear");
    __gui_combobox_size = connector->__register_function("gui_combobox::size");
    __gui_combobox_get = connector->__register_function("gui_combobox::get");
    __gui_combobox_set = connector->__register_function("gui_combobox::set");
    __gui_combobox_getindex = connector->__register_function("gui_combobox::getindex");
    __gui_combobox_setindex = connector->__register_function("gui_combobox::setindex");

    __gui_timer_run = connector->__register_function("gui_timer::run");
    __gui_timer_pause = connector->__register_function("gui_timer::pause");
    __gui_timer_isrunning = connector->__register_function("gui_timer::isrunning");
    __gui_timer_getinterval = connector->__register_function("gui_timer::getinterval");
    __gui_timer_setinterval = connector->__register_function("gui_timer::setinterval");

    __gui_stack_add = connector->__register_function("gui_stack::add");
    __gui_stack_addspacer = connector->__register_function("gui_stack::addspacer");
    __gui_grid_add = connector->__register_function("gui_grid::add");
    __gui_grid_addgrowablecol = connector->__register_function("gui_grid::addgrowablecol");
    __gui_grid_addgrowablerow = connector->__register_function("gui_grid::addgrowablerow");

    __gui_imagebox_getimage = connector->__register_function("gui_imagebox::getimage");
    __gui_imagebox_setimage = connector->__register_function("gui_imagebox::setimage");
    __gui_imagebox_setscalemode = connector->__register_function("gui_imagebox::setscalemode");
    __gui_imagebox_getoriginalwidth = connector->__register_function("gui_imagebox::getoriginalwidth");
    __gui_imagebox_getoriginalheight = connector->__register_function("gui_imagebox::getoriginalheight");

    __gui_gettext = connector->__register_function("gui::gettext");
    __gui_settext = connector->__register_function("gui::settext");
    __gui_getoverx = connector->__register_function("gui::getoverx");
    __gui_getovery = connector->__register_function("gui::getovery");
    __gui_getx = connector->__register_function("gui::getx");
    __gui_gety = connector->__register_function("gui::gety");
    __gui_setx = connector->__register_function("gui::setx");
    __gui_sety = connector->__register_function("gui::sety");
    __gui_getheight = connector->__register_function("gui::getheight");
    __gui_getwidth = connector->__register_function("gui::getwidth");
    __gui_setheight = connector->__register_function("gui::setheight");
    __gui_setwidth = connector->__register_function("gui::setwidth");
    __gui_getinnerheight = connector->__register_function("gui::getinnerheight");
    __gui_getinnerwidth = connector->__register_function("gui::getinnerwidth");

    __gui_setvisible = connector->__register_function("gui::setvisible");
    __gui_isvisible = connector->__register_function("gui::isvisible");
    __gui_setenable = connector->__register_function("gui::setenable");
    __gui_isenable = connector->__register_function("gui::isenable");

    __gui_setbackgroundcolour = connector->__register_function("gui::setbackgroundcolour");
    __gui_getbackgroundcolour = connector->__register_function("gui::getbackgroundcolour");
    __gui_setforegroundcolour = connector->__register_function("gui::setforegroundcolour");
    __gui_getforegroundcolour = connector->__register_function("gui::getforegroundcolour");

    __gui_setfont = connector->__register_function("gui::setfont");
    __gui_setfontsize = connector->__register_function("gui::setfontsize");
    __gui_setfontbold = connector->__register_function("gui::setfontbold");
    __gui_setfontlight = connector->__register_function("gui::setfontlight");
    __gui_setfontitalic = connector->__register_function("gui::setfontitalic");
    __gui_setfontunderline = connector->__register_function("gui::setfontunderline");
    __gui_setfontstrikethrough = connector->__register_function("gui::setfontstrikethrough");
    __gui_getfont = connector->__register_function("gui::getfont");
    __gui_getfontsize = connector->__register_function("gui::getfontsize");
    __gui_isfontbold = connector->__register_function("gui::isfontbold");
    __gui_isfontlight = connector->__register_function("gui::isfontlight");
    __gui_isfontitalic = connector->__register_function("gui::isfontitalic");
    __gui_isfontunderline = connector->__register_function("gui::isfontunderline");
    __gui_isfontstrikethrough = connector->__register_function("gui::isfontstrikethrough");

    __gui_setfocus = connector->__register_function("gui::setfocus");
    __gui_settooltip = connector->__register_function("gui::settooltip");
    __gui_gettooltip = connector->__register_function("gui::gettooltip");

    __gui_center = connector->__register_function("gui::center");
    __gui_centerhorizontal = connector->__register_function("gui::centerhorizontal");
    __gui_centervertical = connector->__register_function("gui::centervertical");
    __gui_right = connector->__register_function("gui::right");
    __gui_bottom = connector->__register_function("gui::bottom");
    __gui_stretch = connector->__register_function("gui::stretch");
    __gui_stretchwidth = connector->__register_function("gui::stretchwidth");
    __gui_stretchheight = connector->__register_function("gui::stretchheight");

    __gui_refresh = connector->__register_function("gui::refresh");
    __gui_panel_update = connector->__register_function("gui_panel::update");

    __gui_draw_setpen = connector->__register_function("gui_panel::draw_setpen");
    __gui_draw_setbrush = connector->__register_function("gui_panel::draw_setbrush");
    __gui_draw_setfont = connector->__register_function("gui_panel::draw_setfont");
    __gui_draw_settextcolour = connector->__register_function("gui_panel::draw_settextcolour");
    __gui_draw_setbackgroundcolour = connector->__register_function("gui_panel::draw_setbackgroundcolour");
    __gui_draw_line = connector->__register_function("gui_panel::draw_line");
    __gui_draw_lines = connector->__register_function("gui_panel::draw_lines");
    __gui_draw_rectangle = connector->__register_function("gui_panel::draw_rectangle");
    __gui_draw_point = connector->__register_function("gui_panel::draw_point");
    __gui_draw_circle = connector->__register_function("gui_panel::draw_circle");
    __gui_draw_ellipse = connector->__register_function("gui_panel::draw_ellipse");
    __gui_draw_arc = connector->__register_function("gui_panel::draw_arc");
    __gui_draw_ellipticarc = connector->__register_function("gui_panel::draw_ellipticarc");
    __gui_draw_polygon = connector->__register_function("gui_panel::draw_polygon");
    __gui_draw_roundedrectangle = connector->__register_function("gui_panel::draw_roundedrectangle");
    __gui_draw_spline = connector->__register_function("gui_panel::draw_spline");
    __gui_draw_text = connector->__register_function("gui_panel::draw_text");
    __gui_draw_image_data = connector->__register_function("gui_panel::draw_image_data");
    __gui_draw_image = connector->__register_function("gui_panel::draw_image");
    __gui_draw_gettextwidth = connector->__register_function("gui_panel::draw_gettextwidth");
    __gui_draw_gettextheight = connector->__register_function("gui_panel::draw_gettextheight");
    __gui_draw_clear = connector->__register_function("gui_panel::draw_clear");
    __gui_draw_save = connector->__register_function("gui_panel::draw_save");
    __gui_draw_now = connector->__register_function("gui_panel::draw_now");

    __gui_dialog_open = connector->__register_function("dialog::open");
    __gui_dialog_save = connector->__register_function("dialog::save");
    __gui_dialog_multiple = connector->__register_function("dialog::open_multiple");
    __gui_dialog_directory = connector->__register_function("dialog::directory");

    __gui_clipboard_available = connector->__register_function("clipboard::available");
    __gui_clipboard_get = connector->__register_function("clipboard::get");
    __gui_clipboard_set = connector->__register_function("clipboard::set");
    __gui_clipboard_clear = connector->__register_function("clipboard::clear");

    __gui_add_event = connector->__register_function("gui::addevent");
    __gui_start = 1;   // It's special, called directly from main


    // Set function addresses boundary

    __min = __gui_messagebox;
    __max = __gui_add_event;   // DO NOT FORGET THIS!


    // Add constants

    __add_constant_message();
    __add_constant_event();
    __add_constant_keycode();
    __add_constant_colour();
    __add_constant_menu();
    __add_constant_stack();
    __add_constant_alignment();
    __add_constant_padding();
    __add_constant_scale_mode();
    __add_constant_pen_style();
    __add_constant_brush_style();
    __add_constant_image_type();
    __add_constant_dialog();
    __add_constant_clipboard();


    // Initialise GUI

    int argc = 0;
    char* argv[] = {0};
    
    wxEntryStart(argc, argv);
    wxInitAllImageHandlers();

    wxTheApp->CallOnInit();
}


// For now __event_gui_window_load is not used yet

void __event_gui_window_load(int id) {
    GUI_Window* g = (GUI_Window*) __gui_map[id];

    AST* f = g->__event_loaded;
    if (f == NULL) {
        return;
    }

    connector->__call_function(f, g->__caller_id);
}

void __event_gui_window_activate(wxActivateEvent &event) {
    int id = event.GetId();
    GUI_Window* g = (GUI_Window*) __gui_map[id];
    AST* f;

    if (event.GetActive()) {
        f = g->__event_activated;
        if (f == NULL) {
            event.Skip();
            return;
        }
    } else {
        f = g->__event_deactivated;
        if (f == NULL) {
            event.Skip();
            return;
        }
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_window_close(wxCloseEvent &event) {
    int id = event.GetId();
    GUI_Window* g = (GUI_Window*) __gui_map[id];

    AST* f = g->__event_closed;
    if (f == NULL) {
        g->__holder->Destroy();
        event.Skip();
        return;
    }

    gc<DataType> d = connector->__get_value(f, g->__caller_id);

    if (d->__value_bool == true) {
        g->__holder->Destroy();
        event.Skip();
    }
}

void __event_gui_window_resize(wxSizeEvent &event) {
    int id = event.GetId();
    GUI_Window* g = (GUI_Window*) __gui_map[id];

    AST* f = g->__event_resized;
    if (f == NULL) {
        event.Skip();
        return;
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_window_minimize(wxIconizeEvent &event) {
    int id = event.GetId();
    GUI_Window* g = (GUI_Window*) __gui_map[id];

    AST* f = g->__event_minimized;
    if (f == NULL) {
        event.Skip();
        return;
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_window_maximize(wxMaximizeEvent &event) {
    int id = event.GetId();
    GUI_Window* g = (GUI_Window*) __gui_map[id];

    AST* f = g->__event_maximized;
    if (f == NULL) {
        event.Skip();
        return;
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_menu(wxCommandEvent &event) {
    int id = event.GetId();

    if (__menu_action.find(id) == __menu_action.end()) {
        event.Skip();
        return;
    }

    AST* f = __menu_action[id];
    uint_fast32_t caller_id = __menu_action_caller_id[id];

    connector->__call_function(f, caller_id);
    event.Skip();
}

void GUI_App::OnAbout(wxCommandEvent &event) {
    int id = event.GetId();

    if (__menu_action.find(id) == __menu_action.end()) {
        event.Skip();
        return;
    }

    AST* f = __menu_action[id];
    uint_fast32_t caller_id = __menu_action_caller_id[id];

    connector->__call_function(f, caller_id);
    event.Skip();
}

void GUI_App::OnPref(wxCommandEvent &event) {
    int id = event.GetId();

    if (__menu_action.find(id) == __menu_action.end()) {
        event.Skip();
        return;
    }

    AST* f = __menu_action[id];
    uint_fast32_t caller_id = __menu_action_caller_id[id];

    connector->__call_function(f, caller_id);
    event.Skip();
}

void GUI_App::OnExit(wxCommandEvent &event) {
    int id = event.GetId();

    if (__menu_action.find(id) == __menu_action.end()) {
        event.Skip();
        return;
    }

    AST* f = __menu_action[id];
    uint_fast32_t caller_id = __menu_action_caller_id[id];

    connector->__call_function(f, caller_id);
}

void __event_gui_tab(wxBookCtrlEvent &event) {
    int id = event.GetId();
    GUI* g = __gui_map[id];

    if (g == NULL) {
        event.Skip();
        return;
    }

    GUI_Tab* t = (GUI_Tab*) g;
    AST* f = t->__event_tab_changed;
    t->__tab_index = event.GetSelection();

    if (f == NULL) {
        event.Skip();
        return;
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_command(wxCommandEvent &event) {
    int id = event.GetId();
    GUI* g = __gui_map[id];

    AST* f = g->__event_click;
    if (f == NULL) return;

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_text(wxCommandEvent &event) {
    int id = event.GetId();
    GUI_TextBox* g = (GUI_TextBox*) __gui_map[id];

    AST* f = g->__event_changed;
    if (f == NULL) return;

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_textarea(wxCommandEvent &event) {
    int id = event.GetId();
    GUI_TextArea* g = (GUI_TextArea*) __gui_map[id];

    AST* f = g->__event_changed;
    if (f == NULL) return;

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_radiobox(wxCommandEvent &event) {
    int id = event.GetId();
    GUI_RadioBox* g = (GUI_RadioBox*) __gui_map[id];

    AST* f = g->__event_changed;
    if (f == NULL) return;

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_checkbox(wxCommandEvent &event) {
    int id = event.GetId();
    GUI_CheckBox* g = (GUI_CheckBox*) __gui_map[id];

    AST* f = g->__event_changed;
    if (f == NULL) return;

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_listbox_click(wxCommandEvent &event) {
    int id = event.GetId();
    GUI* g = __gui_map[id];

    GUI_ListBox* l = (GUI_ListBox*) g;

    AST* f = g->__event_click;
    if (f == NULL) {
        event.Skip();
        return;
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_listbox_double_click(wxCommandEvent &event) {
    int id = event.GetId();
    GUI* g = __gui_map[id];

    AST* f = g->__event_double_click;
    if (f == NULL) {
        event.Skip();
        return;
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_combobox_click(wxCommandEvent &event) {
    int id = event.GetId();
    GUI* g = __gui_map[id];

    AST* f = g->__event_click;
    if (f == NULL) {
        event.Skip();
        return;
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_combobox_change(wxCommandEvent &event) {
    int id = event.GetId();
    GUI_ComboBox* g = (GUI_ComboBox*) __gui_map[id];

    AST* f = g->__event_changed;
    if (f == NULL) {
        event.Skip();
        return;
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_mouse(wxMouseEvent &event) {
    int id = event.GetId();
    GUI* g = __gui_map[id];
    AST* f;
    wxEventType t = event.GetEventType();

    if (g == NULL){
        event.Skip();
        return;
    }

    if (t == wxEVT_MOTION) {
        f = g->__event_mouse_over;
        if (f == NULL){
            event.Skip();
            return;
        }
    } else if (t == wxEVT_LEFT_UP) {
        f = g->__event_mouse_left_up;
        if (f == NULL){
            event.Skip();
            return;
        }
    } else if (t == wxEVT_LEFT_DOWN) {
        f = g->__event_mouse_left_down;
        if (f == NULL){
            event.Skip();
            return;
        }
    } else if (t == wxEVT_RIGHT_UP) {
        f = g->__event_mouse_right_up;
        if (f == NULL){
            event.Skip();
            return;
        }
    } else if (t == wxEVT_RIGHT_DOWN) {
        f = g->__event_mouse_right_down;
        if (f == NULL){
            event.Skip();
            return;
        }
    } else if (t == wxEVT_ENTER_WINDOW) {
        f = g->__event_mouse_enter;
        if (f == NULL){
            event.Skip();
            return;
        }
    } else if (t == wxEVT_LEAVE_WINDOW) {
        f = g->__event_mouse_leave;
        if (f == NULL){
            event.Skip();
            return;
        }
    } else {
        event.Skip();
        return;
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}

void __event_gui_key(wxKeyEvent &event) {
    int id = event.GetId();
    GUI* g = __gui_map[id];
    AST* f;
    wxEventType t = event.GetEventType();

    if (g == NULL){
        event.Skip();
        return;
    }

    if (t == wxEVT_KEY_UP) {
        f = g->__event_key_up;

        if (f == NULL){
            event.Skip();
            return;
        }

        __key_code = event.GetKeyCode();
    } else if (t == wxEVT_KEY_DOWN) {
        f = g->__event_key_down;

        if (f == NULL){
            event.Skip();
            return;
        }

        __key_code = event.GetKeyCode();
    } else {
        event.Skip();
        return;
    }

    connector->__call_function(f, g->__caller_id);
    event.Skip();
}


// Drawing renderer

void __panel_render(wxDC& dc, GUI_Panel* gui) {
    wxPen pen(*wxBLACK, 1);
    dc.SetPen(pen);
    dc.SetBrush(*wxTRANSPARENT_BRUSH);
    
    for (int i = 0; i < gui->__drawing.size(); i++) {
        DrawingCommand* d = gui->__drawing.at(i);

        if (d->__type == __GUI_DRAW_PEN__) {
            DrawingPen* dd = (DrawingPen*) d;
            int s = dd->__s;

            if (s == 0) {
                wxPen pen(wxColour(dd->__red, dd->__green, dd->__blue), dd->__w, wxPENSTYLE_SOLID);
                dc.SetPen(pen);
            } else if (s == 1) {
                wxPen pen(wxColour(dd->__red, dd->__green, dd->__blue), dd->__w, wxPENSTYLE_DOT);
                dc.SetPen(pen);
            } else if (s == 2) {
                wxPen pen(wxColour(dd->__red, dd->__green, dd->__blue), dd->__w, wxPENSTYLE_LONG_DASH);
                dc.SetPen(pen);
            } else if (s == 3) {
                wxPen pen(wxColour(dd->__red, dd->__green, dd->__blue), dd->__w, wxPENSTYLE_SHORT_DASH);
                dc.SetPen(pen);
            } else if (s == 4) {
                wxPen pen(wxColour(dd->__red, dd->__green, dd->__blue), dd->__w, wxPENSTYLE_DOT_DASH);
                dc.SetPen(pen);
            } else {
                wxPen pen(wxColour(dd->__red, dd->__green, dd->__blue), dd->__w, wxPENSTYLE_SOLID);
                dc.SetPen(pen);
            }
        } else if (d->__type == __GUI_DRAW_BRUSH__) {
            DrawingBrush* dd = (DrawingBrush*) d;
            int s = dd->__s;

            if (s == 0) {
                wxBrush brush(wxColour(dd->__red, dd->__green, dd->__blue), wxBRUSHSTYLE_SOLID);
                dc.SetBrush(brush);
            } else if (s == 1) {
                wxBrush brush(wxColour(dd->__red, dd->__green, dd->__blue), wxBRUSHSTYLE_BDIAGONAL_HATCH);
                dc.SetBrush(brush);
            } else if (s == 2) {
                wxBrush brush(wxColour(dd->__red, dd->__green, dd->__blue), wxBRUSHSTYLE_CROSSDIAG_HATCH);
                dc.SetBrush(brush);
            } else if (s == 3) {
                wxBrush brush(wxColour(dd->__red, dd->__green, dd->__blue), wxBRUSHSTYLE_FDIAGONAL_HATCH);
                dc.SetBrush(brush);
            } else if (s == 4) {
                wxBrush brush(wxColour(dd->__red, dd->__green, dd->__blue), wxBRUSHSTYLE_CROSS_HATCH);
                dc.SetBrush(brush);
            } else if (s == 5) {
                wxBrush brush(wxColour(dd->__red, dd->__green, dd->__blue), wxBRUSHSTYLE_HORIZONTAL_HATCH);
                dc.SetBrush(brush);
            } else if (s == 6) {
                wxBrush brush(wxColour(dd->__red, dd->__green, dd->__blue), wxBRUSHSTYLE_VERTICAL_HATCH);
                dc.SetBrush(brush);
            } else if (s == 7) {
                dc.SetBrush(*wxTRANSPARENT_BRUSH);
            } else {
                wxBrush brush(wxColour(dd->__red, dd->__green, dd->__blue), wxBRUSHSTYLE_SOLID);
                dc.SetBrush(brush);
            }
        } else if (d->__type == __GUI_DRAW_FONT__) {
            DrawingFont* dd = (DrawingFont*) d;
            int s = dd->__s;
            wxFontStyle style = (dd->__i) ? wxFONTSTYLE_ITALIC : wxFONTSTYLE_NORMAL;
            wxFontWeight weight = (dd->__b) ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL;

            if (dd->__f == "") {
                dc.SetFont(wxFont(s, wxFONTFAMILY_DEFAULT, style, weight, false));
            } else {
                dc.SetFont(wxFont(s, wxFONTFAMILY_DEFAULT, style, weight, false, dd->__f));
            }
        } else if (d->__type == __GUI_DRAW_TEXTCOLOUR__) {
            DrawingTextColour* dd = (DrawingTextColour*) d;
            dc.SetTextForeground(wxColour(dd->__red, dd->__green, dd->__blue));
        } else if (d->__type == __GUI_DRAW_BACKGROUND__) {
            DrawingBackColour* dd = (DrawingBackColour*) d;
            dc.SetBackground(wxBrush(wxColour(dd->__red, dd->__green, dd->__blue), wxBRUSHSTYLE_SOLID));
            dc.Clear();
        } else if (d->__type == __GUI_DRAW_LINE__) {
            DrawingLine* dd = (DrawingLine*) d;
            dc.DrawLine(dd->__x1, dd->__y1, dd->__x2, dd->__y2);
        } else if (d->__type == __GUI_DRAW_RECT__) {
            DrawingRect* dd = (DrawingRect*) d;
            dc.DrawRectangle(dd->__x, dd->__y, dd->__w, dd->__h);
        } else if (d->__type == __GUI_DRAW_CIRCLE__) {
            DrawingCircle* dd = (DrawingCircle*) d;
            dc.DrawCircle(dd->__x, dd->__y, dd->__r);
        } else if (d->__type == __GUI_DRAW_POINT__) {
            DrawingPoint* dd = (DrawingPoint*) d;
            dc.DrawPoint(dd->__x, dd->__y);
        } else if (d->__type == __GUI_DRAW_ELLIPSE__) {
            DrawingEllipse* dd = (DrawingEllipse*) d;
            dc.DrawEllipse(dd->__x, dd->__y, dd->__w, dd->__h);
        } else if (d->__type == __GUI_DRAW_ROUNDEDRECT__) {
            DrawingRoundedRect* dd = (DrawingRoundedRect*) d;
            dc.DrawRoundedRectangle(dd->__x, dd->__y, dd->__w, dd->__h, dd->__r);
        } else if (d->__type == __GUI_DRAW_ARC__) {
            DrawingArc* dd = (DrawingArc*) d;
            dc.DrawArc(dd->__xs, dd->__ys, dd->__xe, dd->__ye, dd->__xc, dd->__yc);
        } else if (d->__type == __GUI_DRAW_ELLIPTICARC__) {
            DrawingEllipticArc* dd = (DrawingEllipticArc*) d;
            dc.DrawEllipticArc(dd->__x, dd->__y, dd->__w, dd->__h, dd->__s, dd->__e);
        } else if (d->__type == __GUI_DRAW_TEXT__) {
            DrawingText* dd = (DrawingText*) d;
            double angle = dd->__a;

            if (angle == 0.0) {
                dc.DrawText(wxString::FromUTF8(dd->__t.c_str()), dd->__x, dd->__y);
            } else {
                dc.DrawRotatedText(wxString::FromUTF8(dd->__t.c_str()), dd->__x, dd->__y, angle);
            }
        } else if (d->__type == __GUI_DRAW_POLYGON__) {
            DrawingPolygon* dd = (DrawingPolygon*) d;
            int n = dd->__n;
            int s = dd->__s;
            wxPoint points[n];

            for (int j = 0; j < n; j++) {
                DrawingPointData p = dd->__p.at(j);
                points[j] = wxPoint(p.x, p.y);
            }

            if (s == 0) {
                dc.DrawPolygon(n, points, dd->__xo, dd->__yo, wxODDEVEN_RULE);
            } else {
                dc.DrawPolygon(n, points, dd->__xo, dd->__yo, wxWINDING_RULE);
            }
        } else if (d->__type == __GUI_DRAW_SPLINE__) {
            DrawingSpline* dd = (DrawingSpline*) d;
            int n = dd->__n;
            wxPoint points[n];

            for (int j = 0; j < n; j++) {
                DrawingPointData p = dd->__p.at(j);
                points[j] = wxPoint(p.x, p.y);
            }

            dc.DrawSpline(n, points);
        } else if (d->__type == __GUI_DRAW_LINES__) {
            DrawingLines* dd = (DrawingLines*) d;
            int n = dd->__n;
            wxPoint points[n];

            for (int j = 0; j < n; j++) {
                DrawingPointData p = dd->__p.at(j);
                points[j] = wxPoint(p.x, p.y);
            }

            dc.DrawLines(n, points);
        } else if (d->__type == __GUI_DRAW_IMAGE_DATA__) {
            DrawingImageData* dd = (DrawingImageData*) d;
            int x = dd->__x;
            int y = dd->__y;
            int w = dd->__w;
            int h = dd->__h;
            bool use_mask = dd->__use_mask;
            
            wxImage img = wxImage(dd->__image_data->__w, dd->__image_data->__h, dd->__image_data->__bytes, true);
            wxBitmap bmp;

            #ifndef __RPI__
                if (__scale_factor > 1.0) {
                    img.Rescale(w * __scale_factor, h * __scale_factor);
                    bmp = wxBitmap(img, -1, __scale_factor);
                } else {
                    if (w != dd->__image_data->__w || h != dd->__image_data->__h) img.Rescale(w, h);
                    bmp = wxBitmap(img);
                }
            #else
                if (w != dd->__image_data->__w || h != dd->__image_data->__h) img.Rescale(w, h);
                bmp = wxBitmap(img);
            #endif

            dc.DrawBitmap(bmp, x, y, use_mask);
        } else if (d->__type == __GUI_DRAW_IMAGE__) {
            DrawingImage* dd = (DrawingImage*) d;
            int x = dd->__x;
            int y = dd->__y;
            
            dc.DrawBitmap(dd->__img->__bmp, x, y);
        }
    }
}

void __event_gui_panel_paint(wxPaintEvent &event) {
    int id = event.GetId();
    GUI_Panel* g = (GUI_Panel*) __gui_map[id];
    
    if (g == NULL){
        event.Skip();
        return;
    }

    if (g->__drawing.empty()) {
        event.Skip();
        return;
    }

    wxPaintDC dc(g->__holder);
    __panel_render(dc, g);
}

void __event_gui_panel_erase(wxEraseEvent &event) {

}

void __gui_add_functions(gc<DataType> d) {
    connector->__object_set_function(d, "addevent", __gui_add_event);
    connector->__object_set_function(d, "gettext", __gui_gettext);
    connector->__object_set_function(d, "settext", __gui_settext);
    connector->__object_set_function(d, "getoverx", __gui_getoverx);
    connector->__object_set_function(d, "getovery", __gui_getovery);
    connector->__object_set_function(d, "getx", __gui_getx);
    connector->__object_set_function(d, "gety", __gui_gety);
    connector->__object_set_function(d, "setx", __gui_setx);
    connector->__object_set_function(d, "sety", __gui_sety);
    connector->__object_set_function(d, "getwidth", __gui_getwidth);
    connector->__object_set_function(d, "getheight", __gui_getheight);
    connector->__object_set_function(d, "setwidth", __gui_setwidth);
    connector->__object_set_function(d, "setheight", __gui_setheight);
    connector->__object_set_function(d, "getinnerwidth", __gui_getinnerwidth);
    connector->__object_set_function(d, "getinnerheight", __gui_getinnerheight);
    connector->__object_set_function(d, "setvisible", __gui_setvisible);
    connector->__object_set_function(d, "isvisible", __gui_isvisible);
    connector->__object_set_function(d, "setenable", __gui_setenable);
    connector->__object_set_function(d, "isenable", __gui_isenable);
    connector->__object_set_function(d, "setbackgroundcolour", __gui_setbackgroundcolour);
    connector->__object_set_function(d, "getbackgroundcolour", __gui_getbackgroundcolour);
    connector->__object_set_function(d, "setforegroundcolour", __gui_setforegroundcolour);
    connector->__object_set_function(d, "getforegroundcolour", __gui_getforegroundcolour);
    connector->__object_set_function(d, "setfont", __gui_setfont);
    connector->__object_set_function(d, "setfontsize", __gui_setfontsize);
    connector->__object_set_function(d, "setfontbold", __gui_setfontbold);
    connector->__object_set_function(d, "setfontlight", __gui_setfontlight);
    connector->__object_set_function(d, "setfontitalic", __gui_setfontitalic);
    connector->__object_set_function(d, "setfontunderline", __gui_setfontunderline);
    connector->__object_set_function(d, "setfontstrikethrough", __gui_setfontstrikethrough);
    connector->__object_set_function(d, "getfont", __gui_getfont);
    connector->__object_set_function(d, "getfontsize", __gui_getfontsize);
    connector->__object_set_function(d, "isfontbold", __gui_isfontbold);
    connector->__object_set_function(d, "isfontlight", __gui_isfontlight);
    connector->__object_set_function(d, "isfontitalic", __gui_isfontitalic);
    connector->__object_set_function(d, "isfontunderline", __gui_isfontunderline);
    connector->__object_set_function(d, "isfontstrikethrough", __gui_isfontstrikethrough);
    connector->__object_set_function(d, "setfocus", __gui_setfocus);
    connector->__object_set_function(d, "settooltip", __gui_settooltip);
    connector->__object_set_function(d, "gettooltip", __gui_gettooltip);

    connector->__object_set_function(d, "centre", __gui_center);
    connector->__object_set_function(d, "centrehorizontal", __gui_centerhorizontal);
    connector->__object_set_function(d, "centrevertical", __gui_centervertical);
    connector->__object_set_function(d, "right", __gui_right);
    connector->__object_set_function(d, "bottom", __gui_bottom);
    connector->__object_set_function(d, "stretch", __gui_stretch);
    connector->__object_set_function(d, "stretchwidth", __gui_stretchwidth);
    connector->__object_set_function(d, "stretchheight", __gui_stretchheight);

    connector->__object_set_function(d, "refresh", __gui_refresh);
}

void __gui_bind_events(wxWindow* gui, int index) {
    gui->Bind(wxEVT_LEFT_UP, &__event_gui_mouse, index);
    gui->Bind(wxEVT_LEFT_DOWN, &__event_gui_mouse, index);
    gui->Bind(wxEVT_RIGHT_UP, &__event_gui_mouse, index);
    gui->Bind(wxEVT_RIGHT_DOWN, &__event_gui_mouse, index);
    gui->Bind(wxEVT_ENTER_WINDOW, &__event_gui_mouse, index);
    gui->Bind(wxEVT_LEAVE_WINDOW, &__event_gui_mouse, index);
    gui->Bind(wxEVT_MOTION, &__event_gui_mouse, index);

    gui->Bind(wxEVT_KEY_UP, &__event_gui_key, index);
    gui->Bind(wxEVT_KEY_DOWN, &__event_gui_key, index);
}

wxWindow* __get_gui_holder(GUI* g) {
    if (g->__type == __GUI_TEXTBOX__) {
        return ((GUI_TextBox*) g)->__holder;
    } else if (g->__type == __GUI_LABEL__) {
        return ((GUI_Label*) g)->__holder;
    } else if (g->__type == __GUI_BUTTON__) {
        return ((GUI_Button*) g)->__holder;
    } else if (g->__type == __GUI_RADIOBOX__) {
        return ((GUI_RadioBox*) g)->__holder;
    } else if (g->__type == __GUI_CHECKBOX__) {
        return ((GUI_CheckBox*) g)->__holder;
    } else if (g->__type == __GUI_PANEL__) {
        return ((GUI_Panel*) g)->__holder;
    } else if (g->__type == __GUI_LABELED_PANEL__) {
        return ((GUI_LabeledPanel*) g)->__holder;
    } else if (g->__type == __GUI_WINDOW__) {
        return ((GUI_Window*) g)->__holder;
    } else if (g->__type == __GUI_TAB__) {
        return ((GUI_Tab*) g)->__holder;
    } else if (g->__type == __GUI_TEXTAREA__) {
        return ((GUI_TextArea*) g)->__holder;
    } else if (g->__type == __GUI_LISTBOX__) {
        return ((GUI_ListBox*) g)->__holder;
    } else if (g->__type == __GUI_COMBOBOX__) {
        if (((GUI_ComboBox*) g)->__editable) {
            return ((GUI_ComboBox*) g)->__holder;
        } else {
            return ((GUI_ComboBox*) g)->__holder_choice;
        }
    } else if (g->__type == __GUI_IMAGEBOX__) {
        return ((GUI_ImageBox*) g)->__holder;
    }

    return NULL;
}

wxWindow* __get_gui_holder_alt(GUI* g) {
    if (g->__type == __GUI_TEXTBOX__) {
        return ((GUI_TextBox*) g)->__holder;
    } else if (g->__type == __GUI_LABEL__) {
        return ((GUI_Label*) g)->__holder;
    } else if (g->__type == __GUI_BUTTON__) {
        return ((GUI_Button*) g)->__holder;
    } else if (g->__type == __GUI_RADIOBOX__) {
        return ((GUI_RadioBox*) g)->__holder;
    } else if (g->__type == __GUI_CHECKBOX__) {
        return ((GUI_CheckBox*) g)->__holder;
    } else if (g->__type == __GUI_PANEL__) {
        return ((GUI_Panel*) g)->__holder;
    } else if (g->__type == __GUI_LABELED_PANEL__) {
        return ((GUI_LabeledPanel*) g)->__holder;
    } else if (g->__type == __GUI_WINDOW__) {
        return ((GUI_Window*) g)->__panel_holder;
    } else if (g->__type == __GUI_TAB__) {
        return ((GUI_Tab*) g)->__holder;
    } else if (g->__type == __GUI_TEXTAREA__) {
        return ((GUI_TextArea*) g)->__holder;
    } else if (g->__type == __GUI_LISTBOX__) {
        return ((GUI_ListBox*) g)->__holder;
    } else if (g->__type == __GUI_COMBOBOX__) {
        if (((GUI_ComboBox*) g)->__editable) {
            return ((GUI_ComboBox*) g)->__holder;
        } else {
            return ((GUI_ComboBox*) g)->__holder_choice;
        }
    } else if (g->__type == __GUI_IMAGEBOX__) {
        return ((GUI_ImageBox*) g)->__holder;
    }

    return NULL;
}

gc<DataType> __create_window(string title, int width, int height, bool resizable, bool minimisable, bool closable, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_window");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";

    __gui_add_functions(result);

    connector->__object_set_function(result, "show", __gui_window_show);
    connector->__object_set_function(result, "close", __gui_window_close);
    connector->__object_set_function(result, "settitle", __gui_window_settitle);
    connector->__object_set_function(result, "gettitle", __gui_window_gettitle);
    connector->__object_set_function(result, "isminimised", __gui_window_isminimised);
    connector->__object_set_function(result, "ismaximised", __gui_window_ismaximised);
    connector->__object_set_function(result, "setfullscreen", __gui_window_setfullscreen);
    connector->__object_set_function(result, "isfullscreen", __gui_window_isfullscreen);

    GUI_Window* w = new GUI_Window();
    w->__index = __gui_n++;
    w->__caller_id = caller_id;

    long style = wxSYSTEM_MENU | wxCAPTION | wxCLIP_CHILDREN;

    if (resizable) style |= wxRESIZE_BORDER | wxMAXIMIZE_BOX;
    if (minimisable) style |= wxMINIMIZE_BOX;
    if (closable) style |= wxCLOSE_BOX;

    wxFrame* frame = new wxFrame(NULL, w->__index, wxString::FromUTF8(title.c_str()), wxDefaultPosition, wxSize(width, height), style);
    wxPanel* panel = new wxPanel(frame, w->__index);

    int delta_width = width - frame->GetClientSize().GetWidth();
    int delta_height = height - frame->GetClientSize().GetHeight();

    frame->SetSize(wxSize(width + delta_width, height + delta_height));

    #ifndef __RPI__
        if (!__factor_set) {
            __scale_factor = frame->GetContentScaleFactor();
            __dpi_factor = frame->GetDPIScaleFactor();
            __factor_set = true;
        }
    #else
        __factor_set = true;
    #endif

    #ifdef _WIN32
        frame->SetIcon(wxIcon("FIO-ICON-3"));
    #endif

    #ifdef __APPLE__
        wxMenuBar* menubar = new wxMenuBar();

        wxMenu* window_menu = new wxMenu();
        wxMenu* help_menu = new wxMenu();

        menubar->Append(window_menu, _("Window"));
        menubar->Append(help_menu, _("Help"));

        frame->SetMenuBar(menubar);
    #endif

    frame->Bind(wxEVT_ACTIVATE, &__event_gui_window_activate, w->__index);
    frame->Bind(wxEVT_CLOSE_WINDOW, &__event_gui_window_close, w->__index);
    frame->Bind(wxEVT_ICONIZE, &__event_gui_window_minimize, w->__index);
    frame->Bind(wxEVT_MAXIMIZE, &__event_gui_window_maximize, w->__index);
    frame->Bind(wxEVT_SIZE, &__event_gui_window_resize, w->__index);

    __gui_bind_events(panel, w->__index);

    __gui_map[w->__index] = w;
    w->__holder = frame;
    w->__panel_holder = panel;

    obj->__holder_pointer = w;
    return result;
}

gc<DataType> __create_menubar(GUI* parent) {
    gc<DataType> result = connector->__create_object("gui_menubar");
    gc<Object> obj = result->__value_object;

    connector->__object_set_function(result, "append", __gui_menubar_append);
    connector->__object_set_function(result, "insert", __gui_menubar_insert);
    connector->__object_set_function(result, "remove", __gui_menubar_remove);

    GUI_MenuBar* g = new GUI_MenuBar();
    g->__index = __gui_n++;

    wxMenuBar* gui = new wxMenuBar();

    if (parent->__type == __GUI_WINDOW__) {
        ((GUI_Window*) parent)->__holder->SetMenuBar(gui);
    } else {
        connector->__error_message("gui_menubar(): parameter #1 must be a gui_window object");
    }

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_menu() {
    gc<DataType> result = connector->__create_object("gui_menu");
    gc<Object> obj = result->__value_object;

    connector->__object_set_function(result, "append", __gui_menu_append);
    connector->__object_set_function(result, "appendseparator", __gui_menu_appendseparator);
    connector->__object_set_function(result, "appendsubmenu", __gui_menu_appendsubmenu);
    connector->__object_set_function(result, "insert", __gui_menu_insert);
    connector->__object_set_function(result, "insertseparator", __gui_menu_insertseparator);
    connector->__object_set_function(result, "insertsubmenu", __gui_menu_insertsubmenu);
    connector->__object_set_function(result, "remove", __gui_menu_remove);
    connector->__object_set_function(result, "setlabel", __gui_menu_setlabel);
    connector->__object_set_function(result, "getlabel", __gui_menu_getlabel);
    connector->__object_set_function(result, "setenable", __gui_menu_setenable);
    connector->__object_set_function(result, "isenable", __gui_menu_isenable);
    connector->__object_set_function(result, "setchecked", __gui_menu_setchecked);
    connector->__object_set_function(result, "ischecked", __gui_menu_ischecked);

    GUI_Menu* g = new GUI_Menu();
    g->__index = __gui_n++;

    wxMenu* gui = new wxMenu();

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_stack(bool vertical, GUI* parent) {
    gc<DataType> result = connector->__create_object("gui_stack");
    gc<Object> obj = result->__value_object;

    connector->__object_set_function(result, "add", __gui_stack_add);
    connector->__object_set_function(result, "addspacer", __gui_stack_addspacer);

    GUI_Stack* g = new GUI_Stack();
    g->__index = __gui_n++;

    wxBoxSizer* gui = new wxBoxSizer(vertical ? wxVERTICAL : wxHORIZONTAL);

    if (parent->__type == __GUI_WINDOW__) {
        ((GUI_Window*) parent)->__panel_holder->SetSizer(gui);
        gui->SetSizeHints(((GUI_Window*) parent)->__panel_holder);
    } else if (parent->__type == __GUI_PANEL__) {
        ((GUI_Panel*) parent)->__holder->SetSizer(gui);
    } else {
        connector->__error_message("gui_stack(): parameter #2 must be a gui_window or gui_panel object");
    }

    __gui_map[g->__index] = g;
    g->__holder = gui;
    g->__is_vertical = vertical;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_grid(int rows, int cols, GUI* parent, int vertical_gap, int horizontal_gap, bool grow_all = false) {
    gc<DataType> result = connector->__create_object("gui_grid");
    gc<Object> obj = result->__value_object;

    connector->__object_set_function(result, "add", __gui_grid_add);
    connector->__object_set_function(result, "addgrowablecol", __gui_grid_addgrowablecol);
    connector->__object_set_function(result, "addgrowablerow", __gui_grid_addgrowablerow);

    GUI_Grid* g = new GUI_Grid();
    g->__index = __gui_n++;

    wxFlexGridSizer* gui = new wxFlexGridSizer(rows, cols, vertical_gap, horizontal_gap);

    if (parent->__type == __GUI_WINDOW__) {
        ((GUI_Window*) parent)->__panel_holder->SetSizer(gui);
        gui->SetSizeHints(((GUI_Window*) parent)->__panel_holder);
    } else if (parent->__type == __GUI_PANEL__) {
        ((GUI_Panel*) parent)->__holder->SetSizer(gui);
    } else {
        connector->__error_message("gui_grid(): parameter #3 must be a gui_window or gui_panel object");
    }

    if (grow_all) {
        for (int i = 0; i < rows; i++) {
            gui->AddGrowableRow(i);
        }

        for (int i = 0; i < cols; i++) {
            gui->AddGrowableCol(i);
        }
    }

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_panel(GUI* parent, int x, int y, int width, int height, bool as_canvas, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_panel");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";

    __gui_add_functions(result);

    connector->__object_set_function(result, "draw_setpen", __gui_draw_setpen);
    connector->__object_set_function(result, "draw_setbrush", __gui_draw_setbrush);
    connector->__object_set_function(result, "draw_setfont", __gui_draw_setfont);
    connector->__object_set_function(result, "draw_settextcolour", __gui_draw_settextcolour);
    connector->__object_set_function(result, "draw_setbackgroundcolour", __gui_draw_setbackgroundcolour);
    connector->__object_set_function(result, "draw_line", __gui_draw_line);
    connector->__object_set_function(result, "draw_lines", __gui_draw_lines);
    connector->__object_set_function(result, "draw_rectangle", __gui_draw_rectangle);
    connector->__object_set_function(result, "draw_point", __gui_draw_point);
    connector->__object_set_function(result, "draw_circle", __gui_draw_circle);
    connector->__object_set_function(result, "draw_ellipse", __gui_draw_ellipse);
    connector->__object_set_function(result, "draw_arc", __gui_draw_arc);
    connector->__object_set_function(result, "draw_ellipticarc", __gui_draw_ellipticarc);
    connector->__object_set_function(result, "draw_polygon", __gui_draw_polygon);
    connector->__object_set_function(result, "draw_roundedrectangle", __gui_draw_roundedrectangle);
    connector->__object_set_function(result, "draw_spline", __gui_draw_spline);
    connector->__object_set_function(result, "draw_image_data", __gui_draw_image_data);
    connector->__object_set_function(result, "draw_image", __gui_draw_image);
    connector->__object_set_function(result, "draw_text", __gui_draw_text);
    connector->__object_set_function(result, "draw_gettextwidth", __gui_draw_gettextwidth);
    connector->__object_set_function(result, "draw_gettextheight", __gui_draw_gettextheight);
    connector->__object_set_function(result, "draw_clear", __gui_draw_clear);
    connector->__object_set_function(result, "draw_save", __gui_draw_save);
    connector->__object_set_function(result, "draw_now", __gui_draw_now);
    connector->__object_set_function(result, "update", __gui_panel_update);

    GUI_Panel* g = new GUI_Panel();
    g->__index = __gui_n++;
    g->__caller_id = caller_id;
    g->__canvas_mode = as_canvas;

    wxPanel* gui;

    if (parent->__type == __GUI_WINDOW__) {
        if (width == 0 && height == 0) {
            gui = new wxPanel(((GUI_Window*) parent)->__panel_holder, g->__index, wxPoint(x, y));
        } else {
            gui = new wxPanel(((GUI_Window*) parent)->__panel_holder, g->__index, wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxPanel(((GUI_Panel*) parent)->__holder, g->__index, wxPoint(x, y));
        } else {
            gui = new wxPanel(((GUI_Panel*) parent)->__holder, g->__index, wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxPanel(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxPoint(x, y));
        } else {
            gui = new wxPanel(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else if (parent->__type == __GUI_TAB__) {
        if (width == 0 && height == 0) {
            gui = new wxPanel(((GUI_Tab*) parent)->__holder, g->__index, wxPoint(x, y));
        } else {
            gui = new wxPanel(((GUI_Tab*) parent)->__holder, g->__index, wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_Tab*) parent)->__holder;
    } else {
        connector->__error_message("gui_panel(): invalid parent");
    }

    if (as_canvas) gui->Bind(wxEVT_PAINT, &__event_gui_panel_paint, g->__index);
    if (as_canvas) gui->Bind(wxEVT_ERASE_BACKGROUND, &__event_gui_panel_erase, g->__index);
    
    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_labeled_panel(GUI* parent, string text, int x, int y, int width, int height, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_labeled_panel");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";

    __gui_add_functions(result);

    GUI_LabeledPanel* g = new GUI_LabeledPanel();
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxStaticBox* gui;

    if (parent->__type == __GUI_WINDOW__) {
        if (width == 0 && height == 0) {
            gui = new wxStaticBox(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y));
        } else {
            gui = new wxStaticBox(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxStaticBox(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y));
        } else {
            gui = new wxStaticBox(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxStaticBox(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y));
        } else {
            gui = new wxStaticBox(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_labeled_panel(): invalid parent");
    }

    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_tab(GUI* parent, int x, int y, int width, int height, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_tab");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";

    __gui_add_functions(result);
    connector->__object_set_function(result, "addpage", __gui_tab_addpage);
    connector->__object_set_function(result, "removepage", __gui_tab_removepage);
    connector->__object_set_function(result, "getpage", __gui_tab_getpage);
    connector->__object_set_function(result, "setpage", __gui_tab_setpage);

    GUI_Tab* g = new GUI_Tab();
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxNotebook* gui;

    if (parent->__type == __GUI_WINDOW__) {
        if (width == 0 && height == 0) {
            gui = new wxNotebook(((GUI_Window*) parent)->__panel_holder, g->__index, wxPoint(x, y));
        } else {
            gui = new wxNotebook(((GUI_Window*) parent)->__panel_holder, g->__index, wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxNotebook(((GUI_Panel*) parent)->__holder, g->__index, wxPoint(x, y));
        } else {
            gui = new wxNotebook(((GUI_Panel*) parent)->__holder, g->__index, wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxNotebook(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxPoint(x, y));
        } else {
            gui = new wxNotebook(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_tab(): invalid parent");
    }

    gui->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, &__event_gui_tab, g->__index);
    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_button(GUI* parent, string text, int x, int y, int width, int height, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_button");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";
    
    __gui_add_functions(result);

    GUI_Button* g = new GUI_Button();
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxButton* gui;

    if (parent->__type == __GUI_WINDOW__) {
        gui = new wxButton(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        gui = new wxButton(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        gui = new wxButton(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_button(): invalid parent");
    }

    gui->Bind(wxEVT_BUTTON, &__event_gui_command, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_label(GUI* parent, string text, int x, int y, int width, int height, int alignment, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_label");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";

    __gui_add_functions(result);

    GUI_Label* g = new GUI_Label();
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxStaticText* gui;

    if (parent->__type == __GUI_WINDOW__) {
        if (width == 0 && height == 0) {
            gui = new wxStaticText(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxDefaultSize, alignment);
        } else {
            gui = new wxStaticText(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), alignment | wxST_NO_AUTORESIZE);
        }

        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxStaticText(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxDefaultSize, alignment);
        } else {
            gui = new wxStaticText(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), alignment | wxST_NO_AUTORESIZE);
        }

        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxStaticText(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxDefaultSize, alignment);
        } else {
            gui = new wxStaticText(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), alignment | wxST_NO_AUTORESIZE);
        }

        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_label(): invalid parent");
    }

    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_textbox(GUI* parent, string text, int x, int y, int width, int height, bool is_password, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_textbox");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";

    __gui_add_functions(result);
    
    connector->__object_set_function(result, "appendtext", __gui_textbox_appendtext);
    connector->__object_set_function(result, "setlocked", __gui_textbox_setlocked);
    connector->__object_set_function(result, "islocked", __gui_textbox_islocked);
    connector->__object_set_function(result, "setmaxlength", __gui_textbox_setmaxlength);
    connector->__object_set_function(result, "setsel", __gui_textbox_setsel);
    connector->__object_set_function(result, "getselbegin", __gui_textbox_getselbegin);
    connector->__object_set_function(result, "getselend", __gui_textbox_getselend);
    connector->__object_set_function(result, "setseltext", __gui_textbox_setseltext);
    connector->__object_set_function(result, "getseltext", __gui_textbox_getseltext);

    GUI_TextBox* g = new GUI_TextBox();
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxTextCtrl* gui;

    if (!is_password) {
        if (parent->__type == __GUI_WINDOW__) {
            if (width == 0 && height == 0) {
                gui = new wxTextCtrl(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y));
            } else {
                gui = new wxTextCtrl(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
            }

            g->__parent = ((GUI_Window*) parent)->__holder;
        } else if (parent->__type == __GUI_PANEL__) {
            if (width == 0 && height == 0) {
                gui = new wxTextCtrl(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y));
            } else {
                gui = new wxTextCtrl(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
            }

            g->__parent = ((GUI_Panel*) parent)->__holder;
        } else if (parent->__type == __GUI_LABELED_PANEL__) {
            if (width == 0 && height == 0) {
                gui = new wxTextCtrl(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y));
            } else {
                gui = new wxTextCtrl(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
            }

            g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
        } else {
            connector->__error_message("gui_textbox(): invalid parent");
        }
    } else {
        if (parent->__type == __GUI_WINDOW__) {
            if (width == 0 && height == 0) {
                gui = new wxTextCtrl(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxDefaultSize, wxTE_PASSWORD);
            } else {
                gui = new wxTextCtrl(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), wxTE_PASSWORD);
            }

            g->__parent = ((GUI_Window*) parent)->__holder;
        } else if (parent->__type == __GUI_PANEL__) {
            if (width == 0 && height == 0) {
                gui = new wxTextCtrl(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxDefaultSize, wxTE_PASSWORD);
            } else {
                gui = new wxTextCtrl(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), wxTE_PASSWORD);
            }

            g->__parent = ((GUI_Panel*) parent)->__holder;
        } else if (parent->__type == __GUI_LABELED_PANEL__) {
            if (width == 0 && height == 0) {
                gui = new wxTextCtrl(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxDefaultSize, wxTE_PASSWORD);
            } else {
                gui = new wxTextCtrl(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), wxTE_PASSWORD);
            }

            g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
        } else {
            connector->__error_message("gui_textbox(): invalid parent");
        }
    }

    gui->Bind(wxEVT_TEXT, &__event_gui_text, g->__index);
    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_textarea(GUI* parent, string text, int x, int y, int width, int height, bool wrap, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_textarea");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui,gui_textbox";

    __gui_add_functions(result);
    
    connector->__object_set_function(result, "appendtext", __gui_textbox_appendtext);
    connector->__object_set_function(result, "setlocked", __gui_textbox_setlocked);
    connector->__object_set_function(result, "islocked", __gui_textbox_islocked);
    connector->__object_set_function(result, "setsel", __gui_textbox_setsel);
    connector->__object_set_function(result, "getselbegin", __gui_textbox_getselbegin);
    connector->__object_set_function(result, "getselend", __gui_textbox_getselend);
    connector->__object_set_function(result, "setseltext", __gui_textbox_setseltext);
    connector->__object_set_function(result, "getseltext", __gui_textbox_getseltext);

    GUI_TextBox* g = new GUI_TextBox();
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxTextCtrl* gui;

    if (parent->__type == __GUI_WINDOW__) {
        if (wrap) {
            gui = new wxTextCtrl(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), wxTE_PROCESS_TAB | wxTE_MULTILINE);
        } else {
            gui = new wxTextCtrl(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), wxTE_PROCESS_TAB | wxTE_MULTILINE | wxTE_DONTWRAP);
        }

        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        if (wrap) {
            gui = new wxTextCtrl(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), wxTE_PROCESS_TAB | wxTE_MULTILINE);
        } else {
            gui = new wxTextCtrl(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), wxTE_PROCESS_TAB | wxTE_MULTILINE | wxTE_DONTWRAP);
        }

        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        if (wrap) {
            gui = new wxTextCtrl(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), wxTE_PROCESS_TAB | wxTE_MULTILINE);
        } else {
            gui = new wxTextCtrl(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), wxTE_PROCESS_TAB | wxTE_MULTILINE | wxTE_DONTWRAP);
        }

        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_textarea(): invalid parent");
    }
    
    gui->Bind(wxEVT_TEXT, &__event_gui_textarea, g->__index);
    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_checkbox(GUI* parent, string text, bool checked, int x, int y, int width, int height, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_checkbox");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";

    __gui_add_functions(result);
    connector->__object_set_function(result, "ischecked", __gui_checkbox_ischecked);
    connector->__object_set_function(result, "setchecked", __gui_checkbox_setchecked);

    GUI_CheckBox* g = new GUI_CheckBox();
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxCheckBox* gui;

    if (parent->__type == __GUI_WINDOW__) {
        if (width == 0 && height == 0) {
            gui = new wxCheckBox(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y));
        } else {
            gui = new wxCheckBox(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxCheckBox(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y));
        } else {
            gui = new wxCheckBox(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxCheckBox(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y));
        } else {
            gui = new wxCheckBox(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height));
        }

        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_checkbox(): invalid parent");
    }

    if (checked) gui->SetValue(true);

    gui->Bind(wxEVT_CHECKBOX, &__event_gui_checkbox, g->__index);
    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_radiobox(GUI* parent, string text, bool start_group, bool checked, int x, int y, int width, int height, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_radiobox");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";

    __gui_add_functions(result);
    connector->__object_set_function(result, "ischecked", __gui_radiobox_ischecked);
    connector->__object_set_function(result, "setchecked", __gui_radiobox_setchecked);

    GUI_RadioBox* g = new GUI_RadioBox();
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxRadioButton* gui;

    if (parent->__type == __GUI_WINDOW__) {
        if (width == 0 && height == 0) {
            gui = new wxRadioButton(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxDefaultSize, (start_group) ? wxRB_GROUP : 0);
        } else {
            gui = new wxRadioButton(((GUI_Window*) parent)->__panel_holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), (start_group) ? wxRB_GROUP : 0);
        }

        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxRadioButton(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxDefaultSize, (start_group) ? wxRB_GROUP : 0);
        } else {
            gui = new wxRadioButton(((GUI_Panel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), (start_group) ? wxRB_GROUP : 0);
        }

        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        if (width == 0 && height == 0) {
            gui = new wxRadioButton(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxDefaultSize, (start_group) ? wxRB_GROUP : 0);
        } else {
            gui = new wxRadioButton(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxString::FromUTF8(text.c_str()), wxPoint(x, y), wxSize(width, height), (start_group) ? wxRB_GROUP : 0);
        }

        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_radiobox(): invalid parent");
    }

    if (checked) gui->SetValue(true);

    gui->Bind(wxEVT_RADIOBUTTON, &__event_gui_radiobox, g->__index);
    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_listbox(GUI* parent, gc<Array> list, bool multiple_selection, int x, int y, int width, int height, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_listbox");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";
    
    __gui_add_functions(result);

    connector->__object_set_function(result, "add", __gui_listbox_add);
    connector->__object_set_function(result, "remove", __gui_listbox_remove);
    connector->__object_set_function(result, "clear", __gui_listbox_clear);
    connector->__object_set_function(result, "size", __gui_listbox_size);
    connector->__object_set_function(result, "get", __gui_listbox_get);
    connector->__object_set_function(result, "set", __gui_listbox_set);
    connector->__object_set_function(result, "getindex", __gui_listbox_getindex);
    connector->__object_set_function(result, "setindex", __gui_listbox_setindex);
    connector->__object_set_function(result, "getselections", __gui_listbox_getselections);

    GUI_ListBox* g = new GUI_ListBox();
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxListBox* gui;
    wxArrayString arr;
    
    for (const auto t: list->__elements) {
        string s = "";

        if (t->__type == __TYPE_DOUBLE__) {
            char buffer[255];
            sprintf(buffer, "%g", t->__value_double);
            s = buffer;
            arr.Add(s);
        } else if (t->__type == __TYPE_STRING__) {
            s = t->__value_string;
            arr.Add(wxString::FromUTF8(s.c_str()));
        } else if (t->__type == __TYPE_BOOL__) {
            s = t->__value_bool ? "true" : "false";
            arr.Add(s);
        }
    }

    if (parent->__type == __GUI_WINDOW__) {
        gui = new wxListBox(((GUI_Window*) parent)->__panel_holder, g->__index, wxPoint(x, y), wxSize(width, height), arr, (multiple_selection) ? wxLB_EXTENDED : wxLB_SINGLE);
        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        gui = new wxListBox(((GUI_Panel*) parent)->__holder, g->__index, wxPoint(x, y), wxSize(width, height), arr, (multiple_selection) ? wxLB_EXTENDED : wxLB_SINGLE);
        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        gui = new wxListBox(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxPoint(x, y), wxSize(width, height), arr, (multiple_selection) ? wxLB_EXTENDED : wxLB_SINGLE);
        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_listbox(): invalid parent");
    }

    gui->Bind(wxEVT_LISTBOX, &__event_gui_listbox_click, g->__index);
    gui->Bind(wxEVT_LISTBOX_DCLICK, &__event_gui_listbox_double_click, g->__index);
    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_combobox(GUI* parent, gc<Array> list, int x, int y, int width, int height, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_combobox");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui,gui_listbox";
    
    __gui_add_functions(result);
    
    connector->__object_set_function(result, "add", __gui_combobox_add);
    connector->__object_set_function(result, "remove", __gui_combobox_remove);
    connector->__object_set_function(result, "clear", __gui_combobox_clear);
    connector->__object_set_function(result, "size", __gui_combobox_size);
    connector->__object_set_function(result, "get", __gui_combobox_get);
    connector->__object_set_function(result, "set", __gui_combobox_set);
    connector->__object_set_function(result, "getindex", __gui_combobox_getindex);
    connector->__object_set_function(result, "setindex", __gui_combobox_setindex);

    GUI_ComboBox* g = new GUI_ComboBox(false);
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxChoice* gui;
    wxArrayString arr;
    
    for (const auto t: list->__elements) {
        string s = "";

        if (t->__type == __TYPE_DOUBLE__) {
            char buffer[255];
            sprintf(buffer, "%g", t->__value_double);
            s = buffer;
            arr.Add(s);
        } else if (t->__type == __TYPE_STRING__) {
            s = t->__value_string;
            arr.Add(wxString::FromUTF8(s.c_str()));
        } else if (t->__type == __TYPE_BOOL__) {
            s = t->__value_bool ? "true" : "false";
            arr.Add(s);
        }
    }

    wxSize size = wxDefaultSize;
    if (width != 0 || height != 0) size = wxSize(width, height);

    if (parent->__type == __GUI_WINDOW__) {
        gui = new wxChoice(((GUI_Window*) parent)->__panel_holder, g->__index, wxPoint(x, y), size, arr);
        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        gui = new wxChoice(((GUI_Panel*) parent)->__holder, g->__index, wxPoint(x, y), size, arr);
        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        gui = new wxChoice(((GUI_LabeledPanel*) parent)->__holder, g->__index, wxPoint(x, y), size, arr);
        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_combobox(): invalid parent");
    }

    gui->Bind(wxEVT_CHOICE, &__event_gui_combobox_click, g->__index);
    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder_choice = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_editable_combobox(GUI* parent, gc<Array> list, int x, int y, int width, int height, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_combobox");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui,gui_listbox";
    
    __gui_add_functions(result);
    
    connector->__object_set_function(result, "add", __gui_combobox_add);
    connector->__object_set_function(result, "remove", __gui_combobox_remove);
    connector->__object_set_function(result, "clear", __gui_combobox_clear);
    connector->__object_set_function(result, "size", __gui_combobox_size);
    connector->__object_set_function(result, "get", __gui_combobox_get);
    connector->__object_set_function(result, "set", __gui_combobox_set);
    connector->__object_set_function(result, "getindex", __gui_combobox_getindex);
    connector->__object_set_function(result, "setindex", __gui_combobox_setindex);

    GUI_ComboBox* g = new GUI_ComboBox(true);
    g->__index = __gui_n++;
    g->__caller_id = caller_id;

    wxComboBox* gui;
    wxArrayString arr;

    for (const auto t: list->__elements) {
        string s = "";

        if (t->__type == __TYPE_DOUBLE__) {
            char buffer[255];
            sprintf(buffer, "%g", t->__value_double);
            s = buffer;
            arr.Add(s);
        } else if (t->__type == __TYPE_STRING__) {
            s = t->__value_string;
            arr.Add(wxString::FromUTF8(s.c_str()));
        } else if (t->__type == __TYPE_BOOL__) {
            s = t->__value_bool ? "true" : "false";
            arr.Add(s);
        }
    }

    wxSize size = wxDefaultSize;
    if (width != 0 || height != 0) size = wxSize(width, height);

    if (parent->__type == __GUI_WINDOW__) {
        gui = new wxComboBox(((GUI_Window*) parent)->__panel_holder, g->__index, "", wxPoint(x, y), size, arr, wxCB_DROPDOWN);
        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        gui = new wxComboBox(((GUI_Panel*) parent)->__holder, g->__index, "", wxPoint(x, y), size, arr, wxCB_DROPDOWN);
        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        gui = new wxComboBox(((GUI_LabeledPanel*) parent)->__holder, g->__index, "", wxPoint(x, y), size, arr, wxCB_DROPDOWN);
        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_combobox(): invalid parent");
    }

    gui->Bind(wxEVT_COMBOBOX, &__event_gui_combobox_click, g->__index);
    gui->Bind(wxEVT_TEXT, &__event_gui_combobox_change, g->__index);
    __gui_bind_events(gui, g->__index);

    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

gc<DataType> __create_timer(int interval, AST* event, uint_fast32_t caller_id) {
    gc<DataType> result = connector->__create_object("gui_timer");
    gc<Object> obj = result->__value_object;

    connector->__object_set_function(result, "run", __gui_timer_run);
    connector->__object_set_function(result, "pause", __gui_timer_pause);
    connector->__object_set_function(result, "isrunning", __gui_timer_isrunning);
    connector->__object_set_function(result, "getinterval", __gui_timer_getinterval);
    connector->__object_set_function(result, "setinterval", __gui_timer_setinterval);

    AST* func;

    if (event->__type == __AST_FUNCTION_CALL__) {
        vector<AST*> params;
        AST_FunctionCall* af = (AST_FunctionCall*) event;

        for (int i = 0; i < af->__parameters.size(); i++) {
            gc<DataType> d = connector->__get_value(af->__parameters.at(i), caller_id);
            gc<DataType> e;

            if (d->__type == __TYPE_DOUBLE__) {
                e = new_gc<DataType>(__TYPE_DOUBLE__);
                e->__value_double = d->__value_double;
            } else if (d->__type == __TYPE_BOOL__) {
                e = new_gc<DataType>(__TYPE_BOOL__);
                e->__value_bool = d->__value_bool;
            } else if (d->__type == __TYPE_STRING__) {
                e = new_gc<DataType>(__TYPE_STRING__);
                e->__value_string = d->__value_string;
            } else if (d->__type == __TYPE_ARRAY__) {
                e = new_gc<DataType>(__TYPE_ARRAY__);
                e->__value_array = d->__value_array;
            } else if (d->__type == __TYPE_OBJECT__) {
                e = new_gc<DataType>(__TYPE_OBJECT__);
                e->__value_object = d->__value_object;
            }

            params.push_back(new AST_Value(e));
        }

        AST_FunctionCall* f = new AST_FunctionCall(af->__identifier);
        f->__address = af->__address;
        f->__parameters = params;

        func = f;
    } else {
        connector->__error_message("gui_timer(): parameter #2 cannot be an object function call");
    }
    
    GUI_Timer* t = new GUI_Timer(interval);
    TimerHandler* timer = new TimerHandler(func, caller_id);

    t->__holder = timer;
    obj->__holder_pointer = t;

    return result;
}

gc<DataType> __create_imagebox(GUI* parent, string path, int x, int y, int width, int height) {
    gc<DataType> result = connector->__create_object("gui_imagebox");
    gc<Object> obj = result->__value_object;
    obj->__inherited = "gui";

    __gui_add_functions(result);
    connector->__object_set_function(result, "getimage", __gui_imagebox_getimage);
    connector->__object_set_function(result, "setimage", __gui_imagebox_setimage);
    connector->__object_set_function(result, "setscalemode", __gui_imagebox_setscalemode);
    connector->__object_set_function(result, "getoriginalwidth", __gui_imagebox_getoriginalwidth);
    connector->__object_set_function(result, "getoriginalheight", __gui_imagebox_getoriginalheight);

    GUI_ImageBox* g = new GUI_ImageBox();
    g->__index = __gui_n++;

    wxStaticBitmap* gui;
    wxBitmap bmp(path, wxBITMAP_TYPE_ANY);

    g->__path = path;
    g->__original_width = bmp.GetWidth();
    g->__original_height = bmp.GetHeight();

    if (parent->__type == __GUI_WINDOW__) {
        gui = new wxStaticBitmap(((GUI_Window*) parent)->__panel_holder, g->__index, bmp, wxPoint(x, y), wxDefaultSize);
        g->__parent = ((GUI_Window*) parent)->__holder;
    } else if (parent->__type == __GUI_PANEL__) {
        gui = new wxStaticBitmap(((GUI_Panel*) parent)->__holder, g->__index, bmp, wxPoint(x, y), wxDefaultSize);
        g->__parent = ((GUI_Panel*) parent)->__holder;
    } else if (parent->__type == __GUI_LABELED_PANEL__) {
        gui = new wxStaticBitmap(((GUI_LabeledPanel*) parent)->__holder, g->__index, bmp, wxPoint(x, y), wxDefaultSize);
        g->__parent = ((GUI_LabeledPanel*) parent)->__holder;
    } else {
        connector->__error_message("gui_imagebox(): invalid parent");
    }

    #ifndef __RPI__
        gui->SetScaleMode(wxStaticBitmapBase::Scale_AspectFit);
    #endif
    
    if (width != 0) {
        gui->SetSize(width, gui->GetSize().GetHeight());
    }
    if (height != 0) {
        gui->SetSize(gui->GetSize().GetWidth(), height);
    }
    
    __gui_map[g->__index] = g;
    g->__holder = gui;

    obj->__holder_pointer = g;
    return result;
}

void __gui_add_event_handler(GUI* gui, int event, AST* funct, uint_fast32_t& caller_id) {
    AST* func;

    if (funct->__type == __AST_FUNCTION_CALL__) {
        vector<AST*> params;
        AST_FunctionCall* af = (AST_FunctionCall*) funct;

        for (int i = 0; i < af->__parameters.size(); i++) {
            gc<DataType> d = connector->__get_value(af->__parameters.at(i), caller_id);
            gc<DataType> e;

            if (d->__type == __TYPE_DOUBLE__) {
                e = new_gc<DataType>(__TYPE_DOUBLE__);
                e->__value_double = d->__value_double;
            } else if (d->__type == __TYPE_BOOL__) {
                e = new_gc<DataType>(__TYPE_BOOL__);
                e->__value_bool = d->__value_bool;
            } else if (d->__type == __TYPE_STRING__) {
                e = new_gc<DataType>(__TYPE_STRING__);
                e->__value_string = d->__value_string;
            } else if (d->__type == __TYPE_ARRAY__) {
                e = new_gc<DataType>(__TYPE_ARRAY__);
                e->__value_array = d->__value_array;
            } else if (d->__type == __TYPE_OBJECT__) {
                e = new_gc<DataType>(__TYPE_OBJECT__);
                e->__value_object = d->__value_object;
            }

            params.push_back(new AST_Value(e));
        }

        AST_FunctionCall* f = new AST_FunctionCall(af->__identifier);
        f->__address = af->__address;
        f->__parameters = params;

        func = f;
    } else {
        connector->__error_message("gui::addevent(): parameter #2 cannot be an object function call");
    }
    
    if (gui->__type == __GUI_WINDOW__) {
        if (event == __GUI_EVENT_ACTIVATE__) {
            ((GUI_Window*) gui)->__event_activated = func;
        } else if (event == __GUI_EVENT_DEACTIVATE__) {
            ((GUI_Window*) gui)->__event_deactivated = func;
        } else if (event == __GUI_EVENT_RESIZE__) {
            ((GUI_Window*) gui)->__event_resized = func;
        } else if (event == __GUI_EVENT_MINIMIZE__) {
            ((GUI_Window*) gui)->__event_minimized = func;
        } else if (event == __GUI_EVENT_MAXIMIZE__) {
            ((GUI_Window*) gui)->__event_maximized = func;
        } else if (event == __GUI_EVENT_CLOSE__) {
            ((GUI_Window*) gui)->__event_closed = func;
        
        } else if (event == __GUI_EVENT_MOUSE_LEFT_UP__) {
            gui->__event_mouse_left_up = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_DOWN__) {
            gui->__event_mouse_left_down = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_UP__) {
            gui->__event_mouse_right_up = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_DOWN__) {
            gui->__event_mouse_right_down = func;
        } else if (event == __GUI_EVENT_MOUSE_ENTER__) {
            gui->__event_mouse_enter = func;
        } else if (event == __GUI_EVENT_MOUSE_LEAVE__) {
            gui->__event_mouse_leave = func;
        } else if (event == __GUI_EVENT_MOUSE_OVER__) {
            gui->__event_mouse_over = func;
        } else if (event == __GUI_EVENT_KEY_UP__) {
            gui->__event_key_up = func;
        } else if (event == __GUI_EVENT_KEY_DOWN__) {
            gui->__event_key_down = func;

        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_window");
        }
    } else if (gui->__type == __GUI_PANEL__) {
        if (event == __GUI_EVENT_MOUSE_LEFT_UP__) {
            gui->__event_mouse_left_up = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_DOWN__) {
            gui->__event_mouse_left_down = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_UP__) {
            gui->__event_mouse_right_up = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_DOWN__) {
            gui->__event_mouse_right_down = func;
        } else if (event == __GUI_EVENT_MOUSE_ENTER__) {
            gui->__event_mouse_enter = func;
        } else if (event == __GUI_EVENT_MOUSE_LEAVE__) {
            gui->__event_mouse_leave = func;
        } else if (event == __GUI_EVENT_MOUSE_OVER__) {
            gui->__event_mouse_over = func;
        } else if (event == __GUI_EVENT_KEY_UP__) {
            gui->__event_key_up = func;
        } else if (event == __GUI_EVENT_KEY_DOWN__) {
            gui->__event_key_down = func;

        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_panel");
        }
    } else if (gui->__type == __GUI_TAB__) {
        if (event == __GUI_EVENT_TAB_CHANGE__) {
            ((GUI_Tab*) gui)->__event_tab_changed = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_UP__) {
            gui->__event_mouse_left_up = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_DOWN__) {
            gui->__event_mouse_left_down = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_UP__) {
            gui->__event_mouse_right_up = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_DOWN__) {
            gui->__event_mouse_right_down = func;
        } else if (event == __GUI_EVENT_MOUSE_ENTER__) {
            gui->__event_mouse_enter = func;
        } else if (event == __GUI_EVENT_MOUSE_LEAVE__) {
            gui->__event_mouse_leave = func;
        } else if (event == __GUI_EVENT_MOUSE_OVER__) {
            gui->__event_mouse_over = func;
        } else if (event == __GUI_EVENT_KEY_UP__) {
            gui->__event_key_up = func;
        } else if (event == __GUI_EVENT_KEY_DOWN__) {
            gui->__event_key_down = func;
        
        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_tab");
        }
    } else if (gui->__type == __GUI_BUTTON__) {
        if (event == __GUI_EVENT_CLICK__) {
            gui->__event_click = func;
        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_button");
        }
    } else if (gui->__type == __GUI_LABEL__) {
        if (event == __GUI_EVENT_MOUSE_LEFT_UP__) {
            gui->__event_mouse_left_up = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_DOWN__) {
            gui->__event_mouse_left_down = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_UP__) {
            gui->__event_mouse_right_up = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_DOWN__) {
            gui->__event_mouse_right_down = func;
        } else if (event == __GUI_EVENT_MOUSE_ENTER__) {
            gui->__event_mouse_enter = func;
        } else if (event == __GUI_EVENT_MOUSE_LEAVE__) {
            gui->__event_mouse_leave = func;
        } else if (event == __GUI_EVENT_MOUSE_OVER__) {
            gui->__event_mouse_over = func;
        } else if (event == __GUI_EVENT_KEY_UP__) {
            gui->__event_key_up = func;
        } else if (event == __GUI_EVENT_KEY_DOWN__) {
            gui->__event_key_down = func;

        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_label");
        }
    } else if (gui->__type == __GUI_TEXTBOX__) {
        if (event == __GUI_EVENT_CHANGE__) {
            ((GUI_TextBox*) gui)->__event_changed = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_UP__) {
            gui->__event_mouse_left_up = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_DOWN__) {
            gui->__event_mouse_left_down = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_UP__) {
            gui->__event_mouse_right_up = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_DOWN__) {
            gui->__event_mouse_right_down = func;
        } else if (event == __GUI_EVENT_MOUSE_ENTER__) {
            gui->__event_mouse_enter = func;
        } else if (event == __GUI_EVENT_MOUSE_LEAVE__) {
            gui->__event_mouse_leave = func;
        } else if (event == __GUI_EVENT_MOUSE_OVER__) {
            gui->__event_mouse_over = func;
        } else if (event == __GUI_EVENT_KEY_UP__) {
            gui->__event_key_up = func;
        } else if (event == __GUI_EVENT_KEY_DOWN__) {
            gui->__event_key_down = func;

        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_textbox");
        }
    } else if (gui->__type == __GUI_TEXTAREA__) {
        if (event == __GUI_EVENT_CHANGE__) {
            ((GUI_TextArea*) gui)->__event_changed = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_UP__) {
            gui->__event_mouse_left_up = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_DOWN__) {
            gui->__event_mouse_left_down = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_UP__) {
            gui->__event_mouse_right_up = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_DOWN__) {
            gui->__event_mouse_right_down = func;
        } else if (event == __GUI_EVENT_MOUSE_ENTER__) {
            gui->__event_mouse_enter = func;
        } else if (event == __GUI_EVENT_MOUSE_LEAVE__) {
            gui->__event_mouse_leave = func;
        } else if (event == __GUI_EVENT_MOUSE_OVER__) {
            gui->__event_mouse_over = func;
        } else if (event == __GUI_EVENT_KEY_UP__) {
            gui->__event_key_up = func;
        } else if (event == __GUI_EVENT_KEY_DOWN__) {
            gui->__event_key_down = func;

        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_textarea");
        }
    } else if (gui->__type == __GUI_RADIOBOX__) {
        if (event == __GUI_EVENT_CHANGE__) {
            ((GUI_RadioBox*) gui)->__event_changed = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_UP__) {
            gui->__event_mouse_left_up = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_DOWN__) {
            gui->__event_mouse_left_down = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_UP__) {
            gui->__event_mouse_right_up = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_DOWN__) {
            gui->__event_mouse_right_down = func;
        } else if (event == __GUI_EVENT_MOUSE_ENTER__) {
            gui->__event_mouse_enter = func;
        } else if (event == __GUI_EVENT_MOUSE_LEAVE__) {
            gui->__event_mouse_leave = func;
        } else if (event == __GUI_EVENT_MOUSE_OVER__) {
            gui->__event_mouse_over = func;
        } else if (event == __GUI_EVENT_KEY_UP__) {
            gui->__event_key_up = func;
        } else if (event == __GUI_EVENT_KEY_DOWN__) {
            gui->__event_key_down = func;

        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_radiobox");
        }
    } else if (gui->__type == __GUI_CHECKBOX__) {
        if (event == __GUI_EVENT_CHANGE__) {
            ((GUI_CheckBox*) gui)->__event_changed = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_UP__) {
            gui->__event_mouse_left_up = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_DOWN__) {
            gui->__event_mouse_left_down = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_UP__) {
            gui->__event_mouse_right_up = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_DOWN__) {
            gui->__event_mouse_right_down = func;
        } else if (event == __GUI_EVENT_MOUSE_ENTER__) {
            gui->__event_mouse_enter = func;
        } else if (event == __GUI_EVENT_MOUSE_LEAVE__) {
            gui->__event_mouse_leave = func;
        } else if (event == __GUI_EVENT_MOUSE_OVER__) {
            gui->__event_mouse_over = func;
        } else if (event == __GUI_EVENT_KEY_UP__) {
            gui->__event_key_up = func;
        } else if (event == __GUI_EVENT_KEY_DOWN__) {
            gui->__event_key_down = func;

        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_checkbox");
        }
    } else if (gui->__type == __GUI_LISTBOX__) {
        if (event == __GUI_EVENT_CLICK__) {
            ((GUI_ListBox*) gui)->__event_click = func;
        } else if (event == __GUI_EVENT_DOUBLE_CLICK__) {
            ((GUI_ListBox*) gui)->__event_double_click = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_UP__) {
            gui->__event_mouse_left_up = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_DOWN__) {
            gui->__event_mouse_left_down = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_UP__) {
            gui->__event_mouse_right_up = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_DOWN__) {
            gui->__event_mouse_right_down = func;
        } else if (event == __GUI_EVENT_MOUSE_ENTER__) {
            gui->__event_mouse_enter = func;
        } else if (event == __GUI_EVENT_MOUSE_LEAVE__) {
            gui->__event_mouse_leave = func;
        } else if (event == __GUI_EVENT_MOUSE_OVER__) {
            gui->__event_mouse_over = func;
        } else if (event == __GUI_EVENT_KEY_UP__) {
            gui->__event_key_up = func;
        } else if (event == __GUI_EVENT_KEY_DOWN__) {
            gui->__event_key_down = func;

        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_listbox");
        }
    } else if (gui->__type == __GUI_COMBOBOX__) {
        if (event == __GUI_EVENT_CLICK__) {
            ((GUI_ComboBox*) gui)->__event_click = func;
        } else if (event == __GUI_EVENT_CHANGE__) {
            ((GUI_ComboBox*) gui)->__event_changed = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_UP__) {
            gui->__event_mouse_left_up = func;
        } else if (event == __GUI_EVENT_MOUSE_LEFT_DOWN__) {
            gui->__event_mouse_left_down = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_UP__) {
            gui->__event_mouse_right_up = func;
        } else if (event == __GUI_EVENT_MOUSE_RIGHT_DOWN__) {
            gui->__event_mouse_right_down = func;
        } else if (event == __GUI_EVENT_MOUSE_ENTER__) {
            gui->__event_mouse_enter = func;
        } else if (event == __GUI_EVENT_MOUSE_LEAVE__) {
            gui->__event_mouse_leave = func;
        } else if (event == __GUI_EVENT_MOUSE_OVER__) {
            gui->__event_mouse_over = func;
        } else if (event == __GUI_EVENT_KEY_UP__) {
            gui->__event_key_up = func;
        } else if (event == __GUI_EVENT_KEY_DOWN__) {
            gui->__event_key_down = func;

        } else {
            connector->__error_message("gui::addevent(): this event is not supported by gui_combobox");
        }
    }

    // TODO: Other future GUIs
}

gc<DataType> Module::__call(uint_fast16_t& func_id, AST* func, gc<Object> obj, uint_fast32_t& caller_id) {
    gc<DataType> result = new_gc<DataType>(__TYPE_NULL__);
    vector<AST*> params;

    if (func_id != 1) {
        params = ((AST_FunctionCall*) func)->__parameters;
    }


    // Start of GUI components

    if (func_id == __gui_window) {
        string title = "";
        int width = 220;
        int height = 160;
        bool resizable = true;
        bool minimisable = true;
        bool closable = true;

        if (params.size() > 0) {
            gc<DataType> d = connector->__get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_STRING__) connector->__error_message("gui_window(): parameter #1 must be a string");
            title = d->__value_string;

            connector->__remove_garbage(params.at(0), d);
        }
        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_window(): parameter #2 must be a number");
            width = e->__value_double;

            connector->__remove_garbage(params.at(1), e);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_window(): parameter #3 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_window(): parameter #4 must be a boolean");
            resizable = f->__value_bool;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_window(): parameter #5 must be a boolean");
            minimisable = f->__value_bool;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_window(): parameter #6 must be a boolean");
            closable = f->__value_bool;

            connector->__remove_garbage(params.at(5), f);
        }

        return __create_window(title, width, height, resizable, minimisable, closable, caller_id);
    
    } else if (func_id == __gui_menubar) {
        if (params.size() < 1) connector->__error_message_param("gui_menubar");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_menubar(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_menubar(): parameter #1 must be a gui object");

        GUI* parent = (GUI*) d->__value_object->__holder_pointer;
        connector->__remove_garbage(params.at(0), d);
        
        return __create_menubar(parent);
    } else if (func_id == __gui_menu) {
        return __create_menu();
    
    } else if (func_id == __gui_stack) {
        if (params.size() < 2) connector->__error_message_params("gui_stack", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_stack(): parameter #1 must be a number");
        if (e->__type != __TYPE_OBJECT__) connector->__error_message("gui_stack(): parameter #2 must be an object");
        if (e->__value_object->__name.substr(0, 3) != "gui" && e->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_stack(): parameter #2 must be a gui object");

        bool vertical = d->__value_double == 0;
        GUI* parent = (GUI*) e->__value_object->__holder_pointer;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        
        return __create_stack(vertical, parent);
    } else if (func_id == __gui_grid) {
        if (params.size() < 3) connector->__error_message_params("gui_grid", 3);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_grid(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_grid(): parameter #2 must be a number");
        if (f->__type != __TYPE_OBJECT__) connector->__error_message("gui_grid(): parameter #3 must be an object");
        if (f->__value_object->__name.substr(0, 3) != "gui" && f->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_grid(): parameter #3 must be a gui object");

        int rows = d->__value_double;
        int cols = e->__value_double;
        int vertical_gap = 0;
        int horizontal_gap = 0;
        bool grow_all = false;
        GUI* parent = (GUI*) f->__value_object->__holder_pointer;

        if (params.size() > 3) {
            gc<DataType> g = connector->__get_value(params.at(3), caller_id);
            if (g->__type != __TYPE_DOUBLE__) connector->__error_message("gui_grid(): parameter #4 must be a number");
            vertical_gap = g->__value_double;

            connector->__remove_garbage(params.at(3), g);
        }
        if (params.size() > 4) {
            gc<DataType> g = connector->__get_value(params.at(4), caller_id);
            if (g->__type != __TYPE_DOUBLE__) connector->__error_message("gui_grid(): parameter #5 must be a number");
            horizontal_gap = g->__value_double;

            connector->__remove_garbage(params.at(4), g);
        }
        if (params.size() > 5) {
            gc<DataType> g = connector->__get_value(params.at(5), caller_id);
            if (g->__type != __TYPE_BOOL__) connector->__error_message("gui_grid(): parameter #6 must be a boolean");
            grow_all = g->__value_bool;

            connector->__remove_garbage(params.at(5), g);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
        
        return __create_grid(rows, cols, parent, vertical_gap, horizontal_gap, grow_all);
    
    } else if (func_id == __gui_panel) {
        if (params.size() < 1) connector->__error_message_param("gui_panel");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_panel(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_panel(): parameter #1 must be a gui object");

        GUI* parent = (GUI*) d->__value_object->__holder_pointer;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        bool as_canvas = false;
        
        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel(): parameter #2 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel(): parameter #3 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel(): parameter #4 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel(): parameter #5 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_panel(): parameter #6 must be a boolean");
            as_canvas = f->__value_bool;

            connector->__remove_garbage(params.at(5), f);
        }

        connector->__remove_garbage(params.at(0), d);

        return __create_panel(parent, x, y, width, height, as_canvas, caller_id);
    } else if (func_id == __gui_labeled_panel) {
        if (params.size() < 2) connector->__error_message_params("gui_labeled_panel", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_labeled_panel(): parameter #1 must be a string");
        if (e->__type != __TYPE_OBJECT__) connector->__error_message("gui_labeled_panel(): parameter #2 must be an object");
        if (e->__value_object->__name.substr(0, 3) != "gui" && e->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_labeled_panel(): parameter #2 must be a gui object");

        GUI* parent = (GUI*) e->__value_object->__holder_pointer;
        string text = d->__value_string;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_labeled_panel(): parameter #3 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_labeled_panel(): parameter #4 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_labeled_panel(): parameter #5 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_labeled_panel(): parameter #6 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(5), f);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return __create_labeled_panel(parent, text, x, y, width, height, caller_id);
    } else if (func_id == __gui_tab) {
        if (params.size() < 1) connector->__error_message_param("gui_tab");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_tab(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_tab(): parameter #1 must be a gui object");

        GUI* parent = (GUI*) d->__value_object->__holder_pointer;
        string text = d->__value_string;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        
        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_tab(): parameter #2 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_tab(): parameter #3 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_tab(): parameter #4 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_tab(): parameter #5 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }

        connector->__remove_garbage(params.at(0), d);

        return __create_tab(parent, x, y, width, height, caller_id);
    } else if (func_id == __gui_button) {
        if (params.size() < 2) connector->__error_message_params("gui_button", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_button(): parameter #1 must be a string");
        if (e->__type != __TYPE_OBJECT__) connector->__error_message("gui_button(): parameter #2 must be an object");
        if (e->__value_object->__name.substr(0, 3) != "gui" && e->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_button(): parameter #2 must be a gui object");

        GUI* parent = (GUI*) e->__value_object->__holder_pointer;
        string text = d->__value_string;
        int x = 0;
        int y = 0;
        int width = 80;
        int height = 26;
        
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_button(): parameter #3 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_button(): parameter #4 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_button(): parameter #5 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_button(): parameter #6 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(5), f);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return __create_button(parent, text, x, y, width, height, caller_id);
    } else if (func_id == __gui_label) {
        if (params.size() < 2) connector->__error_message_params("gui_label", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_label(): parameter #1 must be a string");
        if (e->__type != __TYPE_OBJECT__) connector->__error_message("gui_label(): parameter #2 must be an object");
        if (e->__value_object->__name.substr(0, 3) != "gui" && e->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_label(): parameter #2 must be a gui object");

        GUI* parent = (GUI*) e->__value_object->__holder_pointer;
        string text = d->__value_string;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        int alignment = wxALIGN_LEFT;
        
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_label(): parameter #3 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_label(): parameter #4 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_label(): parameter #5 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_label(): parameter #6 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(5), f);
        }
        if (params.size() > 6) {
            gc<DataType> f = connector->__get_value(params.at(6), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_label(): parameter #7 must be a number");
            alignment = f->__value_double;

            connector->__remove_garbage(params.at(6), f);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return __create_label(parent, text, x, y, width, height, alignment, caller_id);
    } else if (func_id == __gui_textbox) {
        if (params.size() < 2) connector->__error_message_params("gui_textbox", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_textbox(): parameter #1 must be a string");
        if (e->__type != __TYPE_OBJECT__) connector->__error_message("gui_textbox(): parameter #2 must be an object");
        if (e->__value_object->__name.substr(0, 3) != "gui" && e->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_textbox(): parameter #2 must be a gui object");

        GUI* parent = (GUI*) e->__value_object->__holder_pointer;
        string text = d->__value_string;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        bool is_password = false;

        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textbox(): parameter #3 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textbox(): parameter #4 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textbox(): parameter #5 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textbox(): parameter #6 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(5), f);
        }
        if (params.size() > 6) {
            gc<DataType> f = connector->__get_value(params.at(6), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_textbox(): parameter #7 must be a boolean");
            is_password = f->__value_bool;

            connector->__remove_garbage(params.at(6), f);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return __create_textbox(parent, text, x, y, width, height, is_password, caller_id);
    } else if (func_id == __gui_textarea) {
        if (params.size() < 2) connector->__error_message_params("gui_textarea", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_textarea(): parameter #1 must be a string");
        if (e->__type != __TYPE_OBJECT__) connector->__error_message("gui_textarea(): parameter #2 must be an object");
        if (e->__value_object->__name.substr(0, 3) != "gui" && e->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_textarea(): parameter #2 must be a gui object");

        GUI* parent = (GUI*) e->__value_object->__holder_pointer;
        string text = d->__value_string;
        int x = 0;
        int y = 0;
        int width = 160;
        int height = 80;
        bool wrap = true;
        
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textarea(): parameter #3 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textarea(): parameter #4 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textarea(): parameter #5 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textarea(): parameter #6 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(5), f);
        }
        if (params.size() > 6) {
            gc<DataType> f = connector->__get_value(params.at(6), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_textarea(): parameter #7 must be a boolean");
            wrap = f->__value_bool;

            connector->__remove_garbage(params.at(6), f);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return __create_textarea(parent, text, x, y, width, height, wrap, caller_id);
    } else if (func_id == __gui_checkbox) {
        if (params.size() < 2) connector->__error_message_params("gui_checkbox", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_checkbox(): parameter #1 must be a string");
        if (e->__type != __TYPE_OBJECT__) connector->__error_message("gui_checkbox(): parameter #2 must be an object");
        if (e->__value_object->__name.substr(0, 3) != "gui" && e->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_checkbox(): parameter #2 must be a gui object");

        GUI* parent = (GUI*) e->__value_object->__holder_pointer;
        string text = d->__value_string;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        bool checked = false;
        
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_checkbox(): parameter #3 must be a boolean");
            checked = f->__value_bool;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_checkbox(): parameter #4 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_checkbox(): parameter #5 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_checkbox(): parameter #6 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(5), f);
        }
        if (params.size() > 6) {
            gc<DataType> f = connector->__get_value(params.at(6), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_checkbox(): parameter #7 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(6), f);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return __create_checkbox(parent, text, checked, x, y, width, height, caller_id);
    } else if (func_id == __gui_radiobox) {
        if (params.size() < 2) connector->__error_message_params("gui_radiobox", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_radiobox(): parameter #1 must be a string");
        if (e->__type != __TYPE_OBJECT__) connector->__error_message("gui_radiobox(): parameter #2 must be an object");
        if (e->__value_object->__name.substr(0, 3) != "gui" && e->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_radiobox(): parameter #2 must be a gui object");

        GUI* parent = (GUI*) e->__value_object->__holder_pointer;
        string text = d->__value_string;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        bool start_group = false;
        bool checked = false;
        
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_radiobox(): parameter #3 must be a boolean");
            start_group = f->__value_bool;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_radiobox(): parameter #4 must be a boolean");
            checked = f->__value_bool;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_radiobox(): parameter #5 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_radiobox(): parameter #6 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(5), f);
        }
        if (params.size() > 6) {
            gc<DataType> f = connector->__get_value(params.at(6), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_radiobox(): parameter #7 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(6), f);
        }
        if (params.size() > 7) {
            gc<DataType> f = connector->__get_value(params.at(7), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_radiobox(): parameter #8 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(7), f);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return __create_radiobox(parent, text, start_group, checked, x, y, width, height, caller_id);
    } else if (func_id == __gui_listbox) {
        if (params.size() < 1) connector->__error_message_param("gui_listbox");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_listbox(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_listbox(): parameter #1 must be a gui object");

        GUI* parent = (GUI*) d->__value_object->__holder_pointer;
        int x = 0;
        int y = 0;
        int width = 160;
        int height = 80;
        gc<Array> list = connector->__create_array(0)->__value_array;
        bool multiple_selection = false;
        
        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_ARRAY__) connector->__error_message("gui_listbox(): parameter #2 must be an array");
            list = f->__value_array;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_listbox(): parameter #3 must be a boolean");
            multiple_selection = f->__value_bool;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_listbox(): parameter #4 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_listbox(): parameter #5 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_listbox(): parameter #6 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(5), f);
        }
        if (params.size() > 6) {
            gc<DataType> f = connector->__get_value(params.at(6), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_listbox(): parameter #7 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(6), f);
        }

        connector->__remove_garbage(params.at(0), d);

        return __create_listbox(parent, list, multiple_selection, x, y, width, height, caller_id);
    } else if (func_id == __gui_combobox) {
        if (params.size() < 1) connector->__error_message_param("gui_combobox");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_combobox(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_combobox(): parameter #1 must be a gui object");

        GUI* parent = (GUI*) d->__value_object->__holder_pointer;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        gc<Array> list = connector->__create_array(0)->__value_array;
        bool editable = false;
        
        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_ARRAY__) connector->__error_message("gui_combobox(): parameter #2 must be an array");
            list = f->__value_array;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_combobox(): parameter #3 must be a boolean");
            editable = f->__value_bool;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_combobox(): parameter #4 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_combobox(): parameter #5 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_combobox(): parameter #6 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(5), f);
        }
        if (params.size() > 6) {
            gc<DataType> f = connector->__get_value(params.at(6), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_combobox(): parameter #7 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(6), f);
        }

        connector->__remove_garbage(params.at(0), d);

        if (editable) {
            return __create_editable_combobox(parent, list, x, y, width, height, caller_id);
        } else {
            return __create_combobox(parent, list, x, y, width, height, caller_id);
        }
    } else if (func_id == __gui_timer) {
        if (params.size() < 2) connector->__error_message_params("gui_timer", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        AST* e = params.at(1);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_timer(): parameter #1 must be a number");
        if (e->__type != __AST_FUNCTION_CALL__ && e->__type != __AST_OBJECT_FUNCTION_CALL__) connector->__error_message("gui_timer(): parameter #2 must be a function call");

        int interval = d->__value_double;
        connector->__remove_garbage(params.at(0), d);

        return __create_timer(interval, e, caller_id);
    } else if (func_id == __gui_imagebox) {
        if (params.size() < 2) connector->__error_message_params("gui_imagebox", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_imagebox(): parameter #1 must be a string");
        if (e->__type != __TYPE_OBJECT__) connector->__error_message("gui_imagebox(): parameter #2 must be an object");
        if (e->__value_object->__name.substr(0, 3) != "gui" && e->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_imagebox(): parameter #2 must be a gui object");

        GUI* parent = (GUI*) e->__value_object->__holder_pointer;
        string path = d->__value_string;
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
        
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_imagebox(): parameter #3 must be a number");
            x = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_imagebox(): parameter #4 must be a number");
            y = f->__value_double;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_imagebox(): parameter #5 must be a number");
            width = f->__value_double;

            connector->__remove_garbage(params.at(4), f);
        }
        if (params.size() > 5) {
            gc<DataType> f = connector->__get_value(params.at(5), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_imagebox(): parameter #6 must be a number");
            height = f->__value_double;

            connector->__remove_garbage(params.at(5), f);
        }

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        return __create_imagebox(parent, path, x, y, width, height);


    // Start of GUI_Window functions

    } else if (func_id == __gui_window_show) {
        wxFrame* f = ((GUI_Window*) obj->__holder_pointer)->__holder;
        f->Show(true);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_window_close) {
        wxFrame* f = ((GUI_Window*) obj->__holder_pointer)->__holder;
        f->Close();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_window_settitle) {
        if (params.size() < 1) connector->__error_message_param("gui_window::settitle");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_window::settitle(): parameter #1 must be a string");
        
        wxFrame* f = ((GUI_Window*) obj->__holder_pointer)->__holder;
        f->SetTitle(wxString::FromUTF8(d->__value_string.c_str()));

        result->__type = __TYPE_STRING__;
        result->__value_string = d->__value_string;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_window_gettitle) {
        wxFrame* f = ((GUI_Window*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_STRING__;
        result->__value_string = f->GetTitle().ToUTF8();
    } else if (func_id == __gui_window_isminimised) {
        wxFrame* f = ((GUI_Window*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_BOOL__;
        result->__value_bool = f->IsIconized();
    } else if (func_id == __gui_window_ismaximised) {
        wxFrame* f = ((GUI_Window*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_BOOL__;
        result->__value_bool = f->IsMaximized();
    } else if (func_id == __gui_window_setfullscreen) {
        if (params.size() < 1) connector->__error_message_param("gui_window::setfullscreen");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui_window::setfullscreen(): parameter #1 must be a boolean");
        
        wxFrame* f = ((GUI_Window*) obj->__holder_pointer)->__holder;
        f->ShowFullScreen(d->__value_bool);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_window_isfullscreen) {
        wxFrame* f = ((GUI_Window*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_BOOL__;
        result->__value_bool = f->IsFullScreen();
    

    // Start of GUI_MenuBar & GUI_Menu functions

    } else if (func_id == __gui_menubar_append) {
        if (params.size() < 2) connector->__error_message_params("gui_menubar::append", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_menubar::append(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_menubar::append(): parameter #1 must be a gui object");
        if (e->__type != __TYPE_STRING__) connector->__error_message("gui_menubar::append(): parameter #2 must be a string");

        GUI* p = (GUI*) d->__value_object->__holder_pointer;
        GUI_MenuBar* m = (GUI_MenuBar*) obj->__holder_pointer;
        wxMenuBar* g = m->__holder;

        if (p->__type != __GUI_MENU__) {
            connector->__error_message("gui_menubar::append(): parameter #1 must be a gui_menu object");
        }

        g->Append(((GUI_Menu*) p)->__holder, _(e->__value_string));

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_menubar_insert) {
        if (params.size() < 3) connector->__error_message_params("gui_menubar::insert", 3);
        gc<DataType> f = connector->__get_value(params.at(0), caller_id);
        gc<DataType> d = connector->__get_value(params.at(1), caller_id);
        gc<DataType> e = connector->__get_value(params.at(2), caller_id);
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menubar::insert(): parameter #1 must be a number");
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_menubar::insert(): parameter #2 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_menubar::insert(): parameter #2 must be a gui object");
        if (e->__type != __TYPE_STRING__) connector->__error_message("gui_menubar::insert(): parameter #3 must be a string");

        GUI* p = (GUI*) d->__value_object->__holder_pointer;
        GUI_MenuBar* m = (GUI_MenuBar*) obj->__holder_pointer;
        wxMenuBar* g = m->__holder;

        if (p->__type != __GUI_MENU__) {
            connector->__error_message("gui_menubar::insert(): parameter #2 must be a gui_menu object");
        }

        g->Insert(f->__value_double, ((GUI_Menu*) p)->__holder, _(e->__value_string));

        connector->__remove_garbage(params.at(0), f);
        connector->__remove_garbage(params.at(1), d);
        connector->__remove_garbage(params.at(2), e);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_menubar_remove) {
        if (params.size() < 1) connector->__error_message_param("gui_menubar::remove");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menubar::remove(): parameter #1 must be a number");
        
        GUI_MenuBar* m = (GUI_MenuBar*) obj->__holder_pointer;
        wxMenuBar* g = m->__holder;

        g->Remove(d->__value_double);

        connector->__remove_garbage(params.at(0), d);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    
    } else if (func_id == __gui_menu_append) {
        if (params.size() < 1) connector->__error_message_param("gui_menu::append");
        gc<DataType> dd = connector->__get_value(params.at(0), caller_id);
        if (dd->__type != __TYPE_STRING__) connector->__error_message("gui_menu::append(): parameter #1 must be a string");

        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        string label = dd->__value_string;
        int menu_id = 0;
        int type = wxITEM_NORMAL;
        AST* func = NULL;
        bool special = false;

        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::append(): parameter #2 must be a number");
            type = f->__value_double;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            AST* fe = params.at(2);
            if (fe->__type != __AST_FUNCTION_CALL__) connector->__error_message("gui_menu::append(): parameter #3 must be a function call");
            
            vector<AST*> params;
            AST_FunctionCall* af = (AST_FunctionCall*) fe;

            for (int i = 0; i < af->__parameters.size(); i++) {
                gc<DataType> d = connector->__get_value(af->__parameters.at(i), caller_id);
                gc<DataType> e;

                if (d->__type == __TYPE_DOUBLE__) {
                    e = new_gc<DataType>(__TYPE_DOUBLE__);
                    e->__value_double = d->__value_double;
                } else if (d->__type == __TYPE_BOOL__) {
                    e = new_gc<DataType>(__TYPE_BOOL__);
                    e->__value_bool = d->__value_bool;
                } else if (d->__type == __TYPE_STRING__) {
                    e = new_gc<DataType>(__TYPE_STRING__);
                    e->__value_string = d->__value_string;
                } else if (d->__type == __TYPE_ARRAY__) {
                    e = new_gc<DataType>(__TYPE_ARRAY__);
                    e->__value_array = d->__value_array;
                } else if (d->__type == __TYPE_OBJECT__) {
                    e = new_gc<DataType>(__TYPE_OBJECT__);
                    e->__value_object = d->__value_object;
                } else {
                    e = new_gc<DataType>(__TYPE_NULL__);
                }

                params.push_back(new AST_Value(e));
            }

            AST_FunctionCall* f = new AST_FunctionCall(af->__identifier);
            f->__address = af->__address;
            f->__parameters = params;

            func = f;
        }

        if (type == wxID_EXIT || type == wxID_ABOUT || type == wxID_PREFERENCES) {
            menu_id = type;
            special = true;
            g->Append(type, _(label));
        } else {
            menu_id = __menu_n++;
            wxItemKind k = (wxItemKind) type;
            g->Append(menu_id, _(label), "", k);
        }

        if (func != NULL) {
            __menu_action[menu_id] = func;
            __menu_action_caller_id[menu_id] = caller_id;
            
            if (!special) g->Bind(wxEVT_MENU, &__event_gui_menu, menu_id);
        }

        connector->__remove_garbage(params.at(0), dd);

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = menu_id;
    } else if (func_id == __gui_menu_appendseparator) {
        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        int menu_id = __menu_n++;
        g->Append(menu_id, "", "", wxITEM_SEPARATOR);

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = menu_id;
    } else if (func_id == __gui_menu_appendsubmenu) {
        if (params.size() < 2) connector->__error_message_params("gui_menu::appendsubmenu", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_menu::appendsubmenu(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_menu::appendsubmenu(): parameter #1 must be a gui object");
        if (e->__type != __TYPE_STRING__) connector->__error_message("gui_menu::appendsubmenu(): parameter #2 must be a string");

        GUI* p = (GUI*) d->__value_object->__holder_pointer;
        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        if (p->__type != __GUI_MENU__) {
            connector->__error_message("gui_menu::appendsubmenu(): parameter #1 must be a gui_menu object");
        }

        int menu_id = __menu_n++;
        g->Append(menu_id, _(e->__value_string), ((GUI_Menu*) p)->__holder);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = menu_id;
    } else if (func_id == __gui_menu_insert) {
        if (params.size() < 2) connector->__error_message_params("gui_menu::insert", 2);
        gc<DataType> de = connector->__get_value(params.at(0), caller_id);
        gc<DataType> dd = connector->__get_value(params.at(1), caller_id);
        if (de->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::insert(): parameter #1 must be a number");
        if (dd->__type != __TYPE_STRING__) connector->__error_message("gui_menu::insert(): parameter #2 must be a string");

        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        int pos = de->__value_double;
        string label = dd->__value_string;
        int menu_id = 0;
        int type = wxITEM_NORMAL;
        AST* func = NULL;
        bool special = false;

        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::insert(): parameter #3 must be a number");
            type = f->__value_double;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 3) {
            AST* fe = params.at(3);
            if (fe->__type != __AST_FUNCTION_CALL__) connector->__error_message("gui_menu::insert(): parameter #4 must be a function call");
            
            vector<AST*> params;
            AST_FunctionCall* af = (AST_FunctionCall*) fe;

            for (int i = 0; i < af->__parameters.size(); i++) {
                gc<DataType> d = connector->__get_value(af->__parameters.at(i), caller_id);
                gc<DataType> e;

                if (d->__type == __TYPE_DOUBLE__) {
                    e = new_gc<DataType>(__TYPE_DOUBLE__);
                    e->__value_double = d->__value_double;
                } else if (d->__type == __TYPE_BOOL__) {
                    e = new_gc<DataType>(__TYPE_BOOL__);
                    e->__value_bool = d->__value_bool;
                } else if (d->__type == __TYPE_STRING__) {
                    e = new_gc<DataType>(__TYPE_STRING__);
                    e->__value_string = d->__value_string;
                } else if (d->__type == __TYPE_ARRAY__) {
                    e = new_gc<DataType>(__TYPE_ARRAY__);
                    e->__value_array = d->__value_array;
                } else if (d->__type == __TYPE_OBJECT__) {
                    e = new_gc<DataType>(__TYPE_OBJECT__);
                    e->__value_object = d->__value_object;
                } else {
                    e = new_gc<DataType>(__TYPE_NULL__);
                }

                params.push_back(new AST_Value(e));
            }

            AST_FunctionCall* f = new AST_FunctionCall(af->__identifier);
            f->__address = af->__address;
            f->__parameters = params;

            func = f;
        }

        if (type == wxID_EXIT || type == wxID_ABOUT || type == wxID_PREFERENCES) {
            menu_id = type;
            special = true;
            g->Insert(pos, type, _(label));
        } else {
            menu_id = __menu_n++;
            wxItemKind k = (wxItemKind) type;
            g->Insert(pos, menu_id, _(label), "", k);
        }

        if (func != NULL) {
            __menu_action[menu_id] = func;
            __menu_action_caller_id[menu_id] = caller_id;
            
            if (!special) g->Bind(wxEVT_MENU, &__event_gui_menu, menu_id);
        }

        connector->__remove_garbage(params.at(0), de);
        connector->__remove_garbage(params.at(1), dd);

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = menu_id;
    } else if (func_id == __gui_menu_insertseparator) {
        if (params.size() < 1) connector->__error_message_param("gui_menu::insertseparator");
        gc<DataType> de = connector->__get_value(params.at(0), caller_id);
        if (de->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::insertseparator(): parameter #1 must be a number");

        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        int pos = de->__value_double;
        int menu_id = __menu_n++;

        g->Insert(pos, menu_id, "", "", wxITEM_SEPARATOR);
        connector->__remove_garbage(params.at(0), de);

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = menu_id;
    } else if (func_id == __gui_menu_insertsubmenu) {
        if (params.size() < 3) connector->__error_message_params("gui_menu::insertsubmenu", 3);
        gc<DataType> f = connector->__get_value(params.at(0), caller_id);
        gc<DataType> d = connector->__get_value(params.at(1), caller_id);
        gc<DataType> e = connector->__get_value(params.at(2), caller_id);
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::insertsubmenu(): parameter #1 must be a number");
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_menu::insertsubmenu(): parameter #2 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_menu::insertsubmenu(): parameter #2 must be a gui object");
        if (e->__type != __TYPE_STRING__) connector->__error_message("gui_menu::insertsubmenu(): parameter #3 must be a string");

        GUI* p = (GUI*) d->__value_object->__holder_pointer;
        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        if (p->__type != __GUI_MENU__) {
            connector->__error_message("gui_menu::appendsubmenu(): parameter #1 must be a gui_menu object");
        }

        int pos = f->__value_double;
        int menu_id = __menu_n++;

        g->Insert(pos, menu_id, _(e->__value_string), ((GUI_Menu*) p)->__holder);

        connector->__remove_garbage(params.at(0), f);
        connector->__remove_garbage(params.at(1), d);
        connector->__remove_garbage(params.at(2), e);

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = menu_id;
    } else if (func_id == __gui_menu_remove) {
        if (params.size() < 1) connector->__error_message_param("gui_menu::remove");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::remove(): parameter #1 must be a number");

        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        int item_id = d->__value_double;
        g->Remove(item_id);

        connector->__remove_garbage(params.at(0), d);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    
    } else if (func_id == __gui_menu_setlabel) {
        if (params.size() < 2) connector->__error_message_params("gui_menu::setlabel", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::setlabel(): parameter #1 must be a number");
        if (e->__type != __TYPE_STRING__) connector->__error_message("gui_menu::setlabel(): parameter #2 must be a string");

        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        int item_id = d->__value_double;
        string label = e->__value_string;

        g->SetLabel(item_id, _(label));

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_menu_getlabel) {
        if (params.size() < 1) connector->__error_message_param("gui_menu::getlabel");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::getlabel(): parameter #1 must be a number");

        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        int item_id = d->__value_double;
        bool complete_label = false;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("gui_menu::getlabel(): parameter #2 must be a boolean");
            complete_label = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        connector->__remove_garbage(params.at(0), d);

        result->__type = __TYPE_STRING__;
        result->__value_string = complete_label ? g->GetLabel(item_id) : g->GetLabelText(item_id);
    } else if (func_id == __gui_menu_setenable) {
        if (params.size() < 2) connector->__error_message_params("gui_menu::setenable", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::setenable(): parameter #1 must be a number");
        if (e->__type != __TYPE_BOOL__) connector->__error_message("gui_menu::setenable(): parameter #2 must be a boolean");

        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        int item_id = d->__value_double;
        bool enable = e->__value_bool;

        g->Enable(item_id, enable);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_menu_isenable) {
        if (params.size() < 1) connector->__error_message_param("gui_menu::isenable");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::isenable(): parameter #1 must be a number");

        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        int item_id = d->__value_double;
        connector->__remove_garbage(params.at(0), d);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = g->IsEnabled(item_id);
    } else if (func_id == __gui_menu_setchecked) {
        if (params.size() < 2) connector->__error_message_params("gui_menu::setchecked", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::setchecked(): parameter #1 must be a number");
        if (e->__type != __TYPE_BOOL__) connector->__error_message("gui_menu::setchecked(): parameter #2 must be a boolean");

        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        int item_id = d->__value_double;
        bool enable = e->__value_bool;

        g->Check(item_id, enable);

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_menu_ischecked) {
        if (params.size() < 1) connector->__error_message_param("gui_menu::ischecked");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_menu::ischecked(): parameter #1 must be a number");

        GUI_Menu* m = (GUI_Menu*) obj->__holder_pointer;
        wxMenu* g = m->__holder;

        int item_id = d->__value_double;
        connector->__remove_garbage(params.at(0), d);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = g->IsChecked(item_id);


    // Start of GUI_Stack functions

    } else if (func_id == __gui_stack_add) {
        if (params.size() < 1) connector->__error_message_param("gui_stack::add");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_stack::add(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_stack::add(): parameter #1 must be a gui object");

        GUI* p = (GUI*) d->__value_object->__holder_pointer;
        GUI_Stack* s = (GUI_Stack*) obj->__holder_pointer;
        wxBoxSizer* g = s->__holder;
        wxWindow* f = __get_gui_holder(p);

        bool vertical_stretch = false;
        bool horizontal_stretch = false;
        int flags = 0;
        int padding = 0;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("gui_stack::add(): parameter #2 must be a boolean");
            vertical_stretch = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }
        if (params.size() > 2) {
            gc<DataType> e = connector->__get_value(params.at(2), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("gui_stack::add(): parameter #3 must be a boolean");
            horizontal_stretch = e->__value_bool;

            connector->__remove_garbage(params.at(2), e);
        }
        if (params.size() > 3) {
            gc<DataType> e = connector->__get_value(params.at(3), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_stack::add(): parameter #4 must be a number");
            flags = e->__value_double;

            connector->__remove_garbage(params.at(3), e);
        }
        if (params.size() > 4) {
            gc<DataType> e = connector->__get_value(params.at(4), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_stack::add(): parameter #5 must be a number");
            padding = e->__value_double;

            connector->__remove_garbage(params.at(4), e);
        }

        if (p->__type == __GUI_WINDOW__ || f == NULL) {
            connector->__error_message("gui_stack::add(): this gui object is cannot be added to gui_stack");
        }

        if (s->__is_vertical) {
            if (horizontal_stretch) flags = flags + wxEXPAND;
            g->Add(f, vertical_stretch ? 1 : 0, flags, padding);
        } else {
            if (vertical_stretch) flags = flags + wxEXPAND;
            g->Add(f, horizontal_stretch ? 1 : 0, flags, padding);
        }

        connector->__remove_garbage(params.at(0), d);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_stack_addspacer) {
        if (params.size() < 1) connector->__error_message_param("gui_stack::addspacer");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_stack::addspacer(): parameter #1 must be a number");

        GUI_Stack* s = (GUI_Stack*) obj->__holder_pointer;

        bool stretch = false;
        int size = d->__value_double;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("gui_stack::addspacer(): parameter #2 must be a boolean");
            stretch = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }

        if (!stretch) {
            s->__holder->AddSpacer(size);
        } else {
            s->__holder->AddStretchSpacer(1);
        }

        connector->__remove_garbage(params.at(0), d);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    
    } else if (func_id == __gui_grid_add) {
        if (params.size() < 1) connector->__error_message_param("gui_grid::add");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_grid::add(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("gui_grid::add(): parameter #1 must be a gui object");

        GUI* p = (GUI*) d->__value_object->__holder_pointer;
        GUI_Grid* s = (GUI_Grid*) obj->__holder_pointer;
        wxFlexGridSizer* g = s->__holder;
        wxWindow* f = __get_gui_holder(p);

        bool stretch = false;
        int flags = 0;
        int padding = 0;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("gui_grid::add(): parameter #2 must be a boolean");
            stretch = e->__value_bool;

            connector->__remove_garbage(params.at(1), e);
        }
        if (params.size() > 2) {
            gc<DataType> e = connector->__get_value(params.at(2), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_grid::add(): parameter #3 must be a number");
            flags = e->__value_double;

            connector->__remove_garbage(params.at(2), e);
        }
        if (params.size() > 3) {
            gc<DataType> e = connector->__get_value(params.at(3), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_grid::add(): parameter #4 must be a number");
            padding = e->__value_double;

            connector->__remove_garbage(params.at(3), e);
        }

        if (p->__type == __GUI_WINDOW__ || f == NULL) {
            connector->__error_message("gui_grid::add(): this gui object is cannot be added to gui_grid");
        }
        
        if (stretch) flags = flags + wxEXPAND;
        g->Add(f, 0, flags, padding);

        connector->__remove_garbage(params.at(0), d);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_grid_addgrowablecol) {
        if (params.size() < 1) connector->__error_message_param("gui_grid::addgrowablecol");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_grid::addgrowablecol(): parameter #1 must be a number");

        GUI_Grid* s = (GUI_Grid*) obj->__holder_pointer;

        s->__holder->AddGrowableCol(d->__value_double);
        connector->__remove_garbage(params.at(0), d);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_grid_addgrowablerow) {
        if (params.size() < 1) connector->__error_message_param("gui_grid::addgrowablerow");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_grid::addgrowablerow(): parameter #1 must be a number");

        GUI_Grid* s = (GUI_Grid*) obj->__holder_pointer;

        s->__holder->AddGrowableRow(d->__value_double);
        connector->__remove_garbage(params.at(0), d);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;


    // Start of GUI_Tab functions
    
    } else if (func_id == __gui_tab_addpage) {
        if (params.size() < 3) connector->__error_message_params("gui_tab::addpage", 3);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_tab::addpage(): parameter #1 must be a string");
        if (e->__type != __TYPE_OBJECT__) connector->__error_message("gui_tab::addpage(): parameter #2 must be an object");
        if (e->__value_object->__name != "gui_panel") connector->__error_message("gui_tab::addpage(): parameter #2 must be a gui_panel");
        if (f->__type != __TYPE_BOOL__) connector->__error_message("gui_tab::addpage(): parameter #3 must be a boolean");

        wxNotebook* g = ((GUI_Tab*) obj->__holder_pointer)->__holder;
        g->AddPage(((GUI_Panel*) e->__value_object->__holder_pointer)->__holder, wxString::FromUTF8(d->__value_string.c_str()), f->__value_bool);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
    } else if (func_id == __gui_tab_getpage) {
        wxNotebook* g = ((GUI_Tab*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ((GUI_Tab*) obj->__holder_pointer)->__tab_index;
    } else if (func_id == __gui_tab_setpage) {
        if (params.size() < 1) connector->__error_message_param("gui_tab::setpage");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_tab::setpage(): parameter #1 must be a number");
        
        wxNotebook* g = ((GUI_Tab*) obj->__holder_pointer)->__holder;
        g->SetSelection((size_t) d->__value_double);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_tab_removepage) {
        if (params.size() < 1) connector->__error_message_param("gui_tab::removepage");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_tab::removepage(): parameter #1 must be a number");
        
        wxNotebook* g = ((GUI_Tab*) obj->__holder_pointer)->__holder;
        g->RemovePage((size_t) d->__value_double);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    

    // Start of GUI_Textbox & GUI_Textarea functions

    } else if (func_id == __gui_textbox_appendtext) {
        if (params.size() < 1) connector->__error_message_param("gui_textbox::appendtext");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_textbox::appendtext(): parameter #1 must be a string");
        
        wxTextEntry* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;
        f->AppendText(wxString::FromUTF8(d->__value_string.c_str()));

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_textbox_setlocked) {
        if (params.size() < 1) connector->__error_message_param("gui_textbox::setlocked");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui_textbox::setlocked(): parameter #1 must be a boolean");
        
        wxTextEntry* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;
        f->SetEditable(!d->__value_bool);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_textbox_islocked) {
        wxTextEntry* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_BOOL__;
        result->__value_bool = !f->IsEditable();
    } else if (func_id == __gui_textbox_setmaxlength) {
        if (params.size() < 1) connector->__error_message_param("gui_textbox::setmaxlength");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textbox::setmaxlength(): parameter #1 must be a number");
        
        wxTextEntry* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;
        f->SetMaxLength(d->__value_double);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_textbox_setsel) {
        if (params.size() < 2) connector->__error_message_params("gui_textbox::setsel", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textbox::setsel(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_textbox::setsel(): parameter #2 must be a number");
        
        wxTextEntry* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;
        f->SetSelection(d->__value_double, e->__value_double);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
    } else if (func_id == __gui_textbox_getselbegin) {
        wxTextEntry* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;

        long sel_from, sel_to;
        f->GetSelection(&sel_from, &sel_to);

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = sel_from;
    } else if (func_id == __gui_textbox_getselend) {
        wxTextEntry* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;

        long sel_from, sel_to;
        f->GetSelection(&sel_from, &sel_to);

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = sel_to;
    } else if (func_id == __gui_textbox_setseltext) {
        if (params.size() < 1) connector->__error_message_param("gui_textbox::setseltext");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_textbox::setseltext(): parameter #1 must be a string");
        
        wxTextEntry* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;
        long sel_from, sel_to;
        f->GetSelection(&sel_from, &sel_to);
        f->Replace(sel_from, sel_to, wxString::FromUTF8(d->__value_string.c_str()));

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_textbox_getseltext) {
        wxTextEntry* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_STRING__;
        result->__value_string = f->GetStringSelection().ToUTF8();


    // Start of GUI_RadioBox & GUI_CheckBox functions

    } else if (func_id == __gui_radiobox_setchecked) {
        if (params.size() < 1) connector->__error_message_param("gui_radiobox::setchecked");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui_radiobox::setchecked(): parameter #1 must be a boolean");
        
        wxRadioButton* f = ((GUI_RadioBox*) obj->__holder_pointer)->__holder;
        f->SetValue(d->__value_bool);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = d->__value_bool;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_radiobox_ischecked) {
        wxRadioButton* f = ((GUI_RadioBox*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_BOOL__;
        result->__value_bool = f->GetValue();
    } else if (func_id == __gui_checkbox_setchecked) {
        if (params.size() < 1) connector->__error_message_param("gui_checkbox::setchecked");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui_checkbox::setchecked(): parameter #1 must be a boolean");
        
        wxCheckBox* f = ((GUI_CheckBox*) obj->__holder_pointer)->__holder;
        f->SetValue(d->__value_bool);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = d->__value_bool;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_checkbox_ischecked) {
        wxCheckBox* f = ((GUI_CheckBox*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_BOOL__;
        result->__value_bool = f->GetValue();
    

    // Start of GUI_ListBox & GUI_ComboBox functions

    } else if (func_id == __gui_listbox_add) {
        if (params.size() < 1) connector->__error_message_param("gui_listbox::add");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_listbox::add(): parameter #1 must be a string");
        int index = -1;

        if (params.size() > 1) {
            gc<DataType> d = connector->__get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_listbox::add(): parameter #2 must be a number");
            index = d->__value_double;

            connector->__remove_garbage(params.at(1), d);
        }
        
        wxListBox* f = ((GUI_ListBox*) obj->__holder_pointer)->__holder;
        
        if (index != -1) {
            f->Insert(wxString::FromUTF8(d->__value_string.c_str()), index);
        } else {
            f->AppendString(wxString::FromUTF8(d->__value_string.c_str()));
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_listbox_remove) {
        if (params.size() < 1) connector->__error_message_param("gui_listbox::remove");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_listbox::remove(): parameter #1 must be a number");
        
        wxListBox* f = ((GUI_ListBox*) obj->__holder_pointer)->__holder;
        f->Delete(d->__value_double);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_listbox_clear) {
        wxListBox* f = ((GUI_ListBox*) obj->__holder_pointer)->__holder;
        f->Clear();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_listbox_size) {
        wxListBox* f = ((GUI_ListBox*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = f->GetCount();
    } else if (func_id == __gui_listbox_get) {
        if (params.size() < 1) connector->__error_message_param("gui_listbox::get");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_listbox::get(): parameter #1 must be a number");
        
        wxListBox* f = ((GUI_ListBox*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_STRING__;
        result->__value_string = f->GetString(d->__value_double).ToUTF8();

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_listbox_set) {
        if (params.size() < 2) connector->__error_message_params("gui_listbox::set", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_listbox::set(): parameter #1 must be a number");
        if (e->__type != __TYPE_STRING__) connector->__error_message("gui_listbox::set(): parameter #2 must be a string");
        
        wxListBox* f = ((GUI_ListBox*) obj->__holder_pointer)->__holder;
        f->SetString(d->__value_double, wxString::FromUTF8(e->__value_string.c_str()));

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
    } else if (func_id == __gui_listbox_getindex) {
        wxListBox* f = ((GUI_ListBox*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = f->GetSelection();
    } else if (func_id == __gui_listbox_setindex) {
        if (params.size() < 1) connector->__error_message_param("gui_listbox::setindex");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_listbox::setindex(): parameter #1 must be a number");
        
        wxListBox* f = ((GUI_ListBox*) obj->__holder_pointer)->__holder;
        f->SetSelection(d->__value_double);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_listbox_getselections) {
        wxListBox* f = ((GUI_ListBox*) obj->__holder_pointer)->__holder;
        gc<DataType> d = connector->__create_array(0);

        wxArrayInt s;
        f->GetSelections(s);

        for (int i = 0; i < s.size(); i++) {
            d->__value_array->__elements.push_back(__new_double(s[i]));
        }

        return d;

    } else if (func_id == __gui_combobox_add) {
        if (params.size() < 1) connector->__error_message_param("gui_combobox::add");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_combobox::add(): parameter #1 must be a string");
        int index = -1;

        if (params.size() > 1) {
            gc<DataType> d = connector->__get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_combobox::add(): parameter #2 must be a number");
            index = d->__value_double;

            connector->__remove_garbage(params.at(1), d);
        }
        
        GUI_ComboBox* c = (GUI_ComboBox*) obj->__holder_pointer;

        if (c->__editable) {
            wxComboBox* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder;
            
            if (index != -1) {
                f->Insert(wxString::FromUTF8(d->__value_string.c_str()), index);
            } else {
                f->AppendString(wxString::FromUTF8(d->__value_string.c_str()));
            }
        } else {
            wxChoice* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder_choice;
            
            if (index != -1) {
                f->Insert(wxString::FromUTF8(d->__value_string.c_str()), index);
            } else {
                f->AppendString(wxString::FromUTF8(d->__value_string.c_str()));
            }
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_combobox_remove) {
        if (params.size() < 1) connector->__error_message_param("gui_combobox::remove");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_combobox::remove(): parameter #1 must be a number");

        GUI_ComboBox* c = (GUI_ComboBox*) obj->__holder_pointer;

        if (c->__editable) {
            wxComboBox* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder;
            f->Delete(d->__value_double);
        } else {
            wxChoice* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder_choice;
            f->Delete(d->__value_double);
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_combobox_clear) {
        GUI_ComboBox* c = (GUI_ComboBox*) obj->__holder_pointer;

        if (c->__editable) {
            wxComboBox* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder;
            f->Clear();
        } else {
            wxChoice* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder_choice;
            f->Clear();
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_combobox_size) {
        GUI_ComboBox* c = (GUI_ComboBox*) obj->__holder_pointer;

        if (c->__editable) {
            wxComboBox* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder;
            result->__type = __TYPE_DOUBLE__;
            result->__value_double = f->GetCount();
        } else {
            wxChoice* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder_choice;
            result->__type = __TYPE_DOUBLE__;
            result->__value_double = f->GetCount();
        }
    } else if (func_id == __gui_combobox_get) {
        if (params.size() < 1) connector->__error_message_param("gui_combobox::get");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_combobox::get(): parameter #1 must be a number");
        
        GUI_ComboBox* c = (GUI_ComboBox*) obj->__holder_pointer;

        if (c->__editable) {
            wxComboBox* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder;
            result->__type = __TYPE_STRING__;
            result->__value_string = f->GetString(d->__value_double).ToUTF8();
        } else {
            wxChoice* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder_choice;
            result->__type = __TYPE_STRING__;
            result->__value_string = f->GetString(d->__value_double).ToUTF8();
        }

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_combobox_set) {
        if (params.size() < 2) connector->__error_message_params("gui_combobox::set", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_combobox::set(): parameter #1 must be a number");
        if (e->__type != __TYPE_STRING__) connector->__error_message("gui_combobox::set(): parameter #2 must be a string");
        
        GUI_ComboBox* c = (GUI_ComboBox*) obj->__holder_pointer;
        
        if (c->__editable) {
            wxComboBox* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder;
            f->SetString(d->__value_double, wxString::FromUTF8(e->__value_string.c_str()));
        } else {
            wxChoice* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder_choice;
            f->SetString(d->__value_double, wxString::FromUTF8(e->__value_string.c_str()));
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
    } else if (func_id == __gui_combobox_getindex) {
        GUI_ComboBox* c = (GUI_ComboBox*) obj->__holder_pointer;
        
        if (c->__editable) {
            wxComboBox* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder;
            result->__type = __TYPE_DOUBLE__;
            result->__value_double = f->GetSelection();
        } else {
            wxChoice* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder_choice;
            result->__type = __TYPE_DOUBLE__;
            result->__value_double = f->GetSelection();
        }
    } else if (func_id == __gui_combobox_setindex) {
        if (params.size() < 1) connector->__error_message_param("gui_combobox::setindex");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_combobox::setindex(): parameter #1 must be a number");

        GUI_ComboBox* c = (GUI_ComboBox*) obj->__holder_pointer;
        
        if (c->__editable) {
            wxComboBox* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder;
            f->SetSelection(d->__value_double);
        } else {
            wxChoice* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder_choice;
            f->SetSelection(d->__value_double);
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);


    // Start of GUI_Timer functions

    } else if (func_id == __gui_timer_run) {
        TimerHandler* f = ((GUI_Timer*) obj->__holder_pointer)->__holder;
        int interval = ((GUI_Timer*) obj->__holder_pointer)->__interval;
        f->Start(interval);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_timer_pause) {
        TimerHandler* f = ((GUI_Timer*) obj->__holder_pointer)->__holder;
        f->Stop();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_timer_isrunning) {
        TimerHandler* f = ((GUI_Timer*) obj->__holder_pointer)->__holder;

        result->__type = __TYPE_BOOL__;
        result->__value_bool = f->IsRunning();
    } else if (func_id == __gui_timer_getinterval) {
        GUI_Timer* t = (GUI_Timer*) obj->__holder_pointer;

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = t->__interval;
    } else if (func_id == __gui_timer_setinterval) {
        if (params.size() < 1) connector->__error_message_param("gui_timer::setinterval");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_timer::setinterval(): parameter #1 must be a number");

        GUI_Timer* t = (GUI_Timer*) obj->__holder_pointer;
        TimerHandler* f = t->__holder;

        t->__interval = d->__value_double;
        f->Stop();
        f->Start(t->__interval);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    

    // Start of GUI_ImageBox functions
    
    } else if (func_id == __gui_imagebox_setscalemode) {
        if (params.size() < 1) connector->__error_message_param("gui_imagebox::setscalemode");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_imagebox::setscalemode(): parameter #1 must be a number");

        int scale_mode = (int) d->__value_double;
        wxStaticBitmap* g = ((GUI_ImageBox*) obj->__holder_pointer)->__holder;
        
        #ifndef __RPI__
            if (scale_mode == 0) {
                g->SetScaleMode(wxStaticBitmapBase::Scale_None);
                g->SetSize(((GUI_ImageBox*) obj->__holder_pointer)->__original_width, ((GUI_ImageBox*) obj->__holder_pointer)->__original_height);
            } else if (scale_mode == 1) {
                g->SetScaleMode(wxStaticBitmapBase::Scale_Fill);
            } else if (scale_mode == 2) {
                g->SetScaleMode(wxStaticBitmapBase::Scale_AspectFit);
            } else if (scale_mode == 3) {
                g->SetScaleMode(wxStaticBitmapBase::Scale_AspectFill);
            }
        #endif

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_imagebox_getimage) {
        result->__type = __TYPE_STRING__;
        result->__value_string = ((GUI_ImageBox*) obj->__holder_pointer)->__path;
    } else if (func_id == __gui_imagebox_setimage) {
        if (params.size() < 1) connector->__error_message_param("gui_imagebox::setimage");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_imagebox::setimage(): parameter #1 must be a string");

        GUI_ImageBox* gui = (GUI_ImageBox*) obj->__holder_pointer;
        wxStaticBitmap* g = gui->__holder;

        wxBitmap bmp(d->__value_string, wxBITMAP_TYPE_ANY);
        g->SetBitmap(bmp);
        gui->__path = d->__value_string;
        gui->__original_width = bmp.GetWidth();
        gui->__original_height = bmp.GetHeight();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_imagebox_getoriginalwidth) {
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ((GUI_ImageBox*) obj->__holder_pointer)->__original_width;
    } else if (func_id == __gui_imagebox_getoriginalheight) {
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = ((GUI_ImageBox*) obj->__holder_pointer)->__original_height;


    // Generic GUI functions

    } else if (func_id == __gui_add_event) {
        if (params.size() < 2) connector->__error_message_params("gui::addevent", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        AST* e = params.at(1);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::addevent(): parameter #1 must be a gui event");
        if (e->__type != __AST_FUNCTION_CALL__ && e->__type != __AST_OBJECT_FUNCTION_CALL__) connector->__error_message("gui::addevent(): parameter #2 must be a function call");

        GUI* g = (GUI*) obj->__holder_pointer;
        __gui_add_event_handler(g, d->__value_double, e, caller_id);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_settext) {
        if (params.size() < 1) connector->__error_message_param("gui::settext");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui::settext(): parameter #1 must be a string");
        
        GUI* g = (GUI*) obj->__holder_pointer;

        if (g->__type == __GUI_TEXTBOX__) {
            wxTextCtrl* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;
            f->SetValue(wxString::FromUTF8(d->__value_string.c_str()));
        } else if (g->__type == __GUI_LABEL__) {
            wxStaticText* f = ((GUI_Label*) obj->__holder_pointer)->__holder;
            f->SetLabel(wxString::FromUTF8(d->__value_string.c_str()));
        } else if (g->__type == __GUI_BUTTON__) {
            wxButton* f = ((GUI_Button*) obj->__holder_pointer)->__holder;
            f->SetLabel(wxString::FromUTF8(d->__value_string.c_str()));
        } else if (g->__type == __GUI_RADIOBOX__) {
            wxRadioButton* f = ((GUI_RadioBox*) obj->__holder_pointer)->__holder;
            f->SetLabel(wxString::FromUTF8(d->__value_string.c_str()));
        } else if (g->__type == __GUI_CHECKBOX__) {
            wxCheckBox* f = ((GUI_CheckBox*) obj->__holder_pointer)->__holder;
            f->SetLabel(wxString::FromUTF8(d->__value_string.c_str()));
        } else if (g->__type == __GUI_LABELED_PANEL__) {
            wxStaticBox* f = ((GUI_LabeledPanel*) obj->__holder_pointer)->__holder;
            f->SetLabel(wxString::FromUTF8(d->__value_string.c_str()));
        } else if (g->__type == __GUI_COMBOBOX__) {
            GUI_ComboBox* c = (GUI_ComboBox*) g;

            if (c->__editable) {
                wxComboBox* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder;
                f->SetValue(wxString::FromUTF8(d->__value_string.c_str()));
            } else {
                connector->__error_message("gui::settext() is not implemented in non-editable gui_combobox");
            }
        } else {
            connector->__error_message("gui::settext() is not implemented in this gui object");
        }

        result->__type = __TYPE_STRING__;
        result->__value_string = d->__value_string;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_gettext) {
        result->__type = __TYPE_STRING__;
        GUI* g = (GUI*) obj->__holder_pointer;

        if (g->__type == __GUI_TEXTBOX__) {
            wxTextCtrl* f = ((GUI_TextBox*) obj->__holder_pointer)->__holder;
            result->__value_string = f->GetValue().ToUTF8();
        } else if (g->__type == __GUI_LABEL__) {
            wxStaticText* f = ((GUI_Label*) obj->__holder_pointer)->__holder;
            result->__value_string = f->GetLabel().ToUTF8();
        } else if (g->__type == __GUI_BUTTON__) {
            wxButton* f = ((GUI_Button*) obj->__holder_pointer)->__holder;
            result->__value_string = f->GetLabel().ToUTF8();
        } else if (g->__type == __GUI_RADIOBOX__) {
            wxRadioButton* f = ((GUI_RadioBox*) obj->__holder_pointer)->__holder;
            result->__value_string = f->GetLabel().ToUTF8();
        } else if (g->__type == __GUI_CHECKBOX__) {
            wxCheckBox* f = ((GUI_CheckBox*) obj->__holder_pointer)->__holder;
            result->__value_string = f->GetLabel().ToUTF8();
        } else if (g->__type == __GUI_LABELED_PANEL__) {
            wxStaticBox* f = ((GUI_LabeledPanel*) obj->__holder_pointer)->__holder;
            result->__value_string = f->GetLabel().ToUTF8();
        } else if (g->__type == __GUI_COMBOBOX__) {
            GUI_ComboBox* c = (GUI_ComboBox*) g;

            if (c->__editable) {
                wxComboBox* f = ((GUI_ComboBox*) obj->__holder_pointer)->__holder;
                result->__value_string = f->GetValue().ToUTF8();
            } else {
                connector->__error_message("gui::gettext() is not implemented in non-editable gui_combobox");
            }
        } else {
            connector->__error_message("gui::gettext() is not implemented in this gui object");
        }
    
    } else if (func_id == __gui_getoverx) {
        result->__type = __TYPE_DOUBLE__;
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        wxPoint p = wxGetMousePosition();
        wxPoint q = w->GetScreenPosition();

        result->__value_double = p.x - q.x;
    } else if (func_id == __gui_getovery) {
        result->__type = __TYPE_DOUBLE__;
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        wxPoint p = wxGetMousePosition();
        wxPoint q = w->GetScreenPosition();

        result->__value_double = p.y - q.y;
    
    } else if (func_id == __gui_getx) {
        result->__type = __TYPE_DOUBLE__;
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        wxPoint p = w->GetPosition();

        result->__value_double = p.x;
    } else if (func_id == __gui_gety) {
        result->__type = __TYPE_DOUBLE__;
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        wxPoint p = w->GetPosition();

        result->__value_double = p.y;
    } else if (func_id == __gui_getwidth) {
        result->__type = __TYPE_DOUBLE__;
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        wxSize p = w->GetSize();

        result->__value_double = p.GetWidth();
    } else if (func_id == __gui_getheight) {
        result->__type = __TYPE_DOUBLE__;
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        wxSize p = w->GetSize();

        result->__value_double = p.GetHeight();
    } else if (func_id == __gui_getinnerwidth) {
        result->__type = __TYPE_DOUBLE__;
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        wxSize p = w->GetClientSize();

        result->__value_double = p.GetWidth();
    } else if (func_id == __gui_getinnerheight) {
        result->__type = __TYPE_DOUBLE__;
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        wxSize p = w->GetClientSize();

        result->__value_double = p.GetHeight();
    } else if (func_id == __gui_setx) {
        if (params.size() < 1) connector->__error_message_param("gui::setx");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::setx(): parameter #1 must be a number");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxPoint p = w->GetPosition();
        p.x = d->__value_double;
        w->SetPosition(p);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_sety) {
        if (params.size() < 1) connector->__error_message_param("gui::sety");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::sety(): parameter #1 must be a number");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxPoint p = w->GetPosition();
        p.y = d->__value_double;
        w->SetPosition(p);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_setwidth) {
        if (params.size() < 1) connector->__error_message_param("gui::setwidth");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::setwidth(): parameter #1 must be a number");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxSize p = w->GetSize();
        p.SetWidth(d->__value_double);
        w->SetSize(p);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_setheight) {
        if (params.size() < 1) connector->__error_message_param("gui::setheight");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::setheight(): parameter #1 must be a number");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxSize p = w->GetSize();
        p.SetHeight(d->__value_double);
        w->SetSize(p);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    
    } else if (func_id == __gui_setenable) {
        if (params.size() < 1) connector->__error_message_param("gui::setenable");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui::setenable(): parameter #1 must be a boolean");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        w->Enable(d->__value_bool);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_isenable) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = w->IsEnabled();
    } else if (func_id == __gui_setvisible) {
        if (params.size() < 1) connector->__error_message_param("gui::setvisible");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui::setvisible(): parameter #1 must be a boolean");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        if (d->__value_bool == true) {
            w->Show();
        } else {
            w->Hide();
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_isvisible) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = w->IsShown();
    
    } else if (func_id == __gui_setbackgroundcolour) {
        if (params.size() < 1) connector->__error_message_param("gui::setbackgroundcolour");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui::setbackgroundcolour(): parameter #1 must be an object");
        if (d->__value_object->__name != "gui_colour") connector->__error_message("gui::setbackgroundcolour(): parameter #1 must be a gui_colour");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder_alt(g);
        GUI_Colour* c = (GUI_Colour*) d->__value_object->__holder_pointer;

        w->SetBackgroundColour(wxColour(c->__red, c->__green, c->__blue, c->__alpha));

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_setforegroundcolour) {
        if (params.size() < 1) connector->__error_message_param("gui::setforegroundcolour");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui::setforegroundcolour(): parameter #1 must be an object");
        if (d->__value_object->__name != "gui_colour") connector->__error_message("gui::setforegroundcolour(): parameter #1 must be a gui_colour");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder_alt(g);
        GUI_Colour* c = (GUI_Colour*) d->__value_object->__holder_pointer;

        w->SetForegroundColour(wxColour(c->__red, c->__green, c->__blue, c->__alpha));

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_getbackgroundcolour) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder_alt(g);
        wxColour c = w->GetBackgroundColour();
        
        return __new_colour(c.Red(), c.Green(), c.Blue(), c.Alpha());
    } else if (func_id == __gui_getforegroundcolour) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder_alt(g);
        wxColour c = w->GetForegroundColour();
        
        return __new_colour(c.Red(), c.Green(), c.Blue(), c.Alpha());
    
    } else if (func_id == __gui_setfont) {
        if (params.size() < 1) connector->__error_message_param("gui::setfont");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui::setfont(): parameter #1 must be a string");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();
        f.SetFaceName(d->__value_string);
        w->SetFont(f);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_setfontsize) {
        if (params.size() < 1) connector->__error_message_param("gui::setfontsize");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::setfontsize(): parameter #1 must be a number");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();
        f.SetPointSize(d->__value_double);
        w->SetFont(f);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_setfontbold) {
        if (params.size() < 1) connector->__error_message_param("gui::setfontbold");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui::setfontbold(): parameter #1 must be a boolean");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();
        if (d->__value_bool == true) f.SetWeight(wxFONTWEIGHT_BOLD); else f.SetWeight(wxFONTWEIGHT_NORMAL);
        w->SetFont(f);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_setfontlight) {
        if (params.size() < 1) connector->__error_message_param("gui::setfontlight");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui::setfontlight(): parameter #1 must be a boolean");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();
        if (d->__value_bool == true) f.SetWeight(wxFONTWEIGHT_LIGHT); else f.SetWeight(wxFONTWEIGHT_NORMAL);
        w->SetFont(f);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_setfontitalic) {
        if (params.size() < 1) connector->__error_message_param("gui::setfontitalic");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui::setfontitalic(): parameter #1 must be a boolean");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();
        if (d->__value_bool == true) f.SetStyle(wxFONTSTYLE_ITALIC); else f.SetStyle(wxFONTSTYLE_NORMAL);
        w->SetFont(f);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_setfontunderline) {
        if (params.size() < 1) connector->__error_message_param("gui::setfontunderline");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui::setfontunderline(): parameter #1 must be a boolean");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();
        f.SetUnderlined(d->__value_bool);
        w->SetFont(f);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_setfontstrikethrough) {
        if (params.size() < 1) connector->__error_message_param("gui::setfontstrikethrough");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_BOOL__) connector->__error_message("gui::setfontstrikethrough(): parameter #1 must be a boolean");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();
        f.SetStrikethrough(d->__value_bool);
        w->SetFont(f);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_getfont) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();

        result->__type = __TYPE_STRING__;
        result->__value_string = f.GetFaceName();
    } else if (func_id == __gui_getfontsize) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();

        result->__type = __TYPE_DOUBLE__;
        result->__value_double = f.GetPointSize();
    } else if (func_id == __gui_isfontbold) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = (f.GetWeight() == wxFONTWEIGHT_BOLD);
    } else if (func_id == __gui_isfontlight) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = (f.GetWeight() == wxFONTWEIGHT_LIGHT);
    } else if (func_id == __gui_isfontitalic) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = (f.GetStyle() == wxFONTSTYLE_ITALIC);
    } else if (func_id == __gui_isfontunderline) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = f.GetUnderlined();
    } else if (func_id == __gui_isfontstrikethrough) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        wxFont f = w->GetFont();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = f.GetStrikethrough();
    
    } else if (func_id == __gui_setfocus) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        w->SetFocus();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_settooltip) {
        if (params.size() < 1) connector->__error_message_param("gui::settooltip");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui::settooltip(): parameter #1 must be a string");
        
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        w->SetToolTip(wxString::FromUTF8(d->__value_string.c_str()));

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_gettooltip) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        result->__type = __TYPE_STRING__;
        result->__value_string = w->GetToolTipText().ToUTF8();
    
    } else if (func_id == __gui_centerhorizontal) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        if (g->__parent != NULL) {
            wxWindow* parent = g->__parent;
            wxSize s = parent->GetClientSize();

            wxPoint p = w->GetPosition();
            p.x = (s.GetWidth() / 2) - (w->GetSize().GetWidth() / 2);
            w->SetPosition(p);
        } else {
            cout << "Warning: function gui::centerhorizontal() is not compatible with gui_window" << endl;
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_centervertical) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        if (g->__parent != NULL) {
            wxWindow* parent = g->__parent;
            wxSize s = parent->GetClientSize();

            wxPoint p = w->GetPosition();
            p.y = (s.GetHeight() / 2) - (w->GetSize().GetHeight() / 2);
            w->SetPosition(p);
        } else {
            cout << "Warning: function gui::centervertical() is not compatible with gui_window" << endl;
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_center) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        if (g->__parent != NULL) {
            wxWindow* parent = g->__parent;
            wxSize s = parent->GetClientSize();

            wxPoint p = w->GetPosition();
            p.x = (s.GetWidth() / 2) - (w->GetSize().GetWidth() / 2);
            p.y = (s.GetHeight() / 2) - (w->GetSize().GetHeight() / 2);
            w->SetPosition(p);
        } else {
            cout << "Warning: function gui::center() is not compatible with gui_window" << endl;
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_right) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        
        int margin = 0;

        if (params.size() > 0) {
            gc<DataType> d = connector->__get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::right(): parameter #1 must be a number");
            margin = d->__value_double;

            connector->__remove_garbage(params.at(0), d);
        }

        if (g->__parent != NULL) {
            wxWindow* parent = g->__parent;
            wxSize s = parent->GetClientSize();

            wxPoint p = w->GetPosition();
            p.x = s.GetWidth() - w->GetSize().GetWidth() - margin;
            w->SetPosition(p);
        } else {
            cout << "Warning: function gui::right() is not compatible with gui_window" << endl;
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_bottom) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        
        int margin = 0;

        if (params.size() > 0) {
            gc<DataType> d = connector->__get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::bottom(): parameter #1 must be a number");
            margin = d->__value_double;

            connector->__remove_garbage(params.at(0), d);
        }

        if (g->__parent != NULL) {
            wxWindow* parent = g->__parent;
            wxSize s = parent->GetClientSize();

            wxPoint p = w->GetPosition();
            p.y = s.GetHeight() - w->GetSize().GetHeight() - margin;
            w->SetPosition(p);
        } else {
            cout << "Warning: function gui::bottom() is not compatible with gui_window" << endl;
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_stretchwidth) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        
        int margin_left = 0;
        int margin_right = 0;

        if (params.size() > 0) {
            gc<DataType> d = connector->__get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::stretchwidth(): parameter #1 must be a number");
            margin_left = d->__value_double;

            connector->__remove_garbage(params.at(0), d);
        }
        if (params.size() > 1) {
            gc<DataType> d = connector->__get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::stretchwidth(): parameter #2 must be a number");
            margin_right = d->__value_double;

            connector->__remove_garbage(params.at(1), d);
        }

        if (g->__parent != NULL) {
            wxWindow* parent = g->__parent;
            wxSize s = parent->GetClientSize();

            wxPoint p = w->GetPosition(); p.x = margin_left; w->SetPosition(p);
            wxSize ss = w->GetSize(); ss.SetWidth(s.GetWidth() - margin_right - margin_left); w->SetSize(ss);
        } else {
            cout << "Warning: function gui::stretchwidth() is not compatible with gui_window" << endl;
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_stretchheight) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        
        int margin_top = 0;
        int margin_bottom = 0;

        if (params.size() > 0) {
            gc<DataType> d = connector->__get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::stretchheight(): parameter #1 must be a number");
            margin_top = d->__value_double;

            connector->__remove_garbage(params.at(0), d);
        }
        if (params.size() > 1) {
            gc<DataType> d = connector->__get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::stretchheight(): parameter #2 must be a number");
            margin_bottom = d->__value_double;

            connector->__remove_garbage(params.at(1), d);
        }

        if (g->__parent != NULL) {
            wxWindow* parent = g->__parent;
            wxSize s = parent->GetClientSize();

            wxPoint p = w->GetPosition(); p.y = margin_top; w->SetPosition(p);
            wxSize ss = w->GetSize(); ss.SetHeight(s.GetHeight() - margin_bottom - margin_top); w->SetSize(ss);
        } else {
            cout << "Warning: function gui::stretchheight() is not compatible with gui_window" << endl;
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_stretch) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);
        
        int margin_left = 0;
        int margin_right = 0;
        int margin_top = 0;
        int margin_bottom = 0;

        if (params.size() > 0) {
            gc<DataType> d = connector->__get_value(params.at(0), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::stretch(): parameter #1 must be a number");
            margin_left = d->__value_double;

            connector->__remove_garbage(params.at(0), d);
        }
        if (params.size() > 1) {
            gc<DataType> d = connector->__get_value(params.at(1), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::stretch(): parameter #2 must be a number");
            margin_right = d->__value_double;

            connector->__remove_garbage(params.at(1), d);
        }
        if (params.size() > 2) {
            gc<DataType> d = connector->__get_value(params.at(2), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::stretch(): parameter #3 must be a number");
            margin_top = d->__value_double;

            connector->__remove_garbage(params.at(2), d);
        }
        if (params.size() > 3) {
            gc<DataType> d = connector->__get_value(params.at(3), caller_id);
            if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui::stretch(): parameter #4 must be a number");
            margin_bottom = d->__value_double;

            connector->__remove_garbage(params.at(3), d);
        }

        if (g->__parent != NULL) {
            wxWindow* parent = g->__parent;
            wxSize s = parent->GetClientSize();

            wxPoint p = w->GetPosition(); p.x = margin_left; p.y = margin_top; w->SetPosition(p);
            wxSize ss = w->GetSize(); ss.SetWidth(s.GetWidth() - margin_right - margin_left); ss.SetHeight(s.GetHeight() - margin_bottom - margin_top); w->SetSize(ss);
        } else {
            cout << "Warning: function gui::stretch() is not compatible with gui_window" << endl;
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_refresh) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        #ifdef _WIN32
            w->Refresh(true);
        #else
            w->Refresh(false);
        #endif
    
        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_panel_update) {
        GUI* g = (GUI*) obj->__holder_pointer;
        wxWindow* w = __get_gui_holder(g);

        int width = w->GetSize().GetWidth();
        wxSize ws = w->GetSize();
        ws.SetWidth(100);

        w->SetSize(ws);
        ws.SetWidth(width);
        w->SetSize(ws);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    

    // Dialogs

    } else if (func_id == __gui_dialog_open) {
        if (params.size() < 1) connector->__error_message_param("dialog::open");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("dialog::open(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("dialog::open(): parameter #1 must be a gui object");

        GUI* parent = (GUI*) d->__value_object->__holder_pointer;
        if (parent->__type != __GUI_WINDOW__) connector->__error_message("dialog::open(): parameter #1 must be a gui_window object");

        string rst = "";
        string title = "Open";
        string wildcard = "All files (*.*)|*.*";
        string default_dir = "";
        string default_file = "";

        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::open(): parameter #2 must be a string");
            title = f->__value_string;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::open(): parameter #3 must be a string");
            wildcard = f->__value_string;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::open(): parameter #4 must be a string");
            default_dir = f->__value_string;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::open(): parameter #5 must be a string");
            default_file = f->__value_string;

            connector->__remove_garbage(params.at(4), f);
        }

        #ifdef __APPLE__
            title = "";
        #endif

        wxFileDialog dialog(((GUI_Window*) parent)->__holder, title, default_dir, default_file, wildcard, wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (dialog.ShowModal() == wxID_OK) {
            rst = dialog.GetPath();
        }

        result->__type = __TYPE_STRING__;
        result->__value_string = rst;
    } else if (func_id == __gui_dialog_multiple) {
        if (params.size() < 1) connector->__error_message_param("dialog::open_multiple");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("dialog::open_multiple(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("dialog::open_multiple(): parameter #1 must be a gui object");

        GUI* parent = (GUI*) d->__value_object->__holder_pointer;
        if (parent->__type != __GUI_WINDOW__) connector->__error_message("dialog::open_multiple(): parameter #1 must be a gui_window object");

        string title = "Open";
        string wildcard = "All files (*.*)|*.*";
        string default_dir = "";
        string default_file = "";

        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::open_multiple(): parameter #2 must be a string");
            title = f->__value_string;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::open_multiple(): parameter #3 must be a string");
            wildcard = f->__value_string;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::open_multiple(): parameter #4 must be a string");
            default_dir = f->__value_string;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::open_multiple(): parameter #5 must be a string");
            default_file = f->__value_string;

            connector->__remove_garbage(params.at(4), f);
        }

        #ifdef __APPLE__
            title = "";
        #endif

        wxFileDialog dialog(((GUI_Window*) parent)->__holder, title, default_dir, default_file, wildcard, wxFD_OPEN | wxFD_FILE_MUST_EXIST | wxFD_MULTIPLE);
        gc<DataType> rst = connector->__create_array(0);

        if (dialog.ShowModal() == wxID_OK) {
            wxArrayString arr;
            dialog.GetPaths(arr);

            for (int i = 0; i < arr.size(); i++) {
                rst->__value_array->__elements.push_back(__new_string(arr[i].ToStdString()));
            }
        }
        
        result = rst;
    } else if (func_id == __gui_dialog_save) {
        if (params.size() < 1) connector->__error_message_param("dialog::save");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("dialog::save(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("dialog::save(): parameter #1 must be a gui object");

        GUI* parent = (GUI*) d->__value_object->__holder_pointer;
        if (parent->__type != __GUI_WINDOW__) connector->__error_message("dialog::save(): parameter #1 must be a gui_window object");

        string rst = "";
        string title = "Save";
        string wildcard = "All files (*.*)|*.*";
        string default_dir = "";
        string default_file = "";

        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::save(): parameter #2 must be a string");
            title = f->__value_string;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::save(): parameter #3 must be a string");
            wildcard = f->__value_string;

            connector->__remove_garbage(params.at(2), f);
        }
        if (params.size() > 3) {
            gc<DataType> f = connector->__get_value(params.at(3), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::save(): parameter #4 must be a string");
            default_dir = f->__value_string;

            connector->__remove_garbage(params.at(3), f);
        }
        if (params.size() > 4) {
            gc<DataType> f = connector->__get_value(params.at(4), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::save(): parameter #5 must be a string");
            default_file = f->__value_string;

            connector->__remove_garbage(params.at(4), f);
        }

        #ifdef __APPLE__
            title = "";
        #endif

        wxFileDialog dialog(((GUI_Window*) parent)->__holder, title, default_dir, default_file, wildcard, wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

        if (dialog.ShowModal() == wxID_OK) {
            rst = dialog.GetPath();
        }

        result->__type = __TYPE_STRING__;
        result->__value_string = rst;
    } else if (func_id == __gui_dialog_directory) {
        if (params.size() < 1) connector->__error_message_param("dialog::directory");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("dialog::directory(): parameter #1 must be an object");
        if (d->__value_object->__name.substr(0, 3) != "gui" && d->__value_object->__inherited.find("gui") == string::npos) connector->__error_message("dialog::directory(): parameter #1 must be a gui object");

        GUI* parent = (GUI*) d->__value_object->__holder_pointer;
        if (parent->__type != __GUI_WINDOW__) connector->__error_message("dialog::directory(): parameter #1 must be a gui_window object");

        string rst = "";
        string title = "Choose a directory";
        string default_dir = "";

        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::directory(): parameter #2 must be a string");
            title = f->__value_string;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("dialog::directory(): parameter #3 must be a string");
            default_dir = f->__value_string;

            connector->__remove_garbage(params.at(2), f);
        }

        #ifdef __APPLE__
            title = "";
        #endif

        wxDirDialog dialog(((GUI_Window*) parent)->__holder, title, default_dir);

        if (dialog.ShowModal() == wxID_OK) {
            rst = dialog.GetPath();
        }

        result->__type = __TYPE_STRING__;
        result->__value_string = rst;
    

    // Clipboard

    } else if (func_id == __gui_clipboard_available) {
        bool available = false;

        if (wxTheClipboard->Open()) {
            if (wxTheClipboard->IsSupported(wxDF_TEXT) || wxTheClipboard->IsSupported(wxDF_UNICODETEXT)) {
                available = true;
            }

            wxTheClipboard->Close();
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = available;
    } else if (func_id == __gui_clipboard_get) {
        string data = "";

        if (wxTheClipboard->Open()) {
            if (wxTheClipboard->IsSupported(wxDF_TEXT) || wxTheClipboard->IsSupported(wxDF_UNICODETEXT)) {
                wxTextDataObject d;
                wxTheClipboard->GetData(d);
                data = d.GetText().ToUTF8();
            }

            wxTheClipboard->Close();
        }

        result->__type = __TYPE_STRING__;
        result->__value_string = data;
    } else if (func_id == __gui_clipboard_clear) {
        if (wxTheClipboard->Open()) {
            wxTheClipboard->Clear();
            wxTheClipboard->Close();
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_clipboard_set) {
        if (params.size() < 1) connector->__error_message_param("clipboard::set");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("clipboard::set(): parameter #1 must be a string");

        if (wxTheClipboard->Open()) {
            wxTheClipboard->SetData(new wxTextDataObject(wxString::FromUTF8(d->__value_string.c_str())));
            wxTheClipboard->Close();
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;


    // Other functions

    } else if (func_id == __gui_messagebox) {
        if (params.size() < 1) connector->__error_message_param("messagebox");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("messagebox(): parameter #1 must be a string");

        string message = d->__value_string;
        string title = "Dinfio";
        long style = wxOK + wxICON_INFORMATION;
        
        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_STRING__) connector->__error_message("messagebox(): parameter #2 must be a string");
            title = f->__value_string;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("messagebox(): parameter #3 must be a number");
            style = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }

        int msg = wxMessageBox(wxString::FromUTF8(message.c_str()), wxString::FromUTF8(title.c_str()), style);
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = msg;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_keycode) {
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = __key_code;

    } else if (func_id == __gui_colour_rgba) {
        if (params.size() < 4) connector->__error_message_params("gui_colours::rgba", 4);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        gc<DataType> g = connector->__get_value(params.at(3), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_colours::rgba(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_colours::rgba(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_colours::rgba(): parameter #3 must be a number");
        if (g->__type != __TYPE_DOUBLE__) connector->__error_message("gui_colours::rgba(): parameter #4 must be a number");

        int red = d->__value_double;
        int green = e->__value_double;
        int blue = f->__value_double;
        int alpha = g->__value_double;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
        connector->__remove_garbage(params.at(3), g);

        return __new_colour(red, green, blue, alpha);
    } else if (func_id == __gui_colour_rgb) {
        if (params.size() < 3) connector->__error_message_params("gui_colours::rgb", 3);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_colours::rgb(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_colours::rgb(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_colours::rgb(): parameter #3 must be a number");
        
        int red = d->__value_double;
        int green = e->__value_double;
        int blue = f->__value_double;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);

        return __new_colour(red, green, blue, 255);
    } else if (func_id == __gui_colour_hex) {
        if (params.size() < 1) connector->__error_message_param("gui_colours::hex");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_colours::hex(): parameter #1 must be a string");

        string s = d->__value_string;
        unsigned int red = 0;
        unsigned int green = 0;
        unsigned int blue = 0;
        unsigned int alpha = 255;

        if (s.length() != 6 && s.length() != 8) {
            connector->__error_message("gui_colours::hex(): invalid hex string");
        }

        stringstream ss_red; ss_red << hex << s.substr(0, 2); ss_red >> red;
        stringstream ss_green; ss_green << hex << s.substr(2, 2); ss_green >> green;
        stringstream ss_blue; ss_blue << hex << s.substr(4, 2); ss_blue >> blue;

        if (s.length() == 8) {
            stringstream ss_alpha; ss_alpha << hex << s.substr(6, 2); ss_alpha >> alpha;
        }

        connector->__remove_garbage(params.at(0), d);
        return __new_colour(red, green, blue, alpha);
    
    } else if (func_id == __gui_image_data) {
        if (params.size() < 2) connector->__error_message_params("image_data", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("image_data(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("image_data(): parameter #2 must be a number");

        return __new_image_data(d->__value_double, e->__value_double);
    } else if (func_id == __gui_image_data_setdata) {
        if (params.size() < 1) connector->__error_message_param("image_data::setdata");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_ARRAY__) connector->__error_message("image_data::setdata(): parameter #1 must be an array");

        GUI_ImageData* img = (GUI_ImageData*) obj->__holder_pointer;

        if (!img->__is_loaded) {
            img->__bytes = (unsigned char*) malloc(d->__value_array->__elements.size());
            img->__is_loaded = true;
            img->__size = d->__value_array->__elements.size();
        } else {
            if (img->__size != d->__value_array->__elements.size()) connector->__error_message("image_data::setdata(): new data size must be equal to the current data size");
        }

        for (int i = 0; i < d->__value_array->__elements.size(); i++) {
            img->__bytes[i] = (unsigned char) d->__value_array->__elements[i]->__value_double;
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_image_data_savetofile) {
        if (params.size() < 1) connector->__error_message_param("image_data::savetofile");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("image_data::savetofile(): parameter #1 must be a string");

        GUI_ImageData* img = (GUI_ImageData*) obj->__holder_pointer;

        if (!img->__is_loaded) {
            connector->__error_message("image_data::savetofile(): image data does not have any data yet");
        } else {
            int w = img->__w;
            int h = img->__h;

            if (params.size() > 1) {
                gc<DataType> e = connector->__get_value(params.at(1), caller_id);
                if (e->__type != __TYPE_DOUBLE__) connector->__error_message("image_data::savetofile(): parameter #2 must be a number");
                w = e->__value_double;
            }

            if (params.size() > 2) {
                gc<DataType> e = connector->__get_value(params.at(2), caller_id);
                if (e->__type != __TYPE_DOUBLE__) connector->__error_message("image_data::savetofile(): parameter #3 must be a number");
                h = e->__value_double;
            }
            
            wxImage wximg = wxImage(img->__w, img->__h, img->__bytes, true);

            if (w != img->__w || h != img->__h) wximg.Rescale(w, h);
            wxBitmap bmp = wxBitmap(wximg);

            bmp.SaveFile(d->__value_string, wxBITMAP_TYPE_PNG);
        }

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_image) {
        if (params.size() < 1) connector->__error_message_param("image");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("image_data(): parameter #1 must be a string");

        return __new_image(d->__value_string);


    // Start of drawing functions

    } else if (func_id == __gui_draw_clear) {
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_clear(): canvas mode of this gui_panel must be true");

        panel->__current_font_size = 0;

        for (int i = panel->__drawing.size() - 1; i >= 0; i--) {
            delete(panel->__drawing.at(i));
            panel->__drawing.erase(panel->__drawing.begin() + i);
        }

        panel->__drawing.clear();
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_draw_setpen) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_setpen");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_panel::draw_setpen(): parameter #1 must be an object");
        if (d->__value_object->__name != "gui_colour") connector->__error_message("gui_panel::draw_setpen(): parameter #1 must be a gui_colour");

        int w = 1;
        int s = 0;

        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_setpen(): parameter #2 must be a number");
            w = f->__value_double;

            connector->__remove_garbage(params.at(1), f);
        }
        if (params.size() > 2) {
            gc<DataType> f = connector->__get_value(params.at(2), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_setpen(): parameter #3 must be a number");
            s = f->__value_double;

            connector->__remove_garbage(params.at(2), f);
        }
        
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_setpen(): canvas mode of this gui_panel must be true");
        GUI_Colour* c = (GUI_Colour*) d->__value_object->__holder_pointer;

        panel->__drawing.push_back(new DrawingPen(c->__red, c->__green, c->__blue, w, s));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_draw_setbrush) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_setbrush");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_panel::draw_setbrush(): parameter #1 must be an object");
        if (d->__value_object->__name != "gui_colour") connector->__error_message("gui_panel::draw_setbrush(): parameter #1 must be a gui_colour");

        int s = 0;

        if (params.size() > 1) {
            gc<DataType> f = connector->__get_value(params.at(1), caller_id);
            if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_setbrush(): parameter #2 must be a number");
            s = f->__value_double;

            connector->__remove_garbage(params.at(1), f);
        }
        
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_setbrush(): canvas mode of this gui_panel must be true");
        GUI_Colour* c = (GUI_Colour*) d->__value_object->__holder_pointer;

        panel->__drawing.push_back(new DrawingBrush(c->__red, c->__green, c->__blue, s));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_draw_setfont) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_setfont");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_setfont(): parameter #1 must be a number");

        string face = "";
        bool italic = false;
        bool bold = false;

        if (params.size() > 1) {
            gc<DataType> g = connector->__get_value(params.at(1), caller_id);
            if (g->__type != __TYPE_STRING__) connector->__error_message("gui_panel::draw_setfont(): parameter #2 must be a string");
            face = g->__value_string;

            connector->__remove_garbage(params.at(1), g);
        }
        if (params.size() > 2) {
            gc<DataType> g = connector->__get_value(params.at(2), caller_id);
            if (g->__type != __TYPE_BOOL__) connector->__error_message("gui_panel::draw_setfont(): parameter #3 must be a boolean");
            bold = g->__value_bool;

            connector->__remove_garbage(params.at(2), g);
        }
        if (params.size() > 3) {
            gc<DataType> g = connector->__get_value(params.at(3), caller_id);
            if (g->__type != __TYPE_BOOL__) connector->__error_message("gui_panel::draw_setfont(): parameter #4 must be a boolean");
            italic = g->__value_bool;

            connector->__remove_garbage(params.at(3), g);
        }

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_setfont(): canvas mode of this gui_panel must be true");

        panel->__current_font_face = face;
        panel->__current_font_size = d->__value_double;
        panel->__current_font_bold = bold;
        panel->__current_font_italic = italic;

        panel->__drawing.push_back(new DrawingFont(d->__value_double, face, bold, italic));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_draw_settextcolour) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::settextcolour");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_panel::settextcolour(): parameter #1 must be an object");
        if (d->__value_object->__name != "gui_colour") connector->__error_message("gui_panel::settextcolour(): parameter #1 must be a gui_colour");

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::settextcolour(): canvas mode of this gui_panel must be true");
        GUI_Colour* c = (GUI_Colour*) d->__value_object->__holder_pointer;

        panel->__drawing.push_back(new DrawingTextColour(c->__red, c->__green, c->__blue));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_draw_setbackgroundcolour) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_setbackgroundcolour");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_panel::draw_setbackgroundcolour(): parameter #1 must be an object");
        if (d->__value_object->__name != "gui_colour") connector->__error_message("gui_panel::draw_setbackgroundcolour(): parameter #1 must be a gui_colour");

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_setbackgroundcolour(): canvas mode of this gui_panel must be true");
        GUI_Colour* c = (GUI_Colour*) d->__value_object->__holder_pointer;

        panel->__drawing.push_back(new DrawingBackColour(c->__red, c->__green, c->__blue));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_draw_line) {
        if (params.size() < 4) connector->__error_message_params("gui_panel::draw_line", 4);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        gc<DataType> g = connector->__get_value(params.at(3), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_line(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_line(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_line(): parameter #3 must be a number");
        if (g->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_line(): parameter #4 must be a number");
        
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_line(): canvas mode of this gui_panel must be true");

        panel->__drawing.push_back(new DrawingLine(d->__value_double, e->__value_double, f->__value_double, g->__value_double));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
        connector->__remove_garbage(params.at(3), g);
    } else if (func_id == __gui_draw_rectangle) {
        if (params.size() < 4) connector->__error_message_params("gui_panel::draw_rectangle", 4);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        gc<DataType> g = connector->__get_value(params.at(3), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_rectangle(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_rectangle(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_rectangle(): parameter #3 must be a number");
        if (g->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_rectangle(): parameter #4 must be a number");
        
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_rectangle(): canvas mode of this gui_panel must be true");

        panel->__drawing.push_back(new DrawingRect(d->__value_double, e->__value_double, f->__value_double, g->__value_double));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
        connector->__remove_garbage(params.at(3), g);
    } else if (func_id == __gui_draw_roundedrectangle) {
        if (params.size() < 5) connector->__error_message_params("gui_panel::draw_roundedrectangle", 5);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        gc<DataType> g = connector->__get_value(params.at(3), caller_id);
        gc<DataType> h = connector->__get_value(params.at(4), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_roundedrectangle(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_roundedrectangle(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_roundedrectangle(): parameter #3 must be a number");
        if (g->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_roundedrectangle(): parameter #4 must be a number");
        if (h->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_roundedrectangle(): parameter #5 must be a number");
        
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_roundedrectangle(): canvas mode of this gui_panel must be true");

        panel->__drawing.push_back(new DrawingRoundedRect(d->__value_double, e->__value_double, f->__value_double, g->__value_double, h->__value_double));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
        connector->__remove_garbage(params.at(3), g);
        connector->__remove_garbage(params.at(4), h);
    } else if (func_id == __gui_draw_text) {
        if (params.size() < 3) connector->__error_message_params("gui_panel::draw_text", 3);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_panel::draw_text(): parameter #1 must be a string");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_text(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_text(): parameter #3 must be a number");

        double angle = 0.0;

        if (params.size() > 3) {
            gc<DataType> g = connector->__get_value(params.at(3), caller_id);
            if (g->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_text(): parameter #4 must be a number");
            angle = g->__value_double;

            connector->__remove_garbage(params.at(3), g);
        }

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_text(): canvas mode of this gui_panel must be true");

        panel->__drawing.push_back(new DrawingText(d->__value_string, e->__value_double, f->__value_double, angle));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
    } else if (func_id == __gui_draw_circle) {
        if (params.size() < 3) connector->__error_message_params("gui_panel::draw_circle", 3);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_circle(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_circle(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_circle(): parameter #3 must be a number");
        
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_circle(): canvas mode of this gui_panel must be true");

        panel->__drawing.push_back(new DrawingCircle(d->__value_double, e->__value_double, f->__value_double));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
    } else if (func_id == __gui_draw_point) {
        if (params.size() < 2) connector->__error_message_params("gui_panel::draw_point", 2);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_point(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_point(): parameter #2 must be a number");
        
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_point(): canvas mode of this gui_panel must be true");

        panel->__drawing.push_back(new DrawingPoint(d->__value_double, e->__value_double));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
    } else if (func_id == __gui_draw_ellipse) {
        if (params.size() < 4) connector->__error_message_params("gui_panel::draw_ellipse", 4);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        gc<DataType> g = connector->__get_value(params.at(3), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_ellipse(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_ellipse(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_ellipse(): parameter #3 must be a number");
        if (g->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_ellipse(): parameter #4 must be a number");

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_ellipse(): canvas mode of this gui_panel must be true");

        panel->__drawing.push_back(new DrawingEllipse(d->__value_double, e->__value_double, f->__value_double, g->__value_double));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
        connector->__remove_garbage(params.at(3), g);
    } else if (func_id == __gui_draw_arc) {
        if (params.size() < 6) connector->__error_message_params("gui_panel::draw_arc", 6);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        gc<DataType> g = connector->__get_value(params.at(3), caller_id);
        gc<DataType> h = connector->__get_value(params.at(4), caller_id);
        gc<DataType> i = connector->__get_value(params.at(5), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_arc(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_arc(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_arc(): parameter #3 must be a number");
        if (g->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_arc(): parameter #4 must be a number");
        if (h->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_arc(): parameter #5 must be a number");
        if (i->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_arc(): parameter #6 must be a number");

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_arc(): canvas mode of this gui_panel must be true");

        panel->__drawing.push_back(new DrawingArc(d->__value_double, e->__value_double, f->__value_double, g->__value_double, h->__value_double, i->__value_double));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
        connector->__remove_garbage(params.at(3), g);
        connector->__remove_garbage(params.at(4), h);
        connector->__remove_garbage(params.at(5), i);
    } else if (func_id == __gui_draw_ellipticarc) {
        if (params.size() < 6) connector->__error_message_params("gui_panel::draw_ellipticarc", 6);
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        gc<DataType> e = connector->__get_value(params.at(1), caller_id);
        gc<DataType> f = connector->__get_value(params.at(2), caller_id);
        gc<DataType> g = connector->__get_value(params.at(3), caller_id);
        gc<DataType> h = connector->__get_value(params.at(4), caller_id);
        gc<DataType> i = connector->__get_value(params.at(5), caller_id);
        if (d->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_ellipticarc(): parameter #1 must be a number");
        if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_ellipticarc(): parameter #2 must be a number");
        if (f->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_ellipticarc(): parameter #3 must be a number");
        if (g->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_ellipticarc(): parameter #4 must be a number");
        if (h->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_ellipticarc(): parameter #5 must be a number");
        if (i->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_ellipticarc(): parameter #6 must be a number");

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_ellipticarc(): canvas mode of this gui_panel must be true");

        panel->__drawing.push_back(new DrawingEllipticArc(d->__value_double, e->__value_double, f->__value_double, g->__value_double, h->__value_double, i->__value_double));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
        connector->__remove_garbage(params.at(1), e);
        connector->__remove_garbage(params.at(2), f);
        connector->__remove_garbage(params.at(3), g);
        connector->__remove_garbage(params.at(4), h);
        connector->__remove_garbage(params.at(5), i);
    } else if (func_id == __gui_draw_polygon) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_polygon");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_ARRAY__) connector->__error_message("gui_panel::draw_polygon(): parameter #1 must be an array");
        
        int xo = 0;
        int yo = 0;
        int s = 0;
        vector<DrawingPointData> p;
        gc<Array> ap = d->__value_array;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_polygon(): parameter #2 must be a number");
            xo = e->__value_double;

            connector->__remove_garbage(params.at(1), e);
        }
        if (params.size() > 2) {
            gc<DataType> e = connector->__get_value(params.at(2), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_polygon(): parameter #3 must be a number");
            yo = e->__value_double;

            connector->__remove_garbage(params.at(2), e);
        }
        if (params.size() > 3) {
            gc<DataType> e = connector->__get_value(params.at(3), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_polygon(): parameter #4 must be a number");
            s = e->__value_double;

            connector->__remove_garbage(params.at(3), e);
        }

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_polygon(): canvas mode of this gui_panel must be true");

        for (int i = 0; i < ap->__elements.size(); i++) {
            gc<DataType> app = ap->__elements.at(i);
            if (app->__type != __TYPE_ARRAY__) connector->__error_message("gui_panel::draw_polygon(): parameter #1 must be a 2D array");
            gc<Array> appa = app->__value_array;

            DrawingPointData dp;
            dp.x = appa->__elements.at(0)->__value_double;
            dp.y = appa->__elements.at(1)->__value_double;
            p.push_back(dp);
        }

        panel->__drawing.push_back(new DrawingPolygon(p, p.size(), xo, yo, s));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_draw_spline) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_spline");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_ARRAY__) connector->__error_message("gui_panel::draw_spline(): parameter #1 must be an array");
        
        vector<DrawingPointData> p;
        gc<Array> ap = d->__value_array;

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_spline(): canvas mode of this gui_panel must be true");

        for (int i = 0; i < ap->__elements.size(); i++) {
            gc<DataType> app = ap->__elements.at(i);
            if (app->__type != __TYPE_ARRAY__) connector->__error_message("gui_panel::draw_spline(): parameter #1 must be a 2D array");
            gc<Array> appa = app->__value_array;

            DrawingPointData dp;
            dp.x = appa->__elements.at(0)->__value_double;
            dp.y = appa->__elements.at(1)->__value_double;
            p.push_back(dp);
        }

        panel->__drawing.push_back(new DrawingSpline(p, p.size()));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_draw_lines) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_lines");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_ARRAY__) connector->__error_message("gui_panel::draw_lines(): parameter #1 must be an array");
        
        vector<DrawingPointData> p;
        gc<Array> ap = d->__value_array;

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_lines(): canvas mode of this gui_panel must be true");

        for (int i = 0; i < ap->__elements.size(); i++) {
            gc<DataType> app = ap->__elements.at(i);
            if (app->__type != __TYPE_ARRAY__) connector->__error_message("gui_panel::draw_lines(): parameter #1 must be a 2D array");
            gc<Array> appa = app->__value_array;

            DrawingPointData dp;
            dp.x = appa->__elements.at(0)->__value_double;
            dp.y = appa->__elements.at(1)->__value_double;
            p.push_back(dp);
        }

        panel->__drawing.push_back(new DrawingLines(p, p.size()));
        // panel->__holder->Refresh();

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    
    } else if (func_id == __gui_draw_image_data) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_image_data");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_panel::draw_image_data(): parameter #1 must be an object");
        if (d->__value_object->__name != "image_data") connector->__error_message("gui_panel::draw_image_data(): parameter #1 must be an image_data");
        
        int x = 0;
        int y = 0;
        int w = -1;
        int h = -1;
        bool use_mask = false;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_image_data(): parameter #2 must be a number");
            x = e->__value_double;
        }

        if (params.size() > 2) {
            gc<DataType> e = connector->__get_value(params.at(2), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_image_data(): parameter #3 must be a number");
            y = e->__value_double;
        }

        if (params.size() > 3) {
            gc<DataType> e = connector->__get_value(params.at(3), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_image_data(): parameter #4 must be a number");
            w = e->__value_double;
        }

        if (params.size() > 4) {
            gc<DataType> e = connector->__get_value(params.at(4), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_image_data(): parameter #5 must be a number");
            h = e->__value_double;
        }

        if (params.size() > 5) {
            gc<DataType> e = connector->__get_value(params.at(5), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("gui_panel::draw_image_data(): parameter #6 must be a boolean");
            use_mask = e->__value_bool;
        }

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_image_data(): canvas mode of this gui_panel must be true");
        GUI_ImageData* img = (GUI_ImageData*) d->__value_object->__holder_pointer;

        if (!img->__is_loaded) connector->__error_message("gui_panel::draw_image_data(): image data does not have any data yet");

        if (w == -1) w = img->__w;
        if (h == -1) h = img->__h;

        panel->__drawing.push_back(new DrawingImageData(img, x, y, w, h, use_mask));

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_draw_image) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_image");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_OBJECT__) connector->__error_message("gui_panel::draw_image(): parameter #1 must be an object");
        if (d->__value_object->__name != "image") connector->__error_message("gui_panel::draw_image(): parameter #1 must be an image");
        
        int x = 0;
        int y = 0;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_image(): parameter #2 must be a number");
            x = e->__value_double;
        }

        if (params.size() > 2) {
            gc<DataType> e = connector->__get_value(params.at(2), caller_id);
            if (e->__type != __TYPE_DOUBLE__) connector->__error_message("gui_panel::draw_image(): parameter #3 must be a number");
            y = e->__value_double;
        }

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_image(): canvas mode of this gui_panel must be true");
        GUI_Image* img = (GUI_Image*) d->__value_object->__holder_pointer;

        panel->__drawing.push_back(new DrawingImage(img, x, y));

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);
    
    } else if (func_id == __gui_draw_gettextwidth) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_gettextwidth");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_panel::draw_gettextwidth(): parameter #1 must be a string");
        
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_gettextwidth(): canvas mode of this gui_panel must be true");

        wxClientDC dc(panel->__holder);

        if (panel->__current_font_size != 0) {
            int s = panel->__current_font_size;
            wxFontStyle style = (panel->__current_font_italic) ? wxFONTSTYLE_ITALIC : wxFONTSTYLE_NORMAL;
            wxFontWeight weight = (panel->__current_font_bold) ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL;

            if (panel->__current_font_face == "") {
                dc.SetFont(wxFont(s, wxFONTFAMILY_DEFAULT, style, weight, false));
            } else {
                dc.SetFont(wxFont(s, wxFONTFAMILY_DEFAULT, style, weight, false, panel->__current_font_face));
            }
        }

        wxSize size = dc.GetTextExtent(d->__value_string);
        
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = size.GetWidth();

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_draw_gettextheight) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_gettextheight");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_panel::draw_gettextheight(): parameter #1 must be a string");
        
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_gettextheight(): canvas mode of this gui_panel must be true");

        wxClientDC dc(panel->__holder);

        if (panel->__current_font_size != 0) {
            int s = panel->__current_font_size;
            wxFontStyle style = (panel->__current_font_italic) ? wxFONTSTYLE_ITALIC : wxFONTSTYLE_NORMAL;
            wxFontWeight weight = (panel->__current_font_bold) ? wxFONTWEIGHT_BOLD : wxFONTWEIGHT_NORMAL;

            if (panel->__current_font_face == "") {
                dc.SetFont(wxFont(s, wxFONTFAMILY_DEFAULT, style, weight, false));
            } else {
                dc.SetFont(wxFont(s, wxFONTFAMILY_DEFAULT, style, weight, false, panel->__current_font_face));
            }
        }

        wxSize size = dc.GetTextExtent(d->__value_string);
        
        result->__type = __TYPE_DOUBLE__;
        result->__value_double = size.GetHeight();

        connector->__remove_garbage(params.at(0), d);
    } else if (func_id == __gui_draw_now) {
        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_now(): canvas mode of this gui_panel must be true");

        wxClientDC dc(panel->__holder);
        dc.Clear();
        __panel_render(dc, panel);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;
    } else if (func_id == __gui_draw_save) {
        if (params.size() < 1) connector->__error_message_param("gui_panel::draw_save");
        gc<DataType> d = connector->__get_value(params.at(0), caller_id);
        if (d->__type != __TYPE_STRING__) connector->__error_message("gui_panel::draw_save(): parameter #1 must be a string");
        
        string path = d->__value_string;
        bool use_alpha = false;

        if (params.size() > 1) {
            gc<DataType> e = connector->__get_value(params.at(1), caller_id);
            if (e->__type != __TYPE_BOOL__) connector->__error_message("gui_panel::draw_save(): parameter #2 must be a boolean");
        
            use_alpha = e->__value_bool;
            connector->__remove_garbage(params.at(1), e);
        }

        GUI_Panel* panel = (GUI_Panel*) obj->__holder_pointer;
        if (!panel->__canvas_mode) connector->__error_message("gui_panel::draw_save(): canvas mode of this gui_panel must be true");

        wxBitmap bmp(panel->__holder->GetSize().GetWidth(), panel->__holder->GetSize().GetHeight());
        
        #ifndef __RPI__
            #ifndef __WXGTK__
                if (use_alpha) bmp.UseAlpha();
            #endif
        #endif
        
        wxMemoryDC dc;

        dc.SelectObject(bmp);

        if (use_alpha) {
            dc.SetBackground(*wxTRANSPARENT_BRUSH);
        } else {
            dc.SetBackground(*wxWHITE_BRUSH);
        }

        dc.Clear();
        __panel_render(dc, panel);
        dc.SelectObject(wxNullBitmap);

        bmp.SaveFile(path, wxBITMAP_TYPE_PNG);

        result->__type = __TYPE_BOOL__;
        result->__value_bool = true;

        connector->__remove_garbage(params.at(0), d);


    // GUI Event Loop

    } else if (func_id == __gui_start) {
        wxTheApp->OnRun();
    }

    return result;
}
