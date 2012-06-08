/*
* VisueelScherm.cpp
*
* Created on: 3 jun. 2012
* Author: niekert
*/

#include "VisueelScherm.hpp"

// hulp bools om het klikken van de buttons te verbeteren
bool touch = false, touch2 = false;

// constructor
VisueelScherm::VisueelScherm( WeerData* weerData )
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
	// weer gebruik ik padding om alles een stuk mooier te maken
	this->updateLabel = new Label( 11, EXTENT_Y( screenSize ) - 50, (EXTENT_X( screenSize ) / 2) - 20, 39, label, "Update", 0, font );
	this->updateLabel->setPaddingLeft( 9 );
	this->updateLabel->setPaddingTop( 10 );
	this->updateLabel->setSkin( skin );

	// knop om naar terug naar het textueele scherm te keren
	this->visueelLabel = new Label( (EXTENT_X( screenSize ) / 2) + 9, EXTENT_Y( screenSize ) - 50, (EXTENT_X( screenSize ) / 2) - 20, 39, label, "Textueel", 0, font );
	this->visueelLabel->setPaddingLeft( 9 );
	this->visueelLabel->setPaddingTop( 10 );
	this->visueelLabel->setSkin( skin );

	// placeholder maken en tekenbaar maken
	this->diagram = maCreatePlaceholder();
	maCreateDrawableImage( this->diagram, EXTENT_X( maGetScrSize() ), 370 );

	//nieuwe image met de placeholder maken en een achtergrondkleur toekennen
	this->diagramImage = new Image( 0, 0, EXTENT_X( maGetScrSize() ), 370, label, true, true, this->diagram );
	this->diagramImage->setBackgroundColor( 0x9cd7eb );

	// updaten
	this->setMain( label );
	this->update();
}

// destructor, weer niks aan doen
VisueelScherm::~VisueelScherm()
{}

// hier wordt het hele gebeuren getekend
void VisueelScherm::update()
{
	// update de weerdata
	this->weerData->update();

	// drawtarget instellen zodat we kunnen gaan tekenen
	maSetDrawTarget( this->diagram );

	// de legenda tekenen
	maSetColor(0xFFFFFF);
	maDrawText(7, 7, "% zonneschijn");
	maSetColor(0xFF0000);
	maFillRect(150, 7, 20, 20);

	maSetColor(0xFFFFFF);
	maDrawText(7, 30, "% neerslag");
	maSetColor(0x0000FF);
	maFillRect(150, 30, 20, 20);

	maSetColor(0xFFFFFF);
	maDrawText(7, 53, "Min. temperatuur");
	maSetColor(0x00FF00);
	maFillRect(150, 53, 20, 20);

	// teken 13 lijnen
	maSetColor(0xFFFFFF);
	for( int i = 0; i < 13; i++ )
	{
		maLine(30, 100+(i*20), 309, 100+(i*20) );

		// voeg de y-as waardes toe
		if( i == 0)
			maDrawText(7, 90+(i*20), "100");
		else if( i == 1)
			maDrawText(15, 90+(i*20), "90");
		else if( i == 2)
			maDrawText(15, 90+(i*20), "80");
		else if( i == 3)
			maDrawText(15, 90+(i*20), "70");
		else if( i == 4)
			maDrawText(15, 90+(i*20), "60");
		else if( i == 5)
			maDrawText(15, 90+(i*20), "50");
		else if( i == 6)
			maDrawText(15, 90+(i*20), "40");
		else if( i == 7)
			maDrawText(15, 90+(i*20), "30");
		else if( i == 8)
			maDrawText(15, 90+(i*20), "20");
		else if( i == 9)
			maDrawText(15, 90+(i*20), "10");
		else if( i == 10)
			maDrawText(23, 90+(i*20), "0");
		else if( i == 11)
			maDrawText(7, 90+(i*20), "-10");
		else if( i == 12)
			maDrawText(7, 90+(i*20), "-20");
	}

	// zonneschijn staaf tekenen
	maSetColor(0xFF0000);
	for( int i = 0; i < 3; i++ )
	{
		maFillRect( 40 + ( i*90 ), 200 + ( 100 - this->weerData->zonneschijn[i] * 2 ), 20, this->weerData->zonneschijn[i] * 2 );
	}

	// neerslag staaf tekenen
	maSetColor(0x0000FF);
	for( int i = 0; i < 3; i++ )
	{
		maFillRect( 70 + ( i*90 ), 200 + ( 100 - this->weerData->neerslag[i] * 2 ) , 20, this->weerData->neerslag[i] * 2 );
	}

	// min. temperatuur staaf tekenen
	maSetColor(0x00FF00);
	for( int i = 0; i < 3; i++ )
	{
		maFillRect( 100 + ( i*90 ), 200 + ( 100 - this->weerData->mintemperatuur[i] * 2 ) , 20, this->weerData->mintemperatuur[i] * 2 );
	}

	// drawtarget terug geven aan het scherm
	maSetDrawTarget( HANDLE_SCREEN );

	// de image updaten
	this->diagramImage->setResource( this->diagram );
}

// naar andere scherm veranderen
void VisueelScherm::setToggleScherm( Screen* toggleScherm )
{
	// ga terug naar het andere scherm, textueel
	this->toggleScherm = toggleScherm;
}

// pointerpressevent
void VisueelScherm::pointerPressEvent( MAPoint2d point )
{
	// de update knop is ingedrukt
	if( this->updateLabel->contains( point.x, point.y ) )
	{
		this->updateLabel->setSelected( true );
		touch = true;
	}
	else
	{
		this->updateLabel->setSelected( false );
		touch = false;
	}

	// de visueel knop is ingedrukt
	if( this->visueelLabel->contains( point.x, point.y ) )
	{
		this->visueelLabel->setSelected( true );
		touch2 = true;
	}
	else
	{
		this->visueelLabel->setSelected( false );
		touch2 = false;
	}
}

// pointerreleaseevent, laat de knoppen beter werken
void VisueelScherm::pointerReleaseEvent( MAPoint2d point )
{
	// de update knop is losgelaten
	if( this->updateLabel->contains( point.x, point.y ) && touch )
	{
		this->updateLabel->setSelected( false );
		this->update();
	}
	else
	{
		this->updateLabel->setSelected( false );
		touch = false;
	}

	// de visueel knop is losgelaten
	if( this->visueelLabel->contains( point.x, point.y ) && touch2 )
	{
		this->visueelLabel->setSelected( false );
		this->hide();
		this->toggleScherm->show();
	}
	else
	{
		this->visueelLabel->setSelected( false );
		touch2 = false;
	}
}
