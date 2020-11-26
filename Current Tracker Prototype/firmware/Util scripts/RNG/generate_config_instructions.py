import struct
import time
import datetime

time.time()


epoch_unix = 1577840461


def convert_datatime_to_special_epoch_min(ts:datetime.datetime):
    return int((ts.timestamp() - epoch_unix)/60)


def gen_instruction(older, newer):
    print("older",older)
    print("newer",newer)
    newer = struct.pack('<I', newer)
    older = struct.pack('<I', older)


    return newer.hex()+older.hex()


if __name__ == "__main__":

    date_time_str = '2020-11-26 11:45:27.243860'
    date_time_older = datetime.datetime.strptime(date_time_str, '%Y-%m-%d %H:%M:%S.%f')

    date_time_str = '2020-11-26 11:50:27.243860'
    date_time_newer = datetime.datetime.strptime(date_time_str, '%Y-%m-%d %H:%M:%S.%f')


    print(gen_instruction(convert_datatime_to_special_epoch_min(date_time_older),
                          convert_datatime_to_special_epoch_min(date_time_newer)))