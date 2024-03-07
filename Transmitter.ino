#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//Both transmitter and reciever must have the same pipe out value.  
const uint64_t pipeOut = 0xE8E8F0F0E1LL;

RF24 radio(9, 10); // select  CE and CSN  pin

//This struct gives us 5 8-bit channels
struct MyData {
  byte throttle; //Elevation control
  byte yaw;      //Vertical axis rotation
  byte pitch;    //Lateral axis rotation
  byte roll;     //Longitudinal axis rotation
  byte AUX1;     //For the Light source
};

MyData data;

void resetData() 
{
// Throttle is 0 in order to stop the motors
//127 is the middle value of the A/D Converter.
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
}

void setup()
{
  //Start everything up
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  resetData();
}

/**************************************************/

// Returns a corrected value for a joystick position that takes into account
// the values of the outer extents and the middle of the joystick range.
int mapJoystickValues(int val, int lower, int middle, int upper, bool reverse)
{
  val = constrain(val, lower, upper);
  if ( val < middle )
    val = map(val, lower, middle, 0, 128);
  else
    val = map(val, middle, upper, 128, 255);
  return ( reverse ? 255 - val : val );
}

void loop()
{
  // The calibration numbers used here should be measured 
  // for your joysticks till they send the correct values.
  data.throttle = mapJoystickValues( analogRead(A0), 13, 524, 1015, true );
  data.yaw      = mapJoystickValues( analogRead(A1),  1, 505, 1020, true );
  data.pitch    = mapJoystickValues( analogRead(A2), 12, 544, 1021, true );
  data.roll     = mapJoystickValues( analogRead(A3), 34, 522, 1020, true );
  data.AUX1     = digitalRead(4); //The switch or potentiometer

  radio.write(&data, sizeof(MyData));
}