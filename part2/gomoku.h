#include <iostream>
#include <stdio.h>
#include <stdlib.h>    
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#define BOARD_DIM 7
#define BOARD_SIZE 49
#define PLAYER1 0
#define PLAYER2 1
#define RF_AGENT 1-MINIMAX_AGENT
#define RF_AGENT2 1-AB_AGENT
using namespace std;

class gomoku{

	private:
		std::vector<std::vector<char> > board;
		vector<bool> rem_blocks;
		vector<int> placed_moves;

		//Relating to the players of the game
		int prev_player;
		int curr_player;
		int player_one_char = 0;
		int player_two_char = 0;

	public:
		int MINIMAX_AGENT = 1;
		int AB_AGENT = 0;
		int mm_nodes = 0;
		int ab_nodes = 0;
		struct tree_node{
			int lin_idx;
			int value;
			vector<tree_node> childrens;
		};
		void get_possible_moves(vector<int> & moves);

		gomoku();
		void play_game();
		void text_ui();
		int return_move(int store, int index);
		void test_reflex();

		void rf_minimax(int start);
		void minimax_alphabeta();


		int eval_move(int pos, int depth);
		int eval(int player);
		int minimax_choose();

		int ab_choose(int & alpha, int & beta);
		int ab_eval(int & alpha, int & beta);
		int ab_eval_move(int pos, int depth, int & alpha, int & beta);

		int first_rule_checker(int player, int open);
		int second_rule_checker(int player, int open);
		int third_rule_checker(int player, int open);

		int row_checker(int player, int piece_number, int space);
		int col_checker(int player, int piece_number, int space);
		int ldiag_checker(int player, int piece_number, int space);
		int rdiag_checker(int player, int piece_number, int space);



		void undo_move(int player, int lin_idx);
		void tentative_move(int player, int lin_idx);



		pair<int,int> winning_block(int player);
		pair<int,int> winning_row(int player);
		pair<int,int> winning_col(int player);
		pair<int,int> winning_ldiag(int player);
		pair<int,int> winning_rdiag(int player);

		void place_move(int player, int lin_idx);
		void print_board();
		bool is_winner(int player);


};
