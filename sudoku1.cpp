#include <iostream>
using namespace std;

const int UNK = false;

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

int main()
{
	SpacePtrPtr Board = MakeBoard();
	Print(Board);
	StartingNums(Board);
	while(!Done(Board)){
		cout << "(A)" << endl;
		Update move = LastOption(Board);
		cout << "(B)" << endl;
		if(move.row != -1){
			cout << "(C.1)" << endl;
			move = FixBoard(move);
			cout << "(C.2)" << endl;}
		cout << "(D)" << endl;
		move = OnlyPossible(Board);
		cout << "(E)" << endl;
		if(move.row != -1){
			cout << "(F.1)" << endl;
			move = FixBoard(move);
			cout << "(F.2)" << endl;}
		cout << "(G)" << endl;
		Print(Board);
	}
	DeleteBoard(Board);
	return 0;
}

Update FixBoard(Update move)
{
	SpacePtrPtr board = move.board;
	int row = move.row;
	int col = move.col;
	int num = board[row][col].num;
	int ishift = 0, jshift = 0;
	ishift += 3*(move.row/3);
	jshift += 3*(move.row/3);
	cout << "<A>" << endl;
	for(int i = 0; i < 9; i++){
		cout << "<B" << i << ">" << endl;
		board[row][col].Not[i] = true;
		cout << "<C" << i << ">" << endl;}
	cout << "<D>" << endl;
	for(int j = 0; j < 9; j++){
		cout << "<E" << j << ">" << endl;
		board[row][j].Not[num] = true;
		cout << "<F" << j << ">" << endl;}
	cout << "<G>" << endl;
	for(int i = 0; i < 9; i++){
		cout << "<H" << i << ">" << endl;
		board[i][col].Not[num] = true;
		cout << "<H" << i << ">" << endl;}
	for(int i = ishift; i < (3 + ishift); i++){
		cout << "<I" << i << ">" << endl;
		for(int j = jshift; j < (3 + jshift); j++){
			cout << "<J" << j << ">" << endl;
			board[i][j].Not[num] = true;
			cout << "<K" << j << ">" << endl;
		}
		cout << "<L" << i << ">" << endl;
	}
	/*move = FixSqr(move);
	move = FixRow(move);
	move = FixCol(move);
	move = FixSpace(move);*/
	return move;
}

Update FixSpace(Update move)
{
	SpacePtrPtr board = move.board;
	int row = move.row;
	int col = move.col;
	for(int i = 0; i < 9; i++)
		board[row][col].Not[i] = true;
	return move;
}

Update FixRow(Update move)
{
	SpacePtrPtr board = move.board;
	int row = move.row;
	int col = move.col;
	int num = board[row][col].num;
	for(int j = 0; j < 9; j++)
		board[row][j].Not[num] = true;
	return move;
}

Update FixCol(Update move)
{
	SpacePtrPtr board = move.board;
	int row = move.row;
	int col = move.col;
	int num = board[row][col].num;
	for(int i = 0; i < 9; i++)
		board[i][col].Not[num] = true;
	return move;
}

Update FixSqr(Update move)
{
	SpacePtrPtr board = move.board;
	int row = move.row;
	int col = move.col;
	int num = board[row][col].num;
	int ishift = 0, jshift = 0;
	ishift += 3*(move.row/3);
	jshift += 3*(move.row/3);
	for(int i = ishift; i < (3 + ishift); i++){
	for(int j = ishift; j < (3 + jshift); j++){
		board[i][j].Not[num] = true;
	}}
	return move;
}

SpacePtrPtr MakeBoard()
{
	SpacePtrPtr board = new Space* [9];
	for (int a = 0; a < 9; a++)
		board[a] = new Space[9];
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
		//cout << 'A' << num << endl;
		cin >> num;
		//cout << 'B' << num << endl;
		if(num == -1){
		//	cout << 'C' << num << endl;
			return;
		//	cout << 'D' << num << endl;
		}
		//cout << 'E' << num << endl;
		cin >> New.row;
		//cout << 'F' << num << endl; 
		cin >> New.col;
		//cout << 'G' << num << endl;
		num--;
		//cout << 'H' << num << endl;
		New.row--;
		//cout << 'I' << num << endl;
		New.col--;
		//cout << 'J' << num << endl;
		if(num<0 || num>8 || New.row<0 || New.row>8 
			 || New.col<0 || New.col>8){
		//	cout << 'K' << num << endl;
			continue;
		//	cout << 'L' << num << endl;
		}
		//cout << 'M' << num << endl;
		board[New.row][New.col].num = num;
		//cout << 'N' << num << endl;
		FixBoard(New);
		//cout << 'O' << num << endl;
	}
}

bool Done(SpacePtrPtr board)
{
	for(int i = 0; i < 9; i++){
	for(int j = 0; j < 9; j++){
		if(board[i][j].num == 0)
			return false;
	}}
	return true;
}

Update LastOption(SpacePtrPtr board)
{
	Update move;
	for(int i = 0; i < 9; i++){
	for(int j = 0; j < 9; j++){
		if(NumNot(board[i][j].Not) == 8){
			board[i][j].num = LastUnk(board[i][j].Not);
			move.board = board;
			move.row = i;
			move.col = j;
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
		if(!board[i][j].Not[n] && NoOptions(move,n))
			board[i][j].num = n;
			return move;
	}}}
	move.row = -1;
	return move;
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
	int ishift = 0, jshift = 0;
	ishift += 3*(move.row/3);
	jshift += 3*(move.row/3);
	for(int i = ishift; i < (3 + ishift); i++){
	for(int j = jshift; j < (3 + ishift); j++){
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
