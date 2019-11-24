#include <Arduino.h>
#include "Ultrasonic.h"

//Os fios devem estar conectados nos pinos abaixo para o RX e TX
#define RX 0
#define TX 10

 Ultrasonic ultrassom(8,7); // define o nome do sensor(ultrassom)
//e onde esta ligado o trig(8) e o echo(7) respectivamente
 
long distancia;
 
 void setup() {
 Serial.begin(9600); //Habilita Comunicação Serial a uma taxa de 9600 bauds.
 
 }
 
 void loop()
 {
   distancia = ultrassom.Ranging(CM); // ultrassom.Ranging(CM) retorna a distancia em
                                      // centímetros(CM) ou polegadas(INC)
    if(distancia < 40){
      Serial.println("Passou o lixo");
      Serial.print(distancia); //imprime o valor da variável distancia
      Serial.println("cm");
      digitalWrite(TX, LOW);  //Mensagem para a haspberry de que passou o lixo
    }else{
      digitalWrite(TX, HIGH); //Mensagem para a haspberry de que ainda não percebe nada no sensor
    }
    
    delay(100);
 }