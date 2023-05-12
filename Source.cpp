#include<GL\glut.h>
#include<windows.h>
#include<mmsystem.h>
#include<stdlib.h>
#include<math.h>
#include <GL\freeglut.h>   // handle the window-managing operations
#include <iostream>
#include <stdio.h>

float PI = 3.1415;
float cloud_X = 0;
float cloud_Y = 0;
float cloud_X2 = 0;
float cloud_Y2 = 0;
float position3 = -1.0f;
float speed3 = 0.01f;
float rabbit1 = 0;
float rabbit2 = 0;


void DrawCircle(float cx, float cy, float r, int num_segments)
{
	glBegin(GL_POLYGON);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);
		float x = r * cosf(theta);
		float y = r * sinf(theta);

		glVertex2d(x + cx, y + cy);
	}
	glEnd();
}

void scene()
{
	glPushMatrix();
	glBegin(GL_POLYGON); //Sky
	glColor3f(0.4, 0.5, 1.0);
	glVertex2i(0, 800);
	glVertex2i(1200, 800);
	glColor3f(0.7, 0.7, 1.0);
	glVertex2i(1200, 0);
	glVertex2i(0, 0);
	glEnd();

	glBegin(GL_POLYGON); //Middle ground
	glColor3f(0.0, 0.5, 0.0);
	glVertex2i(0, 200);
	glVertex2i(200, 350);
	glVertex2i(400, 400);
	glVertex2i(600, 350);
	glVertex2i(800, 320);
	glVertex2i(1000, 300);
	glColor3f(0.1, 0.9, 0.1);
	glVertex2i(1200, 200);
	glVertex2i(1200, 100);
	glVertex2i(0, 100);
	glEnd();

	glPopMatrix();
}

void drawSun()
{
	glPushMatrix();
	glColor3f(3.0, 1.0, 0.5);
	DrawCircle(900, 700, 40, 1000);
	glPopMatrix();
}

void drawCloud()
{
	glPushMatrix();
	glTranslatef(cloud_X, 0, 0);
	glColor3f(0.8, 0.8, 0.8);
	DrawCircle(200, 690, 25, 1000); // 1st cloud
	DrawCircle(230, 700, 25, 1000);
	DrawCircle(180, 700, 25, 1000);
	DrawCircle(210, 720, 25, 1000);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(cloud_X2, 0, 0);
	DrawCircle(600, 690, 25, 1000); // 2nd cloud
	DrawCircle(630, 700, 25, 1000);
	DrawCircle(580, 700, 25, 1000);
	DrawCircle(610, 720, 25, 1000);
	glPopMatrix();
}

void cloud()
{
	if (cloud_X > 1100)
		cloud_X = -250;
	else
		cloud_X += 2;
}

void cloud2()
{
	if (cloud_X2 > 1000)
		cloud_X2 = -630;
	else
		cloud_X2 += 1.5;
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, float c1, float c2, float c3, float num) {
	int i;
	int triangleAmount = num; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(c1, c2, c3);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

//draw circle (with colors in diclaration)
void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius, float c1, float c2, float c3) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * PI;

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(c1, c2, c3);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}

