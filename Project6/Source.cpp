#include <windows.h>									// Header File For Windows
#include <gl\gl.h>										// Header File For The OpenGL32 Library
#include <gl\glu.h>										// Header File For The GLu32 Library
//#include <gl\glaux.h>									// Header File For The Glaux Library
#include <cmath>
#include "texture.h"
#include <Model_3DS.h>
#include <3DTexture.h>
#include "sound.h"
using namespace std;	

//#include <tchar.h>
//#define _CRT_NONSTDC_NO_DEPRECATE
//#define _CRT_SECURE_NO_WARNINGS
	
HDC			hDC = NULL;									// Private GDI Device Context
HGLRC		hRC = NULL;									// Permanent Rendering Context
HWND		hWnd = NULL;								// Holds Our Window Handle
HINSTANCE	hInstance;									// Holds The Instance Of The Application

bool		keys[256];									// Array Used For The Keyboard Routine
bool		active = TRUE;								// Window Active Flag Set To TRUE By Default
bool		fullscreen = TRUE;							// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc


						/////////////// Global variabels //////////////

GLfloat LightPos[3];

int texture[6] ;



float angle = 0;

GLfloat xRotated = 0, yRotated = 0, zRotated = 0;

int global_num_floor ;

float global_z ;

float num_rooms = 4 ;    // cin >>

INIT initialize= INIT();
Sound sound1;

						/////////////// Functions //////////////


GLvoid ReSizeGLScene(GLsizei width, GLsizei height)			// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;											// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);							// Select The Projection Matrix
	glLoadIdentity();										// Reset The Projection Matrix

															// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 1200.0f);
	glFrustum(0,0,0,0,0,0);
	glOrtho(0,0,0,0,0,0);
	glMatrixMode(GL_MODELVIEW);								// Select The Modelview Matrix
	glLoadIdentity();										// Reset The Modelview Matrix
}
class sky_box{
public:
	float width,length,height;
	double x,y,z;
	sky_box(float width1,float length1,float height1){
		x=0;
		y=0;
		z=0;
		width=width1;
		length=length1;
		height=height1;
		///center sky box
		x = x - width  / 2;
		y = 3;
		z = z - length / 2;
		/*if(eyeX<x) eyeX = x+2;
		if(eyeX>x+width) eyeX = x+width-2;
		if(eyeY<y) eyeY = y+2;
		if(eyeY>y+height) eyeY = y+height-2;
		if(eyeZ<z) eyeZ = z+2;
		if(eyeZ>z+length) eyeZ = z+length-10;*/

	}
	void draw()
	{

	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS); 
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y,  z);
	glEnd();


	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);  
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z + length);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);      
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y,  z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,  z + length); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[5]);
	glBegin(GL_QUADS);      
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length); 
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glBegin(GL_QUADS);      
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length); 
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y,  z + length);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y,  z);     

	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_QUADS);  
    glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,  z);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y,  z + length);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length); 
    glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	}
};
class bulding
{
public:
	float x,y,z;
	double length,width,height;
	int img;
	int walls;
	int repeatBerRow;
	int repeatBerCell;
	int repeatBerRowForSurface;
	int repeatBerCellForSurface;
	int number;
	bulding(float x1, float y1, float z1,double width1, double length1,double height1,int number1,int repeatBerRowForSurface1,int repeatBerCellForSurface1,int img1,int walls1,int repeat1 ,int repeat2){
		x=x1;
		y=y1;
		z=z1;
		width=width1;
		length=length1;
		height=height1;
		img=img1;
		walls=walls1;
		repeatBerCell=repeat1;
		repeatBerRow=repeat2;
		repeatBerCellForSurface=repeatBerCellForSurface1;
		repeatBerRowForSurface=repeatBerRowForSurface1;
		number=number1;
	}
	void draw(){
	glShadeModel(GL_SMOOTH);
	
	if(number == 1){
		glBindTexture(GL_TEXTURE_2D,img);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x, y, z); 
		glTexCoord2d(repeatBerRowForSurface,0);
		glVertex3f(x+width, y, z);
		glTexCoord2d(repeatBerRowForSurface,repeatBerCellForSurface);
		glVertex3f(x+width, y, z-length);// Bottom Left Of The Quad (Bottom)
		glTexCoord2d(0,repeatBerCellForSurface);
		glVertex3f(x, y, z-length);    // Bottom Right Of The Quad (Bottom)
		glDisable(GL_TEXTURE_2D);
		glEnd();
	}

	else{
		glBindTexture(GL_TEXTURE_2D,walls);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x, y, z); 
		glTexCoord2d(repeatBerRow,0);
		glVertex3f(x+width, y, z);
		glTexCoord2d(repeatBerRow,repeatBerCell);
		glVertex3f(x+width, y, z-length);// Bottom Left Of The Quad (Bottom)
		glTexCoord2d(0,repeatBerCell);
		glVertex3f(x, y, z-length);    // Bottom Right Of The Quad (Bottom)
		glDisable(GL_TEXTURE_2D);
		glEnd();
	}

	if (number == 2){
		glBindTexture(GL_TEXTURE_2D,img);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x, y+height, z); 
		glTexCoord2d(repeatBerRowForSurface,0);
		glVertex3f(x+width, y+height , z);
		glTexCoord2d(repeatBerRowForSurface,repeatBerCellForSurface);
		glVertex3f(x+width, y+height, z-length);
		glTexCoord2d(0,repeatBerCellForSurface);
		glVertex3f(x, y+height, z-length);
		glEnd();
	}

	else{
		glBindTexture(GL_TEXTURE_2D,walls);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x, y+height, z); 
		glTexCoord2d(repeatBerRow,0);
		glVertex3f(x+width, y+height , z);
		glTexCoord2d(repeatBerRow,repeatBerCell);
		glVertex3f(x+width, y+height, z-length);
		glTexCoord2d(0,repeatBerCell );
		glVertex3f(x, y+height, z-length);
		glEnd();
	}	

	if(number == 3){
		glBindTexture(GL_TEXTURE_2D,img);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x, y, z);    // Top Right Of The Quad (Front)
		glTexCoord2d(repeatBerRowForSurface,0);
		glVertex3f(x+width, y, z);    // Top Left Of The Quad (Front)
		glTexCoord2d(repeatBerRowForSurface,repeatBerCellForSurface);
		glVertex3f(x+width, y+height, z);    // Bottom Left Of The Quad (Front)
		glTexCoord2d(0,repeatBerCellForSurface);
		glVertex3f(x, y+height, z);    // Bottom Right Of The Quad (Front)
		glEnd();
	}

	else{
		glBindTexture(GL_TEXTURE_2D,walls);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x, y, z);    // Top Right Of The Quad (Front)
		glTexCoord2d(repeatBerRow,0);
		glVertex3f(x+width, y, z);    // Top Left Of The Quad (Front)
		glTexCoord2d(repeatBerRow,repeatBerCell);
		glVertex3f(x+width, y+height, z);    // Bottom Left Of The Quad (Front)
		glTexCoord2d(0,repeatBerCell );
		glVertex3f(x, y+height, z);    // Bottom Right Of The Quad (Front)
		glEnd();
	}
	
	if(number == 4){
		glBindTexture(GL_TEXTURE_2D,img);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x+width, y, z-length);    
		glTexCoord2d(repeatBerRowForSurface,0);
		glVertex3f(x, y, z-length);    
		glTexCoord2d(repeatBerRowForSurface,repeatBerCellForSurface);
		glVertex3f(x, y+height, z-length);   
		glTexCoord2d(0,repeatBerCellForSurface);
		glVertex3f(x+width, y+height, z-length);
		glEnd();
	}

	else{
		glBindTexture(GL_TEXTURE_2D,walls);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x+width, y, z-length);    
		glTexCoord2d(repeatBerRow,0);
		glVertex3f(x, y, z-length);    
		glTexCoord2d(repeatBerRow,repeatBerCell);
		glVertex3f(x, y+height, z-length);   
		glTexCoord2d(0,repeatBerCell);
		glVertex3f(x+width, y+height, z-length);
		glEnd();
	}

	if(number == 5){
		glBindTexture(GL_TEXTURE_2D,img);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x, y, z);    
		glTexCoord2d(repeatBerRowForSurface,0);
		glVertex3f(x, y, z-length);
		glTexCoord2d(repeatBerRowForSurface,repeatBerCellForSurface);
		glVertex3f(x, y+height, z-length);
		glTexCoord2d(0,repeatBerCellForSurface);
		glVertex3f(x, y+height, z);
		glEnd();
	}

	else{
		glBindTexture(GL_TEXTURE_2D,walls);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x, y, z);    
		glTexCoord2d(repeatBerRow,0);
		glVertex3f(x, y, z-length);
		glTexCoord2d(repeatBerRow,repeatBerCell);
		glVertex3f(x, y+height, z-length);
		glTexCoord2d(0,repeatBerCell);
		glVertex3f(x, y+height, z);
		glEnd();
	}

	if(number == 6){
		glBindTexture(GL_TEXTURE_2D,img);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x+width, y, z);   
		glTexCoord2d(repeatBerRowForSurface,0);
		glVertex3f(x+width, y, z-length); 
		glTexCoord2d(repeatBerRowForSurface,repeatBerCellForSurface);
		glVertex3f(x+width, y+height, z-length);    
		glTexCoord2d(0,repeatBerCellForSurface);
		glVertex3f(x+width, y+height, z);
		glEnd();
	}
	else{
		glBindTexture(GL_TEXTURE_2D,walls);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x+width, y, z);   
		glTexCoord2d(repeatBerRow,0);
		glVertex3f(x+width, y, z-length); 
		glTexCoord2d(repeatBerRow,repeatBerCell);
		glVertex3f(x+width, y+height, z-length);    
		glTexCoord2d(0,repeatBerCell);
		glVertex3f(x+width, y+height, z);
		glEnd();
	}
            // End Drawing The Cube
	}
};
class wall
{
public:
	int x,y,z,a,b,c,d,e,f,g,h,i,img,numberOfRepeatBerRow,numberOfRepeatBerColum;
	wall(int x1,int y1,int z1,int x2,int y2,int z2,int x3,int y3,int z3,int x4,int y4,int z4 ,int img1,int numberOfRepeatBerRow1,int numberOfRepeatBerColum1){
		x=x1;y=y1;z=z1;
		a=x2;b=y2;c=z2;
		d=x3;e=y3;f=z3;
		g=x4;h=y4;i=z4;
		numberOfRepeatBerRow=numberOfRepeatBerRow1; 
		numberOfRepeatBerColum=numberOfRepeatBerColum1;
		img=img1;
	}
	void draw(){
		glBindTexture(GL_TEXTURE_2D,img);
		glBegin(GL_QUADS);
		glTexCoord2d(0,0);
		glVertex3f(x, y, z);   
		glTexCoord2d(0,numberOfRepeatBerColum);
		glVertex3f(a, b,c); 
		glTexCoord2d(numberOfRepeatBerRow,numberOfRepeatBerColum);
		glVertex3f(d, e, f);    
		glTexCoord2d(numberOfRepeatBerRow,0);
		glVertex3f(g, h, i);
		glEnd();
	}
	

};


