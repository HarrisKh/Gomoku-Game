# Tic-Tac-Toe Game in C++

## Overview

This project is a customizable Tic-Tac-Toe style board game developed in C++ using the Windows Console API.

Unlike a standard 3x3 Tic-Tac-Toe game, this implementation allows the user to specify the number of rows, columns, and the number of symbols required to win.

The game supports two modes:

1. Human vs Human
2. Human vs Computer

The game also uses mouse input in the console. Players select a board position by left-clicking on the desired cell.

---

# Features

* Human vs Human mode
* Human vs Computer mode
* Custom board dimensions
* Custom number of symbols required to win
* Custom player symbols and names
* Mouse-based board selection
* Colored console output
* Horizontal win detection
* Vertical win detection
* Diagonal win detection
* Additional T-shaped win detection
* Draw detection
* Computer move generation
* Computer winning-move detection
* Computer blocking strategy
* Random computer moves when no immediate move exists

---

# Technologies Used

* C++
* Windows Console API
* `windows.h`
* Standard C++ input/output
* Arrays
* Functions
* Random number generation

The program uses Windows-specific console functions to receive mouse input and change console colors.

---

# Game Modes

## 1. Human vs Human

In this mode, all players are human.

The program asks for:

* Number of players
* Number of symbols required to win
* Number of rows
* Number of columns
* Each player's symbol
* Each player's name

For example:

```text
NOP, WinCount, Rows, Cols:
2 3 3 3
```

The players then take turns selecting cells using the mouse.

---

## 2. Human vs Computer

In this mode, the game automatically creates two players:

```text
Player 1: Computer
Player 2: Human
```

The computer uses the symbol:

```text
C
```

The user chooses their own symbol and name.

The default winning count for this mode is:

```text
3
```

The user can still choose the board dimensions.

---

# Board Representation

The board is stored in a two-dimensional character array:

```cpp
char B[MR][MC];
```

The maximum dimensions are defined as:

```cpp
#define MR 100
#define MC 100
```

Therefore, the program can support boards up to:

```text
100 rows x 100 columns
```

The actual board size is selected by the user.

---

# Board Initialization

The `Init()` function initializes the game.

Every board cell is initially filled with:

```text
-
```

For example, a 3x3 board initially looks like:

```text
---
---
---
```

The `-` character represents an empty cell.

The function also initializes:

* Number of players
* Player symbols
* Player names
* Board dimensions
* Winning count
* Starting turn

The starting player is selected randomly using:

```cpp
turn = rand() % Nop;
```

---

# Console Board Display

The `displayBoard()` function prints the board in the console.

It draws a border around the board and displays different colors for:

* Empty cells
* Computer moves
* Human moves

The board is cleared and redrawn after every move.

The basic structure is:

```text
+---------+
|---------|
|---------|
|---------|
+---------+
```

The actual width depends on the number of columns.

---

# Mouse Input

One of the main features of this project is mouse-based board selection.

The function:

```cpp
getRowColbyLeftClick()
```

uses the Windows Console API to detect a left mouse click.

It enables mouse input using:

```cpp
ENABLE_MOUSE_INPUT
```

and reads console events using:

```cpp
ReadConsoleInput()
```

When the player clicks somewhere in the console, the program obtains the screen row and column of the click.

---

# Converting Mouse Position to Board Position

The function:

```cpp
selectPos()
```

converts the mouse's console coordinates into board coordinates.

The board starts approximately at:

```text
X = 35
Y = 3
```

Therefore:

```cpp
r = mR - Y;
c = mC - X;
```

converts the mouse position into the corresponding row and column of the board.

This allows the player to simply click on the desired board cell instead of entering row and column numbers manually.

---

# Move Validation

The `isValid()` function checks whether a selected position is legal.

A move is valid when:

1. The row is inside the board.
2. The column is inside the board.
3. The selected cell is empty.

The condition is essentially:

```cpp
r >= 0
r < R
c >= 0
c < C
B[r][c] == '-'
```

If the move is invalid, the player is asked to select another position.

---

# Updating the Board

Once a valid move has been selected, `updateBoard()` places the player's symbol into the selected cell.

For example:

```text
Before:

---
-C-
---

After another player moves:

-A-
-C-
---
```

The board is then displayed again.

---

# Turn Management

The current player's turn is stored in:

```cpp
int turn;
```

The `turnChange()` function switches to the next player.

```cpp
turn = (turn + 1) % Nop;
```

For two players:

```text
Player 0
   |
   v
Player 1
   |
   v
Player 0
```

This continues until somebody wins or the board becomes full.

---

# Winning Conditions

The program checks several different patterns to determine whether a player has won.

