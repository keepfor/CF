in=$(ls in*)
obj="prog"
output="out"
echo "all in"
echo $in
echo 
for i in $in;
do 
  echo "input $i"
  cat $i
  echo "output"
  ./${obj} < $i 2>&1 | tee ${output}
  echo 
done
