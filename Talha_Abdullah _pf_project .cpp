// Adding Header files

#include<iostream>
#include<conio.h>
#include<dos.h> 
#include <windows.h>
#include <time.h>
// defining screen and window size
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70 

using namespace std; 
 // defining global variables
 
  // handle to the console window
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
// current position of the cursor
COORD CursorPosition;

// array to store y coordinates of enemies
int enemyY[3];
// array to store X coordinates of enemies
int enemyX[3];
// array to store flag to check if enemy exists
int enemyFlag[3];
// 2D array to store the car shape
char car[4][4] = { ' ','±','±',' ', 
					'±','±','±','±', 
					' ','±','±',' ',
					'±','±','±','±' }; 
					
 // initial position of the car
int carPos = WIN_WIDTH/2;
// initial score
int score = 0; 
// function to set cursor position
void gotoxy(int x, int y){
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}// function to set cursor properties
void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;	
	
	CONSOLE_CURSOR_INFO lpCursor;	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

// function to draw game border
void drawBorder(){  
	for(int i=0; i<SCREEN_HEIGHT; i++){
		for(int j=0; j<17; j++){
			gotoxy(0+j,i); cout<<"±";
			gotoxy(WIN_WIDTH-j,i); cout<<"±";
		}
	} 
	for(int i=0; i<SCREEN_HEIGHT; i++){
		gotoxy(SCREEN_WIDTH,i); cout<<"±";
	} 
}
// function to generate enemy car at random x coordinate
void genEnemy(int ind){
	enemyX[ind] = 17 + rand()%(33);  
}
// function to draw enemy car
void drawEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]);   cout<<"****";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<" ** "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"****"; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<" ** ";  
	} 
}
// function to erase enemy car
void eraseEnemy(int ind){
	if( enemyFlag[ind] == true ){
		gotoxy(enemyX[ind], enemyY[ind]); cout<<"    ";  
		gotoxy(enemyX[ind], enemyY[ind]+1); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+2); cout<<"    "; 
		gotoxy(enemyX[ind], enemyY[ind]+3); cout<<"    "; 
	} 
}
// function to reset enemy car after it goes out of screen
void resetEnemy(int ind){
	eraseEnemy(ind);
	enemyY[ind] = 1;
	genEnemy(ind);
}
// function to draw car
void drawCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<car[i][j];
		}
	}
}
// function to erase car
void eraseCar(){
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+carPos, i+22); cout<<" ";
		}
	}
}
 // This function checks for collision between the player's car and the enemy car.
int collision(){
	// checks if the enemy car has reached the bottom of the screen
	if( enemyY[0]+4 >= 23 ){
		 // checks if the player's car has collided with the enemy car
		if( enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9  ){
			 // returns 1 if there is a collision
			return 1;
		}
	}
	 // returns 0 if there is no collision
	return 0;
} 
// This function displays the game over screen and waits for user input to return to the main menu.
void gameover(){
	system("cls");
	cout<<endl;
	cout<<"\t\t--------------------------"<<endl;
	cout<<"\t\t-------- Game Over -------"<<endl;
	cout<<"\t\t--------------------------"<<endl<<endl;
	cout<<"\t\tPress any key to go back to menu.";
	getch();
}
// This function updates the score on the screen.

