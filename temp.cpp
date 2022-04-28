void AI_Proc(TTT_field & game_data) 
{
 //for normal and higher. Checks for easy victory or user's victory
  if (game_data.diff > 1) 
  {
     for (size_t i = 0; i < game_data.fieldsize; i++)
       for (size_t k = 0; k < game_data.fieldsize; k++)
         if (game_data.fieldsmall[i][k] == EMTY)
         {
           if (game_data.diff == 2) //Normal. Chance to complete row 85%. Chance to react to threat 25% (75% if it completes own row). 
           {
             game_data.fieldsmall[i][k] = game_data.turn; //AI figure placement
             if (winCheck(game_data) == 1) //DOUBLECHEK!! Needs to be victory! (maybe DRAW)
             {
               if(game_data.turn == game_data.ai_f && rollRandom(0, 100) >= 15) //DOUBLECHECK!!
                 return;
               else //75% chance check
               {
                 game_data.field[i][k] = game_data.p1_f
                 int ai_temp1 = winCheck(game_data) //move declaration!!!
                 game_data.fieldsmall[i][k] = game_data.turn
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
             game_data.fieldsmall[i][k] = game_data.turn;
             if (winCheck(game_data) == 1) //DOUBLECHEK!! Needs to be victory! (maybe DRAW)
             {
               return;
             } //end of imminent victory check
             else 
             {
                game_data.fieldsmall[i][k] = game_data.p1_f
                int ai_temp1 = winCheck(game_data) //move declaration!!!
                game_data.fieldsmall[i][k] = game_data.turn
                if(ai_temp1 == 1)
                {
                  return;
                } //end of imminent player victory check
                else 
                {
                  game_data.fieldsmall[i][k] = EMTY;
                } //end of top difficulty checks for imminent victory
             }   
           }
         }
  } //end of diff > 1 checks for imminent victory
  if (game_data.diff == 1) //all easy-mode mechanics here!!
  {
    int x = rollRandom(0, &game_data.fieldSize);
    int y = rollRandom(0, &game_data.fieldSize);
    for(;;)
    {
      if (game_data.fieldsmall[y][x] != EMTY)
      {
        game_data.fieldsmall[y][x] = game_data.turn;
        return; //only exit from the cycle. Make redundancy break after fieldSize^2 iterations?? 
      }
      else
      {
        x = rollRandom(0, &game_data.fieldSize);
        y = rollRandom(0, &game_data.fieldSize);
      }
    }//конец кода для сложности 1. Больше кода для неё не будет
  }//end of easy win ai_checks. 
  
   //Scenarios for game's begining
  if ((game_data.diff == 3 || (game_data.diff == 2 && (rollRandom(0,100) >= 50)) && game_data.fieldsmall[1][1] == EMTY)
  {
    game_data.fieldsmall[1][1] = game_data.turn;
    return;
  }
  else if (game_data.diff == 3 && game_data.fieldsmall[1][1] != EMTY)
    {
      if (game_data.fieldsmall[0][2] == EMTY)
      {
        game_data.fieldsmall[0][2] = game_data.turn;
        return;
      }
      else if (game_data.fieldsmall[2][2] == EMTY)
      {
        game_data.fieldsmall[2][2] = game_data.turn;
        return;
      }
      else if (game_data.fieldsmall[2][0] == EMTY)
      {
        game_data.fieldsmall[2][0] = game_data.turn;
        return;
      }
      else if (game_data.fieldsmall[0][0] == EMTY)
      {
        game_data.fieldsmall[0][0] = game_data.turn;
        return;
      } 
    } //end of hard diff begining checks and scripts
  else if (game_data.diff == 2)
    {
      if (game_data.fieldsmall[2][1] == EMTY)
      {
        game_data.fieldsmall[2][1] = game_data.turn;
        return;
      }
      else if (game_data.fieldsmall[1][2] == EMTY)
      {
        game_data.fieldsmall[1][2] = game_data.turn;
        return;
      }
      else if (game_data.fieldsmall[0][1] == EMTY)
      {
        game_data.fieldsmall[0][1] = game_data.turn;
        return;
      }
      else if (game_data.fieldsmall[1][0] == EMTY)
      {
        game_data.fieldsmall[1][0] = game_data.turn;
        return;
      } 
    }//end of medium diff begining checks and scripts 
 

  //All that remains are mittelspiel AI scripts (one figure in potential row)      
  
}
