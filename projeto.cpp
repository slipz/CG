#include "header.h"
#include <cmath>
/* 
	Projeto Computacao Grafica 2018
	Bruna Lopes - 2015227332
	Eduardo Andrade - 2014199186
	" La Casa de las Latas "
*/

//Identificador das Texturas
RgbImage imag;
GLuint textures[30];
int proj = 1;

node can_tree;

int can_display[10];
int can_hit = 0;


void ApplyGLNormal(GLfloat v1[], GLfloat v2[], GLfloat v3[]){
	Vector d1 , d2;	
	d1.x = v2[0] - v1[0];
	d1.y = v2[1] - v1[1];
	d1.z = v2[2] - v1[2];

	d2.x = v3[0] - v1[0];
	d2.y = v3[1] - v1[1];
	d2.z = v3[2] - v1[2];

	Vector cross_product;
	cross_product.x = d1.y*d2.z - d1.z*d2.y;
	cross_product.y = d1.z*d2.x - d1.x*d2.z;
	cross_product.z = d1.x*d2.y - d1.y*d2.x;

	float distance = sqrt(	(cross_product.x*cross_product.x) +
				(cross_product.y*cross_product.y) +
				(cross_product.z*cross_product.z));
	
	Vector normal;
	normal.x = cross_product.x / distance;
	normal.y = cross_product.y / distance;
	normal.z = cross_product.z / distance;

	glNormal3f(normal.x , normal.y , normal.z);
}

