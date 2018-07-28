#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>
#include "RgbImage.h"

#define BLUE     0.0, 0.0, 1.0, 1.0
#define RED		 1.0, 0.0, 0.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 1.0
#define GRAY     0.4, 0.4, 0.4, 1.0
#define GRAY1	 0.1902, 0.1902, 0.1902, 1.0 
#define SKIN     1.0, 0.8, 0.58, 1.0
#define GLASS    0.68, 0.81, 1.0, 0.4
#define PI		 3.14159

#define NUM_KEYS 10
#define NUM_BALLS 1
#define NUM_CANS 10
#define NUM_DOORS 1

#define frand()			((float)rand()/RAND_MAX)
#define MAX_PARTICULAS  200

struct Vector{
	float x;
	float y;
	float z;
} vec; 

typedef struct Can *node;
struct Can{
	int id;
	int is_base;
	node BottomLeft;
	node BottomRight;
} cn;

int nexp = 0;

typedef struct {
	float size;
	float life;
	float fade;
	float r,g,b;
	GLfloat x,y,z;
	GLfloat vx,vy,vz;
	GLfloat ax,ay,az;
} Particle;

int is_exploding[NUM_CANS];
int counters[NUM_CANS];

Particle  particula[NUM_CANS][MAX_PARTICULAS];
GLint    milisec = 1000; 

GLfloat tam=2.0;


GLboolean   frenteVisivel=1;

// Obs + Ball
GLint		wScreen=1000, hScreen=650;		//.. janela (pixeis)
GLfloat		xC=10.0, yC=10.0, zC=10.0;		//.. Mundo  (unidades mundo)

GLfloat  initPos[] = {30.0,2.0,21.5};
GLfloat  obsP[] ={30.0,2.0,21.5};

GLfloat	 rotBall=0;
GLfloat	 rotBallY=0;
GLfloat	 rotMan=0;

GLfloat  ballP[]={30.0,1.7,28.0};
GLfloat  ballShotP[]={30.0,1.7,28.0};
GLfloat  angBall=-40.0*PI/180, angBallY = 0*PI, shotAngY = 0*PI;
GLfloat  rBall = 0.7;
GLfloat  rBallTemp = 0.7;
float t = 0.0f;
float stepf = 0.017f; // 60fps
GLfloat v = 3;

GLfloat  rVisaoObs=10, angObs=0.0*PI, step=0.05;
GLfloat  transAng = 0.0*PI;
GLfloat  angObsY = 0*PI;
GLfloat  g = 9.8f;

int mouseX, mouseY;
float mouseSpeed = 1/1000;
double lastTime = 0;

int keysDown[NUM_KEYS];

GLfloat  angZoom=90;
GLfloat  incZoom=3;
GLfloat  trans=0;
GLfloat  parAng=0;
GLfloat  parAngrad=0;

//shots
int fired = 0;
GLfloat shotAng = angObs;
GLfloat rShot = 0.7;

int physics = 0;

float xminPower = 30.0f;
float xmaxPower = 30.1f;
float power_step = 0.1f;
int power_dir = 1;

// Paintings
int modulate = 0;

// Materials

GLfloat  esmeraldAmb []={ 0.0215 ,0.1745 ,0.0215 };
GLfloat  esmeraldDif []={   0.07568 ,0.61424 ,0.07568 };
GLfloat  esmeraldSpec []={ 0.633 ,0.727811 ,0.633 };
GLint    esmeraldCoef = 0.6 *128;

GLfloat  jadeAmb []={ 0.135 ,0.2225 ,0.1575 };
GLfloat  jadeDif []={   0.54 ,0.89 ,0.63 };
GLfloat  jadeSpec []={ 0.316228 ,0.316228 ,0.316228 };
GLint   jadeCoef = 0.1 *128;

GLfloat  obsidianAmb []={ 0.05375 ,0.05 ,0.06625 };
GLfloat  obsidianDif []={   0.18275 ,0.17 ,0.22525 };
GLfloat  obsidianSpec []={ 0.332741 ,0.328634 ,0.346435 };
GLint  obsidianCoef = 0.3 *128;

