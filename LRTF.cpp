#include <bits/stdc++.h>

using namespace std;
struct process {
    int processno;
    int AT;
    int BT;
    int BTbackup;
    int WT;
    int TAT;
    int CT;
};
struct process p[4];
int totaltime = 0;
int prefinaltotal = 0;
bool compare(process p1, process p2)
{
    return p1.AT < p2.AT;
}
int findlargest(int at)
{
    int max = 0, i;
    for (i = 0; i < 4; i++) {
        if (p[i].AT <= at) {
            if (p[i].BT > p[max].BT)
                max = i;
        }
    }
    return max;
}
int findCT()
{

    int index;
    int flag = 0;
    int i = p[0].AT;
    while (1) {
        if (i <= 4) {
            index = findlargest(i);
        }

        else
            index = findlargest(4);
        cout << "Process executing at time " << totaltime
            << " is: P" << index + 1 << "\t";

        p[index].BT -= 1;
        totaltime += 1;
        i++;

        if (p[index].BT == 0) {
            p[index].CT = totaltime;
            cout << " Process P" << p[index].processno 
                << " is completed at " << totaltime;
        }
        cout << endl;
        if (totaltime == prefinaltotal)
            break;
    }
}

int main()
{

    int i;
    for (i = 0; i < 4; i++) {
        p[i].processno = i + 1;
    }
    for (i = 0; i < 4; i++) 
    {
        p[i].AT = i + 1;
    }    
    for (i = 0; i < 4; i++) {

        p[i].BT = 2 * (i + 1);
        p[i].BTbackup = p[i].BT;
        prefinaltotal += p[i].BT;
    }
    cout << "PNo\tAT\tBT\n";

    for (i = 0; i < 4; i++) {
        cout << p[i].processno << "\t";
        cout << p[i].AT << "\t";
        cout << p[i].BT << "\t";
        cout << endl;
    }
    cout << endl;
    sort(p, p + 4, compare);
    totaltime += p[0].AT;
    prefinaltotal += p[0].AT;
    findCT();
    int totalWT = 0;
    int totalTAT = 0;
    for (i = 0; i < 4; i++) {
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BTbackup;        
        totalWT += p[i].WT;
        totalTAT += p[i].TAT;
    }

    cout << "After execution of all processes ... \n";
    cout << "PNo\tAT\tBT\tCT\tTAT\tWT\n";

    for (i = 0; i < 4; i++) {
        cout << p[i].processno << "\t";
        cout << p[i].AT << "\t";
        cout << p[i].BTbackup << "\t";
        cout << p[i].CT << "\t";
        cout << p[i].TAT << "\t";
        cout << p[i].WT << "\t";
        cout << endl;
    }

    cout << endl;
    cout << "Total TAT = " << totalTAT << endl;
    cout << "Average TAT = " << totalTAT / 4.0 << endl;
    cout << "Total WT = " << totalWT << endl;
    cout << "Average WT = " << totalWT / 4.0 << endl;
    return 0;
}
