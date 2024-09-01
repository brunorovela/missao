#ifndef MISSEL_H
#define MISSEL_H

#include <allegro.h>

class CMissel
{
private:
	int iPosx;
	int iPosy;
	int r, g, b;

public:
	int iLinhax;
	int iLinhay;
	int iVelocidade;
	bool bAtivo;
	int iDirecao;
	int iTempo;
	int iAlvo;
	
	CMissel();
	~CMissel();
	
	void Setaxy( int, int );
	void Setax( int vx );
	void Setay( int vy );
	int Pegax();
	int Pegay();
	void Atualiza( BITMAP * );
	void Iniciar();
};

#endif
