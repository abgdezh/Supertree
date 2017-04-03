for ((i=0; i<10000; ++i));
do #echo $i;
python3 gentest.py 20 10;
./stupid < input.txt > output.txt;
./clever < input.txt > output1.txt;
diff output.txt output1.txt;
if [ $? -ne 0 ]; then break; fi;
done;
