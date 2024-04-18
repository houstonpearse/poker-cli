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

### `poker-cli sort`

- reads hands of the format "A-S,K-S,Q-S,J-S,T-S" from stdin.
- outputs hands in the order of highest rank to lowest rank.
- hands can have any number of cards.
- poker rules are high poker rules. This means an Ace can be a high or low card.

### `poker-cli sim`

- simulates poker and outputs statistics about win percentage.
- By default players cards are randomly selected
- By setting the hand and table cards we can learn about the odds of different hands
  - ./poker-cli sim --hand 'A-S,A-C' --hands 50000 --players 5
  - win=0.51, lose=0.49, tied=0.01
  - ./poker-cli sim --hand 'A-S,A-C' --hands 50000 --players 5 --table 'A-D'
  - win=0.80, lose=0.20, tied=0.00
- By setting the number of players we can see how it affects our chances of having the highest ranking hand
  - ./poker-cli sim --hand 'A-S,A-C' --hands 50000 --players 10
  - win=0.27, lose=0.73, tied=0.00
- We can set the verbose option to see individual hands played

```
⚡ ./poker-cli sim --verbose
seed: 1713451877
game 1
table: T-C,5-S,Q-H,8-S,A-S
player2: 5-H,A-C
player0: J-C,A-D
player4: Q-D,2-C
player1: T-D,K-D
player3: 6-H,2-S
win,lost,tied
0.000,1.000,0.000
```

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

| option | long option     | effect                                                    |
| ------ | --------------- | --------------------------------------------------------- |
| -h     | --help          | display help message                                      |
| -v     | --verbose       | displays information for each hand and ranking of players |
| -p     | --players <int> | number of players for simulation                          |
| -h     | --hands <int>   | number of hands for simulation                            |
| -s     | --seed <int>    | suedo-random seed for shuffling deck                      |
| -t     | --table         | sets the table cards                                      |
| -a     | --hand          | sets the hand for player 0                                |

## Running test

`make sort-test` for testing sort cli tool.
`make unit-test` for unit testing of source code.

```
⚡ make sort-test
make poker-cli
make[1]: `poker-cli' is up to date.
bash ./tests/sort-test.sh
✅ Test straight-flush Passed
✅ Test four-of-a-kind Passed
✅ Test full-house Passed
✅ Test full-house-6 Passed
✅ Test flush Passed
✅ Test straight Passed
✅ Test triple Passed
✅ Test pairs-singles Passed
```
