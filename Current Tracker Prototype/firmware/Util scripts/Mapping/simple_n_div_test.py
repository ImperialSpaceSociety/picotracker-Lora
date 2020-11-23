def freq(i,j):
    return (2**(i)-1)*(2**(j)-1)


for i in range(7+1):
    for j in range(15+1):

        print(i,j,freq(i,j))
