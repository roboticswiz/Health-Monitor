
#include <ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/UInt32.h>
#include "spo2_algorithm.h"
ros::NodeHandle nh;

std_msgs::Float32 my_temp;
ros::Publisher pub_ardu_temp("/arduino_temp", &my_temp);
long publisher_timer_temp;

std_msgs::UInt32 my_heart;
ros::Publisher pub_ardu_heart("/arduino_heart", &my_heart);
long publisher_timer_heart;

std_msgs::UInt32 my_oxy;
ros::Publisher pub_ardu_oxy("/arduino_oxygen", &my_oxy);
long publisher_timer_oxy;


//LCD Display
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);


//OLED Display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//Servo Motor
#include <Servo.h>

Servo myservo;
int input_range = 180; // input range of 0 to 180


// MAX30105 Sensor
#include <Wire.h>
#include "MAX30105.h"
#include "heartRate.h"
#include "spo2_algorithm.h"

MAX30105 particleSensor;

//SPO2
#define MAX_BRIGHTNESS 255

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
//Arduino Uno doesn't have enough SRAM to store 100 samples of IR led data and red led data in 32-bit format
//To solve this problem, 16-bit MSB of the sampled data will be truncated. Samples become 16-bit data.
uint16_t irBuffer[100]; //infrared LED sensor data
uint16_t redBuffer[100];  //red LED sensor data
#else
uint32_t irBuffer[100]; //infrared LED sensor data
uint32_t redBuffer[100];  //red LED sensor data
#endif

int32_t bufferLength; //data length
int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid
uint32_t spo2valid;
uint32_t hrvalid;
uint32_t lcd_oxy;
uint32_t lcd_bpm;

byte readLED = 13; //Blinks with each data read


// ros to arduino communication

void temp_cb( const std_msgs::Float32& ros_temp) {
  float temp_out = ros_temp.data;
  if (temp_out > 99)
  {
    digitalWrite(8, HIGH);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 15);
    display.println("Temp High F");
    display.setCursor(70, 15);
    display.println(temp_out);
    display.display();
    tone(5, 1000);
    delay(100);
    noTone(5);

  }
  else {
    digitalWrite(7, HIGH);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 15);
    display.println("Temp Normal F");
    display.setCursor(70, 15);
    display.println(temp_out);
    display.display();
  }


}

void hr_cb( const std_msgs::UInt32& ros_hr) {
  uint32_t hr_out = ros_hr.data;

  if (hr_out <= 200 && hr_out >= 130)
  {
    digitalWrite(9, HIGH);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 30);
    display.println("BPM Normal");
    display.setCursor(70, 30);
    display.println(hr_out);
    display.display();
    myservo.write(90);
  }

  else if (hr_out > 200) {
    digitalWrite(10, HIGH);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 30);
    display.println("BPM High");
    display.setCursor(70, 30);
    display.println(hr_out);
    display.display();
    myservo.write(20);
    tone(5, 1000);
    delay(100);
    noTone(5);

  }

  else {
    digitalWrite(10, HIGH);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 30);
    display.println("BPM Low");
    display.setCursor(70, 30);
    display.println(hr_out);
    display.display();
    myservo.write(160);
    tone(5, 1000);
    delay(100);
    noTone(5);

  }
}


void spo2_cb( const std_msgs::UInt32 & ros_spo2) {
  uint32_t spo2_out = ros_spo2.data;

  if (spo2_out < 95)
  {
    digitalWrite(12, HIGH);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 50);
    display.println("SPO2 LOW");
    display.setCursor(70, 50);
    display.println(spo2_out);
    display.display();
    tone(5, 1000);
    delay(100);
    noTone(5);

  }

  else {
    digitalWrite(11, HIGH);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 50);
    display.println("SPO2 Normal");
    display.setCursor(70, 50);
    display.println(spo2_out);
    display.display();
  }
}

ros::Subscriber<std_msgs::Float32> sub_temp("ros_temp", &temp_cb);
ros::Subscriber<std_msgs::UInt32> sub_hr("ros_hr", &hr_cb);
ros::Subscriber<std_msgs::UInt32> sub_spo2("ros_spo2", &spo2_cb);



