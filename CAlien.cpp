#include "CAlien.h"

CAlien::CAlien()
{
	this->iLargura = 56;
	this->iAltura = 17;
	this->imgAlien = NULL;
	this->imgAlien = create_bitmap( this->iLargura, this->iAltura );
	this->imgAlien = load_bitmap( "alien.bmp", NULL );
	Iniciar();
}

CAlien::~CAlien()
{
	this->iPosx = 0;
	this->iPosy = 0;
	this->iVelocidade = 0;
	this->bAtivo = false;
	this->iDirecao = 0;
	this->iTempo = 0;
	this->iLargura = 0;
	this->iAltura = 0;

	imgAlien = NULL;
	delete imgAlien;
}

void CAlien::Setax( int vx )
{
	this->iPosx = vx;
}

void CAlien::Setay( int vy )
{
	this->iPosy = vy;
}

void CAlien::Setaxy( int vx, int vy )
{
	this->iPosx += vx;
}
int CAlien::Pegax()
{
	return this->iPosx;
}
 
int CAlien::Pegay()
{
	return this->iPosy;
}

void CAlien::Atualiza( BITMAP *buffer )
{
	int i = 0;

	if ( iTempo <= 0 )
	{
		Setaxy( this->iVelocidade, 1 );

		if ( this->iPosx >= 700 )
		{
			for ( i=0; i< (::QtdeBombas); i++ )
			{
				Bombas[i].Iniciar();
			}

			this->iPosx = -57;
			this->iPosy = ( 17 + ( rand() % 70 ) );
			this->iTempo = ( rand() % 500 );
		}
		draw_sprite( buffer, imgAlien, this->iPosx, this->iPosy );
	} else 
	{
		iTempo--;
	}

	
}

void CAlien::Iniciar()
{
	this->iVelocidade = 1;
	this->iDirecao = 0;
	this->bAtivo = true;
 	this->iPosx = 0;
	this->iPosy = ( 17 + ( rand() % 70 ) );
	this->iTempo = ( rand() % 500 );
}
