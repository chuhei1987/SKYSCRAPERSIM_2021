/* $Id$ */

/*
        Scalable Building Simulator - Action Class
        The Skyscraper Project - Version 1.8 Alpha
        Copyright (C)2004-2012 Ryan Thoryk
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

#ifndef _SBS_ACTION_H
#define _SBS_ACTION_H

class SBSIMPEXP Action
{
public:
	//functions
	Action(Object* action_parent, const std::string &command, const std::vector<std::string> &parameters);
	Action(Object* action_parent, const std::string &command);
	~Action();
	bool DoAction();
	const char *GetName();

private:

	std::string command_name;
	std::vector<std::string> command_parameters;
	int state;
	Object *parent_object;
};

#endif
