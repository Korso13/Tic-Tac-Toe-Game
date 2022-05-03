/*
=========================================================================================================
Tic Tac Toe Game (v 1.1) by Tim Corso
The first real gaming piece in C++ for me (hopefully not the last)
=========================================================================================================
 
To do list:
- add "crazyhouse" mutator (reshuffles field every N turns)
*/

#include <iostream>
#include <string>
#include "add.h"

using namespace std;

enum TTT : char { X = 'X', O = 'O', EMTY = '·' };

//Main structure for keeping game data
#pragma pack(push, 1)
struct TTT_field
{
    short int game_mode = 1; // 0 - pvp, 1 - AI
    short int diff = 0;
    short int field_size = 3;
    TTT** field = nullptr;
    string p1 = ""; //player names
    string p2 = "";
    TTT p1_f = X; //player figures
    TTT p2_f = O;
    short int VictoryRowSize = 3;
    int game_state = 0;
    string turn; //whose turn is it?
    string winner;
};

struct coord
{
    size_t x = 0;
    size_t y = 0;
    short int flag = 0; //coords characteristics for calling functions
    short int EMTY_n = 0; //number of empty cells
};
#pragma pack(pop)

//Game logic for making moves
inline void game(TTT_field& game_data)
{
    coord pl;

    //human player move
    if (game_data.game_mode == 0 || (game_data.game_mode == 1 && game_data.turn == game_data.p1)) 
    {
        clear();
        fieldPrint(game_data);
        cout << endl;
        cout << "Ход игрока " << game_data.turn << " (" << ((game_data.turn == game_data.p1) ? game_data.p1_f : game_data.p2_f) << ")" << endl;
        for (;;) //coordinates input and check
        {
            cout << "Введите координаты для совершения хода (строка и столбик, через пробел или по очереди): ";
            cin >> pl.y;
            cinCheck();
            cin >> pl.x;
            cinCheck();

            pl.y--; //adapt coords for field indices
            pl.x--;
            if (game_data.field[pl.y][pl.x] != EMTY) //need branch for bigger fields
                cout << "Ячейка занята! Выберите другую!" << endl;
            else
            {
                if ((pl.y >= 0 && pl.y < game_data.field_size) && (pl.x >= 0 && pl.x < game_data.field_size)) //check if coords are ok
                {
                    break;
                }
                else
                {
                    cout << "Неправильный ввод!" << endl;
                    continue;
                }
            }
        }
        game_data.field[pl.y][pl.x] = (game_data.turn == game_data.p1) ? game_data.p1_f : game_data.p2_f;
    }
    //AI's move
    else if (game_data.game_mode == 1 && game_data.turn == game_data.p2) 
    {
        fieldPrint(game_data);
        cout << endl;
        cout << "Ход ИИ" << endl;
        AI_Proc(game_data);
    }  
}

int main()
{
    setlocale(LC_ALL, "Russian");
    TTT_field game_data;
    init(game_data);
    do
    {
        game_data.winner = " "; //reset winner in case of rematch
        rollInitiative(game_data);

        //cleaning or initializing game field
        {
            if (game_data.field == nullptr)
            {
                fieldInit(game_data);
            }
            else
            {
                for (size_t i = 0; i < game_data.field_size; i++)
                {
                    delete[] game_data.field[i];
                }
                delete[] game_data.field;
                game_data.field = nullptr;
                fieldInit(game_data);
            }
        }

        //main game loop
        do
        {
            game(game_data); //player or AI makes move
            game_data.game_state = winCheck(game_data);
            if (game_data.game_state == 2) //draws checks
            {
                break;
            }
            else
            {
                if (game_data.game_state == 0) //Victory checks
                {
                    if (game_data.turn == game_data.p1) //players take turns
                        game_data.turn = game_data.p2;
                    else
                        game_data.turn = game_data.p1;
                }
                else if (game_data.game_state == 1)
                    game_data.winner = game_data.turn; //relay winner name if one is achieved
            }
        } while (game_data.game_state == 0);

        clear();
        fieldPrint(game_data);
        if (game_data.game_state == 2) //draw declaration
        {
            cout << "Ничья!" << endl;
            cout << endl;
            fieldPrint(game_data);
        }
        else if (game_data.game_state == 1) //winner declaration
        {
            if (game_data.game_mode == 1 && game_data.winner == game_data.p2)
                cout << "Победил ИИ!" << endl;
            else
                cout << "Победил игрок: " << game_data.winner << "!" << endl;
            cout << endl;
            fieldPrint(game_data);
        }
    } while (ReMatch() != 1);//Offer a rematch with same conditions. 1 turn player is rerolled
   
    return 0;
}
