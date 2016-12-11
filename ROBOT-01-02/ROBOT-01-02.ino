#include <Servo.h>



/* Servo - Sweep
   by BARRAGAN <http://barraganstudio.com>
   This example code is in the public domain.

   modified 28 May 2015 by Michael C. Miller
   modified 8 Nov 2013 by Scott Fitzgerald

   http://arduino.cc/en/Tutorial/Sweep
   https://github.com/esp8266/Arduino/blob/master/libraries/Servo/examples/Sweep/Sweep.ino
*/
Servo servo1;  // create servo object to control a servo
Servo servo2;  // create servo object to control a servo
Servo servo3;  // create servo object to control a servo
Servo servo4;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int firepos1;
int firepos2;
int firepos3;
int firepos4;

int readpos1;
int readpos2;
int readpos3;
int readpos4;

int pos1;
int pos2;
int pos3;
int pos4;


int maxpos1 = 180;
int minpos1 = 0;
int initpos1 = 90;

int maxpos2 = 180;
int minpos2 = 100;
int initpos2 = 140;

int maxpos3 = 120;
int minpos3 = 10;
int initpos3 = 100;

int maxpos4 = 110;
int minpos4 = 0;
int initpos4 = 70;


#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "arduino-5ae20.firebaseio.com"
#define FIREBASE_AUTH "720aYgkaZJwiqu3WsDoHcaDahc1H6sryhogyVbXD"
#define WIFI_SSID "Gottvaldova"
#define WIFI_PASSWORD "ivana1234"

// Update these with values suitable for your network.
IPAddress ip(192, 168, 0, 130); //Node static IP
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);


#include <Adafruit_NeoPixel.h>

// NeoPixel stick DIN pin
#define DIN_PIN 14 //D5

// How many NeoPixels on the stick?
#define NUM_PIXELS 8  //GPI14/D4

// Third parameter:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream (NeoPixel Stick)
//   NEO_KHZ400  400 KHz bitstream for FLORA pixels
//   NEO_KHZ800  800 KHz bitstream for High Density LED strip (NeoPixel Stick)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, DIN_PIN, NEO_GRB + NEO_KHZ800);

int pause = 1000;
int pinservo1 = 5; // attaches the servo on GPIO5/D1
int pinservo2 = 4; //                       GPIO4/D2
int pinservo3 = 0; //                    GPIO0/D3
int pinservo4 = 2; //                      GPIO2/D4

void setup()

{

  //int pinservo1=5;  // attaches the servo on GPIO5/D1
  //int pinservo2=4;  //                       GPIO4/D2
  //int pinservo3=0;  //                    GPIO0/D3
  //int pinservo4=2;  //                      GPIO2/D4


  servo1.attach(pinservo1);  // attaches the servo on GPIO5/D1
  servo2.attach(pinservo2);  //                       GPIO4/D2
  servo3.attach(pinservo3);  //                    GPIO0/D3
  servo4.attach(pinservo4);  //                      GPIO2/D4

  //servo2.attach(1);  // attaches the servo on GPIO2 to the servo object

  //servo2.attach(2);  // attaches the servo on GPIO2 to the servo object

  //servo3.attach(5);  // attaches the servo on GPIO2 to the servo object

  // servo3.attach(3);  // attaches the servo on GPIO2 to the servo object
  //servo4.attach(4);  // attaches the servo on GPIO2 to the servo object
  //myservo.write(100);

  //Position initial


  /*
    servo1.write(initpos1);
    servo2.write(initpos2);
    servo3.write(initpos3);
    servo4.write(initpos4);

    colorWipe(strip.Color(0, 0, 0), 100);
    delay(pause);
    colorWipe(strip.Color(255, 0, 0), 100);
    delay(pause);
    colorWipe(strip.Color(0, 255, 0), 100);
    delay(pause);
    colorWipe(strip.Color(0, 0,255 ), 100);
    delay(pause);
  */
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  WiFi.config(ip, gateway, subnet);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());


  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);



  strip.begin();
  strip.show(); // Start with all pixels off
  int pause = 1000;

  delay(pause);
}

