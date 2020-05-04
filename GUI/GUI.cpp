#include "GUI.h"
#include <time.h>
#include <cstdlib>

//////////////////////////////////////////////////////////////////////////////////////////
GUI::GUI()
{
	DrawingItemsCount = 0;
	pWind = new window(WindWidth+15,WindHeight,0,0); 
	pWind->ChangeTitle("The Castle Battle");

	BackgroundClr = KHAKI;	//Background color
	StatusBarClr = WHITE;	//Status bar color

	//Set color for each enemy type
	DrawingColors[FIGHTER] =  BLUE;		//fighter-enemy color
	DrawingColors[FREEZER] = ORANGE;		//Frosted-enemy color
	DrawingColors[HEALER] =  RED;		//healer-enemy color	

	RegionsLabels[INAC] = "INAC";
	RegionsLabels[ACTV] = "ACTV";
	RegionsLabels[FRST] = "FRST";
	RegionsLabels[KILD] = "KILD";

	ClearStatusBar();
	ClearDrawingArea(); 
	DrawCastleArea();  
}
//////////////////////////////////////////////////////////////////////////////////////////
GUI::~GUI()
{
	delete pWind;
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== INPUT FUNCTIONS ====================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::waitForClick() const
{
	int x,y;
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}
//////////////////////////////////////////////////////////////////////////////////////////
string GUI::GetString() const 
{
	string Label;
	char Key;
	while(1)
	{
		pWind->WaitKeyPress(Key);
		if(Key == 27 )	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if(Key == 13 )	//ENTER key is pressed
			return Label;
		if((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() -1 );			
		else
			Label += Key;
		
		PrintMessage(Label);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////
// ================================== OUTPUT FUNCTIONS ===================================
//////////////////////////////////////////////////////////////////////////////////////////

void GUI::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar
	
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(10, WindHeight - (int) (StatusBarHeight/1.5) , msg); // You may need to change these coordinates later 
	                                                                      // to be able to write multi-line
}
//////////////////////////////////////////////////////////////////////////////////////////
void GUI::DrawString(const int iX, const int iY, const string Text)
{
	pWind->SetPen(DARKRED);
	pWind->SetFont(18, BOLD , BY_NAME, "Arial");   
	pWind->DrawString(iX, iY, Text);
}

//////////////////////////////////////////////////////////////////////////////////////////
void GUI::ClearStatusBar() const
{
	pWind->SetPen(StatusBarClr, 3);
	pWind->SetBrush(StatusBarClr);
	pWind->DrawRectangle(0, WindHeight - StatusBarHeight , WindWidth, WindHeight);	

	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, WindHeight - StatusBarHeight , WindWidth, WindHeight - StatusBarHeight);	
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::ClearDrawingArea() const
{
	// Clearing the Drawing area
	pWind->SetPen(BackgroundClr, 3);
	pWind->SetBrush(BackgroundClr);
	pWind->DrawRectangle(0, MenuBarHeight, WindWidth, WindHeight - StatusBarHeight);
}
///////////////////////////////////////////////////////////////////////////////////
void GUI::DrawCastleArea() const
{
	int L = CastleWidth / 2;

	// 1- Drawing the brown square of the Castle
	pWind->SetPen(BROWN);
	pWind->SetBrush(BROWN);
	pWind->DrawRectangle(CastleStartX, CastleStartY, CastleEndX, CastleEndY);

	// 2- Drawing the 2 brown crossed lines (for making 4 regions)
	pWind->SetPen(BROWN, 3);
	pWind->DrawLine(0, YHalfDrawingArea, WindWidth, YHalfDrawingArea);
	pWind->DrawLine(WindWidth/2, MenuBarHeight, WindWidth/2, WindHeight-StatusBarHeight);

	// 3- Drawing the 2 white crossed lines (inside the Castle)
	pWind->SetPen(WHITE);
	pWind->DrawLine(WindWidth/2, YHalfDrawingArea - CastleWidth/2, WindWidth/2, YHalfDrawingArea + CastleWidth/2);
	pWind->DrawLine(WindWidth/2 - CastleWidth/2, YHalfDrawingArea, WindWidth/2 + CastleWidth/2, YHalfDrawingArea);

	// 5- Writing regions labels
	pWind->SetPen(WHITE);
	pWind->SetFont(20, BOLD , BY_NAME, "Arial");
	pWind->DrawString(CastleStartX + (int)(0.1*L), CastleStartY + 5*L/12, RegionsLabels[INAC]);

	pWind->DrawString(WindWidth/2 + (int)(0.1*L), CastleStartY + 5*L/12, RegionsLabels[ACTV]);

	pWind->DrawString(WindWidth/2 + (int)(0.1*L), YHalfDrawingArea + 5*L/12, RegionsLabels[FRST]); 

	pWind->DrawString(CastleStartX + (int)(0.1*L), YHalfDrawingArea + 5*L/12, RegionsLabels[KILD]);
}
//////////////////////////////////////////////////////////////////////////////////////////
//Draws the passed item in its region
//region count in the numbers of items drawn so far in that item's region
void GUI::DrawSingleItem(const DrawingItem* pDitem, int RegionCount) const       // It is a private function
{

	if (RegionCount > MaxRegionEnemyCount) 
		return; //no more items can be drawn in this region

	int DrawDistance = RegionCount;
	int YPos = 1;
	if(RegionCount>=MaxHorizEnemies )	//max no. of enemies to draw in one line
	{
		DrawDistance = (RegionCount-1)%MaxHorizEnemies + 1;
		YPos = (RegionCount-1) / MaxHorizEnemies + 1; 
	}

	GUI_REGION Region = pDitem->region;

	color pixelClr = BackgroundClr;
	int VertCount;	//Verical enemy count at same distance

	int x, y, refX, refY;
	//First calculate x,y position of the enemy on the output screen
	//It depends on the region and the enemy distance
	switch (Region)
	{
	case INAC_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfDrawingArea - EnemyHeight; //
		x = refX - DrawDistance*EnemyWidth - DrawDistance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		break;
	case ACTV_REG:		
		DrawDistance = pDitem->distance;
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfDrawingArea - EnemyWidth - 1 ; //
		x = refX + (DrawDistance-1)*EnemyWidth + DrawDistance; //(Distance)
		y = refY - YPos*EnemyHeight - YPos; // YPos
		
		
		pixelClr = pWind->GetColor(x+1, y+1);
		VertCount = 0;
		while (pixelClr != BackgroundClr && VertCount<MaxVerticalEnemies) 		
		{ 
			y -= (EnemyHeight+1);
			VertCount++;
			pixelClr = pWind->GetColor(x+1, y+1);
		}
		if(VertCount == MaxVerticalEnemies)	//max enemies that can be drawn at same distance exceeded
			return;		//don't draw this enemy

		break;
	case FRST_REG:
		DrawDistance = pDitem->distance;
		refX = (WindWidth/2 + CastleWidth/2);
		refY = YHalfDrawingArea + EnemyHeight; //
		x = refX + (DrawDistance-1)*EnemyWidth + DrawDistance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos

		pixelClr = pWind->GetColor(x+1, y+1);
		VertCount = 0;
		while (pixelClr != BackgroundClr && VertCount<MaxVerticalEnemies) 		
		{ 
			y += (EnemyHeight+1);
			VertCount++;
			pixelClr = pWind->GetColor(x+1, y+1);
		}
		if(VertCount == MaxVerticalEnemies)	//max enemies that can be drawn at same distance exceeded
			return;		//don't draw this enemy

		break;
	case KILD_REG:
		refX = (WindWidth/2 - CastleWidth/2);
		refY = YHalfDrawingArea + EnemyHeight; //
		x = refX - DrawDistance*EnemyWidth - DrawDistance; //(Distance)
		y = refY + (YPos-1)*EnemyHeight + YPos; // YPos
		break;
	default:
		break;
	}

	// Drawing the item
	pWind->SetPen(pDitem->clr);
	pWind->SetBrush(pDitem->clr);
	pWind->DrawRectangle(x, y, x + EnemyWidth, y + EnemyHeight);
	
}


//////////////////////////////////////////////////////////////////////////////////////////
/* A function to draw all items in DrawingList and ensure there is no overflow in the drawing*/
void GUI::DrawAllItems() 
{
	//Prepare counter for each region
	int RegionsCounts[REG_CNT]={0};	//initlaize all counters to zero

	DrawingItem* pDitem;
	for(int i=0; i<DrawingItemsCount; i++)
	{
		pDitem = DrawingList[i];
		RegionsCounts[pDitem->region]++;
		DrawSingleItem(DrawingList[i],RegionsCounts[pDitem->region]);
	}
}

//prints info on status bar. 
//Info includes timestep and other enemies info as illustrated in project doc
//void GUI::UpdateStatusBar(int TimeStep, double castlehealth, CASTLE_STAT FROZ, int aFighter, int aHealer, int aFreezer, int fFighter, int fHealer, int fFreezer, int kFighter, int kHealer, int kFreezer)	//prints info on status bar. Info includes timestep and other enemies info as illustrated in project doc
//void GUI::UpdateStatusBar(int TimeStep, double castlehealth, CASTLE_STAT FROZ)	//prints info on status bar. Info includes timestep and other enemies info as illustrated in project doc
void GUI::UpdateStatusBar(int TimeStep, double castlehealth, CASTLE_STAT FROZ, int ActiveFighters, int ActiveHealers, int ActiveFreezers, int ActiveCount,
	int FrozenFighters, int FrozenHealers, int FrozenFreezers, int FrostedCount,
	int KilledFighters, int KilledFreezers, int KilledHealers, int KilledCount)
{
		//print current timestep

	//	

		char strTimestep[10];
		itoa(TimeStep, strTimestep, 10);
		PrintMessage(strTimestep);

		pWind->SetPen(BLUE);

		string CASTLE = "CASTLE:";
		pWind->DrawString(110, WindHeight - (int)(StatusBarHeight / 1.5) - 20, CASTLE);


	char strCastleHealth[10];
	itoa(castlehealth, strCastleHealth, 10);
	pWind->DrawString(210, WindHeight - (int)(StatusBarHeight / 1.5) -20, strCastleHealth); 

	if (FROZ== ACTIVE)
	pWind->DrawString(310, WindHeight - (int)(StatusBarHeight / 1.5) -20, "ACTIVE");
	else if (FROZ==FROZEN)
	pWind->DrawString(310, WindHeight - (int)(StatusBarHeight / 1.5) - 20, "FROZEN");
	else if (FROZ==KILD)
	pWind->DrawString(310, WindHeight - (int)(StatusBarHeight / 1.5) - 20, "KILLED");

	pWind->SetPen(DARKGREEN);


	char straFighter[10];
	itoa(ActiveFighters, straFighter, 10);
	pWind->DrawString(110, WindHeight - (int)(StatusBarHeight / 1.5) + 20, straFighter);

	char straHealer[10];
	itoa(ActiveHealers, straHealer, 10);
	pWind->DrawString(210, WindHeight - (int)(StatusBarHeight / 1.5) + 20, straHealer);

	char straFreezer[10];
	itoa(ActiveFreezers, straFreezer, 10);
	pWind->DrawString(310, WindHeight - (int)(StatusBarHeight / 1.5) + 20, straFreezer);

	char strActiveCount[10];
	itoa(ActiveCount, strActiveCount, 10);
	pWind->DrawString(410, WindHeight - (int)(StatusBarHeight / 1.5) + 20, strActiveCount);

	char strfFighter[10];
	itoa(FrozenFighters, strfFighter, 10);
	pWind->DrawString(110, WindHeight - (int)(StatusBarHeight / 1.5) + 40, strfFighter);

	char strfHealer[10];
	itoa(FrozenHealers, strfHealer, 10);
	pWind->DrawString(210, WindHeight - (int)(StatusBarHeight / 1.5) + 40, strfHealer);

	char strfFreezer[10];
	itoa(FrozenFreezers, strfFreezer, 10);
	pWind->DrawString(310, WindHeight - (int)(StatusBarHeight / 1.5) + 40, strfFreezer);

	char strFrostedCount[10];
	itoa(FrostedCount, strFrostedCount, 10);
	pWind->DrawString(410, WindHeight - (int)(StatusBarHeight / 1.5) + 40, strFrostedCount);

	char strkFighter[10];
	itoa(KilledFighters, strkFighter, 10);
	pWind->DrawString(110, WindHeight - (int)(StatusBarHeight / 1.5) + 60, strkFighter);

	char strkHealer[10];
	itoa(KilledHealers, strkHealer, 10);
	pWind->DrawString(210, WindHeight - (int)(StatusBarHeight / 1.5) + 60, strkHealer);

	char strkFreezer[10];
	itoa(KilledFreezers, strkFreezer, 10);
	pWind->DrawString(310, WindHeight - (int)(StatusBarHeight / 1.5) + 60, strkFreezer);

	char strKilledCount[10];
	itoa(KilledCount, strKilledCount, 10);
	pWind->DrawString(410, WindHeight - (int)(StatusBarHeight / 1.5) + 60, strKilledCount);

	string FIGHTERS = "FIGHTERS";
	//itoa(ActiveFighters, straFighter, 10);
	pWind->DrawString(110, WindHeight - (int)(StatusBarHeight / 1.5) , FIGHTERS);

	string HEALERS = "HEALERS";
	//itoa(ActiveFighters, straFighter, 10);
	pWind->DrawString(210, WindHeight - (int)(StatusBarHeight / 1.5), HEALERS);

	string FREEZERS = "FREEZERS";
	//itoa(ActiveFighters, straFighter, 10);
	pWind->DrawString(310, WindHeight - (int)(StatusBarHeight / 1.5), FREEZERS);


	string ACTIVE = "ACTIVE";
	//itoa(ActiveFighters, straFighter, 10);
	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight / 1.5) +20, ACTIVE);

	string FROZEN = "FROZEN";
	//itoa(ActiveFighters, straFighter, 10);
	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight / 1.5)+40, FROZEN);

	string KILLED = "KILLED";
	//itoa(ActiveFighters, straFighter, 10);
	pWind->DrawString(10, WindHeight - (int)(StatusBarHeight / 1.5)+60, KILLED);

	string TOTAL = "TOTAL";
	//itoa(ActiveFighters, straFighter, 10);
	pWind->DrawString(410, WindHeight - (int)(StatusBarHeight / 1.5), TOTAL);

}

