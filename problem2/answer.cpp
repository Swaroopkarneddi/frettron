#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void distributeApples()
{
    vector<int> apples;
    int weight;

    cout << "Enter apple weight in gram (-1 to stop): ";
    while (cin >> weight && weight != -1)
    {
        apples.push_back(weight);
        cout << "Enter apple weight in gram (-1 to stop): ";
    }

    int totalWeight = 0;
    for (int w : apples)
    {
        totalWeight += w;
    }

    double proportionRam = 0.5;
    double proportionSham = 0.3;
    double proportionRahim = 0.2;

    int targetRam = static_cast<int>(totalWeight * proportionRam + 0.5); // Rounding to nearest integer
    int targetSham = static_cast<int>(totalWeight * proportionSham + 0.5);
    int targetRahim = static_cast<int>(totalWeight * proportionRahim + 0.5);

    sort(apples.begin(), apples.end(), greater<int>());

    vector<int> ramApples, shamApples, rahimApples;
    int ramWeight = 0, shamWeight = 0, rahimWeight = 0;

    for (int apple : apples)
    {
        if (ramWeight + apple <= targetRam)
        {
            ramApples.push_back(apple);
            ramWeight += apple;
        }
        else if (shamWeight + apple <= targetSham)
        {
            shamApples.push_back(apple);
            shamWeight += apple;
        }
        else if (rahimWeight + apple <= targetRahim)
        {
            rahimApples.push_back(apple);
            rahimWeight += apple;
        }
    }

    cout << "Distribution Result:" << endl;
    cout << "Ram: ";
    for (int a : ramApples)
    {
        cout << a << " ";
    }
    cout << endl;

    cout << "Sham: ";
    for (int a : shamApples)
    {
        cout << a << " ";
    }
    cout << endl;

    cout << "Rahim: ";
    for (int a : rahimApples)
    {
        cout << a << " ";
    }
    cout << endl;
}

int main()
{
    distributeApples();
    return 0;
}
