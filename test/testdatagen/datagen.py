import sys
import random
import uuid
import os
from datetime import datetime

def getfilename(directory):
	return directory + str(uuid.uuid4()) + ".txt"

directory = '../tests/'
if not os.path.exists(directory):
    os.makedirs(directory)

random.seed(datetime.now())

DEFAULT_LIMIT = 20000
argc = len(sys.argv)
row = 0
col = 0

if argc > 1 and sys.argv[1].isdigit():
	row = int(sys.argv[1])
if argc > 2 and sys.argv[2].isdigit():
	col = int(sys.argv[2])

min = col
if col > argc-3 and argc > 3:
	min = argc-3

limits = range(min)

for i in limits:
	if (1+i > argc):
		limits[i] = int(sys.argv[1+i])
	else:
		limits[i] = DEFAULT_LIMIT

filename = getfilename(directory)

target = open(filename, 'w')

for j in range(row):
	num_row = [random.random()*limits[i] for i in range(min)]
	target.write(str(num_row).strip('[]')+'\n')