void forest()
{
	//grass
	glTranslatef(0, 0, 0);
	glColor3f(0.5f, 0.7f, 0.0f);
	glBegin(GL_POLYGON);
	glVertex2f(-1.0, 0.0 + 0.3);
	glVertex2f(-1.0, -0.3 + 0.3);
	glVertex2f(1.0, -0.3 + 0.3);
	glVertex2f(1.0, 0.0 + 0.3);
	glEnd();

	//------------- road ----------------
	glTranslatef(0, 0, 0);
	glColor3f(0.8f, 0.7f, 0.6f);
	glBegin(GL_POLYGON);
	glVertex2f(1.0, -0.3);
	glVertex2f(-1.0, -0.3);
	glVertex2f(-1.0, -1.0);
	glVertex2f(1.0, -1.0);
	glEnd();

	//------------- line 1 ----------------
	glLineWidth(3.0f);
	//glLineStipple(10, 0x00FF);
	//glEnable(GL_LINE_STIPPLE);
	glBegin(GL_LINES);
	glColor3f(8.0f, 9.0f, 7.0f);
	glVertex2f(1.0, -0.5);
	glVertex2f(-1.0, -0.5);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0,0,0);
	glVertex2f(0.87, -0.3);
	glVertex2f(0.87, -1);
	glVertex2f(0.9, -1);
	glVertex2f(0.9, -0.3);

	glEnd();

	//------------ rock 1 -------------
	drawFilledCircle(-0.5, -0.2 + 0.3, 0.03, 0.5f, 0.5f, 0.5f, 7);

	//------------ rock 2 -------------
	drawFilledCircle(1.0, 0.05 + 0.3, 0.1, 0.5f, 0.5f, 0.5f, 7);

	//------------ rock 3 -------------
	drawFilledCircle(0.4, -0.10 + 0.3, 0.1, 0.5f, 0.5f, 0.5f, 7);

	//------------- tree 1 --------------

	//glTranslatef(-0.0f, 0.0f, 0.0f);
	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.3f, 0.1f);
	glVertex2f(0.73, 0.20 + 0.3);
	glVertex2f(0.67, 0.20 + 0.3);
	glVertex2f(0.67, -0.05 + 0.3);
	glVertex2f(0.73, -0.05 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.4f, 0.0f);
	glVertex2f(0.80, 0.20 + 0.3);
	glVertex2f(0.60, 0.20 + 0.3);
	glVertex2f(0.70, 0.40 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.6f, 0.0f);
	glVertex2f(0.80, 0.34 + 0.3);
	glVertex2f(0.60, 0.34 + 0.3);
	glVertex2f(0.70, 0.54 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.4f, 0.0f);
	glVertex2f(0.80, 0.48 + 0.3);
	glVertex2f(0.60, 0.48 + 0.3);
	glVertex2f(0.70, 0.68 + 0.3);
	glEnd();

	//------------- tree 2 --------------

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.3f, 0.1f);
	glVertex2f(-0.60, 0.0 + 0.3);
	glVertex2f(-0.66, 0.0 + 0.3);
	glVertex2f(-0.66, -0.15 + 0.3);
	glVertex2f(-0.60, -0.15 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.4f, 0.0f);
	glVertex2f(-0.53, 0.0 + 0.3);
	glVertex2f(-0.73, 0.0 + 0.3);
	glVertex2f(-0.63, 0.20 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.6f, 0.0f);
	glVertex2f(-0.53, 0.15 + 0.3);
	glVertex2f(-0.73, 0.15 + 0.3);
	glVertex2f(-0.63, 0.35 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.4f, 0.0f);
	glVertex2f(-0.53, 0.30 + 0.3);
	glVertex2f(-0.73, 0.30 + 0.3);
	glVertex2f(-0.63, 0.50 + 0.3);
	glEnd();



	//------------- tree 3 --------------

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.3f, 0.1f);
	glVertex2f(-0.30, 0.03 + 0.3);
	glVertex2f(-0.35, 0.03 + 0.3);
	glVertex2f(-0.35, -0.07 + 0.3);
	glVertex2f(-0.30, -0.07 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.4f, 0.0f);
	glVertex2f(-0.25, 0.03 + 0.3);
	glVertex2f(-0.40, 0.03 + 0.3);
	glVertex2f(-0.325, 0.23 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.6f, 0.0f);
	glVertex2f(-0.25, 0.18 + 0.3);
	glVertex2f(-0.40, 0.18 + 0.3);
	glVertex2f(-0.325, 0.38 + 0.3);
	glEnd();

	//------------- tree 4 --------------

	glBegin(GL_POLYGON);
	glColor3f(0.5f, 0.3f, 0.1f);
	glVertex2f(0.50, -0.15 + 0.3);
	glVertex2f(0.45, -0.15 + 0.3);
	glVertex2f(0.45, -0.25 + 0.3);
	glVertex2f(0.50, -0.25 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.4f, 0.0f);
	glVertex2f(0.55, -0.15 + 0.3);
	glVertex2f(0.40, -0.15 + 0.3);
	glVertex2f(0.475, 0.0 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.6f, 0.0f);
	glVertex2f(0.55, -0.05 + 0.3);
	glVertex2f(0.40, -0.05 + 0.3);
	glVertex2f(0.475, 0.10 + 0.3);
	glEnd();

	//------------ flower 1 -------------

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0.1f, 0.3f, 0.0f);
	glVertex2f(-0.80, -0.20 + 0.3);
	glVertex2f(-0.80, -0.25 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.4f, 0.5f);
	glVertex2f(-0.79, -0.20 + 0.3);
	glVertex2f(-0.81, -0.20 + 0.3);
	glVertex2f(-0.81, -0.17 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.4f, 0.5f);
	glVertex2f(-0.79, -0.20 + 0.3);
	glVertex2f(-0.81, -0.20 + 0.3);
	glVertex2f(-0.79, -0.17 + 0.3);
	glEnd();

	//------------ flower 2 -------------

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0.1f, 0.3f, 0.0f);
	glVertex2f(-0.90, -0.05 + 0.3);
	glVertex2f(-0.90, 0.0 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.4f, 0.5f);
	glVertex2f(-0.89, 0.0 + 0.3);
	glVertex2f(-0.91, 0.0 + 0.3);
	glVertex2f(-0.91, 0.03 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.4f, 0.5f);
	glVertex2f(-0.89, 0.0 + 0.3);
	glVertex2f(-0.91, 0.0 + 0.3);
	glVertex2f(-0.89, 0.03 + 0.3);
	glEnd();

	//------------ flower 3 -------------

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0.1f, 0.3f, 0.0f + 0.3);
	glVertex2f(0.10, -0.02 + 0.3);
	glVertex2f(0.10, 0.02 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.4f, 0.5f);
	glVertex2f(0.09, 0.02 + 0.3);
	glVertex2f(0.11, 0.02 + 0.3);
	glVertex2f(0.11, 0.05 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.4f, 0.5f);
	glVertex2f(0.09, 0.02 + 0.3);
	glVertex2f(0.11, 0.02 + 0.3);
	glVertex2f(0.09, 0.05 + 0.3);
	glEnd();

	//------------ flower 4 -------------

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0.1f, 0.3f, 0.0f);
	glVertex2f(-0.20, -0.15 + 0.3);
	glVertex2f(-0.20, -0.10 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.4f, 0.5f);
	glVertex2f(-0.19, -0.10 + 0.3);
	glVertex2f(-0.21, -0.10 + 0.3);
	glVertex2f(-0.21, -0.07 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.4f, 0.5f);
	glVertex2f(-0.19, -0.10 + 0.3);
	glVertex2f(-0.21, -0.10 + 0.3);
	glVertex2f(-0.19, -0.07 + 0.3);
	glEnd();

	//------------ flower 5 -------------

	glLineWidth(5.0f);
	glBegin(GL_LINES);
	glColor3f(0.1f, 0.3f, 0.0f);
	glVertex2f(0.78, -0.10 + 0.3);
	glVertex2f(0.78, -0.15 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.4f, 0.5f);
	glVertex2f(0.77, -0.10 + 0.3);
	glVertex2f(0.79, -0.10 + 0.3);
	glVertex2f(0.79, -0.07 + 0.3);
	glEnd();

	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.4f, 0.5f);
	glVertex2f(0.77, -0.10 + 0.3);
	glVertex2f(0.79, -0.10 + 0.3);
	glVertex2f(0.77, -0.07 + 0.3);
	glEnd();

}

