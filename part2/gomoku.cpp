#include "gomoku.h"
#include "limits.h"
using namespace std;

gomoku::gomoku()
{
	for(int j = 0; j < BOARD_DIM; j++)
	{
		std::vector<char> row;
		this-> board.push_back(row);
		for(int i = 0; i < BOARD_DIM; i++)
		{
			board[j].push_back('.');
		}
	}
	for (int i = 0; i < BOARD_SIZE; i++){
		this->rem_blocks.push_back(true);
	}

}

void gomoku::print_board()
{
	for(int j = 0; j < BOARD_DIM; j++)
	{
		cout << BOARD_DIM - j - 1 << '|';
		for(int i = 0; i < BOARD_DIM; i++)
		{
			char to_print = this->board[j][i];
			std::cout << to_print;
			std::cout << ' ';
		}
		std::cout << std::endl;
	}
	cout << " --------------" << endl;
	cout << "  0 1 2 3 4 5 6" << endl;
}

void gomoku::play_game()
{
	// Tossing a coin to see who starts first

	// std::cout << "got into the function" <<endl;
	int first_player = std::rand() % 2;
    int next_player = 0;
    next_player = (first_player == PLAYER1) ? PLAYER2 : PLAYER1;
    std::cout << "first_player: " << first_player << endl;
    std::cout << "next_player: " << next_player << endl;

    // std::cout << first_player << endl;
    // std::cout << "getting the start index" <<endl;

    first_player = 1;
    next_player = 0;
    //int start_index = winning_block(first_player);
    // cout << "placing the move" << endl;
    place_move(0,36);
	print_board();
	cout << "num_moves 1" << endl;
	place_move(1, 12);
	print_board();

    // cout << "before the players assignment" << endl;
    this->curr_player = next_player;
    this->prev_player = first_player;

    int num_moves = 2;
    // cout << "before the while loop" << endl;
    while(!is_winner(this->prev_player) && num_moves < 49)
    {
    	// First, we check if we have four stones any where
    	cout << "num_moves " << num_moves << endl;
    	int out1 = first_rule_checker(this->curr_player, 1);
    	if(out1 != -1)
    	{
    		std::cout << "got into first rule checker" << std::endl;
    		place_move(this->curr_player, out1);
    		num_moves++;
    		int temp = this-> curr_player;
    		this -> curr_player = this-> prev_player;
    		this -> prev_player = temp;
			print_board();
    		continue;
    	}

    	int out2 = second_rule_checker(this->curr_player,1);
    	if(out2 != -1)
    	{
    		std::cout << "got into second rule checker" << std::endl;
    		place_move(this->curr_player, out2);
    		num_moves++;
    		int temp = this-> curr_player;
    		this -> curr_player = this-> prev_player;
    		this -> prev_player = temp;
			print_board();
    		continue;
    	}

    	int out3 = third_rule_checker(this->curr_player,2);
    	if(out3 != -1)
    	{
    		std::cout << "got into third rule checker" << std::endl;
    		place_move(this->curr_player, out3);
    		num_moves++;
    		int temp = this-> curr_player;
    		this -> curr_player = this-> prev_player;
    		this -> prev_player = temp;
			print_board();
    		continue;
    	}

    	int win_index = winning_block(this->curr_player).first;
    	place_move(this->curr_player, win_index);
    	num_moves++;
    	int temp = this-> curr_player;
    	this -> curr_player = this-> prev_player;
    	this -> prev_player = temp;

    	print_board();
    }

    if(num_moves < 48)
    {
    	cout << "Congrats to player " << this->prev_player << " !!!" << std::endl;
    }
    else
    	cout << "No winner was found :-(" << std::endl;
}

