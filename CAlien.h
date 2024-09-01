#ifndef ALIEN_H
#define ALIEN_H

#include "CBomba.h"
#include <allegro.h>

const int QtdeBombas = 3;

class CAlien
{ 
private:
	BITMAP *imgAlien;
	int iPosx;
	int iPosy;
public:
	int iVelocidade;
	bool bAtivo;
	int iDirecao;
	int iTempo;
	int iLargura;
	int iAltura;

	CBomba Bombas[ ::QtdeBombas ];

	CAlien();
	~CAlien();
	
	void Setaxy( int,int );
	void Setax( int vx );
	void Setay( int vy );
	int Pegax();
	int Pegay();
	void Atualiza( BITMAP * );
	void Iniciar();
};

#endif