void rabbit() {

	glPushMatrix();
	glTranslatef(rabbit1, 0, 0);

	//----------------- head ----------------------
	drawFilledCircle(-0.70, -0.35, 0.04, 1.0, 1.0, 1.0, 9);

	//----------------- body ----------------------
	drawFilledCircle(-0.75, -0.40, 0.07, 1.0, 1.0, 1.0, 9);

	//----------------- eye ----------------------
	drawFilledCircle(-0.68, -0.34, 0.01, 0.1, 0.1, 0.1, 20);

	//----------------- ear ----------------------
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.70, -0.32);
	glVertex2f(-0.72, -0.25);
	glVertex2f(-0.74, -0.26);
	glVertex2f(-0.71, -0.33);
	glEnd();

	//----------------- tail ----------------------
	drawFilledCircle(-0.82, -0.36, 0.02, 1.0, 1.0, 1.0, 5);

	glPopMatrix();
	
	//rabbit2

	glPushMatrix();
	glTranslatef(rabbit2, 0, 0);

	//----------------- head ----------------------
	drawFilledCircle(-0.70, -0.35-0.2, 0.04, 1.0, 1.0, 1.0, 9);

	//----------------- body ----------------------
	drawFilledCircle(-0.75, -0.40 - 0.2, 0.07, 1.0, 1.0, 1.0, 9);

	//----------------- eye ----------------------
	drawFilledCircle(-0.68, -0.34 - 0.2, 0.01, 0.1, 0.1, 0.1, 20);

	//----------------- ear ----------------------
	glBegin(GL_POLYGON);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(-0.70, -0.32 - 0.2);
	glVertex2f(-0.72, -0.25 - 0.2);
	glVertex2f(-0.74, -0.26 - 0.2);
	glVertex2f(-0.71, -0.33 - 0.2);
	glEnd();

	//----------------- tail ----------------------
	drawFilledCircle(-0.82, -0.36 - 0.2, 0.02, 1.0, 1.0, 1.0, 5);

	glPopMatrix();
}


