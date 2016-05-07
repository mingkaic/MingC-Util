MIN=10
NTESTS=50
COUNTER=0
while [  $COUNTER -lt $NTESTS ]; do
let ROWS=$MIN+$[RANDOM%40]
python datagen.py $ROWS 1
let COUNTER=COUNTER+1 
done