void updateScore(){
	gotoxy(WIN_WIDTH + 7, 5);cout<<"Score: "<<score<<endl;
}
// This function displays the instructions screen and waits for user input to return to the main menu.
void instructions(){
	//clear the Screen
	system("cls");
	cout<<"Instructions";
	cout<<"\n----------------";
	cout<<"\n Avoid Cars by moving left or right. ";
	cout<<"\n\n Press 'a' to move left";
	cout<<"\n Press 'd' to move right";
	cout<<"\n Press 'escape' to exit";
	cout<<"\n\nPress any key to go back to menu";
	// waits for user input
	getch();
}
// This function starts the game and handles player input and enemy movement.
void play(){
	// sets the initial position of the player's car
	carPos = -1 + WIN_WIDTH/2;
	// sets the initial score to 0
	score = 0;
	// sets the flag for the first enemy car to 1
	enemyFlag[0] = 1;
	// sets the flag for the second enemy car to 0
	enemyFlag[1] = 0;
	// sets the initial position of the enemy cars
	enemyY[0] = enemyY[1] = 1;
 // clears the screen
system("cls");
 // draws the border of the game area
 drawBorder();
// displays the initial score
updateScore(); 
 // generates the first enemy car
 genEnemy(0);
 // generates the second enemy car
 genEnemy(1);
// displays the game title
gotoxy(WIN_WIDTH + 7, 2);cout<<"Car Game"; 
// displays a separator line
gotoxy(WIN_WIDTH + 6, 4);cout<<"----------";
 // displays a separator line
gotoxy(WIN_WIDTH + 6, 6);cout<<"----------"; 
// displays the control section title

gotoxy(WIN_WIDTH + 7, 12);cout<<"Control "; 
 // displays a separator line

gotoxy(WIN_WIDTH + 7, 13);cout<<"-------- ";
 // displays the instruction to move left

gotoxy(WIN_WIDTH + 2, 14);cout<<" A Key - Left"; 

// displays the instruction to move right

gotoxy(WIN_WIDTH + 2, 15);cout<<" D Key - Right"; 
// displays a message to start the game

gotoxy(18, 5);cout<<"Press any key to start";
 // waits for user input to start the game 
getch();
// clears the message to start the game
gotoxy(18, 5);cout<<"                      "; 


   // This is the game loop
while (1) {
    // Check if a key is pressed
    if (kbhit()) {
        // Get the pressed key
        char ch = getch();
        // Move the car left if 'a' or 'A' is pressed
        if (ch == 'a' || ch == 'A') {
            if (carPos > 18)
                carPos -= 4;
        }
        // Move the car right if 'd' or 'D' is pressed
        if (ch == 'd' || ch == 'D') {
            if (carPos < 50)
                carPos += 4;
        }
        // Exit the game if the escape key is pressed
        if (ch == 27) {
            break;
        }
    }

    // Draw the car and the enemies
    drawCar();
    drawEnemy(0);
    drawEnemy(1);

    // Check for collision
    if (collision() == 1) {
        // If there's a collision, end the game and return
        gameover();
        return;
    }

    // Wait for 50 milliseconds
    Sleep(50);

    // Erase the car and the enemies
    eraseCar();
    eraseEnemy(0);
    eraseEnemy(1);

    // Update the positions of the enemies
    if (enemyY[0] == 10)
        if (enemyFlag[1] == 0)
            enemyFlag[1] = 1;
    if (enemyFlag[0] == 1)
        enemyY[0] += 1;
    if (enemyFlag[1] == 1)
        enemyY[1] += 1;

    // Check if an enemy has reached the bottom of the screen
    if (enemyY[0] > SCREEN_HEIGHT - 4) {
        resetEnemy(0);
        score++;
        updateScore();
    }
    if (enemyY[1] > SCREEN_HEIGHT - 4) {
        resetEnemy(1);
        score++;
        updateScore();
    }
}}

int main() {
    // Hide the cursor and initialize the random number generator
    setcursor(0, 0);
    srand((unsigned)time(NULL));

    // Display the menu and get the user's choice
    do {
        system("cls");
        gotoxy(10, 5); cout << " -------------------------- ";
        gotoxy(10, 6); cout << " |     MEKAZ Car Game     | ";
        gotoxy(10, 7); cout << " --------------------------";
        gotoxy(10, 9); cout << "1. Start Game";
        gotoxy(10, 10); cout << "2. Instructions";
        gotoxy(10, 11); cout << "3. Quit";
        gotoxy(10, 13); cout << "Select option: ";
        char op = getche();

        // Start the game if the user chooses option 1
        if (op == '1')
            play();
        // Show the instructions if the user chooses option 2
        else if (op == '2')
            instructions();
        // Exit the program if the user chooses option 3
        else if (op == '3')
            exit(0);
    } while (1);

    return 0;
}

