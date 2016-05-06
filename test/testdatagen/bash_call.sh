LIMIT=20
COUNTER=0
while [  $COUNTER -lt $LIMIT ]; do
python datagen.py $[RANDOM%40] 1
let COUNTER=COUNTER+1 
done