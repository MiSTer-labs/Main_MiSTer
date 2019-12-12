/*
This file contains functions to draw a controller joypad into the OSD
*/

#include <inttypes.h>
#include <string.h>

#include "osd.h"
#include "input.h"


// button label styles
const char *button_styles[]   =	{" \x10     Classic Plumber     \x11",
								 " \x10        Modern X         \x11",
								 " \x10       Alt Station       \x11",
								 " \x10      Mega Hedgehog      \x11",
								 " \x10      Arcade Stick       \x11"};
const char *button_A_labels[] = {"A",       "B",      "O",        "C",    "3"};
const char *button_B_labels[] = {"B",       "A",      "X",        "B",    "2"};
const char *button_X_labels[] = {"X",       "Y",      "\x12",     "Y",    "5"};
const char *button_Y_labels[] = {"Y",       "X",      "\x8C",     "A",    "1"};
const char *button_L_labels[] = {"L",       "L",      "L",        "X",    "4"};
const char *button_R_labels[] = {"R",       "R",      "R",        "Z",    "6"};

// ASCII UI graphic for gamepad and indexes to update buttons
const char *joypad_ascii[] = {	"  \x86 L \x88               \x86 R \x88  ",
								" \x86\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x88",
								" \x83   U                 X   \x83",
								" \x83 L \x1b R  Sel Start  Y   A \x83",
								" \x83   D   \x86\x81\x81\x81\x81\x81\x81\x81\x81\x81\x88   B   \x83",
								" \x8b\x81\x81\x81\x81\x81\x81\x81\x8a         \x8b\x81\x81\x81\x81\x81\x81\x81\x8a"};

const char *joypad_ascii_6btn[] = {
								"  \x86\x81\x81\x81\x81\x88               \x86\x81\x81\x81\x81\x88  ",
								" \x86\x8a        \x81\x81\x81\x81\x81\x81\x81\x81\x81      \x8b\x88",
								" \x83   U               X Y Z \x83",
								" \x83 L \x1b R     Start   A B C \x83",
								" \x83   D       Sel           \x83",
								" \x8b\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x81\x8a"};

const uint32_t GAMEPAD_UI_LINE_L_R    = 0;
const uint32_t GAMEPAD_UI_LINE_U_X    = 2;
const uint32_t GAMEPAD_UI_LINE_MIDDLE = 3;
const uint32_t GAMEPAD_UI_LINE_D_B    = 4;

const uint32_t GAMEPAD_UI_BTN_UP    = 5; 
const uint32_t GAMEPAD_UI_BTN_DOWN  = GAMEPAD_UI_BTN_UP;
const uint32_t GAMEPAD_UI_BTN_LEFT  = GAMEPAD_UI_BTN_UP-2;
const uint32_t GAMEPAD_UI_BTN_RIGHT = GAMEPAD_UI_BTN_UP+2;
const uint32_t GAMEPAD_UI_BTN_SELECT= 10;
const uint32_t GAMEPAD_UI_BTN_START = GAMEPAD_UI_BTN_SELECT+4;
const uint32_t GAMEPAD_UI_BTN_L     = 4; 
const uint32_t GAMEPAD_UI_BTN_R     = 24; 
const uint32_t GAMEPAD_UI_BTN_Y     = 21; 
const uint32_t GAMEPAD_UI_BTN_A     = GAMEPAD_UI_BTN_Y+4; 
const uint32_t GAMEPAD_UI_BTN_B     = GAMEPAD_UI_BTN_A-2;
const uint32_t GAMEPAD_UI_BTN_X     = GAMEPAD_UI_BTN_B;

const uint32_t GAMEPAD_UI_6BTN_SELECT= 10;
const uint32_t GAMEPAD_UI_6BTN_START = GAMEPAD_UI_BTN_SELECT+4;
const uint32_t GAMEPAD_UI_6BTN_L     = 4; 
const uint32_t GAMEPAD_UI_6BTN_R     = 24; 
const uint32_t GAMEPAD_UI_6BTN_Y     = 21; 
const uint32_t GAMEPAD_UI_6BTN_A     = GAMEPAD_UI_BTN_Y+4; 
const uint32_t GAMEPAD_UI_6BTN_B     = GAMEPAD_UI_BTN_A-2;
const uint32_t GAMEPAD_UI_6BTN_X     = GAMEPAD_UI_BTN_B;




// wrapper to return UI gamepad graphic
const char *osd_joypad_raw_data(uint32_t line, uint32_t button_style) {
	if (line>5) line=5;
	if (button_style>2)
	   return joypad_ascii_6btn[line];
	return joypad_ascii[line];
}

// returns image of gamepad with desired button label style
void osd_joypad_line(uint32_t line, char *s, uint32_t button_style) {
	strcpy(s, osd_joypad_raw_data(line, button_style));
	if (button_style>2)
		return; // ignore labels for now
	switch(line) {
		case GAMEPAD_UI_LINE_MIDDLE:
			s[GAMEPAD_UI_BTN_A] = button_A_labels[button_style][0];
			s[GAMEPAD_UI_BTN_Y] = button_Y_labels[button_style][0];
			break;
		case GAMEPAD_UI_LINE_L_R:
			s[GAMEPAD_UI_BTN_L] = button_L_labels[button_style][0];
			s[GAMEPAD_UI_BTN_R] = button_R_labels[button_style][0];
			break;
		case GAMEPAD_UI_LINE_D_B:
			s[GAMEPAD_UI_BTN_B] = button_B_labels[button_style][0];
			break;
		case GAMEPAD_UI_LINE_U_X:
			s[GAMEPAD_UI_BTN_X] = button_X_labels[button_style][0];
			break;
	}
	return;
}