void gomoku::text_ui(){
	cout << "Choose an enemy to play against: 1. reflex, 2. minimax, 3. alpha_beta" << endl;
	int enemy;
	cin >> enemy;
	while (enemy < 1 || enemy>3){
		cout << "Invalid input, please choose again." << endl;
		cin >> enemy;
	}
	cout << "Do you want to be the first player? 0. yes, 1. no" << endl;
	int order;
	cin >> order;
	while (order < 0 || order>1){
		cout << "Invalid input, please choose again." << endl;
		cin >> order;
	}

	int first_player = 1;
	int next_player = 0;
	//std::cout << "first_player: " << first_player << endl;
	//std::cout << "next_player: " << next_player << endl;
	MINIMAX_AGENT = 1 - order;
	AB_AGENT = 1 - order;

	this->curr_player = next_player;
	this->prev_player = first_player;

	int num_moves = 0;
	// cout << "before the while loop" << endl;
	while (!is_winner(this->prev_player) && num_moves < 49)
	{
		// First, we check if we have four stones any where
		cout << "num_moves " << num_moves << endl;
		if (curr_player == order){
			int userx, usery;
			cout << "Input the coordinate of your next move: " << endl;
			cout << "x: ";
			cin >> userx;
			cout << "y: ";
			cin >> usery;
			int idx = (6 - usery) * 7 + userx;
			while (idx < 0 || idx>48 || !rem_blocks[idx]){
				cout << "Invalid position, please try again: " << endl;
				cout << "x: ";
				cin >> userx;
				cout << endl;
				cout << "y: ";
				cin >> usery;
				cout << endl;
				idx = (6 - usery) * 7 + userx;
			}
			place_move(this->curr_player, idx);
		}
		else{
			switch (enemy)
			{
			case 1:{
				int out1 = first_rule_checker(this->curr_player, 1);
				if (out1 != -1)
				{
					std::cout << "got into first rule checker" << std::endl;
					place_move(this->curr_player, out1);
					num_moves++;
					int temp = this->curr_player;
					this->curr_player = this->prev_player;
					this->prev_player = temp;

					print_board();
					continue;
				}

				int out2 = second_rule_checker(this->curr_player, 1);
				if (out2 != -1)
				{
					std::cout << "got into second rule checker" << std::endl;
					place_move(this->curr_player, out2);
					num_moves++;
					int temp = this->curr_player;
					this->curr_player = this->prev_player;
					this->prev_player = temp;

					print_board();
					continue;
				}

				int out3 = third_rule_checker(this->curr_player, 2);
				if (out3 != -1)
				{
					std::cout << "got into third rule checker" << std::endl;
					place_move(this->curr_player, out3);
					num_moves++;
					int temp = this->curr_player;
					this->curr_player = this->prev_player;
					this->prev_player = temp;

					print_board();
					continue;
				}

				int win_index = winning_block(this->curr_player).first;
				place_move(this->curr_player, win_index);
				break;
			}
			case 2:{
				int move = minimax_choose();
				place_move(this->curr_player, move);
				break;
			}
			case 3:{
				int alpha = INT_MIN;
				int beta = INT_MAX;
				int move = ab_choose(alpha, beta);
				place_move(this->curr_player, move);
				break;
			}
			}
		}
		num_moves++;
		int temp = this->curr_player;
		this->curr_player = this->prev_player;
		this->prev_player = temp;

		print_board();
	}

	if (num_moves < 49)
	{
		cout << "Congrats to player " << this->prev_player << " !!!" << std::endl;
	}
	else
		cout << "No winner was found :-(" << std::endl;

}
void gomoku::rf_minimax(int start)
{
	// Tossing a coin to see who starts first

	// std::cout << "got into the function" <<endl;
	// reflect agent will be the first player
	int first_player = 1;
	int next_player = 0;
	std::cout << "first_player: " << first_player << endl;
	std::cout << "next_player: " << next_player << endl;

	// std::cout << first_player << endl;
	// std::cout << "getting the start index" <<endl;

	//int start_index = winning_block(first_player).first;
	// cout << "placing the move" << endl;
	//int st = rand() % 49;
	//place_move(first_player, st);
	//print_board();

	// cout << "before the players assignment" << endl;
	this->curr_player = next_player;
	this->prev_player = first_player;

	int num_moves = 0;
	// cout << "before the while loop" << endl;
	while (!is_winner(this->prev_player) && num_moves < 49)
	{
		// First, we check if we have four stones any where
		cout << "num_moves " << num_moves << endl;
		if (curr_player == 1-MINIMAX_AGENT){
			int out1 = first_rule_checker(this->curr_player, 1);
			if (out1 != -1)
			{
				std::cout << "got into first rule checker" << std::endl;
				place_move(this->curr_player, out1);
				num_moves++;
				int temp = this->curr_player;
				this->curr_player = this->prev_player;
				this->prev_player = temp;

				print_board();
				continue;
			}

			int out2 = second_rule_checker(this->curr_player,1);
			if (out2 != -1)
			{
				std::cout << "got into second rule checker" << std::endl;
				place_move(this->curr_player, out2);
				num_moves++;
				int temp = this->curr_player;
				this->curr_player = this->prev_player;
				this->prev_player = temp;

				print_board();
				continue;
			}

			int out3 = third_rule_checker(this->curr_player,2);
			if (out3 != -1)
			{
				std::cout << "got into third rule checker" << std::endl;
				place_move(this->curr_player, out3);
				num_moves++;
				int temp = this->curr_player;
				this->curr_player = this->prev_player;
				this->prev_player = temp;

				print_board();
				continue;
			}

			int win_index = winning_block(this->curr_player).first;
			place_move(this->curr_player, win_index);
		}
		else{
			int move = minimax_choose();
			
			int alpha = INT_MIN;
			int beta = INT_MAX;
			//int move = ab_choose(alpha, beta);
			place_move(this->curr_player, move);
		}
		num_moves++;
		int temp = this->curr_player;
		this->curr_player = this->prev_player;
		this->prev_player = temp;

		print_board();
	}

	if (num_moves < 49)
	{
		cout << "Congrats to player " << this->prev_player <<" !!!" << std::endl;
	}
	else
		cout << "No winner was found :-(" << std::endl;
}


