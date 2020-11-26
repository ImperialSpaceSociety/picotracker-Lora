import struct




def gen_instruction(older, newer):
    newer = struct.pack('<I', newer)
    older = struct.pack('<I', older)


    return newer.hex()+older.hex()


if __name__ == "__main__":
    a = 475325
    b = 475125
    print(gen_instruction(b,a))