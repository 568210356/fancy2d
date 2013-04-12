#include "fuiControl.h"

#include "fuiContainer.h"

#include "fcyMisc/fcyStringHelper.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
const F2DINPUTKEYCODE fuiHelper::VKCodeToF2DKeyCodeTable[256] = 
{
	F2DINPUTKEYCODE_UNKNOWN,
	F2DINPUTKEYCODE_UNKNOWN,    // 1 VK_LBUTTON
	F2DINPUTKEYCODE_UNKNOWN,    // 2 VK_RBUTTON
	F2DINPUTKEYCODE_UNKNOWN,    // 3 VK_CANCEL
	F2DINPUTKEYCODE_UNKNOWN,    // 4 VK_MBUTTON
	F2DINPUTKEYCODE_UNKNOWN,    // 5 VK_XBUTTON1
	F2DINPUTKEYCODE_UNKNOWN,    // 6 VK_XBUTTON2
	F2DINPUTKEYCODE_UNKNOWN,    // 7
	F2DINPUTKEYCODE_BACK,       // 8 VK_BACK = Backspace
	F2DINPUTKEYCODE_TAB,        // 9 VK_TAB = Tab
	F2DINPUTKEYCODE_UNKNOWN,    // 10
	F2DINPUTKEYCODE_UNKNOWN,    // 11
	F2DINPUTKEYCODE_UNKNOWN,    // 12 VK_CLEAR = Clear
	F2DINPUTKEYCODE_RETURN,     // 13 VK_RETURN = Enter
	F2DINPUTKEYCODE_UNKNOWN,    // 14
	F2DINPUTKEYCODE_UNKNOWN,    // 15
	F2DINPUTKEYCODE_LSHIFT,     // 16 VK_SHIFT = Shift
	F2DINPUTKEYCODE_LCONTROL,   // 17 VK_CONTROL = Ctrl
	F2DINPUTKEYCODE_LMENU,      // 18 VK_MENU = Alt
	F2DINPUTKEYCODE_PAUSE,      // 19 VK_PAUSE = Pause
	F2DINPUTKEYCODE_CAPITAL,    // 20 VK_CAPITAL = Caps Lock
	F2DINPUTKEYCODE_KANA,       // 21 VK_KANA
	F2DINPUTKEYCODE_UNKNOWN,    // 22
	F2DINPUTKEYCODE_UNKNOWN,    // 23 VK_JUNJA
	F2DINPUTKEYCODE_UNKNOWN,    // 24 VK_FINAL
	F2DINPUTKEYCODE_KANJI,      // 25 VK_HANJA
	F2DINPUTKEYCODE_UNKNOWN,    // 26
	F2DINPUTKEYCODE_ESCAPE,     // 27 VK_ESCAPE = Esc
	F2DINPUTKEYCODE_CONVERT,    // 28 VK_CONVERT
	F2DINPUTKEYCODE_NOCONVERT,  // 29 VK_NONCONVERT
	F2DINPUTKEYCODE_UNKNOWN,    // 30 VK_ACCEPT
	F2DINPUTKEYCODE_UNKNOWN,    // 31 VK_MODECHANGE
	F2DINPUTKEYCODE_SPACE,      // 32 VK_SPACE = Space
	F2DINPUTKEYCODE_PRIOR,      // 33 VK_PRIOR = Page Up
	F2DINPUTKEYCODE_NEXT,       // 34 VK_NEXT = Page Down
	F2DINPUTKEYCODE_END,        // 35 VK_END = End
	F2DINPUTKEYCODE_HOME,       // 36 VK_HOME = Home
	F2DINPUTKEYCODE_LEFT,       // 37 VK_LEFT = Left Arrow
	F2DINPUTKEYCODE_UP,         // 38 VK_UP	= Up Arrow
	F2DINPUTKEYCODE_RIGHT,      // 39 VK_RIGHT = Right Arrow
	F2DINPUTKEYCODE_DOWN,       // 40 VK_DOWN = Down Arrow
	F2DINPUTKEYCODE_UNKNOWN,    // 41 VK_SELECT = Select
	F2DINPUTKEYCODE_UNKNOWN,    // 42 VK_PRINT = Print
	F2DINPUTKEYCODE_UNKNOWN,    // 43 VK_EXECUTE = Execute
	F2DINPUTKEYCODE_UNKNOWN,    // 44 VK_SNAPSHOT = Snapshot
	F2DINPUTKEYCODE_INSERT,     // 45 VK_INSERT = Insert
	F2DINPUTKEYCODE_DELETE,     // 46 VK_DELETE = Delete
	F2DINPUTKEYCODE_UNKNOWN,    // 47 VK_HELP = Help
	F2DINPUTKEYCODE_0,          // 48 0
	F2DINPUTKEYCODE_1,          // 49 1
	F2DINPUTKEYCODE_2,          // 50 2
	F2DINPUTKEYCODE_3,          // 51 3
	F2DINPUTKEYCODE_4,          // 52 4
	F2DINPUTKEYCODE_5,          // 53 5
	F2DINPUTKEYCODE_6,          // 54 6
	F2DINPUTKEYCODE_7,          // 55 7
	F2DINPUTKEYCODE_8,          // 56 8
	F2DINPUTKEYCODE_9,          // 57 9
	F2DINPUTKEYCODE_UNKNOWN,    // 58
	F2DINPUTKEYCODE_UNKNOWN,    // 59
	F2DINPUTKEYCODE_UNKNOWN,    // 60
	F2DINPUTKEYCODE_UNKNOWN,    // 61
	F2DINPUTKEYCODE_UNKNOWN,    // 62
	F2DINPUTKEYCODE_UNKNOWN,    // 63
	F2DINPUTKEYCODE_UNKNOWN,    // 64
	F2DINPUTKEYCODE_A,          // 65 A
	F2DINPUTKEYCODE_B,          // 66 B
	F2DINPUTKEYCODE_C,          // 67 C
	F2DINPUTKEYCODE_D,          // 68 D
	F2DINPUTKEYCODE_E,          // 69 E
	F2DINPUTKEYCODE_F,          // 70 F
	F2DINPUTKEYCODE_G,          // 71 G
	F2DINPUTKEYCODE_H,          // 72 H
	F2DINPUTKEYCODE_I,          // 73 I
	F2DINPUTKEYCODE_J,          // 74 J
	F2DINPUTKEYCODE_K,          // 75 K
	F2DINPUTKEYCODE_L,          // 76 L
	F2DINPUTKEYCODE_M,          // 77 M
	F2DINPUTKEYCODE_N,          // 78 N
	F2DINPUTKEYCODE_O,          // 79 O
	F2DINPUTKEYCODE_P,          // 80 P
	F2DINPUTKEYCODE_Q,          // 81 Q
	F2DINPUTKEYCODE_R,          // 82 R
	F2DINPUTKEYCODE_S,          // 83 S
	F2DINPUTKEYCODE_T,          // 84 T
	F2DINPUTKEYCODE_U,          // 85 U
	F2DINPUTKEYCODE_V,          // 86 V
	F2DINPUTKEYCODE_W,          // 87 W
	F2DINPUTKEYCODE_X,          // 88 X
	F2DINPUTKEYCODE_Y,          // 89 Y
	F2DINPUTKEYCODE_Z,          // 90 Z
	F2DINPUTKEYCODE_LWIN,       // 91 VK_LWIN
	F2DINPUTKEYCODE_RWIN,       // 92 VK_RWIN
	F2DINPUTKEYCODE_APPS,       // 93 VK_APPS
	F2DINPUTKEYCODE_UNKNOWN,    // 94
	F2DINPUTKEYCODE_SLEEP,      // 95 VK_SLEEP
	F2DINPUTKEYCODE_NUMPAD0,    // 96 VK_NUMPAD0 = С���� 0
	F2DINPUTKEYCODE_NUMPAD1,    // 97 VK_NUMPAD1 = С���� 1
	F2DINPUTKEYCODE_NUMPAD2,    // 98 VK_NUMPAD2 = С���� 2
	F2DINPUTKEYCODE_NUMPAD3,    // 99 VK_NUMPAD3 = С���� 3
	F2DINPUTKEYCODE_NUMPAD4,    // 100 VK_NUMPAD4 = С���� 4
	F2DINPUTKEYCODE_NUMPAD5,    // 101 VK_NUMPAD5 = С���� 5
	F2DINPUTKEYCODE_NUMPAD6,    // 102 VK_NUMPAD6 = С���� 6
	F2DINPUTKEYCODE_NUMPAD7,    // 103 VK_NUMPAD7 = С���� 7
	F2DINPUTKEYCODE_NUMPAD8,    // 104 VK_NUMPAD8 = С���� 8
	F2DINPUTKEYCODE_NUMPAD9,    // 105 VK_NUMPAD9 = С���� 9
	F2DINPUTKEYCODE_MULTIPLY,   // 106 VK_MULTIPLY = С���� *
	F2DINPUTKEYCODE_ADD,        // 107 VK_ADD = С���� +
	F2DINPUTKEYCODE_NUMPADENTER,// 108 VK_SEPARATOR = С���� Enter
	F2DINPUTKEYCODE_SUBTRACT,   // 109 VK_SUBTRACT = С���� -
	F2DINPUTKEYCODE_DECIMAL,    // 110 VK_DECIMAL = С���� .
	F2DINPUTKEYCODE_DIVIDE,     // 111 VK_DIVIDE = С���� /
	F2DINPUTKEYCODE_F1,         // 112 VK_F1 = F1
	F2DINPUTKEYCODE_F2,         // 113 VK_F2 = F2
	F2DINPUTKEYCODE_F3,         // 114 VK_F3 = F3
	F2DINPUTKEYCODE_F4,         // 115 VK_F4 = F4
	F2DINPUTKEYCODE_F5,         // 116 VK_F5 = F5
	F2DINPUTKEYCODE_F6,         // 117 VK_F6 = F6
	F2DINPUTKEYCODE_F7,         // 118 VK_F7 = F7
	F2DINPUTKEYCODE_F8,         // 119 VK_F8 = F8
	F2DINPUTKEYCODE_F9,         // 120 VK_F9 = F9
	F2DINPUTKEYCODE_F10,        // 121 VK_F10 = F10
	F2DINPUTKEYCODE_F11,        // 122 VK_F11 = F11
	F2DINPUTKEYCODE_F12,        // 123 VK_F12 = F12
	F2DINPUTKEYCODE_F13,        // 124 VK_F13
	F2DINPUTKEYCODE_F14,        // 125 VK_F14
	F2DINPUTKEYCODE_F15,        // 126 VK_F15
	F2DINPUTKEYCODE_UNKNOWN,    // 127 VK_F16
	F2DINPUTKEYCODE_UNKNOWN,    // 128 VK_F17
	F2DINPUTKEYCODE_UNKNOWN,    // 129 VK_F18
	F2DINPUTKEYCODE_UNKNOWN,    // 130 VK_F19
	F2DINPUTKEYCODE_UNKNOWN,    // 131 VK_F20
	F2DINPUTKEYCODE_UNKNOWN,    // 132 VK_F21
	F2DINPUTKEYCODE_UNKNOWN,    // 133 VK_F22
	F2DINPUTKEYCODE_UNKNOWN,    // 134 VK_F23
	F2DINPUTKEYCODE_UNKNOWN,    // 135 VK_F24
	F2DINPUTKEYCODE_UNKNOWN,    // 136
	F2DINPUTKEYCODE_UNKNOWN,    // 137
	F2DINPUTKEYCODE_UNKNOWN,    // 138
	F2DINPUTKEYCODE_UNKNOWN,    // 139
	F2DINPUTKEYCODE_UNKNOWN,    // 140
	F2DINPUTKEYCODE_UNKNOWN,    // 141
	F2DINPUTKEYCODE_UNKNOWN,    // 142
	F2DINPUTKEYCODE_UNKNOWN,    // 143
	F2DINPUTKEYCODE_NUMLOCK,    // 144 VK_NUMLOCK = Num Lock
	F2DINPUTKEYCODE_SCROLL,     // 145 VK_SCROLL = Scroll
	F2DINPUTKEYCODE_UNKNOWN,    // 146
	F2DINPUTKEYCODE_UNKNOWN,    // 147
	F2DINPUTKEYCODE_UNKNOWN,    // 148
	F2DINPUTKEYCODE_UNKNOWN,    // 149
	F2DINPUTKEYCODE_UNKNOWN,    // 150
	F2DINPUTKEYCODE_UNKNOWN,    // 151
	F2DINPUTKEYCODE_UNKNOWN,    // 152
	F2DINPUTKEYCODE_UNKNOWN,    // 153
	F2DINPUTKEYCODE_UNKNOWN,    // 154
	F2DINPUTKEYCODE_UNKNOWN,    // 155
	F2DINPUTKEYCODE_UNKNOWN,    // 156
	F2DINPUTKEYCODE_UNKNOWN,    // 157
	F2DINPUTKEYCODE_UNKNOWN,    // 158
	F2DINPUTKEYCODE_UNKNOWN,    // 159
	F2DINPUTKEYCODE_LSHIFT,     // 160 VK_LSHIFT
	F2DINPUTKEYCODE_RSHIFT,     // 161 VK_RSHIFT
	F2DINPUTKEYCODE_LCONTROL,   // 162 VK_LCONTROL
	F2DINPUTKEYCODE_RCONTROL,   // 163 VK_RCONTROL
	F2DINPUTKEYCODE_LMENU,      // 164 VK_LMENU
	F2DINPUTKEYCODE_RMENU,      // 165 VK_RMENU
	F2DINPUTKEYCODE_WEBBACK,    // 166 VK_BROWSER_BACK
	F2DINPUTKEYCODE_WEBFORWARD, // 167 VK_BROWSER_FORWARD
	F2DINPUTKEYCODE_WEBREFRESH, // 168 VK_BROWSER_REFRESH
	F2DINPUTKEYCODE_WEBSTOP,    // 169 VK_BROWSER_STOP
	F2DINPUTKEYCODE_WEBSEARCH,  // 170 VK_BROWSER_SEARCH
	F2DINPUTKEYCODE_WEBFAVORITES, // 171 VK_BROWSER_FAVORITES
	F2DINPUTKEYCODE_WEBHOME,    // 172 VK_BROWSER_HOME
	F2DINPUTKEYCODE_MUTE,       // 173 VK_VOLUME_MUTE
	F2DINPUTKEYCODE_VOLUMEDOWN, // 174 VK_VOLUME_DOWN
	F2DINPUTKEYCODE_VOLUMEUP,   // 175 VK_VOLUME_UP
	F2DINPUTKEYCODE_NEXTTRACK,  // 176 VK_MEDIA_NEXT_TRACK
	F2DINPUTKEYCODE_PREVTRACK,  // 177 VK_MEDIA_PREV_TRACK
	F2DINPUTKEYCODE_MEDIASTOP,  // 178 VK_MEDIA_STOP
	F2DINPUTKEYCODE_PLAYPAUSE,  // 179 VK_MEDIA_PLAY_PAUSE
	F2DINPUTKEYCODE_MAIL,       // 180 VK_LAUNCH_MAIL
	F2DINPUTKEYCODE_MEDIASELECT,// 181 VK_LAUNCH_MEDIA_SELECT
	F2DINPUTKEYCODE_UNKNOWN,    // 182 VK_LAUNCH_APP1
	F2DINPUTKEYCODE_UNKNOWN,    // 183 VK_LAUNCH_APP2
	F2DINPUTKEYCODE_UNKNOWN,    // 184
	F2DINPUTKEYCODE_UNKNOWN,    // 185
	F2DINPUTKEYCODE_SEMICOLON,  // 186 VK_OEM_1	= ; :
	F2DINPUTKEYCODE_EQUALS,     // 187 VK_OEM_PLUS = = +
	F2DINPUTKEYCODE_COMMA,      // 188 VK_OEM_COMMA = ,
	F2DINPUTKEYCODE_MINUS,      // 189 VK_OEM_MINUS = - _
	F2DINPUTKEYCODE_PERIOD,     // 190 VK_OEM_PERIOD = .
	F2DINPUTKEYCODE_SLASH,      // 191 VK_OEM_2 = / ?
	F2DINPUTKEYCODE_GRAVE,      // 192 VK_OEM_3 = ` ~
	F2DINPUTKEYCODE_UNKNOWN,    // 193
	F2DINPUTKEYCODE_UNKNOWN,    // 194
	F2DINPUTKEYCODE_UNKNOWN,    // 195
	F2DINPUTKEYCODE_UNKNOWN,    // 196
	F2DINPUTKEYCODE_UNKNOWN,    // 197
	F2DINPUTKEYCODE_UNKNOWN,    // 198
	F2DINPUTKEYCODE_UNKNOWN,    // 199
	F2DINPUTKEYCODE_UNKNOWN,    // 200
	F2DINPUTKEYCODE_UNKNOWN,    // 201
	F2DINPUTKEYCODE_UNKNOWN,    // 202
	F2DINPUTKEYCODE_UNKNOWN,    // 203
	F2DINPUTKEYCODE_UNKNOWN,    // 204
	F2DINPUTKEYCODE_UNKNOWN,    // 205
	F2DINPUTKEYCODE_UNKNOWN,    // 206
	F2DINPUTKEYCODE_UNKNOWN,    // 207
	F2DINPUTKEYCODE_UNKNOWN,    // 208
	F2DINPUTKEYCODE_UNKNOWN,    // 209
	F2DINPUTKEYCODE_UNKNOWN,    // 210
	F2DINPUTKEYCODE_UNKNOWN,    // 211
	F2DINPUTKEYCODE_UNKNOWN,    // 212
	F2DINPUTKEYCODE_UNKNOWN,    // 213
	F2DINPUTKEYCODE_UNKNOWN,    // 214
	F2DINPUTKEYCODE_UNKNOWN,    // 215
	F2DINPUTKEYCODE_UNKNOWN,    // 216
	F2DINPUTKEYCODE_UNKNOWN,    // 217
	F2DINPUTKEYCODE_UNKNOWN,    // 218
	F2DINPUTKEYCODE_LBRACKET,   // 219 VK_OEM_4 = [ {
	F2DINPUTKEYCODE_BACKSLASH,  // 220 VK_OEM_5 = \ |
	F2DINPUTKEYCODE_RBRACKET,   // 221 VK_OEM_6 = ] }
	F2DINPUTKEYCODE_APOSTROPHE, // 222 VK_OEM_7 = ' "
	F2DINPUTKEYCODE_UNKNOWN,    // 223 VK_OEM_8
	F2DINPUTKEYCODE_UNKNOWN,    // 224
	F2DINPUTKEYCODE_UNKNOWN,    // 225
	F2DINPUTKEYCODE_OEM_102,    // 226 VK_OEM_102
	F2DINPUTKEYCODE_UNKNOWN,    // 227
	F2DINPUTKEYCODE_UNKNOWN,    // 228
	F2DINPUTKEYCODE_UNKNOWN,    // 229 VK_PROCESSKEY
	F2DINPUTKEYCODE_UNKNOWN,    // 230
	F2DINPUTKEYCODE_UNKNOWN,    // 231 VK_PACKET
	F2DINPUTKEYCODE_UNKNOWN,    // 232
	F2DINPUTKEYCODE_UNKNOWN,    // 233
	F2DINPUTKEYCODE_UNKNOWN,    // 234
	F2DINPUTKEYCODE_UNKNOWN,    // 235
	F2DINPUTKEYCODE_UNKNOWN,    // 236
	F2DINPUTKEYCODE_UNKNOWN,    // 237
	F2DINPUTKEYCODE_UNKNOWN,    // 238
	F2DINPUTKEYCODE_UNKNOWN,    // 239
	F2DINPUTKEYCODE_UNKNOWN,    // 240
	F2DINPUTKEYCODE_UNKNOWN,    // 241
	F2DINPUTKEYCODE_UNKNOWN,    // 242
	F2DINPUTKEYCODE_UNKNOWN,    // 243
	F2DINPUTKEYCODE_UNKNOWN,    // 244
	F2DINPUTKEYCODE_UNKNOWN,    // 245
	F2DINPUTKEYCODE_UNKNOWN,    // 246 VK_ATTN
	F2DINPUTKEYCODE_UNKNOWN,    // 247 VK_CRSEL
	F2DINPUTKEYCODE_UNKNOWN,    // 248 VK_EXSEL
	F2DINPUTKEYCODE_UNKNOWN,    // 249 VK_EREOF
	F2DINPUTKEYCODE_UNKNOWN,    // 250 VK_PLAY
	F2DINPUTKEYCODE_UNKNOWN,    // 251 VK_ZOOM
	F2DINPUTKEYCODE_UNKNOWN,    // 252 VK_NONAME
	F2DINPUTKEYCODE_UNKNOWN,    // 253 VK_PA1	
	F2DINPUTKEYCODE_UNKNOWN,    // 254 VK_OEM_CLEAR
	F2DINPUTKEYCODE_UNKNOWN     // 255
};

