#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Board
{
public:
    Board(int size) : size(size), board(size, vector<char>(size, '.')) {}

    void placeSoldier(int x, int y)
    {
        board[x][y] = 'S';
    }

    void placeCastle(int x, int y)
    {
        board[x][y] = 'C';
    }

    bool isSoldier(int x, int y) const
    {
        return board[x][y] == 'S';
    }

    void removeSoldier(int x, int y)
    {
        board[x][y] = '.';
    }

    void printBoard() const
    {
        for (const auto &row : board)
        {
            for (const auto &cell : row)
            {
                cout << cell << ' ';
            }
            cout << '\n';
        }
        cout << '\n';
    }

    int size;
    vector<vector<char>> board;
};

void findPaths(Board &board, int startX, int startY, vector<string> &path, vector<vector<string>> &paths)
{
    vector<pair<int, int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}}; // Right, Down, Left, Up
    int currentDir = 0;                                                     // Start by moving right
    int currentX = startX, currentY = startY;
    pair<int, int> home = {startX, startY};

    while (true)
    {
        int nextX = currentX + directions[currentDir].first;
        int nextY = currentY + directions[currentDir].second;

        if (0 <= nextX && nextX < board.size && 0 <= nextY && nextY < board.size)
        {
            if (board.isSoldier(nextX, nextY))
            {
                path.push_back("Kill (" + to_string(nextX) + "," + to_string(nextY) + "). Turn Left");
                board.removeSoldier(nextX, nextY);
                currentX = nextX;
                currentY = nextY;
                currentDir = (currentDir + 3) % 4; // Turn left
            }
            else
            {
                currentX = nextX;
                currentY = nextY;
            }

            if (currentX == home.first && currentY == home.second)
            {
                path.push_back("Arrive (" + to_string(home.first) + "," + to_string(home.second) + ")");
                paths.push_back(path);
                break;
            }
        }
        else
        {
            break;
        }
    }
}

int main()
{
    int size = 10; // Chessboard size
    vector<pair<int, int>> soldiers = {{0, 0}, {8, 7}, {8, 0}, {0, 3}, {1, 3}, {7, 3}, {5, 1}, {5, 4}, {1, 7}, {8, 4}, {7, 1}};
    pair<int, int> castle = {1, 0};

    Board board(size);

    for (const auto &soldier : soldiers)
    {
        board.placeSoldier(soldier.first, soldier.second);
    }

    board.placeCastle(castle.first, castle.second);
    board.printBoard();

    vector<vector<string>> paths;
    vector<string> path = {"Start (" + to_string(castle.first) + "," + to_string(castle.second) + ")"};
    findPaths(board, castle.first, castle.second, path, paths);

    cout << "Thanks. There are " << paths.size() << " unique paths for your 'special_castle'\n";
    for (size_t i = 0; i < paths.size(); ++i)
    {
        cout << "\nPath " << i + 1 << ":\n";
        cout << "=======\n";
        for (const auto &step : paths[i])
        {
            cout << step << '\n';
        }
    }

    return 0;
}
