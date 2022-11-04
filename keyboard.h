//--------------------------------------------------------------------------------------
// File: Keyboard.h
//
// キーボードモジュール
//
//--------------------------------------------------------------------------------------
// 2020/06/07
//     DirectXTKより、なんちゃってC言語用にシェイプアップ改変
//
// Licensed under the MIT License.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
// http://go.microsoft.com/fwlink/?LinkID=615561
//--------------------------------------------------------------------------------------
#ifndef HAL_YOUHEI_KEYBOARD_H
#define HAL_YOUHEI_KEYBOARD_H
#pragma once


#include <windows.h>
#include <memory>


// キー列挙
typedef enum Keyboard_Keys_tag
{
    KK_NONE               = 0x0,
                            
    KK_BACK               = 0x8,
    KK_TAB                = 0x9,
                            
    KK_ENTER              = 0xd,
                            
    KK_PAUSE              = 0x13,
    KK_CAPSLOCK           = 0x14,
    KK_KANA               = 0x15,
                            
    KK_KANJI              = 0x19,
                            
    KK_ESCAPE             = 0x1b,
    KK_IMECONVERT         = 0x1c,
    KK_IMENOCONVERT       = 0x1d,
                            
    KK_SPACE              = 0x20,
    KK_PAGEUP             = 0x21,
    KK_PAGEDOWN           = 0x22,
    KK_END                = 0x23,
    KK_HOME               = 0x24,
    KK_LEFT               = 0x25,
    KK_UP                 = 0x26,
    KK_RIGHT              = 0x27,
    KK_DOWN               = 0x28,
    KK_SELECT             = 0x29,
    KK_PRINT              = 0x2a,
    KK_EXECUTE            = 0x2b,
    KK_PRINTSCREEN        = 0x2c,
    KK_INSERT             = 0x2d,
    KK_DELETE             = 0x2e,
    KK_HELP               = 0x2f,
    KK_D0                 = 0x30,
    KK_D1                 = 0x31,
    KK_D2                 = 0x32,
    KK_D3                 = 0x33,
    KK_D4                 = 0x34,
    KK_D5                 = 0x35,
    KK_D6                 = 0x36,
    KK_D7                 = 0x37,
    KK_D8                 = 0x38,
    KK_D9                 = 0x39,
                            
    KK_A                  = 0x41,
    KK_B                  = 0x42,
    KK_C                  = 0x43,
    KK_D                  = 0x44,
    KK_E                  = 0x45,
    KK_F                  = 0x46,
    KK_G                  = 0x47,
    KK_H                  = 0x48,
    KK_I                  = 0x49,
    KK_J                  = 0x4a,
    KK_K                  = 0x4b,
    KK_L                  = 0x4c,
    KK_M                  = 0x4d,
    KK_N                  = 0x4e,
    KK_O                  = 0x4f,
    KK_P                  = 0x50,
    KK_Q                  = 0x51,
    KK_R                  = 0x52,
    KK_S                  = 0x53,
    KK_T                  = 0x54,
    KK_U                  = 0x55,
    KK_V                  = 0x56,
    KK_W                  = 0x57,
    KK_X                  = 0x58,
    KK_Y                  = 0x59,
    KK_Z                  = 0x5a,
    KK_LEFTWINDOWS        = 0x5b,
    KK_RIGHTWINDOWS       = 0x5c,
    KK_APPS               = 0x5d,
                            
    KK_SLEEP              = 0x5f,
    KK_NUMPAD0            = 0x60,
    KK_NUMPAD1            = 0x61,
    KK_NUMPAD2            = 0x62,
    KK_NUMPAD3            = 0x63,
    KK_NUMPAD4            = 0x64,
    KK_NUMPAD5            = 0x65,
    KK_NUMPAD6            = 0x66,
    KK_NUMPAD7            = 0x67,
    KK_NUMPAD8            = 0x68,
    KK_NUMPAD9            = 0x69,
    KK_MULTIPLY           = 0x6a,
    KK_ADD                = 0x6b,
    KK_SEPARATOR          = 0x6c,
    KK_SUBTRACT           = 0x6d,
                            
    KK_DECIMAL            = 0x6e,
    KK_DIVIDE             = 0x6f,
    KK_F1                 = 0x70,
    KK_F2                 = 0x71,
    KK_F3                 = 0x72,
    KK_F4                 = 0x73,
    KK_F5                 = 0x74,
    KK_F6                 = 0x75,
    KK_F7                 = 0x76,
    KK_F8                 = 0x77,
    KK_F9                 = 0x78,
    KK_F10                = 0x79,
    KK_F11                = 0x7a,
    KK_F12                = 0x7b,
    KK_F13                = 0x7c,
    KK_F14                = 0x7d,
    KK_F15                = 0x7e,
    KK_F16                = 0x7f,
    KK_F17                = 0x80,
    KK_F18                = 0x81,
    KK_F19                = 0x82,
    KK_F20                = 0x83,
    KK_F21                = 0x84,
    KK_F22                = 0x85,
    KK_F23                = 0x86,
    KK_F24                = 0x87,
                            
    KK_NUMLOCK            = 0x90,
    KK_SCROLL             = 0x91,
                            
    KK_LEFTSHIFT          = 0xa0,
    KK_RIGHTSHIFT         = 0xa1,
    KK_LEFTCONTROL        = 0xa2,
    KK_RIGHTCONTROL       = 0xa3,
    KK_LEFTALT            = 0xa4,
    KK_RIGHTALT           = 0xa5,
    KK_BROWSERBACK        = 0xa6,
    KK_BROWSERFORWARD     = 0xa7,
    KK_BROWSERREFRESH     = 0xa8,
    KK_BROWSERSTOP        = 0xa9,
    KK_BROWSERSEARCH      = 0xaa,
    KK_BROWSERFAVORITES   = 0xab,
    KK_BROWSERHOME        = 0xac,
    KK_VOLUMEMUTE         = 0xad,
    KK_VOLUMEDOWN         = 0xae,
    KK_VOLUMEUP           = 0xaf,
    KK_MEDIANEXTTRACK     = 0xb0,
    KK_MEDIAPREVIOUSTRACK = 0xb1,
    KK_MEDIASTOP          = 0xb2,
    KK_MEDIAPLAYPAUSE     = 0xb3,
    KK_LAUNCHMAIL         = 0xb4,
    KK_SELECTMEDIA        = 0xb5,
    KK_LAUNCHAPPLICATION1 = 0xb6,
    KK_LAUNCHAPPLICATION2 = 0xb7,
                            
    KK_OEMSEMICOLON       = 0xba,
    KK_OEMPLUS            = 0xbb,
    KK_OEMCOMMA           = 0xbc,
    KK_OEMMINUS           = 0xbd,
    KK_OEMPERIOD          = 0xbe,
    KK_OEMQUESTION        = 0xbf,
    KK_OEMTILDE           = 0xc0,
                            
    KK_OEMOPENBRACKETS    = 0xdb,
    KK_OEMPIPE            = 0xdc,
    KK_OEMCLOSEBRACKETS   = 0xdd,
    KK_OEMQUOTES          = 0xde,
    KK_OEM8               = 0xdf,
                            
    KK_OEMBACKSLASH       = 0xe2,
                            
    KK_PROCESSKEY         = 0xe5,
                            
    KK_OEMCOPY            = 0xf2,
    KK_OEMAUTO            = 0xf3,
    KK_OEMENLW            = 0xf4,
                            
    KK_ATTN               = 0xf6,
    KK_CRSEL              = 0xf7,
    KK_EXSEL              = 0xf8,
    KK_ERASEEOF           = 0xf9,
    KK_PLAY               = 0xfa,
    KK_ZOOM               = 0xfb,
                            
    KK_PA1                = 0xfd,
    KK_OEMCLEAR           = 0xfe,
} Keyboard_Keys;


