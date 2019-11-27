

line = "3A48C7BC74CF4314408BEF211DF773C1"

n = 2
result = ",".join(["0x"+line[i:i+n] for i in range(0, len(line), n)])
print(result)