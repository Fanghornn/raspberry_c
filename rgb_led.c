/*
 * rgb_led.c:
 *
 *  Doc wiringPI : https://projects.drogon.net/raspberry-pi/wiringpi/functions/
 *
 *  Controle d'une LED RGB
 *
 *  Le mode PWM (pulse with modulation/modulation de largeur d'impulsions)
 *  peut permettre de mélanger les couleurs d'allumage
 *  http://fr.wikipedia.org/wiki/Modulation_de_largeur_d%27impulsion
 *
 *  Rajouter "-lwiringPi" en dernier argument de compilation avec gcc
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <signal.h>

//Macros
#define RED 1
#define GREEN 4
#define BLUE 5

void togglePins(int value, int color)
{
    digitalWrite(color,value);

    return;
}

void setPinsOff(int signum)
{
    if(signum == SIGINT)
    {
        //Reset du courant éléctrique dans les pins
        togglePins(0, RED);
        togglePins(0, GREEN);
        togglePins(0, BLUE);

        printf("Programme interronpu\nArrêt du courant dans les pins de la LED\n");

        exit(0);
    }

    return;
}

void poulet()
{

    int i = 0;

    while(i != 50)
    {
        togglePins(1, RED);
        delay(120);
        togglePins(0, RED);

        togglePins(1, BLUE);
        delay(120);
        togglePins(0, BLUE);

        i++;
    }

    return;

}

int main (void)
{
    printf("Et la lumière fu !\n");

    if(wiringPiSetup () == -1){
        printf("L'initialisation des GPIO à echoué\n");
        return 1;
    }

    //Configuration des pin
    //BCM GPIO18
    pinMode(RED, OUTPUT);

    //BCM GPIO23
    pinMode(GREEN, OUTPUT);

    //BCM GPIO24
    pinMode(BLUE, OUTPUT);

    //Handler du signal d'interruption du programme -> http://www.gnu.org/software/libc/manual/html_node/Termination-Signals.html#Termination-Signals
    signal(SIGINT, setPinsOff);

    while(1)
    {
        //les 3 en même temps
        togglePins(1, RED);
        togglePins(1, GREEN);
        togglePins(1, BLUE);

        delay(500);

        togglePins(0, RED);
        togglePins(0, GREEN);
        togglePins(0, BLUE);

        delay(500);

        //Rouge ON
        togglePins(1, RED);
        delay(500);

        //Rouge OFF
        togglePins(0, RED);
        delay(500);

        //Vert ON
        togglePins(1, GREEN);
        delay(500);
        //Vert OFF
        togglePins(0, GREEN);
        delay(500);

        //Bleu ON
        togglePins(1, BLUE);
        delay(500);
        //Bleu OFF
        togglePins(0, BLUE);

        delay(500);

        poulet();

        delay(500);
    }

    return 0;

}
