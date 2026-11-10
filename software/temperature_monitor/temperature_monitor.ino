

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

  const int gain = 4.3;

  const float overheatTemp = 60.0f; // Critical limit (°C)

  const int faultLED = 7;

  
  //Defining address for Arduino as Slave
  const byte SLAVE_ADDRESS = 0x08;
  float avgTemp = 0.0f;
  float maxTemp = -999.0f;
  float minTemp = 999.0f;

  //Creating an object for the linear interpolation
  struct table {
    float voltage;
    float temperature;
  };

  
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
  Wire.onRequest(requestData);

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
  //send avg, highest, and lowest temperatures over I2C
  Wire.write((byte*)&avgTemp, sizeof(avgTemp));
  Wire.write((byte*)&maxTemp, sizeof(maxTemp));
  Wire.write((byte*)&minTemp, sizeof(minTemp));
}

void blinkFaultLED() {
  //Use this function to blink the LED fault, use with IF statement inside loop
  for(int i = 0; i < 6; i++){ //remove loop if only want to blink once
    digitalWrite(faultLED, HIGH);
    delay(150);
    digitalWrite(faultLED, LOW);
    delay(150);
  }
  
}


//Helper function for reading the channel voltage 
//Takes in the rawADC value and then converts to temperature value in Celsius, using linear interpolation
float voltagetoTemperature(int rawADC) {
//Converts rawADC value to actual voltage value between 0-5 volts
//It will be between 1.30V to 2.44V based on the diode
  float volt = (rawADC * 4.850f) / 1024.0f;
 

  //Linear interpolation using the two datasheet coordinates
  // (-40°C @ 2.44V) and (120°C @ 1.30V)
  const float V_cold = 2.44f;
  const float V_hot  = 1.30f;
  const float T_cold = -40.0f;
  const float T_hot  = 120.0f;

  float slope = (T_hot - T_cold) / (V_hot - V_cold); // ~ -140.3509 C/V. 
  //For every voltage increase there is a -140 decrease in temperature. (negative slope)
  float temp  = T_cold + slope * (volt - V_cold);
  return temp;
}


void loop() {
  //Starting Values to compare to when trying to store maximum and minimum values 
  maxTemp = -999.0f;
  minTemp = 999.0f;
  float sumTemp = 0.0f;

  // put your main code here, to run repeatedly:
  //Loop through all 8 channels
  //Read each temperature
  //Calculate the highest temperature, lowest, and the average
  //Check if we have to blink the fault LED 


  for (byte ch = 0; ch < numChannels; ch++) {
    temperatures[ch] = readChannelVoltage(ch); 

    float chVoltage = (analogRead(A0) * 4.86f) / 1024.0f;

    Serial.print("Channel ");
    Serial.print(ch); 
    Serial.print(" | Volt: ");
    Serial.print(chVoltage, 2);
    Serial.print(" V | Temp: ");
    Serial.print(temperatures[ch], 2);
    Serial.println(" °C");

    //Delay to be able to read input and testing, for max sampling rate remove this delay
    //delay(500);

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

    //delay(200);
  }

  avgTemp = sumTemp / numChannels;
  Serial.print("AVG: ");
  Serial.print(avgTemp, 2);
  Serial.print(" °C | MAX: ");
  Serial.print(maxTemp, 2);
  Serial.print(" °C | MIN: ");
  Serial.print(minTemp, 2);
  Serial.println(" °C\n");

}
