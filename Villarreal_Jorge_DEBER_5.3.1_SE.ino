/*
 * CAP V: FUNCIONES ESPECIFICAS
 * CODIGO 24: Realizar lecturas del conversor analogo digital y luego apagarlo por un tiempo establecido por el usuario
 * NOMBRE: Jorge Villarreal
 * Funciones: 
 *      power_xx_disable();
 *      power_xx_enable();
 *      xx->adc,timer0,timer1,usart,all
 *      
 *           
 */
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <MsTimer2.h>

int on;
int tiempo = 0;
int cont=0;

void setup() {
  Serial.begin(9600);
  MsTimer2::set(1000,reloj);
  attachInterrupt(0,activacion,LOW);
  attachInterrupt(1,configuracion,LOW);

}

void loop() {
  Serial.println(analogRead(0));
  delay(1000);

}

void activacion(){
  switch(on){
    case 0:
    Serial.println("Inicio del sistema");
    Serial.println("Seleccione tiempo de lectura del cad");
    power_adc_disable();
    on++;
    break;
    case 1:
    Serial.println(String("Sitema funciona en:")+String(tiempo)+String("seg"));
    MsTimer2::start();
    on++;
    break;
    case 2:
    Serial.println("Sistema apagado");
    tiempo=0;
    on=0;
    MsTimer2::stop();
    power_adc_disable();
    break;
  }
}


void configuracion(){
  if(on==1){
    tiempo=tiempo+10;
    if(tiempo<100){
      Serial.println(String("Tiempo: ")+String(tiempo));
    }else{
      tiempo=0;
    }
  }
}

void reloj(){
  power_adc_disable();
  cont++;
  Serial.println(String("Lectura en:")+String(tiempo-cont));
  if(cont==tiempo){
    power_adc_enable();
    delay(10);
    Serial.println(analogRead(0));
    cont=0;
  
  }
}
