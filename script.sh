#!/bin/zsh

pipexInstructions=("./pipex '' '' '' ''" \
					"./pipex '' 'cat' 'cat' ''" \
					"./pipex 'infile' 'cat' 'cat' ''" \
					"./pipex '' 'cat' 'cat' 'outfile'" \
					"./pipex 'infile' '' '' 'outfile'" \
					"./pipex 'infile' 'cat' 'cat' 'outfile'" \
					"./pipex 'infile' './testsegv' './testsegv' 'outfile'" \
					"./pipex 'infile' './myfolder' 'cat' 'outfile'" \
					"./pipex 'infile' 'cat' './myfolder' 'outfile'" \
					"./pipex 'infile' '/bin/hello' '/bin/hello' 'outfile'" \
					"./pipex 'testsegv.c' 'cat' 'grep str\ =\ NULL' 'outfile'" \
					"./pipex 'infile2' 'cat' 'awk -F \";\" \"{print \$1}\"' 'outfile'")

zshInstructions=("< '' '' | '' > ''" \
				"< '' cat | cat > ''" \
				"< infile cat | cat > ''" \
				"< '' cat | cat > outfile" \
				"< infile '' | '' > outfile" \
				"< infile cat | cat > outfile" \
				"< infile ./testsegv | ./testsegv > outfile" \
				"< infile ./myfolder | cat > outfile" \
				"< infile cat | ./myfolder > outfile" \
				"< infile /bin/hello | /bin/hello > outfile" \
				"< testsegv.c cat | grep str\ =\ NULL > outfile" \
				"< infile2 cat | awk -F \";\" '{print \$1}' > outfile")

echo "COMPILING THE PROGRAM"
make
sleep 2
echo "Creating files for testing."
mkdir myfolder
if [ ! -d "testValgrind" ]; then
	mkdir testValgrind;
fi
echo "THIS IS AN INFILE" > infile
echo -e "hello;world\nhola;mundo" > infile2
<< EOF cat > testsegv.c
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	*str;
	size_t	size;

	str = NULL;
	size = strlen(str);
	printf("%zu\n", size);
	return (0);
}
EOF

cc -Wall -Wextra -Werror testsegv.c -o testsegv

returnPipex=0
returnZsh=0
index=1
sizeArray=${#pipexInstructions[@]}
while [ $index -le $sizeArray ]; do
	echo "";
	echo "";
	echo "TEST NUMBER " ${index} ": " ${pipexInstructions[$index]} " and " ${zshInstructions[$index]};
	echo "ZSH:";
	eval "${zshInstructions[$index]}";
	returnZsh=$?;
	if [ -f "outfile" ]; then
		echo ""
		echo "Content of outfile from zsh:"
		cat outfile
		rm -f outfile;
	fi
	echo "";
	echo "PIPEX:";
	eval "${pipexInstructions[$index]}";
	returnPipex=$?
	if [ -f "outfile" ]; then
		echo ""
		echo "Content of outfile from pipex:"
		cat outfile
		rm -f outfile;
	fi
	echo "";
	echo "Return value of zsh: " ${returnZsh} ". Return value of pipex: " ${returnPipex};
	sleep 3;
	echo "";
	echo "Testing leaks with valgrind: This will be stored in the in test${index}.txt";
	eval "valgrind --leak-check=full --show-reachable=yes --track-origins=yes --verbose --tool=memcheck ${pipexInstructions[$index]} 2> test${index}.txt";
	mv test${index}.txt testValgrind/
	((index++));
done

while true
do
	sleep 1;
done