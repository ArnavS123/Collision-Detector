#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point
{
    int x;
    int y;
};

double squared_distance(int x1, int y1, int x2, int y2)
{
    return(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1))); // a^2 + b^2 = c^2
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("ERROR! Argument count not equal to 2\n");
        return(1);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", argv[1]);
        return(1);
    }

    struct Point *points = NULL;
    int points_count = 0;
    int x_coor;
    int y_coor;

    while (fscanf(file, "%d %d", &x_coor, &y_coor) == 2)
    {
        points = realloc(points, (points_count + 1) * sizeof(struct Point)); // Dynamic memory allocation
        if (points == NULL)
        {
            printf("Error reallocating memory\n");
            fclose(file);
            return(1);
        }
        points[points_count].x = x_coor;
        points[points_count].y = y_coor;
        points_count++;
    }

    fclose(file);

    int query_x;
    int query_y;
    int query_r;

    while (scanf("%d %d %d", &query_x, &query_y, &query_r) == 3)
    {
        int collision_count = 0;
        double r_squared = query_r * query_r;

        for (int i = 0; i < points_count; i++)
        {
            if (squared_distance(points[i].x, points[i].y, query_x, query_y) <= r_squared) // "<=" because being on the line counts as collision: 0 0 100 example
            {
                collision_count++;
            }
        }
        printf("%d\n", collision_count);
    }

    free(points);
    
    return(0);
}