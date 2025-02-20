//  engine.c
//  20th of February, 2025
//  Julio Dominguez

#include "C3D.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

Point3D vertices[MAX_VERTICES];
int faces[MAX_FACES][3];
int vertex_count = 0, face_count = 0;

Point project_point(Point3D p, Camera cam) {
    // Translate points relative to camera
    float dx = p.x - cam.x;
    float dy = p.y - cam.y;
    float dz = p.z - cam.z;

    // Rotate points inversely to camera yaw/pitch
    float rad_yaw = cam.yaw * (M_PI / 180.0f);
    float rad_pitch = -cam.pitch * (M_PI / 180.0f);

    // Rotate around Y-axis (yaw)
    float temp_x = dx * cos(rad_yaw) - dz * sin(rad_yaw);
    float temp_z = dx * sin(rad_yaw) + dz * cos(rad_yaw);
    dx = temp_x;
    dz = temp_z;

    // Rotate around X-axis (pitch)
    float temp_y = dy * cos(rad_pitch) - dz * sin(rad_pitch);
    dz = dy * sin(rad_pitch) + dz * cos(rad_pitch);
    dy = temp_y;

    // Perspective projection
    float scale = 200.0f / dz; // Adjust this for FOV
    return (Point){
        .x = (int)(dx * scale + WIDTH / 2),
        .y = (int)(dy * scale + HEIGHT / 2)
    };
}

Point3D rotate_x(Point3D p, float angle) {
    float rad = angle * (M_PI / 180.0f);
    return (Point3D){
        .x = p.x,
        .y = p.y * cos(rad) - p.z * sin(rad),
        .z = p.y * sin(rad) + p.z * cos(rad)
    };
}

Point3D rotate_y(Point3D p, float angle) {
    float rad = angle * (M_PI / 180.0f);
    return (Point3D){
        .x = p.x * cos(rad) + p.z * sin(rad),
        .y = p.y,
        .z = -p.x * sin(rad) + p.z * cos(rad)
    };
}

Point3D rotate_z(Point3D p, float angle) {
    float rad = angle * (M_PI / 180.0f);
    return (Point3D){
        .x = p.x * cos(rad) - p.y * sin(rad),
        .y = p.x * sin(rad) + p.y * cos(rad),
        .z = p.z
    };
}

void load_obj(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Cannot open %s\n", filename);
        return;
    }

    char line[128];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] == 'v' && line[1] == ' ') {
            if (vertex_count >= MAX_VERTICES) {
                printf("Error: Too many vertices in OBJ file.\n");
                break;
            }
            sscanf(line, "v %f %f %f", &vertices[vertex_count].x, &vertices[vertex_count].y, &vertices[vertex_count].z);
            vertex_count++;
        } else if (line[0] == 'f' && line[1] == ' ') {
            if (face_count >= MAX_FACES) {
                printf("Error: Too many faces in OBJ file.\n");
                break;
            }
            sscanf(line, "f %d %d %d", &faces[face_count][0], &faces[face_count][1], &faces[face_count][2]);
            face_count++;
        }
    }

    fclose(file);
    printf("Loaded %d vertices and %d faces.\n", vertex_count, face_count);
}

void plot(int x, int y, char c) {
    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
        framebuffer[y][x] = c;
    }
}

void draw_line(int x0, int y0, int x1, int y1, char c) {
    int dx = abs(x1 - x0);
    int dy = -abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (1) {
        plot(x0, y0, c);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}