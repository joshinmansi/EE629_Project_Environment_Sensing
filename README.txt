Spring 2020 - EE629 Final Project
Stevens Institute of Technology
Sanket Jain, Mansi Joshi, Neel Haria

Aim of the project is to collect sensor data from Nodes to local servers and from the local server to the cloud server.

Reason for this three part architecture is to allow scalability. The nodes and local servers are fairly easy to install physically.
The local servers can also record regional data and storing backup before sending to the cloud server.

Following are the codes involved:

1] NodeMCU ESP8266 + DHT-11 Temperature Sensor (client)

NodeMCU is a microcontoller with WiFi capability. It collects temperature and humidity data using DHT-11 sensor and sends this data to the local server using MQTT

2] Raspberry Pi	(server)

Raspberry Pi runs an MQTT server, collects data from nodes and pushes the data to a Google Sheet. There is also some control mechanism involved using an android application to turn the system ON/OFF

3] Google Cloud Platform (Cloud)

The data is pushed to an HTTPS URL, which is the URL for a web app used to retrieve data from the local servers and store them in a Google Sheet.

App used in this project is MQTT Dash, you can download it here
https://play.google.com/store/apps/details?id=net.routix.mqttdash&hl=en_US

References:

MQTT Tutorial: https://www.instructables.com/id/How-to-Use-MQTT-With-the-Raspberry-Pi-and-ESP8266/

Web API for HTTP: https://www.youtube.com/watch?v=fVBqUeksR1I
This code is for an Arduino using an Ethernet shield and HTTP (unsecured). Some changes were made to make it into Raspberry Pi sending data using HTTPS