// キーボード状態構造体
typedef struct Keyboard_State_tag
{
    bool Reserved0 : 8;
    bool Back : 1;              // VK_BACK, 0x8
    bool Tab : 1;               // VK_TAB, 0x9
    bool Reserved1 : 3;
    bool Enter : 1;             // VK_RETURN, 0xD
    bool Reserved2 : 2;
    bool Reserved3 : 3;
    bool Pause : 1;             // VK_PAUSE, 0x13
    bool CapsLock : 1;          // VK_CAPITAL, 0x14
    bool Kana : 1;              // VK_KANA, 0x15
    bool Reserved4 : 2;
    bool Reserved5 : 1;
    bool Kanji : 1;             // VK_KANJI, 0x19
    bool Reserved6 : 1;
    bool Escape : 1;            // VK_ESCAPE, 0x1B
    bool ImeConvert : 1;        // VK_CONVERT, 0x1C
    bool ImeNoConvert : 1;      // VK_NONCONVERT, 0x1D
    bool Reserved7 : 2;
    bool Space : 1;             // VK_SPACE, 0x20
    bool PageUp : 1;            // VK_PRIOR, 0x21
    bool PageDown : 1;          // VK_NEXT, 0x22
    bool End : 1;               // VK_END, 0x23
    bool Home : 1;              // VK_HOME, 0x24
    bool Left : 1;              // VK_LEFT, 0x25
    bool Up : 1;                // VK_UP, 0x26
    bool Right : 1;             // VK_RIGHT, 0x27
    bool Down : 1;              // VK_DOWN, 0x28
    bool Select : 1;            // VK_SELECT, 0x29
    bool Print : 1;             // VK_PRINT, 0x2A
    bool Execute : 1;           // VK_EXECUTE, 0x2B
    bool PrintScreen : 1;       // VK_SNAPSHOT, 0x2C
    bool Insert : 1;            // VK_INSERT, 0x2D
    bool Delete : 1;            // VK_DELETE, 0x2E
    bool Help : 1;              // VK_HELP, 0x2F
    bool D0 : 1;                // 0x30
    bool D1 : 1;                // 0x31
    bool D2 : 1;                // 0x32
    bool D3 : 1;                // 0x33
    bool D4 : 1;                // 0x34
    bool D5 : 1;                // 0x35
    bool D6 : 1;                // 0x36
    bool D7 : 1;                // 0x37
    bool D8 : 1;                // 0x38
    bool D9 : 1;                // 0x39
    bool Reserved8 : 6;
    bool Reserved9 : 1;
    bool A : 1;                 // 0x41
    bool B : 1;                 // 0x42
    bool C : 1;                 // 0x43
    bool D : 1;                 // 0x44
    bool E : 1;                 // 0x45
    bool F : 1;                 // 0x46
    bool G : 1;                 // 0x47
    bool H : 1;                 // 0x48
    bool I : 1;                 // 0x49
    bool J : 1;                 // 0x4A
    bool K : 1;                 // 0x4B
    bool L : 1;                 // 0x4C
    bool M : 1;                 // 0x4D
    bool N : 1;                 // 0x4E
    bool O : 1;                 // 0x4F
    bool P : 1;                 // 0x50
    bool Q : 1;                 // 0x51
    bool R : 1;                 // 0x52
    bool S : 1;                 // 0x53
    bool T : 1;                 // 0x54
    bool U : 1;                 // 0x55
    bool V : 1;                 // 0x56
    bool W : 1;                 // 0x57
    bool X : 1;                 // 0x58
    bool Y : 1;                 // 0x59
    bool Z : 1;                 // 0x5A
    bool LeftWindows : 1;       // VK_LWIN, 0x5B
    bool RightWindows : 1;      // VK_RWIN, 0x5C
    bool Apps : 1;              // VK_APPS, 0x5D
    bool Reserved10 : 1;
    bool Sleep : 1;             // VK_SLEEP, 0x5F
    bool NumPad0 : 1;           // VK_NUMPAD0, 0x60
    bool NumPad1 : 1;           // VK_NUMPAD1, 0x61
    bool NumPad2 : 1;           // VK_NUMPAD2, 0x62
    bool NumPad3 : 1;           // VK_NUMPAD3, 0x63
    bool NumPad4 : 1;           // VK_NUMPAD4, 0x64
    bool NumPad5 : 1;           // VK_NUMPAD5, 0x65
    bool NumPad6 : 1;           // VK_NUMPAD6, 0x66
    bool NumPad7 : 1;           // VK_NUMPAD7, 0x67
    bool NumPad8 : 1;           // VK_NUMPAD8, 0x68
    bool NumPad9 : 1;           // VK_NUMPAD9, 0x69
    bool Multiply : 1;          // VK_MULTIPLY, 0x6A
    bool Add : 1;               // VK_ADD, 0x6B
    bool Separator : 1;         // VK_SEPARATOR, 0x6C
    bool Subtract : 1;          // VK_SUBTRACT, 0x6D
    bool Decimal : 1;           // VK_DECIMANL, 0x6E
    bool Divide : 1;            // VK_DIVIDE, 0x6F
    bool F1 : 1;                // VK_F1, 0x70
    bool F2 : 1;                // VK_F2, 0x71
    bool F3 : 1;                // VK_F3, 0x72
    bool F4 : 1;                // VK_F4, 0x73
    bool F5 : 1;                // VK_F5, 0x74
    bool F6 : 1;                // VK_F6, 0x75
    bool F7 : 1;                // VK_F7, 0x76
    bool F8 : 1;                // VK_F8, 0x77
    bool F9 : 1;                // VK_F9, 0x78
    bool F10 : 1;               // VK_F10, 0x79
    bool F11 : 1;               // VK_F11, 0x7A
    bool F12 : 1;               // VK_F12, 0x7B
    bool F13 : 1;               // VK_F13, 0x7C
    bool F14 : 1;               // VK_F14, 0x7D
    bool F15 : 1;               // VK_F15, 0x7E
    bool F16 : 1;               // VK_F16, 0x7F
    bool F17 : 1;               // VK_F17, 0x80
    bool F18 : 1;               // VK_F18, 0x81
    bool F19 : 1;               // VK_F19, 0x82
    bool F20 : 1;               // VK_F20, 0x83
    bool F21 : 1;               // VK_F21, 0x84
    bool F22 : 1;               // VK_F22, 0x85
    bool F23 : 1;               // VK_F23, 0x86
    bool F24 : 1;               // VK_F24, 0x87
    bool Reserved11 : 8;
    bool NumLock : 1;           // VK_NUMLOCK, 0x90
    bool Scroll : 1;            // VK_SCROLL, 0x91
    bool Reserved12 : 6;
    bool Reserved13 : 8;
    bool LeftShift : 1;         // VK_LSHIFT, 0xA0
    bool RightShift : 1;        // VK_RSHIFT, 0xA1
    bool LeftControl : 1;       // VK_LCONTROL, 0xA2
    bool RightControl : 1;      // VK_RCONTROL, 0xA3
    bool LeftAlt : 1;           // VK_LMENU, 0xA4
    bool RightAlt : 1;          // VK_RMENU, 0xA5
    bool BrowserBack : 1;       // VK_BROWSER_BACK, 0xA6
    bool BrowserForward : 1;    // VK_BROWSER_FORWARD, 0xA7
    bool BrowserRefresh : 1;    // VK_BROWSER_REFRESH, 0xA8
    bool BrowserStop : 1;       // VK_BROWSER_STOP, 0xA9
    bool BrowserSearch : 1;     // VK_BROWSER_SEARCH, 0xAA
    bool BrowserFavorites : 1;  // VK_BROWSER_FAVORITES, 0xAB
    bool BrowserHome : 1;       // VK_BROWSER_HOME, 0xAC
    bool VolumeMute : 1;        // VK_VOLUME_MUTE, 0xAD
    bool VolumeDown : 1;        // VK_VOLUME_DOWN, 0xAE
    bool VolumeUp : 1;          // VK_VOLUME_UP, 0xAF
    bool MediaNextTrack : 1;    // VK_MEDIA_NEXT_TRACK, 0xB0
    bool MediaPreviousTrack : 1;// VK_MEDIA_PREV_TRACK, 0xB1
    bool MediaStop : 1;         // VK_MEDIA_STOP, 0xB2
    bool MediaPlayPause : 1;    // VK_MEDIA_PLAY_PAUSE, 0xB3
    bool LaunchMail : 1;        // VK_LAUNCH_MAIL, 0xB4
    bool SelectMedia : 1;       // VK_LAUNCH_MEDIA_SELECT, 0xB5
    bool LaunchApplication1 : 1;// VK_LAUNCH_APP1, 0xB6
    bool LaunchApplication2 : 1;// VK_LAUNCH_APP2, 0xB7
    bool Reserved14 : 2;
    bool OemSemicolon : 1;      // VK_OEM_1, 0xBA
    bool OemPlus : 1;           // VK_OEM_PLUS, 0xBB
    bool OemComma : 1;          // VK_OEM_COMMA, 0xBC
    bool OemMinus : 1;          // VK_OEM_MINUS, 0xBD
    bool OemPeriod : 1;         // VK_OEM_PERIOD, 0xBE
    bool OemQuestion : 1;       // VK_OEM_2, 0xBF
    bool OemTilde : 1;          // VK_OEM_3, 0xC0
    bool Reserved15 : 7;
    bool Reserved16 : 8;
    bool Reserved17 : 8;
    bool Reserved18 : 3;
    bool OemOpenBrackets : 1;   // VK_OEM_4, 0xDB
    bool OemPipe : 1;           // VK_OEM_5, 0xDC
    bool OemCloseBrackets : 1;  // VK_OEM_6, 0xDD
    bool OemQuotes : 1;         // VK_OEM_7, 0xDE
    bool Oem8 : 1;              // VK_OEM_8, 0xDF
    bool Reserved19 : 2;
    bool OemBackslash : 1;      // VK_OEM_102, 0xE2
    bool Reserved20 : 2;
    bool ProcessKey : 1;        // VK_PROCESSKEY, 0xE5
    bool Reserved21 : 2;
    bool Reserved22 : 8;
    bool Reserved23 : 2;
    bool OemCopy : 1;           // 0XF2
    bool OemAuto : 1;           // 0xF3
    bool OemEnlW : 1;           // 0xF4
    bool Reserved24 : 1;
    bool Attn : 1;              // VK_ATTN, 0xF6
    bool Crsel : 1;             // VK_CRSEL, 0xF7
    bool Exsel : 1;             // VK_EXSEL, 0xF8
    bool EraseEof : 1;          // VK_EREOF, 0xF9
    bool Play : 1;              // VK_PLAY, 0xFA
    bool Zoom : 1;              // VK_ZOOM, 0xFB
    bool Reserved25 : 1;
    bool Pa1 : 1;               // VK_PA1, 0xFD
    bool OemClear : 1;          // VK_OEM_CLEAR, 0xFE
    bool Reserved26 : 1;
} Keyboard_State;


