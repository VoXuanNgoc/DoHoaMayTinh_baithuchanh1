// #include <GL/glut.h>
// #include <iostream>
// #include <vector>
// #include <stack>
// using namespace std;

// struct Point {
//     int x, y;
// };

// vector<Point> polygon;
// int winW = 800, winH = 600;

// // Cửa sổ xén
// int clip_xmin = 150, clip_ymin = 150, clip_xmax = 500, clip_ymax = 400;

// //================= CLIPPING (Cohen-Sutherland) =================//
// const int INSIDE = 0; // 0000
// const int LEFT = 1;   // 0001
// const int RIGHT = 2;  // 0010
// const int BOTTOM = 4; // 0100
// const int TOP = 8;    // 1000

// int computeCode(int x, int y) {
//     int code = INSIDE;
//     if (x < clip_xmin) code |= LEFT;
//     else if (x > clip_xmax) code |= RIGHT;
//     if (y < clip_ymin) code |= BOTTOM;
//     else if (y > clip_ymax) code |= TOP;
//     return code;
// }

// void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
//     int code1 = computeCode(x1, y1);
//     int code2 = computeCode(x2, y2);
//     bool accept = false;

//     while (true) {
//         if ((code1 | code2) == 0) { 
//             accept = true;
//             break;
//         } else if (code1 & code2) {
//             break;
//         } else {
//             int codeOut = code1 ? code1 : code2;
//             int x, y;
//             if (codeOut & TOP) {
//                 x = x1 + (x2 - x1) * (clip_ymax - y1) / (y2 - y1);
//                 y = clip_ymax;
//             } else if (codeOut & BOTTOM) {
//                 x = x1 + (x2 - x1) * (clip_ymin - y1) / (y2 - y1);
//                 y = clip_ymin;
//             } else if (codeOut & RIGHT) {
//                 y = y1 + (y2 - y1) * (clip_xmax - x1) / (x2 - x1);
//                 x = clip_xmax;
//             } else {
//                 y = y1 + (y2 - y1) * (clip_xmin - x1) / (x2 - x1);
//                 x = clip_xmin;
//             }
//             if (codeOut == code1) {
//                 x1 = x; y1 = y; code1 = computeCode(x1, y1);
//             } else {
//                 x2 = x; y2 = y; code2 = computeCode(x2, y2);
//             }
//         }
//     }

//     if (accept) {
//         glColor3f(0, 1, 0);
//         glBegin(GL_LINES);
//         glVertex2i(x1, y1);
//         glVertex2i(x2, y2);
//         glEnd();
//     }
// }

// //================= FILLING (Boundary Fill) =================//
// void boundaryFill(int x, int y, float fillColor[3], float borderColor[3]) {
//     unsigned char pixel[3];
//     glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

//     if ((pixel[0] != (unsigned char)(borderColor[0]*255) ||
//          pixel[1] != (unsigned char)(borderColor[1]*255) ||
//          pixel[2] != (unsigned char)(borderColor[2]*255)) &&
//         (pixel[0] != (unsigned char)(fillColor[0]*255) ||
//          pixel[1] != (unsigned char)(fillColor[1]*255) ||
//          pixel[2] != (unsigned char)(fillColor[2]*255))) {

//         glColor3fv(fillColor);
//         glBegin(GL_POINTS);
//         glVertex2i(x, y);
//         glEnd();
//         glFlush();

//         boundaryFill(x+1, y, fillColor, borderColor);
//         boundaryFill(x-1, y, fillColor, borderColor);
//         boundaryFill(x, y+1, fillColor, borderColor);
//         boundaryFill(x, y-1, fillColor, borderColor);
//     }
// }

// //================= DRAW =================//
// void drawClippingWindow() {
//     glColor3f(1, 0, 0);
//     glBegin(GL_LINE_LOOP);
//         glVertex2i(clip_xmin, clip_ymin);
//         glVertex2i(clip_xmax, clip_ymin);
//         glVertex2i(clip_xmax, clip_ymax);
//         glVertex2i(clip_xmin, clip_ymax);
//     glEnd();
// }

// void drawPolygon() {
//     glColor3f(0, 0, 1);
//     glBegin(GL_LINE_LOOP);
//     for (auto &p : polygon) {
//         glVertex2i(p.x, p.y);
//     }
//     glEnd();

//     // Xén từng cạnh (Cohen-Sutherland)
//     for (int i=0; i<polygon.size(); i++) {
//         int j = (i+1) % polygon.size();
//         cohenSutherlandClip(polygon[i].x, polygon[i].y,
//                             polygon[j].x, polygon[j].y);
//     }
// }

// //================= MOUSE =================//
// void mouse(int button, int state, int x, int y) {
//     if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
//         float fillColor[3] = {1, 1, 0};     // vàng
//         float borderColor[3] = {0, 0, 1};   // xanh
//         boundaryFill(x, winH - y, fillColor, borderColor);
//     }
//     glutPostRedisplay();
// }

