# Connect4
Outscal dsa mat 1

Intro: </br>
Connect 4 is a classic game Where 2 player tries to place their color 4 times consicutively  on the board.(Horizontaly or vertically or digonally)
Here I am tring to recreate that game but in console.

Game Play: </br>
It is a turned based game and starts with Red player and then followed by yellow player.
Choose a column and your color token will be dropped on that column and if there are any empty place on that coloumn. Then that token will be placed there.

Rules: </br>
Try to place your color 4 times consicutively  on the board.(Horizontaly or vertically or digonally)
Before your completion if other player is going to win you can stop him from doing so.
If all the place on the board are filled then it will be draw.


Overview of the entire code: </br>
1. a game loop
2. turn based player input system
3. input control
4. Game Board print and update system
5. Result (Here I am maintaining a vector of pair<int, int> per player and it is recording the place their ball is placed on board. On each step verifying whether is it a four connect or not. If it is a four connect declare result and stop the game. Otherwise continue until the board is filled.)

Code Structure: </br>
Main Program -> Main Method </br></br>
class Game -> StartGame Method (It has a intro Game banner, game rules and instructions. According to the users input it will starts the main game loop or Quit the game. )</br></br>
class Main Game Loop -> GameLoop method (It deals with player turns and player input control. It also has conditions that decides when the game loop will stop.)</br></br>
class Board -> it has update board, print board, get character methods. </br></br>
class Player -> it has player info and a vector of pair<int, int> that contains all the boxes player's ball dropped in.</br></br>
base class WinningConditionChecker -> it is a base class there are 4 types of checks which are the sub classes of this one.</br></br>
class HorizontalCheck, Vertical Check, PositiveDigonal Check, negative digonal check.</br></br>
class ResultChecker -> that tells when the check should be done</br></br>
class Result printer -> that declares the result</br></br>


