

#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include <cstdlib>


const int WINDOW_WIDTH = 900;
const int WINDOW_HEIGHT = 650;


float car1X = 150;
float car2X = 550;
float person1X = 300;
float person2X = 650;
float cloud1X = 400;
float cloud2X = 600;
float cloud3X = 200;


bool person1Dir = false;  
bool person2Dir = true;   




void drawRect(float x, float y, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}


void drawRectBorder(float x, float y, float w, float h, float r, float g, float b) {
    glColor3f(r, g, b);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}


void drawSmallText(float x, float y, const char* text, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
    }
}

void drawMediumText(float x, float y, const char* text, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void drawLargeText(float x, float y, const char* text, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; ++c) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}




void drawCar(float x, float y, float r, float g, float b) {
   
    drawRect(x, y + 8, 60, 18, r, g, b);
    drawRectBorder(x, y + 8, 60, 18, 0.2f, 0.2f, 0.2f);

  
    drawRect(x + 12, y + 20, 36, 12, r * 0.8f, g * 0.8f, b * 0.8f);
    drawRectBorder(x + 12, y + 20, 36, 12, 0.2f, 0.2f, 0.2f);

   
    drawRect(x + 14, y + 22, 14, 8, 0.6f, 0.8f, 1.0f);
    drawRect(x + 32, y + 22, 14, 8, 0.6f, 0.8f, 1.0f);

  
    drawRect(x + 2, y + 12, 4, 6, 1.0f, 1.0f, 0.5f);
    drawRect(x + 54, y + 12, 4, 6, 1.0f, 0.2f, 0.2f);

    
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + 12 + 8 * cos(angle), y + 8 + 8 * sin(angle));
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + 48 + 8 * cos(angle), y + 8 + 8 * sin(angle));
    }
    glEnd();
}


void drawPersonWalking(float x, float y, bool leftDirection) {
  
    glColor3f(0.9f, 0.7f, 0.5f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + 8 * cos(angle), y + 27 + 8 * sin(angle));
    }
    glEnd();

  
    glColor3f(0.2f, 0.3f, 0.8f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x, y + 18);
    glVertex2f(x, y + 5);
    glEnd();

  
    glBegin(GL_LINES);
    if (leftDirection) {
        glVertex2f(x, y + 14);
        glVertex2f(x - 8, y + 10);
        glVertex2f(x, y + 12);
        glVertex2f(x + 8, y + 6);
    } else {
        glVertex2f(x, y + 14);
        glVertex2f(x + 8, y + 10);
        glVertex2f(x, y + 12);
        glVertex2f(x - 8, y + 6);
    }
    glEnd();


    glBegin(GL_LINES);
    if (leftDirection) {
        glVertex2f(x, y + 5);
        glVertex2f(x - 10, y);
        glVertex2f(x, y + 5);
        glVertex2f(x + 4, y - 2);
    } else {
        glVertex2f(x, y + 5);
        glVertex2f(x + 10, y);
        glVertex2f(x, y + 5);
        glVertex2f(x - 4, y - 2);
    }
    glEnd();
}


void drawBuilding(float x, float y, float w, float h, float r, float g, float b, int floors) {
    
    drawRect(x, y, w, h, r, g, b);
    drawRectBorder(x, y, w, h, 0.1f, 0.1f, 0.1f);

   
    float windowW = 12;
    float windowH = 16;
    float gap = 8;
    float floorHeight = h / floors;

    for (int floor = 0; floor < floors; floor++) {
        float floorY = y + floor * floorHeight + 12;
        for (int windowCol = 0; windowCol < 4; windowCol++) {
            float windowX = x + 15 + windowCol * (windowW + gap);
            if (windowX + windowW < x + w - 15) {
                drawRect(windowX, floorY, windowW, windowH, 0.6f, 0.8f, 1.0f);
                drawRectBorder(windowX, floorY, windowW, windowH, 0.2f, 0.2f, 0.3f);
            }
        }
    }
}