GLfloat  pearlAmb []={ 0.25 ,0.20725 ,0.20725 };
GLfloat  pearlDif []={   1.0 ,0.829 ,0.829 };
GLfloat  pearlSpec []={ 0.296648 ,0.296648 ,0.296648 };
GLint  pearlCoef = 0.088 *128;

GLfloat  rubyAmb []={ 0.1745 ,0.01175 ,0.01175 };
GLfloat  rubyDif []={   0.61424 ,0.04136 ,0.04136 };
GLfloat  rubySpec []={ 0.727811 ,0.626959 ,0.626959 };
GLint  rubyCoef = 0.6 *128;

GLfloat  turquoiseAmb []={ 0.1 ,0.18725 ,0.1745 };
GLfloat  turquoiseDif []={   0.396 ,0.74151 ,0.69102 };
GLfloat  turquoiseSpec []={ 0.297254 ,0.30829 ,0.306678 };
GLint  turquoiseCoef = 0.1 *128;

GLfloat  brassAmb []={ 0.329412 ,0.223529 ,0.027451 };
GLfloat  brassDif []={   0.780392 ,0.568627 ,0.113725 };
GLfloat  brassSpec []={ 0.992157 ,0.941176 ,0.807843 };
GLint  brassCoef = 0.21794872 *128;

GLfloat  bronzeAmb []={ 0.2125 ,0.1275 ,0.054 };
GLfloat  bronzeDif []={   0.714 ,0.4284 ,0.18144 };
GLfloat  bronzeSpec []={ 0.393548 ,0.271906 ,0.166721 };
GLint  bronzeCoef = 0.2 *128;

GLfloat  chromeAmb []={ 0.25 ,0.25 ,0.25 };
GLfloat  chromeDif []={   0.4 ,0.4 ,0.4 };
GLfloat  chromeSpec []={ 0.774597 ,0.774597 ,0.774597 };
GLint  chromeCoef = 0.6 *128;

GLfloat  copperAmb []={ 0.19125 ,0.0735 ,0.0225 };
GLfloat  copperDif []={   0.7038 ,0.27048 ,0.0828 };
GLfloat  copperSpec []={ 0.256777 ,0.137622 ,0.086014 };
GLint  copperCoef = 0.1 *128;

GLfloat  goldAmb []={ 0.24725 ,0.1995 ,0.0745 };
GLfloat  goldDif []={   0.75164 ,0.60648 ,0.22648 };
GLfloat  goldSpec []={ 0.628281 ,0.555802 ,0.366065 };
GLint  goldCoef = 0.4 *128;

GLfloat  silverAmb []={ 0.19225 ,0.19225 ,0.19225 };
GLfloat  silverDif []={   0.50754 ,0.50754 ,0.50754 };
GLfloat  silverSpec []={ 0.508273 ,0.508273 ,0.508273 };
GLint  silverCoef = 0.4 *128;

GLfloat blackPlasticAmb []={ 0.0 ,0.0 ,0.0 };
GLfloat blackPlasticDif []={   0.01 ,0.01 ,0.01 };
GLfloat blackPlasticSpec []={ 0.50 ,0.50 ,0.50 };
GLint blackPlasticCoef = 0.25 *128;


GLfloat  cyanPlasticAmb []={ 0.0 ,0.1 ,0.06 };
GLfloat  cyanPlasticDif []={   0.0 ,0.50980392 ,0.50980392 };
GLfloat  cyanPlasticSpec []={ 0.50196078 ,0.50196078 ,0.50196078 };
GLint  cyanPlasticCoef = 0.25 *128;

GLfloat greenPlasticAmb []={ 0.0 ,0.0 ,0.0 };
GLfloat greenPlasticDif []={   0.1 ,0.35 ,0.1 };
GLfloat greenPlasticSpec []={ 0.45 ,0.55 ,0.45 };
GLint greenPlasticCoef = 0.25 *128;

GLfloat  redPlasticAmb []={ 0.0 ,0.0 ,0.0 };
GLfloat  redPlasticDif []={   0.5 ,0.0 ,0.0 };
GLfloat  redPlasticSpec []={ 0.7 ,0.6 ,0.6 };
GLint  redPlasticCoef = 0.25 *128;