void setup()
{ //Node & Topics publishing and subscribing initialization
  nh.initNode();
  nh.advertise(pub_ardu_temp);
  nh.advertise(pub_ardu_heart);
  nh.advertise(pub_ardu_oxy);
  nh.subscribe(sub_temp);
  nh.subscribe(sub_hr);
  nh.subscribe(sub_spo2);

  //LED
  pinMode(5, OUTPUT);//Buzzer
  myservo.attach(6);  // servo motor
  pinMode(7, OUTPUT);//Temperature Blue
  pinMode(8, OUTPUT);//Temperatue Red
  pinMode(9, OUTPUT);//Heart Rate Blue
  pinMode(10, OUTPUT);//Heart Rate Red
  pinMode(11, OUTPUT);//SPO2 Blue
  pinMode(12, OUTPUT);//SPO2 Rate Red



  //OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();


  //LCD
  lcd.init();
  lcd.backlight();

  // Initialize sensor
  if (particleSensor.begin(Wire, I2C_SPEED_FAST) == false) //Use default I2C port, 400kHz speed
  {
    lcd.println("MAX30105 not foundCheck ");
    while (1);
  }

  lcd.print("Place finger");
  lcd.setCursor(0, 1);
  lcd.print("on Sensor");
  delay(3000);
  lcd.clear();
  //The LEDs are very low power and won't affect the temp reading much but
  //you may want to turn off the LEDs to avoid any local heating
  particleSensor.setup(); //Configure sensor. Turn on LEDs
  //particleSensor.setup(); //Configure sensor. Use 25mA for LED drive
  particleSensor.enableDIETEMPRDY(); //Enable the temp ready interrupt. This is required.
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

  //SPO2
  //pinMode(pulseLED, OUTPUT);
  pinMode(readLED, OUTPUT);

  byte ledBrightness = 60; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 2; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 4096; //Options: 2048, 4096, 8192, 16384

  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange);

}


void loop()
{

  //SPO2 & Heart Rate
  bufferLength = 100; //buffer length of 100 stores 4 seconds of samples running at 25sps

  //read the first 100 samples, and determine the signal range
  for (byte i = 0 ; i < bufferLength ; i++)
  {
    while (particleSensor.available() == false) //do we have new data?
      particleSensor.check(); //Check the sensor for new data

    redBuffer[i] = particleSensor.getRed();
    irBuffer[i] = particleSensor.getIR();
    particleSensor.nextSample(); //We're finished with this sample so move to next sample

  }

  //calculate heart rate and SpO2 after first 100 samples (first 4 seconds of samples)
  maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

  //Continuously taking samples from MAX30102.  Heart rate and SpO2 are calculated every 1 second
  while (1)
  {
    //dumping the first 25 sets of samples in the memory and shift the last 75 sets of samples to the top
    for (byte i = 25; i < 100; i++)
    {
      redBuffer[i - 25] = redBuffer[i];
      irBuffer[i - 25] = irBuffer[i];
    }

    //take 25 sets of samples before calculating the heart rate.
    for (byte i = 75; i < 100; i++)
    {
      while (particleSensor.available() == false) //do we have new data?
        particleSensor.check(); //Check the sensor for new data

      digitalWrite(readLED, !digitalRead(readLED)); //Blink onboard LED with every data read

      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample

      //temp
      float temperatureF = particleSensor.readTemperatureF();

      if (validSPO2 == 1) {
        lcd_oxy = spo2;
      }

      if (validHeartRate == 1) {
        lcd_bpm = heartRate;
      }

      lcd.clear();

      lcd.setCursor(0, 0);
      lcd.print("TEMP=");
      lcd.setCursor(6, 0);
      lcd.print(temperatureF, 1);
      lcd.setCursor(11, 0);
      lcd.print("F");

      lcd.setCursor(0, 2);
      lcd.print("SP02=");
      lcd.setCursor(6, 2);
      lcd.print(lcd_oxy, 1);
      lcd.setCursor(18, 2);
      lcd.print(validSPO2);

      lcd.setCursor(0, 1);
      lcd.print("BPM =");
      lcd.setCursor(6, 1);
      lcd.print(lcd_bpm);
      lcd.setCursor(18, 1);
      lcd.print(validHeartRate);

      long irValue = particleSensor.getIR();
      if (irValue < 50000) {
        lcd.setCursor(5, 3);
        lcd.println("No Finger");
      }

    }

    //After gathering 25 new samples recalculate HR and SP02
    maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);

    if (validSPO2 == 1) {
      my_oxy.data = spo2;
    }

    if (validHeartRate == 1) {
      my_heart.data = heartRate;
    }

    if (millis() > publisher_timer_oxy) {
      delay(10);

      pub_ardu_oxy.publish(&my_oxy);
      publisher_timer_oxy = millis() + 3000;

    }

    if (millis() > publisher_timer_heart) {
      delay(10);
      pub_ardu_heart.publish(&my_heart);
      publisher_timer_heart = millis() + 5000;
    }

    float temperatureF = particleSensor.readTemperatureF();
    if (millis() > publisher_timer_temp) {
      delay(10);
      my_temp.data = temperatureF;
      pub_ardu_temp.publish(&my_temp);
      publisher_timer_temp = millis() + 5000;
    }

    digitalWrite(12, LOW);
    digitalWrite(11, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);

    display.clearDisplay();
    display.setTextSize(1.8);
    display.setTextColor(WHITE);
    display.setCursor(10, 0);
    display.println("Health Monitor");

    noTone(5); // Buzzer

    nh.spinOnce();

  }
}
