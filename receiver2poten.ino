#include <LiquidCrystal.h>
#include <SoftwareSerial.h>                                                    //add the soft serial libray
SoftwareSerial ble(0, 1); // RX, TX

//Constants
const int ledPin = 7; //Led to Arduino pin 3 (PWM)
#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD
#define VELOCIDAD 300 // Velocidad a la que se mueve el texto
//Variables
bool started= false;//True: Message is strated
bool ended 	= false;//True: Message is finished 
char incomingByte ; //Variable to store the incoming byte
char msg[3];		//Message - array from 0 to 2 (3 values - PWM - e.g. 240)
byte index;			//Index of array
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup() {

	//Start the serial communication
	Serial.begin(9600); //Baud rate must be the same as is on xBee module
	pinMode(ledPin, OUTPUT);
   Serial.begin(9600);
    Serial.print("BLEbee v1.0.0 Sketch setup...");
  ble.begin(9600);

  // Configuramos las filas y las columnas del LCD en este caso 16 columnas y 2 filas
  lcd.begin(COLS, ROWS);
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.print("Welcome to DPTelemetry sytstem coordinator.");
  delay(2000);
  lcd.clear();
}

void loop() {
	  // Limpiamos la pantalla
//lcd.setCursor(16,1);
//  lcd.autoscroll();
 
  // Situamos el cursor en la columna 0 fila 0
  lcd.setCursor(0,0);
  while (Serial.available()>0 && Serial.available()){
  	//Read the incoming byte
    incomingByte = Serial.read();
    //Start the message when the '<' symbol is received
    if(incomingByte == '<')
    {
     started = true;
     index = 0;
     msg[index] = '\0'; // Throw away any incomplete packet
   }
   //End the message when the '>' symbol is received
   else if(incomingByte == '>')
   {
     ended = true;
     break; // Done reading - exit from while loop!
   }
   //Read the message!
   else
   {
     if(index < 4) // Make sure there is room
     {
       msg[index] = incomingByte; // Add char to array
       index++;
       msg[index] = '\0'; // Add NULL to end
     }
   }
 }
 
 if(started && ended)
 {
   int value = atoi(msg);
   analogWrite(ledPin, value);
   //Serial.println(value); //Only for debugging
   index = 0;
   msg[index] = '\0';
   started = false;
   ended = false;
 }
 //ble
/*  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;       
    Serial2.print("Hello from Arduino: ");      
    Serial2.println(cnt++);
  }
  */
 /// fin ble
 String mensage;
  mensage = String(atoi(msg));
 Serial.print(msg);//Value from 0 to 255
ble.print(msg);
 // Escribimos Hola Mundo!!!!!!
  lcd.print(msg);  
    // wait a bit:
   //delay(150);
    
}
  

