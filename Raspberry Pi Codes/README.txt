These are the instructions for the Raspberry Pi side of this project

There are three python files here

wait.py
This file is just a file to run a delay function for 5 seconds. For the code to run properly on startup
the boot files need to be run first properly. Just so that the main code does not start before the boot files,
a delay is added

EE629.py
This file contains the main code of collecting data and pushing it to the Google Sheet

Master_Control.py
This file is started at boot in order to turn ON/OFF the program, this is just extra control for a headless
setup of the Pi.

Log.log file is there to record the output of the codes above, since the terminal won't be accessed at all. 
These codes are going to run in the background.

launcher.sh is a shell file that runs the scripts at boot
________________________________________________________________________________________________________________________

MQTT DASH - Android App

I have used the MQTT Dash Android App in my project to control turning the program ON/OFF
You can download the app at
https://play.google.com/store/apps/details?id=net.routix.mqttdash&hl=en_US

(I don't know if there is an Apple app for the same)

In the app, configure two switches and one text box
Publishing topic for switch 1: RemoteControl
Publishing topic for switch 2: MasterControl
Subscribing topic for text box: ProgStatus

While setting up, the app will ask for MQTT credentials, server IP address and port number

_________________________________________________________________________________________________________________________
In order to setup launching these files at boot, first put them all in the directory /home/pi/EE629
(You can choose your own directory also but then make sure you make the directory changes in all the codes,
the launch file and py files have directory paths in them)

then open the terminal and run the following commands
NOTE: PLEASE TYPE IN THE NEXT COMMANDS CAREFULLY, YOU ARE GOING TO CHANGE BOOT FILES NOW
$ cd /etc/xdg/lxsessions/LXDE/
$ sudo nano autostart

Add the following line to the bottom of the code

@sh /home/pi/EE629/launcher.sh

Press CTRL+X, it'll prompt you to save the file, press Y and then while overwriting name, press Enter

(if you had changed directory before instead of /home/pi/EE629, make sure you change the directory in the autostart file also)

To make sure you've done everything properly, start the terminal and type in command

$sh /home/pi/EE629/launcher.sh

If the progress takes some time, don't worry, there's a delay file running
Soon, the code will start and on your app, you will see Welcome on the text box.
The second switch is to turn on/off the program and the first switch is to toggle on/off sensing