void drawQuadro(float width, float height, float depth, int tex_id){

	// Frente Quadro
	glEnable(GL_TEXTURE_2D);
	if(modulate){
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	glBindTexture(GL_TEXTURE_2D,textures[tex_id]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0f, 0.0f, depth);
		glTexCoord2f(1.0f,0.0f); glVertex3f(width,0.0f, depth);
		glTexCoord2f(1.0f,1.0f); glVertex3f(width,height,depth);
		glTexCoord2f(0.0f,1.0f); glVertex3f(0.0f,height,depth);
	glEnd();
	

	glBindTexture(GL_TEXTURE_2D,textures[10]);
	glBegin(GL_QUADS);
		// Esquerda
		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(0.3f,0.0f); glVertex3f(0.0f, 0.0f, depth);
		glTexCoord2f(0.3f,0.3f); glVertex3f(0.0f, height, depth);
		glTexCoord2f(0.0f,0.3f); glVertex3f(0.0f, height, 0.0f);

		glTexCoord2f(0.0f,0.0f); glVertex3f(width, 0.0f, depth);
		glTexCoord2f(0.3f,0.0f); glVertex3f(width, 0.0f, 0.0f);
		glTexCoord2f(0.3f,0.3f); glVertex3f(width, height, 0.0f);
		glTexCoord2f(0.0f,0.3f); glVertex3f(width, height, depth);

		glTexCoord2f(0.0f,0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
		glTexCoord2f(0.0f,0.3f); glVertex3f(width, 0.0f, 0.0f);
		glTexCoord2f(0.3f,0.3f); glVertex3f(width, 0.0f, depth);
		glTexCoord2f(0.3f,0.0f); glVertex3f(0.0f, 0.0f, depth);
	glEnd();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_TEXTURE_2D);
}

void load_textures(){

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &textures[0]);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	imag.LoadBmpFile("images/floor_wood.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[1]);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	imag.LoadBmpFile("images/baseball_ball.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[2]);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	imag.LoadBmpFile("images/sodacan.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[3]);
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	imag.LoadBmpFile("images/can_top.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[4]);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	imag.LoadBmpFile("images/left.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[5]);
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	imag.LoadBmpFile("images/front.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[6]);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	imag.LoadBmpFile("images/right.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[7]);
	glBindTexture(GL_TEXTURE_2D, textures[7]);
	imag.LoadBmpFile("images/back.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[8]);
	glBindTexture(GL_TEXTURE_2D, textures[8]);
	imag.LoadBmpFile("images/top.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[9]);
	glBindTexture(GL_TEXTURE_2D, textures[9]);
	imag.LoadBmpFile("images/brilho0.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
                     imag.GetNumCols(),
                     imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     imag.ImageData()); 

   	glGenTextures(1, &textures[10]);
	glBindTexture(GL_TEXTURE_2D, textures[10]);
	imag.LoadBmpFile("images/lateral_quadros.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
                     imag.GetNumCols(),
                     imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     imag.ImageData()); 

   	glGenTextures(1, &textures[11]);
	glBindTexture(GL_TEXTURE_2D, textures[11]);
	imag.LoadBmpFile("images/quadro1.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
                     imag.GetNumCols(),
                     imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     imag.ImageData()); 

   	glGenTextures(1, &textures[12]);
	glBindTexture(GL_TEXTURE_2D, textures[12]);
	imag.LoadBmpFile("images/quadro2.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
                     imag.GetNumCols(),
                     imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     imag.ImageData()); 

    glGenTextures(1, &textures[13]);
	glBindTexture(GL_TEXTURE_2D, textures[13]);
	imag.LoadBmpFile("images/teste.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
                     imag.GetNumCols(),
                     imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     imag.ImageData()); 

    glGenTextures(1, &textures[14]);
	glBindTexture(GL_TEXTURE_2D, textures[14]);
	imag.LoadBmpFile("images/racha.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, 3,
                     imag.GetNumCols(),
                     imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     imag.ImageData()); 


	glGenTextures(1, &textures[15]);
	glBindTexture(GL_TEXTURE_2D, textures[15]);
	imag.LoadBmpFile("images/texparede.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[16]);
	glBindTexture(GL_TEXTURE_2D, textures[16]);
	imag.LoadBmpFile("images/grass.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[17]);
	glBindTexture(GL_TEXTURE_2D, textures[17]);
	imag.LoadBmpFile("images/garage_floor.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[18]);
	glBindTexture(GL_TEXTURE_2D, textures[18]);
	imag.LoadBmpFile("images/warehouse_door.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[19]);
	glBindTexture(GL_TEXTURE_2D, textures[19]);
	imag.LoadBmpFile("images/floor1.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[20]);
	glBindTexture(GL_TEXTURE_2D, textures[20]);
	imag.LoadBmpFile("images/tequilla.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[21]);
	glBindTexture(GL_TEXTURE_2D, textures[21]);
	imag.LoadBmpFile("images/rum.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );	

	glGenTextures(1, &textures[22]);
	glBindTexture(GL_TEXTURE_2D, textures[22]);
	imag.LoadBmpFile("images/vodka.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[23]);
	glBindTexture(GL_TEXTURE_2D, textures[23]);
	imag.LoadBmpFile("images/whiskey.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[24]);
	glBindTexture(GL_TEXTURE_2D, textures[24]);
	imag.LoadBmpFile("images/billiards.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );


	glGenTextures(1, &textures[25]);
	glBindTexture(GL_TEXTURE_2D, textures[25]);
	imag.LoadBmpFile("images/guns.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );	

	glGenTextures(1, &textures[26]);
	glBindTexture(GL_TEXTURE_2D, textures[26]);
	imag.LoadBmpFile("images/obama.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[27]);
	glBindTexture(GL_TEXTURE_2D, textures[27]);
	imag.LoadBmpFile("images/pinkfloyd.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );

	glGenTextures(1, &textures[28]);
	glBindTexture(GL_TEXTURE_2D, textures[28]);
	imag.LoadBmpFile("images/retroposter.bmp"); 
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
		imag.GetNumCols(),
		imag.GetNumRows(),
		0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData() );



    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void initMaterials(int material){
	switch (material){
		case 0: //esmerald
			glMaterialfv(GL_FRONT,GL_AMBIENT,  esmeraldAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  esmeraldDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, esmeraldSpec);
			glMateriali (GL_FRONT,GL_SHININESS,esmeraldCoef);
			break;
		case 1: //jade
			glMaterialfv(GL_FRONT,GL_AMBIENT,  jadeAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  jadeDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, jadeSpec);
			glMateriali (GL_FRONT,GL_SHININESS,jadeCoef);
			break;
	       case 2: //obsidian
			glMaterialfv(GL_FRONT,GL_AMBIENT,  obsidianAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  obsidianDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, obsidianSpec);
			glMateriali (GL_FRONT,GL_SHININESS,obsidianCoef);
			break;
		case 3: //pearl
			glMaterialfv(GL_FRONT,GL_AMBIENT,  pearlAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  pearlDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, pearlSpec);
			glMateriali (GL_FRONT,GL_SHININESS,pearlCoef);
			break;
		case 4: //ruby
			glMaterialfv(GL_FRONT,GL_AMBIENT,  rubyAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  rubyDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, rubySpec);
			glMateriali (GL_FRONT,GL_SHININESS,rubyCoef);
			break;
	         case 5: //turquoise
			glMaterialfv(GL_FRONT,GL_AMBIENT,  turquoiseAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  turquoiseDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, turquoiseSpec);
			glMateriali (GL_FRONT,GL_SHININESS,turquoiseCoef);
			break;
		case 6: //brass
			glMaterialfv(GL_FRONT,GL_AMBIENT,  brassAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  brassDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, brassSpec);
			glMateriali (GL_FRONT,GL_SHININESS,brassCoef);
			break;
		case 7: //bronze
			glMaterialfv(GL_FRONT,GL_AMBIENT,  bronzeAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  bronzeDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, bronzeSpec);
			glMateriali (GL_FRONT,GL_SHININESS,bronzeCoef);
			break;
		case 8: //chrome
			glMaterialfv(GL_FRONT,GL_AMBIENT,  chromeAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  chromeDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, chromeSpec);
			glMateriali (GL_FRONT,GL_SHININESS,chromeCoef);
			break;
	    case 9: //copper
			glMaterialfv(GL_FRONT,GL_AMBIENT,  copperAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  copperDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, copperSpec);
			glMateriali (GL_FRONT,GL_SHININESS,copperCoef);
			break;
	    case 10: //gold
			glMaterialfv(GL_FRONT,GL_AMBIENT,  goldAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  goldDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, goldSpec);
			glMateriali (GL_FRONT,GL_SHININESS,goldCoef);
			break;
		case 11: //silver
			glMaterialfv(GL_FRONT,GL_AMBIENT,  silverAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  silverDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, silverSpec);
			glMateriali (GL_FRONT,GL_SHININESS,silverCoef);
			break;
		case 12: //blackPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  blackPlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackPlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, blackPlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,blackPlasticCoef);
			break;
		case 13: //cyankPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  cyanPlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  cyanPlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, cyanPlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,cyanPlasticCoef);
			break;
		case 14: //greenPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  greenPlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenPlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, greenPlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,greenPlasticCoef);
			break;
		case 15: //redPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  redPlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  redPlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, redPlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,redPlasticCoef);
			break;
	        case 16: //yellowPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  whitePlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  whitePlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, whitePlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,whitePlasticCoef);
			break;
		case 17: //yellowPlastic
			glMaterialfv(GL_FRONT,GL_AMBIENT,  yellowPlasticAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  yellowPlasticDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, yellowPlasticSpec);
			glMateriali (GL_FRONT,GL_SHININESS,yellowPlasticCoef);
			break;
	        case 18: //blackRubber
			glMaterialfv(GL_FRONT,GL_AMBIENT,  blackRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  blackRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, blackRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,blackRubberCoef);
			break;
		case 19: //cyanRubber
			glMaterialfv(GL_FRONT,GL_AMBIENT,  cyanRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  cyanRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, cyanRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,cyanRubberCoef);
			break;
		case 20: //greenRubber

			glMaterialfv(GL_FRONT,GL_AMBIENT,  greenRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  greenRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, greenRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,greenRubberCoef);
			break;
		case 21: //redRubber
			glMaterialfv(GL_FRONT,GL_AMBIENT,  redRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  redRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, redRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,redRubberCoef);
			break;
		case 22: //redRubber
			glMaterialfv(GL_FRONT,GL_AMBIENT,  whiteRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  whiteRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, whiteRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,whiteRubberCoef);
			break;
		case 23: //redRubber
			glMaterialfv(GL_FRONT,GL_AMBIENT,  yellowRubberAmb  );
			glMaterialfv(GL_FRONT,GL_DIFFUSE,  yellowRubberDif );
			glMaterialfv(GL_FRONT,GL_SPECULAR, yellowRubberSpec);
			glMateriali (GL_FRONT,GL_SHININESS,yellowRubberCoef);
			break;
	}
}

void defineLuz(){
	//global
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCor);

	//Lampada (pontual)
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightambient);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightspecular);
	glLightf (GL_LIGHT0, GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf (GL_LIGHT0, GL_LINEAR_ATTENUATION, localAttLin) ;
	//glLightf (GL_LIGHT0, GL_QUADRATIC_ATTENUATION,localAttQua) ;

	glEnable(GL_LIGHT1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightpos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, lightambient);
	glLightfv(GL_LIGHT1, GL_SPECULAR, lightspecular);
	glLightf (GL_LIGHT1, GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf (GL_LIGHT1, GL_LINEAR_ATTENUATION, localAttLin) ;
	//glLightf (GL_LIGHT1, GL_QUADRATIC_ATTENUATION,localAttQua) ;

	glEnable(GL_LIGHT2);
	glLightfv(GL_LIGHT2, GL_POSITION, lightpos2);
	glLightfv(GL_LIGHT2, GL_AMBIENT, lightambient);
	glLightfv(GL_LIGHT2, GL_SPECULAR, lightspecular);
	glLightf (GL_LIGHT2, GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf (GL_LIGHT2, GL_LINEAR_ATTENUATION, localAttLin) ;
	//glLightf (GL_LIGHT2, GL_QUADRATIC_ATTENUATION,localAttQua) ;

	glEnable(GL_LIGHT3);
	glLightfv(GL_LIGHT3, GL_POSITION, lightpos3);
	glLightfv(GL_LIGHT3, GL_AMBIENT, lightambient);
	glLightfv(GL_LIGHT3, GL_SPECULAR, lightspecular);
	glLightf (GL_LIGHT3, GL_CONSTANT_ATTENUATION, localAttCon);
	glLightf (GL_LIGHT3, GL_LINEAR_ATTENUATION, localAttLin) ;
	//glLightf (GL_LIGHT3, GL_QUADRATIC_ATTENUATION,localAttQua) ;
}

void initCanTree(){
	int i;

	// Init Can Array
	for(i=0; i<NUM_CANS; i++){
		can_display[i] = 1;
	}

	// Base
	//1o
	node n1 = (node)malloc(sizeof(node));
	n1->id = 0;
	n1->is_base = 1;
	n1->BottomLeft = NULL;
	n1->BottomRight = NULL;

	//2o
	node n2 = (node)malloc(sizeof(node));
	n2->id = 1;
	n2->is_base = 1;
	n2->BottomLeft = NULL;
	n2->BottomRight = NULL;

	//3o
	node n3 = (node)malloc(sizeof(node));
	n3->id = 2;
	n3->is_base = 1;
	n3->BottomLeft = NULL;
	n3->BottomRight = NULL;

	//4o
	node n4 = (node)malloc(sizeof(node));
	n4->id = 3;
	n4->is_base = 1;
	n4->BottomLeft = NULL;
	n4->BottomRight = NULL;

	// P2
	//1o
	node n5 = (node)malloc(sizeof(node));
	n5->id = 4;
	n5->is_base = 0;
	n5->BottomLeft = n1;
	n5->BottomRight = n2;

	//2o
	node n6 = (node)malloc(sizeof(node));
	n6->id = 5;
	n6->is_base = 0;
	n6->BottomLeft = n2;
	n6->BottomRight = n3;

	//3o
	node n7 = (node)malloc(sizeof(node));
	n7->id = 6;
	n7->is_base = 0;
	n7->BottomLeft = n3;
	n7->BottomRight = n4;

	// P3
	//1o
	node n8 = (node)malloc(sizeof(node));
	n8->id = 7;
	n8->is_base = 0;
	n8->BottomLeft = n5;
	n8->BottomRight = n6;

	//2o
	node n9 = (node)malloc(sizeof(node));
	n9->id = 8;
	n9->is_base = 0;
	n9->BottomLeft = n6;
	n9->BottomRight = n7;	

	// Topo
	can_tree = (node)malloc(sizeof(node));
	can_tree->id = 9;
	can_tree->is_base = 0;
	can_tree->BottomLeft = n8;
	can_tree->BottomRight = n9;
}

//Funcao init - inicializa openGL
void init(void){
	glClearColor(WHITE);		// Clear Color - Branco

	glEnable(GL_NORMALIZE);

	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_LIGHTING);
    defineLuz();

	glEnable(GL_BLEND);
	glBlendFunc (GL_ONE, GL_ZERO);
	
    initCanTree();
    
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	/*glEnable(GL_COLOR_MATERIAL);	
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE ); 
	*/
	//glColorMaterial();

	glEnable(GL_CULL_FACE);		// Ativa o CullFace (so renderiza face visivel)
	glCullFace(GL_BACK);		

	load_textures();
}

void keysHandler(){

	if(keysDown[0] == 1){	// A
		// Calcular novo angulo
		if(checkCollisionObs(obsP[0] + (step*cos(transAng)),obsP[1],obsP[2] - (step*sin(transAng)))){
			transAng = angObs + PI/2; 
			obsP[0] = obsP[0] + (step*cos(transAng));
			obsP[2] = obsP[2] - (step*sin(transAng));
		}
	}
	if(keysDown[1] == 1){	// S
		if(checkCollisionObs(obsP[0] - (step*cos(angObs)),obsP[1],obsP[2] + (step*sin(angObs)))){
			obsP[0] = obsP[0] - (step*cos(angObs));
			obsP[2] = obsP[2] + (step*sin(angObs));
		}
	}
	if(keysDown[2] == 1){	// W
		if(checkCollisionObs(obsP[0] + (step*cos(angObs)),obsP[1],obsP[2] - (step*sin(angObs)))){
			obsP[0] = obsP[0] + (step*cos(angObs));
			obsP[2] = obsP[2] - (step*sin(angObs));
		}
	}
	if(keysDown[3] == 1){	// D
		// Calcular novo angulo
		if(checkCollisionObs(obsP[0] + (step*cos(transAng)),obsP[1],obsP[2] - (step*sin(transAng)))){
			transAng = angObs - PI/2; 
			obsP[0] = obsP[0] + (step*cos(transAng));
			obsP[2] = obsP[2] - (step*sin(transAng));
		}
	}
	if(keysDown[4] == 1){	// J
		angObs = angObs + 0.02;
		rotMan += 0.02;
		angBall = angBall + 0.02;
		rotBall += 0.02;
		if(!fired){
			shotAng += 0.02;
		}
		//keysDown[4] = 0;
	}
	if(keysDown[5] == 1){	// L
		angObs = angObs - 0.02;
		rotMan -= 0.02;
		angBall = angBall - 0.02;
		rotBall -= 0.02;
		//keysDown[5] = 0;
		if(!fired){
			shotAng -= 0.02;
		}
	}
	if(keysDown[6] == 1){
		fired = 1;
		keysDown[6] = 0;
		xmaxPower = 30.1f;
	}
	if(keysDown[7] == 1){	// I
		if(angObsY <= (75*PI)/180){
			angObsY = angObsY + 0.02;
			angBallY = angBallY + 0.02;
			if(!fired){
				shotAngY += 0.02;
				rotBallY += 0.02;
			}
		}

	}
	if(keysDown[8] == 1){	// K
		if(angObsY >= (-75*PI)/180){
			angObsY = angObsY - 0.02;
			angBallY = angBallY - 0.02;
			if(!fired){
				shotAngY -= 0.02;
				rotBallY -= 0.02;
			}
		}
	}

	if(keysDown[9] == 1){	// R
		// Reset Cans
		int i;
		for(i=0; i<NUM_CANS; i++){
			can_display[i] = 1;
			initCanTree();
		}
	}

	rBallTemp = rBall * cos(angBallY);

	if(!fired){
		ballP[0] = obsP[0] + rBallTemp*cos(angBall);
		ballP[1] = obsP[1] + rBall*sin(angBallY);
    	ballP[2] = obsP[2] - rBallTemp*sin(angBall);
    	ballShotP[1] = ballP[1];
    	ballShotP[0] = ballP[0];
    	ballShotP[2] = ballP[2];	
	}

	initPos[0] = obsP[0] + rVisaoObs*cos(angObs);
	initPos[1] = obsP[1] + rVisaoObs*sin(angObsY);
	initPos[2] = obsP[2] - rVisaoObs*sin(angObs);

	glutPostRedisplay(); 
}

void drawWindow(float height, float length){
	glPushMatrix();
		glBegin(GL_QUADS);
			float frame = (height*5)/100;
			//front face
			//left
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(frame, 0.0, 0.0f);
			glVertex3f(frame, height, 0.0f);
			glVertex3f(0.0f, height, 0.0f);

			//bottom
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(length, 0.0, 0.0f);
			glVertex3f(length, frame, 0.0f);
			glVertex3f(0.0f, frame, 0.0f);

			//right
			glVertex3f(length, 0.0f, 0.0f);
			glVertex3f(length + frame, 0.0, 0.0f);
			glVertex3f(length + frame, height, 0.0f);
			glVertex3f(length, height, 0.0f);

			//top
			glVertex3f(0.0f, height-frame, 0.0f);
			glVertex3f(length, height-frame, 0.0f);
			glVertex3f(length, height, 0.0f);
			glVertex3f(0.0f, height, 0.0f);

			//back face
			//left
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, height, 0.0f);
			glVertex3f(frame, height, 0.0f);
			glVertex3f(frame, 0.0, 0.0f);
			

			//bottom
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, frame, 0.0f);
			glVertex3f(length, frame, 0.0f);
			glVertex3f(length, 0.0, 0.0f);
			
			//right
			glVertex3f(length, 0.0f, 0.0f);
			glVertex3f(length, height, 0.0f);
			glVertex3f(length + frame, height, 0.0f);
			glVertex3f(length + frame, 0.0, 0.0f);
			
			//top
			glVertex3f(0.0f, height-frame, 0.0f);
			glVertex3f(0.0f, height-frame, 0.0f);
			glVertex3f(length, height, 0.0f);
			glVertex3f(length, height, 0.0f);
		glEnd();
	glPopMatrix();
}

void updateBallPos(){
	rBallTemp = rBall * cos(angBallY);
	if(ballP[0]>=50.0f || ballP[0]<=0.0f){
		fired = 0;
		ballP[0] = obsP[0] + rBallTemp*cos(angBall);
		ballP[1] = obsP[1] + rBallTemp*sin(angBallY);
    	ballP[2] = obsP[2] - rBallTemp*sin(angBall);
    	shotAng = angObs;
    	ballShotP[1] = ballP[1];
    	ballShotP[0] = ballP[0];
    	ballShotP[2] = ballP[2];
    	t = 0;
	}
	if(ballP[2]>=50.0f || ballP[2]<=0.0f){
		fired = 0;
		ballP[0] = obsP[0] + rBallTemp*cos(angBall);
		ballP[1] = obsP[1] + rBallTemp*sin(angBallY);
    	ballP[2] = obsP[2] - rBallTemp*sin(angBall);
    	shotAng = angObs;
    	ballShotP[1] = ballP[1];
    	ballShotP[0] = ballP[0];
    	ballShotP[2] = ballP[2];
    	t = 0;
	}
	if(ballP[1]>=15.0f || ballP[1]<=0.0f){
		fired = 0;
		ballP[0] = obsP[0] + rBallTemp*cos(angBall);
		ballP[1] = obsP[1] + rBallTemp*sin(angBallY);
    	ballP[2] = obsP[2] - rBallTemp*sin(angBall);
    	shotAng = angObs;
    	ballShotP[1] = ballP[1];
    	ballShotP[0] = ballP[0];
    	ballShotP[2] = ballP[2];
    	t = 0;
	}
	if(fired){
		printf("ballShotP - x %f z %f\n",ballP[0],ballP[2]);
		if(physics){
			float vx = v * cos(shotAngY);
			float vy = v * sin(shotAngY);
			vy = vy*2;

			float tempY = ballShotP[1] + vy*t - (g*t*t)/2; 
			t += stepf;

			ballP[0] = ballP[0] + ((vx/10)*cos(shotAng)); 
			ballP[1] = tempY;
			ballP[2] = ballP[2] - ((vx/10)*sin(shotAng));
		}else {
			ballP[0] = ballP[0] + (0.07*cos(shotAng)); 
			ballP[1] = ballP[1] + (0.07*sin(shotAngY));
			ballP[2] = ballP[2] - (0.07*sin(shotAng));
		}
	}else{
		ballP[0] = obsP[0] + rBallTemp*cos(angBall);
		ballP[1] = 1.7 + rBall*sin(angBallY);
    	ballP[2] = obsP[2] - rBallTemp*sin(angBall);
    	shotAng = angObs;
    	shotAngY = angObsY;
    	ballShotP[1] = ballP[1];
    	ballShotP[0] = ballP[0];
    	ballShotP[2] = ballP[2];
	}
}

void drawGlassDown(float length, float height, float width){
    glColor4f(GLASS);
    glPushMatrix();
        glBegin(GL_QUADS);
            //bottom face
            glNormal3f(0,1,0);
            glVertex3f(0.0f, 0.0f, width);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(length, 0.0f, 0.0f);
            glVertex3f(length, 0.0f, width);
 
            //front face
            glVertex3f(0.0f, height, width);
            glVertex3f(0.0f, 0.0f, width);
            glVertex3f(length, 0.0f, width);
            glVertex3f(length, height, width);
 
            //right face
            glVertex3f(length, 0.0f, width);
            glVertex3f(length, 0.0f, 0.0f);
            glVertex3f(length, height, 0.0f);
            glVertex3f(length, height, width);
 
            //back face
            glVertex3f(length, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, height, 0.0f);
            glVertex3f(length, height, 0.0f);
 
            //left face
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, width);
            glVertex3f(0.0f, height, width);
            glVertex3f(0.0f, height, 0.0f);
 
            //top face
            glVertex3f(0.0f, height, 0.0f);
            glVertex3f(0.0f, height, width);
            glVertex3f(length, height, width);
            glVertex3f(length, height, 0.0f);
        glEnd();
    glPopMatrix();
}

void drawBancos(){
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        drawCubes(0.07, 0.7, 0.07, 13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0, 0.0, 0.33);
        drawCubes(0.07, 0.7, 0.07,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.33, 0.0, 0.0);
        drawCubes(0.07, 0.7, 0.07,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.33, 0.0, 0.33);
        drawCubes(0.07, 0.7, 0.07,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.0, 0.7, 0.0);
        drawCubes(0.4, 0.25, 0.4,13);
    glPopMatrix();
 
    glPushMatrix();
        glTranslatef(0.0, 0.2, 0.0);
        drawCubes(0.04, 0.04, 0.4, 13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.36, 0.2, 0.0);
        drawCubes(0.04, 0.04, 0.4, 13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.4, 0.2, 0.0);
        glRotatef(-90, 0.0, 1.0, 0.0);
        drawCubes(0.04, 0.04, 0.4, 13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(0.4, 0.2, 0.36);
        glRotatef(-90, 0.0, 1.0, 0.0);
        drawCubes(0.04, 0.04, 0.4, 13);
    glPopMatrix();
}
 
void drawGarrafas(float x, int tex_id){
	if(tex_id != -1){
		glEnable(GL_TEXTURE_2D);
     
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        
	    GLUquadricObj *y;
	    y = gluNewQuadric();
	   	gluQuadricTexture(y, GL_TRUE);
	    glBindTexture(GL_TEXTURE_2D,textures[tex_id]);
	    glPushMatrix();
	        glTranslatef(x,3,29.8);
	        glRotatef(-90.0f,0.0f,1.0f,0.0f);
	        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	        gluCylinder(y, 0.1,0.1,0.6,20,20);
	    glPopMatrix();
	    glDisable(GL_TEXTURE_2D);
	    glColor4f(GRAY);
	    glPushMatrix();
	        glTranslatef(x,3.6,29.8);  
	        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	        gluCylinder(y, 0.1,0.05,0.1,20,20);
	    glPopMatrix();
	    glPushMatrix();
	        glTranslatef(x,3.7,29.8);  
	        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	        gluCylinder(y, 0.05,0.035,0.2,20,20);
	    glPopMatrix();
	    glPushMatrix();
	    	glTranslatef(x,3.001,29.8);
			glRotatef(90.0f,1.0f,0.0f,0.0f);
			gluDisk(y,0,0.1,50,50);
		glPopMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	}else{
	    GLUquadricObj *y;
	    y = gluNewQuadric();
	    glPushMatrix();
	        glTranslatef(x,3,29.8);
	        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	        gluCylinder(y, 0.1,0.1,0.6,20,20);
	    glPopMatrix();
	    glPushMatrix();
	        glTranslatef(x,3.6,29.8);  
	        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	        gluCylinder(y, 0.1,0.05,0.1,20,20);
	    glPopMatrix();
	    glPushMatrix();
	        glTranslatef(x,3.7,29.8);  
	        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	        gluCylinder(y, 0.05,0.035,0.2,20,20);
	    glPopMatrix();

	    glPushMatrix();
	    	glTranslatef(x,3.001,29.8);
			glRotatef(90.0f,1.0f,0.0f,0.0f);
			gluDisk(y,0,0.1,50,50);
		glPopMatrix();
	}
}
 
void drawBancoGr(){
    glPushMatrix();
        glTranslatef(32.0, 0.0, 28.7);
        drawCubes(4, 0.7, 1.2, 13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(32.0, 0.0, 29.6);
        drawCubes(4, 1.3, 0.39,13);
    glPopMatrix();
}
 
void drawBar(){
    //candeeiros
    GLUquadricObj *y;
    y = gluNewQuadric();
    glPushMatrix();
        glTranslatef(25.5,1.2,28.7);   
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(y, 0.1,0.05,0.7,20,20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(25.5,1.8,28.7);   
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(y, 0.2,0.2,0.3,20,20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(29.5,1.2,28.7);   
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(y, 0.1,0.05,0.7,20,20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(29.5,1.8,28.7);   
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(y, 0.2,0.2,0.3,20,20);
    glPopMatrix();
 
    //cordas
    glPushMatrix();
        glTranslatef(25.1,3,29.58);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(y, 0.01,0.01,7,20,20);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(29.9,3,29.58);
        glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
        gluCylinder(y, 0.01,0.01,7,20,20);
    glPopMatrix();
 
    //balcao
    //por textura marmore
    glPushMatrix();
        glTranslatef(25, 0, 28.5);
        drawCubes(5, 1.2, 0.4, -1);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(24.6, 0, 28.5);
        drawCubes(0.4, 1.2, 1.48, -1);
    glPopMatrix();
    //tampo do balcao
    glPushMatrix();
        glTranslatef(24.9, 1.2, 28.4);
        drawCubes(5.2, 0.1, 0.7, 13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(24.5, 1.2, 28.4);
        drawCubes(0.6, 0.1, 1.59, 13);
    glPopMatrix();
 
    //bancos
    glPushMatrix();
        glTranslatef(28, 0, 27.7);
        drawBancos();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(26, 0, 27.7);
        drawBancos();
    glPopMatrix();
    glPushMatrix();
        glTranslatef(24, 0, 29.1);
        drawBancos();
    glPopMatrix();
    drawBancoGr();
 
    //latas
    glPushMatrix();

        glTranslatef(26.0, 1.3, 28.7);
        glPushMatrix();
			glTranslatef(0.0,0.36,0.0);
			glRotatef(-90.0f,1.0f,0.0f,0.0f);
			gluDisk(y,0,0.07,50,50);
		glPopMatrix();
        glPushMatrix();
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(y, 0.07,0.1,0.03,20,20);     //inferior
        glPopMatrix();
        glEnable(GL_TEXTURE_2D);
        if(modulate){
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        }
        gluQuadricTexture(y, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glPushMatrix();
            glTranslatef(0.0,0.03,0.0);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(y, 0.1,0.1,0.3,20,20);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        glPushMatrix();
            glTranslatef(0.0,0.33,0.0);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(y, 0.1,0.07,0.03,20,20);    //superior
        glPopMatrix();
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPopMatrix();
 
    glPushMatrix();
        glTranslatef(28.0, 1.3, 28.7);
        glPushMatrix();
			glTranslatef(0.0,0.36,0.0);
			glRotatef(-90.0f,1.0f,0.0f,0.0f);
			gluDisk(y,0,0.07,50,50);
		glPopMatrix();
        glPushMatrix();
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(y, 0.07,0.1,0.03,20,20);     //inferior
        glPopMatrix();
        glEnable(GL_TEXTURE_2D);
        if(modulate){
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        }
        gluQuadricTexture(y, GL_TRUE);
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glPushMatrix();
            glTranslatef(0.0,0.03,0.0);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(y, 0.1,0.1,0.3,20,20);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
        glPushMatrix();
            glTranslatef(0.0,0.33,0.0);
            glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
            gluCylinder(y, 0.1,0.07,0.03,20,20);    //superior
        glPopMatrix();
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glPopMatrix();
   	glDisable(GL_TEXTURE_2D);

    //garrafas
    float i=26.0;
    for(i=26;i<30;i++){
        drawGarrafas(i,i-6);
    }  
}

void drawEixos(){	
	// Eixo X
	glColor4f(RED);
	glBegin(GL_LINES);
		glVertex3i( 0, 0, 0); 
		glVertex3i(10, 0, 0); 
	glEnd();
	// Eixo Y
	glColor4f(GREEN);
	glBegin(GL_LINES);
		glVertex3i(0,  0, 0); 
		glVertex3i(0, 10, 0); 
	glEnd();
	// Eixo Z
	glColor4f(BLUE);
	glBegin(GL_LINES);
		glVertex3i( 0, 0, 0); 
		glVertex3i( 0, 0,10); 
	glEnd();
}	

void drawDoor(){
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textures[18]);
	glBegin(GL_QUADS);
		//Outdoor Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.075,0.0,0.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.075,0.0,7.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.075,7.0,7.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.075,7.0,0.0);
		glDisable(GL_TEXTURE_2D);

		glColor4f(GRAY);
		glVertex3f(0.0,0.0,7.0);
		glVertex3f(0.075,0.0,7.0);
		glVertex3f(0.075,7.0,7.0);
		glVertex3f(0.0,7.0,7.0);

		// Indoor Face
		glEnable(GL_TEXTURE_2D);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.075,0.0,7.0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0.075,0.0,0.0);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(0.075,7.0,0.0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.075,7.0,7.0);
		glDisable(GL_TEXTURE_2D);

		glColor4f(GRAY);
		glVertex3f(0.075,0.0,0.0);
		glVertex3f(0.0,0.0,0.0);
		glVertex3f(0.0,7.0,0.0);
		glVertex3f(0.075,7.0,0.0);
		
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void drawSkybox(float size){
	
	size = 500;

	glEnable(GL_TEXTURE_2D);
	//Left
	glBindTexture(GL_TEXTURE_2D,textures[4]);
	glPushMatrix();

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i(obsP[0]-size,obsP[1]-size,obsP[2]-size);
			glTexCoord2f(1.0f,0.0f); glVertex3i(obsP[0]+size,obsP[1]-size,obsP[2]-size);
			glTexCoord2f(1.0f,1.0f); glVertex3i(obsP[0]+size,obsP[1]+size,obsP[2]-size);
			glTexCoord2f(0.0f,1.0f); glVertex3i(obsP[0]-size,obsP[1]+size,obsP[2]-size);
		glEnd();

	glPopMatrix();

	//Front
	glBindTexture(GL_TEXTURE_2D,textures[5]);
	glPushMatrix();

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i(obsP[0]+size,obsP[1]-size,obsP[2]-size);
			glTexCoord2f(1.0f,0.0f); glVertex3i(obsP[0]+size,obsP[1]-size,obsP[2]+size);
			glTexCoord2f(1.0f,1.0f); glVertex3i(obsP[0]+size,obsP[1]+size,obsP[2]+size);
			glTexCoord2f(0.0f,1.0f); glVertex3i(obsP[0]+size,obsP[1]+size,obsP[2]-size);
		glEnd();

	glPopMatrix();

	//Right
	glBindTexture(GL_TEXTURE_2D,textures[6]);
	glPushMatrix();

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i(obsP[0]+size,obsP[1]-size,obsP[2]+size);
			glTexCoord2f(1.0f,0.0f); glVertex3i(obsP[0]-size,obsP[1]-size,obsP[2]+size);
			glTexCoord2f(1.0f,1.0f); glVertex3i(obsP[0]-size,obsP[1]+size,obsP[2]+size);
			glTexCoord2f(0.0f,1.0f); glVertex3i(obsP[0]+size,obsP[1]+size,obsP[2]+size);
		glEnd();

	glPopMatrix();

	//Back
	glBindTexture(GL_TEXTURE_2D,textures[7]);
	glPushMatrix();

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i(obsP[0]-size,obsP[1]-size,obsP[2]+size);
			glTexCoord2f(1.0f,0.0f); glVertex3i(obsP[0]-size,obsP[1]-size,obsP[2]-size);
			glTexCoord2f(1.0f,1.0f); glVertex3i(obsP[0]-size,obsP[1]+size,obsP[2]-size);
			glTexCoord2f(0.0f,1.0f); glVertex3i(obsP[0]-size,obsP[1]+size,obsP[2]+size);
		glEnd();

	glPopMatrix();

	//Top
	glBindTexture(GL_TEXTURE_2D,textures[8]);
	glPushMatrix();

		glBegin(GL_QUADS);
			glTexCoord2f(0.0f,0.0f); glVertex3i(obsP[0]+size,obsP[1]+size,obsP[2]-size);
			glTexCoord2f(1.0f,0.0f); glVertex3i(obsP[0]+size,obsP[1]+size,obsP[2]+size);
			glTexCoord2f(1.0f,1.0f); glVertex3i(obsP[0]-size,obsP[1]+size,obsP[2]+size);
			glTexCoord2f(0.0f,1.0f); glVertex3i(obsP[0]-size,obsP[1]+size,obsP[2]-size);
		glEnd();

	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
}

void drawFloor(){
	/*glEnable(GL_TEXTURE_2D);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D,textures[0]);
	glBegin(GL_POLYGON);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0,0.0,0.0);
		glTexCoord2f(0.0f, 50.0f); glVertex3f(0.0,0.0,50.0);
		glTexCoord2f(50.0f, 50.0f); glVertex3f(50.0,0.0,50.0);
		glTexCoord2f(50.0f, 0.0f); glVertex3f(50.0,0.0,0.0);
	glEnd();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_TEXTURE_2D);*/


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,textures[16]);
	int i,j;	
	for(i=0; i<5; i++){
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0*i,0.0,0.0);
			glTexCoord2f(0.0f, 10.0f); glVertex3f(10.0*i,0.0,10.0);
			glTexCoord2f(10.0f, 10.0f); glVertex3f(10.0*(i+1),0.0,10.0);
			glTexCoord2f(10.0f, 0.0f); glVertex3f(10.0*(i+1),0.0,0.0);
		glEnd();
	}

	for(i=0; i<2; i++){
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0*i,0.0,0.0);
			glTexCoord2f(0.0f, 10.0f); glVertex3f(10.0*i,0.0,10.0);
			glTexCoord2f(10.0f, 10.0f); glVertex3f(10.0*(i+1),0.0,10.0);
			glTexCoord2f(10.0f, 0.0f); glVertex3f(10.0*(i+1),0.0,0.0);
		glEnd();
	}

	for(i=1; i<3; i++){
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0,0.0,10.0*i);
			glTexCoord2f(0.0f, 10.0f); glVertex3f(0.0,0.0,10.0*(i+1));
			glTexCoord2f(10.0f, 10.0f); glVertex3f(14.0,0.0,10.0*(i+1));
			glTexCoord2f(10.0f, 0.0f); glVertex3f(14.0,0.0,10.0*i);
		glEnd();
	}

	for(i=0; i<5; i++){
		for(j=3;j<5;j++){
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0*i,0.0,10.0*j);
				glTexCoord2f(0.0f, 10.0f); glVertex3f(10.0*i,0.0,10.0*(j+1));
				glTexCoord2f(10.0f, 10.0f); glVertex3f(10.0*(i+1),0.0,10.0*(j+1));
				glTexCoord2f(10.0f, 0.0f); glVertex3f(10.0*(i+1),0.0,10.0*j);
			glEnd();
		}
	}

	for(i=1; i<3; i++){
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(40.0,0.0,10.0*i);
			glTexCoord2f(0.0f, 10.0f); glVertex3f(40.0,0.0,10.0*(i+1));
			glTexCoord2f(10.0f, 10.0f); glVertex3f(50.0,0.0,10.0*(i+1));
			glTexCoord2f(10.0f, 0.0f); glVertex3f(50.0,0.0,10.0*i);
		glEnd();
	}


	glBindTexture(GL_TEXTURE_2D,textures[17]);
	for(i=1; i<3; i++){
		glBegin(GL_POLYGON);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(14.0,0.0,10.0*i);
			glTexCoord2f(0.0f, 5.0f); glVertex3f(14.0,0.0,10.0*(i+1));
			glTexCoord2f(5.0f, 5.0f); glVertex3f(20.0,0.0,10.0*(i+1));
			glTexCoord2f(5.0f, 0.0f); glVertex3f(20.0,0.0,10.0*i);
		glEnd();
	}

	glBindTexture(GL_TEXTURE_2D,textures[19]);
	for(i=2; i<4; i++){
		for(j=1;j<3;j++){
			glBegin(GL_POLYGON);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(10.0*i,0.0,10.0*j);
				glTexCoord2f(0.0f, 10.0f); glVertex3f(10.0*i,0.0,10.0*(j+1));
				glTexCoord2f(10.0f, 10.0f); glVertex3f(10.0*(i+1),0.0,10.0*(j+1));
				glTexCoord2f(10.0f, 0.0f); glVertex3f(10.0*(i+1),0.0,10.0*j);
			glEnd();
		}
	}



	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_TEXTURE_2D);
}

void drawRect(int size_x, int size_y, float slice_size){
	int n_x = size_x / slice_size, n_y = size_y / slice_size;
	int i, j;
	for(i=0; i<n_x; i++){
		for(j=0; j<n_y; j++){
			if(j%2 == 0){
				glColor4f(RED);
			}else{
				glColor4f(BLUE);
			}
			glBegin(GL_POLYGON);
				glNormal3f(0,0,1);
				glVertex3f(slice_size*i,slice_size*j,0.0f);
				glVertex3f(slice_size*(i+1),slice_size*j,0.0f);
				glVertex3f(slice_size*(i+1),slice_size*(j+1),0.0f);
				glVertex3f(slice_size*i,slice_size*(j+1),0.0f);
			glEnd();
		}
	}
}

void drawCubes(float length, float height, float width, int tex_id){
	if(tex_id != -1){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textures[tex_id]);
		if(modulate){
			glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		}
		glPushMatrix();
			glBegin(GL_QUADS);
				//bottom face
				glNormal3f(0,1,0);
				glTexCoord2f(0.0f,0.0f); glVertex3f(0.0f, 0.0f, width);
				glTexCoord2f(1.0f,0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f,1.0f); glVertex3f(length, 0.0f, 0.0f);
				glTexCoord2f(0.0f,1.0f); glVertex3f(length, 0.0f, width);

				//front face
				glTexCoord2f(0.0f,0.0f); glVertex3f(0.0f, height, width);
				glTexCoord2f(1.0f,0.0f); glVertex3f(0.0f, 0.0f, width);
				glTexCoord2f(1.0f,1.0f); glVertex3f(length, 0.0f, width);
				glTexCoord2f(0.0f,1.0f); glVertex3f(length, height, width);

				//right face
				glTexCoord2f(0.0f,0.0f); glVertex3f(length, 0.0f, width);
				glTexCoord2f(1.0f,0.0f); glVertex3f(length, 0.0f, 0.0f);
				glTexCoord2f(1.0f,1.0f); glVertex3f(length, height, 0.0f);
				glTexCoord2f(0.0f,1.0f); glVertex3f(length, height, width);

				//back face
				glTexCoord2f(0.0f,0.0f); glVertex3f(length, 0.0f, 0.0f);
				glTexCoord2f(1.0f,0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f,1.0f); glVertex3f(0.0f, height, 0.0f);
				glTexCoord2f(0.0f,1.0f); glVertex3f(length, height, 0.0f);

				//left face
				glTexCoord2f(0.0f,0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f,0.0f); glVertex3f(0.0f, 0.0f, width);
				glTexCoord2f(1.0f,1.0f); glVertex3f(0.0f, height, width);
				glTexCoord2f(0.0f,1.0f); glVertex3f(0.0f, height, 0.0f);

				//top face
				glTexCoord2f(0.0f,0.0f); glVertex3f(0.0f, height, 0.0f);
				glTexCoord2f(1.0f,0.0f); glVertex3f(0.0f, height, width);
				glTexCoord2f(1.0f,1.0f); glVertex3f(length, height, width);
				glTexCoord2f(0.0f,1.0f); glVertex3f(length, height, 0.0f);
			glEnd();
		glPopMatrix();
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glDisable(GL_TEXTURE_2D);
	}else{		
		glPushMatrix();
			glBegin(GL_QUADS);
				//bottom face
				glNormal3f(0,1,0);
				glVertex3f(0.0f, 0.0f, width);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(length, 0.0f, 0.0f);
				glVertex3f(length, 0.0f, width);

				//front face
				glVertex3f(0.0f, height, width);
				glVertex3f(0.0f, 0.0f, width);
				glVertex3f(length, 0.0f, width);
				glVertex3f(length, height, width);

				//right face
				glVertex3f(length, 0.0f, width);
				glVertex3f(length, 0.0f, 0.0f);
				glVertex3f(length, height, 0.0f);
				glVertex3f(length, height, width);

				//back face
				glVertex3f(length, 0.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, height, 0.0f);
				glVertex3f(length, height, 0.0f);

				//left face
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, 0.0f, width);
				glVertex3f(0.0f, height, width);
				glVertex3f(0.0f, height, 0.0f);

				//top face
				glVertex3f(0.0f, height, 0.0f);
				glVertex3f(0.0f, height, width);
				glVertex3f(length, height, width);
				glVertex3f(length, height, 0.0f);
			glEnd();
		glPopMatrix();
	}
}

void drawCubeWall(float length, float height){
	glPushMatrix();
		glBegin(GL_POLYGON);
			//front face
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(length, 0.0f, 0.0f);
			glVertex3f(length, height, 0.0f);
			glVertex3f(0.0f, height, 0.0f);
		glEnd();
	glPopMatrix();
}

void drawHouseWall(float length, float height, int tex_id){
	if(tex_id != -1){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,textures[tex_id]);
		glPushMatrix();
			glBegin(GL_QUADS);
				//front face
				glTexCoord2f(0.0f,0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f,0.0f); glVertex3f(length, 0.0f, 0.0f);
				glTexCoord2f(1.0f,1.0f); glVertex3f(length, height, 0.0f);
				glTexCoord2f(0.0f,1.0f); glVertex3f(0.0f, height, 0.0f);
				//back face
				glTexCoord2f(0.0f,0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
				glTexCoord2f(1.0f,0.0f); glVertex3f(0.0f, height, 0.0f);
				glTexCoord2f(1.0f,1.0f); glVertex3f(length, height, 0.0f);
				glTexCoord2f(0.0f,1.0f); glVertex3f(length, 0.0f, 0.0f);
			glEnd();
		glPopMatrix();
		glDisable(GL_TEXTURE_2D);
	}else{
		glPushMatrix();
			glBegin(GL_QUADS);
				//front face
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(length, 0.0f, 0.0f);
				glVertex3f(length, height, 0.0f);
				glVertex3f(0.0f, height, 0.0f);
				//back face
				glVertex3f(0.0f, 0.0f, 0.0f);
				glVertex3f(0.0f, height, 0.0f);
				glVertex3f(length, height, 0.0f);
				glVertex3f(length, 0.0f, 0.0f);
			glEnd();
		glPopMatrix();
	}
}

void drawSmallWall(){
	float xCoord = 0.0, yCoord = 0.0, zCoord = 0.0;
	int i = 0, j = 0;
	//PAREDE Z = 0
	for(i = 0; i < 6; i++){
		for(j = 0; j < 25; j++){
			glPushMatrix();
				glTranslatef(xCoord, yCoord,0.0);
				drawCubeWall(2, 1);
			glPopMatrix();
			xCoord += 2.0;
		}
		yCoord += 1.0;
		xCoord = 0.0;
	}
	//PAREDE X = 50
	yCoord = 0.0;
	i = j = 0;
	for(i = 0; i < 6; i++){
		for(j = 0; j < 25; j++){
			glPushMatrix();
				glTranslatef(50.0, yCoord,zCoord);
				glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
				drawCubeWall(2, 1);
			glPopMatrix();
			zCoord += 2.0;
		}
		yCoord += 1.0;
		zCoord = 0.0;
	}
	//PAREDE Z = 50
	yCoord = xCoord = 0.0;
	i = j = 0;
	for(i = 0; i < 6; i++){
		for(j = 0; j < 25; j++){
			glPushMatrix();
				glTranslatef(xCoord+2, yCoord,50.0);
				glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
				drawCubeWall(2, 1);
			glPopMatrix();
			xCoord += 2.0;
		}
		yCoord += 1.0;
		xCoord = 0.0;
	}
	//PAREDE X = 0
	yCoord = zCoord = 0.0;
	i = j = 0;
	for(i = 0; i < 6; i++){
		for(j = 0; j < 25; j++){
			glPushMatrix();
				glTranslatef(0.0, yCoord,zCoord+2);
				glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
				drawCubeWall(2, 1);
			glPopMatrix();
			zCoord += 2.0;
		}
		yCoord += 1.0;
		zCoord = 0.0;
	}
}

void drawHouse(){
	float xCoord = 14.0, yCoord = 0.0, zCoord = 10.0;
	int i = 0, j = 0;
	//PAREDE Z = 10
	for(i = 0; i < 10; i++){
		for(j = 0; j < 13; j++){
			glPushMatrix();
				glTranslatef(xCoord, yCoord,10.0);
				drawHouseWall(2, 1, -1);
			glPopMatrix();
			xCoord += 2.0;
		}
		yCoord += 1.0;
		xCoord = 14.0;
	}
	
	//PAREDE X = 40
	yCoord = 0.0;
	i = j = 0;
	for(i = 0; i < 10; i++){
		for(j = 0; j < 13; j++){
			if(j==2){
				glPushMatrix();
					glTranslatef(40.0, 0.0,zCoord);
					glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
					drawWindow(10, 4);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(40.0, 0.0,zCoord+4);
					glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
					drawWindow(10, 4);
				glPopMatrix();
				glPushMatrix();
					glTranslatef(40.0, 0.0,zCoord+8);
					glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
					drawWindow(10, 4);
				glPopMatrix();
				zCoord += 12;
				j=10;
			}else{
				glPushMatrix();
					glTranslatef(40.0, yCoord,zCoord);
					glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
					drawHouseWall(2, 1, -1);
				glPopMatrix();
				zCoord += 2.0;
			}
		}
		yCoord += 1.0;
		zCoord = 10.0;
	}
	//PAREDE Z = 30
	yCoord = 0.0;
	xCoord = 14.0;
	i = j = 0;
	for(i = 0; i < 10; i++){
		for(j = 0; j < 13; j++){
			glPushMatrix();
				glTranslatef(xCoord+2, yCoord,30.0);
				glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
				drawHouseWall(2, 1, -1);
			glPopMatrix();
			xCoord += 2.0;
		}
		yCoord += 1.0;
		xCoord = 14.0;
	}
	//PAREDE X = 20
	yCoord = 0.0;
	zCoord = 10.0;
	i = j = 0;
	for(i = 0; i < 10; i++){
		for(j = 0; j < 10; j++){
			if(j==3){
				j += 3;
				zCoord += 7.0;
			}else{
				glPushMatrix();
					glTranslatef(20.0, yCoord,zCoord+2);
					glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
					drawHouseWall(2, 1, -1);
				glPopMatrix();
				zCoord += 2.0;
			}
		}
		yCoord += 1.0;
		zCoord = 10.0;
	}

	glPushMatrix();
		glColor4f(RED);
		glTranslatef(20.0, 0.0, 30.0);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		drawHouseWall(1, 10, -1);
	glPopMatrix();

	drawFloor();

	glDisable(GL_LIGHTING);
	glColor4f(GRAY);
	glPushMatrix();
		glTranslatef(14.0f,10.0f,10.0f);
		glRotatef(90.0f,1.0f,0.0f,0.0f);
		glNormal3f(0.0f,-1.0f,0.0f);
		drawCubeWall(30,20);
	glPopMatrix();
	glColor4f(GRAY);
	glEnable(GL_LIGHTING);
}

void drawBilhar(){

	glPushMatrix();
        glTranslatef(29.0, 0.0, 11.0);
        drawCubes(0.3, 0.7, 0.3, 13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(29.0, 0.0, 12.4);
        drawCubes(0.3, 0.7, 0.3,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(33.4, 0.0, 12.4);
        drawCubes(0.3, 0.7, 0.3,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(33.4, 0.0, 11.0);
        drawCubes(0.3, 0.7, 0.3,13);
    glPopMatrix();

    glPushMatrix();
    	glTranslatef(28.85, 0.7, 10.85);
        drawCubes(5.0, 0.3, 0.2,13);
    glPopMatrix();

    glPushMatrix();
    	glTranslatef(28.85, 0.7, 12.7);
        drawCubes(5.0, 0.3, 0.2,13);
    glPopMatrix();

    glPushMatrix();
    	glTranslatef(29, 0.7, 10.85);
    	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        drawCubes(2.0, 0.3, 0.2,13);
    glPopMatrix();

    glPushMatrix();
    	glTranslatef(33.85, 0.7, 10.85);
    	glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
        drawCubes(2.0, 0.3, 0.2,13);
    glPopMatrix();

	glPushMatrix();
        glTranslatef(28.85, 0.7, 10.9);
        drawCubes(4.9, 0.1, 1.9,24);
    glPopMatrix(); 
}	

void drawJogos(){
	glPushMatrix();
        glTranslatef(22.0, 0.0, 11.0);
        drawCubes(0.3, 0.7, 0.3, 13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(22.0, 0.0, 12.7);
        drawCubes(0.3, 0.7, 0.3,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(25.7, 0.0, 12.7);
        drawCubes(0.3, 0.7, 0.3,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(25.7, 0.0, 11.0);
        drawCubes(0.3, 0.7, 0.3,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(22.0, 0.7, 11.0);
        drawCubes(4.0, 0.5, 2.0,13);
    glPopMatrix();
 	
    drawBilhar();


    //bilhar
    /*glPushMatrix();
        glTranslatef(29.0, 0.0, 11.0);
        drawCubes(0.6, 0.7, 0.6, 13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(29.0, 0.0, 12.4);
        drawCubes(0.6, 0.7, 0.6,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(33.4, 0.0, 12.4);
        drawCubes(0.6, 0.7, 0.6,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(33.4, 0.0, 11.0);
        drawCubes(0.6, 0.7, 0.6,13);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(29.0, 0.7, 11.0);
        drawCubes(5.0, 0.5, 2.0,13);
    glPopMatrix();*/
}

void drawBall(){
	glEnable(GL_TEXTURE_2D);
	GLUquadricObj *sphere=NULL;
	sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);

    glPushMatrix();
    	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    	glBindTexture(GL_TEXTURE_2D, textures[1]);
		gluSphere(sphere, 0.1, 20, 40);
    glPopMatrix();
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glDisable(GL_TEXTURE_2D);
}

void drawSodaCan(float height, float rad){
	GLUquadricObj *y;
	y = gluNewQuadric();

	glPushMatrix();
		glTranslatef(0.0,0.15+height,0.0);
		glRotatef(-90.0f,1.0f,0.0f,0.0f);
		gluDisk(y,0,0.25,50,50);
	glPopMatrix();

	glPushMatrix();
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(y, 0.25,rad,0.15,20,20);	 //inferior
	glPopMatrix();
	glEnable(GL_TEXTURE_2D);
	if(modulate){
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
	gluQuadricTexture(y, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glPushMatrix();
		glTranslatef(0.0,0.15,0.0);	
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(y, rad,rad,height,20,20);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glPushMatrix();
		glTranslatef(0.0,0.15+height,0.0);
		glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
		gluCylinder(y, rad,0.25,0.15,20,20);	//superior
	glPopMatrix();
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
}

void drawMan(float size){
	glPushMatrix();
		glTranslatef(-size/2,0,-size*0.625);
		drawCubes(size,size*2,size*1.25,-1);
	glPopMatrix();
}

void drawCans(){
	//desenha latas piramide
	float zCoord = 20.0;
	int i, count = 0;;
	for(i = 0;i<4;i++){
		if(can_display[count] == 1){
			glColor4f(GRAY);
			glPushMatrix();
				glTranslatef(36.5, 1.0, zCoord);
				drawSodaCan(0.8, 0.3);
			glPopMatrix();
		}
		count++;
		zCoord = zCoord + 0.6;
	}

	zCoord = 20.3;
	for(i = 0;i<3;i++){
		if(can_display[count] == 1){
			glColor4f(GRAY);
			glPushMatrix();
				glTranslatef(36.5, 2.1, zCoord);
				drawSodaCan(0.8, 0.3);
			glPopMatrix();
		}
		count++;
		zCoord = zCoord + 0.6;
	}

	zCoord = 20.6;
	for(i = 0;i<2;i++){
		if(can_display[count] == 1){
			glColor4f(GRAY);
			glPushMatrix();
				glTranslatef(36.5, 3.2, zCoord);
				drawSodaCan(0.8, 0.3);
			glPopMatrix();
		}
		count++;
		zCoord = zCoord + 0.6;
	}


	zCoord = 20.9;
	if(can_display[count] == 1){
		glColor4f(GRAY);
		glPushMatrix();
			glTranslatef(36.5, 4.3, zCoord);
			drawSodaCan(0.8, 0.3);
		glPopMatrix();
	}
}

// Done
void checkColisionBall(){
	// Colisão com Latas (Lata a Lata)
	if(ballP[0] + 0.1 >= 36.2f && ballP[0] - 0.1 <= 36.8f){
		// Check YY
		if(ballP[1] + 0.1 >= 1.0 && ballP[1] - 0.1 < 2.1){	
			// Base
			if(can_display[0]){
				if(ballP[2] + 0.1 >= 19.7 && ballP[2] - 0.1 < 20.3){
					can_hit = 1;
					can_display[0] = 0;
					fired = 0;
					initParticulas(0,35.9,37.1,0.8,2.1,19.4,20.6);
					is_exploding[0] = 1;
				}
			}
			if(can_display[1]){
				if(ballP[2] + 0.1 >= 20.3 && ballP[2] - 0.1 < 20.9){
					can_hit = 1;
					can_display[1] = 0;
					fired = 0;
					initParticulas(1,35.9,37.1,0.8,2.1,20.0,21.2);
					is_exploding[1] = 1;
				}
			}
			if(can_display[2]){
				if(ballP[2] + 0.1 >= 20.9 && ballP[2] - 0.1 < 21.5){
					can_hit = 1;
					can_display[2] = 0;
					fired = 0;
					initParticulas(2,35.9,37.1,0.8,2.1,20.6,21.8);
					is_exploding[2] = 1;
				}
			}
			if(can_display[3]){	
				if(ballP[2] + 0.1 >= 21.5 && ballP[2] - 0.1 < 22.1){
					can_hit = 1;
					can_display[3] = 0;
					fired = 0;
					initParticulas(3,35.9,37.1,0.8,2.1,21.2,22.4);
					is_exploding[3] = 1;
				}
			}
		}
		if(ballP[1] + 0.1 >= 2.1 && ballP[1] - 0.1 < 3.2){
			// P1
			if(can_display[4]){
				if(ballP[2] + 0.1 >= 20.0 && ballP[2] - 0.1 < 20.6){
					can_hit = 1;
					can_display[4] = 0;
					fired = 0;
					initParticulas(4,35.9,37.1,1.9,3.2,19.7,20.9);
					is_exploding[4] = 1;
				}
			}
			if(can_display[5]){
				if(ballP[2] + 0.1 >= 20.6 && ballP[2] - 0.1 < 21.2){
					can_hit = 1;
					can_display[5] = 0;
					fired = 0;
					initParticulas(5,35.9,37.1,1.9,3.2,20.3,21.5);
					is_exploding[5] = 1;
				}
			}
			if(can_display[6]){
				if(ballP[2] + 0.1 >= 21.2 && ballP[2] - 0.1 < 21.8){
					can_hit = 1;
					can_display[6] = 0;
					fired = 0;
					initParticulas(6,35.9,37.1,1.9,3.2,20.9,22.1);
					is_exploding[6] = 1;
				}
			}
		}
		if(ballP[1] + 0.1 >= 3.2 && ballP[1] - 0.1 < 4.3){
			// P2
			if(can_display[7]){
				if(ballP[2] + 0.1 >= 20.3 && ballP[2] - 0.1 < 20.9){
					can_hit = 1;
					can_display[7] = 0;
					fired = 0;
					initParticulas(7,35.9,37.1,3.0,4.3,20.0,21.2);
					is_exploding[7] = 1;
				}
			}
			if(can_display[8]){
				if(ballP[2] + 0.1 >= 20.9 && ballP[2] - 0.1 < 21.5){
					can_hit = 1;
					can_display[8] = 0;
					fired = 0;
					initParticulas(8,35.9,37.1,3.0,4.3,20.6,21.8);
					is_exploding[8] = 1;
				}
			}
		}
		if(ballP[1] + 0.1 >= 4.3 && ballP[1] - 0.1 < 5.4){
			// P3
			if(can_display[9]){
				if(ballP[2] + 0.1 >= 20.6 && ballP[2] - 0.1 < 21.2){
					can_hit = 1;
					can_display[9] = 0;
					fired = 0;
					initParticulas(9,35.9,37.1,4.1,5.4,20.3,21.5);
					is_exploding[9] = 1;
				}
			}
		}
	}

	// Colisão House
	if(ballP[0] + 0.1 >= 20 && ballP[0] - 0.1 <= 40){
		if(ballP[1] + 0.1 >= 0.0f && ballP[1] - 0.1 <= 10){
			if(ballP[2] + 0.1 >= 9.8 && ballP[2] - 0.1 <= 10.2){
				fired = 0;
				ballP[0] = obsP[0] + rBallTemp*cos(angBall);
				ballP[1] = obsP[1] + rBallTemp*sin(angBallY);
		    	ballP[2] = obsP[2] - rBallTemp*sin(angBall);
		    	shotAng = angObs;
		    	ballShotP[1] = ballP[1];
		    	ballShotP[0] = ballP[0];
		    	ballShotP[2] = ballP[2];
		    	t = 0;
			}
			if(ballP[2] + 0.1 >= 29.8 && ballP[2] - 0.1 <= 30.2){
				fired = 0;
				ballP[0] = obsP[0] + rBallTemp*cos(angBall);
				ballP[1] = obsP[1] + rBallTemp*sin(angBallY);
		    	ballP[2] = obsP[2] - rBallTemp*sin(angBall);
		    	shotAng = angObs;
		    	ballShotP[1] = ballP[1];
		    	ballShotP[0] = ballP[0];
		    	ballShotP[2] = ballP[2];
		    	t = 0;
			}
		}
	}

	if((ballP[2] + 0.1 >= 10 && ballP[2] - 0.1 <= 16) || (ballP[2] + 0.1 >= 23 && ballP[2] - 0.1 <= 30)){
		if(ballP[1] + 0.1 >= 0.0f && ballP[1] - 0.1 <= 10){
			if(ballP[0] + 0.1 >= 19.8 && ballP[0] - 0.1 <= 20.2){
				fired = 0;
				ballP[0] = obsP[0] + rBallTemp*cos(angBall);
				ballP[1] = obsP[1] + rBallTemp*sin(angBallY);
		    	ballP[2] = obsP[2] - rBallTemp*sin(angBall);
		    	shotAng = angObs;
		    	ballShotP[1] = ballP[1];
		    	ballShotP[0] = ballP[0];
		    	ballShotP[2] = ballP[2];
		    	t = 0;
			}
			if(ballP[0] + 0.1 >= 39.8 && ballP[0] - 0.1 <= 40.2){
				if(ballP[2] + 0.1 <= 14.6 || (ballP[2] + 0.1 <= 18.55 && ballP[2] - 0.1 >= 17.85) || (ballP[2] + 0.1 <= 22.44 && ballP[2] - 0.1 >= 21.94) || ballP[2] - 0.1 >= 25.89){
					fired = 0;
					ballP[0] = obsP[0] + rBallTemp*cos(angBall);
					ballP[1] = obsP[1] + rBallTemp*sin(angBallY);
			    	ballP[2] = obsP[2] - rBallTemp*sin(angBall);
			    	shotAng = angObs;
			    	ballShotP[1] = ballP[1];
			    	ballShotP[0] = ballP[0];
			    	ballShotP[2] = ballP[2];
			    	t = 0;
				}
			}
		}
	}

	// Door Colision
	if(ballP[2] + 0.1 >= doorPos[0][2] && ballP[2] -0.1 <= doorPos[0][2]+7){
		if(ballP[0] + 0.1 >= doorPos[0][0]-0.075 && ballP[0] -0.1 <= doorPos[0][0]+0.075){
			fired = 0;
			ballP[0] = obsP[0] + rBallTemp*cos(angBall);
			ballP[1] = obsP[1] + rBallTemp*sin(angBallY);
	    	ballP[2] = obsP[2] - rBallTemp*sin(angBall);
	    	shotAng = angObs;
	    	ballShotP[1] = ballP[1];
	    	ballShotP[0] = ballP[0];
	    	ballShotP[2] = ballP[2];
	    	t = 0;
		}
	}

	//Colision Bar
}

// Done
void init_spec_particulas(int id){
	if(id == 0){
		initParticulas(0,35.9,37.1,0.8,2.1,19.4,20.6);
		is_exploding[0] = 1;
	}else if(id == 1){
		initParticulas(1,35.9,37.1,0.8,2.1,20.0,21.2);
		is_exploding[1] = 1;
	}else if(id == 2){
		initParticulas(2,35.9,37.1,0.8,2.1,20.6,21.8);
		is_exploding[2] = 1;
	}else if(id == 3){
		initParticulas(3,35.9,37.1,0.8,2.1,21.2,22.4);
		is_exploding[3] = 1;
	}else if(id == 4){
		initParticulas(4,35.9,37.1,1.9,3.2,19.7,20.9);
		is_exploding[4] = 1;
	}else if(id == 5){
		initParticulas(5,35.9,37.1,1.9,3.2,20.3,21.5);
		is_exploding[5] = 1;
	}else if(id == 6){
		initParticulas(6,35.9,37.1,1.9,3.2,20.9,22.1);
		is_exploding[6] = 1;
	}else if(id == 7){
		initParticulas(7,35.9,37.1,3.0,4.3,20.0,21.2);
		is_exploding[7] = 1;
	}else if(id == 8){
		initParticulas(8,35.9,37.1,3.0,4.3,20.6,21.8);
		is_exploding[8] = 1;
	}else if(id == 9){
		initParticulas(9,35.9,37.1,4.1,5.4,20.3,21.5);
		is_exploding[9] = 1;
	}
}

int checkCollisionObs(float x, float y, float z){
	if(x + 0.1  >= 20 && x - 0.1  <= 40){
		if(y + 0.1  >= 0.0f && y - 0.1  <= 10){
			if(z + 0.1  >= 9.8 && z - 0.1  <= 10.2){
				return 0;
			}
			if(z + 0.1  >= 29.8 && z -0.1  <= 30.2){
				return 0;
			}
		}
	}

	if((z + 0.1 >= 10 && z - 0.1  <= 16) || (z + 0.1  >= 23 && z - 0.1 <= 30)){
		if(y + 0.1 >= 0.0f && y - 0.1 <= 10){
			if(x >= 19.8 && x <= 20.2){
				return 0;
			}
			if(x >= 39.8 && x <= 40.2){
				if(z + 0.1 <= 14.6 || (z + 0.1 <= 18.55 && z - 0.1 >= 17.85) || (z + 0.1 <= 22.44 && z - 0.1 >= 21.94) || z - 0.1 >= 25.89){
					return 0;
				}
			}
		}
	}

	if(x >= 35.0 && x <= 38 && z >= 19 && z <= 23){
		return 0;
	}

	if(z + 0.1 >= doorPos[0][2] && z - 0.1 <= doorPos[0][2]+7){
		if(x + 0.1 >= doorPos[0][0]-0.075 && x - 0.1 <= doorPos[0][0]+0.075){
			return 0;
		}
	}


	// Balcao
	if(x + 0.1 >= 24.5 && x - 0.1 <= 30.3){
		if(z + 0.1 >= 28.3 && z - 0.1 <= 29.2){
			return 0;
		}
	}

	// Balcao
	if(x + 0.1 >= 24.5 && x - 0.1 <= 25.5){
		if(z + 0.1 >= 29.2 && z - 0.1 <= 29.9){
			return 0;
		}	
	}

	if(x + 0.1 >= 32 && x - 0.1 <= 36){
		if(z + 0.1 >= 28.7 && z - 0.1 <= 30){
			return 0;
		}
	}


	return 1;
}

void recurseTree(node nd){
	if(nd->is_base){
		return;
	}

	if(nd->BottomLeft != NULL){
		recurseTree(nd->BottomLeft);
	}
	if(nd->BottomRight != NULL){
		recurseTree(nd->BottomRight);
	}

	if(can_display[nd->BottomLeft->id] == 0 && can_display[nd->BottomRight->id] == 0){
		can_display[nd->id] = 0;
		init_spec_particulas(nd->id);
	}
}

void drawGlass(float length, float height){

	glColor4f(GLASS);
	glBegin(GL_QUADS);
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,0.0f,length);
		glVertex3f(0.0f,height,length);
		glVertex3f(0.0f,height,0.0f);
		
		glVertex3f(0.0f,0.0f,0.0f);
		glVertex3f(0.0f,height,0.0f);
		glVertex3f(0.0f,height,length);
		glVertex3f(0.0f,0.0f,length);
	glEnd();
}

void drawScene(){
    // Verificar
    if (frenteVisivel)
	    glCullFace(GL_BACK);  //glFrontFace(GL_CW);
	else
	    glCullFace(GL_FRONT);  //glFrontFace(GL_CCW);

	// Faz update dos diferentes objetos
	updateBallPos();

	int i;
	for(i=0; i<NUM_CANS; i++){
		if(is_exploding[i] == 1){
			glDisable(GL_LIGHTING);
			showParticulas(i);
			glEnable(GL_LIGHTING);
			counters[i]++;
		}
		if(counters[i] >= 200){
			is_exploding[i] = 0;
			counters[i] = 0;
		}	
	}


	// Start Drawing 	
	glColor4f(GRAY);		
	drawSmallWall();		// Muros Exteriores

	drawHouse();			// Corpo da Casa

	for(i=0; i<NUM_DOORS; i++){
		glColor4f(GRAY);
		glPushMatrix();
			glTranslatef(doorPos[i][0],doorPos[i][1],doorPos[i][2]);
			drawDoor();
		glPopMatrix();
	}


	glColor4f(GRAY);
	glPushMatrix();
		glTranslatef(27.0,9.3,25.0);
		drawCubes(0.5, 0.7, 0.5,-1);		// Objeto Lampada		
	glPopMatrix();

	// Mesa
	glPushMatrix();
		glTranslatef(35.0, 0.0, 19.0);
		drawCubes(0.5, 0.7, 0.5, 13);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(35.0, 0.0, 22.5);
		drawCubes(0.5, 0.7, 0.5,13);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(37.5, 0.0, 22.5);
		drawCubes(0.5, 0.7, 0.5,13);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(37.5, 0.0, 19.0);
		drawCubes(0.5, 0.7, 0.5,13);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(35.0, 0.7, 19.0);
		drawCubes(3.0, 0.3, 4.0,13);
	glPopMatrix();	

	drawCans();

	// Quadro 1
	glPushMatrix();
		glTranslatef(35.0,2.5,10.0);
		drawQuadro(1.5,3,0.1,25);
	glPopMatrix();

	// Quadro2
	glPushMatrix();
		glTranslatef(23.0,2.5,10.0);
		drawQuadro(1.5,3,0.1,26);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(28.0,3.5,29.8);
		glRotatef(180.0f,0.0f,1.0f,0.0f);
		drawQuadro(1.5,3,0.1,27);
	glPopMatrix();

	if(fired){
		// Verificar se bola colidiu com latas
		checkColisionBall();
		if(can_hit){
			node temp = can_tree;
			recurseTree(temp);
			can_hit = 0;
		}
	}


	// Ball
	glPushMatrix();
	    glTranslatef(ballP[0],ballP[1],ballP[2]);
        glRotatef(rotBall*(180/PI),0.0f,1.0f,0.0f);
		drawBall();
	glPopMatrix();


	drawJogos();
	drawBar();

	// Human Figure
	if(proj == 1){
		glDisable(GL_LIGHTING);
		glColor4f(BLUE);
		glPushMatrix();
			glTranslatef(obsP[0],obsP[1],obsP[2]);
			glRotatef(rotMan*(180/PI),0.0f,1.0f,0.0f);
			drawMan(1);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}

	glDisable(GL_LIGHTING);
	drawSkybox(100.0f);

	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
		glTranslatef(40.0,0.5,14.5);
		drawGlass(4-(10*0.05),10-(10*0.1));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(40.0,0.5,18.5);
		drawGlass(4-(10*0.05),10-(10*0.1));
	glPopMatrix();

	glPushMatrix();
		glTranslatef(40.0,0.5,22.5);
		drawGlass(4-(10*0.05),10-(10*0.1));
	glPopMatrix();

	glPushMatrix();
        glTranslatef(25.0,3,29.5);
        drawGlassDown(5.0, 0.1, 0.49);
    glPopMatrix();
 
	glBlendFunc (GL_ONE, GL_ZERO);
	glEnable(GL_LIGHTING);


	//DrawParedes
	glutPostRedisplay(); 
}

void drawPowerBar(){
	if(keysDown[6] == 2){
		if(power_dir){
			xmaxPower += power_step;
		}else{
			xmaxPower -= power_step;
		}

		if(xmaxPower >= 46.0f || xmaxPower <= 30.0f){
			power_dir = !power_dir;
		}
	}else if(keysDown[6] == 1){
		v = (xmaxPower - xminPower)/3.33f;			
	}


	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
		glColor4f(RED);
		glVertex3f(xminPower,1.0,20.0);
		glVertex3f(xminPower,1.0,25.0);
		glVertex3f(xmaxPower,1.0,25.0);
		glVertex3f(xmaxPower,1.0,20.0);
	glEnd();
	glEnable(GL_LIGHTING);
}

void display(void){
  	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	proj = 1;
	glViewport (hScreen/30, hScreen/30, wScreen/5, hScreen/5);				//define o tamanho da viewport (xcantoesqinf,y=, comprimento, altura)
  	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (-10,10, -5,5, -10,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	gluLookAt( obsP[0], 7, obsP[2], obsP[0] ,obsP[1],obsP[2], 0, 0, -1);

	drawScene(); 

	proj = 0;
	glViewport (0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100.0, wScreen/hScreen, 0.1, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], initPos[0],initPos[1],initPos[2], 0, 1, 0);

	drawEixos(); 
	drawScene(); 	

	proj = 1;
	glViewport (hScreen/1.001, hScreen/40, wScreen/3, hScreen/10);				//define o tamanho da viewport (xcantoesqinf,y=, comprimento, altura)
  	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho (-10,10, -5,5, -10,10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();	
	gluLookAt( 35.0, 5,25.0, 35.0,0,25.0, 0, 0, -1);

	drawPowerBar(); 


	keysHandler();

	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
	
	
	switch (key) {
	case 'f':
	case 'F':
		physics = !physics;
		glutPostRedisplay();
		break;
	case 'm':
	case 'M':
		modulate = !modulate;
		glutPostRedisplay();
		break;
	case 'A':
	case 'a':
		// Andar para a Esquerda
		keysDown[0] = 1;
		break;

	case 'S':
	case 's':
		// Andar para Tras
		keysDown[1] = 1;
		break;

	case 'w':
	case 'W':
		// Andar em Frente
		keysDown[2] = 1;
		break;

	case 'd':
	case 'D':
		// Andar para a Direita
		keysDown[3] = 1;
		break;

	case 'j':
	case 'J':
		// Andar para a Direita
		keysDown[4] = 1;
		break;

	case 'l':
	case 'L':
		// Andar para a Direita
		keysDown[5] = 1;
		break;

	case 'p':
	case 'P':
		// Lancar
		keysDown[6] = 2;
		break;

	case 'i':
	case 'I':
		// Look Up
		keysDown[7] = 1;
		break;

	case 'k':
	case 'K':
		// Look Down
		keysDown[8] = 1;
		break;

	case 'r':
	case 'R':
		// Look Down
		keysDown[9] = 1;
		break;

	case 27:
		exit(0);
		break;	
  }
}

void keyboardUp(unsigned char key, int x, int y){
	
	
	switch (key) {
	case 'A':
	case 'a':
		// Andar para a Esquerda
		keysDown[0] = 0;
		break;

	case 'S':
	case 's':
		// Andar para Tras
		keysDown[1] = 0;;
		break;

	case 'w':
	case 'W':
		// Andar em Frente
		keysDown[2] = 0;
		break;

	case 'd':
	case 'D':
		// Andar para a Direita
		keysDown[3] = 0;
		break;	

	case 'j':
	case 'J':
		// Virar para a Esquerda
		keysDown[4] = 0;
		break;

	case 'l':
	case 'L':
		// Virar para a Direita
		keysDown[5] = 0;
		break;

	case 'p':
	case 'P':
		// Lancar
		keysDown[6] = 1;
		break;

	case 'i':
	case 'I':
		// Look Up
		keysDown[7] = 0;
		break;

	case 'k':
	case 'K':
		// Look Down
		keysDown[8] = 0;
		break;

	case 'r':
	case 'R':
		// Look Down
		keysDown[9] = 0;
		break;
  }
}

void teclasNotAscii(int key, int x, int y){
	// Rotacao do observador
	if(key == GLUT_KEY_LEFT){ 
		//OpenDoor
		if(doorPos[0][2] > 10.5){
			doorPos[0][2] -= 0.2;
		}
	}
	if(key == GLUT_KEY_RIGHT){
		//CloseDoor
		if(doorPos[0][2] < 16){
			doorPos[0][2] += 0.2;
		}
	}	
}

int main(int argc, char** argv){

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (wScreen, hScreen); 
	glutInitWindowPosition (300, 100); 
	glutCreateWindow ("Olá Malta!");
  
	init();
	glutSetKeyRepeat(1);
	glutSpecialFunc(teclasNotAscii); 
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp); 
	//glutPassiveMotionFunc(mouseHandler);
	glutDisplayFunc(display); 
	//glutTimerFunc(1, NULL, 1);

	glutMainLoop();

	return 0;
}

void initParticulas(int exp_id, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax){

	GLfloat v, theta, phi;
 	int i;

 	for(i=0; i<MAX_PARTICULAS; i++){
		v = 0.001*frand()+0.02;
	    theta = 2.0*frand()*M_PI;
		phi = frand()*M_PI;

		particula[exp_id][i].size = 0.02;
	    particula[exp_id][i].x = (GLfloat)(((float)rand()/(float)RAND_MAX) * (xmax-xmin)) + xmin;
	    particula[exp_id][i].y = (GLfloat)(((float)rand()/(float)RAND_MAX) * (ymax-ymin)) + ymin;
	    particula[exp_id][i].z = (GLfloat)(((float)rand()/(float)RAND_MAX) * (zmax-zmin)) + zmin;
 	
 		particula[exp_id][i].vx = v * cos(theta) * sin(phi);	// esferico
	    particula[exp_id][i].vy = v * cos(phi);
	    particula[exp_id][i].vz = v * sin(theta) * sin(phi);
		particula[exp_id][i].ax = 0;
	    particula[exp_id][i].ay = -0.0001f;
	    particula[exp_id][i].az = 0;

	    particula[exp_id][i].r = 1.0f;
		particula[exp_id][i].g = 1.0f;	
		particula[exp_id][i].b = 1.0f;	
		particula[exp_id][i].life = 1.0f;		                
		particula[exp_id][i].fade = 0.01f;
 	}
}

void showParticulas(int exp_id){
	int i;
  	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	for(i=0; i<MAX_PARTICULAS; i++){
		glColor4f(1,1,1, particula[exp_id][i].life);
		glBindTexture(GL_TEXTURE_2D, textures[9]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glBegin(GL_QUADS);
			glTexCoord2d(0,0); glVertex3f(particula[exp_id][i].x -particula[exp_id][i].size, particula[exp_id][i].y -particula[exp_id][i].size, particula[exp_id][i].z);      
			glTexCoord2d(1,0); glVertex3f(particula[exp_id][i].x +particula[exp_id][i].size, particula[exp_id][i].y -particula[exp_id][i].size, particula[exp_id][i].z);        
			glTexCoord2d(1,1); glVertex3f(particula[exp_id][i].x +particula[exp_id][i].size, particula[exp_id][i].y +particula[exp_id][i].size, particula[exp_id][i].z);            
			glTexCoord2d(0,1); glVertex3f(particula[exp_id][i].x -particula[exp_id][i].size, particula[exp_id][i].y +particula[exp_id][i].size, particula[exp_id][i].z);
			
			glTexCoord2d(1,1); glVertex3f(particula[exp_id][i].x +particula[exp_id][i].size, particula[exp_id][i].y +particula[exp_id][i].size, particula[exp_id][i].z);
			glTexCoord2d(0,1); glVertex3f(particula[exp_id][i].x +particula[exp_id][i].size, particula[exp_id][i].y -particula[exp_id][i].size, particula[exp_id][i].z);    
			glTexCoord2d(0,0); glVertex3f(particula[exp_id][i].x -particula[exp_id][i].size, particula[exp_id][i].y -particula[exp_id][i].size, particula[exp_id][i].z);
			glTexCoord2d(1,0); glVertex3f(particula[exp_id][i].x -particula[exp_id][i].size, particula[exp_id][i].y +particula[exp_id][i].size, particula[exp_id][i].z);        
			            
			glTexCoord2d(1,1); glVertex3f(particula[exp_id][i].x, particula[exp_id][i].y +particula[exp_id][i].size, particula[exp_id][i].z+particula[exp_id][i].size);      
			glTexCoord2d(0,1); glVertex3f(particula[exp_id][i].x, particula[exp_id][i].y +particula[exp_id][i].size, particula[exp_id][i].z-particula[exp_id][i].size);        
			glTexCoord2d(0,0); glVertex3f(particula[exp_id][i].x, particula[exp_id][i].y -particula[exp_id][i].size, particula[exp_id][i].z-particula[exp_id][i].size);            
			glTexCoord2d(1,0); glVertex3f(particula[exp_id][i].x, particula[exp_id][i].y -particula[exp_id][i].size, particula[exp_id][i].z+particula[exp_id][i].size);
			
			glTexCoord2d(1,1); glVertex3f(particula[exp_id][i].x, particula[exp_id][i].y +particula[exp_id][i].size, particula[exp_id][i].z+particula[exp_id][i].size);
			glTexCoord2d(1,0); glVertex3f(particula[exp_id][i].x, particula[exp_id][i].y -particula[exp_id][i].size, particula[exp_id][i].z+particula[exp_id][i].size);
			glTexCoord2d(0,0); glVertex3f(particula[exp_id][i].x, particula[exp_id][i].y -particula[exp_id][i].size, particula[exp_id][i].z-particula[exp_id][i].size);
			glTexCoord2d(0,1); glVertex3f(particula[exp_id][i].x, particula[exp_id][i].y +particula[exp_id][i].size, particula[exp_id][i].z-particula[exp_id][i].size);

		glEnd();

		particula[exp_id][i].x += particula[exp_id][i].vx;
	    particula[exp_id][i].y += particula[exp_id][i].vy;
	    particula[exp_id][i].z += particula[exp_id][i].vz;
	    particula[exp_id][i].vx += particula[exp_id][i].ax;
	    particula[exp_id][i].vy += particula[exp_id][i].ay;
	    particula[exp_id][i].vz += particula[exp_id][i].az;
		particula[exp_id][i].life -= particula[exp_id][i].fade;
		particula[exp_id][i].size -= 0.0002f;
		if(particula[exp_id][i].size < 0.0f){
			particula[exp_id][i].size = 0.0f;;
		}
	}	
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glDisable(GL_TEXTURE_2D);
}


