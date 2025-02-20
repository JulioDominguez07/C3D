//  main.c
//  20th of February, 2025
//  Julio Dominguez

#include "C3D.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

Camera camera = {
    .x = 0, .y = 0, .z = -150,
    .yaw = 0.0f,  // Initial yaw (faces forward)
    .pitch = 0.0f,
    .speed = 50.0f,
};

Point3D cube[] = {
    { -5, -5, -5 }, {  5, -5, -5 }, {  5,  5, -5 }, { -5,  5, -5 }, // Front face
    { -5, -5,  5 }, {  5, -5,  5 }, {  5,  5,  5 }, { -5,  5,  5 }  // Back face
};

// Triangles
// Each vertex is followed by x, y and z.
Point3D left[] = {
    { -5, -5, 0 },  // Vertex 1
    { -5,  5, 0 },  // Vertex 2
    {  5,  5, 0 }   // Vertex 3
};

Point3D right[] = {
    {  5,  5, 0 },  // Vertex 1
    {  5, -5, 0 },  // Vertex 2
    { -5, -5, 0 }   // Vertex 3
};


void clear_framebuffer() {
    for (int i = 0; i < HEIGHT; i++) {
        memset(framebuffer[i], ' ', WIDTH);
        framebuffer[i][WIDTH] = '\0';
    }
}

void render_frame() {
    for (int i = 0; i < HEIGHT; i++) {
        printf("%s\n", framebuffer[i]);
    }
}

void draw_cube(Camera cam, Point3D cube[], float angle_x, float angle_y, float angle_z, char c) {
    Point rotated[8];
    for (int i = 0; i < 8; i++) {
        Point3D p = cube[i];
        p = rotate_x(p, angle_x); // Rotate around X
        p = rotate_y(p, angle_y); // Rotate around Y
        p = rotate_z(p, angle_z); // Rotate around Z
        rotated[i] = project_point(p, cam); // Project to 2D
    }

    // Draw edges
    draw_line(rotated[0].x, rotated[0].y, rotated[1].x, rotated[1].y, c);
    draw_line(rotated[1].x, rotated[1].y, rotated[2].x, rotated[2].y, c);
    draw_line(rotated[2].x, rotated[2].y, rotated[3].x, rotated[3].y, c);
    draw_line(rotated[3].x, rotated[3].y, rotated[0].x, rotated[0].y, c);

    draw_line(rotated[4].x, rotated[4].y, rotated[5].x, rotated[5].y, c);
    draw_line(rotated[5].x, rotated[5].y, rotated[6].x, rotated[6].y, c);
    draw_line(rotated[6].x, rotated[6].y, rotated[7].x, rotated[7].y, c);
    draw_line(rotated[7].x, rotated[7].y, rotated[4].x, rotated[4].y, c);

    draw_line(rotated[0].x, rotated[0].y, rotated[4].x, rotated[4].y, c);
    draw_line(rotated[1].x, rotated[1].y, rotated[5].x, rotated[5].y, c);
    draw_line(rotated[2].x, rotated[2].y, rotated[6].x, rotated[6].y, c);
    draw_line(rotated[3].x, rotated[3].y, rotated[7].x, rotated[7].y, c);
}

void draw_triangle(Camera cam, Point3D triangle[],float angle_x, float angle_y, float angle_z, char c) {
    Point rotated[3];
    for (int i = 0; i < 3; i++) {
        Point3D p = triangle[i];
        p = rotate_x(p, angle_x); // Rotate around X
        p = rotate_y(p, angle_y); // Rotate around Y
        p = rotate_z(p, angle_z); // Rotate around Z
        rotated[i] = project_point(p, cam); // Project to 2D
    }

    // Draw the edges of the triangle
    draw_line(rotated[0].x, rotated[0].y, rotated[1].x, rotated[1].y, c);
    draw_line(rotated[1].x, rotated[1].y, rotated[2].x, rotated[2].y, c);
    draw_line(rotated[2].x, rotated[2].y, rotated[0].x, rotated[0].y, c);
}

void draw_obj(Camera cam, char c) {
    Point projected[MAX_VERTICES];

    for (int i = 0; i < vertex_count; i++) {
        projected[i] = project_point(vertices[i], cam);
    }

    for (int i = 0; i < face_count; i++) {
        draw_line(projected[faces[i][0] - 1].x, projected[faces[i][0] - 1].y,
                  projected[faces[i][1] - 1].x, projected[faces[i][1] - 1].y, c);
        draw_line(projected[faces[i][1] - 1].x, projected[faces[i][1] - 1].y,
                  projected[faces[i][2] - 1].x, projected[faces[i][2] - 1].y, c);
        draw_line(projected[faces[i][2] - 1].x, projected[faces[i][2] - 1].y,
                  projected[faces[i][0] - 1].x, projected[faces[i][0] - 1].y, c);
    }
}

int main() {
    float angle = 0;

    while (true) {
        system("clear");

        clear_framebuffer();
        //draw_cube(camera, cube, angle_x, angle_y, angle_z, '#');
        draw_triangle(camera, left, 0, angle, angle, '#');
        draw_triangle(camera, right, 0, angle, angle, '#');
        render_frame();

        angle += 0.1f;
    }

    return 0;
}