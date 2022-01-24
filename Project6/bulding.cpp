#include "bulding.h"
class bulding
{
	private:
	float x,y,z;
	double length,width,height;
	int img1;
	int number;

public:
	bulding(float x1, float y1, float z1,double width1, double length1,double height1,int number1,int img2){
		x=x1;
		y=y1;
		z=z1;
		width=width1;
		length=length1;
		height=height1;
		img1=img2;
		number=number1;
	}
	void draw(){
		glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);


	//glColor3f(1.0f, 0.5f, 0.0f);    // Color Orange
	
	

	if(number == 1){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,img1);
		glTexCoord2d(0,0);
		glVertex3f(x, y, z); 
		glTexCoord2d(1,0);
		glVertex3f(x+length, y, z);
		glTexCoord2d(1,1);
		glVertex3f(x+length, y, z-width);// Bottom Left Of The Quad (Bottom)
		glTexCoord2d(0,1);
		glVertex3f(x, y, z-width);    // Bottom Right Of The Quad (Bottom)
		glDisable(GL_TEXTURE_2D);
	}else{
	glVertex3f(x, y, z);    // Top Right Of The Quad (Bottom)
	glVertex3f(x+length, y, z);    // Top Left Of The Quad (Bottom)
	glVertex3f(x+length, y, z-width);    // Bottom Left Of The Quad (Bottom)
	glVertex3f(x, y, z-width);    // Bottom Right Of The Quad (Bottom)
	}
	if (number == 2)
	{
		glBindTexture(GL_TEXTURE_2D,img1);
		glTexCoord2d(0,0);
		glVertex3f(x, y+height, z); 
		glTexCoord2d(1,0);
		glVertex3f(x+length, y+height , z);
		glTexCoord2d(1,1);
		glVertex3f(x+length, y+height, z-width);
		glTexCoord2d(0,1);
		glVertex3f(x, y+height, z-width);
	}
	else
	{

//	glColor3f(0.2f ,0.5f, 0.6f);    // Color Blue
	glVertex3f(x, y+height, z);    // Top Right Of The Quad (Top)
	glVertex3f(x+length, y+height, z);    // Top Left Of The Quad (Top)
	glVertex3f(x+length, y+height, z-width);    // Bottom Left Of The Quad (Top)
	glVertex3f(x, y+height, z-width);    // Bottom Right Of The Quad (Top)
	}

//	glColor3f(1.0f, 0.0f, 0.0f);    // Color Red    
	if(number ==3)
	{
		glBindTexture(GL_TEXTURE_2D,img1);
		glTexCoord2d(0,0);
		glVertex3f(x, y, z);    // Top Right Of The Quad (Front)
		glTexCoord2d(1,0);
		glVertex3f(x+length, y, z);    // Top Left Of The Quad (Front)
		glTexCoord2d(1,1);
		glVertex3f(x+length, y+height, z);    // Bottom Left Of The Quad (Front)
		glTexCoord2d(0,1);
		glVertex3f(x, y+height, z);    // Bottom Right Of The Quad (Front)
		glDisable(GL_TEXTURE_2D);
	}
	else
	{
		glVertex3f(x, y, z);    // Top Right Of The Quad (Front)
		glVertex3f(x+length, y, z);    // Top Left Of The Quad (Front)
		glVertex3f(x+length, y+height, z);    // Bottom Left Of The Quad (Front)
		glVertex3f(x, y+height, z);    // Bottom Right Of The Quad (Front)
	}
	

	//glColor3f(1.0f, 1.0f, 0.0f);    // Color Yellow
	if(number == 4){
		glBindTexture(GL_TEXTURE_2D,img1);
		glTexCoord2d(0,0);
		glVertex3f(x+length, y, z-width);    
		glTexCoord2d(1,0);
		glVertex3f(x, y, z-width);    
		glTexCoord2d(1,1);
		glVertex3f(x, y+height, z-width);   
		glTexCoord2d(0,1);
		glVertex3f(x+length, y+height, z-width);
	}else
	{
	glVertex3f(x+length, y, z-width);    // Top Right Of The Quad (Back)
	glVertex3f(x, y, z-width);    // Top Left Of The Quad (Back)
	glVertex3f(x, y+height, z-width);    // Bottom Left Of The Quad (Back)
	glVertex3f(x+length, y+height, z-width);    // Bottom Right Of The Quad (Back)
	}

	//glColor3f(0.0f, 0.0f, 1.0f);    // Color Blue
	if(number ==5){
		glBindTexture(GL_TEXTURE_2D,img1);
		glTexCoord2d(0,0);
		glVertex3f(x, y, z);    
		glTexCoord2d(1,0);
		glVertex3f(x, y, z-width);
		glTexCoord2d(1,1);
		glVertex3f(x, y+height, z-width);
		glTexCoord2d(0,1);
		glVertex3f(x, y+height, z);
	}else{
	glVertex3f(x, y, z);    // Top Right Of The Quad (Left)
	glVertex3f(x, y, z-width);    // Top Left Of The Quad (Left)
	glVertex3f(x, y+height, z-width);    // Bottom Left Of The Quad (Left)
	glVertex3f(x, y+height, z);    // Bottom Right Of The Quad (Left)
	}

	//glColor3f(1.0f, 0.0f, 1.0f);    // Color Violet
	if(number ==6){
		glEnable(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D,img1);
		glTexCoord2d(0,0);
		glVertex3f(x+length, y, z);   
		glTexCoord2d(1,0);
		glVertex3f(x+length, y, z-width); 
		glTexCoord2d(1,1);
		glVertex3f(x+length, y+height, z-width);    
		glTexCoord2d(0,1);
		glVertex3f(x+length, y+height, z);
		glDisable(GL_TEXTURE_2D);
	}else
	{
	glVertex3f(x+length, y, z);    // Top Right Of The Quad (Right)
	glVertex3f(x+length, y, z-width);    // Top Left Of The Quad (Right)
	glVertex3f(x+length, y+height, z-width);    // Bottom Left Of The Quad (Right)
	glVertex3f(x+length, y+height, z);    // Bottom Right Of The Quad (Right)
	}


	glEnd();            // End Drawing The Cube

	}


};

