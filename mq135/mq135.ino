#include "MQ135.h"  //Thêm thư viện
 
#define PIN_MQ135 A0    //Khai báo pin nối với chân AO
MQ135 mq135_sensor = MQ135(PIN_MQ135);   //Khai báo đối tượng thư viện
 
void setup() {
  Serial.begin(115200);   //Mở serial
}
 
void loop() {
  float ppm = mq135_sensor.getPPM();  //Đọc giá trị ppm
  Serial.print("PPM: ");
  Serial.print(ppm);
  Serial.println("ppm");
  delay(2000);
}
