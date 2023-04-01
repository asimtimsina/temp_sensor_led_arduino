# temp_sensor_led_arduino
 interfacing on LCD screen and sensors like temperature, humidity, accelerometer, and light sensor.


1. When the push button WIO_KEY_A is pressed, the current temperature and
humidity is displayed on the LCD screen (State 1). When push button WIO_KEY_A
is again pressed, the current accelerometer values (x, y, and z axes) are displayed
on the next line of the LCD screen (State 2). When the push button WIO_KEY_A is
again pressed, the current light sensor value is displayed on the next line of the
LCD screen (State 3). When the push button WIO_KEY_A is again pressed, the
current temperature and humidity is again read and is displayed on the next line of
the LCD screen (State 1), and it switches between the above states when the push
button WIO_KEY_A is pressed each time
2. When the push button WIO_KEY_B is pressed, the last read sensor’s value is
again read and is displayed on the next line of the LCD screen. This process is
repeated for each press of push button WIO_KEY_B and for each state
3. The LCD screen should be initialized as follows: background color should be
green, the display text color should be black, and the text size should be 2
4. When push button WIO_KEY_C is pressed, the LCD screen should be cleared and
set to the initial settings
Page 2 of 3
5. Each time when the push buttons WIO_KEY_A, WIO_KEY_B, or WIO_KEY_C is
pressed, generate a beep using the buzzer
6. The temperature and humidity should be displayed with two decimal places on the
LCD screen as Temp: <current temperature>C, Hum: <current
humidity>%
7. The accelerometer values (x, y, and z axes) should be displayed with two decimal
places on the LCD screen as X: <current x value>, Y: <current y
value>, Z: <current z value>
8. The light value should be displayed on the LCD screen as Light Value:
<current light value>
9. Write required software routine to handle switch debouncing and do not use any
delay loops or delay functions for handling switch bouncing.
