import struct
import time
from datetime import datetime


epoch_unix = 1577840461


def convert_datatime_to_special_epoch_min(ts:datetime):
    return int((ts.timestamp() - epoch_unix)/60)


def gen_instruction(older, newer):
    print("older",older)
    print("newer",newer)
    newer = struct.pack('<I', newer)
    older = struct.pack('<I', older)


    return newer.hex()+older.hex()

def convert_special_epoch_min_to_datetime(ts_min:int)->str:
    unix = ts_min*60+epoch_unix

    return datetime.utcfromtimestamp(unix).strftime('%Y-%m-%d %H:%M:%S')

if __name__ == "__main__":
    date_time_str = '2020-11-26 19:30:57.084'
    date_time_older = datetime.strptime(date_time_str, '%Y-%m-%d %H:%M:%S.%f')

    date_time_str = '2020-11-26 19:42:03.972'
    date_time_newer = datetime.strptime(date_time_str, '%Y-%m-%d %H:%M:%S.%f')


    print(gen_instruction(convert_datatime_to_special_epoch_min(date_time_older),
                          convert_datatime_to_special_epoch_min(date_time_newer)))
