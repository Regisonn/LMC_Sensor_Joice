// Programa: Sensor IR Oficial _Multi v 2.0  
// Na segunda versão foi utilizado conexão I2c com identificação de IP's, onde cada sensor dever ser reprogamado com o endereço de IP diferente do que vem de fábrica.
// Autor: Regison
//Data de criação: 10/11/2019
//Última atualização: 29/02/2020 20:20:00 UTM -4
//Programa foi criado com base nas especicações do fabricante do sensor
//#include "RTClib.h"
#include <i2cmaster.h>
#include <SdFat.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <HCSR04.h>
#include <DS1307.h>
#include <ClosedCube_HDC1080.h>
ClosedCube_HDC1080 hdc1080;


//Declarando Sensor e criando datafile para o SD 
Adafruit_MLX90614 mlx1 = Adafruit_MLX90614(0x55); //0x55 is adress device 1
Adafruit_MLX90614 mlx2 = Adafruit_MLX90614(0x5A); //0x5A is adress device 2
Adafruit_MLX90614 mlx3 = Adafruit_MLX90614(0x57); //0x57 is adress device 3
Adafruit_MLX90614 mlx4 = Adafruit_MLX90614(0x58); //0x58 is adress device 4




SdFat sdCard;
SdFile meuArquivo;

//Modulo RTC DS1307 ligando as portas A4 (SDA) e A5 (SCL) do Arduino 
DS1307 rtc(A4, A5);



// Pino ligado ao CS do modulo MicroSD
//o modulo foi configurado como conexão SPI do Arduino 
//sdk=52 MOSI=51 MISO=50  CS=53 
const int chipSelect = 53;

