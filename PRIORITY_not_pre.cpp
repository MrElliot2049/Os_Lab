#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void printTable(const vector<Process>& processes) {
    cout << "P.ID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting" << endl;
    for (const auto& p : processes) {
        cout << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t" << p.priority << "\t\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << endl;
    }
}

void priorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.arrivalTime < b.arrivalTime;
    });

    int currentTime = 0;
    int completed = 0;
    vector<bool> isCompleted(n, false);

    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = -1; // Initialize with a low value

        // Find the process with the highest priority value that has arrived
        for (int i = 0; i < n; ++i) {
            if (!isCompleted[i] && processes[i].arrivalTime <= currentTime) {
                if (processes[i].priority > highestPriority) {
                    highestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++;
        } else {
            Process& p = processes[highestPriorityIndex];
            currentTime += p.burstTime;
            p.completionTime = currentTime;
            p.turnaroundTime = p.completionTime - p.arrivalTime;
            p.waitingTime = p.turnaroundTime - p.burstTime;
            isCompleted[highestPriorityIndex] = true;
            completed++;
        }
    }

    // Sort by process ID for final display
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });

    printTable(processes);
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Process " << i + 1 << endl;
        cout << "  Enter arrival time: ";
        cin >> processes[i].arrivalTime;
        cout << "  Enter burst time: ";
        cin >> processes[i].burstTime;
        cout << "  Enter priority (higher value = higher priority): ";
        cin >> processes[i].priority;
    }

    priorityScheduling(processes);

    return 0;
}