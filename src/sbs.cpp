//Scalable Building Simulator - Simulator Core
//The Skyscraper Project - Version 1.1 Alpha
//Copyright �2005 Ryan Thoryk
//http://www.tliquest.net/skyscraper
//http://sourceforge.net/projects/skyscraper
//Contact - ryan@tliquest.net

//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <iostream>
#include <string>

//CrystalSpace Includes
#include "cssysdef.h"
#include "csutil/sysfunc.h"
#include "iutil/vfs.h"
#include "csutil/cscolor.h"
#include "cstool/csview.h"
#include "cstool/initapp.h"
#include "iutil/eventq.h"
#include "iutil/event.h"
#include "iutil/objreg.h"
#include "iutil/csinput.h"
#include "iutil/virtclk.h"
#include "iengine/sector.h"
#include "iengine/engine.h"
#include "iengine/camera.h"
#include "iengine/light.h"
#include "iengine/texture.h"
#include "iengine/mesh.h"
#include "iengine/movable.h"
#include "iengine/material.h"
#include "imesh/thing.h"
#include "imesh/object.h"
#include "ivideo/graph3d.h"
#include "ivideo/graph2d.h"
#include "ivideo/texture.h"
#include "ivideo/material.h"
#include "ivideo/fontserv.h"
#include "ivideo/natwin.h"
#include "igraphic/imageio.h"
#include "imap/parser.h"
#include "ivaria/reporter.h"
#include "ivaria/stdrep.h"
#include "csutil/cmdhelp.h"
#include "csutil/event.h"

CS_IMPLEMENT_APPLICATION

#include "sbs.h"

SBS *sbs;

SBS::SBS(iObjectRegistry* object_reg)
{
    SBS::object_reg = object_reg;
	//csReport (object_reg, CS_REPORTER_SEVERITY_ERROR, "crystalspace.application.sbs", "Starting");
    sbs = this;
}

SBS::~SBS()
{
	//Uninitialize the variables
/*	pScene->DestroyAllMeshes ();

	pScene->Release ();
	pInput->Release ();
	pEngine->Release ();
	pAtmos->Release ();
	pCamera->Release ();
	pMatFactory->Release ();
	pLightEngine->Release ();
	pGraphicEffect->Release ();
	pTextureFactory->Release ();

	pScene = NULL;
	pInput = NULL;
	pEngine = NULL;
	pAtmos = NULL;
	pCamera = NULL;
	pMatFactory = NULL;
	pLightEngine = NULL;
	pGraphicEffect = NULL;
	pTextureFactory = NULL;
*/
}

void SBS::Start()
{
    //mainconsole = new Console(NULL);
    //mainconsole->Show(TRUE);		
	//PrintBanner();
    csDefaultRunLoop (object_reg);
/*	
	pEngine = CreateTVEngine();

	//Set the debug file before doing anything else
	pEngine->SetDebugFile ("c:\\debug.txt");

	//Initialize Windowed
	pEngine->Init3DWindowedMode ((long)WindowHandle, true);

	//Tell it to display the FPS
	pEngine->put_DisplayFPS(tvtrue);

	//AppPath is a small Macro function in tv3dcpp lib to return the path
	//of a file you pass to it, in this case we get the application path
	char path[256];
	char srchpath[256];
	
	HMODULE Module = (HMODULE)hInstance;
	GetModuleFileName(Module,path,255); 
	
	AppPath(path,srchpath);	
	
	//Set the search directory of the objects, textures, ...
	pEngine->SetSearchDirectory(srchpath);
	
	//We set the AngleSystem to Degrees
	pEngine->SetAngleSystem (TV_ANGLE_DEGREE);

	//Init input after main init, and check if it errors anywhere.
	pInput = CreateTVInputEngine();
	pScene = CreateTVScene();	
	pGlobals = CreateTVGlobals();
	pAtmos = CreateTVAtmosphere();
	pCamera = CreateTVCamera();
	pMatFactory = CreateTVMaterialFactory();
	pLightEngine = CreateTVLightEngine();
	pGraphicEffect = CreateTVGraphicEffect();
*/
}

