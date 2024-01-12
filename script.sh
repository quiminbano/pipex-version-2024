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
					"./pipex 'infile2' 'cat' 'awk -F \";\" \"{print \$1}\"' 'outfile'" \
					"./pipex 'infile2' '\"l\"\"s\"' '\"l\"\"s\"\"\" \"\"\"\"\"-\"\"l\"\"a\"' 'outfile'" \
					"./pipex 'infile2' '\a\b\c' '\"l\"\"s\"\"\"\ \"\"\"\"\"-\"\"l\"\"a\"' 'outfile'" \
					"./pipex 'infile2' '\a\b\c\' '\"l\"\"s\"\"\"\ \"\"\"\"\"-\"\"l\"\"a\"' 'outfile'")

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
				"< infile2 cat | awk -F \";\" '{print \$1}' > outfile" \
				"< infile2 \"l\"\"s\" | \"l\"\"s\"\"\" \"\"\"\"\"-\"\"l\"\"a\" > outfile" \
				"< infile2 \a\b\c | \"l\"\"s\"\"\"\ \"\"\"\"\"-\"\"l\"\"a\" > outfile" \
				"< infile2 \a\b\c | \"l\"\"s\"\"\"\ \"\"\"\"\"-\"\"l\"\"a\" > outfile")

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
		rm -f outfile
	fi
	echo "";
	echo "Return value of zsh: " ${returnZsh} ". Return value of pipex: " ${returnPipex};
	echo "";
	echo "Testing leaks with valgrind: This will be stored in the in test${index}.txt";
	eval "valgrind --leak-check=full --show-reachable=yes --track-origins=yes --verbose --tool=memcheck --trace-children=yes ${pipexInstructions[$index]} 2> test${index}.txt";
	mv test${index}.txt testValgrind/
	sleep 3;
	((index++));
done
echo ""
echo ""
echo "TEST NUMBER 16 : ./pipex infile2 ls \"wc -l\" outfile when fork() fails";
<< EOF cat > mock_fork.c
#include <unistd.h>

pid_t	fork()
{
	return (-1);
}
EOF
cc -fPIC -shared mock_fork.c -o libmockfork.so
LD_PRELOAD=/pipex/libmockfork.so ./pipex infile2 ls "wc -l" outfile
echo ""
echo "Testing leaks with valgrind: This will be stored in the in test16.txt";
LD_PRELOAD=/pipex/libmockfork.so valgrind --leak-check=full --show-reachable=yes --track-origins=yes --verbose --tool=memcheck --trace-children=yes ./pipex infile2 ls "wc -l" outfile 2> test16.txt
mv test16.txt testValgrind/
cat outfile
sleep 3
echo ""
echo ""
echo "TEST NUMBER 17 : ./pipex infile2 ls \"wc -l\" outfile when pipe() fails";
<< EOF cat > mock_pipe.c
#include <unistd.h>

int	pipe(int fildes[2])
{
	fildes[0] = -1;
	fildes[1] = -1;
	return (-1);
}
EOF
cc -fPIC -shared mock_pipe.c -o libmockpipe.so
LD_PRELOAD=/pipex/libmockpipe.so ./pipex infile2 ls "wc -l" outfile
echo ""
echo "Testing leaks with valgrind: This will be stored in the in test17.txt";
LD_PRELOAD=/pipex/libmockpipe.so valgrind --leak-check=full --show-reachable=yes --track-origins=yes --verbose --tool=memcheck --trace-children=yes ./pipex infile2 ls "wc -l" outfile 2> test17.txt
mv test17.txt testValgrind/
cat outfile
sleep 3