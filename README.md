<h1 align="center">Simple Poker CLI tool and Simulator</h1>
<br />
<div align="center">
  <a href="https://github.com/houstonpearse/poker-cli">
    <img src="https://github.com/Any-Many/Pixel-Poker-Playing-Cards/blob/main/small/kDimondsSmall.png" alt="Logo" width="200" height="200">
  </a>
  <a href="https://github.com/houstonpearse/poker-cli">
    <img src="https://github.com/Any-Many/Pixel-Poker-Playing-Cards/blob/main/small/qHeartsSmall.png" alt="Logo" width="200" height="200">
  </a>

<h3 align="center">Poker CLI</h3>
<p>
A basic Poker simulator and cli tool.

Poker logic follows high poker rules

</p>
</div>

## Features

1. Sort hands based on poker rules `poker-cli sort`
   - hands are of the format "A-S,K-S,Q-S,J-S,T-S".
   - hands are read from stdin separated by newlines.
2. simulate poker hands `poker-cli --hand "A-S,K-S,Q-S,J-S,T-S" --players 10 --hands 25000 --seed 1234`
   - by default players cards are randomly selected
   - can set hands of players
   - can set table cards

## Usage

Compile by running `make` or `make poker-cli`

run `./poker-cli` for simulation

run `./poker-cli sort < input.txt > output.txt`

```
#input.txt
5-S,4-C,3-H,2-S,A-C
6-S,4-C,3-H,2-S,A-C
6-S,5-S,4-C,3-H,2-S
7-H,6-D,5-S,4-C,3-H
K-S,Q-C,J-H,T-S,9-C
A-C,K-S,Q-C,J-H,T-S
```

```
#output.txt
A-C,K-S,Q-C,J-H,T-S
K-S,Q-C,J-H,T-S,9-C
7-H,6-D,5-S,4-C,3-H
6-S,5-S,4-C,3-H,2-S
5-S,4-C,3-H,2-S,A-C
6-S,4-C,3-H,2-S,A-C
```

## Options

| option | long option     | effect                               |
| ------ | --------------- | ------------------------------------ |
| -h     | --help          | display help message                 |
| -p     | --players <int> | number of players for simulation     |
| -h     | --hands <int>   | number of hands for simulation       |
| -s     | --seed <int>    | suedo-random seed for shuffling deck |
| -t     | --table         | sets the table cards                 |
| -a     | --hand          | sets the hand for player 0           |

## Running test

`make sort-test` for testing sort cli tool.
`make unit-test` for unit testing of source code.