void SBS::Wait(long milliseconds)
{

}

float SBS::AutoSize(float n1, float n2, bool iswidth)
{
//Texture autosizing formulas
//If any of the texture parameters are 0, then automatically size the
//texture using the Skyscraper 1.0 sizing algorithms
    return 0;
}

void SBS::PrintBanner()
{
	//mainconsole->WxMemo1->AppendText("Scalable Building Simulator Starting\n");
}

void SBS::render()
{
/*	pEngine->Clear(tvfalse);						//Clear the screen
	pAtmos->Atmosphere_Render();
	pScene->RenderAllMeshes (tvfalse);
	pEngine->RenderToScreen ();					//Render the screen	
*/
}

void SBS::input()
{
/*	if(pInput->IsKeyPressed(TV_KEY_UP))
        pCamera->MoveRelative ((0.015 * pEngine->TimeElapsed()), 0, 0, tvfalse);

    if(pInput->IsKeyPressed(TV_KEY_DOWN))
        pCamera->MoveRelative ((-0.015 * pEngine->TimeElapsed()), 0, 0, tvfalse);

    if(pInput->IsKeyPressed(TV_KEY_LEFT))
        pCamera->RotateY (pEngine->TimeElapsed() * -6 / 100);

    if(pInput->IsKeyPressed(TV_KEY_RIGHT))
        pCamera->RotateY (pEngine->TimeElapsed() * 6 / 100);

	if(pInput->IsKeyPressed(TV_KEY_PAGEUP))
        pCamera->RotateX (-0.68);
    
	if(pInput->IsKeyPressed(TV_KEY_PAGEDOWN))
        pCamera->RotateX (0.68);

	if(pInput->IsKeyPressed(TV_KEY_HOME))
		pCamera->MoveRelative (0, 1, 0, tvfalse);

	if(pInput->IsKeyPressed(TV_KEY_END))
		pCamera->MoveRelative (0, -1, 0, tvfalse);

	if(pInput->IsKeyPressed(TV_KEY_F1))
		pEngine->ScreenShot ("../shot.bmp");

	if(pInput->IsKeyPressed(TV_KEY_A) && RideCar->GetPosition().z > 0)
		GoCar = true;

	if(pInput->IsKeyPressed(TV_KEY_SPACE))
		pCamera->SetRotation (0, 180, 0);
	
	lineend = pCamera->GetPosition();
	LineTest = lineend;

    if(lineend.x > linestart.x)
		LineTest.x = lineend.x + 2;
    if(lineend.x < linestart.x)
		LineTest.x = lineend.x - 2;
    if(lineend.z > linestart.z)
		LineTest.z = lineend.z + 2;
    if(lineend.z < linestart.z)
		LineTest.z = lineend.z - 2;

	//if (Room->Collision(linestart, LineTest, TV_TESTTYPE_ACCURATETESTING, 0) == tvtrue || HypnoRoom->Collision(linestart, LineTest, TV_TESTTYPE_ACCURATETESTING, 0) == tvtrue || HypnoDoor->Collision(linestart, LineTest, TV_TESTTYPE_ACCURATETESTING, 0) == tvtrue || HypnoRide->Collision(linestart, LineTest, TV_TESTTYPE_ACCURATETESTING, 0) == tvtrue || RideDoor->Collision(linestart, LineTest, TV_TESTTYPE_ACCURATETESTING, 0) == tvrue Or RideCar->Collision(linestart, LineTest, TV_TESTTYPE_ACCURATETESTING, 0) == tvtrue)
	//	pCamera->SetPosition (linestart.x, linestart.y, linestart.z);
	//else
	//	pCamera->SetPosition (lineend.x, lineend.y, lineend.z);
	//
	if(pInput->IsKeyPressed(TV_KEY_ESCAPE))		//Check if ESCAPE has been pressed.
	{		
		PostQuitMessage(0);
	}*/
}

void SBS::SlowToFPS(long FrameRate)
{

}

