#include <iostream>
#include <string>
using namespace std;

void cinCheck()
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(32767, '\n');
    }
}

enum TTT : char { X = 'X', O = 'O', EMTY = '·' };
struct TTT_field
{
    short int game_mode; // 0 - pvp, 1 - AI
    short int diff = 0;
    short int field_size = 0;
    TTT fieldsmall[3][3] = { {EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY} };
    TTT fieldmedium[5][5] = { {EMTY,EMTY,EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY,EMTY,EMTY},{EMTY,EMTY,EMTY,EMTY,EMTY}, {EMTY,EMTY,EMTY,EMTY,EMTY}, {EMTY,EMTY,EMTY,EMTY,EMTY} };
    string p1 = ""; //Имена игроков
    string p2 = "";
    char p1_ip[16] = "127.0.0.1"; //stub
    char p2_ip[16] = "127.0.0.1"; //stub
    TTT p1_f; //Чем играет первый игрок?
    TTT p2_f;
    int game_state = 0;
    string turn; //Чей ход
    string winner;
};

//===================================================================================================
//Инициализация игры. Вввод исходных данных. 
//===================================================================================================

void init(TTT_field &game_data)
{
    // TTT_field game_data - Основной блок данных игры. Заполняем то что нужно на старте.
    cout << "Добро пожаловать в игру 'крестики-нолики'!" << endl;
    string gm;

login:  //Точка входа если данные введены неправильно
    game_data.game_mode = 2;
    //Режим игры
    while (game_data.game_mode < 0 || game_data.game_mode > 1)
    {
        cout << "Выберите режим игры: PvP (игрок против игрока) или AI (против компьютера): ";
        cin >> gm;
        cinCheck();
        if (gm == "PvP" || gm == "pvp")
            game_data.game_mode = 0;
        else
            if (gm == "AI" || gm == "ai")
                game_data.game_mode = 1;
            else cerr << "Некорректный ввод!" << endl;
    }
    cout << endl;

    //Настройка ИИ
    if (game_data.game_mode == 1)
    {
        game_data.diff = 0;  //Защита от проскальзывания при перезапуске init
        while (game_data.diff < 1 || game_data.diff > 4)
        {
            cout << "Выберите сложность. 1 - простая, 2 - средняя, 3 - сложная, 4 - Hurt Me Plenty: ";
            cin >> game_data.diff;
            cinCheck();
            cout << endl;
        }

        game_data.p1 = ""; //защита на случай перезапуска init
        cout << "Введите имя игрока: "; //Настройка игрока против ИИ с проверкой корректности
        cin >> game_data.p1;
        cinCheck();
        game_data.p2 = "ИИ";
        char temp1 = 0; //защита на случай перезапуска init
        do
        {
            cout << "\nЧем играет игрок(X/O)? ";
            cin >> temp1;
            cinCheck();
            if (temp1 == 'X' || temp1 == 'Х' || temp1 == 'x' || temp1 == 'х')
            {
                game_data.p1_f = X;
                game_data.p2_f = O;
                break;
            }
            else if (temp1 == 'O' || temp1 == 'О' || temp1 == 'o' || temp1 == 'о')
            {
                game_data.p1_f = O;
                game_data.p2_f = X;
                break;
            }
            else
            {
                cerr << "Неверный формат!" << endl;
                temp1 = 1;
            }
        } while (temp1 == 1); //конец настройки имени игрока против ИИ
    } //конец настройки сложности ИИ

//Настройка игроков (pvp mode)
    else
    {
        char temp2 = 0;
        game_data.p1 = ""; //Защита на случай перезапуска init
        cout << "Введите имя первого игрока: ";
        cin >> game_data.p1;
        cinCheck();
    inputErr1:
        cout << "\nЧем играет первый игрок(X/O)? ";
        cin >> temp2; //добавить обнуление на случай повторного ввода
        cinCheck();
        switch (temp2)
        {
        case 'X':
        case 'x':
        case 'х':
        case 'Х':
            game_data.p1_f = X;
            break;
        case 'O':
        case 'o':
        case 'о':
        case 'О':
            game_data.p1_f = O;
            break;
        default:
        {
            cerr << "Неверный формат!" << endl;
            goto inputErr1;
        }
        }
        cout << endl;
        game_data.p2 = ""; //Защита на случай перезапуска init
        cout << "Введите имя второго игрока: ";
        cin >> game_data.p2;
        cinCheck();
        if (game_data.p1_f == X)
            game_data.p2_f = O;
        else game_data.p2_f = X;
    }//конец ввода данных об игроках
    cout << endl;

    //============================================================================
    //Настройка размера игрового поля. Если не получится реализовать, можно убрать
    //============================================================================
    if (game_data.game_mode == 1 && game_data.diff == 4)
        game_data.field_size = 5;
    else
    {
        for (;;)
        {
            cout << "Выберите размер игрового поля (3, 5): ";
            cin >> game_data.field_size;
            cinCheck();
            if (game_data.field_size == 3 || game_data.field_size == 5)
                break;
            else
            {
                cout << "Некорректный ввод!" << endl;
            }
        }
    }
    //==============================================================================

    //Последние приготовления
    char y_n = 0;
    for (;;)
    {
        cout << "Приступим (Y/N)? ";
        cin >> y_n;
        if (y_n == 'Y' || y_n == 'y' || y_n == 'У' || y_n == 'у')
        {
            cout << endl;
            break;

        }
        else if (y_n == 'N' || y_n == 'n' || y_n == 'Н' || y_n == 'н')
        {
            cout << endl;
            goto login;
        }
    }
    return;
}