void drawShortBuilding(float x, float y, float w, float h, float r, float g, float b, const char* name) {
 
    drawRect(x, y, w, h, r, g, b);
    drawRectBorder(x, y, w, h, 0.1f, 0.1f, 0.1f);

  
    float windowW = 12;
    float windowH = 14;
    float gap = 6;
    float rows = 2;
    float floorHeight = h / rows;

    for (int row = 0; row < rows; row++) {
        float rowY = y + row * floorHeight + 10;
        for (int col = 0; col < 3; col++) {
            float windowX = x + 12 + col * (windowW + gap);
            if (windowX + windowW < x + w - 12) {
                drawRect(windowX, rowY, windowW, windowH, 0.6f, 0.8f, 1.0f);
                drawRectBorder(windowX, rowY, windowW, windowH, 0.2f, 0.2f, 0.3f);
            }
        }
    }

    
    if (name) {
        drawSmallText(x + w/2 - 15, y + h - 22, name, 1.0f, 1.0f, 1.0f);
    }
}


void drawGarageBuilding(float x, float y, float w, float h, float r, float g, float b) {
    // Main building
    drawRect(x, y, w, h, r, g, b);
    drawRectBorder(x, y, w, h, 0.1f, 0.1f, 0.1f);

   
    float doorX = x + 4;
    float doorY = y + 3;
    float doorW = w - 8;
    float doorH = h - 18;
    drawRect(doorX, doorY, doorW, doorH, 0.25f, 0.25f, 0.25f);
    drawRectBorder(doorX, doorY, doorW, doorH, 0.1f, 0.1f, 0.1f);


    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(1);
    glBegin(GL_LINES);
    for (float lineY = doorY + 6; lineY < doorY + doorH - 4; lineY += 8) {
        glVertex2f(doorX + 2, lineY);
        glVertex2f(doorX + doorW - 2, lineY);
    }
    glEnd();

   
    float winW = 10;
    float winH = 7;
    drawRect(x + 3, y + h - 12, winW, winH, 0.5f, 0.8f, 1.0f);
    drawRectBorder(x + 3, y + h - 12, winW, winH, 0.2f, 0.2f, 0.3f);
    drawRect(x + w - winW - 3, y + h - 12, winW, winH, 0.5f, 0.8f, 1.0f);
    drawRectBorder(x + w - winW - 3, y + h - 12, winW, winH, 0.2f, 0.2f, 0.3f);
}


void drawSmallTree(float x, float y) {
   
    drawRect(x - 2, y, 4, 12, 0.5f, 0.3f, 0.1f);

    
    glColor3f(0.1f, 0.7f, 0.1f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + 15 * cos(angle), y + 15 + 15 * sin(angle));
    }
    glEnd();
}

// Better looking big tree - with natural rounded crown
void drawBigTree(float x, float y) {
  
    drawRect(x - 5, y, 10, 110, 0.45f, 0.28f, 0.12f);

    
    glColor3f(0.08f, 0.55f, 0.08f);

    float leaf[][3] = {
        {0, 130, 28},
        {-20, 118, 24},
        {20, 118, 24},
        {-12, 145, 22},
        {12, 145, 22},
        {0, 160, 20},
        {-28, 138, 20},
        {28, 138, 20}
    };

    for (int i = 0; i < 8; i++) {
        
        if (i % 2 == 0)
            glColor3f(0.08f, 0.55f, 0.08f);
        else
            glColor3f(0.12f, 0.65f, 0.12f);

        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; j += 10) {
            float angle = j * 3.14159f / 180.0f;
            glVertex2f(
                x + leaf[i][0] + leaf[i][2] * cos(angle),
                y + leaf[i][1] + leaf[i][2] * sin(angle)
            );
        }
        glEnd();
    }
}


void drawTreeTop(float x, float y, float r) {
    glColor3f(0.08f, 0.55f, 0.08f);

    for(int i = 0; i < 5; i++) {
        float ox = (i - 2) * 18;
        float oy = (i % 2) * 12;

        
        if (i % 2 == 0)
            glColor3f(0.08f, 0.55f, 0.08f);
        else
            glColor3f(0.12f, 0.65f, 0.12f);

        glBegin(GL_POLYGON);
        for(int j = 0; j < 360; j += 10) {
            float a = j * 3.14159f / 180.0f;
            glVertex2f(
                x + ox + r * cos(a),
                y + oy + r * sin(a)
            );
        }
        glEnd();
    }
}