// キーボードモジュールの初期化
void Keyboard_Initialize(void);

// キーボードの現在のキー毎の状態を取得する
bool Keyboard_IsKeyDown(Keyboard_Keys key);
bool Keyboard_IsKeyUp(Keyboard_Keys key);

// キーボードの現在の状態を取得する
const Keyboard_State* Keyboard_GetState(void);

// キーボードの状態からキー毎の状態を取得する
bool Keyboard_IsKeyDown(Keyboard_Keys key, const Keyboard_State* pState);
bool Keyboard_IsKeyUp(Keyboard_Keys key, const Keyboard_State* pState);

// キーボードの状態をリセットする
void Keyboard_Reset(void);

// キーボード制御のためのウォンどうメッセージプロシージャフック関数
void Keyboard_ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam);


//
// For a Win32 desktop application, call this function from your Window Message Procedure
//
// LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
// {
//     switch (message)
//     {
//
//     case WM_ACTIVATEAPP:
//     case WM_KEYDOWN:
//     case WM_SYSKEYDOWN:
//     case WM_KEYUP:
//     case WM_SYSKEYUP:
//         Keyboard_ProcessMessage(message, wParam, lParam);
//         break;
//
//     }
// }
//


#endif // HAL_YOUHEI_KEYBOARD_H