void rabit2()
{

	if(rabbit2<1.6)
		rabbit2 += 0.01;
		
}


void rabit1()
{

	if (rabbit1 < 1)
		rabbit1 += 0.008;

}

void monkey() {


	//Drawing a monkey

	glLineWidth(2.0f);
	//face
	drawFilledCircle(-0.75, -0.1, 0.07, 0.6, 0.4, 0.3, 20);

	//body
	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.4, 0.3);
	glVertex2f(-0.8, -0.25);
	glVertex2f(-0.6875, -0.25);
	glVertex2f(-0.75, -0.1);
	glEnd();

	//ears
	drawFilledCircle(-0.8179, -0.1, 0.0155, 0.6, 0.4, 0.3, 20);
	drawFilledCircle(-0.6821, -0.1, 0.0155, 0.6, 0.4, 0.3, 20);

	//face
	drawFilledCircle(-0.75, -0.1, 0.05, 0.7, 0.6, 0.5, 20);

	//eyes
	drawFilledCircle(-0.71605, -0.096, 0.009, 0, 0, 0, 20);
	drawFilledCircle(-0.78395, -0.096, 0.009, 0, 0, 0, 20);


	//mouth
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.766975, -0.12);
	glVertex2f(-0.75, -0.14);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.733025, -0.12);
	glVertex2f(-0.75, -0.14);
	glEnd();



}

