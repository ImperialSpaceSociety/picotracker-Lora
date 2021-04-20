
import json
import re
from pathlib import Path




def read_file(filename):
    f = open(filename, 'r')
    return f.read()



def special_replace(raw_str,the_string):
    return raw_str.replace("{}:".format(the_string),'"{}":'.format(the_string))

def process_str(string):
    raw_str = string.replace("MSG","").replace("(","{").replace(")","}").replace("=",":").replace("'",'"')
    things_to_replace = ["app_id","dev_id","hardware_serial","counter","payload_raw","payload_fields",
                         "metadata","frequency","modulation","data_rate","airtime","coding_rate",
                        "gtw_id","gtw_trusted","channel","rssi","snr","rf_chain","latitude","longitude",
                         "location_source","analog_in_3","barometric_pressure_0","digital_out_4","gps_2",
                         "temperature_1","altitude","is_retry","antenna"]

    for i in things_to_replace:

        raw_str = raw_str.replace("{}".format(i),'"{}"'.format(i))

    raw_str = raw_str.replace("{time",'{"time"')
    raw_str = raw_str.replace("True",'true')
    raw_str = raw_str.replace("time:",'"time":')
    raw_str = raw_str.replace("fine_timestamp:",'"fine_timestamp":')
    raw_str = raw_str.replace("fine_timestamp_encrypted:",'"fine_timestamp_encrypted":')
    raw_str = raw_str.replace("timestamp:",'"timestamp":')
    raw_str = special_replace(raw_str,"port")
    raw_str = special_replace(raw_str,"gateways")

    return raw_str


def parse_jackson_log_format(data_str)->list:    
    line_selector = r"(MSG\(app_id='icss_lora_tracker', dev_id='icspace.*)"
    strings = re.findall(line_selector,data_str)
    data_list = []
    for i in strings:
        data = i
        data = process_str(data)
        if "relative_humidity_2" in data:
            continue
        if "analog_in_1" in data:
            continue
        #print(data)
        d = json.loads(data)
        data_list.append(d)
    return data_list


# In[81]:


filename = "ttn-logs/raw_log.txt"
str_data = read_file(filename)
jackson_processed = parse_jackson_log_format(str_data)

# In[ ]:




