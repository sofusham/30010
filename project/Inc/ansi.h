/*
 * ansi.h
 *
 *  Created on: 12. jun. 2023
 *      Author: sofus
 */

#ifndef ANSI_H_
#define ANSI_H_

void fgcolor(uint8_t foreground);
void bgcolor(uint8_t backgrund);
void color(uint8_t foreground, uint8_t background);
void resetbgcolor();
void clrscr();
void clreol();
void gotoxy(int x, int y);
void underline(int true);
void blink(int true);
void inverse(int true);

#endif /* ANSI_H_ */