F2DINPUTKEYCODE fuiHelper::VKCodeToF2DKeyCode(fByte VKCode)
{
	return VKCodeToF2DKeyCodeTable[VKCode];
}

fBool fuiHelper::AttributeToBool(fcyXmlNode* pNode, fcStrW Attribute, fBool& pOut)
{
	wstring tValue = fcyStringHelper::ToLower(pNode->GetAttribute(Attribute));
	
	if(tValue == L"true")
	{
		pOut = true;
		return true;
	}
	else if(tValue == L"false")
	{
		pOut = false;
		return true;
	}

	return false;
}

fBool fuiHelper::AttributeToFloat(fcyXmlNode* pNode, fcStrW Attribute, fFloat& pOut)
{
	fcStrW tValue = pNode->GetAttribute(Attribute);
	
	if(wcslen(tValue) == 0)
		return false;

	pOut = (float)_wtof(tValue);

	return true;
}

fBool fuiHelper::AttributeToRect(fcyXmlNode* pNode, fcStrW Attribute, fcyRect& pOut)
{
	vector<wstring> tRet;

	if(fcyStringHelper::StringSplit(pNode->GetAttribute(Attribute), L",", false, tRet) != 4)
		return false;

	pOut.a.x = (float)_wtof(tRet[0].c_str());
	pOut.a.y = (float)_wtof(tRet[1].c_str());
	pOut.b.x = (float)_wtof(tRet[2].c_str());
	pOut.b.y = (float)_wtof(tRet[3].c_str());

	return true;
}

