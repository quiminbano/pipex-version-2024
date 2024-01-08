#!/bin/zsh

echo "COMPILING THE PROGRAM"
make
sleep 2
echo "CREATING AN INFILE"
echo "THIS IS AN INFILE" > infile
sleep 2
echo ""
echo ""
echo "FIRST TEST: ./pipex \"\" \"\" \"\" \"\""
echo "PIPEX:"
./pipex "" "" "" ""
sleep 1
echo ""
echo "ZSH"
zsh -c < "" "" | "" > ""
sleep 2
echo ""
echo ""
echo "SECOND TEST: ./pipex \"\" \"cat\" \"cat\" \"\""
echo "PIPEX:"
./pipex "" "cat" "cat" ""
sleep 1
echo ""
echo "ZSH"
zsh -c < "" "cat" | "cat" > ""
sleep 2
echo ""
echo ""
echo "THIRD TEST: ./pipex \"infile\" \"cat\" \"cat\" \"\""
echo "PIPEX:"
./pipex "infile" "cat" "cat" ""
sleep 1
echo ""
echo "ZSH"
zsh -c < "infile" "cat" | "cat" > ""
sleep 2
echo ""
echo ""
echo "FOURTH TEST: ./pipex \"\" \"cat\" \"cat\" \"\"outfile"
echo "PIPEX:"
./pipex "infile" "cat" "cat" "outfile"
sleep 1
echo "THIS IS THE CONTENT OF OUTFILE CREATED BY pipex:"
cat outfile
rm outfile
echo ""
echo "ZSH"
zsh -c < "infile" "cat" | "cat" > "outfile"
echo "THIS IS THE CONTENT OF OUTFILE CREATED BY ZSH:"
cat outfile
rm outfile
sleep 2
echo ""
echo ""
echo "FIFTH TEST: ./pipex \"infile\" \"\" \"\" \"outfile\""
echo "PIPEX:"
./pipex "infile" "" "" "outfile"
sleep 1
echo "THIS IS THE CONTENT OF OUTFILE CREATED BY pipex:"
cat outfile
rm outfile
echo ""
echo "ZSH"
zsh -c < "infile" "" | "" > "outfile"
echo "THIS IS THE CONTENT OF OUTFILE CREATED BY ZSH:"
cat outfile
rm outfile
sleep 2
echo ""
valgrind --leak-check=full --show-reachable=yes --track-origins=yes --verbose --tool=memcheck ./pipex "" "" "" ""
valgrind --leak-check=full --show-reachable=yes --track-origins=yes --verbose --tool=memcheck ./pipex "" "cat" "cat" ""
valgrind --leak-check=full --show-reachable=yes --track-origins=yes --verbose --tool=memcheck ./pipex "infile" "cat" "cat" ""
valgrind --leak-check=full --show-reachable=yes --track-origins=yes --verbose --tool=memcheck ./pipex "infile" "cat" "cat" "outfile"
valgrind --leak-check=full --show-reachable=yes --track-origins=yes --verbose --tool=memcheck ./pipex "" "cat" "cat" "outfile"
valgrind --leak-check=full --show-reachable=yes --track-origins=yes --verbose --tool=memcheck ./pipex "infile" "" "" "outfile"
