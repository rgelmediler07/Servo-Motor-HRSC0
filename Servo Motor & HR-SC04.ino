#include<Arduino_FreeRTOS.h>
#include <Servo.h>
void servo(void *pvParameters);
void mesafe(void *pvParameters);

byte trigger = 2; // Sensörün Trigger bacağının bağlı olduğu pin
byte echo = 3; 
unsigned long sure; // Echo bacağının kac mikro saniyede aktif olduğunu saklayacak olan değişken 
double toplamYol; 
int aradakiMesafe; 
Servo motor;
void setup() {
 xTaskCreate(servo,
              (const portCHAR*)"TASK 1",
              100,
              NULL,
              1,
              NULL);
 
 xTaskCreate(mesafe,
              (const portCHAR*)"TASK 2",
              100,
              NULL,
              1,
              NULL);

}

void loop() {
  // put your main code here, to run repeatedly:

}
void mesafe(void *pvParameters){
 (void) pvParameters;


const char *pcTaskName="mesafe";

  pinMode(trigger, OUTPUT); // Sensörün Trigger bacağına gerilim uygulayabilmemiz için OUTPUT yapıyoruz.
  pinMode(echo, INPUT); // Sensörün Echo bacağındaki gerilimi okuyabilmemiz için INPUT yapıyoruz.
  Serial.begin(9600); 
 Serial.begin(9600);
for(;;){ 
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
 
  // Dalga üretildikten sonra geri yansıyıp Echo bacağının HIGH duruma geçireceği süreyi pulseIn fonksiyonu ile 
  // kaydediyoruz. 
  sure = pulseIn(echo, HIGH);
 
  // Aşağıda yapılan süre-mesafe dönüşüm işlemleri yazımızda açıklanmıştır. 
  toplamYol = (double)sure*0.034;
  aradakiMesafe = toplamYol / 2;
  
  Serial.print("Ses dalgasinin geri donus suresi :");
  Serial.print(sure);
  Serial.println("mikro saniye");
  
  Serial.print("Ses dalgasinin toplam kat ettigi yol :");
  Serial.print(toplamYol);
  Serial.println("cm.");
  
  Serial.print("HC-SR04 ile karsisindaki yuzey arasindaki mesafe :");
  Serial.print(aradakiMesafe);
  Serial.println("cm.\n\n");
 
  delay(2000);  
Serial.println(pcTaskName);
vTaskDelay(1000/portTICK_PERIOD_MS);

}
}
 

void servo(void *pvParameters){
 (void) pvParameters;
 
const char *pcTaskName="servo";
motor.attach(8); 
motor.write(0);
Serial.begin(9600); 
for(;;){
  if(aradakiMesafe>15    &&   aradakiMesafe<35){
    motor.write(170);
  }
  else if(aradakiMesafe<15){
    motor.write(0);
  }
  else{
    motor.write(90);
  }
Serial.println(pcTaskName);
vTaskDelay(1000/portTICK_PERIOD_MS);
}
 }
 
