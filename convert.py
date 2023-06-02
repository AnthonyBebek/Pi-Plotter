import coms
import time

yaxis = []
xaxis = []
pen = []
complete = 0
count = 0
start_time = time.time()
with open('output.txt', 'r') as f:
    total_lines = sum(1 for _ in f)
    f.seek(0)
    for line in f:
        count += 1
        tmp = line.strip().split(" ")
        pen.append(tmp[0].replace("G", ""))
        xaxis.append(tmp[1].replace("X", ""))
        yaxis.append(tmp[2].replace("Y", ""))
        coms.move(tmp[1].replace("X", ""),tmp[2].replace("Y", ""))
        elapsed = time.time() - start_time
        progress = count / total_lines * 100
        total = elapsed / progress * 100
        remaining = total - elapsed
        print("Progress " + str(round(progress, 2)) + "%")
        print("Elapsed Time:" + str(round(elapsed, 2)) + " seconds")
        print("Total Time:" + str(round(total, 2)) + " seconds")
        print("Remaining Time:" + str(round(remaining, 2)) + " seconds")
        