void lion() {

	//drawing a lion

	//body
	glBegin(GL_TRIANGLES);
	glColor3f(0.6, 0.4, 0.3);
	glVertex2f(-0.8 + 0.2, -0.25);
	glVertex2f(-0.6875 + 0.2, -0.25);
	glVertex2f(-0.75 + 0.2, -0.1);
	glEnd();

	//mane
	drawFilledCircle(-0.58, -0.15, 0.03, 0.4, 0.2, 0.1, 20);
	drawFilledCircle(-0.6, -0.1, 0.03, 0.4, 0.2, 0.1, 20);
	drawFilledCircle(-0.58, -0.05, 0.03, 0.4, 0.2, 0.1, 20);


	drawFilledCircle(-0.55, -0.03, 0.03, 0.4, 0.2, 0.1, 20);

	drawFilledCircle(-0.52, -0.15, 0.03, 0.4, 0.2, 0.1, 20);
	drawFilledCircle(-0.52, -0.05, 0.03, 0.4, 0.2, 0.1, 20);
	drawFilledCircle(-0.5, -0.1, 0.03, 0.4, 0.2, 0.1, 20);


	drawFilledCircle(-0.55, -0.1, 0.05, 0.6, 0.4, 0.3, 20);
	//eyes
	drawFilledCircle(-0.51605, -0.096, 0.009, 0, 0, 0, 20);
	drawFilledCircle(-0.58395, -0.096, 0.009, 0, 0, 0, 20);

	//mouth
	drawFilledCircle(-0.55, -0.12, 0.019, 0.4, 0.1, 0.1, 20);
	drawFilledCircle(-0.55, -0.129, 0.009, 0.8, 0, 0.1, 20);

	//nose
	drawFilledCircle(-0.55, -0.1, 0.007, 0, 0, 0, 20);

}

void cat() {

	//drawing a cat

	//body
	glBegin(GL_TRIANGLES);
	glColor3f(0.2, 0.3, 0.5);
	glVertex2f(-0.8 + (2 * 0.2), -0.25);
	glVertex2f(-0.6875 + (2 * 0.2), -0.25);
	glVertex2f(-0.75 + (2 * 0.2), -0.1);
	glEnd();

	drawFilledCircle(-0.55 + 0.2, -0.1, 0.059, 0.2, 0.3, 0.5, 20); //face


	//right ear
	glBegin(GL_TRIANGLES);
	glColor3f(0.2, 0.3, 0.5);
	glVertex2f(-0.8 + (2 * 0.2), -0.1);
	glVertex2f(-0.7 + (2 * 0.2), -0.1);
	glVertex2f(-0.7 + (2 * 0.2), -0.01);
	glEnd();


	//left ear
	glBegin(GL_TRIANGLES);
	glColor3f(0.2, 0.3, 0.5);
	glVertex2f(-0.55 + 0.2, -0.1);
	glVertex2f(-0.8099 + (2 * 0.2), -0.1);
	glVertex2f(-0.81 + (2 * 0.2), -0.01);
	glEnd();

	//eyes
	drawFilledCircle(-0.51605 + 0.2, -0.096, 0.009, 0, 0, 0, 20);
	drawFilledCircle(-0.58395 + 0.2, -0.096, 0.009, 0, 0, 0, 20);

	//nose
	drawFilledCircle(-0.55 + 0.2, -0.112, 0.007, 0, 0, 0, 20);


	//mouth
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.55 + 0.2, -0.12);
	glVertex2f(-0.733025 + (2 * 0.2), -0.14);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.55 + 0.2, -0.12);
	glVertex2f(-0.766975 + (2 * 0.2), -0.14);
	glEnd();




}

void panda() {

	//drawing a panda

	//body
	drawFilledCircle(-0.55 + (2 * 0.2), -0.2, 0.07, 0.9, 0.9, 1, 20);

	drawFilledCircle(-0.55 + (2 * 0.2), -0.1, 0.059, 0.9, 0.9, 1, 20); //face

	//left ear
	drawFilledCircle(-0.59 + (2 * 0.2), -0.05, 0.02, 0, 0, 0, 20);

	//right ear
	drawFilledCircle(-0.51 + (2 * 0.2), -0.05, 0.02, 0, 0, 0, 20);


	//eyes
	drawFilledCircle(-0.51605 + (2 * 0.2), -0.096, 0.02, 0, 0, 0, 20);
	drawFilledCircle(-0.58395 + (2 * 0.2), -0.096, 0.02, 0, 0, 0, 20);


	//nose
	drawFilledCircle(-0.55 + (2 * 0.2), -0.112, 0.007, 0, 0, 0, 20);


	//mouth
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.766975 + (3 * 0.2), -0.12);
	glVertex2f(-0.75 + (3 * 0.2), -0.14);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.733025 + (3 * 0.2), -0.12);
	glVertex2f(-0.75 + (3 * 0.2), -0.14);
	glEnd();

}

