#include "data.h"
#include "Variables.h"
#include "Functions.h"
int main()
{
    Setup();
    SetupBoard();
    while (!(key[KEY_ESC]) && RedLeft > 0 && BlackLeft > 0)
    {
		DrawBackGround();
		Clicks();
		CheckPlay();
        Flip();
    }
    destroy_bitmap(buffer2);
    destroy_bitmap(buffer);
    unload_datafile(data);
}
END_OF_MAIN()