void gomoku::minimax_alphabeta()
{
	// Tossing a coin to see who starts first

	// std::cout << "got into the function" <<endl;
	// reflect agent will be the first player
	int first_player = 1;
	int next_player = 0;
	std::cout << "first_player: " << first_player << endl;
	std::cout << "next_player: " << next_player << endl;


	this->curr_player = next_player;
	this->prev_player = first_player;

	int num_moves = 0;
	// cout << "before the while loop" << endl;
	while (!is_winner(this->prev_player) && num_moves < 49)
	{
		// First, we check if we have four stones any where
		cout << "num_moves " << num_moves << endl;
		if (curr_player == MINIMAX_AGENT){
			int move = minimax_choose();
			place_move(this->curr_player, move);
		}
		else{
			//int move = minimax_choose();

			int alpha = INT_MIN;
			int beta = INT_MAX;
			int move = ab_choose(alpha, beta);
			place_move(this->curr_player, move);
		}
		num_moves++;
		int temp = this->curr_player;
		this->curr_player = this->prev_player;
		this->prev_player = temp;

		print_board();
	}

	if (num_moves < 49)
	{
		cout << "Congrats to player " << this->prev_player << " !!!" << std::endl;
	}
	else
		cout << "No winner was found :-(" << std::endl;
}
void gomoku::place_move(int player, int lin_idx)
{
	int x = lin_idx % BOARD_DIM;
	int y = lin_idx / BOARD_DIM;
	rem_blocks[lin_idx] = false;
	placed_moves.push_back(lin_idx);

	if(player == PLAYER1)
	{
		this->board[y][x] = 'a' + this->player_one_char;
		this->player_one_char++;
	}
	else
	{
		this->board[y][x] = 'A' + this->player_two_char;	
		this->player_two_char++;
	}

	// this -> prev_player = player;
	// this -> curr_player = (player == 0) ? 1 : 0;
}
void gomoku::tentative_move(int player, int lin_idx)
{
	int x = lin_idx % BOARD_DIM;
	int y = lin_idx / BOARD_DIM;
	rem_blocks[lin_idx] = false;
	placed_moves.push_back(lin_idx);

	if (player == PLAYER1)
	{
		this->board[y][x] = 'a' + this->player_one_char;
	}
	else
	{
		this->board[y][x] = 'A' + this->player_two_char;
	}

	// this -> prev_player = player;
	// this -> curr_player = (player == 0) ? 1 : 0;
}

