#include <allegro.h>
#define Boardloc Boardy * 8 - 8 + Boardx
#define BoardlocHold BoardHoldy * 8 - 8 + BoardHoldx
#define BoardD Boardy + 1 <= 8
#define BoardR Boardx + 1 <= 8
#define BoardU Boardy - 1 >= 1
#define BoardL Boardx - 1 >= 1
#define BoardJD Boardy + 2 <= 8
#define BoardJR Boardx + 2 <= 8
#define BoardJU Boardy - 2 >= 1
#define BoardJL Boardx - 2 >= 1
#define BoardlocUR (Boardy - 1) * 8 - 8 + (Boardx + 1)
#define BoardlocUL (Boardy - 1) * 8 - 8 + (Boardx - 1)
#define BoardlocDR (Boardy + 1) * 8 - 8 + (Boardx + 1)
#define BoardlocDL (Boardy + 1) * 8 - 8 + (Boardx - 1)
#define BoardlocJUR (Boardy - 2) * 8 - 8 + (Boardx + 2)
#define BoardlocJUL (Boardy - 2) * 8 - 8 + (Boardx - 2)
#define BoardlocJDR (Boardy + 2) * 8 - 8 + (Boardx + 2)
#define BoardlocJDL (Boardy + 2) * 8 - 8 + (Boardx - 2)
#define ClickGamePiece (mouse_b & 1) && mouse_x > GameBoard[Boardloc].xloc && mouse_x < GameBoard[Boardloc].xlocmax && mouse_y > GameBoard[Boardloc].yloc && mouse_y < GameBoard[Boardloc].ylocmax && GameBoard[Boardloc].owner == turn
#define ClickValid (mouse_b & 1) && mouse_x > GameBoard[Boardloc].xloc && mouse_x < GameBoard[Boardloc].xlocmax && mouse_y > GameBoard[Boardloc].yloc && mouse_y < GameBoard[Boardloc].ylocmax && GameBoard[Boardloc].valid == 1
struct tagBoard
{
	int xloc, yloc, xlocmax, ylocmax, direction;
	int valid, legal, clicked, owner;
	int jump, jumpable;
	int forcejump, king, StartJump;
}GameBoard[64];
BITMAP *buffer, *buffer2, *activepage;//Used for timers
DATAFILE *data;
int Boardy, Boardx, BoardHoldx, BoardHoldy, BoardHoldx2, BoardHoldy2;
int turn = 2;//Black = 1, Red = 2. Red usually starts first
int MadeJump = 0, JumpHoldValue, DoStartJumps = 0, InJump = 0;
int RedLeft = 12, BlackLeft = 12;
int NoDoSound, volume = 300, pan = 128, pitch = 750;// sound;