int rasif;
int walls;
Model_3DS tree,car,lamp,garbage,barkingCar;
int wallsForBuilding;
int faceOfBuilding;
int corner;
int corner2;
int numberOfTrees;
int numberOfStreets;
int numberOfStreetLamp;
int numberOfBuilding;
int numberOfCar;
Model_3DS sofa , table , Dresser;
int sjada , doorRoomc , doorRoom , wallPaper , wallPaperc  , bulid_image ,bulid_imagec ,  floor_walls ,floor_wallsc ,stairs,stairsc ,leftDoor , rightDoor ,rightliftDoor  ,leftliftDoor ,insideLift;
sky_box s(1000,1000,1000);
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.50f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glEnable(GL_TEXTURE_2D);
	
  	texture[0] = LoadTexture("front.bmp",255);//front
    texture[1] = LoadTexture("back.bmp",255);//back
    texture[2] = LoadTexture("left.bmp",255);//left
    texture[3] = LoadTexture("right.bmp",255); //right
	texture[4] = LoadTexture("down.bmp",255); //down
	texture[5] = LoadTexture("top.bmp",255);//top
	rasif=LoadTexture("rasif.bmp",255);
	walls=LoadTexture("walls4.bmp",255);
	corner=LoadTexture("corner.bmp",255);
	corner2=LoadTexture("corner2.bmp",255);
	faceOfBuilding=LoadTexture("face of building.bmp",255);
	wallsForBuilding=LoadTexture("wallss for building.bmp",255);

	bulid_image	 = LoadTexture("bulid_image.bmp"  , 255 );
	bulid_imagec = LoadTexture("bulid_imagec.bmp" , 255 );
	floor_walls  = LoadTexture("floor_walls.bmp"  , 255 );
	floor_wallsc = LoadTexture("floor_wallsc.bmp" , 255 );
	stairs		 = LoadTexture("stairs.bmp"		  , 255 );
	stairsc		 = LoadTexture("stairsc.bmp"	  , 255 );
	leftDoor     = LoadTexture("leftDoor.bmp"	  , 255 );
	rightDoor    = LoadTexture("rightDoor.bmp"	  , 255 );
	leftliftDoor = LoadTexture("gate.bmp"		  , 255 );
	rightliftDoor= LoadTexture("gate.bmp"		  , 255 );
	insideLift   = LoadTexture("insideLift.bmp"	  , 255 );
	wallPaper	 = LoadTexture("wallPaper.bmp"	  , 255 );
	wallPaperc   = LoadTexture("wallPaperc.bmp"	  , 255 );
	doorRoom     = LoadTexture("doorRoom.bmp"	  , 255 );
	doorRoomc    = LoadTexture("doorRoomc.bmp"	  , 255 );
	sjada        = LoadTexture("sjada.bmp"		  , 255 );

    
	tree = Model_3DS();
	tree.Load("Tree1.3ds");
	tree.scale = 5;
	GLTexture g,l,b;
	g.LoadBMP("green.bmp");
	l.LoadBMP("bark_loo.bmp");
	b.LoadBMP("brown.bmp");
	tree.Materials[0].tex = l;
	tree.Materials[1].tex = g;
	tree.Materials[2].tex = b;
	tree.Materials[3].tex = b;
	tree.Materials[4].tex = g;
	car = Model_3DS();
	car.Load("car.3ds");
	barkingCar.Load("car.3ds");
	GLTexture carPicture;
	carPicture.LoadBMP("car.bmp");
	car.Materials[0].tex = carPicture;
	barkingCar.Materials[0].tex = carPicture;
	lamp = Model_3DS();
	lamp.Load("Open3DModel (1).3DS");
	lamp.scale = 0.02;
	GLTexture lampBodyColor,lampColor;
	lampBodyColor.LoadBMP("gray.bmp");
	lampColor.LoadBMP("yellow.bmp");
	lamp.Materials[0].tex = lampBodyColor;
	lamp.Materials[1].tex = lampColor;
	garbage = Model_3DS();
	garbage.Load("Garbage_Container_.3ds");
	GLTexture p;
	p.LoadBMP("Garbage_Container_.bmp");
	garbage.Materials[0].tex = p;
	garbage.scale = 10;

	

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

	sofa = Model_3DS();
	sofa.Load("chair.3ds");
	GLTexture m1,m2,m3,m4,m5 ,m6,m7,m8,m9,m10,m11,m12,m13,m14,m15;
	m1.LoadBMP("pink.bmp"); 
	sofa.Materials[0].tex  = m1 ;	//رجل قدام يسار
	sofa.Materials[8].tex  = m1 ;	// رجل ورا يسار
	sofa.Materials[11].tex = m1 ;	// رجل ورا يمين
	sofa.Materials[4].tex  = m1 ;	// رجل قدام يمين
	m2.LoadBMP("korsi.bmp"); 
	sofa.Materials[7].tex  = m2 ;	// ايد يمين فوق
	sofa.Materials[3].tex  = m2 ;	// ايد يسار فوق
	sofa.Materials[1].tex  = m2 ;   // مقعد تحت
	sofa.Materials[5].tex  = m2 ;   // ضهر ورا
	m3.LoadBMP("brwon.bmp"); 
	sofa.Materials[2].tex  = m3 ;	// ايد يمين تحت
	sofa.Materials[9].tex  = m3 ;	// ايد يسار تحت
	m4.LoadBMP("zizi.bmp"); 
	sofa.Materials[6].tex  = m4 ;	// ضهر قدام
	sofa.Materials[10].tex = m4 ;	// مقعد فوق

	table = Model_3DS();
	table.Load("table.3ds");
	m13.LoadBMP("gogo.bmp"); //all
	table.Materials[0].tex = m13 ;

	Dresser = Model_3DS();
	Dresser.Load("Dresser.3ds");
	m14.LoadBMP("pink.bmp");  
	Dresser.Materials[0].tex = m14 ;  // الدروج
	m15.LoadBMP("gogo.bmp"); 
	Dresser.Materials[1].tex = m15 ;  // الخزانة
	initialize.InitOpenAL();
	sound1=Sound("C:\\Users\\PC\\Desktop\\fiinal\\project\\Project6\\sound.wav");
	return TRUE;										// Initialization Went OK



	return TRUE;										// Initialization Went OK
}


