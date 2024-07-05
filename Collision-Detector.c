#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Structure to hold a point
typedef struct {
    int x;
    int y;
} Point;

// Function to calculate the square of the distance between two points
double squared_distance(int x1, int y1, int x2, int y2) {
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <points_file>\n", argv[0]);
        return 1;
    }

    // Open the points file
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    // Read points from the file
    Point *points = NULL;
    size_t points_count = 0;
    int x, y;

    while (fscanf(file, "%d %d", &x, &y) == 2) {
        points = realloc(points, (points_count + 1) * sizeof(Point));
        if (!points) {
            perror("Error reallocating memory");
            fclose(file);
            return 1;
        }
        points[points_count].x = x;
        points[points_count].y = y;
        points_count++;
    }

    fclose(file);

    // Process queries
    int qx, qy, r;
    while (printf("> "), scanf("%d %d %d", &qx, &qy, &r) == 3) {
        int collision_count = 0;
        double r_squared = r * r;

        // Check each point for collision
        for (size_t i = 0; i < points_count; i++) {
            if (squared_distance(points[i].x, points[i].y, qx, qy) <= r_squared) {
                collision_count++;
            }
        }

        printf("%d\n", collision_count);
    }

    // Free allocated memory
    free(points);

    return 0;
}