The main function responsible for this is:

```cpp
isWinHere()
```

It checks:

1. Horizontal
2. Vertical
3. Right diagonal
4. Left diagonal
5. T-shaped pattern

If any of these conditions are satisfied, the player wins.

---

# Horizontal Win

The function:

```cpp
horiCheck()
```

checks for consecutive symbols in the same row.

It starts from the most recent move and searches:

* Left
* Right

The original position is counted as well.

For example, with a winning count of 3:

```text
XXX
```

results in a win.

The function stops counting when:

* The board boundary is reached.
* A different symbol is encountered.

---

# Vertical Win

The function:

```cpp
vertCheck()
```

works similarly but checks vertically.

It searches:

* Up
* Down

For example:

```text
X
X
X
```

is a winning arrangement when the required winning count is 3.

---

# Right Diagonal Win

The function:

```cpp
rightDiagCheck()
```

checks the diagonal running from the upper-left toward the lower-right.

Example:

```text
X--
-X-
--X
```

The function searches in both directions from the latest move:

```text
Upper-left
     \
      Current
           \
          Lower-right
```

The total number of consecutive matching symbols is then compared with the required winning count.

---

# Left Diagonal Win

The function:

```cpp
leftDiagCheck()
```

checks the opposite diagonal direction.

Example:

```text
--X
-X-
X--
```

It searches:

* Upper-right
* Lower-left

and counts consecutive matching symbols.

---

# T-Shaped Winning Condition

In addition to the standard horizontal, vertical, and diagonal checks, this game contains a custom function:

```cpp
Tcheck()
```

This introduces an additional winning pattern based on a T-shaped arrangement.

The function performs additional checking around the current position and compares the resulting count against the required winning count.

This makes the game different from a conventional Tic-Tac-Toe implementation because winning is not limited to straight horizontal, vertical, or diagonal lines.

---

# Overall Win Checking

The function:

```cpp
isWinHere()
```

combines all of the winning checks.

Its logic is:

```text
Check Horizontal
      |
      v
Check Vertical
      |
      v
Check Right Diagonal
      |
      v
Check Left Diagonal
      |
      v
Check T Pattern
      |
      v
Win or No Win
```

As soon as one condition is satisfied, the function returns `true`.

---

# Draw Detection

The `isDraw()` function determines whether the board is full.

It checks every cell.

If at least one cell still contains:

```text
-
```

the game is not a draw.

If no empty cells remain, the game ends in a draw.

Example:

```text
XOX
OXO
XXO
```

If no winning condition exists, the game is declared a draw.

---

# Computer AI

The Human vs Computer mode contains a simple rule-based AI.

The computer does not use advanced algorithms such as Minimax.

Instead, it follows three main steps:

1. Try to win.
2. Try to block the human.
3. Make a random move.

This provides a basic but useful game-playing strategy.

---

# AI Step 1: Find a Winning Move

The function:

```cpp
computerMove()
```

first examines every empty cell.

For each empty cell, it temporarily places the computer's symbol there.

It then calls:

```cpp
isWinHere()
```

to determine whether that move would result in a win.

If it does, the position is selected.

The temporary symbol is then removed before the actual move is made.

Conceptually:

```text
For every empty cell:

Place computer symbol
        |
        v
Check for win
        |
    +---+---+
    |       |
   Yes      No
    |       |
 Select    Try next
```

This means the computer always takes an immediate winning opportunity if one exists.

---

# AI Step 2: Block the Human

If the computer cannot win immediately, it checks whether the human can win on their next move.

It temporarily places the human's symbol in every empty position.

If that position would cause the human to win, the computer chooses that position instead.

Therefore, the computer attempts to block an immediate human victory.

The logic is:

```text
Can Computer Win?
       |
      No
       |
       v
Can Human Win Next?
       |
      Yes
       |
       v
Block Human
```

---

# AI Step 3: Random Move

If neither the computer nor the human has an immediate winning move, the computer chooses a random empty cell.

The program repeatedly generates random row and column values until it finds an empty position.

This is done using:

```cpp
rand() % R
rand() % C
```

Therefore, the computer can make a random move when no tactical move is available.

---

# Complete AI Decision Process

The computer's strategy can be summarized as:

```text
Computer's Turn
      |
      v
Can Computer Win?
   |          |
  Yes         No
   |           |
   v           v
Play Move   Can Human Win?
               |       |
              Yes      No
               |        |
               v        v
             Block    Random Move
```

This is a simple priority-based AI.

---

# Game Flow

The overall program works as follows:

