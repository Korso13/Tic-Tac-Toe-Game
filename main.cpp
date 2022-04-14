#include <iostream>

enum TTT : char {X = 'X', O = 'O', EMTY = '·'};
struct TTT_field
{
    TTT field[3][3] = { {EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY} };
    char p1[32] = "Игрок 1";
    char p2[32] = "Игрок 2";;
    char p1_ip[16] = "127.0.0.1";
    char p2_ip[16] = "127.0.0.1";
    unsigned short Xs_player : 1;
    unsigned short Os_player : 1;
    bool game_started = false;
    bool game_finished = false;
    unsigned short int turn : 4;
    bool winner = false;
};

void init()
{
}

void AI_Proc()
{
}

void game()
{
}

int main()
{
  setlocale(LC_ALL, "Russian");
  /* Заготовка под вывод поля 3х3
    int i1 = 0;
    int i2 = 0;
    for (i1 = 0; i1 < 3; i1++)
    {
        for (i2 = 0; i2 < 3; i2++)
        {
            std::cout << field[i1][i2] << " ";
        }
        std::cout << std::endl;
        i2 = 0;
    } */
  return 0;
}