float eyeX = 0, eyeY = 8, eyeZ = -s.z-s.length/8 , angel = -1.5;
void Key(bool* keys)
{
	float eyeX1 = eyeX;
	float eyeY1 = eyeY;
	float eyeZ1 = eyeZ;
	LightPos[0]=0;
	LightPos[1]=s.y;
	LightPos[2]=s.z;

	if (keys[VK_UP])
	{
		eyeX1 += cos(angel)*4;
		eyeZ1 += sin(angel)*4;
		eyeX = eyeX1;
		eyeZ = eyeZ1;
	}

	if (keys[VK_DOWN])
	{
		eyeX1 -= cos(angel)*4;
		eyeZ1 -= sin(angel)*4;
		eyeX = eyeX1;
		eyeZ = eyeZ1;
	}
	if (keys['A'])
	{
		eyeY-=1;
	}
	if (keys['D'])
	{
		eyeY+=1;
	}
	if (keys['Q'])
	{
		eyeX-=1;
	}
	if (keys['E'])
	{
		eyeX+=1;
	}
	if (keys['Z'] )
	{
		eyeZ-=1;
	}
	if (keys['C'])
	{
		eyeZ+=1;
	}
	if (keys['A'])
	{
		eyeY-=1;
	}
	if (keys['W'])
	{
		glRotated(-20,1,0,0);
	}
	if (keys['S'])
	{
		glRotated(20,1,0,0);
	}
	if (keys[VK_LEFT]){
		angel -= 0.05;
	}
	if (keys[VK_RIGHT]){
	   angel += 0.05;
	}	
	if (keys['O'])
	{
		GLfloat LightAmb[] = { 5.0f,5.0f,5.0f,1.0f };
        GLfloat LightDiff[] = { 5.0f,5.0f,5.0f,1.0f };
        GLfloat LightSpec[] = { 5.0f,5.0f,5.0f,1.0f };
		glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
	    glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmb);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,LightDiff);
	    glEnable(GL_LIGHT0);
	    glEnable(GL_LIGHTING);
	}	
	if (keys['L'])
	{
		GLfloat LightAmb[] = { 0.6f,0.6f,0.6f,1.0f };
        GLfloat LightDiff[] = { 0.6f,0.6f,0.6f,1.0f };
        GLfloat LightSpec[] = { 0.2f,0.2f,0.2f,1.0f };
		glLightfv(GL_LIGHT0,GL_POSITION,LightPos);
	    glLightfv(GL_LIGHT0,GL_AMBIENT,LightAmb);
		glLightfv(GL_LIGHT0,GL_DIFFUSE,LightDiff);
	    glEnable(GL_LIGHT0);
	    glEnable(GL_LIGHTING);
	}
}


		void Playsound()
		{
		if(keys['1'])
		{
			sound1.Play();
		}
		if(keys['0'])
		{
			sound1.Stop();
		}
		}
			/////////////// Classes //////////////


class MainBuilding{

public:

	int x , y , z ,ex, ey ,ez , length  , width  , height ;

	MainBuilding(int x1 , int y1 , int z1 ,int width1,int length1){

		x = x1 ;
		y = y1 ;
		z = z1 ;
		length = length1 ;
		width  = width1  ;
		height = 25  ;

	}

