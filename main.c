#include <proc/pic18f4520.h>
#include "config.h"
#include "timer.h"
#include "adc.h"
#include "lcd.h"
#include "ssd.h"
#include "keypad.h"
#include "atraso.h"
#include "pwm.h"
#include "bits.h"


#define L_ON  0x0F
#define L_OFF 0x08
#define L_CLR 0x01
#define L_L1  0x80
#define L_L2  0xC0

char Flag = 1, tecla;
unsigned int Leitura = 0;
int ValorAD = 0, con1 = 0;
unsigned long int v = 0;
unsigned char LED[1] = {0b011111111};
void LeTeclado(void) {
    
    
    
    if (kpRead() != Leitura) {
        Leitura = kpRead();
        pwmInit();
        ssdInit();
        
        switch (kpReadKey()) {
            case 'U':
                lcdCommand(L_L1);
                lcdString("GASOLINA");
                atraso_ms(1000);
                lcdCommand(L_L2);
                lcdString("QUAL O VALOR?");
                atraso_ms(1000);
                lcdCommand(L_CLR);
                
                for (;;) {
            
                    v = adcRead(0);
                    lcdCommand(0x80);
                    lcdString("R$");
                    lcdChar((v / 1000) % 10 + 48);
                    lcdChar((v / 100) % 10 + 48);
                    lcdChar((v / 10) % 10 + 48);
                    lcdChar(v % 10 + 48);
                    lcdPosition(1, 0);
                    
                    if (kpRead() != tecla)
                        tecla = kpRead();
                    if (bitTst(tecla, 6)) {
                        
                        break;
                    }
                    kpDebounce();

                }
                lcdCommand(L_CLR);
                lcdString("AGUARDE......");
                atraso_ms(2000);
                lcdCommand(L_CLR);
                lcdString("Abastecendo....");
                atraso_ms(2000);
                lcdCommand(L_CLR);
                lcdString("VEICULO ");
                lcdPosition(1,0);
                lcdString("ABASTECIDO");
                PORTD = LED;
                pwmSet(100);
                atraso_ms(1500);
                pwmSet(0);
                lcdCommand(L_CLR);
                break;
            case 'L':
                lcdCommand(L_CLR);
                lcdCommand(L_L1);
                lcdString("ALCOOL");
                atraso_ms(1000);
                lcdCommand(L_L2);
                lcdString("QUANTOS LITROS?");
                atraso_ms(1500);
                lcdCommand(L_CLR);
                for (;;) {
            
                    v = adcRead(0);
                    lcdCommand(0x80);
                    lcdString("R$");
                    lcdChar((v / 1000) % 10 + 48);
                    lcdChar((v / 100) % 10 + 48);
                    lcdChar((v / 10) % 10 + 48);
                    lcdChar(v % 10 + 48);
                    lcdPosition(1, 0);
                    
                    if (kpRead() != tecla)
                        tecla = kpRead();
                    if (bitTst(tecla, 6)) {
                        
                        break;
                    }
                    kpDebounce();

                }
                lcdCommand(L_CLR);
                lcdString("AGUARDE......");
               atraso_ms(2000);
                lcdCommand(L_CLR);
                lcdString("Abastecendo....");
                atraso_ms(2000);
                lcdCommand(L_CLR);
                lcdString("VEICULO ");
                lcdPosition(1,0);
                lcdString("ABASTECIDO");
                PORTD = LED;
                pwmSet(100);
                atraso_ms(1500);
                pwmSet(0);
                lcdCommand(L_CLR);


                break;
            case 'D':
                lcdCommand(L_CLR);
                lcdCommand(L_L1);
                lcdString("DIESEL");
                atraso_ms(1000);
                lcdCommand(L_L2);
                lcdString("QUANTOS LITROS?");
                atraso_ms(1000);
                lcdCommand(L_CLR);
                lcdCommand(0xC0);
               for (;;) {
            
                    v = adcRead(0);
                    lcdCommand(0x80);
                    lcdString("R$");
                    lcdChar((v / 1000) % 10 + 48);
                    lcdChar((v / 100) % 10 + 48);
                    lcdChar((v / 10) % 10 + 48);
                    lcdChar(v % 10 + 48);
                    lcdPosition(1, 0);
                    
                    if (kpRead() != tecla)
                        tecla = kpRead();
                    if (bitTst(tecla, 6)) {
                        
                        break;
                    }
                    kpDebounce();

                }
                lcdCommand(L_CLR);
                lcdString("AGUARDE......");
               atraso_ms(2000);
                lcdCommand(L_CLR);
                lcdString("Abastecendo....");
                atraso_ms(2000);
                lcdCommand(L_CLR);
                lcdString("VEICULO ");
                lcdPosition(1,0);
                lcdString("ABASTECIDO");
                PORTD = LED;
                pwmSet(100);
                atraso_ms(1500);
                pwmSet(0);
                lcdCommand(L_CLR);
                
                break;

            case 'S':
                lcdCommand(L_CLR);
                break;
            default:
                break;
        }
    }
}


void main(void) {
    char slot;

    kpInit();
    adcInit();
    lcdInit();
    ssdInit();
    timerInit();
    pwmInit();
    while (kpReadKey() != 'S') {
        kpDebounce();
        //primeira linha
        lcdCommand(0x80);
        lcdString("BEM VINDOS");
        lcdCommand(0xC0);
        lcdString("POSTO 69 ");
    }


    for (;;) {

        timerReset(5000);
        

        switch (slot) {
            case 0:
                LeTeclado();
                slot = 1;
                break;
            
            case 1:
                kpDebounce();
                slot = 3;
                break;
                slot = 0;
                break;
            default:
                slot = 0;
                break;
        }

        timerWait();
    }
}