void SBS::SetupFrame ()
{
  // First get elapsed time from the virtual clock.
  csTicks elapsed_time = vc->GetElapsedTicks ();
  // Now rotate the camera according to keyboard state
  float speed = (elapsed_time / 1000.0) * (0.06 * 20);

  iCamera* c = view->GetCamera();

  if (kbd->GetKeyState (CSKEY_SHIFT))
  {
    // If the user is holding down shift, the arrow keys will cause
    // the camera to strafe up, down, left or right from it's
    // current position.
    if (kbd->GetKeyState (CSKEY_RIGHT))
      c->Move (CS_VEC_RIGHT * 4 * speed);
    if (kbd->GetKeyState (CSKEY_LEFT))
      c->Move (CS_VEC_LEFT * 4 * speed);
    if (kbd->GetKeyState (CSKEY_UP))
      c->Move (CS_VEC_UP * 4 * speed);
    if (kbd->GetKeyState (CSKEY_DOWN))
      c->Move (CS_VEC_DOWN * 4 * speed);
  }
  else
  {
    // left and right cause the camera to rotate on the global Y
    // axis; page up and page down cause the camera to rotate on the
    // _camera's_ X axis (more on this in a second) and up and down
    // arrows cause the camera to go forwards and backwards.
    if (kbd->GetKeyState (CSKEY_RIGHT))
      rotY += speed;
    if (kbd->GetKeyState (CSKEY_LEFT))
      rotY -= speed;
    if (kbd->GetKeyState (CSKEY_PGUP))
      rotX += speed;
    if (kbd->GetKeyState (CSKEY_PGDN))
        rotX -= speed;
    if (kbd->GetKeyState (CSKEY_UP))
        c->Move (CS_VEC_FORWARD * 4 * speed);
    if (kbd->GetKeyState (CSKEY_DOWN))
        c->Move (CS_VEC_BACKWARD * 4 * speed);
  }

  // We now assign a new rotation transformation to the camera.  You
  // can think of the rotation this way: starting from the zero
  // position, you first rotate "rotY" radians on your Y axis to get
  // the first rotation.  From there you rotate "rotX" radians on the
  // your X axis to get the final rotation.  We multiply the
  // individual rotations on each axis together to get a single
  // rotation matrix.  The rotations are applied in right to left
  // order .
  csMatrix3 rot = csXRotMatrix3 (rotX) * csYRotMatrix3 (rotY);
  csOrthoTransform ot (rot, c->GetTransform().GetOrigin ());
  c->SetTransform (ot);

  // Tell 3D driver we're going to display 3D things.
  if (!g3d->BeginDraw (engine->GetBeginDrawFlags () | CSDRAW_3DGRAPHICS))
    return;

  // Tell the camera to render into the frame buffer.
  view->Draw ();
}

void SBS::FinishFrame ()
{
  g3d->FinishDraw ();
  g3d->Print (0);
}

bool SBS::HandleEvent (iEvent& ev)
{
  if (ev.Type == csevBroadcast && ev.Command.Code == cscmdProcess)
  {
    SetupFrame ();
    return true;
  }
  else if (ev.Type == csevBroadcast && ev.Command.Code == cscmdFinalProcess)
  {
    FinishFrame ();
    return true;
  }
  else if ((ev.Type == csevKeyboard) &&
    (csKeyEventHelper::GetEventType (&ev) == csKeyEventTypeDown) &&
    (csKeyEventHelper::GetCookedCode (&ev) == CSKEY_ESC))
  {
    csRef<iEventQueue> q (CS_QUERY_REGISTRY (object_reg, iEventQueue));
    if (q) q->GetEventOutlet()->Broadcast (cscmdQuit);
    return true;
  }

  return false;
}

bool SBS::SBSEventHandler (iEvent& ev)
{
  return sbs ? sbs->HandleEvent (ev) : false;
}