void gomoku::undo_move(int player, int lin_idx)
{
	int x = lin_idx % BOARD_DIM;
	int y = lin_idx / BOARD_DIM;
	rem_blocks[lin_idx] = true;

	placed_moves.pop_back();

	if (player == PLAYER1)
	{
		this->board[y][x] = '.';
	}
	else
	{
		this->board[y][x] = '.';
	}
}
int gomoku::ab_choose(int & alpha, int & beta){
	map<int, int> moves;
	vector<int> move_range;
	get_possible_moves(move_range);
	int max = INT_MIN;
	int move = move_range[0];
	int a = alpha, b = beta;
	ab_nodes = 0;
	for (auto it = move_range.begin(); it != move_range.end(); it++){
		tentative_move(AB_AGENT, *it);
		if (is_winner(AB_AGENT)) {
			moves[*it] = INT_MAX-1;
		}
		else moves[*it] = ab_eval_move(*it, 2, a, b);

		undo_move(AB_AGENT, *it);
		if (moves[*it] > max){ 
			max = moves[*it];
			move = *it;
		}
		ab_nodes++;
		a = max > a ? max : a;
		if (b <= a) break;
	}
	/*
	int move = -1;
	int max = INT_MIN;
	for (auto it = moves.begin(); it != moves.end(); it++){
		if (it->second >= max){
			max = it->second;
			move = it->first;
		}
	}*/
	cout << "Alpha_beta chose location: (" << move%7 <<", "<< (6-move/7)<<")" << endl;
	cout << "Alpha_beta expanded: " << ab_nodes << " nodes." << endl;
	return move;
}

int gomoku::ab_eval_move(int pos, int depth, int & alpha, int & beta){
	int oppo = 1 - AB_AGENT;
	if (depth == 1){
		vector<int> move_range;
		get_possible_moves(move_range);
		map<int, int> moves;
		int max = INT_MIN;
		//int move = -1;
		int a = alpha;
		int b = beta;
		for (auto it = move_range.begin(); it != move_range.end(); it++){
			tentative_move(AB_AGENT, *it);
			if (is_winner(AB_AGENT)) moves[*it] = INT_MAX - 2;
			else moves[*it] = eval(AB_AGENT);
			undo_move(AB_AGENT, *it);
			if (moves[*it] > max){
				max = moves[*it];
				//move = *it;
			}
			a = moves[*it] > a ? moves[*it] : a;
			ab_nodes++;
			if (b <= a){
				break;
			}
		}
		/*
		int max = INT_MIN;
		for (auto it = moves.begin(); it != moves.end(); it++){
			if (it->second >= max) max = it->second;
		}
		if (moves.size() == 0) return 0;*/
		return max;
	}
	/* oppo's turn */
	if (depth == 2){
		vector<int> move_range;
		get_possible_moves(move_range);
		map<int, int> moves;
		int a = alpha;
		int b = beta;
		int min = INT_MAX;
		for (auto it = move_range.begin(); it != move_range.end(); it++){
			tentative_move(oppo, *it);
			if (is_winner(oppo)) moves[*it] = INT_MIN + 1;
			else moves[*it] = ab_eval_move(*it, 1, a, b);
			undo_move(oppo, *it);
			if (moves[*it] < min){
				min = moves[*it];
				//move = *it;
			}
			b = moves[*it] < b ? moves[*it] : b;
			ab_nodes++;
			if (b <= a) break;
		}
		/*
		for (auto it = moves.begin(); it != moves.end(); it++){
			if (it->second <= min) min = it->second;
		}
		if (moves.size() == 0) return 0;*/
		return min;
	}
}


