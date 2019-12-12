/*****************************************************************************/
// Handle mapping of various joystick controllers
/*****************************************************************************/

#ifndef JOYMAPPING_H
#define JOYMAPPING_H

#include <inttypes.h>

void map_joystick(uint32_t *map, uint32_t *mmap);

// status reporting from outside functions
extern uint32_t joy_status[4];
extern uint32_t set_joypad_status(uint32_t dev, uint32_t index, uint32_t value);
extern uint32_t get_joypad_status(uint32_t dev);


#endif // JOYMAPPING_H
