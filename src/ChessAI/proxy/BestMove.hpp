#pragma once
#include <raylib.h>

struct BestMove {
        float score;
        Vector2 from;
        Vector2 to;
};

struct Max_BestMove
{
  BestMove value;
  Max_BestMove(Vector2 from={0,0}, Vector2 to={0,0},float score=-1001) : value({score,from, to}) {}
  Max_BestMove& operator=(const BestMove& other)
  {
    if (other.score > value.score)
    {
      value = other;
    }
    return *this;
  }
};