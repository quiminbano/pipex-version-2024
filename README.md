# Pipex

The Pipex project is a custom implementation of the Unix `pipe` command. This project is carried out as part of the training at the 42 Network Schools. It focuses on teaching basic Unix operations, particularly about pipelines, child processes, and command execution.

## What is the project trying to simulate?

This project tries to simulate the following entrance in a shell:

```bash
< infile cmd1 | cmd2 > outfile
```

Where `infile` is an input file, `cmd1` and `cmd2` are the commands you want to run in sequence, and `outfile` is an output file to create.

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

## Usage

Once you have compiled the project, you can use the `pipex` program from the command line. Here is an example of how to use it:

```bash
./pipex infile cmd1 cmd2 outfile
```

## Tests

To test this project, you can use the tool pipexTester, that you can find [here](https://github.com/quiminbano/pipexTester)

## Contributions

Contributions to this project are welcome. Please open an issue or a pull request if you have any suggestions or find any bugs.
