#!/bin/zsh

pipexInstructions=("./pipex \"\" \"\" \"\" \"\"" \
					"./pipex \"\" \"cat\" \"cat\" \"\"" \
					"./pipex \"infile\" \"cat\" \"cat\" \"\"" \
					"./pipex \"\" \"cat\" \"cat\" \"\"outfile" \
					"./pipex \"infile\" \"\" \"\" \"outfile\"" \
					"./pipex \"infile\" \"cat\" \"cat\" \"outfile\"" \
					"./pipex \"infile\" \"./testsegv\" \"./testsegv\" \"outfile\"" \
					"./pipex \"infile\" \"./testbus\" \"./testbus\" \"outfile\"" \
					"./pipex \"infile\" \"./myfolder\" \"cat\" \"outfile\"" \
					"./pipex \"infile\" \"cat\" \"./myfolder\" \"outfile\"" \
					"./pipex \"infile\" \"/bin/hello\" \"/bin/hello\" \"outfile\"")

zshInstructions=("< '' '' | '' > ''" \
				"< '' cat | cat > ''" \
				"< infile cat | cat > ''" \
				"< '' cat | cat > outfile" \
				"< infile '' | '' > outfile" \
				"< infile cat | cat > outfile" \
				"< infile ./testsegv | ./testsegv > outfile" \
				"< infile ./testbus | ./testbus > outfile" \
				"< infile ./myfolder | cat > outfile" \
				"< infile cat | ./myfolder > outfile" \
				"< infile /bin/hello | /bin/hello > outfile")

echo "COMPILING THE PROGRAM"
make
sleep 2
echo "Creating files for testing."
mkdir myfolder
if [ ! -d "testValgrind" ]; then
	mkdir testValgrind;
fi
echo "THIS IS AN INFILE" > infile
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
<< EOF cat > testbus.c
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char	*return_string(char *str)
{
	size_t	i;

	i = 0;
	while(str[i])
	{
		str[i] = tolower(str[i]);
		i++;
	}
	return (str);
}

int	main(void)
{
	printf("This is string: %s\n", return_string(strerror(2)));
	return (0);
}
EOF
cc -Wall -Wextra -Werror testsegv.c -o testsegv
cc -Wall -Wextra -Werror testbus.c -o testbus
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