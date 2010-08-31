struct VirtualBoard
{
	int Is_X_Locaction, Is_Y_Location, Is_X_Location_Max, Is_Y_Location_Max, Is_Direction;
	int Is_Valid, Is_Legal, Is_Clicked, Is_Owner;
	int Is_Jump, Is_Jumpable;
	int Is_Force_Jump, Is_King, Is_Start_Jump;
}VirtualGameBoard[64];
void SetStart()
{
}
int AI_Send_Board(int BoxNum, int Box_Own, int King_Me)
{
	VirtualGameBoard[BoxNum].Is_Owner = Box_Own;
	VirtualGameBoard[BoxNum].Is_King = King_Me;
}
int AI_Check_Move_State()
{
}
int AI_Value_Move()
{
}

