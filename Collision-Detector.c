#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point
{
    int x, y;
} Point;

typedef struct KDNode
{
    Point point;
    struct KDNode *left, *right;
} KDNode;

int compareX(const void *a, const void *b)
{
    Point *pointA = (Point *)a;
    Point *pointB = (Point *)b;
    return(pointA->x - pointB->x);
}

int compareY(const void *a, const void *b)
{
    Point *pointA = (Point *)a;
    Point *pointB = (Point *)b;
    return(pointA->y - pointB->y);
}

KDNode* buildKDTree(Point points[], int start, int end, int depth)
{
    if (start > end)
    {
        return(NULL);
    }

    int mid = (start + end) / 2;
    if (depth % 2 == 0)
    {
        qsort(points + start, end - start + 1, sizeof(Point), compareX);
    }
    else
    {
        qsort(points + start, end - start + 1, sizeof(Point), compareY);
    }

    KDNode *node = (KDNode *)malloc(sizeof(KDNode));
    node->point = points[mid];
    node->left = buildKDTree(points, start, mid - 1, depth + 1);
    node->right = buildKDTree(points, mid + 1, end, depth + 1);

    return(node);
}

int isWithinCircle(Point point, Point center, int radius)
{
    int dx = point.x - center.x;
    int dy = point.y - center.y;
    return(dx * dx + dy * dy <= radius * radius);
}

int countPointsInCircle(KDNode *root, Point center, int radius, int depth)
{
    if (root == NULL)
    {
        return(0);
    }

    int count = 0;
    if (isWithinCircle(root->point, center, radius))
    {
        count++;
    }

    int axis = depth % 2;
    int dist = (axis == 0) ? center.x - root->point.x : center.y - root->point.y;

    if (dist <= radius)
    {
        count += countPointsInCircle(root->left, center, radius, depth + 1);
    }
    if (dist >= -radius)
    {
        count += countPointsInCircle(root->right, center, radius, depth + 1);
    }

    return(count);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <points file>\n", argv[0]);
        return(1);
    }

    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        perror("Failed to open file");
        return(1);
    }

    int capacity = 1000;
    Point *points = (Point *)malloc(capacity * sizeof(Point));
    if (!points)
    {
        perror("Failed to allocate memory");
        return(1);
    }

    int n = 0;
    while (fscanf(file, "%d %d", &points[n].x, &points[n].y) != EOF)
    {
        n++;
        if (n >= capacity)
        {
            capacity *= 2;
            points = (Point *)realloc(points, capacity * sizeof(Point));
            if (!points)
            {
                perror("Failed to reallocate memory");
                return(1);
            }
        }
    }
    fclose(file);

    KDNode *root = buildKDTree(points, 0, n - 1, 0);

    int x, y, r;
    while (scanf("%d %d %d", &x, &y, &r) == 3)
    {
        Point center = {x, y};
        int count = countPointsInCircle(root, center, r, 0);
        printf("%d\n", count);
    }

    return(0);
}