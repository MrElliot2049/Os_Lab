#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

struct CompareRemainingTime {
    bool operator()(const Process& a, const Process& b) {
        return a.remainingTime > b.remainingTime;
    }
};

void calculateTimes(vector<Process>& processes) {
    priority_queue<Process, vector<Process>, CompareRemainingTime> readyQueue;
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    vector<bool> executed(n, false);

    while (completed != n) {
        for (int i = 0; i < n; i++) {
            if (!executed[i] && processes[i].arrivalTime <= currentTime) {
                readyQueue.push(processes[i]);
                executed[i] = true;
            }
        }

        if (!readyQueue.empty()) {
            Process current = readyQueue.top();
            readyQueue.pop();

            int index = -1;
            for (int i = 0; i < n; i++) {
                if (processes[i].id == current.id) {
                    index = i;
                    break;
                }
            }

            processes[index].remainingTime--;
            currentTime++;

            if (processes[index].remainingTime == 0) {
                processes[index].completionTime = currentTime;
                processes[index].turnaroundTime = processes[index].completionTime - processes[index].arrivalTime;
                processes[index].waitingTime = processes[index].turnaroundTime - processes[index].burstTime;
                completed++;
            } else {
                readyQueue.push(processes[index]);
            }
        } else {
            currentTime++;
        }
    }
}

void printResults(const vector<Process>& processes) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\n";
    cout << "--------------------------------\n";

    for (const auto& p : processes) {
        cout << p.id << "\t" 
             << p.arrivalTime << "\t" 
             << p.burstTime << "\t"
             << p.completionTime << "\t"
             << p.turnaroundTime << "\t"
             << p.waitingTime << "\n";

        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
    }

    float avgWaitingTime = static_cast<float>(totalWaitingTime) / processes.size();
    float avgTurnaroundTime = static_cast<float>(totalTurnaroundTime) / processes.size();

    cout << "\nAverage Waiting Time: " << fixed << setprecision(2) << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << fixed << setprecision(2) << avgTurnaroundTime << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    for (int i = 0; i < n; ++i) {
        cout << "\nProcess " << i + 1 << ":\n";
        processes[i].id = i + 1;
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
    }

    calculateTimes(processes);
    printResults(processes);

    return 0;
}