#pragma once
struct TTT_field;

inline void rollInitiative(TTT_field& game_data);
void clear();
inline void cinCheck();
void init(TTT_field &game_data);
int winCheck(TTT_field game_data);
void fieldPrint(TTT_field& game_data);
void AI_Proc(TTT_field& game_data);
int ReMatch();
void fieldInit(TTT_field& game_data);
