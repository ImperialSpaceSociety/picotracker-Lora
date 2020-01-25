

line = "B5 62 06 3B 30 00 02 06 00 00 60 90 40 01 00 00 00 00 00 00 00 00 00 00 00 00 02 00 00 00 2C 01 00 00 4F C1 03 00 87 02 00 00 FF 00 00 00 64 40 01 00 00 00 00 00 19 B8"
n = 3
result = ",".join(["0x"+line[i:i+n] for i in range(0, len(line), n)])
print(result)