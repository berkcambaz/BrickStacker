#include "bahkrengine.h"
#include <iostream>
#include <windows.h>

enum Direction{
	RIGHT=1,
	LEFT=-1,
};


float brickSpeed=5.0f;
int brickFloor=1;
int brickLength=3;
int brickLengthVariable=brickLength;
int brickDirection=RIGHT;
float brickPosition=0.0f;
char brickPattern=254;

bool keyPressed=false;	

bool direction;
int main() {
	BahKrEngine engine;
	srand(time(NULL));
	while(1)
	{
		engine.InitializeTimer();
		
		if (GetAsyncKeyState(VK_SPACE)<0&&keyPressed==false)
    	{
        	keyPressed=true;
			for(int i=1;i<brickLength+1;i++){
				if(brickFloor==1||engine.gameMap[HEIGHT-brickFloor][(int)brickPosition+i]==brickPattern){
					if(brickPosition+i>0&&brickPosition+i<WIDTH-2){
						engine.gameMap[HEIGHT-brickFloor-1][(int)brickPosition+i]=brickPattern;
					}
					else{
						brickLengthVariable--;		
					}
				}
				else{
					brickLengthVariable--;		
				}
			}
			brickLength=brickLengthVariable;
			if(brickLength<=0){
				engine.GoToXY(HEIGHT+5, 0);
				return 1;
			}
			brickFloor++;
			
			direction=rand()%2;
			if(direction){
				brickDirection=LEFT;
				brickPosition=WIDTH-2;
			}
			else{
				brickDirection=RIGHT;
				brickPosition=-brickLength;
			}
			brickSpeed+=2.0f;
		}
		
			
		if (GetAsyncKeyState(VK_SPACE)==0&&keyPressed==true)
		{
		    keyPressed=false;
		}
		
		brickPosition+=brickSpeed*engine.elapsedTime*brickDirection;
		
		
		
		
		engine.SetScreen(HEIGHT, WIDTH);
		for(int i=1;i<brickLength+1;i++){
			if(brickPosition+i>0&&brickPosition+i<WIDTH-2){
					engine.screen[HEIGHT-brickFloor-1][(int)brickPosition+i]=brickPattern;
			}	
		}
		if((int)brickPosition+brickLength>WIDTH||(int)brickPosition<-brickLength){
				brickDirection=-brickDirection;
		}
		engine.PrintScreen(HEIGHT, WIDTH);
		engine.PrintText(direction, 15, 15);
		engine.GoToXY(0,0);
	}
	return 0;
}
