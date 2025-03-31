#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

// Check if there are any cars
bool isEmpty(int **matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 2 || matrix[i][j] == 3) {
                return false;
            }
        }
    }
    return true;
}

// BFS function to move the cars
bool BFS(int **matrix, int rows, int cols) {
    if (isEmpty(matrix, rows, cols)) {
        cout << "Already empty of cars..." << endl;
        return true;
    }

    // Find where cars are and push them into the queue
    queue<pair<pair<int,int>, pair<int, int>>> cars;
    vector<vector<vector<int>>> visitedCars;  // This will hold visited states for each car in the queue

    int numOfCars = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 2 || matrix[i][j] == 3) {
                cars.push({{numOfCars,matrix[i][j]}, {i, j}});
                // Initialize the visited matrix for this car
                vector<vector<int>> visited(rows, vector<int>(cols, 0));
                visited[i][j] = 1;  // Mark the car's initial position as visited
                visitedCars.push_back(visited);
                numOfCars++;
            }
        }
    }

    while (!cars.empty()) {
        bool moved = false;
        int queueSize = cars.size();
        for (int i = 0; i < queueSize; i++) {

            pair<pair<int,int>, pair<int, int>> car = cars.front();
            int index = car.first.first;
            int type = car.first.second;
            int x = car.second.first;
            int y = car.second.second;
            cars.pop();

            // Get the visited matrix corresponding to this car
            vector<vector<int>>& visited = visitedCars[index];

            // Car moves north/south
            if (type == 2) {

                if (x == 0 || x == rows - 1) {
                    matrix[x][y] = 0;
                    cout << "Car at " << type << "(" << x << ", " << y << ") unparked." << endl;
                    moved = true;
                } else {
                    // Check the up and down neighbors and swap if you can
                    if (x > 0 && matrix[x - 1][y] == 0 && visited[x - 1][y] == 0) {
                        matrix[x - 1][y] = type;
                        matrix[x][y] = 0;
                        cout << "Car at " << type << "(" << x << ", " << y << ") moved to (" << x - 1 << ", " << y << ")." << endl;
                        cars.push({{index,type}, {x - 1, y}});
                        visited[x - 1][y] = 1; 
                        moved = true;
                    } else if (x + 1 < rows && matrix[x + 1][y] == 0 && visited[x + 1][y] == 0) {
                        matrix[x + 1][y] = type;
                        matrix[x][y] = 0;
                        cout << "Car at " << type << "(" << x << ", " << y << ") moved to (" << x + 1 << ", " << y << ")." << endl;
                        cars.push({{index,type}, {x + 1, y}});
                        visited[x+1][y] = 1; 
                        moved = true;
                    } else {
                        cout << "Car at " << type << "(" << x << ", " << y << ") cannot move." << endl;
                        cars.push(car);
                    }
                }
            }
            // Car moves east/west
            else if (type == 3) {
                if (y == 0 || y == cols - 1) {
                    matrix[x][y] = 0;
                    cout << "Car at " << type << "(" << x << ", " << y << ") unparked." << endl;
                    moved = true;
                } else {
                    // Check the left and right neighbors and swap if you can
                    if (y > 0 && matrix[x][y - 1] == 0 && visited[x][y - 1] == 0) {
                        matrix[x][y - 1] = type;
                        matrix[x][y] = 0;
                        cout << "Car at " << type << "(" << x << ", " << y << ") moved to (" << x << ", " << y - 1 << ")." << endl;
                        cars.push({{index,type}, {x, y - 1}});
                        visited[x][y-1] = 1; 
                        moved = true;
                    } else if (y + 1 < cols && matrix[x][y + 1] == 0 && visited[x][y + 1] == 0) {
                        matrix[x][y + 1] = type;
                        matrix[x][y] = 0;
                        cout << "Car at " << type << "(" << x << ", " << y << ") moved to (" << x << ", " << y + 1 << ")." << endl;
                        cars.push({{index,type}, {x, y + 1}});
                        visited[x][y+1] = 1;
                        moved = true;
                    } else {
                        cout << "Car at " << type << "(" << x << ", " << y << ") cannot move." << endl;
                        cars.push(car);
                    }
                }
            }
        }
        if(!moved){
            cout<<"Unsolvable"<<endl;
            return false;
        }
    }

    return true;
}

int main() {

    // int rows0 = 3;
    // int cols0 = 4;

    // int **matrix0 = new int*[rows0];
    // for (int i = 0; i < rows0; ++i) {
    //     matrix0[i] = new int[cols0];
    // }

    // matrix0[0][0] = 0; matrix0[0][1] = 0; matrix0[0][2] = 3; matrix0[0][3] = 1;
    // matrix0[1][0] = 1; matrix0[1][1] = 3; matrix0[1][2] = 2; matrix0[1][3] = 0;
    // matrix0[2][0] = 0; matrix0[2][1] = 0; matrix0[2][2] = 1; matrix0[2][3] = 0;

    int rows0 = 5;
    int cols0 = 6;
    
    int **matrix0 = new int*[rows0];
    for (int i = 0; i < rows0; ++i) {
        matrix0[i] = new int[cols0];
    }

    matrix0[0][0] = 1; matrix0[0][1] = 0; matrix0[0][2] = 0; matrix0[0][3] = 3; matrix0[0][4] = 2; matrix0[0][5] = 0;
    matrix0[1][0] = 0; matrix0[1][1] = 2; matrix0[1][2] = 0; matrix0[1][3] = 1; matrix0[1][4] = 0; matrix0[1][5] = 1;
    matrix0[2][0] = 1; matrix0[2][1] = 3; matrix0[2][2] = 3; matrix0[2][3] = 2; matrix0[2][4] = 0; matrix0[2][5] = 0;
    matrix0[3][0] = 1; matrix0[3][1] = 0; matrix0[3][2] = 1; matrix0[3][3] = 3; matrix0[3][4] = 3; matrix0[3][5] = 2;
    matrix0[4][0] = 0; matrix0[4][1] = 2; matrix0[4][2] = 1; matrix0[4][3] = 0; matrix0[4][4] = 1; matrix0[4][5] = 0;


    BFS(matrix0, rows0, cols0);

    for (int i = 0; i < rows0; i++) {
        for (int j = 0; j < cols0; j++) {
            cout << matrix0[i][j] << " ";
        }
        cout << endl;
    }

    // Deallocate matrix
    for (int i = 0; i < rows0; i++) {
        delete[] matrix0[i];
    }
    delete[] matrix0;

    return 0;
}