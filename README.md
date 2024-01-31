# Pipex

The Pipex project is a custom implementation of the Unix `pipe` command. This project is carried out as part of the training at the 42 Network Schools. It focuses on teaching basic Unix operations, particularly about pipelines, child processes, and command execution.

## What is the project trying to simulate?

This project tries to simulate the following entrance in a shell:

```bash
< infile cmd1 | cmd2 > outfile
```

Where `infile` is an input file, `cmd1` and `cmd2` are the commands you want to run in sequence, and `outfile` is an output file to create. The behaviour of this command is going to depend of your shell of reference.

In pipex, to get the same result than the command above, you must run your pipex as follows:

```bash
./pipex infile cmd1 cmd2 outfile
```

Where `infile`, `cmd1`, `cmd2` and `outfile` have the same purpuse than the command mentioned above.

## Installation

To install this project, follow these steps:

1. Clone the repository onto your local machine using the following command:
```bash
git clone https://github.com/quiminbano/pipex-version-2024.git
```

3. Navigate to the project directory:

```bash
cd pipex
```

3. Compile the project with the `make` command:

```bash
make
```

4. Run the command, replacing `infile`, `cmd1` and `cmd2` for valid files or commands:

For example:
```bash
./pipex pipex.c "ls" "wc -l" outfile
```

## Bonus

The bonus of this project add some extra features to the program pipex. These functionalities are:

1. Run more than two commands in one call:

For example: 
```bash
./pipex infile cmd1 cmd2 cmd3 .... cmdn outfile
``` 
represents the command
```bash
< infile cmd1 | cmd2 | cmd3 | ..... | cmdn > outfile
```

2. Open a heredoc when the keyword `here_doc` is used as a first parameter. Append the output to `outfile` if `outfile` exists previously.

For example:
```bash
./pipex here_doc EOF "cat" "wc -l" outfile
```
represents the command:
```bash
<< EOF cat | wc -l > outfile
```

## Tests

To test this project, you can use the tool pipexTester, that you can find [here](https://github.com/quiminbano/pipexTester)

## Contributions

Contributions to this project are welcome. Please open an issue or a pull request if you have any suggestions or find any bugs.