	void draw( int num_of_floors ){

		ex = eyeX ;
		ez = eyeZ ;
		ey = eyeY ;

		global_num_floor = num_of_floors ;

		for ( int i = 0 ; i <= num_of_floors  ; i ++ ){

			if (i == 0 ) {

				//////////    back  

				draw_rectangle( x						   , y				 , z + length	, width / 3				,  height      ,	bulid_imagec , floorf(width/(width/3))	, floorf(height/4) );	//حيط يسار
				draw_rectangle( x +(width / 3) * 2  	   , y				 , z + length	, (width-((width/3)*2))	,  height      ,	bulid_imagec , floorf(width/(width/3))	, floorf(height/4) );	//حيط يمين
				draw_rectangle( x +(width / 3)			   , y +(height/3)*2 , z + length	, width / 3				, (height/3)+1 ,	floor_wallsc , floorf(width/(width/3))	, floorf(height/4) );	//عتبة

				if ( eyeX >= x + (width / 3) && eyeX <= x +  ((width / 3)*2) && eyeZ >= z+((length - (length/5))-15) && eyeZ <= z+((length + (length/5))-15) && eyeY >= y && eyeY <= (y+(height/3)*2) ){
					draw_rectangle( x +(width / 3)	-10			   , y		 , z + length +0.5	, (width / 3)/2		, (height/3)*2  ,	leftDoor  , 1	, 1		);	//باب يسار
					draw_rectangle( x +((width/3)+(width/3)/2) +10 , y		 , z + length +0.5	, (width / 3)/2		, (height/3)*2  ,	rightDoor , 1	, 1		);	//باب يمين
				}
				else {
					draw_rectangle( x +(width / 3)				   , y		 , z + length		, ((width / 3)/2)+1	, (height/3)*2  ,	leftDoor  , 1	, 1		);	//باب يسار
					draw_rectangle( x +(width/2)				   , y		 , z + length		, (width / 3)/2		, (height/3)*2  ,	rightDoor , 1	, 1		);	//باب يمين
				}	


				glBindTexture(GL_TEXTURE_2D, insideLift);  //down 
				glBegin(GL_QUADS);      
				glTexCoord2f(15000.0f, 0.0f);		glVertex3f(x		, y , z			 );
				glTexCoord2f(15000.0f, 15000.0f);	glVertex3f(x		, y , z + length );
				glTexCoord2f(0.0f, 15000.0f);		glVertex3f(x + width, y , z + length ); 
				glTexCoord2f(0.0f, 0.0f);			glVertex3f(x + width, y , z			 );
				glEnd();

				glBindTexture(GL_TEXTURE_2D, insideLift);  // top 
				glBegin(GL_QUADS);      
					glTexCoord2f(0.0f, 0.0f);		glVertex3f(x + width , y + height , z+ (length/6)	);
					glTexCoord2f(1.0f, 0.0f);		glVertex3f(x + width , y + height , z + length		); 
					glTexCoord2f(1.0f, 1.0f);		glVertex3f(x		 , y + height , z + length		);
					glTexCoord2f(0.0f, 1.0f);		glVertex3f(x		 , y + height , z+ (length/6)	);
				glEnd();

						// stairs 

				draw_Stairs(x + (width/3) , y , z + (length/6));

						//walls
				draw_Quad(x+(width/3)	 , y , z , length , 0.01 , height , floor_walls , floorf( length/10 ) , floorf( width/10 ) , floorf( height/10 ) );   // left wall
				draw_Quad(x+((width/3)*2), y , z , length , 0.01 , height , floor_walls , floorf( length/10 ) , floorf( width/10 ) , floorf( height/10 ) );   // right wall
				
				
				
				
										// الصدم

				// front

				if (  eyeX >= x  && eyeX <= x+width   && eyeY <= (height*(global_num_floor+1))   && eyeY >= y){
					if ( eyeZ > z + 1 && eyeZ < z + 3  )
						eyeZ = z + 5 ;
					if ( eyeZ < z - 10 && eyeZ > z - 10 )
						eyeZ = z - 12 ;
				}

				// left

				if ( eyeZ <= z + (length  )  && eyeZ >= (z) && eyeY <= (height*(global_num_floor+1))   && eyeY >= y    ){
					if ( eyeX >= x && eyeX <= x+1 )
						eyeX = x - 5 ;
					if ( eyeX <= x + 2 && eyeX >= x+1 )
						eyeX = x + 5 ;
				}

				// right

				if ( eyeZ <= z + (length  )  && eyeZ >= (z)  && eyeY <= (height*(global_num_floor+1))   && eyeY >= y ){
					if ( eyeX >= x+width && eyeX <= x+width+1 )
						eyeX = x+width - 5 ;
					if ( eyeX <= x+width + 2 && eyeX >= x+width+1 )
						eyeX = x+width + 5 ;
				}


				// back

				if ( eyeX >= x  && eyeX <= x + width  && eyeY <= (height*(global_num_floor+1))   && eyeY >= y  ) // inside to out side
					if (eyeZ <= z + length - 5    && eyeZ >= z + length - 10  ) 
						eyeZ = z + length - 13 ;
				/// outside to in side
				if ( eyeX >= x  && eyeX <= x + (width/3)  && eyeY <= (height*(global_num_floor+1))   && eyeY >= y  ) {
					if (eyeZ >= z + length    && eyeZ <= z + length + 3  ) 
						eyeZ = z + length + 5 ;
				}
				if ( eyeX >= x + (width/3)  && eyeX <= x + ((width/3)*2)  && eyeY <= (height*(global_num_floor+1))   && eyeY >= ((height/3)*2)  ) {
					if (eyeZ >= z + length    && eyeZ <= z + length + 3  ) 
						eyeZ = z + length + 5 ;
					
				}
				if ( eyeX >= x + ((width/3)*2) && eyeX <= x + width  && eyeY <= (height*(global_num_floor+1))   && eyeY >= y  ) {
					if (eyeZ >= z + length    && eyeZ <= z + length + 3  ) 
						eyeZ = z + length + 5 ;
				}

				// top

				if ( eyeX <= x+width && eyeX >= x  && eyeZ <= z +length && eyeZ >= z  ){
				
					if ( eyeY <= y + (height*(global_num_floor+1)) +5   && eyeY >= y + (height*(global_num_floor+1))  + 2 )
						eyeY = y + (height*(global_num_floor+1)) +10 ;
					if ( eyeY <= y + (height*(global_num_floor+1)) - 2   && eyeY >= y + (height*(global_num_floor+1)) - 5 )
						eyeY = y + (height*(global_num_floor+1)) - 10 ;
				}

				// floor zero left wall

				if (  eyeX <= x+ (width/3)+5 && eyeX >= x + (width/3)  && eyeZ <= z +length && eyeZ >= z && eyeY <= (height)   && eyeY >= y   )
					eyeX = x + (width/3) + 10 ;

				
				// floor zero right wall

				if (  eyeX <= x+ ((width/3)*2)  && eyeX >= x + ((width/3)*2) - 5 && eyeZ <= z +length && eyeZ >= z  && eyeY <= height  && eyeY >= y )
					eyeX = x + ((width/3)*2)  - 10 ;
				

				//  left quad

				if ( eyeX <= x+ (width/3)+5 && eyeX >= x + (width/3)  && eyeZ <= z +(length/6) && eyeZ >= z && eyeY <= (height*(global_num_floor+1))   && eyeY >= y  ) 
					eyeX = x + (width/3) + 10 ;

				// right  quad

				if (  eyeX <= x+ ((width/3)*2)  && eyeX >= x + ((width/3)*2) - 5 && eyeZ <= z +(length/6) && eyeZ >= z  && eyeY <= (height*(global_num_floor+1))   && eyeY >= y )
					eyeX = x + ((width/3)*2)  - 10 ;

				// face left quad

				if ( eyeX <= x+ (width/3) && eyeX >= x   && eyeZ <= z +(length/6) + 5 && eyeZ >= z +(length/6) && eyeY <= (height*(global_num_floor+1))   && eyeY >= y )
					eyeZ = z +(length/6) + 10 ;

				// face right quad

				if ( eyeX <= x+ (width) && eyeX >= x +  ((width/3)*2)  && eyeZ <= z +(length/6) + 5 && eyeZ >= z +(length/6) && eyeY <= (height*(global_num_floor+1))   && eyeY >= y )
					eyeZ = z +(length/6) + 10 ;

				

				// الطلعة ع الدرج
		
				if (eyeX >= x + (width/3) && eyeX <= x + (width/3)  + (width/9) && eyeZ  <= z + (length/6) && eyeZ >= z + (length/6) - 12)
					eyeY++;
			}
			else if ( i == num_of_floors ){

				glBindTexture(GL_TEXTURE_2D, bulid_imagec);  // top 
				glBegin(GL_QUADS);      
					glTexCoord2f(0.0f, 0.0f);							 glVertex3f( x + width  , y + height+0.1 , z		   );
					glTexCoord2f(floorf( length/10), 0.0f);				 glVertex3f( x + width  , y + height+0.1 , z + length  ); 
					glTexCoord2f(floorf( length/10), floorf( width/10)); glVertex3f( x		    , y + height+0.1 , z + length  );
					glTexCoord2f(0.0f, floorf( width/10));				 glVertex3f( x		    , y + height+0.1 , z		   );
				glEnd();

				glBindTexture(GL_TEXTURE_2D, insideLift);  // top2 
				glBegin(GL_QUADS);      
					glTexCoord2f(0.0f, 0.0f);							glVertex3f( x + width   , y + height , z + (length/6)  );
					glTexCoord2f(1.0f, 0.0f);							glVertex3f( x + width   , y + height , z + length      ); 
					glTexCoord2f(1.0f, 1.0f);							glVertex3f( x			, y + height , z + length	   );
					glTexCoord2f(0.0f, 1.0f);							glVertex3f( x			, y + height , z + (length/6)  );
				glEnd();


				draw_Quad(x					         , y		 , z , length/6		  ,width/3+width/9 , height , floor_walls , floorf( length/10 ) ,floorf( width/10),floorf( height/10)); // مكعب يسار
				draw_Quad(x + ((width/3)*2)		     , y	  	 , z , length/6	      ,width/3		   , height , floor_walls , floorf( length/10 ) ,floorf( width/10),floorf( height/10));  // مكعب يمين
				draw_Quad(x + ((width/3)+(width/9))  , y		 , z , (length/6)-12  ,width/9		   , height , floor_walls , floorf( length/10 ) ,floorf( width/10),floorf( height/10)); // مكعب ورا الاصنصير

							//lift

			     draw_lift(x + ((width/3)+(width/9)) , y , (z+(length/6))  , global_z , ((width/3) - ((width/9)*2)) , height);
	
							// rooms
						
				float newLength =   (length - (length/3)) ;

				float space     =     width * newLength		  ;

				float roomSpace = (width/6) * newLength       ;

				int allRoom = space / roomSpace				  ;

				if ( num_rooms <= allRoom ){

					//// draw_room on numRoom Rooms
					float fofo = 0 ;
					for ( int i = 0 ; i < num_rooms ; i ++ ){ 
					
						draw_room(x + fofo ,y,z + (length/3),(length-(length/3)),(width/num_rooms),height);
						
						float x2=x + fofo;
						float y2=y;
						float z2=z+(length/3);
						float width2=(width/num_rooms);
						float length2=(length-(length/3));
						float height2=height;
						draw_window( x2 +(width2 / 3)     , y2 +(height2/3)	 , z2 + length2	,  width2 / 3	,  height2/3 );		

						fofo+=  (width / num_rooms) ;
					}
				
				}
				else {
				
					//// draw_room on allRoom Rooms
					float fofo = 0 ;
					for ( int i = 0 ; i < allRoom ; i ++ ){ 
						draw_room(x + fofo ,y,z + (length/3),(length-(length/3)),(width/num_rooms),height);
					
						float x2=x + fofo;
						float y2=y;
						float z2=z+(length/3);
						float width2=(width/num_rooms);
						float length2=(length-(length/3));
						float height2=height;
						draw_window( x2 +(width2 / 3)     , y2 +(height2/3)	 , z2 + length2	,  width2 / 3	,  height2/3 );		
						
						fofo+=  (width / num_rooms) ;
					}
				}
			}
			else  {

				
				glBindTexture(GL_TEXTURE_2D, insideLift);  // top 
				glBegin(GL_QUADS);      
					glTexCoord2f(0.0f, 0.0f);	glVertex3f( x + width , y + height , z + (length/6) );
					glTexCoord2f(1.0f, 0.0f);	glVertex3f( x + width , y + height , z + length     ); 
					glTexCoord2f(1.0f, 1.0f);	glVertex3f( x		  , y + height , z + length     );
					glTexCoord2f(0.0f, 1.0f);	glVertex3f( x		  , y + height , z + (length/6) );
				glEnd();

				draw_Stairs(x + (width/3) , y  , z + (length/6));

				draw_Quad( x			   , y , z , length/6 , width/3 , height , floor_walls , floorf( length/10 ) , floorf( width/10 ) , floorf( height/10 ) );  //مكعب يسار
				draw_Quad( x+((width/3)*2) , y , z , length/6 , width/3 , height , floor_walls , floorf( length/10 ) , floorf( width/10 ) , floorf( height/10 ) );  //مكعب يمين

				float newLength =   (length - (length/3))     ;

				float space     =     width * newLength		  ;

					float roomSpace = (width/6) * newLength   ;

					int allRoom = space / roomSpace			  ;

					if ( num_rooms <= allRoom ){

						//// draw_room on numRoom Rooms
						float fofo = 0 ;
						for ( int i = 0 ; i < num_rooms ; i ++ ){ 
							draw_room(x + fofo ,y,z + (length/3),(length-(length/3)),(width/num_rooms),height);
							
							float x2=x + fofo;
					    	float y2=y;
						    float z2=z+(length/3);
						    float width2=(width/num_rooms);
							float length2=(length-(length/3));
						    float height2=height;
						    draw_window( x2 +(width2 / 3)     , y2 +(height2/3)	 , z2 + length2	,  width2 / 3	,  height2/3 );	
							
							fofo+=  (width / num_rooms) ;
						}
				
					}
					else {
				
						//// draw_room on allRoom Rooms
						float fofo = 0 ;
					for ( int i = 0 ; i < allRoom ; i ++ ){ 
						draw_room(x + fofo ,y,z + (length/3),(length-(length/3)),(width/num_rooms),height);
						
						float x2=x + fofo;
						float y2=y;
						float z2=z+(length/3);
						float width2=(width/num_rooms);
						float length2=(length-(length/3));
						float height2=height;
						draw_window( x2 +(width2 / 3)     , y2 +(height2/3)	 , z2 + length2	,  width2 / 3	,  height2/3 );	
						
						fofo+=  (width / num_rooms) ;
					}
				}
			}

				glBindTexture(GL_TEXTURE_2D, bulid_image); //front
				glBegin(GL_QUADS); 
					glTexCoord2f(floorf( width/10), 0.0f);					glVertex3f(x + width, y			,  z );
					glTexCoord2f(floorf( width/10),floorf( height/10));		glVertex3f(x + width, y + height,  z ); 
					glTexCoord2f(0.0f,floorf( height/10));					glVertex3f(x		, y + height,  z );
					glTexCoord2f(0.0f, 0.0f);								glVertex3f(x		, y			,  z );
				glEnd();

				glBindTexture(GL_TEXTURE_2D,bulid_image); //left
				glBegin(GL_QUADS);      
					glTexCoord2f(floorf( length/10), floorf( height/10));	glVertex3f(x, y + height, z			 ); 
					glTexCoord2f(0.0f, floorf( height/10));					glVertex3f(x, y + height, z + length ); 
					glTexCoord2f(0.0f, 0.0f);								glVertex3f(x, y			, z + length );
					glTexCoord2f(floorf( length/10), 0.0f);					glVertex3f(x, y			, z			 );     
				glEnd();

				glBindTexture(GL_TEXTURE_2D, bulid_image	);  //right
				glBegin(GL_QUADS);  
					glTexCoord2f(0.0f, 0.0f);								glVertex3f(x + width, y			, z			 );
					glTexCoord2f(floorf( length/10), 0.0f);				    glVertex3f(x + width, y			, z + length );
					glTexCoord2f(floorf( length/10),floorf(  height/10));	glVertex3f(x + width, y + height, z + length ); 
					glTexCoord2f(0.0f,floorf( height/10));				    glVertex3f(x + width, y + height, z			 );
				glEnd();

				
				
			y+=height;									/////// looooooook aaaaat heeeeereeee   <================================

		}
	}

