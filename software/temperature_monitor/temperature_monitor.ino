

  #include <Wire.h>
  //Defiing all of our pins here 

  //Signal Pin from multiplexer to the Arduino
  const int muxSIG = A0; 

  //Pins that will select what channel to read in binary
  const int muxS0 = 2;
  const int muxS1 = 3;
  const int muxS2 = 4;

  //Global variables for channels and array
  const int numChannels = 8;
  float temperatures[numChannels];

  const float overheatTemp = 60.0f; // Critical limit (°C)

  const int faultLED = 7;

  
  //Defining address for Arduino as Slave
  const byte SLAVE_ADDRESS = 0x08;

  void setMuxChannel(byte channel);
  void requestData();
  void blinkFaultLED();  
  float voltagetoTemperature(int rawADC);
  

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

  //Setting up select pins and digital pins for 8:1 multiplexor
  //They are configured as output because we are going to set the pins from our code to read a particular channel
  pinMode(muxS0, OUTPUT);
  pinMode(muxS1, OUTPUT);
  pinMode(muxS2, OUTPUT);

  //Setting up fault LED to Low
  pinMode(faultLED, OUTPUT);
  digitalWrite(faultLED, LOW);

  //Setting up Adruino as slave and preparing it for requests
  Wire.begin(SLAVE_ADDRESS);

  //Commenting out until we're ready to test I2C
  //Wire.onRequest(requestData);

}




float readChannelVoltage(byte channel) {
  setMuxChannel(channel);
  delayMicroseconds(20); 

  int rawADC = analogRead(muxSIG);
  return voltagetoTemperature(rawADC);

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
  for(int i = 0; i < 4; i++){ //remove loop if only want to blink once
    digitalWrite(faultLED, HIGH);
    delay(30);
    digitalWrite(faultLED, LOW);
    delay(30);
  }
  
}


//Helper function for reading the channel voltage 
//Takes in the rawADC value and then converts to temperature value in Celsius, using linear interpolation
float voltagetoTemperature(int rawADC) {
  float volt = (rawADC * 4.91) / 1024;
  float temp = (volt/4.91)* -160.0 + 120.0;
  return temp;
  
}


void loop() {
  //Starting Values to compare to when trying to store maximum and minimum values 
  float maxTemp = -999.0f;
  float minTemp = 999.0f;
  float sumTemp = 0.0f;

  // put your main code here, to run repeatedly:
  //Loop through all 8 channels
  //Read each temperature
  //Calculate the highest temperature, lowest, and the average
  //Check if we have to blink the fault LED 

  for (byte ch = 0; ch < numChannels; ch++) {
    temperatures[ch] = readChannelVoltage(ch); 
    Serial.print("Channel ");
    Serial.print(ch); 
    Serial.print(": ");
    Serial.print(temperatures[ch],2);
    Serial.println(" °C");

    if(temperatures[ch] > maxTemp) {
      maxTemp = temperatures[ch];
    }
    if(temperatures[ch] > overheatTemp) {
      blinkFaultLED();
    }

    if(temperatures[ch] < minTemp) {
      minTemp = temperatures[ch]; 
    }

    sumTemp = sumTemp + temperatures[ch];

    delay(200);
  }
      float avgTemp = sumTemp/numChannels;


}
