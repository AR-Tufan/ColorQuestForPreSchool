#include <bits/stdc++.h>
#include <GL/glut.h>

using namespace std;
typedef long long int ll;
typedef unsigned long long int ull;
typedef vector<ll>vl;
typedef vector<int>vi;
typedef vector<string>vs;
typedef set<int>si;
typedef map<int,int>mp;
typedef pair<int,int>pii;

// Object structure
struct ColorOption {
    float r, g, b;
    float x, y, width, height;
    string name;
    bool isCorrect;
};

struct GameObject {
    string name;
    float r, g, b; // object color
    float x, y;    // position
};

vector<ColorOption> colorOptions;
vector<GameObject> objects;
string question;
bool showCorrect = false;
bool showWrong = false;
bool transitioning = false;
int currentObjectIndex = 0;

void drawText(float x, float y, const string& text) {
    glRasterPos2f(x, y);
    for (char c : text)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
}

void drawButton(const ColorOption& option) {
    glColor3f(option.r, option.g, option.b);
    glBegin(GL_QUADS);
        glVertex2f(option.x, option.y);
        glVertex2f(option.x + option.width, option.y);
        glVertex2f(option.x + option.width, option.y + option.height);
        glVertex2f(option.x, option.y + option.height);
    glEnd();

    glColor3f(0, 0, 0);
    drawText(option.x + 10, option.y + option.height / 2 - 5, option.name);
}

void drawApple(float x, float y) {
    glColor3f(1.0f, 0.0f, 0.0f); // red
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float angle = i * M_PI / 180;
        glVertex2f(x + cos(angle) * 30, y + sin(angle) * 40);
    }
    glEnd();

    // Stem
    glColor3f(0.4f, 0.2f, 0);
    glBegin(GL_QUADS);
        glVertex2f(x - 3, y + 40);
        glVertex2f(x + 3, y + 40);
        glVertex2f(x + 3, y + 55);
        glVertex2f(x - 3, y + 55);
    glEnd();

    // Leaf
    glColor3f(0.0f, 0.8f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x + 3, y + 55);
        glVertex2f(x + 20, y + 65);
        glVertex2f(x + 10, y + 40);
    glEnd();
}

void drawBanana(float x, float y) {
    glColor3f(1.0f, 1.0f, 0.0f); // yellow
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 180; i++) {
        float angle = i * M_PI / 180;
        glVertex2f(x + cos(angle) * 50, y + sin(angle) * 20);
    }
    for (int i = 180; i >= 0; i--) {
        float angle = i * M_PI / 180;
        glVertex2f(x + cos(angle) * 35, y + sin(angle) * 10 - 10);
    }
    glEnd();
}

void drawSky(float x, float y) {
    glColor3f(0.53f, 0.81f, 0.92f); // sky blue
    glBegin(GL_QUADS);
        glVertex2f(x - 60, y - 30);
        glVertex2f(x + 60, y - 30);
        glVertex2f(x + 60, y + 30);
        glVertex2f(x - 60, y + 30);
    glEnd();

    // Sun
    glColor3f(1.0f, 1.0f, 0);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x + 40, y + 20);
        for (int i = 0; i <= 360; i++) {
            float angle = i * M_PI / 180;
            glVertex2f(x + 40 + cos(angle) * 15, y + 20 + sin(angle) * 15);
        }
    glEnd();
}

void drawRose(float x, float y) {
    // Draw multiple overlapping red petals to simulate a rose bloom
    glColor3f(1.0f, 0.0f, 0.0f);
    for (int i = 0; i < 6; ++i) {
        float angle = i * 60.0f * M_PI / 180.0f;
        float px = x + cos(angle) * 15;
        float py = y + sin(angle) * 15;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(px, py);
        for (int j = 0; j <= 360; ++j) {
            float petalAngle = j * M_PI / 180.0f;
            glVertex2f(
                px + cos(petalAngle) * 15,
                py + sin(petalAngle) * 20
            );
        }
        glEnd();
    }

    glColor3f(0.6f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180;
        glVertex2f(x + cos(angle) * 10, y + sin(angle) * 10);
    }
    glEnd();
}

