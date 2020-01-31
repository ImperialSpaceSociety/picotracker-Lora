

line = "49 6e 74 65 72 6e 73 68 69 70 20 77 61 6e 74 65 64 21 20 48 69 72 65 20 6d 65 21 20 6d 72 6e 33 33 31 37 40 69 63 2e 61 63 2e 75 6b"
n = 3
result = ",".join(["0x"+line[i:i+n] for i in range(0, len(line), n)])
print(result)