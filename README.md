# Conga-AI

The goal of this project is to develop an Artificial Intelligence to play against
a random agent in the board game, "Conga". Documentation regarding the structure
of each class will be added in that class' respective directory with a README file.
This project was assigned as the final project in my Artificial Intelligence course,
[EECS 4740](https://www.utoledo.edu/engineering/electrical-engineering-computer-science/current-students/syllabi/eecs-4740-artificial-intelligence.html).

For reference, a random agent is a player that makes random, but valid, moves, while the AI Agent is the implementation 
of the MiniMax algorithm with Alpha-Beta pruning, with a valid heuristic. In the MiniMax algorithm we define our 
maximizer player the AI agent, and the random agent as the minimizer player.  

## Table of Content
1. [Objective](#Objective)
2. [Development](#Development)
3. [What is Conga](#What-is-Conga)
4. [Heuristic](#Heuristic)
    - [Move Heuristic](#Move-heuristic)
    - [Neighbor Heuristic](#Neighbor-heuristic)
    - [Final Heuristic](#Final-Heuristic)
5. [References](#References)

## Objective
The objective of this project is to develop an AI agent to play against a random agent. The AI agent will employ 
adversarial search, by implementing the [Minimax Algorithm](https://en.wikipedia.org/wiki/Minimax) with 
[Alpha-Beta Pruning](https://en.wikipedia.org/wiki/Alpha–beta_pruning),
and [heuristics-based](https://en.wikipedia.org/wiki/Heuristic_(computer_science)) evaluation function to play a 
two-person board game of Conga. The end goal was to develop an AI agent that could beat, in average, a
random agent in around 30 moves.

## Development
This project was developed utilizing Mac OS and [CLion IDE](https://www.jetbrains.com/clion/), which takes advantage 
of a [CMake file](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) for easier builds
of C++ projects. For Windows user they can refer to the documentation for 
[CMake projects in Visual Studio](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=msvc-160)
in order to build and utilize this project.

### What is Conga
The game of Conga was developed by Matin Franke, and published by “Das Spiel Hamburg” in 1998. It is a two-player game 
played on a square 4x4 board, as shown below.

                         _______ _______ _______ _______
                        |       |       |       |       |
                        | (1,4) | (2,4) | (3,4) | (4,4) |
                        |_______|_______|_______|_______|
                        |       |       |       |       |
                        | (1,3) | (2,3) | (3,3) | (4,3) |
                        |_______|_______|_______|_______|
                        |       |       |       |       |
                        | (1,2) | (2,2) | (3,2) | (4,2) |
                        |_______|_______|_______|_______|
                        |       |       |       |       |
                        | (1,1) | (2,1) | (3,1) | (4,1) |
                        |_______|_______|_______|_______|


#### Initial State
Initially, Player 1 has ten black stones in (1,4) and Player 2 has ten white stones in (4,1). The players alternate 
turns. On each turn, a player chooses a square with some of her stones in it, and picks a direction to move them, either
horizontally, vertically or diagonally. The move is done by removing the stones from the square and placing one stone 
in the following square, two in the next one, and the others into the last one. The stones can only be moved in 
consecutive squares that are not occupied by the opponent; if a direction has less than three squares not occupied by 
the opponent in a row, then all remaining stones are placed in the last empty square. If a square has no neighboring 
squares that are not occupied by the opponent, then the stones in that square cannot be moved.

#### What is a Move
You can move stones from a square to a (series of) neighboring square(s), provided the squares you are moving to are 
not occupied by the opponent. It makes no difference if the squares are free or occupied by yourself. You do not need 
any of the squares you are moving to be free; they could all already be occupied by your other stones. The only 
distinction is between squares that are occupied by the opponent (which block you) and squares that are not occupied by 
the opponent (which you can move to). For example, let's say you have several stones in square (1,4) and you want to 
move them right. There can be four possible cases:
1. The opponent occupies square (2,4). You cannot move right. That is the example in Figure 4.
2. The opponent occupies square (3,4), but square (2,4) is either free or occupied by yourself. You move all the 
    stones from (1,4) to (2,4).
3. The opponent occupies square (4,4), but squares (2,4) and (3,4) are either free or occupied by yourself. You move one
    stone from (1,4) to (2,4), and all other stones in (3,4).
4. The opponent doesn't occupy any squares in that row, and all squares are either free or occupied by yourself. You 
    move one stone from (1,4) to (2,4), two stones to (3,4), and all other stones in (4,4)
    
#### Goal
The goal of the game is to block the opponent, so that (s)he has no legal moves. In other words, all the opponents’ 
stones must be trapped in squares that are all surrounded by the player’s stones.


## Heuristic
The heuristic can be found inside the [AI_Agent/AI_Agent.cpp](https://github.com/cgalo/Conga-AI/blob/master/AI_Agent/AI_Agent.cpp),
specifically in the method *evalBoard*. The heuristic is utilized if in the current state of the board, there is currently
no winner/looser, aka both players have at least one available move in the board. I defined the max player as the AI 
agent, and the minimizer player as the random agent.

The heuristic takes two different scores, the *Move score* and the *Neighbor score*, and
adds them together to provide a final score for the given board, required as a parameter,
of the *evalBoard* method. 

### Move heuristic
The *Move score* consists of counting the total available moves of the AI agent minus the total available moves
for the random agent. The goal of this heuristic is to make the AI choose states/moves that led them to 
having more available moves than the opponent, the random agent.

#### Pseudocode
```c++
int totAIMoves = board->getMoves(maxP).size();  // Count total moves for the AI
int totOppMoves = board->getMoves(minP).size(); // Count total moves for the random agent
const int moveScore = totAIMoves - totOppMoves; // Calculate the move heuristic
```

### Neighbor heuristic
I defined a *neighbor* of a space as all the adjacent spaces for that given space. 

                         _______ _______ _______ _______
                        |       |       |       |       |
                        | (1,4) | (2,4) | (3,4) | (4,4) |
                        |_______|_______|_______|_______|
                        |       |       |       |       |
                        | (1,3) | (2,3) | (3,3) | (4,3) |
                        |_______|_______|_______|_______|
                        |       |       |       |       |
                        | (1,2) | (2,2) | (3,2) | (4,2) |
                        |_______|_______|_______|_______|
                        |       |       |       |       |
                        | (1,1) | (2,1) | (3,1) | (4,1) |
                        |_______|_______|_______|_______|

 Taking the board, as displayed above, for space (1,4) the *neighbor* spaces would be: (2,4), (2,3), and (1,3).
 The neighbor heuristic consists of iterating through every space of the opponent, getting the neighbors for that given space,
 and adding +1 if the AI agent, or maximizer player, already holds that neighbor space, or -1 if the AI doesn't hold that space.
 
 For example, given the starting board, where the AI agent holds 10 rocks in the (1,4) space, and the random agent holds their 
 10 rocks in the (4,1) space, the *Neighbor score* would equate to -3. This is due to the fact that for the 
 random space, (4,1), the neighbor spaces would be (3,1), (3,2), and (4,2), which the AI agent doesn't hold, meaning it 
 has no rocks on them at the moment, leads to -1 pt for each space it doesn't hold. Given that there is a list of 3 neighbor
 spaces that the AI doesn't hold then we get a -3 *Neighbor score*.   
#### Pseudocode
```c++
int neighborScore = 0;                              // 0 is the base score
auto minSpaces = board->getPlayerSpaces(minP);      // Get the list of spaces that the random player holds
for (auto minSpace: minSpaces){                     // Iterate through every space of the list of spaces
    auto neighbors = board->getNeighbors(minSpaces);// Get list of adjacent spaces of the current space
    for (auto neighbor: neighbors){                 // Iterate through every neighbor of the current space
        if (neighbor->getPlayer() == maxP)          // If the AI holds this neighbor space
            neighborScore++;                        // Increase the score of the neighborScore
        else                                        // Else the AI doesn't hold the neighbor space
            neighborScore--;                        // Minus 1 pt of the neighborScore
    }
}
```
### Final Heuristic
The final heuristic consists on just adding both the [Move heuristic](#Move heuristic) and the [Neighbor heuristic](#Neighbor heuristic).
Utilizing the variables from the pseudocode of the *Move* and *Neighbor* heuristics, as shown above we get:
```c++
const int finalScore = moveScore + neighborScore;   // Add both the scores for a final heuristic
```


## References
- [Conga Official Website](http://www.congaspiel.de)
- [Minimax Algorithm](https://en.wikipedia.org/wiki/Minimax)
- [Alpha-Beta Pruning](https://en.wikipedia.org/wiki/Alpha–beta_pruning)
- [Heuristic](https://en.wikipedia.org/wiki/Heuristic_(computer_science))
- [UToledo EECS 4740 - Artificial Intelligence](https://www.utoledo.edu/engineering/electrical-engineering-computer-science/current-students/syllabi/eecs-4740-artificial-intelligence.html)
- [Waterloo Adversarial Search Project](http://pami.uwaterloo.ca/~basir/ECE457/project2.pdf)
