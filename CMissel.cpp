#include "CMissel.h"

CMissel::CMissel()
{
	this->r = ( 100 + ( rand() % 155 ) );
	this->g = ( 100 + ( rand() % 155 ) );
	this->b = ( 100 + ( rand() % 155 ) );

	Iniciar();
}

CMissel::~CMissel()
{
 	this->iPosx = 0;
	this->iPosy = 0;
	this->r = 0;
	this->g = 0;
	this->b = 0;

	this->iLinhax = 0;
	this->iLinhay = 0;
	this->iVelocidade = 0;
	this->bAtivo = false;
	this->iDirecao = 0;
	this->iTempo = 0;
	this->iAlvo = 0;
}

void CMissel::Setax( int vx )
{
	this->iPosx = vx;
}

void CMissel::Setay( int vy )
{
	this->iPosy = vy;
}

void CMissel::Setaxy( int vx, int vy )
{
	this->iPosx += vx;
	this->iPosy += vy;
}

int CMissel::Pegax()
{
	return this->iPosx;
}

int CMissel::Pegay()
{
	return this->iPosy;
}

void CMissel::Atualiza( BITMAP *buffer )
{
	if ( iTempo <= 0 )
	{
		line( buffer, this->iLinhax, this->iLinhay, this->iPosx, this->iPosy, 
		makecol( this->r, this->g, this->b ) );
		
		circlefill( buffer, this->iPosx, this->iPosy, 1, makecol( 255, 0, 0 ) );

		if ( this->iPosy < this->iAlvo )
		{
			if ( iDirecao == 1 ) // vai para a direita
			{
				Setaxy( 1, this->iVelocidade );
			}
			else if ( iDirecao ==  2) // vai para a esquerda
			{
    			Setaxy( -1, this->iVelocidade );
			} else if ( iDirecao == 0 )
			{
				Setaxy( 0, this->iVelocidade );
			}
		} else
		{
			this->bAtivo = false; // Mata o missel
 		}
	} else 
	{
		iTempo--;
	}
}

void CMissel::Iniciar()
{
	this->iVelocidade = 0;
	this->iLinhax = ( 2 + ( rand() % 636 ) );
	this->iDirecao = 0;
	this->iLinhay =  0;	
	this->bAtivo = true;
 	this->Setax( iLinhax );
	this->Setay( iLinhay );
	this->iAlvo = (370 + ( rand() % 100 ) );
	this->iTempo = ( rand() % 1000 );
}