fBool fuiHelper::AttributeToVec2(fcyXmlNode* pNode, fcStrW Attribute, fcyVec2& pOut)
{
	vector<wstring> tRet;

	if(fcyStringHelper::StringSplit(pNode->GetAttribute(Attribute), L",", false, tRet) != 2)
		return false;

	pOut.x = (float)_wtof(tRet[0].c_str());
	pOut.y = (float)_wtof(tRet[1].c_str());

	return true;
}

fBool fuiHelper::AttributeToVec3(fcyXmlNode* pNode, fcStrW Attribute, fcyVec3& pOut)
{
	vector<wstring> tRet;

	if(fcyStringHelper::StringSplit(pNode->GetAttribute(Attribute), L",", false, tRet) != 3)
		return false;

	pOut.x = (float)_wtof(tRet[0].c_str());
	pOut.y = (float)_wtof(tRet[1].c_str());
	pOut.z = (float)_wtof(tRet[2].c_str());

	return true;
}

fBool fuiHelper::AttributeToSprite(fuiContext* pContext, fcyXmlNode* pNode, fcStrW Attribute, f2dSprite* &pOut)
{
	fcStrW tStr = pNode->GetAttribute(Attribute);
	if(tStr == NULL)
		return false;

	f2dSprite* pSprite = pContext->GetSprite(tStr);
	if(pSprite == NULL)
		return false;

	pOut = pSprite;

	return true;
}