int gomoku::minimax_choose(){
	map<int, int> moves;
	vector<int> move_range;
	get_possible_moves(move_range);

	int move = move_range[0];
	int max = INT_MIN;
	mm_nodes = 0;

	for (auto it = move_range.begin(); it != move_range.end(); it++){
		tentative_move(MINIMAX_AGENT, *it);
		if (is_winner(MINIMAX_AGENT)) {
			moves[*it] = INT_MAX-1;
		}
		else moves[*it] = eval_move(*it, 2);
		undo_move(MINIMAX_AGENT, *it);
		if (moves[*it] > max){
			max = moves[*it];
			move = *it;
		}
		mm_nodes++;
	}
	if (move == 7){
		int a = 2;
	}
	cout << "Minimax chose location:  (" << move % 7 << ", " << (6 - move / 7) << ")" << endl;
	cout << "Minimax expanded: " << mm_nodes << " nodes." << endl;

	return move;
	
}

int gomoku::eval_move(int pos, int depth){
	int oppo = 1 - MINIMAX_AGENT;
	if (depth == 1){
		vector<int> move_range;
		get_possible_moves(move_range);
		map<int, int> moves;
		int max = INT_MIN;
		for (auto it = move_range.begin(); it != move_range.end(); it++){
			tentative_move(MINIMAX_AGENT, *it);
			if (is_winner(MINIMAX_AGENT)) moves[*it] = INT_MAX - 2;
			else moves[*it] = eval(MINIMAX_AGENT);
			if (moves[*it] > max){
				max = moves[*it];
				//move = *it;
			}
			undo_move(MINIMAX_AGENT, *it);
			mm_nodes++;
			
		}/*
		for (auto it = moves.begin(); it != moves.end(); it++){
			if (it->second >= max) max = it->second;
		}
		if (moves.size() == 0) return 0;*/
		return max;
	}
	/* oppo's turn */
	if (depth == 2){
		vector<int> move_range;
		get_possible_moves(move_range);
		map<int, int> moves;
		int min = INT_MAX;
		for (auto it = move_range.begin(); it != move_range.end(); it++){
			tentative_move(oppo, *it);
			if (is_winner(oppo)) moves[*it] = INT_MIN + 1;
			else moves[*it] = eval_move(*it, 1);
			if (moves[*it] < min){
				min = moves[*it];
				//move = *it;
			}
			undo_move(oppo, *it);
			mm_nodes++;

		}
		/*
		for (auto it = moves.begin(); it != moves.end(); it++){
			if (it->second <= min) min = it->second;
		}
		if (moves.size() == 0) return 0;*/
		return min;
	}
}

int gomoku::eval(int player){
	int oppo =  1-player;
	int value = 0;

	if (is_winner(player)) return INT_MAX - 2;
	if (is_winner(oppo)) return INT_MIN + 2;

	if (first_rule_checker(oppo, 2) != -1){
		return INT_MIN + 2;
	}

	/* 4 in a row */
	if (first_rule_checker(player, 2) != -1) value += 100;
	else if (first_rule_checker(player,1) != -1) value += 50;
	else if (winning_block(player).second == 4) value += 100;
		
	
	if (first_rule_checker(oppo, 1) != -1) return INT_MIN + 3;
	if (winning_block(oppo).second == 4) return INT_MIN + 3;

	/* 3 in a row */
	if (third_rule_checker(oppo,2) != -1) return INT_MIN + 4;
	else if (third_rule_checker(oppo, 1) != -1) value -= 100;
	else{
		int maxblock = winning_block(oppo).second;
		value -= maxblock * 10;
	}

	if (third_rule_checker(oppo,2) != -1) value += 50;
	else if (third_rule_checker(oppo, 1) != -1) value += 30;
	else{
		int maxblock = winning_block(player).second;
		value += maxblock * 10;
	}

	
	return value;
}

