void AI_Proc(TTT_field & game_data) 
{
  if (game_data.diff > 1) //for normal and higher. Checks for easy victory or user's victory
  {
     for (size_t i = 0; i < game_data.fieldsize; i++)
       for (size_t k = 0; k < game_data.fieldsize; k++)
         if (game_data.field[i][k] == EMTY)
         {
           if (game_data.diff == 2) //Normal. Chance to complete row 85%. Chance to react to threat 25% (75% if it completes own row). 
           {
             game_data.field[i][k] = game_data.turn; //AI figure placement
             if (winCheck(game_data) == 1) //DOUBLECHEK!! Needs to be victory! (maybe DRAW)
             {
               if(game_data.turn == game_data.ai_f && rollRandom(0, 100) >= 15) //DOUBLECHECK!!
                 return;
               else //75% chance check
               {
                 game_data.field[i][k] = game_data.p1_f
                 int ai_temp1 = winCheck(game_data) //move declaration!!!
                 game_data.field[i][k] = game_data.turn
                 if(ai_temp1 == 1 && rollRandom(0, 100) >= 25)
                   return;
               }
             }
             else if(ai_temp1 == 1 && rollRandom(0, 100) >= 75)
                return;
             else
               break;
           } //End of bloc for normal difficulty
           else if (game_data.diff == 3 || game_data.diff == 4)
           {
             game_data.field[i][k] = game_data.turn;
             if (winCheck(game_data) == 1) //DOUBLECHEK!! Needs to be victory! (maybe DRAW)
             {
               return;
             } //end of imminent victory check
             else 
             {
                game_data.field[i][k] = game_data.p1_f
                int ai_temp1 = winCheck(game_data) //move declaration!!!
                game_data.field[i][k] = game_data.turn
                if(ai_temp1 == 1)
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
  if (game_data.diff == 1)
  {
    int x = rollRandom(0, &game_data.fieldSize);
    int y = rollRandom(0, &game_data.fieldSize);
    for(;;)
    {
      if (game_data.field[y][x] != EMTY)
      {
        game_data.field[y][x] = game_data.turn;
        return; //единственный выход из цикла. Сделать запасной после fieldSize^2 итераций? 
      }
      else
      {
        x = rollRandom(0, &game_data.fieldSize);
        y = rollRandom(0, &game_data.fieldSize);
      }
    }//конец кода для сложности 1. Больше кода для неё не будет
  }//end of primary ai_checks. On to begining and mitschpiel checks!
  
}
