#include <iostream>
using namespace std;

const int UNK = false;

struct Line {
	int row;
	int col1;
	int col2;
	int col3;
};

struct Space {
	int num;
	bool Not[9];
};

typedef Space** SpacePtrPtr;

struct Update {
	SpacePtrPtr board;
	int row;
	int col;
};

SpacePtrPtr MakeBoard();
void Print(SpacePtrPtr board);
void StartingNums(SpacePtrPtr board);
bool Done(SpacePtrPtr board);
Update LastOption(SpacePtrPtr board);
Update OnlyPossible(SpacePtrPtr board);
bool ThereIsConflict(Update move, int num);
bool NoOptions(Update move, int n);
bool NoOpsRow(Update move, int n);
bool NoOpsCol(Update move, int n);
bool NoOpsSqr(Update move, int n);
Update FixBoard(Update move);
Update FixSpace(Update move);
Update FixRow(Update move);
Update FixCol(Update move);
Update FixSqr(Update move);
int NumNot(bool* Not);
int LastUnk(bool* Not);
void DeleteBoard(SpacePtrPtr board);
void Arrow(SpacePtrPtr board);
Line TwoInARow(SpacePtrPtr board, int ishift, int jshift, int n);
Line TwoInACol(SpacePtrPtr board, int ishift, int jshift, int n);
void XWing(SpacePtrPtr board);

int main()
{
	SpacePtrPtr Board = MakeBoard();
	if(Board == NULL){
		cerr << "Not enough memory." << endl;
		return 1;
	}
	Print(Board);
	StartingNums(Board);
	Print(Board);
	int counter=0;
	for(int i=0;i<3000;i++){
	//while(!Done(Board)){
		counter++;
		Update move = LastOption(Board);
		if(move.row != -1){
			move = FixBoard(move);
		}
		move = OnlyPossible(Board);
		if(move.row != -1){
			move = FixBoard(move);
		}
		Arrow(Board);
		//XWing(Board);
	}
	Print(Board);
	cout << counter;
	DeleteBoard(Board);
	return 0;
}

/*
void XWing(SpacePtrPtr board)
{
	Line xwing;
	xwing.row  = -1;
	xwing.col1 = -1;
	xwing.col2 = -1;
	xwing.col3 = -1;
	for(int n =0; n<9; n++){
		for(int i = 0; i < 9; i++){
			xwing = OnlyTwo(board,i,n);
			if(xwing.col2 != -1)	
		}	
	}
}

Line OnlyTwo(SpacePtrPtr board, int i, int n)
{
	Line xwing;
	xwing.row  = -1;
	xwing.col1 = -1;
	xwing.col2 = -1;
	xwing.col3 = -1;
	for(int j = 0; j < 9; j++){
		if(board[i][j].Not[n])
			continue;
		if(xwing.row != i && xwing.row != -1){
			xwing.row  = -1;
			xwing.col1 = -1;
			xwing.col2 = -1;
		}
		if(xwing.row == -1){
			xwing.row  = i;
			xwing.col1 = j;
			continue;
		}
		if(xwing.row == i && xwing.col2 == -1){
			xwing.col2 = j;
			continue;
		}
		if(xwing.row == i && xwing.col2 != -1){
			xwing.row  = -1;
			xwing.col1 = -1;
			xwing.col2 = -1;
			break;
		}
	}
	return xwing;
}
*/
void Arrow(SpacePtrPtr board)
{
	for(int n=0; n < 9; n++){
	for(int ishift = 0; ishift < 9; ishift += 3){
	for(int jshift = 0; jshift < 9; jshift += 3){
		Line arrow = TwoInARow(board,ishift,jshift,n);
		if(arrow.row != -1){
			for(int j = 0; j < 9; j++){
				if(j != arrow.col1 
				&& j != arrow.col2 
				&& j != arrow.col3){
					board[arrow.row][j].Not[n] = true;
				}
			}
		}
		arrow = TwoInACol(board,ishift,jshift,n);
		if(arrow.row != -1){
			for(int i = 0; i < 9; i++){
				if(i != arrow.col1 
				&& i != arrow.col2 
				&& i != arrow.col3){
					board[i][arrow.row].Not[n] = true;
				}
			}
		}
	}}	
	}
}