void gomoku::get_possible_moves(vector<int> & moves){
	
	if (placed_moves.size() == 0){
		for (int i = 0; i < 3; i++){
			for (int j = BOARD_DIM-1; j > BOARD_DIM - 4; j--){
				moves.push_back(j*BOARD_DIM + i);
			}
		}
		return;
	}

	if (placed_moves.size() > 24){
		for (int i = 0; i < 49; i++){
			if (rem_blocks[i]) moves.push_back(i);
		}
		return;
	}

	for (int i = 0; i < BOARD_SIZE; i++){
		int x = i % BOARD_DIM;
		int y = i / BOARD_DIM;
		bool in_range = false;
		if (rem_blocks[i]){

			if (x > 0){
				if (!rem_blocks[i - 1]){
					moves.push_back(i);
					continue;
				}
				if (y > 0){
					if (!rem_blocks[i - 8]){
						moves.push_back(i);
						continue;
					}
				}
				if (y < 6){
					if (!rem_blocks[i + 6]){
						moves.push_back(i);
						continue;
					}
				}
			}
			if (x < 6){
				if (!rem_blocks[i + 1]){
					moves.push_back(i);
					continue;
				}
				if (y > 0){
					if (!rem_blocks[i - 6]){
						moves.push_back(i);
						continue;
					}
				}
				if (y < 6){
					if (!rem_blocks[i + 8]){
						moves.push_back(i);
						continue;
					}
				}

			}
			if (y > 0){
				if (!rem_blocks[i - 7]){
					moves.push_back(i);
					continue;
				}
			}
			if (y < 6){
				if (!rem_blocks[i + 7]){
					moves.push_back(i);
					continue;
				}
			}
		}
	}

}

bool gomoku::is_winner(int player)
{
	pair<int,int> best_row = winning_row(player);
	pair<int,int> best_col = winning_col(player);
	pair<int,int> best_ldiag = winning_ldiag(player);
	pair<int,int> best_rdiag = winning_rdiag(player);


	vector<int> best_number_pieces;
	best_number_pieces.push_back(best_row.second);
	best_number_pieces.push_back(best_col.second);
	best_number_pieces.push_back(best_ldiag.second);
	best_number_pieces.push_back(best_rdiag.second);


	auto iter_to_max = std::max_element(best_number_pieces.begin(), best_number_pieces.end());
	int max_element = *iter_to_max;

	if (max_element == 5){
		return true;
	}
		
	return false;
}

int gomoku::first_rule_checker(int player, int open)
{
	int from_rows = row_checker(player, 4,open);
	int from_cols = col_checker(player, 4,open);
	int from_rdiag= rdiag_checker(player, 4,open);
	int from_ldiag = ldiag_checker(player, 4,open);

	if(from_rows != -1 || from_cols != -1 || from_rdiag != -1 || from_ldiag != -1)
	{
		vector<int> vec;
		vec.push_back(from_rows);
		vec.push_back(from_cols);
		vec.push_back(from_ldiag);
		vec.push_back(from_rdiag);

		int store;
		for(int i = 0; i < 4; i++)
		{
			if(vec[i] != -1)
				return vec[i];

		}
	}

	return -1;

}

