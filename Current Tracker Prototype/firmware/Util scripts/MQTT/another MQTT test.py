# Created by Medad Rufus Newman on 18/03/2020


# https://www.thethingsnetwork.org/forum/t/a-python-program-to-listen-to-your-devices-with-mqtt/9036/6
# Get data from MQTT server
# Run this with python 3, install paho.mqtt prior to use

import paho.mqtt.client as mqtt
import json
import base64
import logging

APPID  = "icss_lora_tracker"
PSW    = "ttn-account-v2.jCAIrrrJhQO4UwJtYJVNhxzwkAobQLWkNGUvBS7eung"

#Call back functions

# gives connection message
def on_connect(self, client, userdata, flags, rc):
    logging.debug("MQTT connected: result code=%i", rc)
    if rc == 0:
        res = client.subscribe("+/devices/+/up")
        if res[0] != mqtt.MQTT_ERR_SUCCESS:
            raise RuntimeError("the client is not connected")

    if rc == 1:
        raise RuntimeError("connection failed: incorrect protocol version")
    if rc == 2:
        raise RuntimeError("connection failed: invalid client identifier")
    if rc == 3:
        raise RuntimeError("connection failed: server unavailable")
    if rc == 4:
        raise RuntimeError("connection failed: bad app_id or access_key")
    if rc == 5:
        raise RuntimeError("connection failed: not authorised")
    # 6 - 255: currently unused
# gives message from device
def on_message(mqttc,obj,msg):
    try:
        #print(msg.payload)
        x = json.loads(msg.payload.decode('utf-8'))
        device = x["dev_id"]
        counter = x["counter"]
        payload_raw = x["payload_raw"]
        payload_fields = x["payload_fields"]
        datetime = x["metadata"]["time"]
        gateways = x["metadata"]["gateways"]
        # print for every gateway that has received the message and extract RSSI
        for gw in gateways:
            gateway_id = gw["gtw_id"]
            rssi = gw["rssi"]
            print(datetime + ", " + device + ", " + str(counter) + ", "+ gateway_id + ", "+ str(rssi) + ", " + str(payload_fields))
    except Exception as e:
        print(e)
        pass

def on_publish(mosq, obj, mid):
    print("mid: " + str(mid))

def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_log(self, client, userdata, level, buf):
    """
    Log all MQTT protocol events, and the exceptions in callbacks
    that have been caught by Paho.
    """
    logging_level = mqtt.LOGGING_LEVEL[level]
    logging.log(logging_level, buf)

mqttc= mqtt.Client()
# Assign event callbacks
mqttc.on_connect=on_connect
mqttc.on_message=on_message

mqttc.username_pw_set(APPID, PSW)
mqttc.connect("eu.thethings.network",1883,60)

# and listen to server
run = True
while run:
    mqttc.loop()