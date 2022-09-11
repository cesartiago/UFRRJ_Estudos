/***************************************************
12 de marzo del 2011
Arturo Nereu Nunez Martinez
***************************************************/

//#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <math.h>

#define PI 3.1416

bool drawCircle = true;
bool drawTriangle = true;
bool drawVertex = true;
bool drawCenterOfCircle = true;
bool drawVoronoi = true;

// A struct that represents a vertex in 2D
typedef struct Vertex
{
    float x, y;
} Vertex;

// A struct for a CustomCircle created from three vertices
typedef struct CustomTriangle
{
    Vertex *a, *b, *c, circuncentro;
    float radius;

    void calculateCenter(void)
    {
        float x1 = (a->x + b->x) / 2;
        float y1 = (a->y + b->y) / 2;
        float x2 = (a->x + c->x) / 2;
        float y2 = (a->y + c->y) / 2;
        float pm1 = (a->y - b->y) / (a->x - b->x);
        float pm2 = (a->y - c->y) / (a->x - c->x);

        if(pm1 == 0)
            pm1 = 0.000000001f;
        if(pm2 == 0)
            pm2 = 0.000000001f;

        float inv1 = -1/pm1;
        float inv2 = -1/pm2;
        circuncentro.x = (x1 * inv1 - y1 - x2 * inv2 + y2) / (inv1 - inv2);
        circuncentro.y = (circuncentro.x * inv1) - (x1 * inv1) + y1;
    }

    void calculateRadius(void)
    {
        radius = sqrt(pow(a->x - circuncentro.x, 2) + pow(a->y - circuncentro.y, 2));
    }

    void drawCircle(void)
    {
        calculateRadius();
        glColor3f(0, 0, 1);
        glBegin(GL_LINES);
        for(int i = 0; i < 180; i++)
        {
            float x = radius * cos(i) + circuncentro.x;
            float y = radius * sin(i) + circuncentro.y;
            float x1 = radius * cos(i+0.1) + circuncentro.x;
            float y1 = radius * sin(i+0.1) + circuncentro.y;
            glVertex2f(x, y);
            glVertex2f(x1, y1);
        }
        glEnd();
    }

    void drawCenter(void)
    {
        calculateCenter();
        glColor3f(1, 0, 0);
        glBegin(GL_POINTS);
            glVertex2f(circuncentro.x, circuncentro.y);
        glEnd();
    }

    void drawTriangle(void)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(0.2, 0.2, 0.2);
        glBegin(GL_TRIANGLES);
            glVertex2f(a->x, a->y);
            glVertex2f(b->x, b->y);
            glVertex2f(c->x, c->y);
        glEnd();
    }

    bool isVertexInside(Vertex *vertex)
    {
        calculateCenter();
        calculateRadius();

        float distance = sqrt(pow(vertex->x - circuncentro.x , 2) + pow(vertex->y - circuncentro.y, 2));
        return distance <= radius;

    }

    bool isNeighbor(CustomTriangle *posibleNeighbor)
    {
        int numberOfSameVertices = 0;

        bool isSameA = posibleNeighbor->a == a || posibleNeighbor->a == b || posibleNeighbor->a == c;
        bool isSameB = posibleNeighbor->b == a || posibleNeighbor->b == b || posibleNeighbor->b == c;
        bool isSameC = posibleNeighbor->c == a || posibleNeighbor->c == b || posibleNeighbor->c == c;

        if(isSameA) numberOfSameVertices++;
        if(isSameB) numberOfSameVertices++;
        if(isSameC) numberOfSameVertices++;

        if(numberOfSameVertices >= 2)
            return true;
        else
            return false;
    }

    Vertex getCircuncentro(void)
    {
        calculateCenter();
        return circuncentro;
    }
} CustomTriangle;

//Holds the Vertices in the scene
int numberOfVertices = 0;
Vertex **vertexList;
//Holds the Circles in the scene
int numberOfCircles = 0;
CustomTriangle **circlesList;
//Flag for mouse touching feature
int vertexTouched = 0;

//Testing circle
float testingX = 0.0;
float testingY = 0.0;

bool isAnyVertexInsideCircle(CustomTriangle *subject, int v1, int v2, int v3)
{
    for(int i = 0; i < numberOfVertices; i++)
    {
        //Scape the test over the vertices of the current CustomCircle
        if(i == v1 || i == v2 || i == v3)
        {
            continue;
        }
        else
        {
            if(subject->isVertexInside(vertexList[i]))
            {
                return true;
            }
        }
    }

    return false;
}