void koala() {

	//drawing a koala
	// 
	//body
	glBegin(GL_TRIANGLES);
	glColor3f(0.5, 0.5, 0.6);
	glVertex2f(-0.8 + (4 * 0.2), -0.25);
	glVertex2f(-0.6875 + (4 * 0.2), -0.25);
	glVertex2f(-0.75 + (4 * 0.2), -0.1);
	glEnd();

	//face
	drawFilledCircle(-0.55 + (3 * 0.2), -0.1, 0.059, 0.5, 0.5, 0.6, 20);

	//left ear
	drawFilledCircle(-0.59 + (3 * 0.2), -0.05, 0.02, 0.5, 0.5, 0.6, 20);
	drawFilledCircle(-0.59 + (3 * 0.2), -0.05, 0.009, 0.7, 0.7, 0.8, 20);
	//right ear
	drawFilledCircle(-0.51 + (3 * 0.2), -0.05, 0.02, 0.5, 0.5, 0.6, 20);
	drawFilledCircle(-0.51 + (3 * 0.2), -0.05, 0.009, 0.7, 0.7, 0.8, 20);

	//eyes
	drawFilledCircle(-0.51605 + (3 * 0.2), -0.096, 0.02, 0.7, 0.7, 0.8, 20);
	drawFilledCircle(-0.58395 + (3 * 0.2), -0.096, 0.02, 0.7, 0.7, 0.8, 20);

	drawFilledCircle(-0.51605 + 3 * 0.2, -0.096, 0.008, 0, 0, 0, 20);
	drawFilledCircle(-0.58395 + 3 * 0.2, -0.096, 0.008, 0, 0, 0, 20);

	//nose
	drawFilledCircle(-0.55 + (3 * 0.2), -0.112, 0.007, 0, 0, 0, 20);


	//mouth
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.55 + 3 * 0.2, -0.12);
	glVertex2f(-0.733025 + (4 * 0.2), -0.14);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.55 + 3 * 0.2, -0.12);
	glVertex2f(-0.766975 + (4 * 0.2), -0.14);
	glEnd();

}

void pig() {

	//drawing a pig

	//body
	drawFilledCircle(-0.55 + (4 * 0.2), -0.2, 0.07, 0.8, 0.5, 0.6, 20);

	//face
	drawFilledCircle(-0.55 + (4 * 0.2), -0.1, 0.059, 0.8, 0.5, 0.6, 20);

	//left ear
	glBegin(GL_TRIANGLES);
	glColor3f(0.8, 0.4, 0.5);
	glVertex2f(-0.62 + (4 * 0.2), -0.13);//1
	glVertex2f(-0.59 + (4 * 0.2), -0.13);//2
	glVertex2f(-0.6 + (4 * 0.2), -0.07);//3
	glEnd();


	//right ear
	glBegin(GL_TRIANGLES);
	glColor3f(0.8, 0.4, 0.5);
	glVertex2f(-0.62 + (4 * 0.2) + 0.115, -0.13);//1
	glVertex2f(-0.59 + (4 * 0.2) + 0.12, -0.13);//2
	glVertex2f(-0.6 + (4 * 0.2) + 0.1, -0.07);//3
	glEnd();

	//eyes
	drawFilledCircle(-0.51605 + 4 * 0.2, -0.096, 0.009, 0, 0, 0, 20);
	drawFilledCircle(-0.58395 + 4 * 0.2, -0.096, 0.009, 0, 0, 0, 20);

	//nose
	drawFilledCircle(-0.55 + (4 * 0.2), -0.112, 0.017, 0.8, 0.4, 0.5, 20);
	drawFilledCircle(-0.54 + (4 * 0.2), -0.112, 0.006, 0, 0, 0, 20);
	drawFilledCircle(-0.56 + (4 * 0.2), -0.112, 0.006, 0, 0, 0, 20);
}

