#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    float x;
    float y;
    float z;
} Vector;

typedef struct {
    Vector normal;
    Vector vertex1;
    Vector vertex2;
    Vector vertex3;
    uint16_t attr_byte_cnt;
} Triangle;

uint8_t header[80];
uint32_t num_triangles;
Triangle *triangles;

void collectData(char *inputFile) {
    // Open file
    FILE *file = fopen(inputFile, "rb");
    if (!file) {
        printf("Error: Unable to open file\n");
        exit(1);
    }
    // Read header information
    fread(header, sizeof(uint8_t), 80, file);
    // Read number of triangles
    fread(&num_triangles, sizeof(uint32_t), 1, file);
    // Allocate memory for the array of Triangles 
    triangles = (Triangle*)malloc(num_triangles * sizeof(Triangle));
    if (triangles == NULL) {
        printf("Error: Memory allocation failed\n");
        fclose(file);
        exit(1);
    }
    // Read each triangle
    for (uint32_t i = 0; i < num_triangles; i++) {
        // Read each individual triangle
        fread(&triangles[i], 50, 1, file);
    }
    fclose(file);
}

float calculateVolume(Triangle triangle) {
    // Initialize tetrahedron 
    float v_321 = triangle.vertex3.x * triangle.vertex2.y * triangle.vertex1.z;
    float v_231 = triangle.vertex2.x * triangle.vertex3.y * triangle.vertex1.z;
    float v_312 = triangle.vertex3.x * triangle.vertex1.y * triangle.vertex2.z;
    float v_132 = triangle.vertex1.x * triangle.vertex3.y * triangle.vertex2.z;
    float v_213 = triangle.vertex2.x * triangle.vertex1.y * triangle.vertex3.z;
    float v_123 = triangle.vertex1.x * triangle.vertex2.y * triangle.vertex3.z;
    // Calculate volume of tetrahedron
    return (1.0 / 6.0) * (-v_321 + v_231 + v_312 - v_132 - v_213 + v_123);
}

float calculateArea(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3) {
    // Initialize variables
    float a_1 = x2 - x1;
    float a_2 = y2 - y1;
    float a_3 = z2 - z1;
    float b_1 = x3 - x1;
    float b_2 = y3 - y1;
    float b_3 = z3 - z1;
    // Cross product
    float cross_x = a_2 * b_3 - a_3 * b_2;
    float cross_y = a_3 * b_1 - a_1 * b_3;
    float cross_z = a_1 * b_2 - a_2 * b_1;
    // Calculate individual area
    return 0.5 * sqrt(cross_x * cross_x + cross_y * cross_y + cross_z * cross_z);
}

void printData(void) {
    printf("------ File Information ------\n");
    // Print header data 
    for (uint32_t i = 0; i < 80; i++) {
        printf("header %d: %hhu\n", i+1, header[i]);
    }
    // Print the number of triangles
    printf("Number of triangles: %u\n", num_triangles);
    // Print triangle data
    float surface_area = 0;
    float total_volume = 0;
    for (uint32_t i = 0; i < num_triangles; i++) {
        printf("****** Triangle %i ******\n", i+1);
        printf("Normal vector: (%f,%f,%f)\n", triangles[i].normal.x, triangles[i].normal.y, triangles[i].normal.z);
        printf("Vertex1:       (%f,%f,%f)\n", triangles[i].vertex1.x, triangles[i].vertex1.y, triangles[i].vertex1.z);
        printf("Vertex2:       (%f,%f,%f)\n", triangles[i].vertex2.x, triangles[i].vertex2.y, triangles[i].vertex2.z);
        printf("Vertex3:       (%f,%f,%f)\n", triangles[i].vertex3.x, triangles[i].vertex3.y, triangles[i].vertex3.z);
        printf("Attribute byte count: %hx\n", triangles[i].attr_byte_cnt);
        // Calculate the area of each triangle
        float triangle_area = calculateArea(triangles[i].vertex1.x, triangles[i].vertex1.y, triangles[i].vertex1.z,
                                            triangles[i].vertex2.x, triangles[i].vertex2.y, triangles[i].vertex2.z,
                                            triangles[i].vertex3.x, triangles[i].vertex3.y, triangles[i].vertex3.z);
        // Calculate total surface area
        surface_area += triangle_area; 
        printf("Individual area: %f\n", triangle_area); 
        // Calculate contribution volume
        float contrib_volume = calculateVolume(triangles[i]);
        // Calculate total volume
        total_volume += contrib_volume;
        printf("Contribution volume: %f\n", contrib_volume);
    }
    printf("###### Global data ######\n");
    printf("Surface area: %f\n", surface_area);
    printf("Total volume: %f\n", fabs(total_volume));
}

int main(int argc, char *argv[]) {
    if (argc == 2  && strstr(argv[1], ".stl")) {
        // Initialize and print data
        collectData(argv[1]);
        printData();
    } else {
        printf("Error: Invalid usage\nRun: ./meshData [FILE]\n");
        return 1;
    } 
    // Free dynamically allocated memory
    free(triangles);
    return 0;
}

