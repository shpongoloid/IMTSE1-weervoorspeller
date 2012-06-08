/*
* WeerData.cpp
*
* Created on: 3 jun. 2012
* Author: niekert
*/

#include "WeerData.hpp"

// een search functie zodat we bepaalde tekst kunnen zoeken
char* searchText( char* buffer, char* string )
{
	// beginpositie bepalen
	char* startPos = strstr( buffer, string );

	if( startPos == NULL )
		return NULL;
	else
		// positie teruggeven
		return( startPos + strlen( string ) );
}

// constructor
WeerData::WeerData() : HttpConnection( this )
{
	// connection-bool op true zetten
	this->isConnecting = true;

	// nieuwe connectie maken met de knmi site
	this->url = "http://www.knmi.nl/waarschuwingen_en_verwachtingen/#meerdaagse";
	int res = this->create( url, HTTP_GET );

	// foutafhandeling
	if( res < 0 )
		lprintfln( "unable to connect - %i\n", res );
	else
		this->finish();

	// weerdata terug naar 0 resetten
	for( int i = 0; i < 3; i++ )
	{
		this->zonneschijn[i] = 0;
		this->neerslag[i] = 0;
		this->mintemperatuur[i] = 0;
	}
}

// destructor, niks doen
WeerData::~WeerData()
{}

// laten updaten
void WeerData::update()
{
	// alleen updaten als er een connectie is en er al niet geupdate wordt
	if( this->isConnecting == false )
	{
		// instellen dat er nu geupdate wordt
		this->isConnecting = true;

		// connectie opnieuw maken
		this->connect( this->url );
	}
}

void WeerData::httpFinished( HttpConnection* http, int result )
{
	// isconnecting op true zetten, er is een connectie
	this->isConnecting = true;

	// data ophalen, 800 bytes
	this->recv( weerDataRecv, 800 );
}

void WeerData::connRecvFinished( Connection* conn, int result )
{
	// blijven lezen tot het einde van de site bereikt is
	if(result >= 0)
	{
		// zoek % zonneschijn
		char* weerDataString = searchText( weerDataRecv, "<td>Zonneschijn (%)</td>" );

		if( weerDataString )
		{
			char data[2];

			// de % zonneschijn van morgen
			strncpy( data, weerDataString + 33, 2 );
			this->zonneschijn[0] = atoi( data );

			// de % zonneschijn van overmorgen
			strncpy( data, weerDataString + 69, 2 );
			this->zonneschijn[1] = atoi( data );

			// de % zonneschijn van over-overmorgen
			strncpy( data, weerDataString + 105, 2 );
			this->zonneschijn[2] = atoi( data );
		}

		// zoek % neerslag
		weerDataString = searchText( weerDataRecv, "<td>Neerslagkans (%)</td>" );

		if( weerDataString )
		{
			char data[2];

			// de % neerslag van morgen
			strncpy( data, weerDataString + 33, 2 );
			this->neerslag[0] = atoi( data );

			// de % neerslag van morgen
			strncpy( data, weerDataString + 69, 2 );
			this->neerslag[1] = atoi( data );

			// de % neerslag van morgen
			strncpy( data, weerDataString + 105, 2 );
			this->neerslag[2] = atoi( data );
		}

		//zoek min. temperatuur
		weerDataString = searchText( weerDataRecv, "<td>Minimumtemperatuur (&deg;C)</td>" );

		if( weerDataString )
		{
			char data[2];

			// de min. temperatuur van morgen
			strncpy( data, weerDataString + 33, 2 );
			this->mintemperatuur[0] = atoi( data );

			// de min. temperatuur van morgen
			strncpy( data, weerDataString + 69, 2 );
			this->mintemperatuur[1] = atoi( data );

			// de min. temperatuur van morgen
			strncpy( data, weerDataString + 108, 2 );
			this->mintemperatuur[2] = atoi( data );

			// connectie sluiten, we hebben al onze informatie binnen
			this->close();
			return;
		}

		// mochten we niks vinden, ga weer opnieuw zoeken
		this->recv(weerDataRecv, CONNECTION_BUFFER_SIZE);
	}

	else
	{
		// foutmelding, connectie sluiten
		this->close();
	}
}

void WeerData::connReadFinished( Connection* conn, int result )
{}

void WeerData::connectFinished(Connection* conn, int result)
{
	// de connectie is beindigd, zet isconnecting op false
	this->isConnecting = false;
}
