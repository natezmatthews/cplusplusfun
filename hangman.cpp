#include <iostream>
#include <string>
using namespace std;

struct Letter {
	char letter;
	bool guessed;
};
struct Word {
	Letter *array;
	int size;
};

Word Store_word();
void Print_Hangman(int oops);
void Print_Spaces(Word word);
void Guess_Letter(Word word, int *oops);
void Print_Word(Word word);
bool All_Guessed(Word word);

int main ()
{
	int oops = 0;
	Word word = Store_word();
	Print_Hangman(oops);
	Print_Spaces(word);
	while(true){
		Guess_Letter(word,&oops);
		Print_Hangman(oops);
		Print_Spaces(word);
		if (oops >= 6 ){
			cout << "You lose. The word was \"";
			Print_Word(word);
			cout << "\"." << endl;
			break;
		}
		if ( All_Guessed(word) ){
			cout << "You win!" << endl;
			break;
		}
	}

	delete [] word.array;
	return 0;
}

Word Store_word()
{
	cout << "What word? ";
	string input;
	cin >> input;
	int len = input.length();
	Letter* array = new Letter [len];
	for (int i = 0; i < len; i++){
		array[i].letter  = input[i];
		array[i].guessed = false;
	}
	Word word;
	word.array = array;
	word.size  = len;
	return word;
}

void Print_Hangman(int oops)
{
	char head, armL, torso, armR, legL, legR;
	head = armL = torso = armR = legL = legR = ' ';
	if (oops >= 1) head  = 'O';
	if (oops >= 3) armL  = '-';
	if (oops >= 2) torso = '|';
	if (oops >= 4) armR  = '-';
	if (oops >= 5) legL  = '/';
	if (oops >= 6) legR  = '\\';
	string s = "    ";
	cout << s << " _____ " << endl
	     << s << " |    |" << endl
	     << s << ' ' << head << "    |" << endl
	     << s << armL << torso << armR << "   |" << endl
	     << s << legL << ' ' << legR << "   |" << endl
	     << s << "      |" << endl
	     << s << "=======" << endl;
/*
      _____
      |    |
      O    |
     -|-   |
     / \   |
           |
     =======
*/
}

void Print_Spaces(Word word)
{
	cout << ' ';
	for (int i = 0; i < word.size; i++){
		if (word.array[i].guessed == true)
			cout << word.array[i].letter;
		else cout << '*';
	}
	cout << endl;
}

void Guess_Letter(Word word, int *oops)
{
	cout << "Guess a letter: ";
	char guess;
	cin >> guess;
	bool found = false;
	for(int i = 0; i < word.size; i++){
		if (word.array[i].letter == guess){
			word.array[i].guessed = true;
			found = true;
		}
	}
	if (found)
		cout << "Yup!" << endl;
	else {
		cout << "Nope." << endl;
		(*oops)++;
	}
}

void Print_Word(Word word)
{
	for (int i = 0; i < word.size; i++)
		cout << word.array[i].letter;
}

bool All_Guessed(Word word)
{
	for (int i = 0; i < word.size; i++){
		if (word.array[i].guessed == false)
			return false;
	}
	return true;
}