////////////////////////////////////////////////////////////////////////////////

const fCharW fuiControl::ControlName[] = L"Control";

fuiControl::fuiControl(fuiContainer* pParent)
	: m_pParent(NULL), m_bVisiable(true), m_bUpdate(true), m_bClip(false)
{
	if(pParent)
		SetParent(pParent);
}

fuiControl::~fuiControl(void)
{}

void fuiControl::setMinSize(const fcyVec2& Size)
{
	fcyRect tNewSize(m_UIRect);
	fBool tResize = false;

	m_UIMinSize = Size;
	if(m_UIRect.GetWidth() < m_UIMinSize.x)
	{
		tNewSize.b.x = tNewSize.a.x + Size.x;
		tResize = true;
	}
	if(m_UIRect.GetHeight() < m_UIMinSize.y)
	{
		tNewSize.b.y = tNewSize.a.y + Size.y;
		tResize = true;
	}

	if(tResize)
		SetRect(tNewSize);
}

fuiControl* fuiControl::GetTopParent()const
{
	if(m_pParent)
		return m_pParent->GetTopParent();
	else
		return (fuiControl*)this;
}

fuiContext* fuiControl::GetContext()
{
	return OnQueryContext();
}

const fcyVec2& fuiControl::GetMinSize()const
{
	return m_UIMinSize;
}

