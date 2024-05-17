#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include<stdlib.h>
using namespace sf;
using namespace std;
#define reset "\033[0m"
#define red "\033[1;31m"
#define green "\033[1;32m"
#define yel "\033[1;33m"
#define blue "\033[1;34m"
#define mag "\033[1;35m"
#define cyan "\033[1;36m"
#define white "\033[1;37m"1 


int x = 0, o = 0;
enum  Player { None, Cross, Circle };

 int WS = 400;//window size
 int CS = WS / 4;//cell size 

bool checkWin( Player board[4][4], Player player) {
    // Check rows and columns
    for (int i = 0; i < 4; ++i) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player && board[i][3] == player)
            return true;
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player && board[3][i] == player)
            return true;
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player && board[3][3] == player)
    {
        return true;
    }
    if (board[0][3] == player && board[1][2] == player && board[2][1] == player && board[3][0] == player)
    {
        return true;
    }

    return false;
}

bool Full(const Player board[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (board[i][j] == Player::None)
                return false;
        }
    }
    return true;
}

int main() {
    RenderWindow window(VideoMode(WS, WS), "WELLCOME TO XO");
    Music music;
    if (!music.openFromFile("C:/Users/3B/source/repos/1111/moonlight-sonata-full.mp3")) {
        // error handling
        return 0;
    }
    music.play();

    while (window.isOpen()) {

        Player board[4][4] = {//clear the board
            {Player::None, Player::None, Player::None, Player::None},//initial valu for all the array = none(0)
            {Player::None, Player::None, Player::None, Player::None},
            {Player::None, Player::None, Player::None, Player::None},
            {Player::None, Player::None, Player::None, Player::None}
        };
        bool XorO = true/*x 1 o 0*/, gameEnded = false;
        Player winner = Player::None;//initial valu of winner in none(0)
        while (!gameEnded) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {// Close window button clicked               
                    sf::sleep(sf::milliseconds(0));
                    window.close();
                    return 0;
                }
                //when we start to pressed the button take the cordnat (row,column)
                if (event.type == Event::MouseButtonPressed) {
                    if (event.mouseButton.button == Mouse::Left) {
                        int row = event.mouseButton.y / CS;//It gives the Y-coordinate of the mouse pointer relative to the top-left corner of the window
                        int col = event.mouseButton.x / CS;

                        if (row >= 0 && row < 4 && col >= 0 && col < 4 && board[row][col] == Player::None) {
                            if (XorO)
                            {
                                board[row][col] = Player::Cross;
                            }
                            else
                            {
                                board[row][col] = Player::Circle;
                            }
                            XorO = !XorO;

                            if (checkWin(board, Player::Cross)) {
                                winner = Player::Cross;
                                x++;
                                gameEnded = true;
                            }
                            else if (checkWin(board, Player::Circle)) {
                                winner = Player::Circle;
                                o++;
                                gameEnded = true;
                            }
                            else if (Full(board)) {
                                gameEnded = true;
                            }
                        }
                    }
                }
            }

            window.clear(Color::Transparent);
            // Draw the board
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    RectangleShape cell(Vector2f(CS, CS));
                    cell.setPosition(j * CS, i * CS);
                    cell.setOutlineThickness(2);
                    cell.setOutlineColor(Color::Black);
                    window.draw(cell);

                    if (board[i][j] == Player::Cross) {//x draw
                        VertexArray cross(Lines, 4);//creat x 
                        cross[0].position = Vector2f(j * CS +5 , i * CS+5 );//up left
                        cross[1].position = Vector2f((j + 1) * CS -5 , (i + 1) * CS-5 );//dowen right
                        cross[2].position = Vector2f(j * CS +5 , (i + 1) * CS-5 );//dowen left
                        cross[3].position = Vector2f((j + 1) * CS-5  , i * CS+5 );//up right
                        cross[0].color = cross[1].color = cross[2].color = cross[3].color = Color::Red;//colors
                       
                        window.draw(cross);//draW x
                    }
                    else if (board[i][j] == Player::Circle) {//o draw
                        CircleShape circle(CS /2 -10 );
                        circle.setPosition(j * CS + 10, i * CS + 10);
                        circle.setOutlineThickness(4);
                        circle.setOutlineColor(Color::Blue);
                        circle.setFillColor(Color::Transparent);
                        window.draw(circle);
                    }
                }
            }

            window.display();
        }

        system("cls");
        // Game ended, determine result
        string result;
        if (winner != Player::None) {
            if (winner == Player::Cross)
            {
                cout << yel;
                result = "Cross wins!";
            }
            else
            {
                cout << yel;
                result = "Circle wins!";
            }
        }
        else {
            cout << red;
            result = "It's a draw!";
        }

        cout << result<<reset << endl;
        cout << cyan << " X "<<blue<<"|"<< cyan <<" O "<<blue<<"\n---+---\n "<< cyan <<x<<blue<<" | "<< cyan <<o<<endl;
        // Ask if the user wants to play again
        cout <<green<< "Do you want to play again? (Y/N):(note if you pressed any kay else Y it = NO): "<<reset;
        char choice;
        cin >> choice;
        if (choice != 'Y' && choice != 'y') {
            window.close();// Close window button clicked
            sleep(milliseconds(0));
            return 0;
        }
    }

    return 0;}
 

















































            //140 resultMsg = (winner == Player::Cross) ? "Cross wins!" : "Circle wins!";
            //85 board[row][col] = isCrossTurn ? Player::Cross : Player::Circle;