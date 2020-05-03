#!/usr/bin/env python3

import paho.mqtt.client as mqtt
import os
import subprocess
import signal

broker_address="192.168.1.166"
usname = "Mr_Jay37"
password = "Abagauss"
topic = "ProgStatus"
topicp = "MasterControl"
client_ID = "PiM"
pid = 0
class PID:
    val = 0
    def __init__(self, val):
        self.val = val

client = mqtt.Client(client_ID)
client.username_pw_set(usname, password)
client.connect(broker_address)

procid = PID(0)

def on_message(client, obj, message):
    msg = str(message.payload.decode("utf-8"))
    if msg=="On":
        p = subprocess.Popen("python3 /home/pi/EE629/EE629.py > /home/pi/EE629/Log.log &", shell=True)
        procid.val = p.pid + 1
        print(procid.val)
        client.publish(topic, "Online")
    elif msg=="Off":
        pid = str(procid.val)
        os.system("sudo kill " + pid)
        client.publish(topic, "Offline")
        
client.subscribe(topicp, 0)
client.on_message = on_message
client.publish(topic, "Welcome")

try:
    while(True):
        client.loop_forever()
except KeyboardInterrupt:
        client.publish(topic, "Shut Down")
