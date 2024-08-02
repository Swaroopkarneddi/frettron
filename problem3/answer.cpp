#include <iostream>
#include <vector>
#include <set>

using namespace std;

const int BOARD_SIZE = 10;
vector<vector<bool>> board(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));

enum Direction
{
    RIGHT,
    DOWN,
    LEFT,
    UP
};

void printPath(const vector<pair<int, int>> &path)
{
    cout << "Start (" << path[0].first << "," << path[0].second << ")" << endl;
    for (size_t i = 1; i < path.size(); ++i)
    {
        if (i < path.size() - 1)
        {
            cout << "Kill (" << path[i].first << "," << path[i].second << "). Turn Left" << endl;
        }
        else
        {
            cout << "Jump (" << path[i].first << "," << path[i].second << ")." << endl;
        }
    }
    cout << "Arrive (" << path[0].first << "," << path[0].second << ")" << endl;
}

int findPaths(int x, int y, Direction dir, vector<pair<int, int>> &currentPath, set<vector<pair<int, int>>> &allPaths)
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
        return 0;

    if (x == 0 && y == 0 && currentPath.size() > 1)
    {
        allPaths.insert(currentPath);
        return 1;
    }

    int dx[] = {0, 1, 0, -1}; // RIGHT, DOWN, LEFT, UP
    int dy[] = {1, 0, -1, 0};

    Direction nextDir = static_cast<Direction>((dir + 1) % 4);
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    int pathCount = 0;

    // Option 1: Kill the soldier and turn left
    if (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[nx][ny])
    {
        board[nx][ny] = false;
        currentPath.push_back({nx + 1, ny + 1});
        pathCount += findPaths(nx, ny, nextDir, currentPath, allPaths);
        currentPath.pop_back();
        board[nx][ny] = true;
    }

    // Option 2: Skip the soldier and move forward
    pathCount += findPaths(nx, ny, dir, currentPath, allPaths);

    return pathCount;
}

int main()
{
    int numSoldiers;
    cout << "Enter the number of soldiers: ";
    cin >> numSoldiers;

    if (numSoldiers <= 0)
    {
        cerr << "Number of soldiers must be positive." << endl;
        return 1;
    }

    cout << "Enter coordinates for soldier(s):" << endl;
    for (int i = 0; i < numSoldiers; ++i)
    {
        int x, y;
        char comma;
        cout << "Enter coordinates for soldier " << i + 1 << ": ";
        cin >> x >> comma >> y;
        if (x < 1 || x > BOARD_SIZE || y < 1 || y > BOARD_SIZE)
        {
            cerr << "Invalid coordinates. Must be between 1 and " << BOARD_SIZE << "." << endl;
            return 1;
        }
        board[x - 1][y - 1] = true; // Convert to 0-based index
    }

    int startX, startY;
    char comma;
    cout << "Enter the coordinates for your 'special' castle: ";
    cin >> startX >> comma >> startY;
    if (startX < 1 || startX > BOARD_SIZE || startY < 1 || startY > BOARD_SIZE)
    {
        cerr << "Invalid starting position. Must be between 1 and " << BOARD_SIZE << "." << endl;
        return 1;
    }
    startX--;
    startY--; // Convert to 0-based index

    vector<pair<int, int>> currentPath = {{startX + 1, startY + 1}};
    set<vector<pair<int, int>>> allPaths;

    findPaths(startX, startY, RIGHT, currentPath, allPaths);

    cout << "Thanks. There are " << allPaths.size() << " unique paths for your 'special_castle'" << endl;

    int pathNumber = 1;
    for (const auto &p : allPaths)
    {
        cout << "Path " << pathNumber++ << endl;
        cout << "=====" << endl;
        printPath(p);
        cout << endl;
    }

    return 0;
}