	void draw_Stairs	(float x , float y , float z ) {

								// left stairs
		float local_z;
		for (int  i  = 0 ; i <= (height/2) ; i += 2 ){
			draw_Quad( x , y + i   , z - i	  , 2 , (width/9) , 2 ,stairs ,1,1,1);
			local_z = z - i ;
			if (i == (height/2))
				draw_Quad( x , y + i  , z - i	  , 2 , (width/9) , 1 ,stairs,1,1,1 );
		}
		global_z = local_z ;

		
											// الطلعة ع الدرج

		//if ( eyeZ  <= z && eyeZ >= z-12  && ((eyeX >= x && eyeX <= x+(width/9))||(eyeX >= x + ((width/3)-(width/9)) && eyeX <= x + (((width/3)-(width/9))+(width/9))) && eyeY >= 0 && eyeY <= (height*(global_num_floor + 1) ) && keys[VK_UP])){
			//eyeY+=2;
		//}
		
											// middle

		draw_Quad( x , y + (height/2) + 2 , local_z , -(length/6)+12 , (width/3) ,0.1 , stairsc , floorf( length/10 ) , floorf( width/10 ) , floorf( height/10 ) ) ;
					
											// right stairs

		int gogo = 0 ;
		int j = 0 ; 
		for ( j = (height/2)  ; j < height - 2 ; j += 2 ){
			draw_Quad( x + ((width/3)-(width/9)) , y + j  ,	local_z + gogo   , 2 , (width/9) , 2 ,stairs,1,1,1 );
			gogo+=2;
			
		}
		draw_Quad( x + ((width/3)-(width/9)) , y + j  ,	local_z + gogo   , 2 , (width/9) , 1	 ,stairs,1,1,1); // اخر درجة
		

						///    lift 

		draw_lift(x + (width/9) , y , z , local_z , ((width/3) - ((width/9)*2)) , height);

	}
	
	void draw_window	(float x , float y , float z , float width  , float height ){

		glBlendFunc(GL_ONE,GL_ONE);
		glEnable(GL_BLEND);		
			glColor4f(1.0,1.0,1.0,0.3);
	  		glBegin(GL_QUADS);  
				glVertex3f(x, y, z);
      			glVertex3f(x + width , y , z); 
				glVertex3f(x + width , y + height , z);
				glVertex3f(x , y + height , z);
			glEnd();
		glDisable(GL_BLEND);

}

	void draw_rectangle (float x , float y , float z , float width  , float height , int img       , float rw , float rh){
		
	glBindTexture(GL_TEXTURE_2D, img);
	glBegin(GL_QUADS);  
		glTexCoord2f( rw   , 0.0f );		glVertex3f(x		 , y		  , z );
		glTexCoord2f( rw   , rh   );		glVertex3f(x + width , y		  , z ); 
		glTexCoord2f( 0.0f , rh	  );		glVertex3f(x + width , y + height , z );
		glTexCoord2f( 0.0f , 0.0f );		glVertex3f(x		 , y + height , z );
	glEnd();

}

