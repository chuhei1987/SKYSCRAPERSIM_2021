/* $Id$ */

/*
	Scalable Building Simulator - Call Button Subsystem Class
	The Skyscraper Project - Version 1.8 Alpha
	Copyright (C)2004-2010 Ryan Thoryk
	http://www.skyscrapersim.com
	http://sourceforge.net/projects/skyscraper
	Contact - ryan@tliquest.net

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "globals.h"
#include "sbs.h"
#include "callbutton.h"
#include "camera.h"
#include "elevator.h"
#include "unix.h"

extern SBS *sbs; //external pointer to the SBS engine

CallButton::CallButton(std::vector<int> &elevators, int floornum, int number, const char *BackTexture, const char *UpButtonTexture, const char *UpButtonTexture_Lit, const char *DownButtonTexture, const char *DownButtonTexture_Lit, float CenterX, float CenterZ, float voffset, const char *direction, float BackWidth, float BackHeight, bool ShowBack, float tw, float th)
{
	//create a set of call buttons

	//set up SBS object
	object = new Object();
	object->SetValues(this, sbs->GetFloor(floornum)->object, "CallButton", "", false);

	IsEnabled = true;
	Elevators.resize(elevators.size());
	for (size_t i = 0; i < elevators.size(); i++)
		Elevators[i] = elevators[i];

	//save texture names
	UpTexture = UpButtonTexture;
	UpTextureLit = UpButtonTexture_Lit;
	DownTexture = DownButtonTexture;
	DownTextureLit = DownButtonTexture_Lit;

	UpStatus = false;
	DownStatus = false;
	ProcessedUp = false;
	ProcessedDown = false;

	//create object mesh
	Ogre::String buffer, buffer2, buffer3;
	buffer2 = Ogre::StringConverter::toString(floornum);
	buffer3 = Ogre::StringConverter::toString(number);
	buffer = "Call Panel " + buffer2 + ":" + buffer3;
	TrimString(buffer);
	object->SetName(buffer.c_str());
	CallButtonBackMesh = new MeshObject(object, buffer.c_str(), 0, sbs->GetConfigFloat("Skyscraper.SBS.MaxSmallRenderDistance", 100));

	buffer = "Call Button " + buffer2 + ":" + buffer3 + ":Up";
	CallButtonMeshUp = new MeshObject(object, buffer.c_str(), 0, sbs->GetConfigFloat("Skyscraper.SBS.MaxSmallRenderDistance", 100));

	buffer = "Call Button " + buffer2 + ":" + buffer3 + ":Down";
	CallButtonMeshDown = new MeshObject(object, buffer.c_str(), 0, sbs->GetConfigFloat("Skyscraper.SBS.MaxSmallRenderDistance", 100));

	//set variables
	floor = floornum;
	Number = number;
	Direction = direction;
	SetCase(Direction, false);
	TrimString(Direction);

	if (sbs->Verbose)
		Report("Created");

	sbs->ResetTextureMapping(true);

	//create panel
	if (ShowBack == true)
	{
		if (sbs->Verbose)
			Report("Creating back panel");

		if (Direction == "front" || Direction == "back")
		{
			float x1 = CenterX - (BackWidth / 2);
			float x2 = CenterX + (BackWidth / 2);
			if (Direction == "front")
				sbs->DrawWalls(true, false, false, false, false, false);
			else
				sbs->DrawWalls(false, true, false, false, false, false);

			sbs->AddWallMain(object, CallButtonBackMesh, "Call Button Panel", BackTexture, 0, x1, CenterZ, x2, CenterZ, BackHeight, BackHeight, sbs->GetFloor(floor)->GetBase() + voffset, sbs->GetFloor(floor)->GetBase() + voffset, tw, th, false);
		}
		if (Direction == "left" || Direction == "right")
		{
			float z1 = CenterZ - (BackWidth / 2);
			float z2 = CenterZ + (BackWidth / 2);
			if (Direction == "left")
				sbs->DrawWalls(true, false, false, false, false, false);
			else
				sbs->DrawWalls(false, true, false, false, false, false);

			sbs->AddWallMain(object, CallButtonBackMesh, "Call Button Panel", BackTexture, 0, CenterX, z1, CenterX, z2, BackHeight, BackHeight, sbs->GetFloor(floor)->GetBase() + voffset, sbs->GetFloor(floor)->GetBase() + voffset, tw, th, false);
		}
		sbs->ResetWalls();
	}

	//create buttons
	int bottomfloor = sbs->GetElevator(Elevators[0])->GetBottomFloor();
	int topfloor = sbs->GetElevator(Elevators[0])->GetTopFloor();

	if (sbs->Verbose)
		Report("Creating buttons");

	if (Direction == "front" || Direction == "back")
	{
		float x1 = CenterX - (BackWidth / 4);
		float x2 = CenterX + (BackWidth / 4);
		float offset;
		if (Direction == "front")
		{
			offset = -0.01f;
			sbs->DrawWalls(true, false, false, false, false, false);
		}
		else
		{
			offset = 0.01f;
			sbs->DrawWalls(false, true, false, false, false, false);
		}

		if (floornum > bottomfloor && floornum < topfloor)
		{
			float height = (BackHeight / 7) * 2;
			float altitude = sbs->GetFloor(floor)->GetBase() + voffset + ((BackHeight / 7) * 4);
			float altitude2 = sbs->GetFloor(floor)->GetBase() + voffset + (BackHeight / 7);
			sbs->AddWallMain(object, CallButtonMeshUp, "Call Button Up", UpButtonTexture, 0, x1, CenterZ + offset, x2, CenterZ + offset, height, height, altitude, altitude, 1, 1, false);
			sbs->AddWallMain(object, CallButtonMeshDown, "Call Button Down", DownButtonTexture, 0, x1, CenterZ + offset, x2, CenterZ + offset, height, height, altitude2, altitude2, 1, 1, false);
		}
		else
		{
			float height = (BackHeight / 7) * 2;
			float altitude = sbs->GetFloor(floor)->GetBase() + voffset + (((BackHeight / 7) * 3) - (BackHeight / 14));
			if (floornum < topfloor)
				sbs->AddWallMain(object, CallButtonMeshUp, "Call Button Up", UpButtonTexture, 0, x1, CenterZ + offset, x2, CenterZ + offset, height, height, altitude, altitude, 1, 1, false);
			if (floornum > bottomfloor)
				sbs->AddWallMain(object, CallButtonMeshDown, "Call Button Down", DownButtonTexture, 0, x1, CenterZ + offset, x2, CenterZ + offset, height, height, altitude, altitude, 1, 1, false);
		}
		sbs->ResetWalls();
	}
	else
	{
		float z1 = CenterZ - (BackWidth / 4);
		float z2 = CenterZ + (BackWidth / 4);
		float offset;
		if (Direction == "left")
		{
			offset = -0.01f;
			sbs->DrawWalls(true, false, false, false, false, false);
		}
		else
		{
			offset = 0.01f;
			sbs->DrawWalls(false, true, false, false, false, false);
		}
		if (floornum > bottomfloor && floornum < topfloor)
		{
			float height = (BackHeight / 7) * 2;
			float altitude = sbs->GetFloor(floor)->GetBase() + voffset + ((BackHeight / 7) * 4);
			float altitude2 = sbs->GetFloor(floor)->GetBase() + voffset + (BackHeight / 7);
			sbs->AddWallMain(object, CallButtonMeshUp, "Call Button Up", UpButtonTexture, 0, CenterX + offset, z1, CenterX + offset, z2, height, height, altitude, altitude, 1, 1, false);
			sbs->AddWallMain(object, CallButtonMeshDown, "Call Button Down", DownButtonTexture, 0, CenterX + offset, z1, CenterX + offset, z2, height, height, altitude2, altitude2, 1, 1, false);
		}
		else
		{
			float height = (BackHeight / 7) * 2;
			float altitude = sbs->GetFloor(floor)->GetBase() + voffset + (((BackHeight / 7) * 3) - (BackHeight / 14));
			if (floornum < topfloor)
				sbs->AddWallMain(object, CallButtonMeshUp, "Call Button Up", UpButtonTexture, 0, CenterX + offset, z1, CenterX + offset, z2, height, height, altitude, altitude, 1, 1, false);
			if (floornum > bottomfloor)
				sbs->AddWallMain(object, CallButtonMeshDown, "Call Button Down", DownButtonTexture, 0, CenterX + offset, z1, CenterX + offset, z2, height, height, altitude, altitude, 1, 1, false);
		}
		sbs->ResetWalls();
	}
	sbs->ResetTextureMapping();
}

CallButton::~CallButton()
{
	if (CallButtonMeshDown)
		delete CallButtonMeshDown;
	CallButtonMeshDown = 0;
	if (CallButtonMeshUp)
		delete CallButtonMeshUp;
	CallButtonMeshUp = 0;
	if (CallButtonBackMesh)
		delete CallButtonBackMesh;
	CallButtonBackMesh = 0;

	//unregister with parent floor object
	if (sbs->FastDelete == false)
	{
		if (object->parent_deleting == false)
			sbs->GetFloor(floor)->RemoveCallButton(this);

		sbs->UnregisterCallButtonCallback(this);
	}

	delete object;
}

void CallButton::Enabled(bool value)
{
	//turns call buttons on/off
	if (IsEnabled == value)
		return;

	CallButtonBackMesh->Enable(value);
	CallButtonMeshUp->Enable(value);
	CallButtonMeshDown->Enable(value);
	IsEnabled = value;

	if (sbs->Verbose)
	{
		if (value == true)
			Report("Enabled");
		else
			Report("Disabled");
	}
}

void CallButton::Call(bool direction)
{
	//calls the closest elevator in the elevator array list to the current floor,
	//and also depending on the direction it's traveling

	//exit if call has already been made
	if ((direction == true && UpStatus == true) || (direction == false && DownStatus == true))
	{
		if (sbs->Verbose)
			sbs->Report("Call has already been made");
		return;
	}

	//set light and direction value

	if (sbs->Verbose)
		Report("Call: finding grouped call buttons");

	//this call will return at least this call button
	std::vector<int> buttons = sbs->GetFloor(floor)->GetCallButtons(Elevators[0]);

	for (int i = 0; i < (int)buttons.size(); i++)
	{
		if (direction == true)
		{
			sbs->GetFloor(floor)->CallButtonArray[buttons[i]]->UpLight(true);
			ProcessedUp = false;
		}
		else
		{
			sbs->GetFloor(floor)->CallButtonArray[buttons[i]]->DownLight(true);
			ProcessedDown = false;
		}
	}

	//register callback for this button
	if (sbs->Verbose)
		Report("Registering callback");

	sbs->RegisterCallButtonCallback(this);
}

void CallButton::UpLight(bool value)
{
	//turn on the 'up' directional light
	if (value == UpStatus)
	{
		if (sbs->Verbose)
			Report("UpLight: already in requested status");
		return;
	}

	//set light status
	if (value == true)
		SetLights(1, 0);
	else
		SetLights(2, 0);

	UpStatus = value;
}

void CallButton::DownLight(bool value)
{
	//turn on the 'down' directional light
	if (value == DownStatus)
	{
		if (sbs->Verbose)
			Report("DownLight: already in requested status");
		return;
	}

	//set light status
	if (value == true)
		SetLights(0, 1);
	else
		SetLights(0, 2);

	DownStatus = value;
}

void CallButton::SetLights(int up, int down)
{
	//set status of call button lights
	//values are 0 for no change, 1 for on, and 2 for off

	if (up == 1 && CallButtonMeshUp)
	{
		if (sbs->Verbose)
			Report("SetLights: turning on up light");

		CallButtonMeshUp->ChangeTexture(UpTextureLit.c_str());
	}
	if (up == 2 && CallButtonMeshUp)
	{
		if (sbs->Verbose)
			Report("SetLights: turning off up light");

		CallButtonMeshUp->ChangeTexture(UpTexture.c_str());
	}
	if (down == 1 && CallButtonMeshDown)
	{
		if (sbs->Verbose)
			Report("SetLights: turning on down light");

		CallButtonMeshDown->ChangeTexture(DownTextureLit.c_str());
	}
	if (down == 2 && CallButtonMeshDown)
	{
		if (sbs->Verbose)
			Report("SetLights: turning off down light");

		CallButtonMeshDown->ChangeTexture(DownTexture.c_str());
	}

	/*if (up > 0 && !CallButtonMeshUp && sbs->Verbose)
		Report("SetLights: cannot change up light status");
	if (down > 0 && !CallButtonMeshDown && sbs->Verbose)
		Report("SetLights: cannot change down light status");*/
}

