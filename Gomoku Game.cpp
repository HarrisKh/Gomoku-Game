#include <iostream>
#include <time.h>
#include <iomanip>
#include <windows.h>
using namespace std;

#define MR 100
#define MC 100
void color(int k) { HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole, k); }
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT |
		ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState ==

			FROM_LEFT_1ST_BUTTON_PRESSED)

		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void Init(char B[][MC] ,char Psym[],char Pname[][MC],int &turn, int& Nop,
	int& R, int& C, int& WinC,bool isHvH) {
	srand(time(0));
	if (isHvH) {
		cout << "NOP, WinCount,Rows,Cols: ";
		cin >> Nop >> WinC >> R >> C;
		for (int pi = 0; pi < Nop; pi++) {
			cout << "Player " << pi + 1 << " 's sym and name: ";
			cin >> Psym[pi];
			cin.ignore();
			cin.getline(Pname[pi], 200);
		}
	}
	else {
		Nop = 2;
		WinC = 3;
		cout << "Enter dimensions: ";
		cin >> R >> C;
		Psym[0] = 'C';
		char compN[] = "Computer";
		for (int i = 0; i < 9; i++) {
			Pname[0][i] = compN[i];
		}
		cout << "Enetr your symbol and name: ";
		cin >> Psym[1];
		cin.ignore();
		cin.getline(Pname[1], 200);
	}
	for (int ri = 0; ri < R; ri++) {
		for (int ci = 0; ci < C; ci++) {
			B[ri][ci] = '-';
		}
	}
	turn = rand() % Nop;
}

void displayBoard(char B[][MC], int R, int C) {
	system("cls");
	int move = 35;
	cout << endl << endl;
	cout << setw(move);
	color(14);
	cout << "+";

	for (int i = 0; i < C; i++)
		cout << "-";
	cout << "+" << endl;
	for (int ri = 0; ri < R; ri++) {
		cout << setw(move);
		cout << "|";
		for (int ci = 0; ci < C; ci++) {
			if (B[ri][ci] == '-') {
				color(7);
				cout << B[ri][ci];
			}
			else {
				if (B[ri][ci] == 'C')
					color(12);
				else
					color(10);
				cout << B[ri][ci];
			}

		}
		color(14);
		cout << "|" << endl;
	}
	cout << setw(move);
	color(14);
	cout << "+";
	for (int i = 0; i < C; i++)
		cout << "-";
	cout << "+" << endl;

	color(7);
}

void displayMsg(char Pname[], char sym) {
	color(11);
	cout << Pname << " (" << sym<<")'s Turn: ";
	color(7);
}
//void selectPos(int& r, int& c) {
//	cin >> r >> c;
//	r--;
//	c--;
//}
void selectPos(int& r, int& c){
	int mR, mC;
	getRowColbyLeftClick(mR, mC);
	int X = 35 ;
	int Y = 3;
	r = mR - Y;
	c = mC- X;

}

void updateBoard(char B[][MC], int r, int c, char sym) {
	B[r][c] = sym;
}
bool isValid(char B[][MC], int r, int c, int R, int C) {
	bool valid = (r >= 0 and r < R and c >= 0 and c < C and B[r][c] == '-');
	if (!valid) {
		cout << "Enter a valid move: ";
		return false;
	}
	return true;
}
void turnChange(int& turn,int Nop) {
	turn = (turn + 1) % Nop;
}
bool horiCheck(char B[][MC], int C, int winC, char sym, int r, int c) {
	int count = 1;
	for (int Cc = c - 1; Cc >= 0 and B[r][Cc] == sym; Cc--)
		count++;
	for (int Cc = c + 1; Cc <C and B[r][Cc] == sym; Cc++)
		count++;
	return count >= winC;
}
bool vertCheck(char B[][MC], int R, int winC, char sym, int r, int c) {
	int count = 1;
	for (int Rr = r - 1; Rr >= 0 and B[Rr][c] == sym; Rr--)
		count++;
	for (int Rr = r + 1; Rr <R and B[Rr][c] == sym; Rr++)
		count++;
	return count >= winC;
}
bool rightDiagCheck(char B[][MC], int R,int C, int winC, char sym, int r, int c) {
	int count = 1;
	int Rr = r - 1, Cc = c - 1;
	while (Rr >= 0 and Cc >= 0 and B[Rr][Cc] == sym) {
		count++; 
		Rr--; 
		Cc--; 
	}
	Rr = r + 1; Cc = c + 1;
	while (Rr < R and Cc < C and B[Rr][Cc] == sym) { 
		count++;
		Rr++; 
		Cc++;
	}
	return count >= winC;
}
bool leftDiagCheck(char B[][MC], int R,int C, int winC, char sym, int r, int c) {
	int count = 1;
	int Rr = r - 1, Cc = c + 1;
	while (Rr >= 0 and Cc <C and B[Rr][Cc] == sym) {
		count++;
		Rr--; 
		Cc++; 
	}
	Rr = r + 1; Cc = c - 1;
	while (Rr < R and Cc >=0 and B[Rr][Cc] == sym) { 
		count++;
		Rr++;
		Cc--;
	}
	return count >= winC;
}
bool Tcheck(char B[][MC], int R, int C, int winC, char sym, int r, int c) {
	int count = 1;
	int count1 = 1;
	if (horiCheck(B, C, winC, sym, r, c) == sym) {
		for (int Rr = r - 1; Rr >= 0 and B[Rr][c]; Rr--)
			count1++;
		for (int Rr = r; Rr < R and B[Rr][c] == sym; Rr++)
			count++;
	}
	if (count1 > 1)
		return false;
	else
		return count >= winC+1;
}

