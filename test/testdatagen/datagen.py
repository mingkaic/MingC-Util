import sys
import random
import string
import uuid
import os
from datetime import datetime

def getfilename(directory):
	return directory + str(uuid.uuid4()) + ".txt"

def id_generator(size, \
				chars=string.ascii_lowercase + \
				string.ascii_uppercase + \
				string.digits):
    return ''.join(random.choice(chars) for _ in range(size))

directory = '../tests/'

# seed by time
random.seed(datetime.now())

# define default constants
DEFAULT_NUM_LIMIT = 20000
DEFAULT_STR_LIMIT = 20
argc = len(sys.argv)
row = 20
col = 1

types = ['number', 'string']
type = 'number'

# read from arguments
if argc > 1 and sys.argv[1].isdigit():
	row = int(sys.argv[1])
if argc > 2 and sys.argv[2].isdigit():
	col = int(sys.argv[2])
if argc > 3:
	type = sys.argv[3]
	type = type.lower()
	if not type in types or \
		type == 'int' or \
		type == 'float' or \
		type == 'double':
		type = 'number'

# make output directory if not available
directory += type + '/'
if not os.path.exists(directory):
    os.makedirs(directory)

result = range(row)

def numberGenerate(col, row):
	min = col
	if col > argc-4 and argc > 4:
		min = argc-4

	# define a limit for each value 
	# of each column for any given row
	limits = range(min)

	for i in limits:
		if i+2 > argc:
			limits[i] = int(sys.argv[i+2])
		else:
			limits[i] = DEFAULT_NUM_LIMIT

	for j in range(row):
		result[j] = [random.random()*limits[i] for i in range(min)]

def stringGenerate(col, row):
	min = col
	if col > argc-4 and argc > 4:
		min = argc-4

	# define a limit for each value 
	# of each column for any given row
	limits = range(min)

	for i in limits:
		if i+2 > argc:
			limits[i] = int(sys.argv[i+2])
		else:
			limits[i] = DEFAULT_STR_LIMIT

	for j in range(row):
		result[j] = [id_generator(limits[i]) for i in range(min)]

options = {'number': numberGenerate, \
			'string': stringGenerate}

options[type](col, row)

filename = getfilename(directory)
target = open(filename, 'w')
for j in range(row):
	target.write(str(result[j]).strip('[]'))
	if j != row-1:
		target.write('\n')