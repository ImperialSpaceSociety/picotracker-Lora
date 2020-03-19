# Created by Medad Rufus Newman on 18/03/2020


import time
import ttn

app_id = "icss_lora_tracker"
#app_id = "70B3D57ED002824D"
access_key = "ttn-account-v2.jCAIrrrJhQO4UwJtYJVNhxzwkAobQLWkNGUvBS7eung"


def uplink_callback(msg, client):
  print("Received uplink from ", msg.dev_id)
  print(msg)

handler = ttn.HandlerClient(app_id, access_key)

# using mqtt client
mqtt_client = handler.data()
mqtt_client.set_uplink_callback(uplink_callback)
mqtt_client.connect()
time.sleep(60)
mqtt_client.close()



# using application manager client
app_client =  handler.application()
my_app = app_client.get()
print("+++++++++++++++++++++++++++++++++++++++++")

print(my_app)
print("+++++++++++++++++++++++++++++++++++++++++")
my_devices = app_client.devices()
print(my_devices)
print("+++++++++++++++++++++++++++++++++++++++++")
