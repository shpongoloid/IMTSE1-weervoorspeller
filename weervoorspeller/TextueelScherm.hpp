/*
* TextueelScherm.hpp
*
* Created on: 3 jun. 2012
* Author: niekert
*/
#ifndef TEXTUEELSCHERM_HPP_
#define TEXTUEELSCHERM_HPP_

#include <MAUI/Screen.h>
#include <MAUI/Font.h>
#include <MAUI/WidgetSkin.h>
#include <conprint.h>
#include "WeerData.hpp"

using namespace MAUI;

class TextueelScherm : public Screen
{
	private:
		WidgetSkin* skin;
		Font* font;

		Label* weerDataLabel;
		Label* weerInfo;
		Label* weerInfoZon;
		Label* weerInfoNeerslag;
		Label* weerInfoMintemp;

		Screen* toggleScherm;

		Label* updateLabel;
		Label* visueelLabel;

		WeerData* weerData;

	public:
		TextueelScherm( WeerData* weerData );
		virtual ~TextueelScherm();
		void setToggleScherm( Screen* toggleScherm );
		void update();
		void toonWeerData();

		void pointerPressEvent( MAPoint2d point );
		void pointerReleaseEvent( MAPoint2d point );
};

#endif /* TEXTUEELSCHERM_HPP_ */
