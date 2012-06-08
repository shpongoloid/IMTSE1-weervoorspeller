#include <MAUtil/Moblet.h>

#include "MAHeaders.h"
using namespace MAUtil;

#include "WeerData.hpp"
#include "TextueelScherm.hpp"
#include "VisueelScherm.hpp"

class MAUIMoblet : public Moblet
{
	public:
	MAUIMoblet()
	{
		// WeerData bevat alle data van het weer
		WeerData* weerData = new WeerData();

		// De schermen die alles weer zullen geven
		TextueelScherm* textueelScherm = new TextueelScherm( weerData );
		VisueelScherm* visueelScherm = new VisueelScherm( weerData );

		// Hiermee kunnen de schermen naar elkaar veranderen
		textueelScherm->setToggleScherm( visueelScherm );
		visueelScherm->setToggleScherm( textueelScherm );

		// Laat het textueele scherm zien zodra de app gestart wordt
		textueelScherm->show();
	}

	virtual ~MAUIMoblet()
	{}

	// app afsluiten als MAK_BACk gedrukt wordt
	void keyPressEvent(int keyCode, int nativeCode)
	{
		if (MAK_BACK == keyCode || MAK_0 == keyCode)
		{
			close();
		}
	}
};

extern "C" int MAMain()
{
	Moblet::run(new MAUIMoblet());
	return 0;
}
