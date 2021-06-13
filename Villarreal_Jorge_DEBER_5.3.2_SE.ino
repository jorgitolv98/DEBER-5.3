/*
* CAPÍTULO 5: FUNCIONES ESPECÍFICAS
* PROGRAMA 26: Manejo de prioridades en RTOS
* OBJETIVO: Ejecutar tareas directamente en el Kernel del uC.
* NOMBRE: Jorge Villarreal
*/
#include <Arduino_FreeRTOS.h> // librería de RTOS
// LEDS EN ARDUINO PARA SIMULACIÓN DE PROCESOS
#define RED 8
#define YELLOW 7
#define BLUE 6
//objeto del gestor tareas
typedef int TaskProfiler;
//definir las tareas
TaskProfiler redLEDProfiler;
TaskProfiler yellowLEDProfiler;
TaskProfiler blueLEDProfiler;
TaskHandle_t red_Handle,blue_Handle,yellow_Handle; // manejar la prioridad
int monitor_suspend=0;
void setup() {
Serial.begin(9600);
//crear las rutinas de cada tarea
xTaskCreate(redLedControllerTask,"Red LED Task",100,NULL,1,&red_Handle); //rutina,nombre,memoria,NULL,prioridad,Manejo de prioridad
xTaskCreate(blueLedControllerTask,"Blue LED Task",100,NULL,1,&blue_Handle); //rutina,nombre,memoria,NULL,prioridad,NULL
xTaskCreate(yellowLedControllerTask,"Yellow LED Task",100,NULL,1,&yellow_Handle); //rutina,nombre,memoria,NULL,prioridad,NULL
}
void redLedControllerTask(void *pvParameters){//tarea 1
 pinMode(RED,OUTPUT);
 while(1){
 //Serial.println("Proceso led rojo");
 redLEDProfiler++;
 Serial.print("RED TASK:");
 Serial.println(redLEDProfiler);
 digitalWrite(RED,digitalRead(RED)^1);
 vTaskDelay(50);
 }
}
void blueLedControllerTask (void *pvParameters){
pinMode(BLUE,OUTPUT);
 while(1){
 //Serial.println("Proceso led azul");
 blueLEDProfiler++;
 Serial.print("BLUE TASK:");
 Serial.println(blueLEDProfiler);
 digitalWrite(BLUE,digitalRead(BLUE)^1);
 vTaskDelay(50);
 }
}
void yellowLedControllerTask (void *pvParameters){
pinMode(YELLOW,OUTPUT);
while(1){
 //Serial.println("Proceso led amarillo");
 yellowLEDProfiler++;
 Serial.print("YELLOW TASK:");
 Serial.println(yellowLEDProfiler);
 digitalWrite(YELLOW,digitalRead(YELLOW)^1);
 // vTaskPrioritySet(red_Handle,2); // modificar prioridad de la rutina de led rojo no debe haber delays
 monitor_suspend++;
 if(monitor_suspend==10){
 vTaskSuspend(red_Handle);
 }
 if(monitor_suspend==20){
 vTaskResume(red_Handle);
 monitor_suspend=0;
 }
 vTaskDelay(50);
 }
}
void loop() {
}
