#include "maze.h"
#include <iostream>
#include <iomanip>
#include <utility>
#include <algorithm>
#include <set>

using namespace std;

DisjointSets Maze::getSets() const {
    return maze;
}

void Maze::printMaze() const {
    cout << setw(3) << " ";
    for (int j = 0; j < ncols; j++) {
        cout << setw(6) << "______";
    }
    for (int i = 0; i < nrows; i++) {
        cout << endl;
        cout << setw(3) << "|";
        for (int j = 0; j < ncols - 1; j++) {
            int val = i * nrows + j;
            cout << setw(3) << val << setw(3);
            if (noWalls.empty() ||
                (find(noWalls.begin(), noWalls.end(), pair<int, int>(val, val + 1)) == noWalls.end() &&
                 find(noWalls.begin(), noWalls.end(), pair<int, int>(val + 1, val)) == noWalls.end())
                    )
                cout << "|";
            else
                cout << " ";
        }
        int val = i * nrows + ncols - 1;
        cout << setw(3) << val << setw(3) << "|";
        cout << endl;
        cout << setw(3) << " ";
        for (int j = 0; j < ncols; j++) {
            int val = i * nrows + j;
            if (i < nrows - 1) {
                if (noWalls.empty() ||
                    (find(noWalls.begin(), noWalls.end(), pair<int, int>(val, val + ncols)) == noWalls.end()
                     && find(noWalls.begin(), noWalls.end(), pair<int, int>(val + ncols, val)) == noWalls.end())
                        )
                    cout << setw(6) << "______";
                else
                    cout << setw(6) << " ";
            } else
                cout << setw(6) << "______";
        }

    }
    cout << endl << endl;
}



// a implementar

Maze::Maze(int rows, int cols) {
    nrows = rows;
    ncols = cols;
    maze = DisjointSets(rows * cols);
    noWalls.clear();
}

vector<int> Maze::getNeighbours(int x) const {
    vector<int> res;
    set<int> options = {0, 1, 2, 3}; // 0 = UP, 1 = LEFT, 2 = DOWN, 3 = RIGHT
    if (x < ncols) options.erase(0);
    if (x % ncols == 0) options.erase(1);
    if (x >= nrows * ncols - ncols) options.erase(2);
    if ((x + 1) % ncols == 0) options.erase(3);
    for (auto option : options) {
        if (option == 0) res.push_back(x - ncols);
        else if (option == 1) res.push_back(x - 1);
        else if (option == 2) res.push_back(x + ncols);
        else if (option == 3) res.push_back((x + 1));
    }
    return res;
}

void Maze::buildRandomMaze() {
    int x, y;
    noWalls.clear();
    vector<int> neighbours;
    while (maze.getNumberOfSets() != 1) {
        x = rand() % (nrows * ncols);
        neighbours = getNeighbours(x);
        y = neighbours.at(rand() % neighbours.size());
        int f_x = maze.find(x);
        int f_y = maze.find(y);
        if (f_x != f_y) {
            maze.unionSets(f_x, f_y);
            noWalls.push_back(pair<int, int>(x, y));
        }
    }
}