void drawPerson(float x, float y) {
   
    glColor3f(0.9f, 0.7f, 0.5f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(x + 6 * cos(angle), y + 25 + 6 * sin(angle));
    }
    glEnd();

   
    glColor3f(0.2f, 0.3f, 0.8f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(x, y + 18);
    glVertex2f(x, y + 5);
    glEnd();

    
    glBegin(GL_LINES);
    glVertex2f(x, y + 14);
    glVertex2f(x - 8, y + 8);
    glVertex2f(x, y + 14);
    glVertex2f(x + 8, y + 8);
    glEnd();


    glBegin(GL_LINES);
    glVertex2f(x, y + 5);
    glVertex2f(x - 6, y);
    glVertex2f(x, y + 5);
    glVertex2f(x + 6, y);
    glEnd();
}


void drawChair(float x, float y) {
    
    drawRect(x, y + 12, 20, 4, 0.4f, 0.2f, 0.1f);
    
    drawRect(x + 16, y + 12, 3, 16, 0.4f, 0.2f, 0.1f);
    
    drawRect(x + 2, y, 3, 12, 0.4f, 0.2f, 0.1f);
    drawRect(x + 16, y, 3, 12, 0.4f, 0.2f, 0.1f);
}


void drawTable(float x, float y) {
    
    drawRect(x, y + 16, 50, 4, 0.6f, 0.4f, 0.2f);
   
    drawRect(x + 4, y, 3, 16, 0.6f, 0.4f, 0.2f);
    drawRect(x + 43, y, 3, 16, 0.6f, 0.4f, 0.2f);
}


void drawGroundAndRoad() {
    
    glColor3f(0.2f, 0.2f, 0.2f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(0, 105);
    glVertex2f(WINDOW_WIDTH, 105);
    glEnd();

    
    drawRect(0, 0, WINDOW_WIDTH, 105, 0.55f, 0.35f, 0.15f);

  
    drawRect(0, 0, WINDOW_WIDTH, 65, 0.35f, 0.25f, 0.15f);

    
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2);
    glBegin(GL_LINES);
    for (int i = 0; i < WINDOW_WIDTH; i += 40) {
        glVertex2f(i, 32);
        glVertex2f(i + 20, 32);
    }
    glEnd();

  
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(1.5);
    glBegin(GL_LINES);
    glVertex2f(0, 8);
    glVertex2f(WINDOW_WIDTH, 8);
    glVertex2f(0, 57);
    glVertex2f(WINDOW_WIDTH, 57);
    glEnd();
}


void drawBackground() {
    
    drawRect(0, 105, WINDOW_WIDTH, WINDOW_HEIGHT - 105, 0.6f, 0.8f, 1.0f);

    
    glColor3f(1.0f, 0.9f, 0.2f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i += 10) {
        float angle = i * 3.14159f / 180.0f;
        float cx = 200, cy = 560, r = 35;
        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));
    }
    glEnd();

    
    glColor3f(1.0f, 0.95f, 0.5f);
    glLineWidth(2);
    glBegin(GL_LINES);
    for (int i = 0; i < 12; ++i) {
        float angle = i * 30.0f * 3.14159f / 180.0f;
        float r1 = 42, r2 = 55;
        glVertex2f(200 + r1 * cos(angle), 560 + r1 * sin(angle));
        glVertex2f(200 + r2 * cos(angle), 560 + r2 * sin(angle));
    }
    glEnd();

    
    glColor3f(1.0f, 1.0f, 1.0f);

  
    for (int i = 0; i < 5; i++) {
        float ox = cloud1X + i * 20 - 40;
        float oy = 520 + (i % 3) * 8;
        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; j += 10) {
            float angle = j * 3.14159f / 180.0f;
            glVertex2f(ox + 16 * cos(angle), oy + 10 * sin(angle));
        }
        glEnd();
    }

   
    for (int i = 0; i < 5; i++) {
        float ox = cloud2X + i * 20 - 40;
        float oy = 560 + (i % 3) * 8;
        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; j += 10) {
            float angle = j * 3.14159f / 180.0f;
            glVertex2f(ox + 16 * cos(angle), oy + 10 * sin(angle));
        }
        glEnd();
    }

    
    for (int i = 0; i < 5; i++) {
        float ox = cloud3X + i * 20 - 40;
        float oy = 480 + (i % 3) * 8;
        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; j += 10) {
            float angle = j * 3.14159f / 180.0f;
            glVertex2f(ox + 16 * cos(angle), oy + 10 * sin(angle));
        }
        glEnd();
    }
}


