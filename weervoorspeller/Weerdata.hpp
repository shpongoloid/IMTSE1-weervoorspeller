/*
* WeerData.hpp
*
* Created on: 3 jun. 2012
* Author: niekert
*/

#ifndef WEERDATA_HPP_
#define WEERDATA_HPP_

#include <MAUI/Screen.h>
#include <MAUI/Label.h>
#include <MAUI/Font.h>
#include <MAUI/ListBox.h>
#include <MAUI/Image.h>
#include <MAUI/WidgetSkin.h>
#include <MAUtil/Connection.h>
#include <mastdlib.h>
#include <conprint.h>
#include "MAHeaders.h"

#define CONNECTION_BUFFER_SIZE 1024

using namespace MAUtil;
using namespace MAUI;

class WeerData : private HttpConnection, private HttpConnectionListener
{
	private:
		char* url;
		bool isConnecting;
		char weerDataRecv[1024];

	public:
		// weerdata attributen
		int zonneschijn[3];
		int neerslag[3];
		int mintemperatuur[3];

		WeerData();
		virtual ~WeerData();

		// roept nieuwe connectie aan en updated alle weerdata
		void update();

		// benodigde connectie functies van HttpConnection en listener
		void httpFinished( HttpConnection *conn, int result);
		void connRecvFinished( Connection *conn, int result);
		void connReadFinished( Connection *conn, int result);
		void connectFinished(Connection* conn, int result);
};

#endif /* WEERDATA_HPP_ */
