#!/bin/bash -e
EX=1
MARK="---"
# empty string evaluates to false:
RUNTEST=y

# check whether bash supports arrays.
test[0]='test' || (echo 'Failure: arrays not supported in this version of
bash.' && exit 2)

CMDS=(
	'./ex17 dbtst.dat l' 
	'./ex17 dbtst.dat c' 
	'./ex17 dbtst.dat l'
	'./ex17 dbtst.dat s 1 me me@me'
	'./ex17 dbtst.dat s 2 myself myself@contact'
	'./ex17 dbtst.dat s 3 I I@contact'
	'./ex17 dbtst.dat s 4 others alien@contct'
	'./ex17 dbtst.dat l'
	'./ex17 dbtst.dat d 5'
	'./ex17 dbtst.dat l'
	'./ex17 dbtst.dat g 1'
	)
echo ex.sh

if [ $RUNTEST ]; then
	for CMD in "${CMDS[@]}"
	do
		echo $MARK $EX $MARK
		$CMD
		((EX+=1))
	done

fi
# option -e stops execution in case of error 
echo Success
