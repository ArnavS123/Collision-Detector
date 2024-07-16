#include <stdio.h>
#include <stdlib.h>

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
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    int capacity = file_size / (2 * sizeof(int)); // Rough estimate
    *num_points = 0;
    struct Point* points = (struct Point*)malloc(capacity * sizeof(struct Point));

    int x, y;
    while (fscanf(file, "%d %d", &x, &y) == 2)
    {
        if (*num_points >= capacity)
        {
            capacity *= 2;
            points = (struct Point*)realloc(points, capacity * sizeof(struct Point));
        }
        points[*num_points].x = x;
        points[*num_points].y = y;
        (*num_points)++;
    }

    fclose(file);
    return(points);
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
        printf("%d\n", count);
    }

    free(points);
    return(0);
}