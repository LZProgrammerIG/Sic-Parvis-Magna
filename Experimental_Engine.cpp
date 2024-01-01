#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

#define height 20
#define width 50

// Making array global.
char arra[height][width];

void ShowConsoleCursor(bool showFlag){
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Generate_Walls(){
	// Horizontal Walls.
	for (int i = 0; i < width; i++){
		arra[0][i] = '#';
		arra[height - 1][i] = '#';
	}

	// Vertical Walls.
	for (int i = 0; i < height; i++){
		arra[i][0] = '#';
		arra[i][width - 1] = '#';
	}
}

void Display(){
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			cout << arra[i][j];
		}
		cout << endl;
	}
}

typedef enum{
	UP = 'w',
	DOWN = 's',
	LEFT = 'a',
	RIGHT ='d',
	EXIT = 'q'
}Controls;

typedef struct{
	int X;
	int Y;
}Position;

void Draw_Avatar(Position pos){
	arra[pos.X][pos.Y] = 'O';
	arra[pos.X + 1][pos.Y] = '|';
	arra[pos.X + 1][pos.Y - 1] = '/';
	arra[pos.X + 1][pos.Y + 1] = '\\';
	arra[pos.X + 2][pos.Y - 1] = '/';
	arra[pos.X + 2][pos.Y + 1] = '\\';
}

void Remove_Avatar(Position pos){
	for (int i = pos.X; i <= pos.X + 2; i++){
		for (int j = pos.Y - 1; j <= pos.Y + 1; j++){
			arra[i][j] = ' ';
		}
	}
}

bool Collision_Check(Position pos, char input){
	switch (input){
	case UP:
		return arra[pos.X - 1][pos.Y] != ' ' || 
			arra[pos.X][pos.Y - 1] != ' ' || 
			arra[pos.X][pos.Y + 1] != ' ';
		
	case DOWN:
		return arra[pos.X + 3][pos.Y] != ' ' || 
			arra[pos.X + 3][pos.Y - 1] != ' ' || 
			arra[pos.X + 3][pos.Y + 1] != ' ';
	
	case LEFT:
		return arra[pos.X][pos.Y - 1] != ' ' || 
			arra[pos.X + 1][pos.Y - 2] != ' ' || 
			arra[pos.X + 2][pos.Y - 2] != ' ';

	case RIGHT:
		return arra[pos.X][pos.Y + 1] != ' ' || 
			arra[pos.X + 1][pos.Y + 2] != ' ' || 
			arra[pos.X + 2][pos.Y + 2] != ' ';
	}

	return false;
}

void Character_Movement(Position &pos, bool &Close_Program){
	char input;

	if (kbhit()){
		input = getch();
		
		switch (input){
		case UP:
			if (!Collision_Check(pos, input)){
				Remove_Avatar(pos);
				pos.X--; 
				Draw_Avatar(pos);
			}
			break;

		case DOWN:
			if (!Collision_Check(pos, input)){
				Remove_Avatar(pos);
				pos.X++; 
				Draw_Avatar(pos);
			}
			break;

		case LEFT:
			if (!Collision_Check(pos, input)){
				Remove_Avatar(pos);
				pos.Y--; 
				Draw_Avatar(pos);
			}
			break;

		case RIGHT:
			if (!Collision_Check(pos, input)){
				Remove_Avatar(pos);
				pos.Y++; 
				Draw_Avatar(pos);
			}
			break;

		case EXIT:
			Close_Program = true;
			break;
		}
	}
}

int main(){
	// For creating empty space between walls.
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			arra[i][j] = ' ';
		}
	}

	Generate_Walls();	
	
	// For refreshing frame.
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD Cursor_pos = {0,2};

	// Printing Character in the middle in the beginning.
	Position pos = {height/2, width/2};
	Draw_Avatar(pos);

	// To prevent cursor from rapidly blinking at random places
	// after every frame refresh.
	ShowConsoleCursor(false);
	
	bool Close_Program = false;
	while (!Close_Program){
		SetConsoleCursorPosition(hConsole, Cursor_pos);
		Display();

		Character_Movement(pos, Close_Program);

		Cursor_pos = {0,1};		// Assists frame refreshing.
	}

	ShowConsoleCursor(true);
	cout << endl;
	return 0;
}