	void draw_Quad		(float x , float y , float z , float length , float width  , float height  , int img ,  float rl , float rw , float rh ){

		glBindTexture(GL_TEXTURE_2D,img);
		glBegin(GL_QUADS); 
			glTexCoord2f(rw, 0.0f);		 glVertex3f(x + width , y		   , z			 );
			glTexCoord2f(rw, rh);		 glVertex3f(x + width , y + height , z			 ); 
			glTexCoord2f(0.0f, rh);		 glVertex3f(x		  , y + height , z			 );
			glTexCoord2f(0.0f, 0.0f);	 glVertex3f(x		  , y		   , z		 	 );
		glEnd();

		glBindTexture(GL_TEXTURE_2D, img);
		glBegin(GL_QUADS);  
			glTexCoord2f(rw, 0.0f);		glVertex3f(x		  , y		   , z + length );
			glTexCoord2f(rw,rh);		glVertex3f(x		  , y + height , z + length );
			glTexCoord2f(0.0f, rh);		glVertex3f(x + width  , y + height , z + length ); 
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + width  , y		   , z + length );
		glEnd();

		glBindTexture(GL_TEXTURE_2D,img);
		glBegin(GL_QUADS);      
			glTexCoord2f(rl, 0.0f);		glVertex3f(x		 , y , z					);
			glTexCoord2f(rl, rw);		glVertex3f(x		 , y , z + length			);
			glTexCoord2f(0.0f, rw);		glVertex3f(x + width , y , z + length			); 
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + width , y , z					);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, img);
		glBegin(GL_QUADS);      
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + width , y + height , z			);
			glTexCoord2f(rl, 0.0f);		glVertex3f(x + width , y + height , z + length  ); 
			glTexCoord2f(rl, rw);		glVertex3f(x		 , y + height , z + length  );
			glTexCoord2f(0.0f, rw);		glVertex3f(x		 , y + height , z		    );
		glEnd();

		glBindTexture(GL_TEXTURE_2D, img);
		glBegin(GL_QUADS);      
			glTexCoord2f(rl,rh);		glVertex3f(x , y + height , z					); 
			glTexCoord2f(0.0f, rh);		glVertex3f(x , y + height , z + length			); 
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(x , y		  , z + length			);
			glTexCoord2f(rl, 0.0f);		glVertex3f(x , y		  , z					);     
		glEnd();

		glBindTexture(GL_TEXTURE_2D, img);
		glBegin(GL_QUADS);  
			glTexCoord2f(0.0f, 0.0f);	glVertex3f(x + width , y		  , z			);
			glTexCoord2f(rl, 0.0f);		glVertex3f(x + width , y		  , z + length  );
			glTexCoord2f(rl, rh);		glVertex3f(x + width , y + height , z + length  ); 
			glTexCoord2f(0.0f,rh);		glVertex3f(x + width , y + height , z			);
		glEnd();

	}

	void draw_lift		(float x , float y , float z , float length , float width  , float height  ){

								///  back 
	
				draw_rectangle( x			  , y +((3*height)/4)  , z 	  ,  width	    , (height/4)	    ,	stairsc ,floorf(width/10)	,floorf(height/10)	    );			//عتبة
				
				float dodo = 0 ;
				float toto = ((3*height)/4) ;
				for ( int i = 0 ; i <= global_num_floor ; i++ ){             /////     انو بكل طابق يفتح الباب لحال 
				if ( eyeX >= x && eyeX <=  (x + width ) && eyeZ >= z - 14  && eyeZ <= (z +3)  && eyeY >= 0 && eyeY <= (height * (global_num_floor + 1)) ){
					draw_rectangle( x 			  , y				   , z    ,		0		, ((3*height)/4)	,	leftliftDoor  , 1	, 1		);			//باب يسار
					draw_rectangle( x + (width/2) , y				   , z    ,		0		, ((3*height)/4)    ,	rightliftDoor , 1	, 1		);			//باب يمين	
				}
				else{
					draw_rectangle( x 			  , y				   , z    ,	(width / 2)	, ((3*height)/4)	,	leftliftDoor  , 1	, 1		);			//باب يسار
					draw_rectangle( x + (width/2) , y				   , z    ,	(width / 2)	, ((3*height)/4)    ,	rightliftDoor , 1	, 1		);			//باب يمين
				}
					dodo+=height;
					toto+=height;
				}

				int counter = 0 ;
				for (int j = 48 ; j <= 57 ; j++ ){
					
					if (keys[j] && eyeX >= x && eyeX <=  (x + width ) && eyeZ >= z - 25  && eyeZ <= (z +3)  && eyeY >= 0 && eyeY <= (height * (global_num_floor +1)))
						eyeY = 5 + (height*counter);
					counter++;

				}

				glBindTexture(GL_TEXTURE_2D, insideLift); //front
				glBegin(GL_QUADS); 
					glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width	, y			, length );
					glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width	, y + height, length ); 
					glTexCoord2f(0.0f, 1.0f); glVertex3f(x			, y + height, length );
					glTexCoord2f(0.0f, 0.0f); glVertex3f(x			, y			, length );
				glEnd();

				glBindTexture(GL_TEXTURE_2D, insideLift);  //right
				glBegin(GL_QUADS);  
					glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width	, y			, z		 );
					glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width	, y			, length );
					glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width	, y + height, length ); 
					glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width	, y + height, z		 );
				glEnd();

				glBindTexture(GL_TEXTURE_2D, insideLift); //left
				glBegin(GL_QUADS);      
					glTexCoord2f(1.0f, 1.0f); glVertex3f(x			, y + height, z		 ); 
					glTexCoord2f(0.0f, 1.0f); glVertex3f(x			, y + height, length ); 
					glTexCoord2f(0.0f, 0.0f); glVertex3f(x			, y			, length );
					glTexCoord2f(1.0f, 0.0f); glVertex3f(x			, y			, z		 );     
				glEnd();

				glBindTexture(GL_TEXTURE_2D, insideLift);  // top 
				glBegin(GL_QUADS);      
					glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width	, y + height, z		 );
					glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width	, y + height, length ); 
					glTexCoord2f(1.0f, 1.0f); glVertex3f(x			, y + height, length );
					glTexCoord2f(0.0f, 1.0f); glVertex3f(x			, y + height, z		 );
				glEnd();

	}
	
	void draw_room		(float x , float y , float z , float length , float width  , float height  )
	{
										// back wall

			draw_rectangle( x				   , y				 , z + length	,  width / 3	,  height    ,	bulid_imagec , floorf(width/10)	, floorf(height/10)		);			//حيط يسار
			draw_rectangle( x +(width / 3) * 2 , y				 , z + length	,  width / 3	,  height    ,	bulid_imagec , floorf(width/10)	, floorf(height/10)		);			//حيط يمين
			draw_rectangle( x +(width / 3)	   , y +(height/3)*2 , z + length	,  width / 3	,  height/3  ,	floor_wallsc , floorf(width/10)	, floorf(height/10)		);			//عتبة فوق
			draw_rectangle( x +(width/3)       , y				 , z + length	,  width / 3	,  height/3  ,	floor_wallsc , floorf(width/10)	, floorf(height/10)		);			//عتبة تحت


										// front wall

			draw_rectangle( x				   , y				 , z 			,  width / 3	,  height	 ,	wallPaperc  , floorf(width/10)	, floorf(height/10)		);			//حيط يسار
			draw_rectangle( x +(width / 3) * 2 , y				 , z			,  width / 3	,  height	 ,	wallPaperc  , floorf(width/10)	, floorf(height/10)		);			//حيط يمين
			draw_rectangle( x +(width / 3)	   , y +(height/3)*2 , z 			,  width / 3	,  height/3	 ,	wallPaperc  ,		2		    ,		  2				);			//عتبة فوق

			if ( eyeX >= x + (width/3) &&  eyeX <= x + ((width/3)*2) &&  eyeZ <=  z+10 && eyeZ >= z-20 &&  eyeY >= y &&  eyeY <=(y+(height/3)*2)){
				draw_Quad( x +((width/3)*2)		,  y , z ,  (width / 3) , 0.1 ,((height/3)*2), doorRoomc , 1 , 1 , 1 );
			}
			else
				draw_rectangle( x +(width / 3)  , y  , z ,  (width / 3)	, ((height/3)*2)	 , doorRoom ,  1 , 1	 );			//باب 

			
										//left wall
			
			glBindTexture(GL_TEXTURE_2D, wallPaper); 
		    glBegin(GL_QUADS);      
			glTexCoord2f(floorf( length/10), floorf( height/10));	 glVertex3f(x+0.5 , y + height , z					); 
			glTexCoord2f(0.0f, floorf( height/10));					 glVertex3f(x+0.5 , y + height , z + length			); 
			glTexCoord2f(0.0f, 0.0f);								 glVertex3f(x+0.5 , y		   , z + length			);
			glTexCoord2f(floorf( length/10), 0.0f);					 glVertex3f(x+0.5 , y		   , z					);     
		    glEnd();
				 
				                       //right wall

			glBindTexture(GL_TEXTURE_2D, wallPaper); 
			glBegin(GL_QUADS);      
			glTexCoord2f(floorf( length/10), floorf( height/10));	 glVertex3f(x+(((width / 3) * 2)+width/3)-0.5, y + height, z	      ); 
			glTexCoord2f(0.0f, floorf( height/10));					 glVertex3f(x+(((width / 3) * 2)+width/3)-0.5, y + height, z + length ); 
			glTexCoord2f(0.0f, 0.0f);								 glVertex3f(x+(((width / 3) * 2)+width/3)-0.5, y		 , z + length );
			glTexCoord2f(floorf( length/10), 0.0f);					 glVertex3f(x+(((width / 3) * 2)+width/3)-0.5, y		 , z		  );     
		    glEnd();

									// models

			sofa.pos.x = x +(width/2) ;
			sofa.pos.y = y+0.1 ;
			sofa.pos.z =	z + length - 25 ;
			sofa.scale = 2.5 ;								//// not dynamic
			sofa.Draw();

			table.pos.x = x +(width/2) ;
			table.pos.y = y+0.2 ;
			table.pos.z = z + length - 15 ;
			table.scale = 3.75 ;							//// not dynamic
			table.Draw();

			Dresser.pos.x = x + 3.3  ;
			Dresser.pos.y = y+3.3 ;
			Dresser.pos.z = z + (length/2) ;
			Dresser.scale = 0.03 ;						 //// not dynamic
			Dresser.Draw();

			draw_Quad( x+(width/4) , y+0.2 , z+(length/4) , (length/2) , (width/2) , 0.1 , sjada , 1 , 1 , 1 );  // السجادة


			

					// left wall door

			if ( eyeX <= x + (width/3) && eyeX >= x &&  eyeY <= (height*(global_num_floor+1))   && eyeY >= y)
			{
				if (eyeZ <= z - 5 && eyeZ >= z - 15 )
					eyeZ = z - 20 ;
				if (eyeZ <= z + 5 && eyeZ >= z  + 1 )
					eyeZ = z + 7  ;
			}

			// right wall door

			if ( eyeX <= x +width && eyeX >= x + ((width/3)*2) &&  eyeY <= (height*(global_num_floor+1))   && eyeY >= y)
			{
				if (eyeZ <= z - 5 && eyeZ >= z - 15 )
					eyeZ = z - 20 ;
				if (eyeZ <= z + 5 && eyeZ >= z  + 1 )
					eyeZ = z + 7  ;
			}

			//  wall room

			if ( eyeZ <= z+length && eyeZ >= z ){
				if ( eyeX <= x + 5  && eyeX >= x + 1  )
					eyeX = x + 8 ; 
				if ( eyeX <= x + width  - 1 && eyeX >= x + width - 5 )
					eyeX = x + width - 8 ;
			}





	}
			
};






						///////////////    Main    //////////////

