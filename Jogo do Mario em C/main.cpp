/*Grupo: Davi Soares de Carvalho
		 Leonardo Lourenço Tavares */
#include <GL/glut.h>
#include <math.h>


float r = 0.0, g = 0.0, b = 0.0;
float minx = -30.0, miny = -30.0, minz = -1.0, maxx = 30.0, maxy = 30.0, maxz = 1.0;
bool eixos = true;
float dxm = 0.0, dym = 0.0, dzm = 0.0; //deslocamento em x, y e z do mario
float passo = 1.0;
bool flagBuraco = false;
 //variáveis de pulo
float px = 0.0, py = 0.0, pz = 0.0;
bool pulo = false;
bool sobe = true;
//--------------------- fim das variáveis de pulo
float flag = 1.0;
//---------------------
float vetorCanoDireita[3], vetorCanoEsquerda[3]; // vetores para fazer a colisão
float vetorInicioBuraco[3], vetorFimBuraco[3];
int idC = 0, idB = 0; //índice dos vetores
float marioDireita, marioEsquerda;

//Protótipos
void display(void);
void reshape(int w, int h);
void Projecao(void);
void eixosGlobal(void);
void special(int tecla, int x, int y);
void timer(int i);
void buraco(int i);
void desenhaMario(void);
void desenhaChao(void);
void desenhaCano(void);
void desenhaCeu(void);
void desenhaMontanha();
void desenhaBloco();
void desenhaCastelo();
void desenhaNuvem();
void desenhaMato();
void desenhaBlocoMarrom();
void desenhaBandeira();
void desenhaBuraco();
//

int main(int argc, char *argv[])
{
	//inicialização dos vetores de colisão
	vetorCanoDireita[0] = 50.0;
	vetorCanoDireita[1] = 130.0;
	vetorCanoDireita[2] = 7000.0;
	vetorCanoEsquerda[0] = 59.0;
	vetorCanoEsquerda[1] = 139.0;
	vetorCanoEsquerda[2] = 7001.0;
	vetorInicioBuraco[0] = 100.0;
	vetorInicioBuraco[1] = 220.0;
	vetorInicioBuraco[2] = 7000.0;
	vetorFimBuraco[0] = 110.0;
	vetorFimBuraco[1] = 230.0;
	vetorFimBuraco[2] = 7001.0;
	//Ecopo de criação de janela
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowSize(500, 500); //Tamanho da Janela
	glutCreateWindow("Mario"); //Cria a Janela
	
	//Escopo de Registro de Callbacks
	glutDisplayFunc(display); //única callback obrigatória
	glutTimerFunc(60, timer, 1); //tempo em milisegundos, função, 
	glutTimerFunc(60, buraco, 1);
	glutReshapeFunc(reshape); //mexer no tamanho da janela
	glutSpecialFunc(special); // teclas especiais tipo as setas do teclado


	//Demais
	//Init();
	glutMainLoop();
	return 0;
}

