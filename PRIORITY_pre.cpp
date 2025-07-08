#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void printTable(vector<Process>& processes) {
    // Sort by ID for a clean final output
    sort(processes.begin(), processes.end(), [](const Process& a, const Process& b) {
        return a.id < b.id;
    });

    cout << "P.ID\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting" << endl;
    for (const auto& p : processes) {
        cout << p.id << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t" << p.priority << "\t\t"
             << p.completionTime << "\t\t" << p.turnaroundTime << "\t\t" << p.waitingTime << endl;
    }
}

void preemptivePriorityScheduling(vector<Process>& processes) {
    int n = processes.size();
    for (int i = 0; i < n; ++i) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0;
    int completed = 0;

    while (completed < n) {
        int highestPriorityIndex = -1;
        int highestPriority = -1; // Lower numbers mean lower priority

        // At current time, find the available process with the highest priority
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].priority > highestPriority) {
                    highestPriority = processes[i].priority;
                    highestPriorityIndex = i;
                }
            }
        }

        if (highestPriorityIndex == -1) {
            currentTime++; // No process is ready, advance time
        } else {
            // Execute the highest priority process for one time unit
            Process& p = processes[highestPriorityIndex];
            p.remainingTime--;
            currentTime++;

            // If process is finished
            if (p.remainingTime == 0) {
                p.completionTime = currentTime;
                p.turnaroundTime = p.completionTime - p.arrivalTime;
                p.waitingTime = p.turnaroundTime - p.burstTime;
                completed++;
            }
        }
    }

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

    preemptivePriorityScheduling(processes);

    return 0;
}