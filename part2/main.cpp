#include "gomoku.h"
using namespace std;

int main()
{

  //game.print_board();
	gomoku game;
	//game.play_game();
	//game.rf_minimax(0);
	//game.minimax_alphabeta();
	game.text_ui();
	int a;
	cin >> a;
	//game.rf_minimax(26);
	/*
	for (int i = 3; i < 49; i++){
		gomoku game;
		game.rf_minimax(i);
	}*/
	//game.play_game();
    //game.print_board();
	
    return 0;
}