void penguin() {
	//drawing a penguin

	//body
	glBegin(GL_TRIANGLES);
	glColor3f(0.1, 0, 0.1);
	glVertex2f(-0.8 + (6 * 0.2), -0.25);
	glVertex2f(-0.6875 + (6 * 0.2), -0.25);
	glVertex2f(-0.75 + (6 * 0.2), -0.1);
	glEnd();

	//face
	drawFilledCircle(-0.55 + (5 * 0.2), -0.1, 0.059, 0.1, 0, 0.1, 20);
	drawFilledCircle(-0.58 + (5 * 0.2), -0.1, 0.019, 1, 1, 1, 20);
	drawFilledCircle(-0.52 + (5 * 0.2), -0.1, 0.019, 1, 1, 1, 20);
	drawFilledCircle(-0.55 + (5 * 0.2), -0.13, 0.0259, 1, 1, 1, 20);


	//eyes
	drawFilledCircle(-0.51605 + 5 * 0.2, -0.096, 0.008, 0, 0, 0, 20);
	drawFilledCircle(-0.58395 + 5 * 0.2, -0.096, 0.008, 0, 0, 0, 20);

	//nose
	glBegin(GL_TRIANGLES);
	glColor3f(0.9, 0.8, 0);
	glVertex2f(-0.564 + (5 * 0.2), -0.1);
	glVertex2f(-0.5515 + (5 * 0.2), -0.14);
	glVertex2f(-0.535 + (5 * 0.2), -0.1);
	glEnd();

}

void dog() {

	//drawing a dog


	//body
	glBegin(GL_TRIANGLES);
	glColor3f(0.7, 0.4, 0.2);
	glVertex2f(-0.8 + (7 * 0.2), -0.25);
	glVertex2f(-0.6875 + (7 * 0.2), -0.25);
	glVertex2f(-0.75 + (7 * 0.2), -0.1);
	glEnd();

	//face
	drawFilledCircle(-0.55 + (6 * 0.2), -0.1, 0.059, 0.7, 0.4, 0.2, 20);

	//left ear
	glBegin(GL_TRIANGLES);
	glColor3f(0.7, 0.4, 0.2);
	glVertex2f(-0.62 + (6 * 0.2), -0.13);//1
	glVertex2f(-0.59 + (6 * 0.2), -0.13);//2
	glVertex2f(-0.6 + (6 * 0.2), -0.07);//3
	glEnd();


	//right ear
	glBegin(GL_TRIANGLES);
	glColor3f(0.7, 0.4, 0.2);
	glVertex2f(-0.62 + (6 * 0.2) + 0.115, -0.13);//1
	glVertex2f(-0.59 + (6 * 0.2) + 0.12, -0.13);//2
	glVertex2f(-0.6 + (6 * 0.2) + 0.1, -0.07);//3
	glEnd();


	//eyes
	drawFilledCircle(-0.51605 + 6 * 0.2, -0.096, 0.008, 0, 0, 0, 20);
	drawFilledCircle(-0.58395 + 6 * 0.2, -0.096, 0.008, 0, 0, 0, 20);

	//nose
	drawFilledCircle(-0.55 + (6 * 0.2), -0.112, 0.007, 0, 0, 0, 20);


	//mouth
	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.55 + 6 * 0.2, -0.12);
	glVertex2f(-0.733025 + (7 * 0.2), -0.14);
	glEnd();


	glBegin(GL_LINES);
	glColor3f(0, 0, 0);
	glVertex2f(-0.55 + 6 * 0.2, -0.12);
	glVertex2f(-0.766975 + (7 * 0.2), -0.14);
	glEnd();


	glBegin(GL_QUADS);
	glColor3f(0.8, 0, 0.2);
	glVertex2f(-0.55 + 6 * 0.2, -0.12);

	glVertex2f(-0.766 + (7 * 0.2), -0.14);

	glVertex2f(-0.55 + 6 * 0.2, -0.16);

	glVertex2f(-0.733 + (7 * 0.2), -0.14);

	glEnd();
}