fuiContainer* fuiControl::GetParent()const
{
	return m_pParent;
}

void fuiControl::SetParent(fuiContainer* pParent)
{
	if(m_pParent == pParent || m_pParent == this)
		return;

	fuiContainer* pOld = m_pParent;
	if(pOld)
		pOld->removeControl(this);

	m_pParent = pParent;
	if(pParent)
		pParent->appendControl(this);

	OnParentChanged(pOld);
}

fuInt fuiControl::GetControlLayer()
{
	if(m_pParent)
		return m_pParent->getControlIndex(this);
	else
		return 0;
}

void fuiControl::SetControlLayer(fuInt Index)
{
	m_pParent->setControlIndex(this, Index);
}

fBool fuiControl::IsVisiable()const
{
	return m_bVisiable;
}

void fuiControl::SetVisiable(fBool bVisiable)
{
	if(bVisiable != m_bVisiable)
	{
		m_bVisiable = bVisiable;
		OnVisiableChanged();
	}
}

fBool fuiControl::IsUpdatable()const
{
	return m_bUpdate;
}

void fuiControl::SetUpdatable(fBool bUpdatable)
{
	m_bUpdate = bUpdatable;
}

fBool fuiControl::IsClip()const
{
	return m_bClip;
}

void fuiControl::SetClip(fBool bClip)
{
	m_bClip = bClip;
}

