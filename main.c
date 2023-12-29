#include <stdio.h>
#include <stdbool.h>

int Wall;
char A[20], B[20];
int board[100][100];
int walls[2 * 100 - 1][2 * 100 - 1]; // Adjacency matrix for walls

void initialize() {
    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            board[i][j] = 0;
        }
    }
}

bool canMove(int x1, int y1, int x2, int y2) {
    if (x1 == x2) {
        if (y1 < y2) {
            if (walls[x1 * 2][y1 * 2 + 1] == 1) {
                return false; // There is a wall
            }
        } else {
            if (walls[x1 * 2][(y1 - 1) * 2 + 1] == 1) {
                return false; // There is a wall
            }
        }
    } else if (y1 == y2) {
        if (x1 < x2) {
            if (walls[x1 * 2 + 1][y1 * 2] == 1) {
                return false; // There is a wall
            }
        } else {
            if (walls[(x1 - 1) * 2 + 1][y1 * 2] == 1) {
                return false; // There is a wall
            }
        }
    }
    return true;
}

int BFS(int startX, int startY, int endX, int endY, int num_vertices) {
    bool visited[100] = {false};
    int queue[100];
    int front = 0, rear = 0;
    int start = startX * num_vertices + startY;
    int end = endX * num_vertices + endY;

    visited[start] = true;
    queue[rear++] = start;

    while (front < rear) {
        int node = queue[front++];
        int x = node / num_vertices;
        int y = node % num_vertices;
        if (x == endX && y == endY) {
            return 1;
        }
        for (int i = 0; i < num_vertices; i++) {
            if (board[node][i] && !visited[i] && canMove(x,y,i / num_vertices, i % num_vertices)) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
    return 0;
}

int DFS(int startX, int startY, int endX, int endY, int board[][100], int num_vertices, bool visited[]) {
    if (startX == endX && startY == endY) {
        return 1; // Path found
    }

    int node = startX * num_vertices + startY;
    visited[node] = true;

    for (int i = 0; i < num_vertices; i++) {
        if (board[node][i] && !visited[i]) {
            int nextX = i / num_vertices;
            int nextY = i % num_vertices;
            if (DFS(nextX, nextY, endX, endY, board, num_vertices, visited)) {
                return 1; // Path found
            }
        }
    }
    return 0; // Path found
}
