/*****************************************************************************/
// Handle OSD drawing of gamepads
/*****************************************************************************/

#ifndef OSDJOYPAD_H
#define OSDJOYPAD_H

#include <stdint.h>

//utility functions
const char *osd_joypad_label(uint32_t button, uint32_t button_style);
const char *osd_joypad_raw_data(uint32_t line);
void osd_joypad_line(uint32_t line, char *s, uint32_t button_style);
void osd_joypad_line_alt(uint32_t line, char *s, uint32_t idx, char alt, uint32_t button_style);

// functions to draw gamepad on OSD
const char *osd_joypad_style_name(uint32_t style);
void osd_joypad_draw(uint32_t osd_start_line, uint32_t osd_joypad_style);
void osd_joypad_update(uint32_t osd_start_line, uint32_t osd_joypad_style, char alt_char, uint32_t pressed_button);
void osd_joypad_clear(uint32_t osd_start_line);

#endif // OSDJOYPAD_H

