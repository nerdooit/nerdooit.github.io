#arr_month=(8,9,10)
#arr_day=(31 30 31)

arr_day=(월 화 수 목 금 토 일)

start_year=2019
start_month=$1
start_day=$2
last_day=$3

for i in {0..6}
do 
  #8
  NEXT_MONTH[$i]=$start_month
  NEXT_DAY[$i]=$start_day
  
  if [ $start_day -gt $last_day ]; then
    start_month=`expr $start_month + 1`
    start_day=1
    #echo $start_month $start_day
  else

    if [ $start_day -lt 9 ]; then
      start_day=0`expr $start_day + 1`
    else
      start_day=`expr $start_day + 1`
    fi
  fi
  
  #echo $start_year-0${NEXT_MONTH[$i]}-${NEXT_DAY[$i]}-TE_190${NEXT_MONTH[$i]}${NEXT_DAY[$i]}.md
done

#2019-08-08-TE_190808_0811.md
FILE="$start_year-0${NEXT_MONTH[0]}-${NEXT_DAY[0]}-TE_190${NEXT_MONTH[0]}${NEXT_DAY[0]}_0${NEXT_MONTH[0]}${NEXT_DAY[6]}.md"
touch $FILE
chmod 777 $FILE

for j in {0..6}
do
  echo "## ${NEXT_MONTH[$j]}월 ${NEXT_DAY[$j]}일(${arr_day[$j]})" >> $FILE
  cat "$start_year-0${NEXT_MONTH[$j]}-${NEXT_DAY[$j]}-TE_190${NEXT_MONTH[$j]}${NEXT_DAY[$j]}.md" >> $FILE

  rm "$start_year-0${NEXT_MONTH[$j]}-${NEXT_DAY[$j]}-TE_190${NEXT_MONTH[$j]}${NEXT_DAY[$j]}.md"
done


