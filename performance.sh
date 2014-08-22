#!/bin/sh

# Time and run programs using arguments.
START=$(date +%s)
echo "$1\n$2" | ./wl > out.txt
END=$(date +%s)
DIFF=$(( $END - $START ))

START=$(date +%s)
echo "$1\n$2" | ./wl_ref > refOut.txt
END=$(date +%s)
DIFF2=$(( $END - $START ))

echo "+--------------------------+"
echo "+-- Time Comparison(Sec) --+"
echo "+--------------------------+"
echo "+-- Ref : $DIFF2"
echo "+-- Mine: $DIFF"

diff out.txt refOut.txt
res=$?
echo "============================"

if [ $res -eq 0 ]
	then
		echo "_________________ Tests Successful!"
   	else
    	echo "_________________ Tests Failed!"
   	fi