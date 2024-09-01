#include <allegro.h>
#include "CMissel.h"
#include "CAlien.h"
#include "CTiro.h"
#include <time.h>

void IniciaMisseis( CMissel [], int );
	
int iVel = 1;

//Muda a dificuldade a cada 50 misseis destruidos.
const int MudaDificuldade = 50;
	
// Quantidade de Misseis durante a partida
const int QtdeMisseis = 500;

// Quantidade de Tiros
const int QtdeTiros = 10;

// Quantidade de Misseis a cada mudança de nivel
const int Misseis_por_Nivel = 10;

// variáveis globais
int fps = 0;
int fps_antigo = 0;
int fps_speed = 0;

// prototipo do contador de frames
void frame_rate();

// prototipo do contador de velocidade
void incrementa_speed();

int main( int argc, char *argv[] )
{
	allegro_init();
	install_keyboard();
	install_mouse();
	set_color_depth( 32 ); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640, 480, 0, 0);

	int i = 0;
	int j = 0;
	int iNivel = 1;
	int iMortos = 0;
	int iControle = 0;
	int Buffer_Teclado = 0;
	int Buffer_Mouse = 0;
	srand( time( NULL ) );

	install_timer();
	install_int( frame_rate, 1000 );
	install_int_ex( incrementa_speed, BPS_TO_TIMER( 60 ) );

	BITMAP *buffer = NULL;
	buffer = create_bitmap(SCREEN_W,SCREEN_H);
	clear(buffer);
	
	BITMAP *fundo = NULL;
	fundo = create_bitmap(SCREEN_W,SCREEN_H);
	clear(fundo);
	fundo = load_bitmap( "fundo.bmp", NULL );

	BITMAP *msg = NULL;
	msg = create_bitmap(294,130);
	clear(msg);
	msg = load_bitmap( "msg.bmp", NULL );

	BITMAP *bmpexplosao = NULL;
	bmpexplosao = create_bitmap(24,20);
	clear(bmpexplosao);
	bmpexplosao = load_bitmap( "explosao.bmp",NULL );
	
	BITMAP *bmpMouse = NULL;
	bmpMouse = create_bitmap(16,16);
	clear(bmpMouse);
	bmpMouse = load_bitmap( "mira.bmp", NULL );
	
	bool bGameOver = false;

	CMissel Missel[ ::QtdeMisseis ];
	CTiro Tiro[ ::QtdeTiros ];
	CAlien Alien;

	//Inicia os misseis
	IniciaMisseis( Missel, ::QtdeMisseis );

	while(!bGameOver)
	{
		while ( ::fps_speed > 0 )
      	{
			clear_bitmap( buffer );
			blit(fundo, buffer, 0,0,0,0, SCREEN_W, SCREEN_H );
		
			// INICIO ALIEN
			if ( Alien.bAtivo )
			{
				Alien.Atualiza( buffer );
			}
			// FIM ALIEN
			
			// INICIO MISSEL
			for ( i=iControle; i < ( iControle + (::Misseis_por_Nivel) ); i++ )
			{
				if ( ( iControle + (::Misseis_por_Nivel) ) <= (::QtdeMisseis) )
				{
					for (j=0; j<QtdeTiros; j++)
					{
						if  (Tiro[j].bAtivo)
						{
							if (Tiro[j].Colisao(Missel[i].Pegax(),Missel[i].Pegax(),0, 0) == 1)
							{
								Missel[i].bAtivo = false;
								iMortos++;
								break;
							}
					}
					}
					
					//aquiaquiaquiaquiaquiaquiaquiaquiaquiaquiaquiaquiaqui
					if ( Missel[i].bAtivo )
					{
						Missel[i].Atualiza( buffer );

						if ( !Missel[i].bAtivo )
						{
							iMortos++;
							draw_sprite( fundo, bmpexplosao, Missel[i].Pegax()-5, Missel[i].Pegay() );
						}
	
						if ( iMortos ==(iControle + (::Misseis_por_Nivel)) ) 
						{
							if ( (iControle + (::Misseis_por_Nivel) ) <= (::QtdeMisseis) )
							{
								iNivel++;
								iControle += (::Misseis_por_Nivel);
							} 
						}
					}
				} else 
				{
					bGameOver = true;
				}
			}
			// FIM MISSEL			
		
			//INICIO BOMBA
			for ( i=0; i < 3; i++ )
			{
				if ( Alien.Pegax() == Alien.Bombas[i].iPosx )
				{
					Alien.Bombas[i].iPosy = (Alien.Pegay() + 10);
					Alien.Bombas[i].bAtivo = true;
				}
				if (Alien.Bombas[i].bAtivo)
				{
					Alien.Bombas[i].Atualiza( buffer );
				}
			}
			//FIM BOMBA
			
			//QUANTO ATIRAR COM O MOUSE
			if (Buffer_Mouse == 0)
			{
				if (mouse_b & 1)
				{
					for (i=0;i<QtdeTiros;i++)
					{
						if (!Tiro[i].bAtivo)
						{
							Tiro[i].bAtivo = true;
							Tiro[i].Setaxy(mouse_x+8,mouse_y+8);
							break;
						}
					}
					Buffer_Mouse = 10;
				}
			} else
			{
				Buffer_Mouse--;
			}
			//TERMINA O TIRO DO MOUSE

			//DESENHA O TIRO SE ESTIVER ATIVO
			for (i=0;i<QtdeTiros;i++)
			{
				if (Tiro[i].bAtivo)
				{
					Tiro[i].Atualiza(buffer);
				} 
			}
			//TERMINA O DESENHO DO TIRO
	
			if ( Buffer_Teclado == 0 )
			{
				if ( key[KEY_ESC] )
				{
					bGameOver = true;
					Buffer_Teclado = 50;
				}

				if (key[KEY_F2])
				{
					i = 0;
					iNivel = 1;
					iMortos = 0;
					iControle = 0;
					iVel = 1;
					bGameOver = false;
					IniciaMisseis( Missel, ::QtdeMisseis );
					Buffer_Teclado = 50;
					fundo = load_bitmap( "fundo.bmp", NULL );
				}
			} else 
			{
				Buffer_Teclado--;
			}

  			textprintf_ex(buffer, font, 0, 0, makecol(255,255,0), -1,"Mortos.: %d", iMortos);
  			textprintf_ex(buffer, font, 0, 10, makecol(255,255,0), -1,"Nivel.: %d", iNivel);
			draw_sprite( buffer, bmpMouse, mouse_x, mouse_y );

	    	if ( bGameOver )
    		{
    			while( !key[KEY_ENTER] )
      			{
	   				fps = 0;
	   				fps_speed=0;
	   				draw_sprite( screen, msg, 170, 200 );

					if ( key[KEY_F2] )
					{
						i = 0;
						iNivel = 1;
						iMortos = 0;
						iControle = 0;
						iVel = 1;
						bGameOver = false;
						IniciaMisseis( Missel, ::QtdeMisseis );
						fundo = load_bitmap( "fundo.bmp", NULL );
						break;
					}
					if ( key[KEY_F3] )
					{
						bGameOver = false;
						break;
					}
    			}
			}
			textprintf_right_ex( buffer, font, SCREEN_W, 0, makecol(255,255,0), -1, "FPS %d", ::fps_antigo );
			
			::fps_speed--;
    	    ::fps++;
		}
		blit( buffer, screen, 0,0,0,0, SCREEN_W, SCREEN_H);
    	vsync();
	}

	bmpMouse = NULL;
	bmpexplosao = NULL;
	msg = NULL;
	buffer = NULL;
	fundo = NULL;

	delete( bmpMouse );
	delete( bmpexplosao );
	delete( msg );
	delete( buffer );
	delete( fundo );

	allegro_exit();
	return 0;     
}
 
void IniciaMisseis( CMissel Missel[], int vQtdeMisseis )
{
	int i = 0;
	int iTempo = 0;

	for ( i=0; i < vQtdeMisseis; i++ )
	{
		Missel[i].Iniciar();

		if ( i % (::MudaDificuldade) == 0 )
		{
			iVel++;
		}
		Missel[i].iVelocidade = iVel;

		//Define direção dos misseis
		if ( Missel[i].Pegax() < 100 )
		{
			Missel[i].iDirecao = 1; // direita
		}else if ( Missel[i].Pegax() > 550 )
		{
			Missel[i].iDirecao = 2; // Esquerda
		} else
		{
			Missel[i].iDirecao = 0;
		}
	}
}

void frame_rate()
{
   ::fps_antigo = ::fps;
   ::fps = 0;
}
   
void incrementa_speed()
{
   ::fps_speed++;
} 
END_OF_MAIN();