void insertNewCircle(CustomTriangle *circleToAdd)
{
    numberOfCircles++;
    circlesList = (CustomTriangle **)realloc(circlesList, sizeof(CustomTriangle) * numberOfCircles);
    circlesList[numberOfCircles-1] = circleToAdd;
}

void drawVoronoiCells(void)
{
    glColor3f(0, 0, 0);
    for(int i = 0; i < numberOfCircles; i++)
    {
        for(int j = i + 1; j < numberOfCircles; j++)
        {
            if(circlesList[i]->isNeighbor(circlesList[j]))
            {
                glBegin(GL_LINES);
                    glVertex2f(circlesList[i]->getCircuncentro().x, circlesList[i]->getCircuncentro().y);
                    glVertex2f(circlesList[j]->getCircuncentro().x, circlesList[j]->getCircuncentro().y);
                glEnd();
            }
        }
    }
}

void generateTriangles(void)
{
    bool hasVertexInside = false;

    //Make all the posible combinations of vertices to create valid trigangles
    for(int i = 0; i < numberOfVertices; i++)
    {
        for(int j = i+1; j < numberOfVertices; j++)
        {
            for(int k = j+1; k < numberOfVertices; k++)
            {
                CustomTriangle *tempCircle = (CustomTriangle *)malloc(sizeof(CustomTriangle));
                tempCircle->a = vertexList[i];
                tempCircle->b = vertexList[j];
                tempCircle->c = vertexList[k];

                hasVertexInside = isAnyVertexInsideCircle(tempCircle, i, j, k);

                if(!hasVertexInside)
                    insertNewCircle(tempCircle);
            }
        }
    }
}

void insertVertex(int x, int y)
{
    Vertex *tmp = (Vertex *)malloc(sizeof(Vertex));
    numberOfVertices++;
    tmp->x = x;
    tmp->y = y;

    vertexList = (Vertex **)realloc(vertexList, sizeof(Vertex*) * numberOfVertices);
    vertexList[numberOfVertices-1] = tmp;
}

void initializeGL(void)
{
    glClearColor(1, 1, 1, 1);
}

void drawVertices()
{
    glColor3f(0.5, 0.5, 0.5);
    for(int i = 0; i < numberOfVertices; i++)
    {
        glBegin(GL_POINTS);
            glVertex2f(vertexList[i]->x, vertexList[i]->y);
        glEnd();
    }
}

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);
    glPointSize(5);

    if(drawVertex)
    {
        drawVertices();
    }

    for(int i = 0; i < numberOfCircles; i++)
    {
        if(drawCenterOfCircle)
            circlesList[i]->drawCenter();
        if(drawCircle)
            circlesList[i]->drawCircle();
        if(drawTriangle)
            circlesList[i]->drawTriangle();
    }

    if(drawVoronoi)
        drawVoronoiCells();

    glutSwapBuffers();
}

void resetTriangulation(void)
{
    numberOfCircles = 0;
    circlesList = NULL;
}

void resetProgram(void)
{
    resetTriangulation();
    numberOfVertices = 0;
    vertexList = NULL;
}

void key(unsigned char key, int x, int y)
{
    if(key == 't') drawTriangle = !drawTriangle;
    if(key == 'c') drawCircle = !drawCircle;
    if(key == 'p') drawVertex = !drawVertex;
    if(key == 's') drawCenterOfCircle = !drawCenterOfCircle;
    if(key == 'v') drawVoronoi = !drawVoronoi;
    if(key == 'i') resetProgram();

    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float newX = x - 400;
        float newY = -(y - 300);

        for(int i = 0; i < numberOfVertices; i++)
        {
            if(newX > vertexList[i]->x - 5 && newX < vertexList[i]->x + 5 && newY < vertexList[i]->y + 5 && newY > vertexList[i]->y - 5)
            {
                vertexTouched = i + 1;
                break;
            }
            else
            {
                vertexTouched = 0;
            }
        }
        if(vertexTouched == 0)
        {
            testingX = x - 400;
            testingY = -(y - 300);
            insertVertex(testingX, testingY);
        }

        if(numberOfVertices >= 3)
        {
            resetTriangulation();
            generateTriangles();
        }

        glutPostRedisplay();
    }
}

void mouseMotion(int x, int y){

    if(vertexTouched){
        vertexList[vertexTouched-1]->x = x - 400;
        vertexList[vertexTouched-1]->y = -(y - 300);

        resetTriangulation();
        generateTriangles();
        glutPostRedisplay();
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Cells");
    glutDisplayFunc(draw);
    gluOrtho2D(-400, 400, -300, 300);
    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);
    glutKeyboardFunc(key);

    initializeGL();

    glutMainLoop();
}