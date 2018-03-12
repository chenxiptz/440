#include "gomoku.h"
using namespace std;

int main()
{

  //game.print_board();
	//game.play_game();
	//game.rf_minimax(0);

	//gomoku game;
	//game.minimax_alphabeta();
	
	int c_flag = 0;
	while (!c_flag){
		gomoku game;
		game.text_ui();
		cout << "Do you want to start a new game? 0. yes, 1. no" << endl;
		cin >> c_flag;
	}
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












