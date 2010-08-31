void Setup()
{
    allegro_init();
    set_color_depth(desktop_color_depth());
    install_mouse();
    install_keyboard();
    install_timer();
    srand(time(NULL));
    install_sound(DIGI_AUTODETECT, MIDI_NONE, "");
    int ret = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 480, 480, 0, 0); //INIT Video
    buffer = create_video_bitmap(SCREEN_W, SCREEN_H);
    buffer2 = create_video_bitmap(SCREEN_W, SCREEN_H);
    activepage = buffer2;
    data = load_datafile("data.dat");
}
void Flip()
{
     show_video_bitmap(activepage); //Page flipping :) fun stuff
     if (activepage == buffer)
         activepage = buffer2;
     else
         activepage = buffer;
     clear_to_color(activepage, makecol(0, 0, 0));
}
void DrawBackGround()
{
	draw_sprite(activepage, data[BOARD_BMP].dat, 0, 0);
	for (Boardy = 1; Boardy <= 8; Boardy++)
        for (Boardx = 1; Boardx <= 8; Boardx++)
        {
			if (GameBoard[Boardloc].valid == 1)
                rect(activepage, GameBoard[Boardloc].xloc, GameBoard[Boardloc].yloc, GameBoard[Boardloc].xlocmax, GameBoard[Boardloc].ylocmax, makecol(255,255,255));
			if (GameBoard[Boardloc].owner == 1)
			    if (GameBoard[Boardloc].clicked == 1)
			        draw_sprite(activepage, data[BLACKPICK_BMP].dat, GameBoard[Boardloc].xloc, GameBoard[Boardloc].yloc);
				else
					draw_sprite(activepage, data[BLACK_BMP].dat, GameBoard[Boardloc].xloc, GameBoard[Boardloc].yloc);
			if (GameBoard[Boardloc].owner == 2)
			    if (GameBoard[Boardloc].clicked == 1)
			        draw_sprite(activepage, data[REDPICK_BMP].dat, GameBoard[Boardloc].xloc, GameBoard[Boardloc].yloc);
			    else
			    	draw_sprite(activepage, data[RED_BMP].dat, GameBoard[Boardloc].xloc, GameBoard[Boardloc].yloc);
            if (GameBoard[Boardloc].king == 1)
				draw_sprite(activepage, data[CROWN_BMP].dat, GameBoard[Boardloc].xloc, GameBoard[Boardloc].yloc);
			if (GameBoard[Boardloc].StartJump == 1)
			    rect(activepage, GameBoard[Boardloc].xloc, GameBoard[Boardloc].yloc, GameBoard[Boardloc].xlocmax, GameBoard[Boardloc].ylocmax, makecol(0,255,0));
		}
		circle(activepage, mouse_x, mouse_y, 5, makecol(255, 255, 0));
}
void SetupBoard()
{
    for (Boardy = 1; Boardy <= 8; Boardy++)
        for (Boardx = 1; Boardx <= 8; Boardx++)
			if (Boardy % 2 == 0 && Boardx % 2 == 1 || Boardy % 2 == 1 && Boardx % 2 == 0)
            {
				GameBoard[Boardloc].legal = 1;
				GameBoard[Boardloc].xloc = Boardx * 60 - 61;
				GameBoard[Boardloc].yloc = Boardy * 60 - 61;
				GameBoard[Boardloc].xlocmax = Boardx * 60 - 1;
				GameBoard[Boardloc].ylocmax = Boardy * 60 - 1;
				if (Boardy <= 3)
				{
					GameBoard[Boardloc].owner = 1;
					GameBoard[Boardloc].direction = 1;
				}
				if (Boardy >= 4 && Boardy <= 5)
				{
					GameBoard[Boardloc].owner = 0;
					GameBoard[Boardloc].direction = 0;
				}
				if (Boardy >= 6)
				{
					GameBoard[Boardloc].owner = 2;
					GameBoard[Boardloc].direction = 2;
				}
			}
			else
				GameBoard[Boardloc].legal = 0;
}
void Clicks()
{
	if (!(mouse_b & 1))
	    NoDoSound = 0;
	for (Boardy = 1; Boardy <= 8; Boardy++)
	    for (Boardx = 1; Boardx <= 8; Boardx++)
	        if (ClickGamePiece) //Check Variables for this forumla
     	   {
				if (!NoDoSound)
				    play_sample((SAMPLE *)data[BUTTONCLICK_WAV].dat, volume, pan, pitch, 0);
				NoDoSound++;
				BoardHoldx = Boardx;
				BoardHoldy = Boardy;
				DoStartJumps = 0;
                for (Boardy = 1; Boardy <=8;Boardy++)
					for (Boardx = 1; Boardx <= 8; Boardx++)
					{
						GameBoard[Boardloc].clicked = 0;
						GameBoard[Boardloc].valid = 0;
						if (GameBoard[Boardloc].StartJump == 1)
						    DoStartJumps++;
					}
                Boardx = BoardHoldx;
				Boardy = BoardHoldy;
   				if (GameBoard[Boardloc].direction == 1 || GameBoard[Boardloc].direction == 3)//black
				{
					if (GameBoard[BoardlocDL].owner == 0 && BoardD && BoardL && !MadeJump && !DoStartJumps)
					{
						GameBoard[Boardloc].clicked = 1;
						GameBoard[BoardlocDL].valid = 1;
					}
					if (GameBoard[BoardlocDR].owner == 0 && BoardD && BoardR && !MadeJump && !DoStartJumps)
					{
						GameBoard[Boardloc].clicked = 1;
						GameBoard[BoardlocDR].valid = 1;
					}
					if (GameBoard[BoardlocJDL].owner == 0 && GameBoard[BoardlocDL].owner != turn && GameBoard[BoardlocDL].owner != 0 && BoardJD && BoardJL)
					{
						if (InJump == 0 || InJump != 0 && GameBoard[Boardloc].StartJump !=0)
						{
							JumpHoldValue++;
					    	GameBoard[Boardloc].clicked = 1;
					   	 	GameBoard[BoardlocJDL].valid = 1;
					    	GameBoard[BoardlocJDL].jumpable = JumpHoldValue;
					    	GameBoard[BoardlocDL].jump = JumpHoldValue;
						}
					}
					if (GameBoard[BoardlocJDR].owner == 0 && GameBoard[BoardlocDR].owner != turn && GameBoard[BoardlocDR].owner != 0 && BoardJD && BoardJR)
					{
                        if (InJump == 0 || InJump != 0 && GameBoard[Boardloc].StartJump !=0)
						{
							JumpHoldValue++;
							GameBoard[Boardloc].clicked = 1;
							GameBoard[BoardlocJDR].valid = 1;
							GameBoard[BoardlocJDR].jumpable = JumpHoldValue;
							GameBoard[BoardlocDR].jump = JumpHoldValue;
						}
					}
				}
				if (GameBoard[Boardloc].direction == 2 || GameBoard[Boardloc].direction == 3)
				{
                	if (GameBoard[BoardlocUL].owner == 0 && BoardU && BoardL && !MadeJump && !DoStartJumps)
	                {
						GameBoard[Boardloc].clicked = 1;
						GameBoard[BoardlocUL].valid = 1;
					}
					if (GameBoard[BoardlocUR].owner == 0 && BoardU && BoardR && !MadeJump && !DoStartJumps)
					{
						GameBoard[Boardloc].clicked = 1;
						GameBoard[BoardlocUR].valid = 1;
					}
                    if (GameBoard[BoardlocJUL].owner == 0 && GameBoard[BoardlocUL].owner != turn && GameBoard[BoardlocUL].owner != 0 && BoardJU && BoardJL)
                    {
                        if (InJump == 0 || InJump != 0 && GameBoard[Boardloc].StartJump !=0)
						{
							JumpHoldValue++;
					    	GameBoard[Boardloc].clicked = 1;
					    	GameBoard[BoardlocJUL].valid = 1;
					    	GameBoard[BoardlocJUL].jumpable = JumpHoldValue;
					    	GameBoard[BoardlocUL].jump = JumpHoldValue;
						}
					}
					if (GameBoard[BoardlocJUR].owner == 0 && GameBoard[BoardlocUR].owner != turn && GameBoard[BoardlocUR].owner != 0 && BoardJU && BoardJR)
					{
                        if (InJump == 0 || InJump != 0 && GameBoard[Boardloc].StartJump !=0)
						{
							JumpHoldValue++;
							GameBoard[Boardloc].clicked = 1;
							GameBoard[BoardlocJUR].valid = 1;
							GameBoard[BoardlocJUR].jumpable = JumpHoldValue;
							GameBoard[BoardlocUR].jump = JumpHoldValue;
						}
					}
				}
			}
}
void EndTurn()
{
	for (Boardy = 1; Boardy <= 8; Boardy++)
	    for (Boardx = 1; Boardx <= 8; Boardx++)
	        if (GameBoard[Boardloc].forcejump == 1)
     	   {
				if (GameBoard[Boardloc].owner == 2 && !GameBoard[Boardloc].king)
				{
					if (GameBoard[BoardlocJUL].owner == 0 && GameBoard[BoardlocUL].owner != turn && GameBoard[BoardlocUL].owner != 0 && BoardJU && BoardJL || GameBoard[BoardlocJUR].owner == 0 && GameBoard[BoardlocUR].owner != turn && GameBoard[BoardlocUR].owner != 0 && BoardJU && BoardJR){}
					else
					    MadeJump = 0;
				}
				if (GameBoard[Boardloc].owner == 1 && !GameBoard[Boardloc].king)
				{
					if (GameBoard[BoardlocJDR].owner == 0 && GameBoard[BoardlocDR].owner != turn && GameBoard[BoardlocDR].owner != 0 && BoardJD && BoardJR || GameBoard[BoardlocJDL].owner == 0 && GameBoard[BoardlocDL].owner != turn && GameBoard[BoardlocDL].owner != 0 && BoardJD && BoardJL){}
					else
					    MadeJump = 0;
				}
				if (GameBoard[Boardloc].king == 1)
				{
                    if (GameBoard[BoardlocJUL].owner == 0 && GameBoard[BoardlocUL].owner != turn && GameBoard[BoardlocUL].owner != 0 && BoardJU && BoardJL || GameBoard[BoardlocJUR].owner == 0 && GameBoard[BoardlocUR].owner != turn && GameBoard[BoardlocUR].owner != 0 && BoardJU && BoardJR || GameBoard[BoardlocJDR].owner == 0 && GameBoard[BoardlocDR].owner != turn && GameBoard[BoardlocDR].owner != 0 && BoardJD && BoardJR || GameBoard[BoardlocJDL].owner == 0 && GameBoard[BoardlocDL].owner != turn && GameBoard[BoardlocDL].owner != 0 && BoardJD && BoardJL){}
					else
					    MadeJump = 0;
				}
			}
	if (!MadeJump)
	{
	    JumpHoldValue = 0;
	    InJump = 0;
		if (turn == 1)
	    	turn = 2;
		else
	    	turn = 1;
		BlackLeft = 0;
		RedLeft = 0;
        for (Boardy = 1; Boardy <= 8; Boardy++)
	    	for (Boardx = 1; Boardx <= 8; Boardx++)
	 	   {
				if (GameBoard[Boardloc].owner == 1)
				    BlackLeft++;
				if (GameBoard[Boardloc].owner == 2)
				    RedLeft++;
    			GameBoard[Boardloc].StartJump = 0;
				if (turn == 1 || GameBoard[Boardloc].direction == 3)
					if (GameBoard[Boardloc].direction == 1 || GameBoard[Boardloc].direction == 3)
					{
						if (GameBoard[BoardlocJDR].owner == 0 && GameBoard[BoardlocDR].owner != turn && GameBoard[BoardlocDR].owner != 0 && GameBoard[Boardloc].owner != GameBoard[BoardlocDR].owner && BoardJD && BoardJR || GameBoard[BoardlocJDL].owner == 0 && GameBoard[BoardlocDL].owner != turn && GameBoard[BoardlocDL].owner != 0 && GameBoard[Boardloc].owner != GameBoard[BoardlocDL].owner && BoardJD && BoardJL)
						{
                        	GameBoard[Boardloc].StartJump = 1;
						}
					}
				if (turn == 2 || GameBoard[Boardloc].direction == 3)
					if (GameBoard[Boardloc].direction == 2 || GameBoard[Boardloc].direction == 3)
					{
						if (GameBoard[BoardlocJUR].owner == 0 && GameBoard[BoardlocUR].owner != turn && GameBoard[BoardlocUR].owner != 0 && GameBoard[Boardloc].owner != GameBoard[BoardlocUR].owner && BoardJU && BoardJR || GameBoard[BoardlocJUL].owner == 0 && GameBoard[BoardlocUL].owner != turn && GameBoard[BoardlocUL].owner != 0 && GameBoard[Boardloc].owner != GameBoard[BoardlocUL].owner && BoardJU && BoardJL)
						{
                        	GameBoard[Boardloc].StartJump = 1;
						}
					}
	    	    	GameBoard[Boardloc].forcejump = 0;
			}
	}
	for (Boardy = 1; Boardy <= 8; Boardy++)
	    for (Boardx = 1; Boardx <= 8; Boardx++)
 	   {
			if (Boardy == 1 && GameBoard[Boardloc].owner == 2 && GameBoard[Boardloc].king != 1|| Boardy == 8 && GameBoard[Boardloc].owner == 1 && GameBoard[Boardloc].king != 1)
			{
				GameBoard[Boardloc].king = 1;
				play_sample((SAMPLE *)data[FANFARE_WAV].dat, volume, pan, 1250, 0);
			}
			GameBoard[Boardloc].clicked = 0;
			GameBoard[Boardloc].valid = 0;
			GameBoard[Boardloc].jump = 0;
			GameBoard[Boardloc].jumpable = 0;
			GameBoard[Boardloc].forcejump = 0;
			if (GameBoard[Boardloc].owner == 2 && !GameBoard[Boardloc].king)
				GameBoard[Boardloc].direction = 2;
			if (GameBoard[Boardloc].owner == 1 && !GameBoard[Boardloc].king)
				GameBoard[Boardloc].direction = 1;
			if (GameBoard[Boardloc].king == 1)
				GameBoard[Boardloc].direction = 3;
			if (GameBoard[Boardloc].owner == 0)
			{
			    GameBoard[Boardloc].king = 0;
			    GameBoard[Boardloc].direction = 0;
			    GameBoard[Boardloc].StartJump = 0;
			}
		}
}
void CheckPlay()
{
	for (Boardy = 1; Boardy <= 8; Boardy++)
	    for (Boardx = 1; Boardx <= 8; Boardx++)
			if (ClickValid)
			{
				GameBoard[Boardloc].owner = turn;
				BoardHoldx = Boardx;
				BoardHoldy = Boardy;
				if (GameBoard[Boardloc].jumpable != 0)
					for (Boardy = 1; Boardy <= 8; Boardy++)
						for (Boardx = 1; Boardx <= 8; Boardx++)
						{
							if (GameBoard[Boardloc].jump == GameBoard[BoardlocHold].jumpable)
							{
								GameBoard[Boardloc].owner = 0;
								GameBoard[Boardloc].StartJump = 0;
								GameBoard[BoardlocHold].forcejump = 1;
								BoardHoldx2 = Boardx;
								BoardHoldy2 = Boardy;
								for (Boardy = 1; Boardy <=8; Boardy++)
								    for (Boardx = 1; Boardx <= 8; Boardx++)
								            GameBoard[Boardloc].StartJump = 0;
								Boardx = BoardHoldx2;
								Boardy = BoardHoldy2;
								GameBoard[BoardlocHold].StartJump = 1;
								InJump = 1;
								MadeJump = 1;
							}
						}
				for (Boardy = 1; Boardy <= 8; Boardy++)
				    for (Boardx = 1; Boardx <= 8; Boardx++)
    				{
						if (GameBoard[Boardloc].clicked == 1)
						{
							if (GameBoard[Boardloc].king == 1)
							    GameBoard[BoardlocHold].king = 1;
							GameBoard[Boardloc].clicked = 0;
							GameBoard[Boardloc].owner = 0;
						}
					}
				EndTurn();
				Boardy = BoardHoldy;
				Boardx = BoardHoldx;
				GameBoard[Boardloc].valid = 0;
			}
}
