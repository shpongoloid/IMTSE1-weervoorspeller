/*
* TextueelScherm.cpp
*
* Created on: 3 jun. 2012
* Author: niekert
*/

#include "TextueelScherm.hpp"

// hulp bools om het klikken van de buttons te verbeteren
bool touched = false, touched2 = false;

// constructor
TextueelScherm::TextueelScherm( WeerData* weerData )
{
	// bepaal grootte van het scherm
	MAExtent screenSize = maGetScrSize();

	// sla de weerdata op in een attribuut
	this->weerData = weerData;

	// de font en widgetskin toepassen
	this->font = new MAUI::Font( RES_FONT );
	this->skin = new WidgetSkin( RES_SELECTED, RES_UNSELECTED, 3, 4, 3, 4, false, false );

	// maak een label die andere widgets straks bevat, en een achtergrondkleur heeft
	Label* label = new Label( 0, 0, 0, 0, NULL );

	// stel achtergrondkleur in
	label->setBackgroundColor( 0x9cd7eb );

	// knop om data te updaten
	// ook hier gebruik ik weer paddings om de look te verbeteren
	this->updateLabel = new Label( 11, EXTENT_Y( screenSize ) - 50, (EXTENT_X( screenSize ) / 2) - 20, 39, label, "Update", 0, font );
	this->updateLabel->setPaddingLeft( 9 );
	this->updateLabel->setPaddingTop( 10 );
	this->updateLabel->setSkin( skin );

	// knop om naar visueel scherm terug te keren
	this->visueelLabel = new Label( (EXTENT_X( screenSize ) / 2) + 9, EXTENT_Y( screenSize ) - 50, (EXTENT_X( screenSize ) / 2) - 20, 39, label, "Visueel", 0, font );
	this->visueelLabel->setPaddingLeft( 9 );
	this->visueelLabel->setPaddingTop( 10 );
	this->visueelLabel->setSkin( skin );

	// alle labels die het weerinfo zullen bevatten
	this->weerDataLabel = new Label( 7, 7, 400, 200, label, "Weersverwachting Mobile", 0x9cd7eb , font );
	this->weerInfo = new Label( 7, 30, 400, 30, label, "", 0x9cd7eb, font );
	this->weerInfoZon = new Label( 7, 50, 400, 30, label, "", 0x9cd7eb, font );
	this->weerInfoNeerslag = new Label( 7, 70, 400, 30, label,"", 0x9cd7eb, font );
	this->weerInfoMintemp = new Label( 7, 90, 400, 30, label,"", 0x9cd7eb, font );

	// alles zichtbaar maken
	this->setMain(label);
	this->update();
}

// destructor, niks doen
TextueelScherm::~TextueelScherm()
{}

// het weer data inladen
void TextueelScherm::toonWeerData()
{
	// maken van een data buffer
	char data[500];

	// de tekst toepassen op de gemaakte labels, de white space is om alles een beetje mooi te alignen
	sprintf( data, "    morgen, overmorgen, over-overmorgen");
	this->weerInfo->setCaption(data);
	sprintf( data, "Zonneschijn:          %i%%        %i%%        %i%%", weerData->zonneschijn[0], weerData->zonneschijn[1], weerData->zonneschijn[2] );
	this->weerInfoZon->setCaption( data );
	sprintf( data, "Neerslag:               %i%%        %i%%        %i%%", weerData->neerslag[0], weerData->neerslag[1], weerData->neerslag[2] );
	this->weerInfoNeerslag->setCaption(data);
	sprintf( data, "Min. temperatuur:   %i           %i           %i", weerData->mintemperatuur[0], weerData->mintemperatuur[1], weerData->mintemperatuur[2] );
	this->weerInfoMintemp->setCaption(data);
}

// veranderen van scherm
void TextueelScherm::setToggleScherm( Screen* toggleScherm )
{
	this->toggleScherm = toggleScherm;
}

// het weer data updaten en dan meteen weergeven
void TextueelScherm::update()
{
	this->weerData->update();
	this->toonWeerData();
}

// pointerpressevent
void TextueelScherm::pointerPressEvent( MAPoint2d point )
{
	// update knop is ingedrukt
	if( this->updateLabel->contains( point.x, point.y ) )
	{
		this->updateLabel->setSelected( true );
		touched = true;
	}
	else
	{
		this->updateLabel->setSelected( false );
		touched = false;
	}

	//visueel knop is ingedrukt
	if( this->visueelLabel->contains( point.x, point.y ) )
	{
		this->visueelLabel->setSelected( true );
		touched2 = true;
	}
	else
	{
		this->visueelLabel->setSelected( false );
		touched2 = false;
	}
}

void TextueelScherm::pointerReleaseEvent( MAPoint2d point )
{
	// update knop is losgelaten
	if( this->updateLabel->contains( point.x, point.y ) && touched )
	{
		this->updateLabel->setSelected( false );
		this->update();
	}
	else
	{
		this->updateLabel->setSelected( false );
		touched = false;
	}

	// visueel knop is losgelaten
	if( this->visueelLabel->contains( point.x, point.y ) && touched2 )
	{
		this->visueelLabel->setSelected( false );
		this->hide();
		this->toggleScherm->show();
	}
	else
	{
		this->visueelLabel->setSelected( false );
		touched2 = false;
	}
}
