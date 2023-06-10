/*
 * lcd.h
 *
 *  Created on: 9. jun. 2023
 *      Author: sofus
 */

#ifndef LCD_H_
#define LCD_H_

extern volatile char buffer[512];
extern volatile int flag;

void lcd_write__string();
void lcd_update();

#endif /* LCD_H_ */
