

  #include <Wire.h>
  //Defiing all of our pins here 

  //Signal Pin from multiplexer to the Arduino
  const int muxSIG = A0; 

  //Pins that will select what channel to read in binary
  const int muxS0 = 2;
  const int muxS1 = 3;
  const int muxS2 = 4;

  
  //Defining address for Arduino as Slave
  const byte SLAVE_ADDRESS = 0x08;

  void setMuxChannel(byte channel);
  void requestData();
  void blinkFaultLED();  
  void voltagetoTemperature();
  

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

  //Setting up select pins and digital pins for 8:1 multiplexor
  //They are configured as output because we are going to set the pins from our code to read a particular channel
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);
  pinMode(muxS2, OUTPUT);

  //Setting up Adruino as slave and preparing it for requests
  Wire.begin(SLAVE_ADDRESS);
  Wire.onRequest(requestData);

}




float readChannelVoltage(byte channel) {
  setMuxChannel(channel);
  delayMicroseconds(20); //Why delay 20 microsecondsn

  int rawADC = analogRead(muxSIG);

}
void setMuxChannel(byte channel)  {
  //Allows you to input an integer and then it converts it into binary for the signal pins to read and select the channel
    digitalWrite(muxS0, bitRead(channel, 0));
    digitalWrite(muxS1, bitRead(channel, 1));
    digitalWrite(muxS2, bitRead(channel, 2));
}


void requestData() {
  //send highest temperature over I2C
  

}

void blinkFaultLED() {
  //Use this function to blink the LED fault, use with IF statement inside loop
  
}


void voltagetoTemperature() {
  //Convert the analog voltage reading (0-1024) into an actual temperature values

  
}


void loop() {


  // put your main code here, to run repeatedly:
  //Loop through all 16 channels
  //Read each temperature
  //Calculate the highest temperature, lowest, and the average
  //Check if we have to blink the fault LED 

}
