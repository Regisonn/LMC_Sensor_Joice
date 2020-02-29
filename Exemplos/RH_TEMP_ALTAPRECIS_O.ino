#include <Wire.h>
#include <ClosedCube_HDC1080.h>
ClosedCube_HDC1080 hdc1080;



void setup()
{
  Serial.begin(9600);
  //Inicializa o HDC1080 no endereço 0x40
  hdc1080.begin(0x40);
  Serial.println("Sensor HDC1080 com Arduino");
  
 
}
void loop()
{
  //Ler os valores de temperatura e umidade
  float t = hdc1080.readTemperature();
  float h = hdc1080.readHumidity();
  
  //Mostra os valores no Serial Monitor
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" C, Umidade: ");
  Serial.print(h);
  Serial.println(" %");
  delay(1000);
}