const fcyRect& fuiControl::GetRect()const
{
	return m_UIRect;
}

void fuiControl::SetRect(const fcyRect& Range)
{
	fcyRect tNewSize = Range;

	if(tNewSize.GetWidth() < m_UIMinSize.x)
	{
		tNewSize.b.x = tNewSize.a.x + m_UIMinSize.x;
	}
	if(tNewSize.GetHeight() < m_UIMinSize.y)
	{
		tNewSize.b.y = tNewSize.a.y + m_UIMinSize.y;
	}

	OnResized(tNewSize);

	m_UIRect = tNewSize;

	if(m_pParent)
		m_pParent->subControlResized(this);
}

fcStrW fuiControl::GetStyle()
{
	if(m_StyleName.empty())
		return NULL;
	else
		return m_StyleName.c_str();
}

void fuiControl::SetStyle(fcStrW pStyle)
{
	if(m_StyleName != pStyle)
	{
		OnStyleChanged(pStyle);
		m_StyleName = pStyle;
	}
}

void fuiControl::GetFocus()
{
	if(OnGetFocus())
	{
		if(m_pParent)
			m_pParent->subControlGetFocus(this);
	}
}

void fuiControl::LostFocus()
{
	m_pParent->subControlLostFocus(this);
	OnLostFocus();
}

