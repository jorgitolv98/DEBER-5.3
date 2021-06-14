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

#include <MsTimer2.h> // librería timer 2
#include <avr/power.h> // librería power
#include <avr/sleep.h> // librería sleep
int on=0; // variable de encendido y modos del sistema
int tiempo=0; // variable de selección de tiempo para toma de datos
int cont=0; // conteo de timer 2
void setup() {
Serial.begin(9600); //inicia cx serial
MsTimer2::set(1000, reloj); // configura timer 2 a un segundo
attachInterrupt(0,activacion,LOW);
attachInterrupt(1,configuracion,LOW);
power_adc_disable(); // deshabilidad adc
}
void loop() {
 Serial.println(analogRead(0)); // confirmación de desactivación del cad
 delay(1000);
}
void activacion (){ // rutina de interrupción 0
switch(on){
 case 0: // caso de activación
 Serial.println("INICIO DEL SISTEMA");
 Serial.println("SELECCIONE TIEMPO DE LECTURA DEL CAD");
 on++;
 break;
 case 1: // caso de selección de tiempo
 Serial.println(String("SISTEMA FUNCIONANADO EN: ")+String(tiempo
)+String(" seg"));
 MsTimer2::start(); // activa timer
 on++;
 break;
 case 2: // sistema apagado
 Serial.println("SISTEMA APAGADO");
 tiempo=0;
 on=0;
 MsTimer2::stop(); // detiene timer
 power_adc_disable(); // deshabilidad adc
break;
 }
}
void configuracion(){ // rutina interrupcion 1
 if(on==1){
 tiempo=tiempo+10;
 if(tiempo<110){
 Serial.println(String("TIEMPO: ")+String(tiempo));
 }
 else
 tiempo=0;
 }
}
void reloj(){ // rutina de timer 2
 cont++; // cuenta cada segundo
 Serial.println(String("Lectura en: ")+String(tiempo-cont)); // mensaje de tiempo
 if(cont==tiempo){ // comparación con selección de usuario
 power_adc_enable(); // habilita adc
 delay(10);
 Serial.println(analogRead(0)); // realiza la lectura
 cont=0; // contador a cero
 }

}
