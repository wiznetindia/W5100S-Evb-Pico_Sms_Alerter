# W5100S-Evb-Pico_Sms_Alerter
A device that sends you a text when a flood is detected

![icc_may_thumbnail](https://user-images.githubusercontent.com/69140786/168349050-3b00e7e8-58f9-4b52-9c11-3676af53c712.PNG)


1.Introduction

While some areas are more prone to flooding than others, the establishment of flood warning systems near any major waterway or body of water provides critical information that can protect property and save lives.

If even small areas which are prone to flood or sensitive areas, it could be a small idea to get notified if there is a flood or excessive/set water flow.. If you go out, get a message from your alert device that you need to rush back to your area & save/protect that you wish for :-)

The goal of this project was to develop some form of a communication line between house and myself to notify me that something's wrong.

In order to maximize efficiency, I created this project with these points in mind:

1) Some sort of ultra-fast connection via SMS, and for its service to be free.

2) Once the excessive level reaches, the Arduino sketch should easily connect to the Internet with W5100S-Evb-Pico.

Product: Water sensor that can quickly notify through text if floods at home occurs by connecting to the internet via Wiznet's W5100S-Evb-Pico.

2.Hardware

Wiznet's W5100S-Evb-Pico.

W5100S-EVB-Pico is a microcontroller evaluation board based on the Raspberry Pi RP2040 and fully hardwired TCP/IP controller W5100S – and basically works the same as Raspberry Pi Pico board but with additional Ethernet via W5100S.

Raspberry Pi Pico Clone
Ethernet (W5100S Hardwired TCP/IP CHIP)
AWS IoT Core Qualified
Microsoft Azure CertifiedSensor
This water level sensor module has a series of parallel exposed traces to measure droplets/water volume in order to determine the water level. Very Easy to monitor water level as the output to analog signal is directly proportional to the water level. This output analog values can be directly read via ADC and can also be connected directly Arduino's analog input pins.

Working with Arduino IDE:

The W5100S-EVB-Pico has the same role as the Raspberry Pi Pico platform and includes W5100S, so the Ethernet function is basically included.

It is easy to use an Arduino IDE with W5100S-EVB-Pico.

The W5100S-EVB-Pico is a microcontroller evaluation board based on the Raspberry Pi RP2040 microcontroller chip and a full hardwired TCP/IP controller W5100S chip.

Please refer Arduino Raspberry Pi Pico/RP2040 Ethernet : W5100S-EVB-Pico to set your arduino ide environment to operate W5100S-Evb-Pico.

SMS

There are many ways to approach sending an SMS from an Arduino using the Internet. However, the easiest method is to split the job between Arduino and an online service like ThingSpeak which passes the SMS request to a second service Twilio. The latter integrates the Internet with the telephony infrastructure.
