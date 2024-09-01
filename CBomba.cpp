#include "CBomba.h"

CBomba::CBomba()
{
	this->imgBomba = NULL;
	this->imgBomba = create_bitmap( 16, 16 );
	this->imgBomba = load_bitmap( "bomba.bmp", NULL );

	this->iPosx = ( 15 + ( rand() % 570 ) );
	this->iPosy = 0;
	this->bAtivo = false;
	this->iAlvo = ( 370 + ( rand() % 100 ) );
}

CBomba::~CBomba()
{
	this->iPosx = 0;
	this->iPosy = 0;
	this->bAtivo = false;
	this->iAlvo = 0;
	this->imgBomba = NULL;

	delete imgBomba;
}

void CBomba::Atualiza( BITMAP *buffer )
{
	if ( this->bAtivo )
	{
		if ( this->iPosy < this->iAlvo )
		{
			this->iPosy += 2;
		}else
		{
			bAtivo = false;
		}
		draw_sprite( buffer, this->imgBomba, this->iPosx, this->iPosy );
	}
}

void CBomba::Iniciar()
{
	this->iPosx = (15 + ( rand() % 570 ) );
	this->iPosy = 0;
	this->bAtivo = false;
	this->iAlvo = ( 400 + ( rand() % 60 ) );
}