void drawSunflower(float x, float y) {
    glColor3f(1.0f, 1.0f, 0.0f);
    for (int i = 0; i < 360; i += 30) {
        float angle = i * M_PI / 180;
        float px = x + cos(angle) * 35;
        float py = y + sin(angle) * 35;
        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(px, py);
            for (int j = 0; j <= 360; j++) {
                float petalAngle = j * M_PI / 180;
                glVertex2f(px + cos(petalAngle) * 8, py + sin(petalAngle) * 12);
            }
        glEnd();
    }
    glColor3f(0.5f, 0.25f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= 360; i++) {
            float angle = i * M_PI / 180;
            glVertex2f(x + cos(angle) * 20, y + sin(angle) * 20);
        }
    glEnd();
}

void updateCorrectColor() {
    for (auto& option : colorOptions) {
        option.isCorrect = false;
        if (fabs(option.r - objects[currentObjectIndex].r) < 0.01 &&
            fabs(option.g - objects[currentObjectIndex].g) < 0.01 &&
            fabs(option.b - objects[currentObjectIndex].b) < 0.01) {
            option.isCorrect = true;
        }
    }
}

void nextObject(int value) {
    showCorrect = false;
    transitioning = false;
    currentObjectIndex = (currentObjectIndex + 1) % objects.size();
    updateCorrectColor();
    glutPostRedisplay();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    GameObject obj = objects[currentObjectIndex];
    question = "What is the color of the " + obj.name + "?";
    glColor3f(0, 0, 0);
    drawText(50, 450, question);

    if (obj.name == "apple") drawApple(obj.x, obj.y);
    else if (obj.name == "banana") drawBanana(obj.x, obj.y);
    else if (obj.name == "sky") drawSky(obj.x, obj.y);
    else if (obj.name == "rose") drawRose(obj.x, obj.y);
    else if (obj.name == "sunflower") drawSunflower(obj.x, obj.y);

    for (const auto& option : colorOptions) {
        drawButton(option);
    }

    if (showCorrect) {
        glColor3f(0, 0.6f, 0);
        drawText(200, 100, "Correct! 🎉");
    } else if (showWrong) {
        glColor3f(0.8f, 0, 0);
        drawText(200, 100, "Try Again! ❌");
    }

    glutSwapBuffers();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !transitioning) {
        int windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
        float mx = x;
        float my = windowHeight - y;

        for (auto& option : colorOptions) {
            if (mx >= option.x && mx <= option.x + option.width &&
                my >= option.y && my <= option.y + option.height) {
                if (option.isCorrect) {
                    showCorrect = true;
                    showWrong = false;
                    transitioning = true;
                    glutTimerFunc(1500, nextObject, 0);
                } else {
                    showCorrect = false;
                    showWrong = true;
                }
                glutPostRedisplay();
                return;
            }
        }
    }
}

void setupColors() {
    colorOptions.clear();
    colorOptions.push_back({1, 0, 0, 80, 200, 120, 50, "Red", false});
    colorOptions.push_back({1, 1, 0, 230, 200, 120, 50, "Yellow", false});
    colorOptions.push_back({0.53f, 0.81f, 0.92f, 380, 200, 120, 50, "Blue", false});
    colorOptions.push_back({0.5f, 0.25f, 0.0f, 80, 130, 120, 50, "Brown", false});
}

void setupObjects() {
    objects.clear();
    objects.push_back({"apple", 1.0f, 0.0f, 0.0f, 320, 330});
    objects.push_back({"banana", 1.0f, 1.0f, 0.0f, 320, 330});
    objects.push_back({"sky", 0.53f, 0.81f, 0.92f, 320, 330});
    objects.push_back({"rose", 1.0f, 0.0f, 0.0f, 320, 330});
    objects.push_back({"sunflower", 1.0f, 1.0f, 0.0f, 320, 330});
}

void reshape(int w, int h) {
    // Update the viewport and projection to adapt to window size
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Update button positions and object positions relative to new window size
    // Example: center objects horizontally and position buttons accordingly
    for (auto& obj : objects) {
        obj.x = w / 2.0f;
        obj.y = h * 0.7f;
    }

    // Adjust color options button positions based on window width and height
    float btnWidth = 120.0f;
    float btnHeight = 50.0f;
    float startX = w * 0.1f;
    float startY = h * 0.3f;
    float gapX = 150.0f;

    for (int i = 0; i < (int)colorOptions.size(); i++) {
        colorOptions[i].x = startX + i * gapX;
        colorOptions[i].y = startY;
        colorOptions[i].width = btnWidth;
        colorOptions[i].height = btnHeight;
    }
}

void init() {
    glClearColor(1, 1, 1, 1);
    setupColors();
    setupObjects();
    updateCorrectColor();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Color Learning Game - Apple Example");

    init();

    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}