```text
Start
 |
 v
Select Game Mode
 |
 +-----------------------+
 |                       |
 v                       v
Human vs Human      Human vs Computer
 |                       |
 v                       v
Enter Players       Create Computer
 |                   Enter Human
 +----------+------------+
            |
            v
       Initialize Board
            |
            v
       Select Starting Turn
            |
            v
        Display Board
            |
            v
        Player Turn
            |
       +----+----+
       |         |
     Human    Computer
       |         |
       v         v
  Mouse Click  AI Move
       |         |
       +----+----+
            |
            v
       Validate Move
            |
            v
       Update Board
            |
            v
       Check for Win
        /          \
      Yes           No
       |             |
       v             v
     End          Check Draw
                    /    \
                  Yes     No
                   |       |
                   v       v
                  End   Change Turn
                            |
                            v
                       Next Turn
```

---

# Main Functions

| Function                 | Purpose                                   |
| ------------------------ | ----------------------------------------- |
| `Init()`                 | Initializes the game and board            |
| `color()`                | Changes console text color                |
| `getRowColbyLeftClick()` | Reads mouse click position                |
| `displayBoard()`         | Displays the game board                   |
| `displayMsg()`           | Displays the current player's turn        |
| `selectPos()`            | Converts mouse position to board position |
| `updateBoard()`          | Places a symbol on the board              |
| `isValid()`              | Checks whether a move is valid            |
| `turnChange()`           | Changes the current player                |
| `horiCheck()`            | Checks horizontal winning pattern         |
| `vertCheck()`            | Checks vertical winning pattern           |
| `rightDiagCheck()`       | Checks one diagonal direction             |
| `leftDiagCheck()`        | Checks the other diagonal direction       |
| `Tcheck()`               | Checks the custom T-shaped pattern        |
| `isWinHere()`            | Combines all winning checks               |
| `isDraw()`               | Checks whether the board is full          |
| `computerMove()`         | Generates the computer's move             |
| `main()`                 | Controls the complete game flow           |

---

# Important Data Structures

The project mainly uses arrays.

## Board

```cpp
char B[MR][MC];
```

Stores the board.

## Player Symbols

```cpp
char Psym[MR];
```

Stores the symbols of the players.

## Player Names

```cpp
char Pname[MR][MC];
```

Stores player names.

The use of arrays allows the game to support multiple players in Human vs Human mode.

---

# Console Colors

The game uses the Windows API function:

```cpp
SetConsoleTextAttribute()
```

through the custom:

```cpp
color()
```

function.

Different colors are used to make the board easier to read.

The computer symbol is displayed differently from the human symbols.

---

# Randomization

The program initializes random number generation using:

```cpp
srand(time(0));
```

Randomization is used for:

* Selecting the starting player
* Selecting a random computer move

This prevents the game from always behaving exactly the same way.

---

# Game Limitations

The current implementation has some limitations:

* It relies on Windows-specific console APIs.
* It is not portable to Linux or macOS without changes.
* The computer AI is rule-based rather than a complete optimal Tic-Tac-Toe AI.
* The board uses fixed maximum dimensions of 100 by 100.
* Mouse coordinates depend on the console layout and board position.
* There is no save/load functionality.
* There is no undo/redo system.

---

# Possible Improvements

Future versions could include:

* Minimax-based AI
* Better AI for larger boards
* Difficulty levels
* Keyboard-based movement
* Better mouse coordinate handling
* Score tracking
* Game restart option
* Save/load game
* Improved board interface
* Cross-platform graphics using Raylib
* Player statistics
* Multiple rounds and match scoring

---

# Concepts Demonstrated

This project demonstrates:

* Functions
* Arrays
* Two-dimensional arrays
* Character arrays
* Loops
* Conditional statements
* Random number generation
* Modular programming
* Input validation
* Console graphics
* Mouse input
* Windows API
* Game loops
* Basic artificial intelligence
* Pattern detection algorithms

---

# Conclusion

This project is a customizable Tic-Tac-Toe style game written in C++ with two main gameplay modes: Human vs Human and Human vs Computer.

The Human vs Human mode allows multiple human players to enter their names and symbols and compete by selecting board positions with the mouse.

The Human vs Computer mode introduces a simple AI that first looks for a winning move, then checks whether it needs to block the human player, and finally chooses a random valid move if neither side has an immediate winning opportunity.

The game also supports customizable board sizes and winning conditions. Instead of being restricted to a standard 3x3 board, the user can define the number of rows, columns, and symbols required to win.

Winning is checked in multiple directions, including horizontal, vertical, both diagonal directions, and an additional custom T-shaped pattern.

Overall, the project demonstrates how basic C++ programming concepts, console graphics, mouse input, board-based algorithms, and simple AI can be combined to create a complete interactive game.
