yaxis = []
xaxis = []
pen = []

with open('output.txt', 'r') as f:
    for line in f:
        tmp = line.strip().split(" ")
        pen.append(tmp[0].replace("G", ""))
        xaxis.append(tmp[1].replace("X", ""))
        yaxis.append(tmp[2].replace("Y", ""))

print(pen)
print(xaxis)
print(yaxis)
