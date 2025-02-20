//  engine.h
//  20th of February, 2025
//  Julio Dominguez


#ifndef C3D_H
#define C3D_H
    #define WIDTH 80
    #define HEIGHT 24

    #define MAX_VERTICES 1000
    #define MAX_FACES 2000

    typedef struct {
        int x, y;
    } Point;

    typedef struct {
        float x, y, z;
    } Point3D;

    typedef struct {
        float x, y, z;      // Position
        float yaw, pitch;   // Rotation (in degrees)
        float speed;        // Movement speed
    } Camera;

    extern Camera camera;
    char framebuffer[HEIGHT][WIDTH + 1];

    extern Point3D vertices[MAX_VERTICES];
    extern int faces[MAX_FACES][3];
    extern int vertex_count, face_count;

    Point project_point(Point3D p, Camera cam);
    Point3D rotate_x(Point3D p, float angle);
    Point3D rotate_y(Point3D p, float angle);
    Point3D rotate_z(Point3D p, float angle);

    void load_obj(const char *filename);
    void draw_plot(int x, int y, char c);
    void draw_line(int x0, int y0, int x1, int y1, char c);
#endif