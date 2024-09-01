#include "CTiro.h"

CTiro::CTiro()
{
	this->iPosx = 0;
	this->iPosy = 0;
	this->bAtivo = false;
	this->iMinRadius = 5;
}

CTiro::~CTiro()
{
	this->iPosx = 0;
	this->iPosy = 0;
	this->bAtivo = false;
	this->iMinRadius = 0;
}

void CTiro::Atualiza(BITMAP *buffer)
{
	if (bAtivo && iMinRadius < iMaxRadius)
	{
		this->iMinRadius += 1;
		circle(buffer, this->iPosx, this->iPosy, this->iMinRadius, makecol(255,255,0));
	} else
	{
		this->bAtivo = false;
		this->iMinRadius = 5;
	}
	
}

void CTiro::Setaxy(int vx, int vy)
{
	this->iPosx = vx;
	this->iPosy = vy;
}

int CTiro::Colisao(int obj2x,int obj2y, int obj2a, int obj2l) 
{
	if (this->iPosx+this->iMinRadius > obj2x && 
	    this->iPosx < obj2x+obj2l && 
		this->iPosy+this->iMinRadius > obj2y && 
		this->iPosy < obj2y+obj2a)
 	{
		return 1; // colidiu
	} else return 0; // não colidiu
}
