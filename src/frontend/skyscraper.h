/* $Id$ */

/*
	Skyscraper 1.8 Alpha - Simulation Frontend
	Copyright (C)2004-2011 Ryan Thoryk
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

#ifndef SKYSCRAPER_H
#define SKYSCRAPER_H

#include <wx/app.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <fmod.hpp>
#include "fileio.h"

int main (int argc, char* argv[]);

class Skyscraper : public wxApp
{
public:

	//OGRE engine data
	Ogre::Root* mRoot;
	Ogre::RenderWindow* mRenderWindow;
	Ogre::Viewport* mViewport;
	Ogre::SceneManager* mSceneMgr;
	Ogre::Camera* mCamera;

	std::string version;
	std::string version_rev;
	std::string version_state;
	std::string version_frontend;

	std::string Platform;

	bool RenderOnly; //skip sim processing and only render graphics
	bool InputOnly; //skip sim processing and only run input and rendering code
	bool IsRunning;
	bool StartupRunning;
	bool Starting;
	bool Pause; //pause simulator
	bool DisableSound;
	bool IntroMusic;
	bool FullScreen;
	bool Shutdown;
	bool Reload;
	bool PositionOverride;
	Ogre::Vector3 override_position;
	Ogre::Vector3 override_rotation;
	bool Shaders;

	unsigned int elapsed_time, current_time;

	void Loop();
	virtual bool OnInit(void);
	virtual int OnExit(void);
	void DrawBackground();

	std::string BuildingFile;

	//engine related stuff
	Ogre::RenderWindow* CreateRenderWindow(const Ogre::NameValuePairList* miscParams = 0, const std::string& windowName = std::string(""));
	void destroyRenderWindow();
	const std::string getOgreHandle() const;
	void Render();
	void GetInput();
	void Report(std::string message, ...);
	bool ReportError(std::string message, ...);
	bool ReportFatalError(std::string message, ...);
	bool Initialize();
	void GetMenuInput();
	void StartSound();
	void StopSound();
	bool SelectBuilding();
	bool Start();
	void AllowResize(bool value);
	void Unload();
	void Quit();
	int GetConfigInt(std::string key, int default_value);
	std::string GetConfigString(std::string key, std::string default_value);
	bool GetConfigBool(std::string key, bool default_value);
	float GetConfigFloat(std::string key, float default_value);

private:
	//mouse status
	bool MouseDown;

	//app directory
	std::string root_dir;
	std::string dir_char;

	//canvas data
	int canvas_width, canvas_height;
	wxPanel* canvas;

	//sound data
	FMOD::System *soundsys;
	FMOD::Sound *sound;
	FMOD::Channel *channel;

	//script processor
	ScriptProcessor* processor;

	//button locations
	struct buttondata
	{
		float x;
		float y;
		float size_x;
		float size_y;
		std::string filename;
		std::string filename_selected;
		std::string filename_pressed;
		float offset_x;
		float offset_y;
		bool drawn_selected, drawn_pressed;
		int active_button;
		Ogre::SceneNode* node;
		Ogre::Rectangle2D* rect;
	};
	buttondata button1, button2, button3, button4, button5;

	Ogre::Rectangle2D* background_rect;
	Ogre::SceneNode* background_node;
	std::string background_image;
	void DrawImage(const char *filename, buttondata *button, float x, float y, bool center, const char *filename_selected = 0, const char *filename_pressed = 0);
	void Click(int index);
	void UnloadSim();
	void DeleteButtons();

	Ogre::ConfigFile configfile;
};

class MainScreen : public wxFrame
{
public:
	MainScreen(int width, int height);
	~MainScreen();
	void OnIconize(wxIconizeEvent& event);
	void OnSize(wxSizeEvent& event);
	void OnClose(wxCloseEvent& event);
	void ShowWindow();
	void OnIdle(wxIdleEvent& event);
	void OnPaint(wxPaintEvent& event);
	void OnEnterWindow(wxMouseEvent& event);
	void OnLeaveWindow(wxMouseEvent& event);
	wxPanel *panel;
	bool Active;

	DECLARE_EVENT_TABLE()

};

DECLARE_APP(Skyscraper)

#endif
