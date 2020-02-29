#include <i2cmaster.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>


Adafruit_MLX90614 mlx1 = Adafruit_MLX90614(0x55); //0x55 is adress device 1
Adafruit_MLX90614 mlx2 = Adafruit_MLX90614(0x5A); //0x5A is adress device 2
Adafruit_MLX90614 mlx3 = Adafruit_MLX90614(0x58); //0x58 is adress device 3
void setup() {
  Serial.begin(9600);

  Serial.println("Adafruit MLX90614 test"); 

  mlx1.begin();
  mlx2.begin();
  mlx3.begin();
   
}

void loop() {
  Serial.print("Ambient1 = "); Serial.print(mlx1.readAmbientTempC());
  Serial.print("*C\tObject1 = "); Serial.print(mlx1.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient2 = "); Serial.print(mlx2.readAmbientTempC());
  Serial.print("*C\tObject2 = "); Serial.print(mlx2.readObjectTempC()); Serial.println("*C");
  Serial.print("Ambient3 = "); Serial.print(mlx3.readAmbientTempC());
  Serial.print("*C\tObject3 = "); Serial.print(mlx3.readObjectTempC()); Serial.println("*C");


  Serial.println();
  delay(1000);
}