int z = s.z+100;
int x = s.x+90;
void DrawGLScene(GLvoid)								// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix
	Key(keys);
	gluLookAt(eyeX, eyeY, eyeZ, eyeX + cos(angel), eyeY, eyeZ + sin(angel), 0, 1, 0);
	glTranslated(0,0,-10);
	////////////////////////////////////////////////////////////////////
	s.draw();

	Playsound();
	
	car.pos.x= x;
	car.pos.y = 12;
	car.pos.z = z/*side_pass.z+100*/;
	car.scale = 0.4;
	car.Draw();
	z+=4;
	if(z > -s.z-85 ){
		car.rot.y = 90;
		//if(z!= -s.z-85)
		z-=4;
		x+=4;
	}
	if (x > -s.x-90)
	{
		
		car.rot.y = 180;
		z-=8;
	}
	if(z <s.z +95)
	{
		car.rot.y=270;
		z-=4;
		x-=4;
		
	}
	if (x < s.x+90)
	{
		car.rot.y = 360;
		x+=4;
		z+=4;
	}
	
	wall side_walls(s.x+10,s.y,s.z+10,s.x+10,s.height/8,s.z+10,s.x+10,s.height/8,(s.length/2)-10,s.x+10,s.y,(s.length/2)-10,walls,floor((s.length)/100),floor((s.height/4)/100));
	side_walls.draw();
	side_walls.x = -1*side_walls.x;
	side_walls.a = -1*side_walls.a;
	side_walls.d = -1*side_walls.d;
	side_walls.g = -1*side_walls.g;
	side_walls.draw();
	wall front_wall(s.x+10,s.y,s.z+10,s.x+10,side_walls.b,s.z+10,-s.x-10,side_walls.b,s.z+10,-s.x-10,s.y,s.z+10,walls,floor((s.length)/100),floor((s.height/4)/100));
	front_wall.draw();
	front_wall.z = -1*front_wall.z;
	front_wall.c = -1*front_wall.c;
	front_wall.f = -1*front_wall.f;
	front_wall.i = -1*front_wall.i;
	front_wall.draw();

	/////////////////////////////////////////////////////////////////

	bulding side_pass(-side_walls.x,side_walls.y,side_walls.z,floor((side_walls.b-side_walls.y)/2),side_walls.z-side_walls.f,4,2,2/*floor(((s.z)-(s.length/2))/100)*/,floor(((s.z)-(s.length/2))/100),rasif,corner2,1,floor(((s.z)-(s.length/2))/100));
	side_pass.draw();
	side_pass.x = -side_pass.x;
	side_pass.width = -1*side_pass.width;
	side_pass.draw();
	bulding front_pass(front_wall.x,front_wall.y,front_wall.z,front_wall.i-front_wall.x,floor((side_walls.b-side_walls.y)/2),4,2,floor(((s.z)-(s.length/2))/100),2/*floor(((s.z)-(s.length/2))/100)*/,rasif,corner2,1,floor(((s.z)-(s.length/2))/100));
	front_pass.draw();
	front_pass.z = -1*front_pass.z;
	front_pass.length = -front_pass.length;
	front_pass.draw();
	bulding midlle_pass(+side_pass.x+side_pass.width+side_pass.width/2,0,-side_pass.z+front_pass.length+side_pass.width/2,-((-side_pass.z+front_pass.length+side_pass.width/2)-front_pass.z+front_pass.length+side_pass.width/2),(-side_pass.z+front_pass.length+side_pass.width/2)-front_pass.z+front_pass.length+side_pass.width/2,4,1,1,1,rasif,rasif,floor(((s.z)-(s.length/2))/100),floor(((s.z)-(s.length/2))/100));
	midlle_pass.draw();

	/////////////////////////////////////////////////////////////////

	bulding street(side_pass.x+side_pass.width,0,side_walls.z,side_pass.width/2,side_walls.z-side_walls.f,4,2,2/*floor(((s.z)-(s.length/2))/100)*/,floor(((s.z)-(s.length/2))/100),corner,corner,1,floor(((s.z)-(s.length/2))/100));
	street.draw();
	street.x = -street.x;
	street.width = -street.width;
	street.draw();
	street.width = front_pass.width;
	street.length = side_pass.width/2;
	street.x = front_pass.x;
	street.z = front_pass.z-front_pass.length;
	street.draw();
	street.z = - street.z;
	street.length = -street.length;
	street.draw();
	/////////////////////////////////////////////////////////////////

	MainBuilding main_building(0+midlle_pass.width/8,4,midlle_pass.z-floor(midlle_pass.length/10)-midlle_pass.length/2,abs(midlle_pass.width/4),abs(midlle_pass.length/4));
	main_building.draw(3);


	numberOfBuilding=43;
	numberOfTrees=83;
	int numberOfTreesBerPass = numberOfTrees / 4;
	int validspace = (side_pass.length-(0.25*side_pass.length)-2*(front_pass.length));
	int numberOfBuildingBerPass = numberOfBuilding / 4;
	int distspace = 0.25*side_pass.length-front_pass.length/2 ;
	distspace  /= numberOfBuildingBerPass;
	bulding random_bulding(side_pass.x+side_pass.width-floor(side_pass.width/5),4,-s.z-10+front_pass.length+distspace,-side_pass.width+floor(side_pass.width/5)-2,-validspace/numberOfBuildingBerPass,s.height/4,5,1,1,faceOfBuilding,wallsForBuilding,floor((s.height/4)/10),floor((s.height/4)/10));
	/*for draw side building*/
	for(int i=0;i<numberOfBuildingBerPass*2;i++)
	{
		random_bulding.draw();                                                     
		random_bulding.x=-random_bulding.x; 
		if(i%2!=0)
			random_bulding.z-=random_bulding.length-distspace;
		random_bulding.width=-random_bulding.width;
	}
	tree.pos.x = side_pass.x+side_pass.width-floor(side_pass.width/18);
	tree.pos.y = 4;
	tree.pos.z = side_pass.z-front_pass.length-floor((side_pass.length-2*front_pass.length)/numberOfTreesBerPass)/*-(distspace-side_pass.length/numberOfTrees)*/;
	tree.scale = 2;
	for(int i = 0; i<numberOfTreesBerPass*2 ; i++){
		tree.Draw();
		if(i%2!=0)
			tree.pos.z -=floor((side_pass.length-2*front_pass.length)/numberOfTreesBerPass);/*random_bulding.length-2*distspace/numberOfTrees;*/
		tree.pos.x = -tree.pos.x;
		
	}
	/*for drawing front passes*/
	random_bulding.x = -s.x+10+side_pass.width+distspace;
	random_bulding.y = 4;
	random_bulding.z = front_pass.z-front_pass.length+floor(front_pass.length/4);
	random_bulding.length = -front_pass.length+floor(front_pass.length/4)-2;
	random_bulding.width = validspace / numberOfBuildingBerPass;
	random_bulding.number = 3;
	for(int i=0;i<numberOfBuildingBerPass*2;i++){
		random_bulding.draw();
		if(i%2!=0)
			random_bulding.x+=random_bulding.width+distspace;
		random_bulding.z = -random_bulding.z;
		random_bulding.length = -random_bulding.length;
		
	}

	tree.pos.x = front_pass.x-side_pass.width-floor((side_pass.length-2*front_pass.length)/numberOfTreesBerPass);
	tree.pos.y = 2;
	tree.pos.z = front_pass.z-front_pass.length+floor(front_pass.length/18);
	for(int i = 0; i<numberOfTreesBerPass*2 ; i++){
		tree.Draw();
		if(i%2!=0)
			tree.pos.x -=floor((side_pass.length-2*front_pass.length)/numberOfTreesBerPass);/*random_bulding.length-2*distspace/numberOfTrees;*/
		tree.pos.z = -tree.pos.z;
		
	}

	int remainBuilding = numberOfBuilding % 4;
	int distanceBetweenSideBuilding =0;
	if (remainBuilding!=0)
	{
		int length = (midlle_pass.length-midlle_pass.length/4)/remainBuilding;
		random_bulding.number = 5;
		distanceBetweenSideBuilding = (midlle_pass.length/4)/remainBuilding;
		random_bulding.length = length;
		random_bulding.height =random_bulding.height/2;
		random_bulding.x = midlle_pass.x+floor(midlle_pass.width/25);
		random_bulding.y = 3.1;
		random_bulding.z =midlle_pass.z-distanceBetweenSideBuilding; 
		for (int i = 0; i < remainBuilding; i++)
		{
			
			random_bulding.draw();
			random_bulding.x = -random_bulding.x;
			random_bulding.width = -random_bulding.width;
			if(i%2!=0)
				random_bulding.z = random_bulding.z - abs(distanceBetweenSideBuilding) - abs(random_bulding.length); 
		}
	}



	int remainTrees = numberOfTrees % 4;
	if(remainTrees!=0)
	{
		int lengthForTree = (midlle_pass.length-midlle_pass.length/4)/remainTrees;
			tree.pos.x = midlle_pass.x+floor(midlle_pass.width/25);
			tree.pos.y = 3 ;
			tree.pos.z = midlle_pass.z-distanceBetweenSideBuilding-random_bulding.length -(distanceBetweenSideBuilding/2);
			for (int i = 0; i < remainTrees; i++)
			{
				tree.Draw();
				tree.pos.x = - tree.pos.x;
				if (i%2!=0)
					tree.pos.z = tree.pos.z - distanceBetweenSideBuilding - random_bulding.length;
			}
	}


	

	numberOfStreets = 8;
	int valid_space_for_street = (midlle_pass.width +(main_building.width)+10)/2;
	int dist_space_for_street = midlle_pass.width/2;
	dist_space_for_street /= numberOfStreets;
	bulding random_streets((-midlle_pass.width/8)+10,0,midlle_pass.z,-valid_space_for_street/numberOfStreets,midlle_pass.length+1,4,1,1,1,corner,corner,floor((validspace/numberOfStreets)/100),floor((midlle_pass.length)/100));
	for(int i=0;i<numberOfStreets;i++){
		random_streets.draw();
		if(i%2!=0)
			random_streets.x = random_streets.x+dist_space_for_street;
		random_streets.x = -random_streets.x;
		random_streets.width = -random_streets.width;
	}

	numberOfStreetLamp = 40;
	numberOfStreetLamp -=2;
	numberOfStreetLamp/= 2;
	lamp.pos.x = midlle_pass.x-4;
	lamp.pos.y = 34;
	lamp.pos.z = midlle_pass.z-midlle_pass.length+4;
	for(int i=0;i<numberOfStreetLamp*2+2;i++){
		lamp.Draw();
		if(i==numberOfStreetLamp*2)
			lamp.pos.z = lamp.pos.z-8;
		if(i%2!=0)
			lamp.pos.z = lamp.pos.z+(midlle_pass.length/numberOfStreetLamp);
		lamp.pos.x = -lamp.pos.x;
		
	}
	barkingCar.pos.x = main_building.x+main_building.width/8;
	barkingCar.pos.y = 10;
	barkingCar.pos.z = main_building.length/2+ main_building.length/3-15;
	barkingCar.scale = 0.3;
	barkingCar.rot.y = 90;

	numberOfCar = 16;
	for (int i = 0; i < numberOfCar; i++)
	{
		barkingCar.Draw();
		barkingCar.pos.x = -barkingCar.pos.x;
		barkingCar.rot.y = -barkingCar.rot.y;
		if(i%2!=0)
			barkingCar.pos.z = barkingCar.pos.z+30;
		
	}

	/////////////////////////////////////////////////////////////////
	glFlush();
	SwapBuffers(hDC);
}








































GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

																	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = FALSE;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

														// Ask The User Which Screen Mode They Prefer
														//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	//(LPCWSTR)
	if (!CreateGLWindow("NeHe Template", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 50, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}
