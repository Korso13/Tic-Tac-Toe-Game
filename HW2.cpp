#include <iostream>
const int SIZE = 30;
//2. создаём перечисление для игры ·
enum TTT {X = 'X', O = 'O', EMTY = '·'};

int main()
{
    setlocale(LC_ALL, "Russian");
    //1. инициализируем переменные
    unsigned short int nSI = 3;
    auto nLL = 123'125'125'578LL;
    char a = 'G';
    bool lFlag = true;
    float b = 1234.124789f;
    double bb = 34312.5559793;
    //3. создаём двумерный массив - поле для игры
    TTT field[3][3] = { {EMTY,X,X},{O,EMTY,X},{O,EMTY,O} };
    int i1 = 0;
    int i2 = 0;
    for (i1 = 0; i1 < 3; i1++)
    {
        for (i2 = 0; i2 < 3; i2++)
        {
            std::cout << field[i1][i2];
        }
        std::cout << std::endl;
        i2 = 0;
    }

    return 0;
}