void fuiControl::Render(fuiRenderer* pRenderer)
{
	if(m_bVisiable)
	{
		// ���������
		if(m_bClip)
		{
			// �ü�������ü�����
			if(!pRenderer->PushClip(OnQueryClipRect()))
				return; // ����ü����β��ཻ��ֱ����������
		}

		OnRender(pRenderer);

		if(m_bClip)
			pRenderer->PopClip();
	}
}

void fuiControl::Update(fDouble ElapsedTime)
{
	if(m_bUpdate)
		OnUpdate(ElapsedTime);
}

fBool fuiControl::SendMouseEvent(FUIMOUSEEVENT Type, fFloat X, fFloat Y)
{
	if(!m_bVisiable)
		return false; // �������򷵻�

	X -= m_UIRect.a.x;
	Y -= m_UIRect.a.y;

	switch(Type)
	{
	case FUIMOUSEEVENT_MOVE:
		return OnMouseMove(X, Y);
	case FUIMOUSEEVENT_LDOWN:
		return OnLMouseDown(X, Y);
	case FUIMOUSEEVENT_LUP:
		OnLMouseUp(X, Y);
		return true;
	case FUIMOUSEEVENT_RDOWN:
		return OnRMouseDown(X, Y);
	case FUIMOUSEEVENT_RUP:
		OnRMouseUp(X, Y);
		return true;
	case FUIMOUSEEVENT_MDOWN:
		return OnMMouseDown(X, Y);
	case FUIMOUSEEVENT_MUP:
		OnMMouseUp(X, Y);
		return true;
	default:
		return false;
	}
}