void osd_joypad_line_6btn(uint32_t line, char *s, uint32_t button_style) {
	strcpy(s, osd_joypad_raw_data(line, button_style));
	switch(line) {
		case GAMEPAD_UI_LINE_MIDDLE:
			s[GAMEPAD_UI_BTN_A] = button_A_labels[button_style][0];
			s[GAMEPAD_UI_BTN_Y] = button_Y_labels[button_style][0];
			break;
		case GAMEPAD_UI_LINE_L_R:
			s[GAMEPAD_UI_BTN_L] = button_L_labels[button_style][0];
			s[GAMEPAD_UI_BTN_R] = button_R_labels[button_style][0];
			break;
		case GAMEPAD_UI_LINE_D_B:
			s[GAMEPAD_UI_BTN_B] = button_B_labels[button_style][0];
			break;
		case GAMEPAD_UI_LINE_U_X:
			s[GAMEPAD_UI_BTN_X] = button_X_labels[button_style][0];
			break;
	}
	return;
}

// used to replace a char in the gamepad UI, e.g. to blink or show button presses
void osd_joypad_line_alt(uint32_t line, char *s, uint32_t idx, char alt, uint32_t button_style) {
	osd_joypad_line(line, s, button_style);
	s[idx] = alt;
	if (idx==GAMEPAD_UI_BTN_START) {
		for(uint32_t j=0; j<5; j++) 
			s[idx+j] = alt;
	} else {
		if (idx==GAMEPAD_UI_BTN_SELECT) {
			for(uint32_t j=0; j<3; j++) 
				s[idx+j] = alt;
		}
	}
}

//returns name of currently selected joypad style
const char *osd_joypad_style_name(uint32_t style) {
	if (style>4) style=4;
	return button_styles[style];
}

// draws raw joypad in OSD (no updates) in desired style, starting at OSD start_line
void osd_joypad_draw(uint32_t osd_start_line, uint32_t osd_joypad_style) {
	char s[256];
	for (int i=0; i<6; ++i) {
		osd_joypad_line(i, s, osd_joypad_style); 
		OsdWrite(osd_start_line+i, s);
	}
}

//draws one line in OSD with one button pressed updating relevant button with "alt_char"
void osd_joypad_update(uint32_t osd_start_line, uint32_t osd_joypad_style, char alt_char, uint32_t pressed_button) {
	char s[256];
	uint32_t button_line = 0;
	uint32_t offset = 0;
	switch (pressed_button)
	{
		case SYS_BTN_L     :	button_line=GAMEPAD_UI_LINE_L_R;    offset = GAMEPAD_UI_BTN_L;  	break;
		case SYS_BTN_R     :	button_line=GAMEPAD_UI_LINE_L_R;    offset = GAMEPAD_UI_BTN_R;  	break;
		case SYS_BTN_UP    :	button_line=GAMEPAD_UI_LINE_U_X;    offset = GAMEPAD_UI_BTN_R;  	break;
		case SYS_BTN_X     :	button_line=GAMEPAD_UI_LINE_U_X;    offset = GAMEPAD_UI_BTN_X;   	break;
		case SYS_BTN_A     :	button_line=GAMEPAD_UI_LINE_MIDDLE; offset = GAMEPAD_UI_BTN_A;   	break;
		case SYS_BTN_Y     :	button_line=GAMEPAD_UI_LINE_MIDDLE; offset = GAMEPAD_UI_BTN_Y;   	break;
		case SYS_BTN_LEFT  :	button_line=GAMEPAD_UI_LINE_MIDDLE; offset = GAMEPAD_UI_BTN_LEFT;	break;
		case SYS_BTN_RIGHT :	button_line=GAMEPAD_UI_LINE_MIDDLE; offset = GAMEPAD_UI_BTN_RIGHT;	break;
		case SYS_BTN_SELECT:	button_line=GAMEPAD_UI_LINE_MIDDLE; offset = GAMEPAD_UI_BTN_SELECT;	break;
		case SYS_BTN_START :	button_line=GAMEPAD_UI_LINE_MIDDLE; offset = GAMEPAD_UI_BTN_START;	break;
		case SYS_BTN_DOWN  :	button_line=GAMEPAD_UI_LINE_D_B;    offset = GAMEPAD_UI_BTN_DOWN;	break;
		case SYS_BTN_B     :	button_line=GAMEPAD_UI_LINE_D_B;    offset = GAMEPAD_UI_BTN_B;   	break;
	}
	osd_joypad_line_alt(button_line, s, offset, alt_char, osd_joypad_style);
	OsdWrite(osd_start_line+button_line, s);
}

void osd_joypad_clear(uint32_t osd_start_line) {
	if (osd_start_line > 11)
		osd_start_line = 11; // OSD has max 16 lines
	for (int i=0; i<5; ++i) {
		OsdWrite(osd_start_line+i);
	}
	OsdWrite(15);
}