//configuração 
void setup()
{
  Serial.begin(9600);
  mlx1.begin();
  mlx2.begin();
  mlx3.begin();
  mlx4.begin();
  hdc1080.begin(0x40);
  pinMode(10,OUTPUT); //define o pine de saída para ascender o LED 
  //TA=mlx.readAmbientTempC()
  //TO=mlx.readObjectTempC()
  digitalWrite(10,HIGH);
     // Inicializa o modulo SD
  if(!sdCard.begin(chipSelect,SPI_HALF_SPEED))sdCard.initErrorHalt();
  // Abre o arquivo LER.TXT
  if (!meuArquivo.open("ler_Temp2.dat", O_RDWR | O_CREAT | O_AT_END))
 //nome da planilha de acordo com o local de instalção
  {
    sdCard.errorHalt("Erro na abertura do arquivo LER_temp.TXT!");
    //digitalWrite(10,HIGH); //Ascende o led para avisar erro de leitura
  }
   //Ascende o led para avisar erro de leitura
  //Aciona o relogio
  rtc.halt(false);
  
   //*********************************************************************************************
  //As linhas abaixo setam a data e hora do modulo (usado para ajusta o horario do clock)
  //Devem ser comentadas apos ajuste do horario(para evitar que o horario seja reprogramado toda vez que for lançado o modulo) 
  //rtc.setDOW(THURSDAY);      //Define o dia da semana
  //rtc.setTime(13, 42, 0);     //Define o horario (formato 24hr)
  //rtc.setDate(27, 02, 2020);   //Define o dia, mes e ano
  //rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); //CAPTURA A DATA E HORA EM QUE O SKETCH É COMPILADO
  //**********************************************************************************************
  //Definicoes do pino SQW/Out
  rtc.setSQWRate(SQW_RATE_1);
  rtc.enableSQW(true);
  

 {
  //cabeçalho da tabela  
  meuArquivo.println("Joice Experiment ");
  meuArquivo.println("Station: Teste  "); //Nome do local de instalação
  meuArquivo.println("time,T_ar1,T_obj1,T_ar2,T_obj2,T_ar3,T_obj3,T_ar4,T_obj4,Temp,RH");
 }
}
//******Criação do loop*******
void loop()
{
  // ________________Leitura do Sensor___________
  //t = rtc.getTime().;

  //Usado para piscar o LED toda vez que for efetuada uma leitura. #caso o LED fique acesso, ocorreu algum problema
  digitalWrite(10,HIGH);
  delay(10);
  digitalWrite(10,LOW);
  
  //****Exibição do painel serial***   (usado para visualizar os dados pelo computador )
  Serial.print("Amb1 = ");
  Serial.print(mlx1.readAmbientTempC()); 
  Serial.print("ºC\tObj1 = "); 
  Serial.print(mlx1.readObjectTempC()); 

  Serial.print("   Amb2 = ");
  Serial.print(mlx2.readAmbientTempC()); 
  Serial.print("ºC\tObj2 = "); 
  Serial.print(mlx2.readObjectTempC()); 

  Serial.print("    Amb3 = ");
  Serial.print(mlx3.readAmbientTempC()); 
  Serial.print("ºC\tObj3 = "); 
  Serial.print(mlx3.readObjectTempC()); 
  
  Serial.print("    Amb4 = ");
  Serial.print(mlx3.readAmbientTempC()); 
  Serial.print("ºC\tObj4 = "); 
  Serial.print(mlx3.readObjectTempC()); 

  Serial.print("    Amb4 = ");
  Serial.print(hdc1080.readTemperature()); 
  Serial.print("ºC\tObj4 = "); 
  Serial.print(hdc1080.readHumidity()); 
  
  
  Serial.print("ºC   ");
  Serial.print("Data : ");

  Serial.print(rtc.getTime().date, DEC);
  Serial.print("/");
  Serial.print(rtc.getTime().mon, DEC);
  Serial.print("/");
  Serial.print(rtc.getTime().year, DEC);
  Serial.print(" ");
  Serial.print(rtc.getTimeStr());

  
  Serial.print(" ");
  Serial.print(" ---- ");
  Serial.println(rtc.getDOWStr());

  



  

  
  //declaração de variaveis
  float TA1=(mlx1.readAmbientTempC(),4);  // numero 4 indica a quantidade de casas decimais
  float TO1=(mlx1.readObjectTempC(),4);

  float TA2=(mlx2.readAmbientTempC(),4);
  float TO2=(mlx2.readObjectTempC(),4);
  
  float TA3=(mlx3.readAmbientTempC(),4);
  float TO3=(mlx3.readObjectTempC(),4);
  
  float TA4=(mlx4.readAmbientTempC(),4);
  float TO4=(mlx4.readObjectTempC(),4);
  
  float t = (hdc1080.readTemperature(),4);
  float h = (hdc1080.readHumidity(),4);


  
  //float H=(distanceSensor.measureDistanceCm());
  // Grava dados do sensor em LER_Temp_test.TXT

  //Escrever na tabela (data,T_ar, T_obj)             //(data, dia, mes, ano, hora, T_ar, T_obj)

  //formato data e hora (dd/mm/aaaa hh:mm:ss)
  meuArquivo.print(rtc.getTime().date, DEC);
  meuArquivo.print("-");
  meuArquivo.print(rtc.getTime().mon, DEC);
  meuArquivo.print("-");
  meuArquivo.print(rtc.getTime().year, DEC);
  meuArquivo.print(" ");
  meuArquivo.print(rtc.getTimeStr());

    
  

  //dados sensor de temperatura (T_ar  T_obj)
  meuArquivo.print(",");
  meuArquivo.print(TA1,4);
  meuArquivo.print(",");
  meuArquivo.print(TO1,4);

  meuArquivo.print(",");
  meuArquivo.print(TA2,4);
  meuArquivo.print(",");
  meuArquivo.print(TO2,4);

  meuArquivo.print(",");
  meuArquivo.print(TA3,4);
  meuArquivo.print(",");
  meuArquivo.print(TO3,4);

  meuArquivo.print(",");
  meuArquivo.print(TA4,4);
  meuArquivo.print(",");
  meuArquivo.print(TO4,4);

  meuArquivo.print(",");
  meuArquivo.print(t,4);
  meuArquivo.print(",");
  meuArquivo.print(h,4);
 
  
  meuArquivo.println(); //quebra de linha 
  meuArquivo.close();
  if(!sdCard.begin(chipSelect,SPI_HALF_SPEED))sdCard.initErrorHalt();
  
  // Abre o arquivo LER_Temp.TXT
  if (!meuArquivo.open("ler_Temp2.dat", O_RDWR | O_CREAT | O_AT_END));  //abri o arquivo novamente para escrever a leitura do proximo loop
   

  delay(5000); //define o intervalo de leitura 1000 = 1 segundo 
}