bool isWinHere(char B[][MC], int R, int C, int WinC, char sym, int r, int c) {
	if (horiCheck(B, C, WinC, sym, r, c))
		return true;
	if (vertCheck(B, R, WinC, sym, r, c)) 
		return true;
	if (rightDiagCheck(B, R, C, WinC, sym, r, c))
		return true;
	if (leftDiagCheck(B, R, C, WinC, sym, r, c)) 
		return true;
	if (Tcheck(B, R, C, WinC, sym, r, c)) 
		return true;
	return false;
}

bool isDraw(char B[][MC], int R, int C) {
	for (int r = 0; r < R; r++) 
		for (int c = 0; c < C; c++) 
			if (B[r][c] == '-')
				return false;
	return true;
}
void computerMove(char B[][MC], int R, int C, int WinC, char humanSym, char compSym, int& sr, int& sc) {
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			if (B[r][c] == '-') {
				B[r][c] = compSym;
				if (isWinHere(B, R, C, WinC, compSym, r, c)) {
					sr = r;
					sc = c;
					B[r][c] = '-';
					return;
				}
				B[r][c] = '-';
			}
		}
		
	}
	for (int r = 0; r < R; r++) {
		for (int c = 0; c < C; c++) {
			if (B[r][c] == '-') {
				B[r][c] = humanSym;
				if (isWinHere(B, R, C, WinC, humanSym, r, c)) {
					sr = r;
					sc = c;
					B[r][c] = '-';
					return;
				}
				B[r][c] = '-';
			}
		}
	}
	do {
		sr = rand() % R;
		sc = rand() % C;
	} while (B[sr][sc] != '-');
}
int main() {
	int Nop, turn, WinC, sr, sc,R,C;
	char B[MR][MC], Psym[MR],Pname[MR][MC];
	color(11);
	cout << "Select mode:" << endl<< "1. Human vs Human" << endl
		<< "2. Human Vs computer" << endl;
	int choice;
	bool HvH;
	cin >> choice;
	if (choice == 1)
		HvH = true;
	else
		HvH = false;

	Init(B, Psym, Pname,  turn, Nop,  R, C, WinC,HvH);
	displayBoard(B, R, C);
	do {
		color(11);
		if (HvH or turn ==1) {
			displayMsg(Pname[turn], Psym[turn]);
			do {
				selectPos(sr, sc);
			} while (!isValid(B, sr, sc, R, C));
		}
		else{
			computerMove(B, R, C, WinC, Psym[1], Psym[0], sr, sc);
		}
		updateBoard(B, sr, sc, Psym[turn]);
		displayBoard(B, R, C);
		if (isWinHere(B, R, C, WinC, Psym[turn], sr, sc)) {
			color(10);
			cout <<endl<< setw(35) << Pname[turn] << " Wins" << endl;
			break;
		}
		if (isDraw(B, R, C)) {
			color(10);
			cout <<setw(35) << "  Game Draw" <<endl;
			break;
		}
		turnChange(turn,Nop);
	} while (true);
		color(7);
	return 0;
}