Line TwoInARow(SpacePtrPtr board, int ishift, int jshift, int n)
{
	Line arrow;
	arrow.row  = -1;
	arrow.col1 = -1;
	arrow.col2 = -1;
	arrow.col3 = -1;
	for(int i = ishift; i < (3+ishift); i++){
	for(int j = jshift; j < (3+jshift); j++){
		if(board[i][j].Not[n])
			continue;
		if(arrow.row != (i + ishift) && arrow.row != -1){
			arrow.row  = -1;
			return arrow;
		}
		if(arrow.row == -1){
			arrow.row  = (i + ishift);
			arrow.col1 = (j + jshift);
			continue;
		}
		if(arrow.row == (i + ishift) && arrow.col2 == -1){
			arrow.col2 = (j + jshift);
		}
		else if(arrow.col2 != -1)
			arrow.col3 = (j + jshift);
	}}
	return arrow;
}

Line TwoInACol(SpacePtrPtr board, int ishift, int jshift, int n)
{
	Line arrow;
	arrow.row  = -1;
	arrow.col1 = -1;
	arrow.col2 = -1;
	arrow.col3 = -1;
	for(int j = jshift; j < 3; j++){
	for(int i = ishift; i < 3; i++){
		if(board[i][j].Not[n])
			continue;
		if(arrow.row != (j + jshift) && arrow.row != -1){
			arrow.row  = -1;
			return arrow;
		}
		if(arrow.row == -1){
			arrow.row  = (j + jshift);
			arrow.col1 = (i + ishift);
			continue;
		}
		if(arrow.row == (j + jshift) && arrow.col2 == -1){
			arrow.col2 = (i + ishift);
		}
		else if(arrow.col2 != -1)
			arrow.col3 = (i + ishift);
	}}
	return arrow;
}

Update FixBoard(Update move)
{
	SpacePtrPtr board = move.board;
	int row = move.row;
	int col = move.col;
	int num = board[row][col].num;
	int ishift = 0;
	int jshift = 0;
	ishift += 3*(move.row/3);
	jshift += 3*(move.col/3);
	for(int i = 0; i < 9; i++)
		board[row][col].Not[i] = true;
	for(int j = 0; j < 9; j++)
		board[row][j].Not[num] = true;
	for(int i = 0; i < 9; i++)
		board[i][col].Not[num] = true;
	for(int i = ishift; i < (3 + ishift); i++){
		for(int j = jshift; j < (3 + jshift); j++)
			board[i][j].Not[num] = true;
	}
	return move;
}

SpacePtrPtr MakeBoard()
{
	SpacePtrPtr board = new Space* [9];
	if(board == NULL)
		return NULL;
	for (int a = 0; a < 9; a++){
		board[a] = new Space[9];
		if(board[a] == NULL)
			return NULL;
	}
	for(int i = 0; i < 9; i++){
	for(int j = 0; j < 9; j++){
		board[i][j].num = -1;
		for(int k = 0; k < 9; k++)
			board[i][j].Not[k] = UNK;
	}}
	return board;
}

void Print(SpacePtrPtr board)
{
	for(int i = 0; i < 9; i++){
		if(i%3 == 0)
			cout << "# = = = = = # = = = = = # = = = = = #" << endl;
		else
			cout << "H - + - + - H - + - + - H - + - + - H" << endl;
	for(int j = 0; j < 9; j++){
		if(j%3 == 0)
			cout << "H ";
		else 
			cout << "| ";
		if(board[i][j].num != -1)
			cout << board[i][j].num + 1 << ' ';
		else
			cout << "  ";
	}
	cout << 'H' << endl;
	}
	cout << "# = = = = = # = = = = = # = = = = = #" << endl;
}

