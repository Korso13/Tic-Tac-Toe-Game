/*
=========================================================================================================
Tic Tac Toe Game by Tim Corso
The first real gaming piece in C++ for me (hopefully not the last)
=========================================================================================================
*/

/*
toDo list:
1) Modify TTT_field and game() to create dynamic fields.
2) Modify init to roll initiative, recieve VictoryRow size input
3) create winCheck for field_size > 3
4) add separate function for AI gameplay or modify the existing game()

5) add fancy render for fields smaller than X (optional)
6) add "crazyhouse" mutator (optional)
*/

#include <iostream>
#include <string>
#include "add.h"
using namespace std;

enum TTT : char { X = 'X', O = 'O', EMTY = '·' };
struct TTT_field
{
    short int game_mode; // 0 - pvp, 1 - AI
    short int diff = 0;
    short int field_size = 3;
    TTT fieldsmall[3][3] = { {EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY} };
    TTT fieldmedium[5][5] = { {EMTY,EMTY,EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY,EMTY,EMTY}, {EMTY,EMTY,EMTY,EMTY,EMTY}, {EMTY,EMTY,EMTY,EMTY,EMTY} };
    string p1 = ""; //Имена игроков
    string p2 = "";
    TTT p1_f; //Чем играет первый игрок?
    TTT p2_f;
    short int VictoryRowSize = 3;
    int game_state = 0;
    string turn; //Чей ход
    string winner;
};

void game(TTT_field &game_data) //Основная игровая логика для PvP режима
{
    std::cout << std::endl;
    std::cout << "Ход игрока " << game_data.turn << std::endl;
    fieldPrint(game_data);
    size_t x{ 0 }, y{ 0 };
    for (;;) //Ввод и проверка координат
    {
        std::cout << "Введите координаты для совершения хода (строка и столбик, через пробел или по очереди): ";
        std::cin >> x;
        cinCheck();
        std::cin >> y;
        cinCheck();

        x--; //корректировка координат под индекс массива
        y--;
        if (game_data.fieldsmall[x][y] != EMTY) //need branch for bigger fields
            std::cout << "Ячейка занята! Выберите другую!" << std::endl;
        else
        {
            if ((x >= 0 && x < game_data.field_size) && (y >= 0 && y < game_data.field_size)) //проверка корректности координат
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

    if (game_data.field_size == 3) 
        game_data.fieldsmall[x][y] = (game_data.turn == game_data.p1) ? game_data.p1_f : game_data.p2_f;
    else //!!stub for custom field size!! 
        game_data.fieldmedium[x][y] = (game_data.turn == game_data.p1) ? game_data.p1_f : game_data.p2_f;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    TTT_field game_data;
    init(game_data);
    do
    {
        game_data.winner = " "; //Подготовка к старту новой игры со старыми установками
        game_data.turn = game_data.p1;
        //очистка полей !!Переделать под динамические поля с очисткой памяти!!
        for (size_t i = 0; i < game_data.field_size; i++)
        {
            for (size_t k = 0; k < game_data.field_size; k++)
            {
                game_data.fieldsmall[i][k] = EMTY;
                game_data.fieldmedium[i][k] = EMTY;
            }
        }

        do
        {
            game(game_data);
            game_data.game_state = winCheck(game_data);
            if (game_data.game_state == 2) //проверка на ничью
            {
                break;
            }
            else
            {
                if (game_data.game_state == 0) //Проверка - привёл ли очередной ход к победе
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
        if (game_data.game_state == 2) //Объявление ничей или победителя
        {
            std::cout << "Ничья!" << std::endl;
        }
        else if (game_data.game_state == 1) //!! добавить проверку на ИИ
            std::cout << "Победил игрок: " << game_data.winner << "!" << std::endl;

      
    } while (ReMatch() != 1);//Предложение реванша
    
    //Debugging - to be deleted
    cout << "game_mode " << game_data.game_mode << endl;
    cout << "difficulty " << game_data.diff << endl;
    cout << "field_size " << game_data.field_size << endl;
    cout << "p1 name " << game_data.p1 << endl;
    cout << "p2 name " << game_data.p2 << endl;
    cout << "p1 figure " << game_data.p1_f << endl;
    cout << "p2 figure " << game_data.p2_f << endl;
    fieldPrint(game_data);
    return 0;
}