//void GUI::UpdateInterface(int TimeStep, double castlehealth, CASTLE_STAT FROZ) 
void GUI::UpdateInterface(int TimeStep, double castlehealth, CASTLE_STAT FROZ, int ActiveFighters, int ActiveHealers, int ActiveFreezers, int ActiveCount,
	int FrozenFighters, int FrozenHealers, int FrozenFreezers, int FrostedCount,
	int KilledFighters, int KilledFreezers, int KilledHealers, int KilledCount)
{
	
	ClearDrawingArea();
	UpdateStatusBar(TimeStep, castlehealth, FROZ, ActiveFighters, ActiveHealers, ActiveFreezers, ActiveCount,
		FrozenFighters, FrozenHealers, FrozenFreezers, FrostedCount,
		KilledFighters, KilledFreezers, KilledHealers, KilledCount);
	DrawCastleArea();
	DrawAllItems();
}

/*
	AddOrderForDrawing: Adds a new item related to the passed Enemy to the drawing list
*/


//void GUI::AddToDrawingList(const Enemy* pE)
void GUI::AddToDrawingList(Enemy* pE)
{
	DrawingItem *pDitem=new DrawingItem;
	pDitem->ID = pE->GetID();
	pDitem->distance = pE->GetDistance();
	pDitem->region= (GUI_REGION) (pE->GetStatus());	//map status to drawing region	

	// IMPORTANT [TO DO]
	// enemy type has been generated randomly here because enemy classes are not written yet
	// in next phases, to know enemy type, you should apply dynamic_cast to pE pointer

	int eType;
	//const Healer* der = dynamic_cast<const Healer*>(pE);
	if (pE->getType() == HEALER)
	{
		eType = 1;

	}
	else if (pE->getType() == FREEZER)
	{
		eType = 2;
	}
	else
		eType = 0;

	pDitem->clr = DrawingColors[eType];
	DrawingList[DrawingItemsCount++] = pDitem;

	//int eType = pDitem->ID%ENMY_TYPE_CNT;	
	//pDitem->clr = DrawingColors[eType];
	//DrawingList[DrawingItemsCount++]=pDitem;	//add item to the list
}


void GUI::ResetDrawingList()
{
	for(int i=0; i<DrawingItemsCount; i++)
		delete DrawingList[i];

	DrawingItemsCount = 0;
}

PROG_MODE	GUI::getGUIMode() const
{
	PROG_MODE Mode;
	do
	{
		PrintMessage("Please select GUI mode: (1)Interactive, (2)StepByStep, (3)Silent, (4)DEMO... ");
		string S = GetString();
		Mode = (PROG_MODE) (atoi(S.c_str())-1);
	}
	while(Mode< 0 || Mode >= MODE_CNT);
	return Mode;
}