bool SBS::Initialize ()
{
  if (!csInitializer::RequestPlugins (object_reg,
    CS_REQUEST_VFS,
    CS_REQUEST_OPENGL3D,
    CS_REQUEST_ENGINE,
    CS_REQUEST_FONTSERVER,
    CS_REQUEST_IMAGELOADER,
    CS_REQUEST_LEVELLOADER,
    CS_REQUEST_REPORTER,
    CS_REQUEST_REPORTERLISTENER,
    CS_REQUEST_END))
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
        "crystalspace.application.sbs",
    "Can't initialize plugins!");
    return false;
  }

  if (!csInitializer::SetupEventHandler (object_reg, SBSEventHandler))
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
        "crystalspace.application.sbs",
    "Can't initialize event handler!");
    return false;
  }

  // Check for commandline help.
  if (csCommandLineHelper::CheckHelp (object_reg))
  {
    csCommandLineHelper::Help (object_reg);
    return false;
  }

  // The virtual clock.
  vc = CS_QUERY_REGISTRY (object_reg, iVirtualClock);
  if (vc == 0)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
        "crystalspace.application.sbs",
    "Can't find the virtual clock!");
    return false;
  }

  // Find the pointer to engine plugin
  engine = CS_QUERY_REGISTRY (object_reg, iEngine);
  if (engine == 0)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
        "crystalspace.application.sbs",
    "No iEngine plugin!");
    return false;
  }

  loader = CS_QUERY_REGISTRY (object_reg, iLoader);
  if (loader == 0)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
        "crystalspace.application.sbs",
        "No iLoader plugin!");
    return false;
  }

  g3d = CS_QUERY_REGISTRY (object_reg, iGraphics3D);
  if (g3d == 0)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
        "crystalspace.application.sbs",
        "No iGraphics3D plugin!");
    return false;
  }

  kbd = CS_QUERY_REGISTRY (object_reg, iKeyboardDriver);
  if (kbd == 0)
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
        "crystalspace.application.sbs",
        "No iKeyboardDriver plugin!");
    return false;
  }

  // Open the main system. This will open all the previously loaded plug-ins.
  if (!csInitializer::OpenApplication (object_reg))
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
        "crystalspace.application.sbs",
        "Error opening system!");
    return false;
  }

  // First disable the lighting cache. Our app is simple enough
  // not to need this.
  engine->SetLightingCacheMode (0);

  // Load the texture from the standard library.  This is located in
  // CS/data/standard.zip and mounted as /lib/std using the Virtual
  // File System (VFS) plugin.
  if (!loader->LoadTexture ("stone", "/lib/std/stone4.gif"))
  {
    csReport (object_reg, CS_REPORTER_SEVERITY_ERROR,
        "crystalspace.application.sbs",
        "Error loading 'stone4' texture!");
    return false;
  }
  iMaterialWrapper* tm = engine->GetMaterialList ()->FindByName ("stone");

  // these are used store the current orientation of the camera
  rotY = rotX = 0;

  room = engine->CreateSector ("room");
  csRef<iMeshWrapper> walls (engine->CreateSectorWallsMesh (room, "walls"));
  csRef<iThingState> ws =
    SCF_QUERY_INTERFACE (walls->GetMeshObject (), iThingState);
  csRef<iThingFactoryState> walls_state = ws->GetFactory ();
  walls_state->AddInsideBox (csVector3 (-5, 0, -5), csVector3 (5, 20, 5));
  walls_state->SetPolygonMaterial (CS_POLYRANGE_LAST, tm);
  walls_state->SetPolygonTextureMapping (CS_POLYRANGE_LAST, 3);

  csRef<iLight> light;
  iLightList* ll = room->GetLights ();

  light = engine->CreateLight (0, csVector3 (-3, 5, 0), 10,
    csColor (1, 0, 0));
  ll->Add (light);

  light = engine->CreateLight (0, csVector3 (3, 5,  0), 10,
    csColor (0, 0, 1));
  ll->Add (light);

  light = engine->CreateLight (0, csVector3 (0, 5, -3), 10,
    csColor (0, 1, 0));
  ll->Add (light);

  engine->Prepare ();

  view = csPtr<iView> (new csView (engine, g3d));
  view->GetCamera ()->SetSector (room);
  view->GetCamera ()->GetTransform ().SetOrigin (csVector3 (0, 5, -3));
  iGraphics2D* g2d = g3d->GetDriver2D ();
  view->SetRectangle (0, 0, g2d->GetWidth (), g2d->GetHeight ());

  return true;
}

bool IsEven(int Number)
{
    return false;
}
