#ifndef TIRO_H
#define TIRO_H

#include <allegro.h>

static int iMaxRadius = 30;

class CTiro
{ 
public:
	int iPosx;
	int iPosy;
	bool bAtivo;
	int iMinRadius;

	CTiro();
	~CTiro();

	void Setaxy(int, int);
	void Atualiza(BITMAP *);
	int Colisao(int obj2x,int obj2y, int obj2a, int obj2l);
};

#endif