void loop()
{

  int redvalue = Firebase.getInt("Robot/redvalue");
  int greenvalue = Firebase.getInt("Robot/greenvalue");
  int bluevalue = Firebase.getInt("Robot/bluevalue");
  //Serial.println("Color Wipe Red");
  // Serial.println(redvalue);
  colorWipe(strip.Color(redvalue, greenvalue, bluevalue), 100);
  delay(pause);

  // get value

  //Firebase.setInt("Robot/servo1read",readpos1);
  //Firebase.setInt("Robot/servo2read",readpos2);
  //Firebase.setInt("Robot/servo3read",readpos3);
  //Firebase.setInt("Robot/servo4read",readpos4);


  // control a servo1----------------------------------------------------------




  readpos1 = servo1.read();
  Firebase.setInt("Robot/servo1read", readpos1);
  firepos1 = Firebase.getInt("Robot/servo1");

  //Serial.println("readpos1");
  //Serial.println(readpos1);


  //Serial.println("firepos1");
  //Serial.println(firepos1);

  if (firepos1 == readpos1)

  {
    Serial.println("1==");
    servo1.detach();
  }
  else
  {
    Serial.println("1not ==");
    servo1.attach(pinservo1);



    if (firepos1 > maxpos1) {
      firepos1 = maxpos1;
      Firebase.setInt("Robot/servo1", firepos1);
    }
    if (firepos1 <  minpos1) {
      firepos1 = minpos1;
      Firebase.setInt("Robot/servo1", firepos1);
    }
    servo1.write(firepos1);


    if (firepos1 >  readpos1) {

      //Serial.println("case 1");


      for (pos1 = readpos1; pos1 <= firepos1; pos1 += 1) // goes from 180 degrees to 0 degrees
      {



        servo1.write(pos1);
        servo1.write(pos1);
        delay(15);                        // waits 15ms for the servo to reach the position

      };
    }

    if (firepos1 <  readpos1) {

      // Serial.println("case 1");
      // Serial.println("readpos1");
      // Serial.println(readpos1);
      for (pos1 = readpos1 ; pos1 >= firepos1 ; pos1 -= 1) // goes from 180 degrees to 0 degrees
      {



        //Serial.println("case 1");
        Serial.println(pos1);
        servo1.write(pos1);
        delay(15);                        // waits 15ms for the servo to reach the position


      };

    }
  }



  // control a servo2----------------------------------------------------------




  readpos2 = servo2.read();
  Firebase.setInt("Robot/servo2read", readpos2);
  firepos2 = Firebase.getInt("Robot/servo2");

  //Serial.println("readpos2");
  //Serial.println(readpos2);


  //Serial.println("firepos2");
  //Serial.println(firepos2);

  if (firepos2 == readpos2)

  {
    Serial.println("2==");
    servo2.detach();
  }
  else
  {
    Serial.println("2not ==");
    servo2.attach(pinservo2);



    if (firepos2 > maxpos2) {
      firepos2 = maxpos2;
      Firebase.setInt("Robot/servo2", firepos2);
    }
    if (firepos2 <  minpos2) {
      firepos2 = minpos2;
      Firebase.setInt("Robot/servo2", firepos2);
    }
    servo2.write(firepos2);


    if (firepos2 >  readpos2) {

      //Serial.println("case 1");


      for (pos2 = readpos2; pos2 <= firepos2; pos2 += 1) // goes from 180 degrees to 0 degrees
      {



        servo2.write(pos2);
        servo2.write(pos2);
        delay(15);                        // waits 15ms for the servo to reach the position

      };
    }

    if (firepos2 <  readpos2) {

      // Serial.println("case 2");
      // Serial.println("readpos2");
      // Serial.println(readpos2);
      for (pos2 = readpos2 ; pos2 >= firepos2 ; pos2 -= 1) // goes from 180 degrees to 0 degrees
      {



        //Serial.println("case 2");
        Serial.println(pos2);
        servo2.write(pos2);
        delay(15);                        // waits 15ms for the servo to reach the position


      };

    }
  }


 // control a servo3----------------------------------------------------------




  readpos3 = servo3.read();
  Firebase.setInt("Robot/servo3read", readpos3);
  firepos3 = Firebase.getInt("Robot/servo3");

  //Serial.println("readpos3");
  //Serial.println(readpos3);


  //Serial.println("firepos3");
  //Serial.println(firepos3);

  if (firepos3 == readpos3)

  {
    Serial.println("3==");
    servo3.detach();
  }
  else
  {
    Serial.println("3not ==");
    servo3.attach(pinservo3);



    if (firepos3 > maxpos3) {
      firepos3 = maxpos3;
      Firebase.setInt("Robot/servo3", firepos3);
    }
    if (firepos3 <  minpos3) {
      firepos3 = minpos3;
      Firebase.setInt("Robot/servo3", firepos3);
    }
    servo3.write(firepos3);


    if (firepos3 >  readpos3) {

      //Serial.println("case 1");


      for (pos3 = readpos3; pos3 <= firepos3; pos3 += 1) // goes from 180 degrees to 0 degrees
      {



        servo3.write(pos3);
        servo3.write(pos3);
        delay(15);                        // waits 15ms for the servo to reach the position

      };
    }

    if (firepos3 <  readpos3) {

      // Serial.println("case 3");
      // Serial.println("readpos3");
      // Serial.println(readpos3);
      for (pos3 = readpos3 ; pos3 >= firepos3 ; pos3 -= 1) // goes from 180 degrees to 0 degrees
      {



        //Serial.println("case 3");
        Serial.println(pos3);
        servo3.write(pos3);
        delay(15);                        // waits 15ms for the servo to reach the position


      };

    }
  }













/*
  // control a servo3----------------------------------------------------------
  readpos3 = servo3.read();
  Firebase.setInt("Robot/servo3read", readpos3);
  firepos3 = Firebase.getInt("Robot/servo3");

  //Serial.println("readpos3");
  //Serial.println(readpos3);


  //Serial.println("firepos3");
  //Serial.println(firepos3);

  if (firepos3 == readpos3)

  {
    Serial.println("3==");
    servo3.detach();
  }
  else
  {
    Serial.println("3not ==");
    servo3.attach(pinservo3);



    if (firepos3 > maxpos3) {
      firepos3 = maxpos3;
      Firebase.setInt("Robot/servo3", firepos3);
    }
    if (firepos3 <  minpos3) {
      firepos3 = minpos3;
      Firebase.setInt("Robot/servo3", firepos3);
    }
    servo3.write(firepos3);


    if (firepos3 >  readpos3) {

      //Serial.println("case 1");


      for (pos3 = readpos3; pos3 <= firepos3; pos3 += 1) // goes from 180 degrees to 0 degrees
      {



        servo3.write(pos3);
        servo3.write(pos3);
        delay(15);                        // waits 15ms for the servo to reach the position

      };
    }

    if (firepos3 <  readpos3) {

      // Serial.println("case 3");
      // Serial.println("readpos3");
      // Serial.println(readpos3);
      for (pos3 = readpos3 ; pos3 >= firepos3 ; pos3 -= 1) // goes from 180 degrees to 0 degrees
      {



        //Serial.println("case 3");
        Serial.println(pos3);
        servo3.write(pos3);
        delay(15);                        // waits 15ms for the servo to reach the position


      };

    }
  }








*/


  // control a servo4----------------------------------------------------------





  readpos4 = servo4.read();
  Firebase.setInt("Robot/servo4read", readpos4);
  firepos4 = Firebase.getInt("Robot/servo4");

  if (firepos4 == readpos4)

  {
    // Serial.println("4==");
    servo4.detach();
  }
  else
  {
    //Serial.println("4not ==");
    servo4.attach(pinservo4);
    if (firepos4 > maxpos4) {
      firepos4 = maxpos4;
      Firebase.setInt("Robot/servo4", firepos4);
    }

    if (firepos4 <  minpos4) {
      firepos4 = minpos4;
      Firebase.setInt("Robot/servo4", firepos4);
    }


    if (firepos4 >  readpos4) {


      for (pos4 = readpos4; pos4 <= firepos4; pos4 += 1) // goes from 180 degrees to 0 degrees
      {

        servo4.write(pos4);
        delay(15);                        // waits 15ms for the servo to reach the position

      };
    }

    if (firepos4 <=  readpos4) {

      for (pos4 = readpos4 ; pos4 >= firepos4 ; pos4 -= 1) // goes from 180 degrees to 0 degrees
      {

        servo4.write(pos4);
        delay(15);                        // waits 15ms for the servo to reach the position


      };

    }

  }




}



// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  uint16_t i;
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


