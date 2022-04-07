#include <iostream>
const int SIZE = 30;
//2. создаём перечисление для игры (типизацию char подсмотрел в интернете)
enum TTT : char {X = 'X', O = 'O', EMTY = '·'};
//4. создаём структуру для игры
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
//5. Структура с объединением и битовыми флагами
union MyData
{
    int i;
    float fl;
    char ch;
};
struct MyVariant
{
    MyData val;
    unsigned short isInt : 1;
    unsigned short isFloat : 1;
    unsigned short isChar : 1;
};



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
    /* Проверка для себя
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

    //5. Тестируем структуру MyVariant
    MyVariant variant;
    variant.val.ch = 'g';
    variant.isChar = 1;
    variant.isInt = 0;
    variant.isFloat = 0;
    
    std::cout << "В переменной variant хранится значение: " << variant.val.ch << std::endl;
    if (variant.isInt == 1) //Синтаксис подсмотрел из Шилдта
    {
        std::cout << "Переменная variant целочисленная! " << std::endl;
    }
        else 
        {
        if (variant.isFloat == 1)
            std::cout << "Переменная variant с плавающей точкой! " << std::endl;
            else std::cout << "Переменная variant символьная! " << std::endl;
        }

    //5*. В идеале бы конечно проверять MyVariant так (typeid опять же подсмотрел)
    float Var1 = 242.324; //можно переписать под любой из трех типов данных

    if (typeid(Var1) == typeid(variant.val.i))
    {
        variant.val.i = Var1;
        variant.isInt = 1;
        std::cout << "В переменной variant хранится значение: " << variant.val.i << std::endl;
        std::cout << "Переменная variant целочисленная! " << std::endl;
    }
    else if (typeid(Var1) == typeid(variant.val.fl))
    {
        variant.val.fl = Var1;
        variant.isFloat = 1;
        std::cout << "В переменной variant хранится значение: " << variant.val.fl << std::endl;
        std::cout << "Переменная variant с плавающей точкой! " << std::endl;
    }
    else 
    {
        variant.val.ch = Var1;
        variant.isChar = 1;
        std::cout << "В переменной variant хранится значение: " << variant.val.ch << std::endl;
        std::cout << "Переменная variant символьная! " << std::endl;
    }   
    return 0;
}