void drawStall(float x, float y, float w, float h, const char* name,
               float r1, float g1, float b1, float r2, float g2, float b2) {
    
    drawRect(x + 3, y - 3, w, 4, 0.45f, 0.45f, 0.45f);

    
    drawRect(x, y, w, h, 0.95f, 0.93f, 0.86f);
    drawRectBorder(x, y, w, h, 0.25f, 0.25f, 0.25f);


    float signH = 26;
    drawRect(x, y + h - signH, w, signH, r2, g2, b2);
    drawRectBorder(x, y + h - signH, w, signH, 0.2f, 0.2f, 0.2f);

  
    drawSmallText(x + w/2 - 12, y + h - signH + 8, name, 1.0f, 1.0f, 1.0f);

    
    drawRect(x - 2, y + h - signH - 6, w + 4, 6, r2, g2, b2);

    
    drawRect(x + 8, y + 30, w - 16, h - 65, 0.70f, 0.88f, 1.0f);
    drawRectBorder(x + 8, y + 30, w - 16, h - 65, 0.35f, 0.35f, 0.35f);

    
    drawRect(x + 5, y + 10, w - 10, 18, 0.55f, 0.35f, 0.18f);
    drawRectBorder(x + 5, y + 10, w - 10, 18, 0.2f, 0.2f, 0.2f);
}



void update(int value) {
    
    car1X += 4.5;
    if (car1X > WINDOW_WIDTH + 60) {
        car1X = -60;
    }

    
    car2X -= 4.0;
    if (car2X < -60) {
        car2X = WINDOW_WIDTH + 60;
    }

   
    person1X += 1.2;
    if (person1X > WINDOW_WIDTH + 30) {
        person1X = -30;
        
    }

    
    person2X -= 1.2;
    if (person2X < -30) {
        person2X = WINDOW_WIDTH + 30;
        
    }

    
    cloud1X += 0.4;
    if (cloud1X > WINDOW_WIDTH + 60) {
        cloud1X = -60;
    }

    cloud2X += 0.3;
    if (cloud2X > WINDOW_WIDTH + 60) {
        cloud2X = -60;
    }

    cloud3X += 0.5;
    if (cloud3X > WINDOW_WIDTH + 60) {
        cloud3X = -60;
    }

    glutPostRedisplay();
    glutTimerFunc(30, update, 0);
}




