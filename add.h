#pragma once
struct TTT_field;

//DOUBLECHECK for redundancies!!!
void rollInitiative(TTT_field& game_data);
int32_t RollRandom(int32_t min, int32_t max);
void clear();
void cinCheck();
void init(TTT_field &game_data);
int winCheck(TTT_field game_data);
void fieldPrint(TTT_field& game_data);
void AI_Proc(TTT_field& game_data);
int ReMatch();
void fieldInit(TTT_field& game_data);
