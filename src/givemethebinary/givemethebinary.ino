/*
 * Assignment #1 - Give Me the Binary! (GMB)
 * Author: Elisa Yan
 */

#include "Game.h"
#include "GameStatus.h"

void setup() {
  initialize();
  setUpGame();
}

void loop() {
  const GameStatus gameStatus = getGameStatus();

  //Serial.println(gameStatus);

  switch (gameStatus) {
    case WAITING:
      waiting();
      break;
    case START_ROUND:
      startRound();
      break;
    case GAME_OVER:
      gameOver();
      break;
    case SLEEP_MODE:
      sleeping();
      break;
    default:
      break;
  }

  //delay(500);
}
