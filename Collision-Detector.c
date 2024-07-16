#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point
{
    int x;
    int y;
};

struct Point* read_points(const char* filename, int* num_points)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return(1);
    }

    int capacity = 10;
    *num_points = 0;
    struct Point* points = (struct Point*)malloc(capacity * sizeof(struct Point));

    while (fscanf(file, "%d %d", &points[*num_points].x, &points[*num_points].y) == 2)
    {
        (*num_points)++;
        if (*num_points >= capacity)
        {
            capacity *= 2;
            points = (struct Point*)realloc(points, capacity * sizeof(struct Point));
        }
    }

    fclose(file);
    return(points);
}

int count_points_within_radius(struct Point* points, int num_points, int x_center, int y_center, int radius)
{
    int count = 0;
    int radius_squared = radius * radius;

    for (int i = 0; i < num_points; i++)
    {
        int dx = points[i].x - x_center;
        int dy = points[i].y - y_center;
        if (dx * dx + dy * dy <= radius_squared)
        {
            count++;
        }
    }
    return(count);
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <points file>\n", argv[0]);
        return(1);
    }

    int num_points;
    struct Point* points = read_points(argv[1], &num_points);

    int x_center, y_center, radius;
    while (scanf("%d %d %d", &x_center, &y_center, &radius) == 3)
    {
        int count = count_points_within_radius(points, num_points, x_center, y_center, radius);
        printf("%d\n", count);
    }

    free(points);
    return(0);
}