GLfloat whitePlasticAmb []={ 0.0 ,0.0 ,0.0 };
GLfloat whitePlasticDif []={   0.55 ,0.55 ,0.55 };
GLfloat whitePlasticSpec []={ 0.70 ,0.70 ,0.70 };
GLint whitePlasticCoef = 0.25 *128;

GLfloat yellowPlasticAmb []={ 0.0 ,0.0 ,0.0 };
GLfloat yellowPlasticDif []={   0.5 ,0.5 ,0.0 };
GLfloat yellowPlasticSpec []={ 0.60 ,0.60 ,0.50 };
GLint yellowPlasticCoef = 0.25 *128;

GLfloat  blackRubberAmb []={ 0.02 ,0.02 ,0.02 };
GLfloat  blackRubberDif []={   0.01 ,0.01 ,0.01 };
GLfloat  blackRubberSpec []={ 0.4 ,0.4 ,0.4 };
GLint  blackRubberCoef = 0.078125 *128;

GLfloat  cyanRubberAmb []={ 0.0 ,0.05 ,0.05 };
GLfloat  cyanRubberDif []={   0.4 ,0.5 ,0.5 };
GLfloat  cyanRubberSpec []={ 0.04 ,0.7 ,0.7 };
GLint  cyanRubberCoef = 0.078125 *128;

GLfloat  greenRubberAmb []={ 0.0 ,0.05 ,0.0 };
GLfloat  greenRubberDif []={   0.4 ,0.5 ,0.4 };
GLfloat  greenRubberSpec []={ 0.04 ,0.7 ,0.04 };
GLint  greenRubberCoef = 0.078125 *128;

GLfloat  redRubberAmb []={ 0.05 ,0.0 ,0.0 };
GLfloat  redRubberDif []={   0.5 ,0.4 ,0.4 };
GLfloat  redRubberSpec []={ 0.7 ,0.04 ,0.04 };
GLint  redRubberCoef = 0.078125 *128;

GLfloat  whiteRubberAmb []={ 0.05 ,0.05 ,0.05 };
GLfloat  whiteRubberDif []={   0.5 ,0.5 ,0.5 };
GLfloat  whiteRubberSpec []={ 0.7 ,0.7 ,0.7 };
GLint  whiteRubberCoef = 0.078125 *128;

GLfloat yellowRubberAmb []={ 0.05 ,0.05 ,0.0 };
GLfloat yellowRubberDif []={   0.5 ,0.5 ,0.4 };
GLfloat yellowRubberSpec []={ 0.7 ,0.7 ,0.04 };
GLint yellowRubberCoef = 0.078125 *128;


// Lampada (Pontual)
GLfloat intLuzA = 0.6;
GLfloat intLuzD = 0.7;
GLfloat lightpos[] = {21.0,10.0,11.0,1.0}; //pontual
GLfloat lightpos1[] = {21.0,10.0,29.0,1.0};
GLfloat lightpos2[] = {39.0,10.0,11.0,1.0};
GLfloat lightpos3[] = {39.0,10.0,29.0,1.0};
GLfloat lightambient[] = { intLuzA, intLuzA, intLuzA };
GLfloat lightdiffuse[] = { intLuzD, intLuzD, intLuzD };
GLfloat lightspecular[] = { 1.0,     1.0,   1.0 };
GLfloat localAttCon =1.0;
GLfloat localAttLin =0.01;
GLfloat localAttQua =0.005;

//Luz Global
GLfloat luzGlobalCor[4]={1.0,1.0,1.0,1.0}; 

// Door
GLfloat doorPos[NUM_DOORS][3] = {20.0,0.0,16.0};
GLfloat doorOpen[NUM_DOORS] = {0};
GLfloat doorSeen[NUM_DOORS] = {0};


void initParticulas(int exp_id, float xmin, float xmax, float ymin, float ymax, float zmin, float zmax);
void showParticulas(int exp_id);
int checkCollisionObs(float x, float y, float z);
void drawCubes(float length, float height, float width, int tex_id);