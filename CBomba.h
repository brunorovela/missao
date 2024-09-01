#ifndef BOMBA_H
#define BOMBA_H

#include <allegro.h>

class CBomba
{ 
private:
	BITMAP *imgBomba;
public:
	int iPosx;
	int iPosy;
	bool bAtivo;
	int iAlvo;
	void Iniciar();

	CBomba();
	~CBomba();

	void Atualiza( BITMAP * );
};

#endif
