
void setup() {
  // put your setup code here, to run once:

  //Signal Pin from multiplayer to the Arduino
  const int muxSIG = A0;

  //Pins that will select what channel to read in binary
  const int muxS0 = 2;
  const int muxS1 = 3;
  const int muxS2 = 4;
  const int muxS3 = 5;

}



int SetMuxChannel(byte channel)  {
  //Allows you to input an integer and then it converts it into binary for the signal pins to read and select the channel
    digitalWrite(muxS0, bitread(channel, 0));
    digitalWrite(muxS1, bitread(channel, 1));
    digitalWrite(muxS2, bitread(channel, 2));
    digitalWrite(muxS3, bitread(channel, 3));
}



void sendI2CData() {
  //send highest temperature over I2C
}

void blinkFaultLED() {

}

void voltagetoTemperature()) {
  //Convert the analog voltage reading (0-1024) into an actual temperature values
}


void loop() {
  // put your main code here, to run repeatedly:
  //Loop through all 16 channels
  //Read each temperature
  //Calculate the highest temperature, lowest, and the average
  //Check if we have to blink the fault LED 

}
