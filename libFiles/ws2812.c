/*
 * Done for Ukrainian Catholic University, by Vladyslav Zadorozhnyy (CS 2-grade student). Intended to be used by
 * all, who need. You can see instrucitons in Instructions.pdf file reached with following link:
 * https://github.com/captainvlad/ws2812b.git
 * All rights reserved.
 */

#include "ws2812.h"
//------------------------------------------------------------------------------
struct diod_tape set_tape(GPIO_TypeDef *type_of_port, uint16_t port_number, int size){

/*	This method is intended to initialize a diod line. Expected arguments:
 * 		GPIO_TypeDef *type_of_port: (e.g. GPIOD if you want to work with PD. port, GPIOB if with PB. and so on)
 * 		uint16_t port_number: (e.g. GPIO_PIN_9 if you want to work with Pin9 and so on)
 * 		int size: amount of diods on a line (must be more than zero!)
 *
 * 		In buffer we hold the colors to be shown in RGB style. Note, that buffer is one-dimensional.
 */

  struct diod_tape current = {type_of_port, port_number, size};
  current.length = current.size * 3;

  current.buffer = malloc(sizeof(int) * current.length);
  reset(current);

  light_from_buffer(current);
  return current;
}
//------------------------------------------------------------------------------
void send_byte(GPIO_TypeDef *port_type, uint16_t port, int a) {
/*
 * This method sends byte to the line in order to light.
 * NOTE: It's used by other methods and user should work with it directly
 * only in extreme cases.
 */
  int DELAY[3] = {10, 20, 10};
  for (int i = 7; i >= 0; i--) {

    int bit = (a >> i) & 1;
    port_type->BSRR = port;

    delay_asm(DELAY[bit]);
    port_type->BSRR = (uint32_t) port << 16U;
    delay_asm(DELAY[bit + 1]);
  }
}
//------------------------------------------------------------------------------
void delay_asm(int useconds) {
/*
 * This method generates delays in miliseconds with assembler code.
 */
  asm volatile("   mov r0, %[useconds]    \n"
      "1: subs r0, #1            \n"
      "   bhi 1b                 \n": :[useconds] "r" (useconds): "r0");
}
//------------------------------------------------------------------------------
void light_from_buffer(struct diod_tape argument){
/*
 * This method transmits values from buffer to the tape and lights the colors on diods.
 */

  GPIO_TypeDef *typ = argument.type;
  uint16_t por = argument.port;
  int *arr = argument.buffer;

  for (int i = 0; i < argument.length; i += 3){
    send_byte(typ, por, *(arr + i));
    send_byte(typ, por, *(arr + i + 1));
    send_byte(typ, por, *(arr + i + 2));
  }
  HAL_Delay(1);
}
//------------------------------------------------------------------------------
void reset(struct diod_tape argument){
	/*
	 * This method switches the line of diods off.
	 */
	light_all_diod_tape(argument, 0, 0, 0);
}
//------------------------------------------------------------------------------
void set_buffer(struct diod_tape argument, int r, int g, int b, int start, int finish){
	/*
	 * This method gives chosen values to chosen indexes.
	 */
	if (r > 255 || r < 0 || b < 0 || b > 255 || g < 0 || g > 255 ){
		errorHandler(argument, 1);
	}
	else if(start > finish || start < 0 || finish < 0){
		errorHandler(argument, 2);
	}
	else{
	  for(int i = start * 3; i < finish * 3; i += 3){
		argument.buffer[i] = g;
		argument.buffer[i + 1] = r;
		argument.buffer[i + 2] = b;
	  }
  }
}
//------------------------------------------------------------------------------
void light_diod_tape(struct diod_tape argument, int r, int g, int b, int start, int finish){
	/*
	 * This method gives chosen values to chosen indexes and lights the line.
	 */
	set_buffer(argument, r, g, b, start, finish);
	light_from_buffer(argument);
}
//------------------------------------------------------------------------------
void light_all_diod_tape(struct diod_tape argument, int r, int g, int b){
	/*
	 * This method sets all diods and lights them with given color.
	 */
	set_buffer(argument, r, g, b, 0, argument.size);
	light_from_buffer(argument);
}
//------------------------------------------------------------------------------
void light_single_diod(struct diod_tape argument, int r, int g, int b, int position){
	/*
	 * This lights chosen index with given color.
	 */
	set_buffer(argument, r, g, b, position, position + 1);
	light_from_buffer(argument);
}
//------------------------------------------------------------------------------
void set_single_diod(struct diod_tape argument, int r, int g, int b, int position){
	/*
	 * This sets in buffer given color values.
	 */
	set_buffer(argument, r, g, b, position, position + 1);
}
//------------------------------------------------------------------------------
int *get_colour(struct diod_tape argument, int position){
	/*
	 * This method returns values by given index in RGB color.
	 */
	int result[3] = {0, 0, 0};
	if (position < 0 || position > argument.size){
		errorHandler(argument, 3);
	}
	else{
		for (int i = 0; i < 3; i++){
			result[i] = argument.buffer[position + i];
		}
	}
	return *result;
}
//------------------------------------------------------------------------------
void set_pattern_colouring(struct diod_tape argument, int pattern[][3], int pattern_size, int st_position, int f_position){
	/*
	 * This method lights in needed indexes diods lane with given pattern.
	 * NOTE: pattern_size - size of pattern
	 */
	if (pattern_size <= 0 || st_position < 0 || st_position > f_position || f_position > argument.size){
		errorHandler(argument, 4);
	}
	else{
		for (int i = st_position; i< f_position; i++){
			set_single_diod(argument, pattern[i % pattern_size][0], pattern[i % pattern_size][1], pattern[i % pattern_size][2], i);
		}
	}
}
//------------------------------------------------------------------------------
void pattern_colouring(struct diod_tape argument, int pattern[][3], int pattern_size, int st_position, int f_position){
	/*
	 * This method lights in needed indexes diods lane with given pattern and lights the lane.
	 * NOTE: pattern_size - size of pattern
	 */
	set_pattern_colouring(argument, pattern, pattern_size, st_position, f_position);
	light_from_buffer(argument);
}
//------------------------------------------------------------------------------
void decrease_colour_brightness(struct diod_tape argument, int position, int percentage){
/*
 * This method decreases brightness of a needed diod by given percentage.
 */
	if (position < 0 || position > argument.size || percentage < 0 || percentage > 100){
		errorHandler(argument, 5);
	}
	else{
		for (int i = 0; i < 3; i++){
			argument.buffer[position * 3 + i] = argument.buffer[position * 3 + i] * percentage / 100;
		}
	}
}
//------------------------------------------------------------------------------
void increase_colour_brightness(struct diod_tape argument, int position, int percentage){
	/*
	 * This method increases brightness of a needed diod by given percentage.
	 * NOTE: constants in calculations 6 and 4 are experimentally chosen.
	 */
	if (position < 0 || position > argument.size || percentage < 0 || percentage > 100){
			errorHandler(argument, 6);
		}
	else{
		int sum = argument.buffer[position] + argument.buffer[position + 1] + argument.buffer[position + 2];
		if (argument.buffer[position] != 0 && argument.buffer[position + 1] != 0 && argument.buffer[position + 2] != 0){
			for (int i = 0; i < 3; i++){
				argument.buffer[position * 3 + i] = argument.buffer[position * 3 + i] * percentage / sum * 255 * 6 / 100;
			}
		}
		else{
			for (int i = 0; i < 3; i++){
					argument.buffer[position * 3 + i] = argument.buffer[position * 3 + i] * percentage / sum * 255 * 4 / 100;
				}
		}
	}
}
//------------------------------------------------------------------------------
void errorHandler(struct diod_tape argument, int error_code){
/*
 * This method shows when error is occured. Number of red diods will show the number of error.
 * (For more look at README.md)
 */
	light_diod_tape(argument, 255, 0, 0, 0, error_code);
	HAL_Delay(250);
	reset(argument);
	HAL_Delay(250);
}
//------------------------------------------------------------------------------
