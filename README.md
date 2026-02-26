# HamClockCYD
## Clock For Amateur Radio Operators using a CYD (Cheap Yellow Display)
Ham Clock is intended for use in a Ham shack. It is implemented using inexpensive components:
  * CYD (Cheap Yellow Display). This component includes a 320x240 color LCD display, and a resistive touch screen.
  * An I2C BME280 Temperature/Humidity Sensor
  * An I2C DS3231 Realtime clock

The software is Arduino, using lvgl graphics library to implement the UI. The UI implementation was aided through the use of the excellent “EEZ Studio” software. The UI is implemented as a set of tabs:
  1.	Clock – This tab is the default display and includes
  2.	Weather
  3.	Solar Conditions
  4.	Tools – This tab controls various options and settings 
