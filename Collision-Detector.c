#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Point {
    int x;
    int y;
};

struct KDNode {
    struct Point point;
    struct KDNode *left;
    struct KDNode *right;
};

double squared_distance(int x1, int y1, int x2, int y2) {
    return(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}

struct KDNode* insert(struct KDNode *root, struct Point point, int depth) {
    if (root == NULL) {
        struct KDNode *node = (struct KDNode *)malloc(sizeof(struct KDNode));
        node->point = point;
        node->left = node->right = NULL;
        return node;
    }

    int cd = depth % 2; // Current dimension (0 for x, 1 for y)

    if (cd == 0) {
        if (point.x < root->point.x)
            root->left = insert(root->left, point, depth + 1);
        else
            root->right = insert(root->right, point, depth + 1);
    } else {
        if (point.y < root->point.y)
            root->left = insert(root->left, point, depth + 1);
        else
            root->right = insert(root->right, point, depth + 1);
    }

    return root;
}

void search(struct KDNode *root, struct Point query, int r_squared, int depth, int *collision_count) {
    if (root == NULL) return;

    if (squared_distance(root->point.x, root->point.y, query.x, query.y) <= r_squared)
        (*collision_count)++;

    int cd = depth % 2;

    if (cd == 0) {
        if ((query.x - r_squared <= root->point.x) && (query.x + r_squared >= root->point.x)) {
            search(root->left, query, r_squared, depth + 1, collision_count);
            search(root->right, query, r_squared, depth + 1, collision_count);
        } else if (query.x < root->point.x)
            search(root->left, query, r_squared, depth + 1, collision_count);
        else
            search(root->right, query, r_squared, depth + 1, collision_count);
    } else {
        if ((query.y - r_squared <= root->point.y) && (query.y + r_squared >= root->point.y)) {
            search(root->left, query, r_squared, depth + 1, collision_count);
            search(root->right, query, r_squared, depth + 1, collision_count);
        } else if (query.y < root->point.y)
            search(root->left, query, r_squared, depth + 1, collision_count);
        else
            search(root->right, query, r_squared, depth + 1, collision_count);
    }
}

void free_tree(struct KDNode *root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("ERROR! Argument count not equal to 2\n");
        return(1);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", argv[1]);
        return(1);
    }

    struct KDNode *root = NULL;
    struct Point point;
    while (fscanf(file, "%d %d", &point.x, &point.y) == 2) {
        root = insert(root, point, 0);
    }

    fclose(file);

    int query_x, query_y, query_r;
    while (scanf("%d %d %d", &query_x, &query_y, &query_r) == 3) {
        struct Point query = {query_x, query_y};
        int collision_count = 0;
        int r_squared = query_r * query_r;
        search(root, query, r_squared, 0, &collision_count);
        printf("%d\n", collision_count);
    }

    free_tree(root);
    return(0);
}