// //================= FILE READING =================//
// void readPolygonFromFile(const char* filename) {
//     FILE* f = fopen(filename, "r");
//     int x, y;
//     while (fscanf(f, "%d %d", &x, &y) != EOF) {
//         if (x == -1 && y == -1) break;
//         polygon.push_back({x, y});
//     }
//     fclose(f);
// }

// //================= DISPLAY =================//
// void display() {
//     glClear(GL_COLOR_BUFFER_BIT);
//     drawClippingWindow();
//     drawPolygon();
//     glFlush();
// }

// void init() {
//     glClearColor(1, 1, 1, 1);
//     gluOrtho2D(0, winW, 0, winH);
// }

// //================= MAIN =================//
// int main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//     glutInitWindowSize(winW, winH);
//     glutCreateWindow("LAB 02 - Clipping & Filling");

//     init();
//     readPolygonFromFile("polygon.txt");

//     glutDisplayFunc(display);
//     glutMouseFunc(mouse);

//     glutMainLoop();
//     return 0;
// }
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <cstdio>  // cho FILE và fscanf
using namespace std;

struct Point {
    int x, y;
};

vector<Point> polygon;
int winW = 800, winH = 600;
Point fillSeed = {-1, -1};  // Global để lưu seed point từ mouse click

// Clipping window
int clip_xmin = 150, clip_ymin = 150, clip_xmax = 500, clip_ymax = 400;

// Cohen-Sutherland codes
const int INSIDE = 0;
const int LEFT   = 1;
const int RIGHT  = 2;
const int BOTTOM = 4;
const int TOP    = 8;

int computeCode(int x, int y) {
    int code = INSIDE;
    if (x < clip_xmin) code |= LEFT;
    else if (x > clip_xmax) code |= RIGHT;
    if (y < clip_ymin) code |= BOTTOM;
    else if (y > clip_ymax) code |= TOP;
    return code;
}

// so sánh màu có tolerance (tăng tol lên 50 để an toàn với line rendering)
inline bool colorEqual(const unsigned char *a, const unsigned char *b, int tol = 50) {
    return (abs(int(a[0]) - int(b[0])) <= tol) &&
           (abs(int(a[1]) - int(b[1])) <= tol) &&
           (abs(int(a[2]) - int(b[2])) <= tol);
}

// Boundary Fill iterative (cải tiến: dùng 1D vector<char> cho visited nhanh, chỉ push nếu !visited)
void boundaryFillIterative(int sx, int sy, const unsigned char fillColor[3], const unsigned char borderColor[3]) {
    if (sx < 0 || sx >= winW || sy < 0 || sy >= winH) return;

    std::vector<Point> toFill;  // Batch các pixel cần tô
    std::vector<char> visited(winW * winH, 0);  // 1D array nhanh, 0.5MB
    stack<Point> st;
    st.push({sx, sy});

    while (!st.empty()) {
        Point p = st.top(); st.pop();
        int idx = p.x * winH + p.y;
        if (idx < 0 || idx >= (int)visited.size() || visited[idx]) continue;  // out bound hoặc visited

        unsigned char pixel[3];
        glReadPixels(p.x, p.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);

        if (!colorEqual(pixel, fillColor) && !colorEqual(pixel, borderColor)) {
            // Thêm vào batch
            toFill.push_back(p);

            // Push neighbors CHỈ NẾU chưa visited (giảm stack size)
            Point n1 = {p.x + 1, p.y}; int idx1 = n1.x * winH + n1.y;
            if (n1.x < winW && idx1 >= 0 && idx1 < (int)visited.size() && !visited[idx1]) st.push(n1);

            Point n2 = {p.x - 1, p.y}; int idx2 = n2.x * winH + n2.y;
            if (n2.x >= 0 && idx2 >= 0 && idx2 < (int)visited.size() && !visited[idx2]) st.push(n2);

            Point n3 = {p.x, p.y + 1}; int idx3 = n3.x * winH + n3.y;
            if (n3.y < winH && idx3 >= 0 && idx3 < (int)visited.size() && !visited[idx3]) st.push(n3);

            Point n4 = {p.x, p.y - 1}; int idx4 = n4.x * winH + n4.y;
            if (n4.y >= 0 && idx4 >= 0 && idx4 < (int)visited.size() && !visited[idx4]) st.push(n4);
        }

        visited[idx] = 1;  // Mark visited sau check
    }

    // Tô batch một lần
    if (!toFill.empty()) {
        glColor3ub(fillColor[0], fillColor[1], fillColor[2]);
        glBegin(GL_POINTS);
        for (auto& pt : toFill) {
            glVertex2i(pt.x, pt.y);
        }
        glEnd();
    }

    glFlush();
}

