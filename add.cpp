#include <iostream>
#include <string>
#include <random> 
#include <stdlib.h>
#include <chrono>

using namespace std;

//==================================================================================================
//Enums and Structures
//==================================================================================================
enum TTT : char { X = 'X', O = 'O', EMTY = '·' };
enum analysis_flag { VOID, NO_ROW, VICTORY_ROW, PRIORITY};

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
    int EMTY_n = 0;
};

struct RowDataBuffer
{
    short int buff1[5]{ 0 }; 
    short int buff2[5]{ 0 };
    short int buff3[5]{ 0 };
    short int buff4[5]{ 0 };
    analysis_flag buff1_flag;
    analysis_flag buff2_flag;
    analysis_flag buff3_flag;
    analysis_flag buff4_flag;
};

//==================================================================================================
//Small service functions
//==================================================================================================

void cinCheck() //проверка ввода общая
{
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(32767, '\n');
    }
}

//clear screen
void clear() // функция очистки экрана
{
    cout << "\x1B[2J\x1B[H"; 
}

int32_t RollRandom(int32_t min, int32_t max) //Генератор случайных чисел от мин до макс
{
    const static auto seed = chrono::system_clock::now().time_since_epoch().count();
    static mt19937_64 generator(seed);
    uniform_int_distribution<int32_t> dis(min, max);
    return dis(generator);
}

//Get random coordinates
coord getRandomCoord(short int f_size)
{
    coord c;
    c.x = RollRandom(0, (f_size - 1));
    c.y = RollRandom(0, (f_size - 1));
    return c;
}

//Roll for initiative!!
void rollInitiative(TTT_field& game_data)
{
    if (RollRandom(0, 100) >= 50)
        game_data.turn = game_data.p2;
    else
        game_data.turn = game_data.p1;
}

//===================================================================================================
//Инициализация игры. Вввод исходных данных. 
//===================================================================================================

