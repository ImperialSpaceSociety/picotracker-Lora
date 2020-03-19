# Created by Medad Rufus Newman on 18/03/2020


import time
import ttn # library contient les modules de ttn pour faire la connection **

app_id = "icss_lora_tracker" # identifiant de l’application **
access_key = "jCAIrrrJhQO4UwJtYJVNhxzwkAobQLWkNGUvBS7eung" # la cle d’entree de l’application

def uplink_callback(msg, client): # fonction qui fait l’affiche de message **
    print("Received uplink from ", msg.dev_id)
    print(msg)
    print("###################################")
    print(msg.payload_fields.message)
    sms=str(msg.payload_fields.message)
    print(sms)
    f=open("test.log","a+")
    f.write(sms+"\n")
    f.close()

handler = ttn.HandlerClient(app_id, access_key)

# using mqtt client
mqtt_client = handler.data()
mqtt_client.set_uplink_callback(uplink_callback)
mqtt_client.connect()
time.sleep(700) # you can set the time as you like here 700 s **
mqtt_client.close()
print("ENDED")