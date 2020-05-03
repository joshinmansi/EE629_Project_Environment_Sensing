#!/usr/bin/env python

import paho.mqtt.client as mqtt
from time import sleep
import requests

broker_address="192.168.1.166"
usname = "Mr_Jay37"
password = "Abagauss"
topic = "Test"
topic1 = "Device1"
topic2 = "RemoteControl"
client_ID = "Pi"
URL = "https://script.google.com/macros/s/AKfycby4CAVolag6ZKC-6pEOL0wpCYAwNm-SilMFH2yqcutimJQdNNHc/exec?device1="
data = ''
machine = 0

client = mqtt.Client(client_ID)
client.username_pw_set(usname, password)
client.connect(broker_address)

def turn_machine_on():
    client.subscribe(topic1, 0)
    client.publish(topic, "On")
    print("Sensing On")

def turn_machine_off():
    client.publish(topic, "Off")
    client.unsubscribe(topic1)
    print("Sensing Off, Standby")

def collect_data(msg):
    data = str(msg)
    sendata = URL + data
    r = requests.get(sendata)
    if r.status_code != 200:
        print("Error:", r.status_code)
    print(data)
    client.publish(topic, "On")
    
def on_message(client, obj, message):
    msg = str(message.payload.decode("utf-8"))
    if message.topic==topic2:
        if msg=="On":
            turn_machine_on()
        elif msg=="Off":
            turn_machine_off()
    if message.topic==topic1:
        collect_data(msg)
        
client.subscribe(topic2, 0)
client.on_message = on_message
client.publish(topic, "Initialize")
print("Initialize")

try:
    while(True):
        client.loop_forever()
except KeyboardInterrupt:
        client.publish(topic, "Shut Down")
        print("Turning off system")
