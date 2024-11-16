#!/bin/bash

./philo $1 800 200 200 $2 > a

echo -e "\n Check Eating \n"

for (( i=0; i<$1; i++ ))
do
	count=$(cat a | grep "$i is eating" | wc -l)
if (( $count == $2 ))
then
	ans=Correct
else
	ans=Incorrect
fi
echo philo $i $ans $count
done

echo -e "\n Check Thinking \n"

for (( i=0; i<$1; i++ ))
do
	count=$(cat a | grep "$i is thinking" | wc -l)
if (( $count == $2 ))
then
	ans=Correct
else
	ans=Incorrect
fi
echo philo $i $ans $count
done

echo -e "\n Check Sleeping \n"

for (( i=0; i<$1; i++ ))
do
	count=$(cat a | grep "$i is sleeping" | wc -l)
if (( $count == $2 ))
then
	ans=Correct
else
	ans=Incorrect
fi
echo philo $i $ans $count
done
rm a
