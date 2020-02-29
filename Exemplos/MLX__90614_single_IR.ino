
#include <Wire.h>
#include <Adafruit_MLX90614.h>


//Declarando Sensor 
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

//configuração 
void setup()
{
  Serial.begin(9600);
  mlx.begin();
 
}
//******Criação do loop*******
void loop()
{
  // ________________Leitura do Sensor___________
  

 
  //****Exibição do painel serial***   (usado para visualizar os dados pelo computador )
  Serial.print("Ambiente = ");
  Serial.print(mlx.readAmbientTempC()); 
  Serial.print("ºC\tObjeto = "); 
  Serial.print(mlx.readObjectTempC()); 
  Serial.print("ºC   ");
 
  Serial.println();


  delay(1000);
}