void init(TTT_field& game_data)
{
    // TTT_field game_data - Основной блок данных игры. Заполняем то что нужно на старте.
    cout << "Добро пожаловать в игру 'крестики-нолики'!" << endl;
    string gm; //Temp variable to interpret user input

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
            cout << "Выберите сложность. 1 - простая, 2 - средняя, 3 - сложная, 4 - Hurt Me Plenty (на кастомных полях и условиях): ";
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
    else if (game_data.game_mode == 0)
    {
        char temp2;
        game_data.p1 = ""; //Защита на случай перезапуска init
        cout << "Введите имя первого игрока: ";
        cin >> game_data.p1;
        cinCheck();
    inputErr1:
        temp2 = 0;
        cout << "\nЧем играет первый игрок(X/O)? ";
        cin >> temp2;
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

    
    //Setting up game field size and victory requirements
    if ((game_data.game_mode == 1 && game_data.diff == 4) || game_data.game_mode == 0)
    {
        for (;;) //game field size
        {
            cout << "Выберите размер игрового поля (от 3 и больше): ";
            cin >> game_data.field_size;
            cinCheck();
            if (game_data.field_size > 3)
                break;
            else
            {
                cout << "Некорректный ввод!" << endl;
            }
        }
        cout << endl;
        for (;;) //victory requirements
        {
            cout << "Сколько нужно собрать Х/О в ряд для победы (не меньше трех, но не больше размера поля): ";
            cin >> game_data.VictoryRowSize;
            cinCheck();
            if ((game_data.VictoryRowSize >= 3) && (game_data.VictoryRowSize <= game_data.field_size))
                break;
            else
            {
                cout << "Некорректный ввод!" << endl;
            }
        }  
        cout << endl;
    }

    //Roll for initiative!!
    rollInitiative(game_data);

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

//=================================================================================================
//initializing dynamic game field
//=================================================================================================

void fieldInit(TTT_field& game_data)
{
    game_data.field = new (std::nothrow) TTT * [game_data.field_size];
    for (size_t i = 0; i < game_data.field_size; i++)
    {
        game_data.field[i] = new (std::nothrow) TTT [game_data.field_size];
    }
    for (size_t y = 0; y < game_data.field_size; y++)
    {
        for (size_t x = 0; x < game_data.field_size; x++)
        {
            game_data.field[y][x] = EMTY;
        }
    }
}

//=================================================================================================
//Печать игрового поля
//=================================================================================================

void fieldPrint(TTT_field& game_data)
{
    cout << "  ";
    for (size_t i = 1; i <= game_data.field_size; i++) //print x coords
    {
        cout << "| " << i << " ";
    }
    cout << endl;

    for (int i = 0; i < game_data.field_size; i++)//print rest of field
    {
        for (size_t j = 0; j <= game_data.field_size; j++) //print separator ahead of new line
        {
            cout << "----";
        }
        cout << endl;

        cout << (i + 1) << " ";  //print y coords
        for (int k = 0; k < game_data.field_size; k++) //print i line
        {
            cout << "| " << game_data.field[i][k] << " ";
        }
        cout << endl;
    }
}


coord rowsCheck(TTT_field& game_data, int y, int x, bool winCheck = false); //protptype for use in below functions

//==================================================================================================
//Victory and Draw checks function 
//Returns 0 if game continues, 1 - if victory happened with last turn, 2 - if it's draw
//==================================================================================================

int winCheck(TTT_field game_data)
{
    coord checkRes;
    int drawRows = 0;
    for (int y = 0; y < game_data.field_size; y++)
    {
        for (int x = 0; x < game_data.field_size; x++)
        {
            checkRes = rowsCheck(game_data, y, x, true);
            if (checkRes.flag == 2) //checks if victory row was found
            {
                return 1;
            }
            if (checkRes.flag == 0) //checks if no valid moves were found for this cell
            {
                drawRows++;
            }
        }
    }

    //Check if draws found in every scenario
    if (drawRows == (game_data.field_size * game_data.field_size))
    {
        return 2;
    }
    else
        return 0;
}

//==================================================================================================
//AI Logic. Makes move, doesn't return anything
//==================================================================================================

void AI_Proc(TTT_field& game_data)
{
    //Checks for imminent victory of AI or user. Returns only when either found (and if procs worked on normal diff)!!
    int ai_temp1 = 0; //win checks buffer variable
    if (game_data.diff > 1)
    {
        for (size_t i = 0; i < game_data.field_size; i++)
            for (size_t k = 0; k < game_data.field_size; k++)
                if (game_data.field[i][k] == EMTY)
                {
                    if (game_data.diff == 2) //Normal. Chance to complete row 70%. Chance to react to threat 25% (80% if it completes own row). 
                    {
                        game_data.field[i][k] = game_data.p2_f; //AI figure placement
                        if (winCheck(game_data) == 1)
                        {
                            game_data.field[i][k] = game_data.p1_f;
                            ai_temp1 = winCheck(game_data);
                            game_data.field[i][k] = game_data.p2_f;
                            if (ai_temp1 == 1 && RollRandom(0, 100) >= 20) //80% chance to respond to player's threat and complete own row
                                return;
                            else if (RollRandom(0, 100) >= 30) //general 70% chance to use victory option to complete row
                            {
                                return; 
                            }
                        }
                        else if (ai_temp1 == 1 && RollRandom(0, 100) >= 75) //25% chance to react to threat (but not complete own row) check
                            return;
                        else //nothing proc'ed
                        {
                            game_data.field[i][k] = EMTY;
                            break;
                        }
                    } //End of bloc for normal difficulty

                    else if (game_data.diff >= 3)
                    {
                        game_data.field[i][k] = game_data.p2_f;
                        if (winCheck(game_data) == 1)
                        {
                            return;
                        } //end of imminent victory check
                        else
                        {
                            game_data.field[i][k] = game_data.p1_f;
                            ai_temp1 = winCheck(game_data);
                            game_data.field[i][k] = game_data.p2_f;
                                if (ai_temp1 == 1)
                                {
                                    return;
                                } //end of imminent player victory check
                                else
                                {
                                    game_data.field[i][k] = EMTY;
                                } //end of top difficulty checks for imminent victory
                        }
                    }
                }
    } //end of diff > 1 checks for imminent victory

    //all easy-mode mechanics (standalone subfunction. Inevitable return if diff == 1!!)
    if (game_data.diff == 1) 
    {
        coord ai_c = getRandomCoord(game_data.field_size);
        for (;;)
        {
            short int itr = 0;
            if (game_data.field[ai_c.y][ai_c.x] == EMTY)
            {
                game_data.field[ai_c.y][ai_c.x] = game_data.p2_f;
                return;
            }
            else
            {
                ai_c = getRandomCoord(game_data.field_size);
                itr++;
            }
            if (itr > (game_data.field_size * game_data.field_size * 4))
            {
                cout << "ИИ Сдаётся!" << endl;
                game_data.turn = game_data.p1;
                game_data.game_state = 1;
                return; //redundancy break after too many iterations
            }
        }
    }//end of easy win ai_checks. 

    //Scenarios for game's begining (diffs 2, 3) - only classic field size!!!
    if (game_data.field_size == 3)
    {
        //Check if central cell in 3x3 field is empty
        if ((game_data.diff == 3 && game_data.field[1][1] == EMTY) || (game_data.diff == 2 && (RollRandom(0, 100) >= 50) && game_data.field[1][1] == EMTY))
        {
            game_data.field[1][1] = game_data.p2_f;
            return;
        }
        //hard diff checks if centrall cell occupied
        else if (game_data.diff == 3 && game_data.field[1][1] != EMTY)
        {
            if (game_data.field[0][2] == EMTY)
            {
                game_data.field[0][2] = game_data.p2_f;
                return;
            }
            else if (game_data.field[2][2] == EMTY)
            {
                game_data.field[2][2] = game_data.p2_f;
                return;
            }
            else if (game_data.field[2][0] == EMTY)
            {
                game_data.field[2][0] = game_data.p2_f;
                return;
            }
            else if (game_data.field[0][0] == EMTY)
            {
                game_data.field[0][0] = game_data.p2_f;
                return;
            }
        } //end of hard diff begining checks and scripts
         //normal diff checks if centrall cell occupied or chances didn't proc
        else if (game_data.diff == 2)
        {
            if (game_data.field[2][1] == EMTY)
            {
                game_data.field[2][1] = game_data.p2_f;
                return;
            }
            else if (game_data.field[1][2] == EMTY)
            {
                game_data.field[1][2] = game_data.p2_f;
                return;
            }
            else if (game_data.field[0][1] == EMTY)
            {
                game_data.field[0][1] = game_data.p2_f;
                return;
            }
            else if (game_data.field[1][0] == EMTY)
            {
                game_data.field[1][0] = game_data.p2_f;
                return;
            }
        }//end of normal diff begining checks and scripts 
    }


  //Mittelspiel AI scripts (one figure in potential row), begining script for field_size >3 and backup move script. Always return!    
    if (game_data.diff > 1)
    {
        coord ai_c;
        for (int y = 0; y < game_data.field_size; y++)
        {
            for (int x = 0; x < game_data.field_size; x++)
            {
                if (game_data.field[y][x] == game_data.p2_f || game_data.field[y][x] == EMTY) //if AI figure, check if there are any good moves using this cell
                {
                    ai_c = rowsCheck(game_data, y, x);
                    if (ai_c.flag == 1) //(0 - good moves found, 1 - good move found)
                    {
                        if (game_data.field[ai_c.y][ai_c.x] == EMTY)
                        {
                            game_data.field[ai_c.y][ai_c.x] = game_data.p2_f;
                            return;
                        }
                    }
                }
            }
        }
    }
    
    //backup scenario - works when no optimal moves found or in begining of the game on fields > 3
    coord ai_c = getRandomCoord(game_data.field_size);
    for (;;)
    {
        if (game_data.field[ai_c.y][ai_c.x] == EMTY)
        {
            game_data.field[ai_c.y][ai_c.x] = game_data.p2_f;
            return; 
        }
        else
        {
            ai_c = getRandomCoord(game_data.field_size);
        }
    }
}

//======================================================================================================================
// Find possible moves function. Plus victory check for field_size > 3
// 
// Checks four directions - left to right, top-down, diagonal top-down-right, diagonal top-down-left
// Params are: 1) game data structure 2) line's index 3) row's index
// Returns coords for optimal move + flag 1 (0 - if no optimal moves found). Returns flag 2 if victory found
//======================================================================================================================

coord rowsCheck(TTT_field& game_data, int y, int x, bool winCheck)
{
    coord c;
    //Buffers for scan results. 0 index - EMTY cells, 1st - 1p_f cells, 2nd - 2p_f cells, 
    //3rd - 'y' of best move, 4th - 'x' of best move 
    RowDataBuffer rb;
    int k; //variable for simultaneous double loops!

    //First we scan potential victory rows for data (EMTY cells, 1p_f cells, 2p_f cells)
    
    //left to right options check (buff1)
    if ((x + game_data.VictoryRowSize) <= game_data.field_size) //don't check if cells nessesary for victory exceed game field's limits
    {
        for (int i = x; i < (x + game_data.VictoryRowSize); i++) //loop limited by victoryRowSize 
        {
            switch(game_data.field[y][i])
            {
            case 'X':
                if (game_data.p1_f == 'X')
                    rb.buff1[1]++;
                else
                    rb.buff1[2]++;
                break;
            case 'O':
                if (game_data.p1_f == 'O')
                    rb.buff1[1]++;
                else
                    rb.buff1[2]++;
                break;
            default:
                if (game_data.field[y][i] == EMTY)
                {
                    rb.buff1[0]++;
                    rb.buff1[3] = y; //if line is completable - will be used as next move coords for AI
                    rb.buff1[4] = i;
                }
                break;
            }
        }
    }

    //top-down options check (buff2)
    if ((y + game_data.VictoryRowSize) <= game_data.field_size) //don't check if cells nessesary for victory exceed game field's limits
    {
        for (int i = (y); i < (y + game_data.VictoryRowSize); i++) //loop limited by victoryRowSize 
        {
            switch (game_data.field[i][x])
            {
            case 'X':
                if (game_data.p1_f == 'X')
                    rb.buff2[1]++;
                else
                    rb.buff2[2]++;
                break;
            case 'O':
                if (game_data.p1_f == 'O')
                    rb.buff2[1]++;
                else
                    rb.buff2[2]++;
                break;
            default:
                if (game_data.field[y][i] == EMTY)
                {
                    rb.buff1[0]++;
                    rb.buff1[3] = y; //if line is completable - will be used as next move coords for AI
                    rb.buff1[4] = i;
                }
                break;
            }
        }
    }

    //diagonal top-down-right options check (buff3)
    if (((y + game_data.VictoryRowSize) <= game_data.field_size) && ((x + game_data.VictoryRowSize) <= game_data.field_size)) //don't check if cells nessesary for victory exceed game field's limits
    {
        k = x; //variable for simultaneous double loops!
        for (int i = (y); i < (y + game_data.VictoryRowSize); i++) //loop limited by victoryRowSize
        {
            switch (game_data.field[i][k++])
            {
            case 'X':
                if (game_data.p1_f == 'X')
                    rb.buff3[1]++;
                else
                    rb.buff3[2]++;
                break;
            case 'O':
                if (game_data.p1_f == 'O')
                    rb.buff3[1]++;
                else
                    rb.buff3[2]++;
                break;
            default:
                if (game_data.field[y][i] == EMTY)
                {
                    rb.buff1[0]++;
                    rb.buff1[3] = y; //if line is completable - will be used as next move coords for AI
                    rb.buff1[4] = i;
                }
                break;
            }
        }
    }

    //diagonal top-down-left options check (buff4)
    if (((y + game_data.VictoryRowSize) <= game_data.field_size) && ((x - game_data.VictoryRowSize) >= 0)) //don't check if cells nessesary for victory exceed game field's limits
    {
        k = x;
        for (int i = y; i < (y + game_data.VictoryRowSize); i++) //loop limited by victoryRowSize
        {
            switch (game_data.field[i][k--])
            {
            case 'X':
                if (game_data.p1_f == 'X')
                    rb.buff4[1]++;
                else
                    rb.buff4[2]++;
                break;
            case 'O':
                if (game_data.p1_f == 'O')
                    rb.buff4[1]++;
                else
                    rb.buff4[2]++;
                break;
            default:
                if (game_data.field[y][i] == EMTY)
                {
                    rb.buff1[0]++;
                    rb.buff1[3] = y; //if line is completable - will be used as next move coords for AI
                    rb.buff1[4] = i;
                }
                break;
            }
        }
    }

    
    //Checking buffers for victory rows (for winCheck) and incompletable rows. 
    //If victory found or all rows ineligable - this code will always return from function!
    {
        if (rb.buff1[0] == 0 && rb.buff1[1] == 0 && rb.buff1[2] == 0)// row didn't have enough cells
            rb.buff1_flag = NO_ROW;
        if (rb.buff1[1] > 0 && rb.buff1[2] > 0) // row had both player's figures
            rb.buff1_flag = NO_ROW;
        else if (rb.buff1[1] == game_data.VictoryRowSize || rb.buff1[2] == game_data.VictoryRowSize)
        {
            rb.buff1_flag = VICTORY_ROW;
            c.flag = 2;
            return c;
        }

        if (rb.buff2[0] == 0 && rb.buff2[1] == 0 && rb.buff2[2] == 0)// row didn't have enough cells
            rb.buff2_flag = NO_ROW;
        if (rb.buff2[1] > 0 && rb.buff2[2] > 0) // row had both player's figures
            rb.buff2_flag = NO_ROW;
        else if (rb.buff2[1] == game_data.VictoryRowSize || rb.buff2[2] == game_data.VictoryRowSize)
        {
            rb.buff2_flag = VICTORY_ROW;
            c.flag = 2;
            return c;
        }

        if (rb.buff3[0] == 0 && rb.buff3[1] == 0 && rb.buff3[2] == 0)// row didn't have enough cells
            rb.buff3_flag = NO_ROW;
        if (rb.buff3[1] > 0 && rb.buff3[2] > 0) // row had both player's figures
            rb.buff3_flag = NO_ROW;
        else if (rb.buff3[1] == game_data.VictoryRowSize || rb.buff3[2] == game_data.VictoryRowSize)
        {
            rb.buff3_flag = VICTORY_ROW;
            c.flag = 2;
            return c;
        }

        if (rb.buff4[0] == 0 && rb.buff4[1] == 0 && rb.buff4[2] == 0)// row didn't have enough cells
            rb.buff4_flag = NO_ROW;
        if (rb.buff4[1] > 0 && rb.buff4[2] > 0) // row had both player's figures
            rb.buff4_flag = NO_ROW;
        else if (rb.buff4[1] == game_data.VictoryRowSize || rb.buff4[2] == game_data.VictoryRowSize)
        {
            rb.buff4_flag = VICTORY_ROW;
            c.flag = 2;
            return c;
        }
        

        if (rb.buff1_flag == NO_ROW && rb.buff2_flag == NO_ROW && rb.buff3_flag == NO_ROW && rb.buff4_flag == NO_ROW)
        {
            c.flag = 0; //only draws found in checked rows (and ineligible rows)
            return c;
        }
    }
    
    //Find buffer with least buffX[0] (EMTY) - it will be closest row to complete. Rows with p1_f already excluded at this point
    //This code will always return from function!
    if (game_data.game_mode == 1 && (game_data.turn == game_data.p2) && winCheck == false)//AI_Proc() call only
    { 
        short int min = game_data.VictoryRowSize; //variable to determine lowest amount of buffX[0]
        if ((rb.buff1_flag != NO_ROW) && rb.buff1[0] < min)
        {
            min = rb.buff1[0];
            rb.buff1_flag = PRIORITY;
        }

        if ((rb.buff2_flag != NO_ROW) && rb.buff2[0] < min)
        {
            min = rb.buff2[0];
            rb.buff2_flag = PRIORITY;
        }

        if ((rb.buff3_flag != NO_ROW) && rb.buff3[0] < min)
        {
            min = rb.buff3[0];
            rb.buff3_flag = PRIORITY;
        }

        if ((rb.buff4_flag != NO_ROW) && rb.buff4[0] < min)
        {
            min = rb.buff4[0];
            rb.buff4_flag = PRIORITY;
        }
        
        //Now we determine which row (buff) had least empty cells and return its 'best' coords from function
        if ((rb.buff1_flag != NO_ROW) && rb.buff1_flag == PRIORITY)
        {
            c.y = rb.buff1[3];
            c.x = rb.buff1[4];
            c.flag = 1;
            c.EMTY_n = rb.buff1[0]; //Relay number of remaining cells to complete row and win
            return c;
        }

        else if ((rb.buff2_flag != NO_ROW) && rb.buff2_flag == PRIORITY)
        {
            c.y = rb.buff2[3];
            c.x = rb.buff2[4];
            c.flag = 1;
            c.EMTY_n = rb.buff2[0]; //Relay number of remaining cells to complete row and win
            return c;
        }

        else if ((rb.buff3_flag != NO_ROW) && rb.buff3_flag == PRIORITY)
        {
            c.y = rb.buff3[3];
            c.x = rb.buff3[4];
            c.flag = 1;
            c.EMTY_n = rb.buff3[0]; //Relay number of remaining cells to complete row and win
            return c;
        }

        else if ((rb.buff4_flag != NO_ROW) && rb.buff4_flag == PRIORITY)
        {
            c.y = rb.buff4[3];
            c.x = rb.buff4[4];
            c.flag = 1;
            c.EMTY_n = rb.buff4[0]; //Relay number of remaining cells to complete row and win
            return c;
        } 
        return c = { 0,0,0 };
    }
    else if (winCheck == true)
    {
        c.flag = 4;
        return c;
    }
}

//======================================================================================================================
//Rematch function
//======================================================================================================================
int ReMatch() //0 - рестарт, 1 - завершение
{
    char y_n = 0;
    for ( ; ; )
    {
        cout << "Реванш (Y/N)? ";
        cin >> y_n;
        if (y_n == 'Y' || y_n == 'y' || y_n == 'У' || y_n == 'у')
        {
            cout << endl;
            return 0; //рестарт игры
        }
        else if (y_n == 'N' || y_n == 'n' || y_n == 'Н' || y_n == 'н')
        {
            cout << endl;
            return 1; //завершение игры
        }
    }
    return 1;
}