void bear() {

	//drawing a bear


	//body
	drawFilledCircle(-0.55 + (7 * 0.2), -0.2, 0.07, 0.4, 0.2, 0.1, 20);

	//face
	drawFilledCircle(-0.55 + (7 * 0.2), -0.1, 0.059, 0.4, 0.2, 0.1, 20);


	//eyes
	drawFilledCircle(-0.51605 + 7 * 0.2, -0.096, 0.009, 0, 0, 0, 20);
	drawFilledCircle(-0.58395 + 7 * 0.2, -0.096, 0.009, 0, 0, 0, 20);

	//left ear
	drawFilledCircle(-0.59 + (7 * 0.2), -0.05, 0.02, 0.4, 0.2, 0.1, 20);

	//right ear
	drawFilledCircle(-0.51 + (7 * 0.2), -0.05, 0.02, 0.4, 0.2, 0.1, 20);

	//mouth

	drawFilledCircle(-0.55 + 0.2 * 7, -0.12, 0.019, 0.4, 0.1, 0.1, 20);
	drawFilledCircle(-0.55 + 0.2 * 7, -0.129, 0.009, 0.8, 0, 0.1, 20);


	//nose
	drawFilledCircle(-0.55 + (7 * 0.2), -0.1, 0.007, 0, 0, 0, 20);
}
void crowd() {

	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);

	//drawing the bench
	glBegin(GL_QUADS);
	glColor3f(0.4, 0.3, 0.4);
	glVertex2f(1, -0.3);
	glColor3f(0.4, 0.4, 0.5);
	glVertex2f(1, 0);
	glVertex2f(-1, 0);
	glColor3f(0.4, 0.3, 0.4);
	glVertex2f(-1, -0.3);

	glEnd();


	float x1 = -1;
	float x2 = -0.8875;
	float y1 = -0.1;
	float y2 = -0.25;

	//drawing seat row
	while (x1 < 1) {
		glBegin(GL_QUADS);
		glColor3f(0.09, 0.09, 0.09);
		glVertex2f(x2, y2);
		glVertex2f(x2, y1);
		glVertex2f(x1, y1);
		glVertex2f(x1, y2);

		glEnd();
		x1 = x1 + 0.2;
		x2 = x2 + 0.2;
	}

	//draw monkey
	monkey();

	//drawing lion
	lion();

	//drawing cat
	cat();

	//drawing panda
	panda();

	//drawing koala
	koala();

	//drawing pig
	pig();

	//drawing penguin
	penguin();

	//drawing dog
	dog();

	//drawing bear
	bear();


}



void line() {

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2f(0.0, -1.0);
	glVertex2f(0.0, 1.0);
	glEnd();

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex2f(1.0, 0.0);
	glVertex2f(-1.0, 0.0);
	glEnd();



}



void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	scene();
	drawSun();
	glPushMatrix();
	glTranslatef(600, 400, 0);

	glScalef(600, 530, 0);
	crowd();
	forest();
	rabbit();
	glTranslatef(600, 400, 0);


	glPopMatrix();
	drawCloud();
	cloud();
	cloud2();
	rabbit();
	rabit1();
	rabit2();
	glFlush();
	glutSwapBuffers();


	
}

void timer(int value) {
	glutPostRedisplay();
	glutTimerFunc(100, timer, 0);
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1200, 0, 800, -1, 1);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(10, 10);

	glutInitWindowSize(1200, 650);
	PlaySound(TEXT("voice.wav"), NULL, SND_ASYNC);
	glutCreateWindow("Rabit Race");

	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	init();

	glutDisplayFunc(display);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();

}
