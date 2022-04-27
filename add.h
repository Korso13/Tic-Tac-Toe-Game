#pragma once
struct TTT_field;

void init(TTT_field &game_data);
int winCheck(TTT_field game_data);
void fieldPrint(TTT_field& game_data);
void cinCheck();
void AI_Proc(TTT_field game_data);
void clear();
int32_t RollRandom(int32_t min, int32_t max);
int ReMatch();
