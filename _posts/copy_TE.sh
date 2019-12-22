array=(31 30 31)

start_year=2019
start_month=$1
start_day=$2


for i in {0..6}
do 
  $month[$i]=8
  $day[$i]= expr ($start_day + 1)
done