// Cohen-Sutherland clipping (giữ nguyên)
void cohenSutherlandClip(int x1, int y1, int x2, int y2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    bool accept = false;

    double sx1 = x1, sy1 = y1, sx2 = x2, sy2 = y2;

    while (true) {
        if ((code1 | code2) == 0) { accept = true; break; }
        else if (code1 & code2) { break; }
        else {
            int codeOut = code1 ? code1 : code2;
            double x=0.0, y=0.0;
            double dx = sx2 - sx1;
            double dy = sy2 - sy1;

            if (codeOut & TOP) {
                x = (fabs(dy) > 1e-9) ? sx1 + dx * (clip_ymax - sy1) / dy : sx1;
                y = clip_ymax;
            } else if (codeOut & BOTTOM) {
                x = (fabs(dy) > 1e-9) ? sx1 + dx * (clip_ymin - sy1) / dy : sx1;
                y = clip_ymin;
            } else if (codeOut & RIGHT) {
                y = (fabs(dx) > 1e-9) ? sy1 + dy * (clip_xmax - sx1) / dx : sy1;
                x = clip_xmax;
            } else { // LEFT
                y = (fabs(dx) > 1e-9) ? sy1 + dy * (clip_xmin - sx1) / dx : sy1;
                x = clip_xmin;
            }

            if (codeOut == code1) {
                sx1 = x; sy1 = y;
                code1 = computeCode(int(round(sx1)), int(round(sy1)));
            } else {
                sx2 = x; sy2 = y;
                code2 = computeCode(int(round(sx2)), int(round(sy2)));
            }
        }
    }

    if (accept) {
        glColor3f(0, 1, 0);  // xanh lá cho clipped lines
        glBegin(GL_LINES);
            glVertex2i(int(round(sx1)), int(round(sy1)));
            glVertex2i(int(round(sx2)), int(round(sy2)));
        glEnd();
    }
}

void drawClippingWindow() {
    glColor3f(1, 0, 0);  // đỏ cho window
    glBegin(GL_LINE_LOOP);
        glVertex2i(clip_xmin, clip_ymin);
        glVertex2i(clip_xmax, clip_ymin);
        glVertex2i(clip_xmax, clip_ymax);
        glVertex2i(clip_xmin, clip_ymax);
    glEnd();
}

void drawPolygon() {
    glColor3ub(0, 0, 255); // xanh dương cho viền (border)
    glLineWidth(2.0f);  // Tăng độ dày line để border rõ hơn, dễ detect
    glBegin(GL_LINE_LOOP);
    for (auto &p : polygon) {
        glVertex2i(p.x, p.y);
    }
    glEnd();
    glLineWidth(1.0f);  // Reset

    // Vẽ clipped segments (xanh lá, dày hơn)
    glLineWidth(2.0f);
    glColor3f(0, 1, 0);
    for (int i = 0; i < (int)polygon.size(); ++i) {
        int j = (i + 1) % polygon.size();
        cohenSutherlandClip(polygon[i].x, polygon[i].y,
                            polygon[j].x, polygon[j].y);
    }
    glLineWidth(1.0f);
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        fillSeed.x = x;
        fillSeed.y = winH - y;  // Flip y
        glutPostRedisplay();
    }
}

void readPolygonFromFile(const char* filename) {
    FILE* f = fopen(filename, "r");
    if (!f) {
        cerr << "Không mở được file polygon.txt, dùng mặc định.\n";
        polygon = {{200, 250}, {450, 250}, {450, 350}, {200, 350}};  // Hình chữ nhật nhỏ bên trong window
        return;
    }
    int x, y;
    polygon.clear();
    while (fscanf(f, "%d %d", &x, &y) != EOF) {
        if (x == -1 && y == -1) break;
        polygon.push_back({x, y});
    }
    fclose(f);
    if (polygon.size() < 3) {
        cerr << "Polygon không hợp lệ, dùng mặc định.\n";
        polygon = {{200, 250}, {450, 250}, {450, 350}, {200, 350}};
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawClippingWindow();
    drawPolygon();

    // Fill nếu có seed (chỉ một lần)
    if (fillSeed.x != -1) {
        unsigned char fillColor[3]   = {255, 255, 0}; // vàng
        unsigned char borderColor[3] = {0, 0, 255};   // xanh dương
        // Kiểm tra seed có phải background không (trắng)
        unsigned char seedPixel[3];
        glReadPixels(fillSeed.x, fillSeed.y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, seedPixel);
        if (colorEqual(seedPixel, (unsigned char[]){255,255,255}, 50)) {  // Chỉ fill nếu là background
            boundaryFillIterative(fillSeed.x, fillSeed.y, fillColor, borderColor);
        } else {
            cerr << "Click vào vùng trắng bên trong polygon để fill!\n";
        }
        fillSeed = {-1, -1};
    }

    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);  // Trắng
    gluOrtho2D(0, winW, 0, winH);
    glDisable(GL_LINE_SMOOTH);
    glLineWidth(1.0f);
    glPointSize(1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("LAB 02 - Clipping & Filling");

    init();
    readPolygonFromFile("polygon.txt");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    cout << "Hướng dẫn: Click chuột vào vùng TRẮNG bên trong polygon để tô vàng. Nếu treo, kiểm tra polygon.txt.\n";

    glutMainLoop();
    return 0;
}