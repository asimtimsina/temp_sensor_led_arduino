#include"TFT_eSPI.h"
#include <Wire.h>
#include"LIS3DHTR.h"
#include "AHT20.h"

LIS3DHTR<TwoWire> lis;

bool last_pressed_A = HIGH;
bool last_pressed_B = HIGH;
bool last_pressed_C = HIGH;
bool last_pressed = HIGH;

int delay_time = 500;
unsigned int last_pressed_time_A = 0;
unsigned int last_pressed_time_B = 0;
unsigned int last_pressed_time_C = 0;
unsigned int debounceDelay = 2000;

void play_buzzer();
void reset_display();
int current_tft_pointer = 10;


void read_temp_hum();
void read_acc();
void read_light();


TFT_eSPI tft;
AHT20 AHT;

int curr_A = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(WIO_BUZZER, OUTPUT);

  AHT.begin();

  lis.begin(Wire1);
  lis.setOutputDataRate(LIS3DHTR_DATARATE_25HZ); // Setting output data rage to 25Hz, can be set up tp 5kHz
  lis.setFullScaleRange(LIS3DHTR_RANGE_2G); // Setting scale range to 2g, select from 2,4,8,16g

  pinMode(WIO_LIGHT, INPUT);

  tft.begin();
  tft.setRotation(3);
  tft.setCursor(0,10);
  tft.fillScreen(TFT_GREEN);
  tft.setTextColor(TFT_BLACK);          //sets the text colour to black
  tft.setTextSize(2);
  //  Serial.println("1111");
}

void loop() {
  // put your main code here, to run repeatedly:


  if (digitalRead(WIO_KEY_A) == HIGH) {
    last_pressed_time_A = millis();
    last_pressed_A = HIGH;
  }
  if (digitalRead(WIO_KEY_B) == HIGH) {
    last_pressed_time_B = millis();
    last_pressed_B = HIGH;
  }
  if (digitalRead(WIO_KEY_C) == HIGH) {
    last_pressed_time_C = millis();
    last_pressed_C = HIGH;
  }


  /////////////////////////////////////////////////////
  if ( current_tft_pointer >= 225) {
    reset_display();
  }

  //////////////////////////////

  //  Serial.println(last_pressed_A);
  if ((digitalRead(WIO_KEY_A) == LOW) &&  (last_pressed_A)) {
    if ( millis() - last_pressed_time_A > debounceDelay) {
      play_buzzer();
      last_pressed_A = LOW;
      if (curr_A % 3 == 0) { // temp and humidity
        read_temp_hum();
        curr_A++;
      }// if temp
      else if (curr_A % 3 == 1) { // accelerometer values
        read_acc();
        curr_A++;
      } //if accelerometer
      else if (curr_A % 3 == 2) { //light sensor
        read_light();
        curr_A++;
      } // if light sensor

    } // debounce
  }// if A

  ///////////////////////////////////////////

  if ((digitalRead(WIO_KEY_B) == LOW) &&  (last_pressed_B)) {
    if ( millis() - last_pressed_time_B > debounceDelay) {
      play_buzzer();
      last_pressed_B = LOW;
      int curr_B;
      if (curr_A > 0) {
        curr_B = curr_A - 1;
      }
      else {
        curr_B = curr_A;
      }

      if (curr_B % 3 == 0) { // temp and humidity
        read_temp_hum();
      }// if temp
      else if (curr_B % 3 == 1) { // accelerometer values
        read_acc();
      } //if accelerometer
      else if (curr_B % 3 == 2) { //light sensor
        read_light();
      } // if light sensor
    }// debounce
  }// if B

  if ((digitalRead(WIO_KEY_C) == LOW) &&  (last_pressed_C)) {
    if ( millis() - last_pressed_time_C > debounceDelay) {
      play_buzzer();
      last_pressed_C = LOW;
      reset_display();
      curr_A = 0;
    } // debounce
  }// if C


  ////////////////


}

///////////////////////////////////////////////////////////////////////////////////////////////////

void play_buzzer() {
  analogWrite(WIO_BUZZER, 128);
  delay(100);
  analogWrite(WIO_BUZZER, 0);
}

void reset_display() {
  tft.setCursor(0,10);
  tft.fillScreen(TFT_GREEN);
  current_tft_pointer = 18;

}

//////////////////////////////////////////

void read_temp_hum() {
  float humi, temp;
  //  Serial.println("\t1");
  int data = AHT.getSensor(&humi, &temp);
  if (data) {
    Serial.println("Temp: " + String(temp) + ",\t Hum: " + String(humi * 100) + "%") ;

    tft.println("Temp: " + String(temp) + ",\t Hum: " + String(humi * 100) + "%");
    current_tft_pointer += 18;
  }
}


void read_acc() {
  float x_values, y_values, z_values;
  x_values = lis.getAccelerationX();
  y_values = lis.getAccelerationY();
  z_values = lis.getAccelerationZ();

  Serial.println("X:" + String(x_values) + ",Y:" + String(y_values) + ",Z:" + String(z_values));
  tft.println("X:" + String(x_values) + ", Y:" + String(y_values) + ", Z:" + String(z_values));
  current_tft_pointer += 18;
}


void read_light() {
  int ldr_value = analogRead(WIO_LIGHT);
  Serial.println("Light Value: " + String(ldr_value));
  tft.println("Light Value: " + String(ldr_value));
  current_tft_pointer += 18;
}
