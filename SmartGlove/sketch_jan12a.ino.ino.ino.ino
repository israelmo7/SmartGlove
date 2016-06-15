#include <Wire.h>
#include <SPI.h>
#include <WiFi.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#define ABS(x) ((x < 0)?x*-1:x)
// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10

// software SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS, LIS3DH_MOSI, LIS3DH_MISO, LIS3DH_CLK);
// hardware SPI
//Adafruit_LIS3DH lis = Adafruit_LIS3DH(LIS3DH_CS);
// I2C
Adafruit_LIS3DH lis = Adafruit_LIS3DH();

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif
void fillPlace(char* bb, int sizeFill);

char ssid[] = "HOTBOX-LIVNAT1";          //  your network SSID (name) 
char pass[] = "10203040";   // your network password

int status = WL_IDLE_STATUS;
IPAddress server(192,168,1,18);  // Google

// Initialize the client library
WiFiClient client;

void setup() {

#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif

  Serial.begin(9600);

    if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("LIS3DH found!");
  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!
  
  Serial.print("Range = "); Serial.print(2 << lis.getRange());  
  Serial.println("G");
  
  Serial.println("Attempting to connect to WPA network...");
  Serial.print("SSID: ");
  Serial.println(ssid);

  status = WiFi.begin(ssid, pass);
  if ( status != WL_CONNECTED) { 
    Serial.println("Couldn't get a wifi connection");
    // don't do anything else:
    while(true);
  } 
  else {
    Serial.println("Connected to wifi");
    Serial.println("\nStarting connection...");
    // if you get a connection, report back via serial:
    if (client.connect(server, 80)) 
    {
      Serial.println("connected");

    }
    else
    {
      Serial.println("Cant connect");
      while(true);
    }
  } 
}

void loop() 
{
  int flexSensorReading[3] ={analogRead(A0),analogRead(A1),analogRead(A2)};
  
  sensors_event_t event; 
  lis.read();      // get X Y and Z data at once
  lis.getEvent(&event);
 /*
  Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
  Serial.print(" \tY: "); Serial.print(event.acceleration.y); 
  Serial.print(" \tZ: "); Serial.print(event.acceleration.z); 
  Serial.println(" m/s^2 ");
 */
  char buffX[5];
  char buffY[5];
  char buffZ[5];

  char temp[20];
  
  itoa(flexSensorReading[0], buffX, 10);
  itoa(flexSensorReading[1], buffY, 10);
  itoa(flexSensorReading[2], buffZ, 10);



  fillPlace(buffX,2);
  fillPlace(buffY,2);
  fillPlace(buffZ,2);
 
  Serial.print("Flex0 - ");
  Serial.println(buffX);
  Serial.print("Flex1 - ");
  Serial.println(buffY);
  Serial.print("Flex2 - ");
  Serial.println(buffZ);
   
  strcpy(temp,buffX);
  strcat(temp,buffY);
  strcat(temp,buffZ);
  
  itoa(int(event.acceleration.x), buffX, 10);
 // Serial.print(buffX);
 // Serial.print("  (X)  ");
  fillPlace(buffX,3);
 // Serial.print(buffX);
 // Serial.println();
  itoa(int(event.acceleration.y), buffY, 10);
 // Serial.print(buffY);
 // Serial.print("  (Y)  ");
  fillPlace(buffY,3);
  //Serial.print(buffY);
 // Serial.println();
  
  itoa(int(event.acceleration.z), buffZ, 10);
  //Serial.print(buffZ);
 // Serial.print("  (Z)  ");
  fillPlace(buffZ,3);
  //Serial.print(buffZ);
  //Serial.println();
  


  strcat(temp, "0000");
  strcat(temp, buffX);
  strcat(temp, buffY);
  strcat(temp, buffZ);
  //strcat(temp, NULL);
  //Serial.println(temp);

  //delay(1500);
  client.print(temp);
  Serial.println(temp);
  Serial.println(strlen(temp));
  delay(1000);
}
void fillPlace(char* bb, int sizeFill)
{
  int value;
  if (!bb|| ABS(strlen(bb)) > sizeFill)
    return;

  value = atoi(bb);  // 0
  char* retStr = new char[sizeFill+1];
  retStr[sizeFill] = NULL; // [ ][ ][ ][N]
  if(value > 0)
  {
      int temp = sizeFill - strlen(bb); // 1
      unsigned int i=0;
      
      for(i; i < temp; i++)
      {
         retStr[i] = '0'; // [0][][][N]
      }
      temp = strlen(bb); // 2
      for(int j =0; j < temp; i++,j++)
      {
          retStr[i] = bb[j]; // [0][3][4][N]
      }
  }
  else
  {
      int temp = sizeFill - strlen(bb)-1; // 1
      unsigned int i=0;
      
      for(i; i < temp; i++)
      {
          retStr[i] = '0'; // [0][][][N]
      }
      temp = strlen(bb); // 1
      retStr[i++] = '-'; // [0][-][][N]
      for(int j =0; j < temp; i++,j++)
      {
         retStr[i] = bb[j]; // [0][-][0][N]
      }   
  }
  strcpy(bb, retStr);    
  delete retStr;
}