void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawGroundAndRoad();

    
    drawRect(0, 105, WINDOW_WIDTH, 115, 0.75f, 0.75f, 0.75f);

    
    glColor3f(0.55f, 0.55f, 0.55f);
    glLineWidth(2);
    glBegin(GL_LINES);
    glVertex2f(0, 220);
    glVertex2f(WINDOW_WIDTH, 220);
    glEnd();

   
    glColor3f(0.62f, 0.62f, 0.62f);
    glLineWidth(1);

    glBegin(GL_LINES);

    
    for(int y = 120; y <= 210; y += 15)
    {
        glVertex2f(0, y);
        glVertex2f(WINDOW_WIDTH, y);
    }

   
    for(int x = 0; x <= WINDOW_WIDTH; x += 25)
    {
        glVertex2f(x, 105);
        glVertex2f(x, 220);
    }

    glEnd();

    
    drawBuilding(20, 190, 120, 370, 0.8f, 0.8f, 0.85f, 7);
    drawLargeText(35, 540, "DIU", 0.0f, 0.2f, 0.6f);

   
    drawBigTree(18, 100);
    drawBigTree(52, 105);
    drawBigTree(86, 100);

    drawShortBuilding(140, 220, 80, 100, 0.4f, 0.6f, 0.8f, "CSE");
    drawShortBuilding(140, 320, 80, 100, 0.8f, 0.5f, 0.3f, "EEE");
    

    float fcX = 220, fcY = 205, fcW = 380, fcH = 155;

    
    drawRect(fcX, fcY, fcW, fcH, 0.95f, 0.92f, 0.85f);
    drawRectBorder(fcX, fcY, fcW, fcH, 0.2f, 0.2f, 0.2f);

    
    drawMediumText(fcX + 115, fcY + fcH - 25, "FOOD COURT", 0.0f, 0.2f, 0.6f);

    
    float stallW = 82;
    float stallH = 115;
    float gap = 10;
    float startX = fcX + 10;
    float startY = fcY + 12;

    drawStall(startX, startY, stallW, stallH, "PIZZA",
              0.9f, 0.3f, 0.2f, 0.8f, 0.1f, 0.1f);

    
    drawStall(startX + stallW + gap, startY, stallW, stallH, "BURGER",
              0.9f, 0.6f, 0.1f, 0.8f, 0.5f, 0.0f);

   
    drawStall(startX + 2 * (stallW + gap), startY, stallW, stallH, "NOODLES",
              0.9f, 0.8f, 0.2f, 0.7f, 0.6f, 0.0f);


    drawStall(startX + 3 * (stallW + gap), startY, stallW, stallH, "DRINKS",
              0.3f, 0.6f, 0.9f, 0.1f, 0.4f, 0.8f);

 

    drawTreeTop(675, 290, 34);
    drawTreeTop(725, 287, 33);
    drawTreeTop(775, 292, 34);
    drawTreeTop(825, 286, 33);
    drawTreeTop(880, 289, 34);


    float rightX = fcX + fcW;        
    float smallW = 40;               
    float smallH = 75;               
    float smallY = fcY + 5;          

    
    drawGarageBuilding(rightX, smallY, smallW, smallH, 0.8f, 0.7f, 0.6f);   
    drawGarageBuilding(rightX + smallW + 4, smallY, smallW, smallH, 0.7f, 0.8f, 0.7f);   
    drawGarageBuilding(rightX + 2*(smallW + 4), smallY, smallW, smallH, 0.8f, 0.7f, 0.8f);   
    drawGarageBuilding(rightX + 3*(smallW + 4), smallY, smallW, smallH, 0.7f, 0.8f, 0.8f);   
    drawGarageBuilding(rightX + 4*(smallW + 4), smallY, smallW, smallH, 0.9f, 0.8f, 0.6f);  
    drawGarageBuilding(rightX + 5*(smallW + 4), smallY, smallW, smallH, 0.8f, 0.6f, 0.7f);  
    drawGarageBuilding(rightX + 6*(smallW + 4), smallY, smallW, smallH, 0.6f, 0.8f, 0.6f);   


    drawTable(230, 150);
    drawChair(218, 150);
    drawChair(268, 150);
    drawPerson(222, 154);
    drawPerson(272, 154);

 
    drawTable(320, 150);
    drawChair(308, 150);
    drawChair(358, 150);
    drawPerson(312, 154);
    drawPerson(362, 154);

    
    drawTable(410, 150);
    drawChair(398, 150);
    drawChair(448, 150);
    drawPerson(402, 154);
    drawPerson(452, 154);

    
    drawTable(500, 150);
    drawChair(488, 150);
    drawChair(538, 150);
    drawPerson(492, 154);
    drawPerson(542, 154);

 
    float treeY = 97;
    for (int i = 0; i < 61; i++) {
        float x = i * 15;
        drawSmallTree(x, treeY);
    }

    
    for (int i = 0; i < 62; i++) {
        float x = -4 + i * 15;
        drawSmallTree(x, 84);
    }

 
    drawPersonWalking(person1X, 60, false);


    drawPersonWalking(person2X, 60, true);

   
    drawCar(car1X, 38, 0.9f, 0.2f, 0.2f);

   
    drawCar(car2X, 10, 0.2f, 0.3f, 0.8f);

    glutSwapBuffers();
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27: // ESC
            exit(0);
            break;
    }
}


void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void init() {
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 50);
    glutCreateWindow("Food Court Scene - Animated");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

   
    glutTimerFunc(30, update, 0);

    glutMainLoop();
    return 0;
}