void fieldPrint(TTT_field& game_data)
{
    //Вывод поля 3х3
    if (game_data.field_size == 3)
    {
        std::cout << "  " << "1 " << "2 " << "3 " << std::endl;
        for (int i1 = 0; i1 < 3; i1++)
        {
            std::cout << (i1 + 1) << " ";
            for (int i2 = 0; i2 < 3; i2++)
            {
                std::cout << game_data.fieldsmall[i1][i2] << " ";
            }
            std::cout << std::endl;
        }
    }
    else
        //Вывод поля 5х5
    {
        for (int i1 = 0; i1 < 5; i1++)
        {
            for (int i2 = 0; i2 < 5; i2++)
            {
                std::cout << game_data.fieldmedium[i1][i2] << " ";
            }
            std::cout << std::endl;
        }
    }
}
//  универсальный проверщик победы, но не ничей:
   //  Проверяем подпрограммами 4 сценария победы. Плюсуем аккумулятор до 3:
   //  а) по-диагонали налево-вниз
   //  б) Вертикально вниз 
   //  в) по-диагонали направо-вниз
   //  г) по горизонтали ВПРАВО. 
   //  Ограничитель по числу оставшихся строк/столбцов до края поля


//==================================================================================================
//Проверка выполнения условий выигрыша. Возврат true - победа игрока чей ход был последним!
//==================================================================================================
int winCheck(TTT_field game_data) //0 - игра продолжается, 1 - произошла победа, 2 - ничья
{
    size_t draw_count = 0; //Если = 8 >> return 2;
    size_t countO, countX, count_0;

    for (size_t i = 0; i < game_data.field_size; i++) //проверка по строкам
    {
        countO = 0;
        countX = 0;
        count_0 = 0;
        for (size_t k = 0; k < game_data.field_size; k++) //считаем значения в строке
        {
            switch(game_data.fieldsmall[i][k])
            {
                case 'X':
                    countX++;
                    break;
                case 'O':
                    countO++;
                    break;
                case 'EMTY':
                    count_0++;
                    break;
            }
        }
        if (countX == 3 || countO == 3)
            return 1;
        else if (countX > 0 && countO > 0)
            draw_count++;
    }

    for (size_t k = 0; k < game_data.field_size; k++) //проверка по столбцам
    {
        countO = 0;
        countX = 0;
        count_0 = 0;
        for (size_t i = 0; i < game_data.field_size; i++) //считаем значения в столбце
        {
            switch (game_data.fieldsmall[i][k])
            {
            case 'X':
                countX++;
                break;
            case 'O':
                countO++;
                break;
            case 'EMTY':
                count_0++;
                break;
            }
        }
        if (countX == 3 || countO == 3)
            return 1;
        else if (countX > 0 && countO > 0)
            draw_count++;
    }

    countO = 0; //проверка по диагонали 1
    countX = 0;
    count_0 = 0;
    for (size_t i = 0; i < game_data.field_size; i++) 
    {
            switch (game_data.fieldsmall[i][i])
            {
            case 'X':
                countX++;
                break;
            case 'O':
                countO++;
                break;
            case 'EMTY':
                count_0++;
                break;
            }
    }
    if (countX == 3 || countO == 3)
        return 1;
    else if (countX > 0 && countO > 0)
        draw_count++;

    countO = 0; //проверка по диагонали 2
    countX = 0;
    count_0 = 0;
    for (size_t i = 0; i < game_data.field_size; i++)
    {
        switch (game_data.fieldsmall[i][(game_data.field_size - 1) - i]) //подсчёт значений по диагонали из правого верхнего угла
        {
        case 'X':
            countX++;
            break;
        case 'O':
            countO++;
            break;
        case 'EMTY':
            count_0++;
            break;
        }
    }
    if (countX == 3 || countO == 3)
        return 1;
    else if (countX > 0 && countO > 0)
        draw_count++;

    //проверка на ничью, выход из функции
    if (draw_count == 8)
        return 2; //ничья
    else
        return 0;
}
