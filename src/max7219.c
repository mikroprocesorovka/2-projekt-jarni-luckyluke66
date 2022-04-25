#include "max7219.h"

// nastaví CLK,LOAD/CS,DATA jako výstupy a nakonfiguruje displej
void max7219_init(void){
GPIO_Init(CS_GPIO,CS_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
GPIO_Init(CLK_GPIO,CLK_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
GPIO_Init(DATA_GPIO,DATA_PIN,GPIO_MODE_OUT_PP_LOW_SLOW);
// nastavíme základní parametry budiče
max7219_posli(DECODE_MODE, DECODE_ALL); // zapnout znakovou sadu na všech cifrách
max7219_posli(SCAN_LIMIT, 7); // velikost displeje 8 cifer (počítáno od nuly, proto je argument číslo 7)
max7219_posli(INTENSITY, 5); // volíme ze začátku nízký jas (vysoký jas může mít velkou spotřebu - až 0.25A !)
max7219_posli(DISPLAY_TEST, DISPLAY_TEST_OFF); // 
max7219_posli(SHUTDOWN, DISPLAY_ON); // zapneme displej
}

// odešle do budiče MAX7219 16bitové číslo složené z prvního a druhého argumentu (nejprve adresa, poté data)
void max7219_posli(uint8_t adresa, uint8_t data){
uint8_t maska; // pomocná proměnná, která bude sloužit k procházení dat bit po bitu
CS_LOW; // nastavíme linku LOAD/CS do úrovně Low (abychom po zapsání všech 16ti bytů mohli vygenerovat na CS vzestupnou hranu)

// nejprve odešleme prvních 8bitů zprávy (adresa/příkaz)
maska = 0b10000000; // lepší zápis je: maska = 1<<7
CLK_LOW; // připravíme si na CLK vstup budiče úroveň Low
while(maska){ // dokud jsme neposlali všech 8 bitů
	if(maska & adresa){ // pokud má právě vysílaný bit hodnotu 1
		DATA_HIGH; // nastavíme budiči vstup DIN do úrovně High
	}
	else{ // jinak má právě vysílaný bit hodnotu 0 a...
		DATA_LOW;	// ... nastavíme budiči vstup DIN do úrovně Low
	}
	CLK_HIGH; // přejdeme na CLK z úrovně Low do úrovně High, a budič si zapíše hodnotu bitu, kterou jsme nastavili na DIN
	maska = maska>>1; // rotujeme masku abychom v příštím kroku vysílali nižší bit
	CLK_LOW; // vrátíme CLK zpět do Low abychom mohli celý proces vysílání bitu opakovat
}

// poté pošleme dolních 8 bitů zprávy (data/argument)
maska = 0b10000000;
while(maska){ // dokud jsme neposlali všech 8 bitů
	if(maska & data){ // pokud má právě vysílaný bit hodnotu 1
		DATA_HIGH; // nastavíme budiči vstup DIN do úrovně High
	}
	else{ // jinak má právě vysílaný bit hodnotu 0 a...
		DATA_LOW;	// ... nastavíme budiči vstup DIN do úrovně Low
	}
	CLK_HIGH; // přejdeme na CLK z úrovně Low do úrovně High, a v budič si zapíše hodnotu bitu, kterou jsme nastavili na DIN
	maska = maska>>1; // rotujeme masku abychom v příštím kroku vysílali nižší bit
	CLK_LOW; // vrátíme CLK zpět do Low abychom mohli celý proces vysílání bitu opakovat
}

CS_HIGH; // nastavíme LOAD/CS z úrovně Low do úrovně High a vygenerujeme tím vzestupnou hranu (pokyn pro MAX7219 aby zpracoval náš příkaz)
}