int gomoku::second_rule_checker(int player, int open)
{
	int oppo = (player == PLAYER1) ? PLAYER2 : PLAYER1;

	int from_rows = row_checker(oppo, 4,open);
	int from_cols = col_checker(oppo, 4,open);
	int from_rdiag= rdiag_checker(oppo, 4,open);
	int from_ldiag = ldiag_checker(oppo, 4,open);

	if(from_rows != -1 || from_cols != -1 || from_rdiag != -1 || from_ldiag != -1)
	{
		vector<int> vec;
		vec.push_back(from_rows);
		vec.push_back(from_cols);
		vec.push_back(from_ldiag);
		vec.push_back(from_rdiag);

		for(int i = 0; i < 4; i++)
		{
			if(vec[i] != -1)
				return vec[i];
		}

	}
	return -1;
}

int gomoku::third_rule_checker(int player, int open)
{

	int oppo = (player == PLAYER1) ? PLAYER2 : PLAYER1;

	int from_rows = row_checker(oppo, 3,open);
	int from_cols = col_checker(oppo, 3,open);
	int from_rdiag= rdiag_checker(oppo, 3,open);
	int from_ldiag = ldiag_checker(oppo, 3,open);

	if(from_rows != -1 || from_cols != -1 || from_rdiag != -1 ||from_ldiag != -1)
	{
		vector<int> vec;
		vec.push_back(from_rows);
		vec.push_back(from_cols);
		vec.push_back(from_ldiag);
		vec.push_back(from_rdiag);

		for(int i = 0; i < 4; i++)
		{
			if(vec[i] != -1)
				return vec[i];
		}

	}

	return -1;
}


pair<int,int> gomoku::winning_block(int player)
{
	// Returns the linear index of the best row, col, ldiag, and rdiag
	// Here best is defined as containing most of player's peices, and 
	pair<int,int> best_row = winning_row(player);
	pair<int,int> best_col = winning_col(player);
	pair<int,int> best_ldiag = winning_ldiag(player);
	pair<int,int> best_rdiag = winning_rdiag(player);

	// cout << "best_row.first = " << best_row.first << " best_row.second = " << best_row.second << endl;
	// cout << "best_col.first = " << best_col.first << " best_col.second = " << best_col.second << endl;
	// cout << "best_ldiag.first = " << best_ldiag.first << " best_ldiag.second = " << best_ldiag.second << endl;
	// cout << "best_rdiag.first = " << best_rdiag.first << " best_rdiag.second = " << best_rdiag.second << endl;


	vector<int> best_number_pieces;
	best_number_pieces.push_back(best_row.second);
	best_number_pieces.push_back(best_col.second);
	best_number_pieces.push_back(best_ldiag.second);
	best_number_pieces.push_back(best_rdiag.second);

	vector<int> linear_indices;
	linear_indices.push_back(best_row.first);
	linear_indices.push_back(best_col.first);
	linear_indices.push_back(best_ldiag.first);
	linear_indices.push_back(best_rdiag.first);

	//We got to return the best index in terms of not only agent peices but also left most and down most
	auto iter_to_max = std::max_element(best_number_pieces.begin(), best_number_pieces.end());
	int max_element = *iter_to_max;
	//std::cout << "max_element: " << max_element << endl;
	std::vector<int> best_indices;
	for(int i = 0; i < 4; i++)
	{
		if(max_element == best_number_pieces[i])
		{
			best_indices.push_back(linear_indices[i]);
		}
	}

	if(best_indices.size() > 1)
	{
		int best_x = best_indices[0] % BOARD_DIM;
		int best_y = best_indices[0] / BOARD_DIM;
		for(int i = 1; i < best_indices.size(); i++)
		{
			int curr_x = best_indices[i] % BOARD_DIM;
			int curr_y = best_indices[i] / BOARD_DIM;
			if(curr_x <= best_x && curr_y >= best_y)
			{
				best_x = curr_x;
				best_y = curr_y;
			}
		}

		// std::cout << "Index to be returned " << (BOARD_DIM*best_y) + best_x << endl;
		return pair<int, int>((BOARD_DIM*best_y) + best_x, max_element);
	}

	// std::cout << "Index to be returned " << best_indices[0] << endl;
	return pair<int, int>(best_indices[0],max_element);
}