void StartingNums(SpacePtrPtr board)
{
	cout << "To enter a starting number, use the form num row col." 
	     << endl << "Enter -1 when you're done." << endl;
	Update New;
	New.board = board;
	int num = -1;
	while(true){
		cin >> num;
		if(num == -1)
			return;
		cin >> New.row;
		cin >> New.col;
		num--;
		New.row--;
		New.col--;
		if(num<0 || num>8 || New.row<0 || New.row>8 
			 || New.col<0 || New.col>8){
			continue;
		}
		board[New.row][New.col].num = num;
		FixBoard(New);
	}
}

bool Done(SpacePtrPtr board)
{
	for(int i = 0; i < 9; i++){
	for(int j = 0; j < 9; j++){
		if(board[i][j].num == -1)
			return false;
	}}
	return true;
}

Update LastOption(SpacePtrPtr board)
{
	Update move;
	move.board = board;
	for(int i = 0; i < 9; i++){
	for(int j = 0; j < 9; j++){
		int n = LastUnk(board[i][j].Not);
		move.row = i;
		move.col = j;
		if(NumNot(board[i][j].Not) == 8 
			&& board[i][j].num == -1
			&& !ThereIsConflict(move,n))
		{
			board[i][j].num = n;
			return move;
		}
	}}
	move.row = -1;
	return move;
}

Update OnlyPossible(SpacePtrPtr board)
{
	Update move;
	move.board = board;
	for(int n = 0; n < 9; n++){
	for(int i = 0; i < 9; i++){
	for(int j = 0; j < 9; j++){
		move.row = i;
		move.col = j;
		if(!board[i][j].Not[n] && NoOptions(move,n) 
			&& !ThereIsConflict(move,n)
			&& board[i][j].num == -1){
			board[i][j].num = n;
			return move;
		}
	}}}
	move.row = -1;
	return move;
}

bool ThereIsConflict(Update move, int num)
{
	SpacePtrPtr board = move.board;
	int row = move.row;
	int col = move.col;
	int ishift = 0;
	int jshift = 0;
	ishift += 3*(move.row/3);
	jshift += 3*(move.col/3);
	for(int j = 0; j < 9; j++){
		if(board[row][j].num == num)
			return true;
	}
	for(int i = 0; i < 9; i++){
		if(board[i][col].num == num)
			return true;
	}
	for(int i = ishift; i < (3 + ishift); i++){
	for(int j = jshift; j < (3 + jshift); j++){
		if(board[i][j].num == num)
			return true;
	}}
	return false;
}

bool NoOptions(Update move, int n)
{
	if(NoOpsRow(move,n) || NoOpsCol(move,n) || NoOpsSqr(move,n))
		return true;
	return false;
}

bool NoOpsRow(Update move, int n)
{
	SpacePtrPtr board = move.board;
	int row = move.row;
	int col = move.col;
	for(int j = 0; j < 9; j++){
		if(board[row][j].Not[n] == UNK && j != col)
			return false;
	}
	return true;
}

bool NoOpsCol(Update move, int n)
{
	SpacePtrPtr board = move.board;
	int row = move.row;
	int col = move.col;
	for(int i = 0; i < 9; i++){
		if(board[i][col].Not[n] == UNK && i != row)
			return false;
	}
	return true;
}

bool NoOpsSqr(Update move, int n)
{
	SpacePtrPtr board = move.board;
	int row = move.row;
	int col = move.col;
	int ishift = 0;
	int jshift = 0;
	ishift += 3*(move.row/3);
	jshift += 3*(move.col/3);
	for(int i = ishift; i < (3 + ishift); i++){
	for(int j = jshift; j < (3 + jshift); j++){
		if(board[i][j].Not[n] == UNK && !(i == row && j == col))
			return false;
	}}
	return true;
}

int NumNot(bool* Not)
{
	int counter = 0;
	for(int i = 0; i < 9; i++){
		if(Not[i])
			counter++;
	}
	return counter;
}

int LastUnk(bool* Not)
{
	for(int i = 0; i < 9; i++){
		if(!Not[i])
			return i;
	}
	return 0;
}

void DeleteBoard(SpacePtrPtr board)
{
	for (int i = 0; i < 9; i++)
		delete [] board[i];
	delete [] board;
}
