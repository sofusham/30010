/*
 * menu.c
 *
 *  Created on: 20. jun. 2023
 *      Author: sofus
 */

#include "stm32f30x_conf.h" // STM32 config
#include "30010_io.h" 		// Input/output library for this course
#include "menu.h"
#include "analogJoystick.h"
#include "ansi.h"
#include "timer.h"
#include "timer2.h"
#include "lcd.h"

void window(int x2, int y2, int x1, int y1) {
	int i;
	for (i = x2 + 80; i < x1; i += 120) {
		gotoxy(i, y2);
		printf("\xCD");
		gotoxy(i, y1);
		printf("\xCD");
	}
	for (i = y2 + 80; i < y1; i += 100) {
		gotoxy(x2, i);
		printf("\xBA");
		gotoxy(x1, i);
		printf("\xBA");
	}
	gotoxy(x1,y1);
	printf("\xBC");
	gotoxy(x1,y2);
	printf("\xBB");
	gotoxy(x2,y2);
	printf("\xC9");
	gotoxy(x2,y1);
	printf("\xC8");
}

void start_menu() {
	int i = 0;
	int8_t prevRot = 0;
	int8_t curRot;
	int8_t prevShot = 0;
	int8_t curShot;

	stop_buzzer();
	clrscr();

	window(9620, 1400, 14620, 3500);
	gotoxy(11720, 1640);
	printf("THE GAME!");
	gotoxy(10060, 1800);
	printf("Start game");
	gotoxy(10060, 2120);
	printf("Controls");
	gotoxy(11580, 1800);
	printf("<");

	for (int i = 0; i < 1000000; i++) {}
	while(1) {
		stop_buzzer();
		curRot = measurePA6();
		curShot = getPF1();

		if (curRot != prevRot) {
			switch (curRot) {
			case 1:
				i++;
				if (i > 1) {i = 1; }
				break;
			case 2:
				i--;
				if (i < 0) {i = 0; }
				break;
			}
		}
		switch (i) {
		case 0:
			gotoxy(11580, 2120);
			printf(" ");
			gotoxy(11580, 1800);
			printf("<");
			break;
		case 1:
			gotoxy(11580, 1800);
			printf(" ");
			gotoxy(11580, 2120);
			printf("<");
		}

		if (i && curShot > prevShot) {
			controls_menu();
		}
		else if (i == 0 && curShot > prevShot) {
			break;
		}

		prevRot = curRot;
		prevShot = curShot;
	}
}

void controls_menu() {
	int8_t prevShot = 0;
	int8_t curShot;
	clrscr();
	window(9620, 1400, 14620, 3500);
	gotoxy(11720, 1640);
	printf("THE GAME!");
	gotoxy(11400, 1800);
	printf("GAME CONTROLS");

	gotoxy(10060, 2300);
	printf("Thrust: Joystick up");
	gotoxy(10060, 2500);
	printf("Rotate left: Joystick left");
	gotoxy(10060, 2700);
	printf("Rotate right: Joystick right");
	gotoxy(10060, 3000);
	printf("Shoot: SW1");
	gotoxy(10060, 3200);
	printf("Exit controls menu  <");

	for (int i = 0; i < 1000000; i++) {}
	while(1) {
		curShot = getPF1();
		if (curShot > prevShot) {break; }

		prevShot = curShot;
	}
	clrscr();
	window(9620, 1400, 14620, 3500);
	gotoxy(11720, 1640);
	printf("THE GAME!");
	gotoxy(10060, 1800);
	printf("Start game");
	gotoxy(10060, 2120);
	printf("Controls");
	gotoxy(11580, 1800);
	printf("<");
}

void death_menu() {
	int i = 0;
	int8_t prevShot = 0;
	int8_t curShot;

	clrscr();
	window(9620, 1400, 14620, 3500);
	gotoxy(11720, 1640);
	printf("GAME OVER");
	gotoxy(10060, 1800);
	printf("Return to main menu  <");

	for (int i = 0; i < 1000000; i++) {}
	while(1) {
		stop_buzzer();
		curShot = getPF1();

		if (curShot > prevShot) {
			break;
		}

		prevShot = curShot;
	}
}

void print_spreadsheet() {
	gotoxy(0,0);
    printf("      A     B     C     D     E     F     G     H     I     J     K     L     M     N     O     P     Q     R     S     T     U     V     X     Y     Z\n");
    for(int i = 1; i <= 25; i++){
    	printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
    	if(i < 10){ //for proper formatting
    		printf("0%d \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3\n", i);
    	} else {
    		printf("%d \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3     \xB3\n", i);
    	}

    }
    printf("\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\xC4\n");
    //to avoid fencepost error
}

void boss_menu() {
	clrscr();
	memset(buffer, 0x00, 512);
	lcd_push_buffer(buffer);
	print_spreadsheet();
	while(1) {
		if (uart_get_count() == 1) {
			if (string_check(read_uart_data(1)) == 1) {
				break;
				clrscr();
			}
		}
	}
}



