#include "ws2812.h"
#define LED_AMOUNT 60
//------------------------------------------------------------------------------
int size;
size_t pin_type;
size_t pin_number;
int buffer[LED_AMOUNT][3];
//------------------------------------------------------------------------------
void light_from_buffer(){
	for (int i = 0; i < size; i++){
		send_byte(buffer[i][1]);
		send_byte(buffer[i][0]);
		send_byte(buffer[i][2]);
	}
	HAL_Delay(1);
}
//------------------------------------------------------------------------------
void delay_asm(int useconds) {
	asm volatile("   mov r0, %[useconds]    \n"
			"1: subs r0, #1            \n"
			"   bhi 1b                 \n": :[useconds] "r" (useconds): "r0");
}
//------------------------------------------------------------------------------
void reset(){
	for (int i = 0; i < size; i++){
		buffer[i][0] = 0;
		buffer[i][1] = 0;
		buffer[i][2] = 0;
	}
}
//------------------------------------------------------------------------------
void send_byte(int a) {
	int DELAY[3] = {10, 20, 10};
	for (int i = 7; i >= 0; i--) {
		int bit = (a >> i) & 1;
		GPIOB->BSRR = GPIO_PIN_8;
		delay_asm(DELAY[bit]);
		GPIOB->BSRR = (uint32_t) GPIO_PIN_8 << 16U;
		delay_asm(DELAY[bit + 1]);
	}
}
//------------------------------------------------------------------------------
void set_diods(int amount, size_t type, size_t number){
	size = amount;
	pin_type = type;
	pin_number = number;
	light_diod_tape(0x00, 0x00, 0x00, size);
}
//------------------------------------------------------------------------------
void light_array_of_diods (int r, int g, int b, int amount_1, int amount_2){
	int pattern[][3] = {{g, r, b}};
	pattern_colouring(pattern, 1, amount_1, amount_2);
}
//------------------------------------------------------------------------------
void light_diod_tape(int r, int g, int b, int amount){
	light_array_of_diods(r, g, b, 0, amount);
}
//------------------------------------------------------------------------------
void light_single_diod(int r, int g, int b, int position){
	light_array_of_diods(r,g,b,position, position + 1);
}
//------------------------------------------------------------------------------
int *get_colour(int position){
	return buffer[position];
}
//------------------------------------------------------------------------------
void pattern_colouring(int pattern[][3], int pattern_size, int st_position, int f_position){
	reset();
	for (int i = st_position; i < f_position; i++){
		buffer[i][2] = pattern[i % pattern_size][2];
		buffer[i][1] = pattern[i % pattern_size][0];
		buffer[i][0] = pattern[i % pattern_size][1];
	}
	light_from_buffer();
}
//------------------------------------------------------------------------------
void set_brightness(int position, int amount){
//	buffer[position][0] -= amount;
//	buffer[position][1] -= amount;
//	buffer[position][2] -= amount;
	light_from_buffer();
}
//------------------------------------------------------------------------------
void set_colour(int r, int g, int b, int position){
	buffer[position][0] = r;
	buffer[position][1] = g;
	buffer[position][2] = b;
	light_from_buffer();
}


