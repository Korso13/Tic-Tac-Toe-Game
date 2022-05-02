/*
=========================================================================================================
Tic Tac Toe Game by Tim Corso
The first real gaming piece in C++ for me (hopefully not the last)
=========================================================================================================
*/

/*
toDo list:
1) починить проверку победы
2) Дополнительный флаг в coord - кол-во пустых ячеек в ходе переданном rowsCheck. 
3) Сделать проверку в AI на выбор оптимального из ходов. Возможно нужен массив coord

*) CODE CLEANUP!!!


*) add "crazyhouse" mutator (optional)
*/

#include <iostream>
#include <string>
#include "add.h"

using namespace std;

enum TTT : char { X = 'X', O = 'O', EMTY = '·' };

//Main structure for keeping game data
struct TTT_field
{
    short int game_mode = 1; // 0 - pvp, 1 - AI
    short int diff = 0;
    short int field_size = 3;
    TTT** field = nullptr;
    string p1 = ""; //Имена игроков
    string p2 = "";
    TTT p1_f = X; //Чем играет первый игрок?
    TTT p2_f = O;
    short int VictoryRowSize = 3;
    int game_state = 0;
    string turn; //Чей ход
    string winner;
};

struct coord
{
    size_t x = 0;
    size_t y = 0;
    short int flag = 0;
};

//Основная игровая логика
void game(TTT_field& game_data) 
{
    std::cout << std::endl;
    coord pl;

    //human player move
    if (game_data.game_mode == 0 || (game_data.game_mode == 1 && game_data.turn == game_data.p1)) 
    {
        cout << "Ход игрока " << game_data.turn << endl;
        fieldPrint(game_data);
        cout << endl;
        for (;;) //Ввод и проверка координат
        {
            std::cout << "Введите координаты для совершения хода (строка и столбик, через пробел или по очереди): ";
            std::cin >> pl.y;
            cinCheck();
            std::cin >> pl.x;
            cinCheck();

            pl.y--; //корректировка координат под индекс массива
            pl.x--;
            if (game_data.field[pl.y][pl.x] != EMTY) //need branch for bigger fields
                std::cout << "Ячейка занята! Выберите другую!" << std::endl;
            else
            {
                if ((pl.y >= 0 && pl.y < game_data.field_size) && (pl.x >= 0 && pl.x < game_data.field_size)) //проверка корректности координат
                {
                    break;
                }
                else
                {
                    std::cout << "Неправильный ввод!" << std::endl;
                    continue;
                }
            }
        }
        game_data.field[pl.y][pl.x] = (game_data.turn == game_data.p1) ? game_data.p1_f : game_data.p2_f;
    }
    //AI's move
    else if (game_data.game_mode == 1 && game_data.turn == game_data.p2) 
    {
        cout << "Ход ИИ" << endl;
        fieldPrint(game_data);
        cout << endl;
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
        game_data.winner = " "; //Подготовка к старту новой игры со старыми установками
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
            if (game_data.game_state == 2) //проверка на ничью
            {
                break;
            }
            else
            {
                if (game_data.game_state == 0) //Проверка - не привёл ли очередной ход к победе
                {
                    if (game_data.turn == game_data.p1) //Передача хода другому игроку
                        game_data.turn = game_data.p2;
                    else
                        game_data.turn = game_data.p1;
                }
                else if (game_data.game_state == 1)
                    game_data.winner = game_data.turn; //В случае выигрыша - передаём имя победителя; заканчиваем цикл
            }
        } while (game_data.game_state == 0);

        fieldPrint(game_data);
        if (game_data.game_state == 2) //Объявление ничьей 
        {
            std::cout << "Ничья!" << std::endl;
            fieldPrint(game_data);
        }
        else if (game_data.game_state == 1) //или победителя
        {
            if (game_data.game_mode = 1 && game_data.winner == game_data.p2)
                std::cout << "Победил ИИ!" << std::endl;
            else
                std::cout << "Победил игрок: " << game_data.winner << "!" << std::endl;
            fieldPrint(game_data);
        }
    } while (ReMatch() != 1);//Предложение реванша
    
    //Debugging - to be deleted
    /*cout << "game_mode " << game_data.game_mode << endl;
    cout << "difficulty " << game_data.diff << endl;
    cout << "field_size " << game_data.field_size << endl;
    cout << "p1 name " << game_data.p1 << endl;
    cout << "p2 name " << game_data.p2 << endl;
    cout << "p1 figure " << game_data.p1_f << endl;
    cout << "p2 figure " << game_data.p2_f << endl;*/
    return 0;
}
