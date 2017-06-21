import os

files = os.listdir('.')
for f in files:
    if '.log' in f:
        metric = []
        fid = open(f)
        print f
        for line in fid:
            if 'psnr' in line:
                metric.append(float(line.split()[5].split(':')[1]))
            else:
                metric.append(float((line.split()[-2].split(':')[1])))
        print sum(metric)/float(len(metric))
