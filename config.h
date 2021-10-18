/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int usealtbar          = 1;        /* 1 means use non-dwm status bar */
static const char *altbarclass      = "Polybar"; /* Alternate bar class name */
static const char *alttrayname      = "tray";    /* Polybar tray instance name */
static const char *altbarcmd        = "$HOME/bar.sh"; /* Alternate bar launch command */
static const char *fonts[]          = { "monospace:size=12", "JoyPixels" };
static const char dmenufont[]       = "monospace:size=10";
static const char normbgcolor[]           = "#000000";
static const char normfgcolor[]           = "#eeeeee";
static const char selbgcolor[]            = "#882233";
static const char selfgcolor[]            = "#ffffff";
static const char normbordercolor[]       = "#444444";
static const char selbordercolor[]        = "#449944";
static const char *colors[][3]      = {
	/*               fg           bg           border   */
	[SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
	[SchemeSel]  = { selfgcolor,  selbgcolor,  selbordercolor  },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class             instance            title       tags mask  isfloating  isterminal  noswallow  monitor */
	{ "TelegramDesktop", "telegram-desktop", NULL,       1 << 8,    0,          0,          0,         -1 },
	{ "VK",              "vk",               NULL,       1 << 7,    0,          0,          0,         -1 },
	{ "Slack",           "slack",            NULL,       1 << 7,    0,          0,          0,         -1 },
	{ "discord",         "discord",          NULL,       1 << 6,    0,          0,          0,         -1 },
	{ "St",              "st",               NULL,       0,         0,          1,          0,         -1 },
	{ "dropdown",        NULL,               NULL,       0,         1,          0,          0,         -1 },
	{ NULL,              NULL,               "Event Tester", 0,     0,          0,          1,         -1 }, /* xev */
	{ "Dragon",          "dragon",           NULL,       0,         0,          0,          1,         -1 },
	{ "Nm-applet",       "nm-applet",        NULL,       0,         0,          0,          1,         -1 },
};

/* layout(s) */
static const float mfact     = 0.60; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "fibonacci.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_Down,   focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_Up,     focusstack,     {.i = -1 } },

	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1} },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1} },
	{ MODKEY|ShiftMask,             XK_Down,   movestack,      {.i = +1} },
	{ MODKEY|ShiftMask,             XK_Up,     movestack,      {.i = -1} },

	{ MODKEY|ShiftMask,             XK_h,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l,      incnmaster,     {.i = -1 } },

	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.01} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.01} },

	{ MODKEY,                       XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,      zoom,           {0} },

	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,      quit,           {1} },

	{ MODKEY|Mod1Mask,              XK_1,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|Mod1Mask,              XK_2,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,              XK_3,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|Mod1Mask,              XK_4,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY|Mod1Mask,              XK_7,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY|Mod1Mask,              XK_8,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY|Mod1Mask,              XK_9,      setlayout,      {.v = &layouts[6]} },

	{ MODKEY,                       XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_comma,  togglesticky,   {0} },

	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },

	{ MODKEY,                       XK_Left,   focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Right,  focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_Tab,    focusmon,       {.i = +1 } },

	{ MODKEY|ShiftMask,             XK_Left,   tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right,  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Tab,    tagmon,         {.i = +1 } },

	{ MODKEY|ControlMask,           XK_Tab,    view,           {0} },
	{ MODKEY|ControlMask,           XK_h,      view_active,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_l,      view_active,    {.i = +1 } },

	{ MODKEY,                       XK_i,      togglebar,      {0} },

	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
};

/* button commands */
static const char *scratchcmd[]  = { "st", "-c", "dropdown", NULL };
static const char *powerctlcmd[]  = { "powermanager", NULL };

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },

	{ ClkWinTitle,          0,              Button2,        spawn,          {.v = powerctlcmd } },
	{ ClkWinTitle,          0,              Button3,        spawn,          {.v = scratchcmd } },

	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },

	{ ClkTagBar,            0,              Button4,        view_active,    {.i = -1 } },
	{ ClkTagBar,            0,              Button5,        view_active,    {.i = +1 } },
};

static const char *ipcsockpath = "/tmp/dwm.sock";
static IPCCommand ipccommands[] = {
  IPCCOMMAND(  view,                1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggleview,          1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tag,                 1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  toggletag,           1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  tagmon,              1,      {ARG_TYPE_UINT}   ),
  IPCCOMMAND(  focusmon,            1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  focusstack,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  zoom,                1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  incnmaster,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  killclient,          1,      {ARG_TYPE_SINT}   ),
  IPCCOMMAND(  togglefloating,      1,      {ARG_TYPE_NONE}   ),
  IPCCOMMAND(  setmfact,            1,      {ARG_TYPE_FLOAT}  ),
  IPCCOMMAND(  setlayoutsafe,       1,      {ARG_TYPE_PTR}    ),
  IPCCOMMAND(  quit,                1,      {ARG_TYPE_NONE}   )
};