fBool fuiControl::SendKeyboardEvent(FUIKEYBOARDEVENT Type, F2DINPUTKEYCODE KeyCode)
{
	switch(Type)
	{
	case FUIKEYBOARDEVENT_KEYUP:
		OnKeyUp(KeyCode);
		break;
	case FUIKEYBOARDEVENT_KEYDOWN:
		OnKeyDown(KeyCode);
		break;
	case FUIKEYBOARDEVENT_CHARINPUT:
		OnCharInput((fCharW)KeyCode);
	default:
		return false;
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
// �¼��б�

void fuiControl::OnRender(fuiRenderer* pRenderer)
{}

void fuiControl::OnUpdate(fDouble ElapsedTime)
{}

void fuiControl::OnResized(fcyRect& NewSize)
{}

void fuiControl::OnParentChanged(fuiContainer* pNew)
{
	OnStyleChanged(GetStyle());
}

void fuiControl::OnStyleChanged(fcStrW NewStyleName)
{}

void fuiControl::OnVisiableChanged()
{}

fBool fuiControl::OnGetFocus()
{
	return true;
}

void fuiControl::OnLostFocus()
{}

void fuiControl::OnMouseLeave()
{}

fBool fuiControl::OnMouseMove(fFloat X, fFloat Y)
{
	return IsVisiable();
}

void fuiControl::OnLMouseUp(fFloat X, fFloat Y)
{}

fBool fuiControl::OnLMouseDown(fFloat X, fFloat Y)
{
	return IsVisiable();
}

void fuiControl::OnRMouseUp(fFloat X, fFloat Y)
{}

fBool fuiControl::OnRMouseDown(fFloat X, fFloat Y)
{
	return IsVisiable();
}

void fuiControl::OnMMouseUp(fFloat X, fFloat Y)
{}

fBool fuiControl::OnMMouseDown(fFloat X, fFloat Y)
{
	return IsVisiable();
}

void fuiControl::OnKeyUp(F2DINPUTKEYCODE KeyCode)
{}

void fuiControl::OnKeyDown(F2DINPUTKEYCODE KeyCode)
{}

void fuiControl::OnCharInput(fCharW CharCode)
{}

void fuiControl::OnQuerySubControlOffset(fcyVec2& pOut)
{
	pOut = fcyVec2();
}

void fuiControl::OnQueryControlName(std::wstring& Out)
{
	Out = fuiControl::ControlName;
}

const fcyRect& fuiControl::OnQueryClipRect()
{
	return m_UIRect;
}

fuiContext* fuiControl::OnQueryContext()
{
	if(m_pParent)
		return m_pParent->OnQueryContext();
	else
		return NULL;
}
