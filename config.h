/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "sans-serif:size=12", "JoyPixels" };
static const char normbgcolor[]           = "#000000";
static const char normfgcolor[]           = "#e2e5de"; // chinese white
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
	/* class             instance            title       tags mask  isfloating  isterminal  noswallow   monitor */
	{ "TelegramDesktop", "Telegram",         NULL,       1 << 8,    0,          0,          0,          -1 },
	{ "St",              "st",               NULL,       0,         0,          1,          0,          -1 },
	{ "XTerm",           "xterm",            NULL,       0,         0,          1,          0,          -1 },
	{ "dropdown",        NULL,               NULL,       0,         1,          0,          1,          -1 },
	{ NULL,              NULL,               "Event Tester", 0,     0,          0,          1,          -1 }, /* xev */
	{ "Dragon",          "dragon",           NULL,       0,         0,          0,          1,          -1 },
	{ "Nm-applet",       "nm-applet",        NULL,       0,         0,          0,          1,          -1 },
	{ "Steam",           "Steam",            NULL,       1 << 3,    1,          0,          0,          -1 },
	{ "steam",           "steamwebhelper",   NULL,       1 << 3,    0,          0,          0,          -1 },
	{ "Onboard",         "onboard",          NULL,       0,         1,          0,          1,          -1 },
	{ "Brave-browser",   "brave-browser",    NULL,       1 << 7,    0,          0,          0,          -1 },
	{ "obsidian",        "obsidian",         NULL,       1 << 2,    0,          0,          0,          -1 },
	{ "Supersonic",      "Supersonic",       NULL,       1 << 6,    0,          0,          0,          -1 },
	{ "by-gdev-Main",    "by-gdev-Main",     NULL,       0,         0,          0,          1,          -1 }, /* TLauncher */
	{ "org-tlauncher-tlauncher-rmo-TLauncher", NULL, NULL, 0,       0,          0,          1,          -1 }, /* TLauncher */
	{ "librewolf",       NULL,               NULL,       1 << 1,    0,          0,          0,          -1 },
};

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* commands */
static const char *xterm_cmd[]     = {"xterm", NULL};
static const char *power_manager_cmd[]  = {"power-manager.sh", NULL};
static const char *rofi_run_cmd[] = {"rofi", "-show", "run", NULL};

#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key         function        argument */
	{ MODKEY|ShiftMask,             XK_Return,  spawn,          {.v = xterm_cmd} },

	{ MODKEY,                       XK_j,       focusstack,     {.i = +1} },
	{ MODKEY,                       XK_k,       focusstack,     {.i = -1} },
	{ MODKEY,                       XK_Down,    focusstack,     {.i = +1} },
	{ MODKEY,                       XK_Up,      focusstack,     {.i = -1} },

	{ MODKEY|ShiftMask,             XK_j,       movestack,      {.i = +1} },
	{ MODKEY|ShiftMask,             XK_k,       movestack,      {.i = -1} },
	{ MODKEY|ShiftMask,             XK_Down,    movestack,      {.i = +1} },
	{ MODKEY|ShiftMask,             XK_Up,      movestack,      {.i = -1} },

	{ MODKEY|ShiftMask,             XK_h,       incnmaster,     {.i = +1} },
	{ MODKEY|ShiftMask,             XK_l,       incnmaster,     {.i = -1} },

	{ MODKEY,                       XK_h,       setmfact,       {.f = -0.01} },
	{ MODKEY,                       XK_l,       setmfact,       {.f = +0.01} },
	{ MODKEY|ShiftMask,             XK_space,   setmfact,       {.f = +1.50} },

	{ MODKEY|ControlMask,           XK_h,       view_active,    {.i = -1} },
	{ MODKEY|ControlMask,           XK_l,       view_active,    {.i = +1} },

	{ MODKEY,                       XK_f,       togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_f,       zoom,           {0} },

	{ MODKEY,                       XK_q,       killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_q,       quit,           {0} },
	{ MODKEY|ShiftMask,             XK_r,       quit,           {1} },

	{ MODKEY|Mod1Mask,              XK_1,       setlayout,      {.v = &layouts[0]} },
	{ MODKEY|Mod1Mask,              XK_2,       setlayout,      {.v = &layouts[1]} },
	{ MODKEY|Mod1Mask,              XK_3,       setlayout,      {.v = &layouts[2]} },

	{ MODKEY,                       XK_space,   togglefloating, {0} },
	{ MODKEY,                       XK_comma,   togglesticky,   {0} },

	{ MODKEY,                       XK_0,       view,           {.ui = ~0} },
	{ MODKEY|ShiftMask,             XK_0,       tag,            {.ui = ~0} },

	{ MODKEY,                       XK_Left,    focusmon,       {.i = -1} },
	{ MODKEY,                       XK_Right,   focusmon,       {.i = +1} },
	{ MODKEY,                       XK_Tab,     focusmon,       {.i = +1} },

	{ MODKEY|ShiftMask,             XK_Left,    tagmon,         {.i = -1} },
	{ MODKEY|ShiftMask,             XK_Right,   tagmon,         {.i = +1} },
	{ MODKEY|ShiftMask,             XK_Tab,     tagmon,         {.i = +1} },

	{ MODKEY,                       XK_i,       togglebar,      {0} },

	TAGKEYS(                        XK_1,                       0)
	TAGKEYS(                        XK_2,                       1)
	TAGKEYS(                        XK_3,                       2)
	TAGKEYS(                        XK_4,                       3)
	TAGKEYS(                        XK_5,                       4)
	TAGKEYS(                        XK_6,                       5)
	TAGKEYS(                        XK_7,                       6)
	TAGKEYS(                        XK_8,                       7)
	TAGKEYS(                        XK_9,                       8)
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        spawn,          {.v = power_manager_cmd} },
	{ ClkWinTitle,          0,              Button3,        spawn,          {.v = rofi_run_cmd   } },
	{ ClkStatusText,        0,              Button1,        barclick,       {.i = 1 } },
	{ ClkStatusText,        0,              Button2,        barclick,       {.i = 2 } },
	{ ClkStatusText,        0,              Button3,        barclick,       {.i = 3 } },
	{ ClkStatusText,        0,              Button4,        barclick,       {.i = 4 } },
	{ ClkStatusText,        0,              Button5,        barclick,       {.i = 5 } },
	{ ClkStatusText,        ShiftMask,      Button1,        barclick,       {.i = 6 } },
	{ ClkStatusText,        ShiftMask,      Button2,        barclick,       {.i = 7 } },
	{ ClkStatusText,        ShiftMask,      Button3,        barclick,       {.i = 8 } },
	{ ClkStatusText,        ShiftMask,      Button4,        barclick,       {.i = 9 } },
	{ ClkStatusText,        ShiftMask,      Button5,        barclick,       {.i = 10} },
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

/* bar settings */
static const char barfifo[] = "/tmp/dwmbar.fifo";