void display(void) //toda função deve ser registrada na display
{
	glClear(GL_COLOR_BUFFER_BIT); //Sempre a primeira função do display
	if(eixos) eixosGlobal();
	
	//desenhando o cenário
	glPushMatrix();
		glTranslatef(-50, 0, 0);
		desenhaCeu();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(150, 0, 0);
		desenhaCeu();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(80, 1, 0);
		desenhaMato();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(-50, 0, 0);
		desenhaChao();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(150, 0, 0);
		desenhaChao();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(100, 0, 0);
		desenhaBuraco();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(220, 0, 0);
		desenhaBuraco();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(30.0, 0.0, 0.0);
		desenhaMontanha();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(66, 15, 0);
		desenhaBloco();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(72, 15, 0);
		desenhaBloco();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(78, 15, 0);
		desenhaBloco();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(96, 0, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(92, 0, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(88, 0, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(96, 4, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(92, 4, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(96, 8, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(110, 0, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(114, 0, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(118, 0, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(110, 4, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(114, 4, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(110, 8, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(200, 0, 0);
		desenhaBlocoMarrom();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(200, 4, 0);
		desenhaBandeira();
	glPopMatrix();
	
	
	glPushMatrix();
		glTranslatef(50.0, 0.0, 0.0);
		desenhaCano();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(130.0, 0.0, 0.0);
		desenhaCano();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(40.0, 25.0, 0.0);
		desenhaNuvem();
	glPopMatrix();
	glPushMatrix();
		glTranslatef(42.5, 25.0, 0.0);
		desenhaNuvem();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(dxm, dym, dzm);
		glTranslatef(px, py, pz);
		glTranslatef(2, 0, 0);
		glScalef(flag, 1.0, 1.0);
		glTranslatef(-2, 0, 0);
		desenhaMario();
	glPopMatrix();
	
	//Fim do cenário
	
	glutSwapBuffers(); //Sempre a ultima função
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	Projecao();
}
void Projecao(void)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(minx + dxm, maxx + dxm, miny, maxy, minz, maxz); //Tamanho da janela de recorte
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void eixosGlobal(void)
{
	glBegin(GL_LINES);
		glColor3f(1, 0, 0);
		glVertex2f(minx, 0.0);
		glVertex2f(maxx, 0.0);
		
		glColor3f(0, 1, 0);
		glVertex2f(0.0, miny);
		glVertex2f(0.0, maxy);
	glEnd();
}
//Teclas de movimento
void special(int tecla, int x, int y)
{
	switch(tecla)
	{
		case GLUT_KEY_F1:  eixos = !eixos; break;
		case GLUT_KEY_RIGHT: dxm += passo;
                             flag = 1.0;
		//---------------------------------------------------------
							marioDireita = 4.0 + dxm;
							if(marioDireita >= vetorCanoDireita[idC])
							{
								dxm += 11;
								idC++;
							}  
							Projecao();
							break;
		case GLUT_KEY_LEFT: dxm -= passo; 
		                    flag = -1.0;
		//-----------------------------------------------
							marioEsquerda = 3.0 + dxm;
							if(idC > 0)
							{
								if(marioEsquerda <= vetorCanoEsquerda[idC-1])
								{
									dxm -= 11;
									idC--;
								}

							}
							Projecao();
							break;
		case GLUT_KEY_UP:
							pulo = true;
							break;
	}
	glutPostRedisplay(); // redesenha a tela
}

void desenhaMario(void)
{
	/*glBegin(GL_QUADS);
		glColor3f(1, 1, 1);
		glVertex2f(-3.0, 0.0);
		glVertex2f(-3.0, 6.0);
		glVertex2f(3.0, 6.0);
		glVertex2f(3.0, 0.0);
	glEnd(); */
	glBegin(GL_QUADS);
		//pernas
		glColor3f(0, 0, 1);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 1.0);
		glVertex2f(2.0, 1.0);
		glVertex2f(2.0, 0.0);
		
		glVertex2f(3.0, 0.0);
		glVertex2f(3.0, 1.0);
		glVertex2f(5.0, 1.0);
		glVertex2f(5.0, 0.0);
		
		//corpo
		glColor3f(1, 0, 0);
		glVertex2f(0.0, 1.0);
		glVertex2f(0.0, 4.0);
		glVertex2f(5.0, 4.0);
		glVertex2f(5.0, 1.0);
		
		//braço
		glColor3f(1, 1, 1);
		glVertex2f(1.0, 1.5);
		glVertex2f(1.0, 3.5);
		glVertex2f(2.0, 3.5);
		glVertex2f(2.0, 1.5);
		
		//cabeça
		glColor3f(1, 1, 1);
		glVertex2f(1.0, 4.0);
		glVertex2f(1.0, 6.0);
		glVertex2f(4.0, 6.0);
		glVertex2f(4.0, 4.0);
		
		//boné
		glColor3f(1, 0, 0);
		glVertex2f(1.0, 5.5);
		glVertex2f(1.0, 6.1);
		glVertex2f(5.0, 6.1);
		glVertex2f(5.0, 5.5);
		
		//nariz
		glColor3f(1, 1, 1);
		glVertex2f(4.0, 4.5);
		glVertex2f(4.0, 5.0);
		glVertex2f(4.5, 5.0);
		glVertex2f(4.5, 4.5);
	glEnd();
}

//Comando do pulo
void timer(int i)
{
	if(pulo)
	{
		if(sobe)
		{
			py += passo;
			if(py >= 30.0)
				sobe = false;
		}else
		{
			py -= passo;
			if(py <= 0.0)
			{
				sobe = true;
				pulo = false;
				py = 0.0;
			}
		}
		glutPostRedisplay();	
	}
	glutTimerFunc(25, timer, 1);
}
//---------------------

//Comando dos buracos (verifica em tempo de clock se o personagem está em cima de um buraco)
void buraco(int i)
{
	if(dxm >= vetorInicioBuraco[idB] && dxm+5 <= vetorFimBuraco[idB])
	{
        if(pulo == false)
        {
            flagBuraco = true;
            if(flagBuraco)
            {
                dym -= passo;
		        if(dym <= -30.0)
		        {
		        	//zera as variáveis de colisão e buraco 
                    flagBuraco = false;
			        dxm = 0.0;
			        dym = 0.0;
			        idC = 0;
			        idB = 0;
                    Projecao();		
		        }
	       }
        }
    }else
    {
        if(dxm+5 > vetorFimBuraco[idB])
            idB++;
        if(idB > 0)
        {
            if(dxm < vetorInicioBuraco[idB])
                idB--;
        }
    }
	glutPostRedisplay();	
    glutTimerFunc(25, buraco, 1);
}

//-----------------------------------
void desenhaChao(void)
{
	glBegin(GL_QUADS);
		glColor3f(0.6, 0.5, 0);
		glVertex2f(0, 0.0);
		glVertex2f(0, -30.0);
		glVertex2f(200.0, -30.0);
		glVertex2f(200.0, 0.0);
	glEnd();
}

void desenhaCano(void)
{
	glBegin(GL_QUADS);
		glColor3f(0, 0.4, 0);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 8.0);
		glColor3f(0, 0.5, 0);
		glVertex2f(7.0, 8.0);
		glVertex2f(7.0, 0.0);
		
		glColor3f(0, 0.4, 0);
		glVertex2f(-1.0, 8.0);
		glVertex2f(-1.0, 11.0);
		glColor3f(0, 0.5, 0);
		glVertex2f(8.0, 11.0);
		glVertex2f(8.0, 8.0);
		
	glEnd();
	
	glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex2f(-1.0, 8.0);
		glVertex2f(-1.0, 11.0);
		glVertex2f(-1.0, 11.0);
		glVertex2f(8.0, 11.0);
		glVertex2f(8.0, 11.0);
		glVertex2f(8.0, 8.0);
		glVertex2f(8.0, 8.0);
		glVertex2f(-1.0, 8.0);
		
		glColor3f(0, 0, 0);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 8.0);
		glVertex2f(7.0, 8.0);
		glVertex2f(7.0, 0.0);
			
	glEnd(); 
}
void desenhaCeu(void)
{
	glBegin(GL_QUADS);
		glColor3f(0.6, 0.5, 1);
		glVertex2f(0, -30.0);
		glVertex2f(0, 30.0);
		glVertex2f(200.0, 30.0);
		glVertex2f(200.0, -30.0);
	glEnd();
}
void desenhaMontanha()
{
	glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 0.5);
		glVertex2f(-15.0, 0.0);
		glVertex2f(0.0, 15.0);
		glVertex2f(15.0, 0.0);
	glEnd(); 
	glBegin(GL_LINES);
		glColor3f(0, 0, 0);
		glVertex2f(-15.0, 0.0);
		glVertex2f(0.0, 15.0);
		glVertex2f(0.0, 15.0);
		glVertex2f(15.0, 0.0);
	glEnd();
}
void desenhaBloco()
{
	glBegin(GL_QUADS);
		glColor3f(0, 0, 0);
		glVertex2f(0.0, -0.2);
		glVertex2f(0.0, 3.9);
		glVertex2f(4.2, 3.9);
		glVertex2f(4.2, -0.2);
	
		glColor3f(1, 1, 0.5);
		glVertex2f(0.0, 0.0);
		glVertex2f(0.0, 4.0);
		glVertex2f(4.0, 4.0);
		glVertex2f(4.0, 0.0);
	glEnd();
	
	glBegin(GL_POINTS);
		glColor3f(0, 0, 0);
		glVertex2f(0.2, 0.2);
		glVertex2f(0.2, 3.8);
		glVertex2f(3.8, 3.8);
		glVertex2f(3.8, 0.2);
	glEnd();
	
	char *texto = "?";
    glRasterPos2f(1.5, 1.0);
    while(*texto){
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *texto++);
    }	
}

void desenhaCastelo()
{
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.0, 0.5);
	glVertex2f(0.0, 0.0);
	glVertex2f(0.0, 7.0);
	glVertex2f(9.0, 7.0);
	glVertex2f(9.0, 0.0);
	
	glVertex2f(3.0, 7.0);
	glVertex2f(3.0, 10.0);
	glVertex2f(6.0, 10.0);
	glVertex2f(6.0, 7.0);
}

void desenhaNuvem()
{
	float x, y;
	float raio = 1.5, centro[2];
	centro[0] = 0;
	centro[1] = 0;
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
        for(int ang = 0; ang<360; ang += 10){
            x = cos(ang * M_PI/180.0) * raio + centro[0];
            y = sin(ang * M_PI/180.0) * raio + centro[1];
            glVertex2f(x, y); 
		}
		for(int ang = 0; ang<360; ang += 10){
            x = (cos(ang * M_PI/180.0) * raio + (centro[0] -1));
            y = (sin(ang * M_PI/180.0) * raio + (centro[1] -1));
            glVertex2f(x, y); 
		}
		for(int ang = 0; ang<360; ang += 10){
            x = (cos(ang * M_PI/180.0) * raio + (centro[0]+1));
            y = (sin(ang * M_PI/180.0) * raio + (centro[1]-1));
            glVertex2f(x, y); 
		}
    glEnd();
}

void desenhaMato()
{
	float x, y;
	float raio = 1.5, centro[2];
	centro[0] = 0;
	centro[1] = 0;
	glBegin(GL_POLYGON);
	glColor3f(0, 0.8, 0);
        for(int ang = 0; ang<360; ang += 10){
            x = cos(ang * M_PI/180.0) * raio + centro[0];
            y = sin(ang * M_PI/180.0) * raio + centro[1];
            glVertex2f(x, y); 
		}
		for(int ang = 0; ang<360; ang += 10){
            x = (cos(ang * M_PI/180.0) * raio + (centro[0] -1));
            y = (sin(ang * M_PI/180.0) * raio + (centro[1] -1));
            glVertex2f(x, y); 
		}
		for(int ang = 0; ang<360; ang += 10){
            x = (cos(ang * M_PI/180.0) * raio + (centro[0]+1));
            y = (sin(ang * M_PI/180.0) * raio + (centro[1]-1));
            glVertex2f(x, y); 
		}
    glEnd();
}

void desenhaBlocoMarrom()
{
	/*glBegin(GL_QUADS);
		glColor3f(0.6, 0.5, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 4);
		glVertex2f(4, 4);
		glVertex2f(4, 0); */
		
	glBegin(GL_TRIANGLES);
		glColor3f(0, 0, 0);
		glVertex2f(0, 0);
		glVertex2f(4, 4);
		glVertex2f(4, 0);
		
		glColor3f(0.7, 0.6, 0);
		glVertex2f(0, 0);
		glVertex2f(0, 4);
		glVertex2f(4, 4);
	glEnd();
	
	glBegin(GL_LINES);
		glColor3f(0.4, 0.3, 0);
		glVertex2f(0, 0);
		glVertex2f(4, 4);
		glVertex2f(0, 4);
		glVertex2f(4, 0);
	glEnd();
	
	glBegin(GL_QUADS);
		glColor3f(0.4, 0.3, 0);
		glVertex2f(1.3, 1.3);
		glVertex2f(1.3, 2.7);
		glVertex2f(2.7, 2.7);
		glVertex2f(2.7, 1.3);
	glEnd();
		
}

void desenhaBandeira()
{
	glBegin(GL_QUADS);
		glColor3f(0, 1, 0.5);
		glVertex2f(1.5, 0);
		glVertex2f(1.5, 20);
		glVertex2f(2.5, 20);
		glVertex2f(2.5, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
		glColor3f(1, 1, 1);
		glVertex2f(1.5, 15.5);
		glVertex2f(-2.5, 17);
		glVertex2f(1.5, 18.5);
	glEnd();
	glBegin(GL_POLYGON);
		glColor3f(0, 0.4, 0);
		float x, y;
		float raio = 1.5, centro[2];
		centro[0] = 2.0;
		centro[1] = 20;
		for(int ang = 0; ang<360; ang += 10){
            x = cos(ang * M_PI/180.0) * raio + centro[0];
            y = sin(ang * M_PI/180.0) * raio + centro[1];
            glVertex2f(x, y); 
		}
	glEnd();
}
void desenhaBuraco()
{
	glBegin(GL_QUADS);
		glColor3f(0.6, 0.5, 1);
		glVertex2f(0, 0);
		glVertex2f(0, -30);
		glVertex2f(10, -30);
		glVertex2f(10, 0);
	glEnd();
}

//sjudice@faeterj-petropolis.edu.br
//slide 4, página 33
// equação paramétrica do círculo:  x() = cos() *r + cx;  y() = sen() *r + cy
