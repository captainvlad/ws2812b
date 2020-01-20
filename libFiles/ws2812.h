/*
 * Done for Ukrainian Catholic University, by Vladyslav Zadorozhnyy (CS 2-grade student). Intended to be used by
 * all, who need. You can see instrucitons in Instructions.pdf file reached with following link:
 * https://github.com/captainvlad/ws2812b.git
 * All rights reserved.
 */

#ifndef WS2812_H_
#define WS2812_H_
//--------------------------------------------------
#include "stm32f4xx_hal.h"
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
//--------------------------------------------------
struct diod_tape
{
  GPIO_TypeDef *type;
    uint16_t port;
    int size;
    int length;
    int *buffer;
};
//--------------------------------------------------
void delay_asm(int useconds);
void send_byte(GPIO_TypeDef *port_type, uint16_t port, int a);


struct diod_tape set_tape(GPIO_TypeDef *type_of_port, uint16_t port_number, int size);
void reset(struct diod_tape argument);

void light_all_diod_tape(struct diod_tape argument, int r, int g, int b);
void set_buffer(struct diod_tape argument, int r, int g, int b, int start, int finish);

void light_from_buffer(struct diod_tape argument);
void light_single_diod(struct diod_tape argument, int r, int g, int b, int position);

int *get_colour(struct diod_tape argument, int position);
void pattern_colouring(struct diod_tape argument, int pattern[][3], int pattern_size, int st_position, int f_position);

void set_colour_brightness(struct diod_tape argument, int position, int percentage);
void decrease_colour_brightness(struct diod_tape argument, int position, int percentage);

void increase_colour_brightness(struct diod_tape argument, int position, int percentage);
void errorHandler(struct diod_tape argument, int error_code);

void light_diod_tape(struct diod_tape argument, int r, int g, int b, int start, int finish);
void errorHandler(struct diod_tape argument, int error_code);

void set_pattern_colouring(struct diod_tape argument, int pattern[][3], int pattern_size, int st_position, int f_position);
//--------------------------------------------------
#endif /* WS2812_H_ */