bool CallButton::ServicesElevator(int elevator)
{
	//return true if this call button services the specified elevator
	for (int i = 0; i < (int)Elevators.size(); i++)
	{
		if (Elevators[i] == elevator)
		{
			if (sbs->Verbose)
				Report(Ogre::String("Services elevator " + Ogre::String(_itoa(elevator, intbuffer, 10))).c_str());
			return true;
		}
	}
	return false;
}

void CallButton::Loop(bool direction)
{
	//call button main loop
	//this function runs for every registered call button via callback
	//direction is the call direction to process

	//first exit if no call button is not processing a call for the current direction
	//or if a call has already been processed
	if ((UpStatus == false && direction == true) || (ProcessedUp == true && direction == true))
		return;
	if ((DownStatus == false && direction == false) || (ProcessedDown == true && direction == false))
		return;

	//initialize values
	int closest = 0;
	int closest_elev = 0;
	int tmpdirection = 0;
	bool check = false;

	if (direction == true)
		tmpdirection = 1;
	else
		tmpdirection = -1;

	if (Elevators.size() > 1)
	{
		//search through elevator list if call button serves more than 1 elevator
		if (sbs->Verbose)
			Report("Finding nearest available elevator...");

		//check each elevator associated with this call button to find the closest available one
		for (int i = 0; i < (int)Elevators.size(); i++)
		{
			Elevator *elevator = sbs->GetElevator(Elevators[i]);
			int current = elevator->GetFloor();

			if (sbs->Verbose)
				Report(Ogre::String("Checking elevator " + Ogre::String(_itoa(elevator->Number, intbuffer, 10))).c_str());

			//if elevator is running
			if (elevator->IsRunning() == true)
			{
				//if elevator is closer than the previously checked one or we're starting the checks
				if (abs(current - floor) < closest || check == false)
				{
					//and if it's above the current floor and should be called down, or below the
					//current floor and called up, or on the same floor, or idle
					if ((current > floor && direction == false) || (current < floor && direction == true) || current == floor || elevator->IsIdle())
					{
						//and if it's either going the same direction as the call or idle
						if (elevator->QueuePositionDirection == tmpdirection || elevator->IsIdle())
						{
							//and if nudge mode is off on all doors
							if (sbs->GetElevator(Elevators[i])->IsNudgeModeActive() == false)
							{
								//and if it's not in any service mode
								if (sbs->GetElevator(Elevators[i])->InServiceMode() == false)
								{
									if (sbs->Verbose)
										Report("Marking - closest so far");
									closest = abs(current - floor);
									closest_elev = i;
									check = true;
								}
								else if (sbs->Verbose == true)
									Report("Skipping - in service mode");
							}
							else if (sbs->Verbose == true)
								Report("Skipping - in nudge mode");
						}
						else if (sbs->Verbose == true)
							Report("Skipping - going a different direction and is not idle");
					}
					else if (sbs->Verbose == true)
						Report("Skipping - position/direction wrong for call");
				}
				else if (sbs->Verbose == true)
					Report("Skipping - not closer than previous");
			}
			else if (sbs->Verbose == true)
				Report("Skipping - elevator not running");
		}
	}
	else
	{
		//set elevator to first elevator if call button only serves one, only if elevator is running
		if (sbs->GetElevator(Elevators[0])->IsRunning() == true && sbs->GetElevator(Elevators[0])->IsNudgeModeActive() == false)
		{
			closest_elev = 0;
			check = true;
		}
		else
		{
			//otherwise turn off call buttons
			UpLight(false);
			DownLight(false);
		}
	}

	if (check == false)
	{
		//exit if no elevator found

		if (sbs->Verbose)
			Report("No elevator found");
		return;
	}

	//change processed state
	if (direction == true)
		ProcessedUp = true;
	else
		ProcessedDown = true;

	Elevator* elevator = sbs->GetElevator(Elevators[closest_elev]);

	//if selected elevator is in a service mode, exit
	if (elevator->InServiceMode() == true)
		return;

	if (sbs->Verbose)
		Report(Ogre::String("Using elevator " + Ogre::String(_itoa(elevator->Number, intbuffer, 10))).c_str());

	//if closest elevator is already on the called floor, if call direction is the same, and if elevator is not idle
	if (elevator->GetFloor() == floor && elevator->QueuePositionDirection == tmpdirection && elevator->IsIdle() == false && elevator->IsMoving == false)
	{
		if (sbs->Verbose)
			Report("Elevator active on current floor - opening");

		//this call will return at least this call button
		std::vector<int> buttons = sbs->GetFloor(floor)->GetCallButtons(Elevators[0]);

		//turn off all button lights in the group
		for (int i = 0; i < (int)buttons.size(); i++)
		{
			if (direction == true)
				sbs->GetFloor(floor)->CallButtonArray[buttons[i]]->UpLight(false);
			else
				sbs->GetFloor(floor)->CallButtonArray[buttons[i]]->DownLight(false);
		}

		if (direction == false)
		{
			//turn on directional indicator
			sbs->GetFloor(floor)->SetDirectionalIndicators(elevator->Number, false, true);
			elevator->SetDirectionalIndicators(false, true);
			//play chime sound
			elevator->Chime(0, floor, false);
		}
		else
		{
			//turn on directional indicator
			sbs->GetFloor(floor)->SetDirectionalIndicators(elevator->Number, true, false);
			elevator->SetDirectionalIndicators(true, false);
			//play chime sound
			elevator->Chime(0, floor, true);
		}
		//open elevator if it's on the same floor
		elevator->OpenDoors();
	}
	else
		//otherwise add a route entry to this floor
		elevator->AddRoute(floor, direction, false);

	//unregister callback if inactive
	if (UpStatus == false && DownStatus == false)
	{
		if (sbs->Verbose)
			Report("Unregistering callback");
		sbs->UnregisterCallButtonCallback(this);
	}
}

void CallButton::Report(const char *message)
{
	//general reporting function
	Ogre::String msg = "Call button " + Ogre::String(_itoa(floor, intbuffer, 10)) + ":" + Ogre::String(_itoa(Number, intbuffer, 10)) + " - " + message;
	sbs->Report(msg.c_str());

}

bool CallButton::ReportError(const char *message)
{
	//general reporting function
	Ogre::String msg = "Call button " + Ogre::String(_itoa(floor, intbuffer, 10)) + ":" + Ogre::String(_itoa(Number, intbuffer, 10)) + " - " + message;
	return sbs->ReportError(msg.c_str());
}
