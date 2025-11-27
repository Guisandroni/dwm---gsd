/* See LICENSE file for copyright and license details. */

#include "movestack.c"
#include "fibonacci.c"



/* appearance */
/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "JetBrainsMono Nerd Font:size=10" };
static const char dmenufont[]       = "JetBrainsMono Nerd Font:size=10";
static  char col_gray1[]       = "#080909";
static  char col_gray2[]       = "#080909";
static  char col_gray3[]       = "#FFFFFF";
static  char col_gray4[]       = "#ae41c6";
static  char col_cyan[]        = "#080909";

/* --- ADICIONE ESTAS LINHAS ABAIXO --- */
static const unsigned int gappih    = 6;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 6;       /* vert inner gap between windows */
static const unsigned int gappoh    = 6;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 6;       /* vert outer gap between windows and screen edge */
//static       int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
/* ------------------------------------ */


static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};


ResourcePref resources[]={
	{"col_gray1", STRING, &col_gray1},
	{"col_gray2", STRING, &col_gray2},
	{"col_gray3", STRING, &col_gray3},
	{"col_gray4", STRING, &col_gray4},
	{"col_cyan", STRING, &col_cyan},
	

		

};



/* auto start */

static const char *const autostart[] = {
	
	"sh", "-c", "/home/guisandroni/dwm/dwm-btw/autostart.sh", NULL,

	 NULL
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int refreshrate = 120;  /* refresh rate (per second) for client move/resize */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "//",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{"[@]", spiral},
	{"[\\]", dwindle},
	{"|M|", centeredmaster},
	{">M>", centeredfloatingmaster}
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }


/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "st", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = {"st", "-t", "scratchpad", "--g", "120x34", NULL};
static const char *rofi[] = {"rofi","-show", "drun", "-theme", "~/.config/rofi/config.rasi", NULL};
static const char *flamecmd[] = { "flameshot", "gui", NULL};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY|Mod1Mask,		XK_s,	   spawn,	   {.v = flamecmd} } ,             
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,			XK_space,  spawn,	   {.v= rofi   } },
	{ MODKEY,	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,		XK_Return, togglescratch,  {.v = scratchpadcmd }},
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_h,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = -1 } },
	{ Mod1Mask,                       XK_z,      incnmaster,     {.i = +1 } },
	{ Mod1Mask,                       XK_x,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_k,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_z, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,	                    XK_x,      killclient,     {0} },
	{ Mod1Mask,                      XK_q,     setlayout,      {.v = &layouts[0]} },
	{ Mod1Mask,                       XK_w,      setlayout,      {.v = &layouts[1]} },
	{ Mod1Mask,                       XK_e,      setlayout,      {.v = &layouts[2]} },
	{ Mod1Mask,                       XK_s,      setlayout,      {.v = &layouts[3]} },
	{ Mod1Mask|ShiftMask,              XK_q,  setlayout,      {.v = &layouts[4]} },
	{ Mod1Mask|ShiftMask,		XK_w,	setlayout,	{.v = &layouts[5] }},
	{ MODKEY,                       XK_a,  setlayout,      {0} },
	{ Mod1Mask,                     XK_a,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	TAGKEYS(                        XK_KP_1,                      0)
	TAGKEYS(                        XK_KP_2,                      1)
	TAGKEYS(                        XK_KP_3,                      2)
	TAGKEYS(                        XK_KP_4,                      3)
	TAGKEYS(                        XK_KP_5,                      4)
	TAGKEYS(                        XK_KP_6,                      5)
	TAGKEYS(                        XK_KP_7,                      6)
	TAGKEYS(                        XK_KP_8,                      7)
	TAGKEYS(                        XK_KP_9,                      8)
	
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },

        { Mod1Mask, XK_Left, movestack, {.i = +1} },
        { Mod1Mask, XK_Right, movestack, {.i = +1} },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY|ShiftMask,         Button1,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkClientWin, MODKEY, Button4, movestack, {.i = -1 } },
	{ ClkClientWin, MODKEY, Button5, movestack, {.i = +1 } },
};

