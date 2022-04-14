#include <iostream>
#include <string>
using namespace std;

enum TTT : char {X = 'X', O = 'O', EMTY = '·'};
struct TTT_field
{
    TTT field[3][3] = { {EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY} };
    string p1 = ""; //Имена игроков
    string p2 = "";
    char p1_ip[16] = "127.0.0.1";
    char p2_ip[16] = "127.0.0.1";
    TTT p1_f; //Чем играет первый игрок?
    TTT p2_f;
    bool game_started = false;
    bool game_finished = false;
    unsigned short int turn : 4;
    bool winner = false;
};

void init() //Инициализация игры. Вввод исходных данных. [Почти дописан]
{
   cout << "Добро пожаловать в игру 'крестики-нолики'!" << endl;
   //вставить точку goto
   cout << "Выберите режим игры: PvP (игрок против игрока) или AI (против компьютера): ";
   enum gmode : short int {PvP = 1, AI = 2};
   gmode game_mode;
   TTT_field game_data;
   cin >> game_mode;
   cout << endl;
   short int diff;
   short_int field_size;
   if (game_mode == 2)
       {
       cout << "Выберите сложность. 1 - простая, 2 - средняя, 3 - сложная, 4 - Hurt Me Plenty: ";
       cin >> diff;
       cout << endl;
       if (diff == 4)  //Если не получится реализовать, можно убрать
           field_size = 5;
       else
           field_size = 3;
       }
   else 
       {
       cout << "Введите имя первого игрока: ";
       cin >> game_data.p1;
       cout >> "\nЧем играет первый игрок(X/O)? " 
       cin >> game_data.p1_f;
       cout << "Введите имя второго игрока: ";
       cin >> game_data.p2;
       if (game_data.p1_f == X)
           game_data.p2_f = O;
       else game_data.p2_f = X;
       }
    char y_n;
    cout << "Приступим (Y/N)? ";
    cin >> y_n;
    if (y_n == N)
    //вставить goto на начало функции
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
