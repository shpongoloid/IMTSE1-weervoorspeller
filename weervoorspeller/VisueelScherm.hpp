/*
* VisueelScherm.hpp
*
* Created on: 3 jun. 2012
* Author: niekert
*/

#ifndef VISUEELSCHERM_HPP_
#define VISUEELSCHERM_HPP_

#include <MAUI/Screen.h>
#include <MAUI/ListBox.h>
#include <MAUI/Label.h>
#include <MAUI/Image.h>
#include <conprint.h>
#include "WeerData.hpp"

using namespace MAUI;

class VisueelScherm : public Screen
{
	private:
		WidgetSkin* skin;
		Font* font;

		Label* updateLabel;
		Label* visueelLabel;
		Screen* toggleScherm;

		WeerData* weerData;

		MAHandle diagram;
		Image* diagramImage;

	public:
		VisueelScherm( WeerData* weerData );
		virtual ~VisueelScherm();
		void update();
		void setToggleScherm( Screen* toggleScherm );

		void pointerPressEvent( MAPoint2d p );
		void pointerReleaseEvent( MAPoint2d point );
};

#endif /* VISUEELSCHERM_HPP_ */
