# Hex Board Analyzer

![GitHub](https://img.shields.io/github/license/m-sadkowski/Hex-Board-Analyzer)
![GitHub issues](https://img.shields.io/github/issues/m-sadkowski/Hex-Board-Analyzer)
![GitHub stars](https://img.shields.io/github/stars/m-sadkowski/Hex-Board-Analyzer)

This project is a **Hex board analyzer** implemented in **C++**. It answers various questions about a given Hex board state, such as board size, pawn count, correctness, game status, and winning possibilities. The Hex game is a strategic board game played on a hexagonal grid. More information about the game can be found [here](https://en.wikipedia.org/wiki/Hex_(board_game)).

---

## Features

The analyzer supports the following operations:

1. **BOARD_SIZE**: Returns the size of the Hex board.
2. **PAWNS_NUMBER**: Returns the number of pawns (red and blue) on the board.
3. **IS_BOARD_CORRECT**: Checks if the board configuration is valid.
4. **IS_GAME_OVER**: Determines if the game has ended (i.e., a player has won).
5. **IS_BOARD_POSSIBLE**: Checks if the board state is possible under normal game rules.
6. **CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT**: Determines if Red can win in one move against a naive opponent.
7. **CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT**: Determines if Blue can win in one move against a naive opponent.
8. **CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT**: Determines if Red can win in two moves against a naive opponent.
9. **CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT**: Determines if Blue can win in two moves against a naive opponent.

---

## How It Works

The analyzer takes a Hex board state as input and processes it to answer the supported questions. It uses graph traversal algorithms (e.g., Depth-First Search or Breadth-First Search) to determine winning conditions and validate the board state.

### Example Input

```
---
--< >--
--< b >-< >--
--< r >-< >-< >--
< b >-< b >-< >-< r >
--< >-< r >-< b >--
--< >-< r >--
--< >--
---
```

### Example Output

```
BOARD_SIZE: 7
PAWNS_NUMBER: Red = 3, Blue = 4
IS_BOARD_CORRECT: Yes
IS_GAME_OVER: No
IS_BOARD_POSSIBLE: Yes
CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT: No
CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT: Yes
CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT: Yes
CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT: No
```

---

## Getting Started

### Prerequisites

- A C++ compiler (e.g., `g++`).
- Basic knowledge of the Hex game.

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/m-sadkowski/Hex-Board-Analyzer.git
   cd Hex-Board-Analyzer
   ```

2. Compile the program:
   ```bash
   g++ -o hex_analyzer main.cpp
   ```

3. Run the program:
   ```bash
   ./hex_analyzer
   ```

---

## Usage

1. Input the Hex board state in the specified format.
2. The program will analyze the board and output the results for the supported operations.

### Input Format

The board is represented as a grid of hexagonal cells. Each cell can be:
- `< >`: Empty cell.
- `< r >`: Red pawn.
- `< b >`: Blue pawn.

The board is surrounded by `---` borders.

### Example Input

```
          ---
       --<   >--
    --< b >-<   >--
 --< r >-<   >-<   >--
< b >-< b >-<   >-< r >
 --<   >-< r >-< b >--
    --<   >-< r >--
       --<   >--
          ---
```

---

## Supported Operations

| Operation                                      | Description                                                                 |
|------------------------------------------------|-----------------------------------------------------------------------------|
| `BOARD_SIZE`                                   | Returns the size of the Hex board.                                          |
| `PAWNS_NUMBER`                                 | Returns the number of Red and Blue pawns on the board.                      |
| `IS_BOARD_CORRECT`                             | Checks if the board configuration is valid.                                 |
| `IS_GAME_OVER`                                 | Determines if the game has ended (i.e., a player has won).                  |
| `IS_BOARD_POSSIBLE`                            | Checks if the board state is possible under normal game rules.             |
| `CAN_RED_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT`    | Determines if Red can win in one move against a naive opponent.            |
| `CAN_BLUE_WIN_IN_1_MOVE_WITH_NAIVE_OPPONENT`   | Determines if Blue can win in one move against a naive opponent.            |
| `CAN_RED_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT`   | Determines if Red can win in two moves against a naive opponent.           |
| `CAN_BLUE_WIN_IN_2_MOVES_WITH_NAIVE_OPPONENT`  | Determines if Blue can win in two moves against a naive opponent.          |

---

## Contributing

Contributions are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

1. Fork the repository.
2. Create a new branch (`git checkout -b feature/YourFeature`).
3. Commit your changes (`git commit -m 'Add some feature'`).
4. Push to the branch (`git push origin feature/YourFeature`).
5. Open a pull request.

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Acknowledgments

- Inspired by the strategic depth of the Hex board game.
- Built as a learning project for C++ programming and game analysis.

---

## Contact

For questions or feedback, please reach out to [m-sadkowski](https://github.com/m-sadkowski).

---

Enjoy analyzing Hex boards! 🎲