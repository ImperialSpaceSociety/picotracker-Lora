import struct
import time
from datetime import datetime


epoch_unix = 1577840461


def convert_datatime_to_special_epoch_min(ts:datetime):
    return int((ts.timestamp() - epoch_unix)/60)


def gen_instruction(older, newer):

    if older>= newer:
        raise ValueError("Older is equal or greater than newer")
    newer = struct.pack('<I', newer)
    older = struct.pack('<I', older)


    return newer.hex()+older.hex()

def unix_to_datetime_str(unix):
    return datetime.utcfromtimestamp(unix).strftime('%Y-%m-%d %H:%M:%S')


def convert_special_epoch_min_to_datetime(ts_min:int)->str:
    unix = ts_min*60+epoch_unix

    return datetime.utcfromtimestamp(unix).strftime('%Y-%m-%d %H:%M:%S')

if __name__ == "__main__":
    date_time_str = '2020-11-26 23:53:01'
    date_time_older = datetime.strptime(date_time_str, '%Y-%m-%d %H:%M:%S')

    date_time_str = '2020-11-26 23:56:01'
    date_time_newer = datetime.strptime(date_time_str, '%Y-%m-%d %H:%M:%S')


    print(gen_instruction(convert_datatime_to_special_epoch_min(date_time_older),
                          convert_datatime_to_special_epoch_min(date_time_newer)))

    print(convert_special_epoch_min_to_datetime(476586))
    print(convert_special_epoch_min_to_datetime(476584))
    print(convert_special_epoch_min_to_datetime(476582))
    print(convert_special_epoch_min_to_datetime(476580))
    print(convert_special_epoch_min_to_datetime(476578))
    print(convert_special_epoch_min_to_datetime(476576))
    print(convert_special_epoch_min_to_datetime(476574))
    print(convert_special_epoch_min_to_datetime(476572))
    print(convert_special_epoch_min_to_datetime(476570))
    print(convert_special_epoch_min_to_datetime(476568))
