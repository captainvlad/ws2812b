#ifndef WS2812_H_
#define WS2812_H_
//--------------------------------------------------
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
//--------------------------------------------------
void delay_asm(int useconds);
void send_byte(int a);
void set_diods(int amount, size_t type, size_t number);
void light_diod_tape(int r, int g, int b, int amount);
void light_array_of_diods (int r, int g, int b, int amount_1, int amount_2);
void light_single_diod(int r, int g, int b, int position);
void pattern_colouring(int pattern[][3], int pattern_size, int st_position, int f_position);
void light_from_buffer();
void set_colour(int r, int g, int b, int position);
void set_brightness(int position, int percentage);
//--------------------------------------------------
#endif /* WS2812_H_ */
