

line = "B5 62 06 11 02 00 08 01 22 92 B5 62 06 09 0D 00 00 00 00 00 FF FF 00 00 00 00 00 00 07 21 AF"
n = 3
result = ",".join(["0x"+line[i:i+n] for i in range(0, len(line), n)])
print(result)