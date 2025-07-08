#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;        // Process ID
    int arrival;    // Arrival time
    int burst;      // Burst time
    int completion; // Completion time
    int waiting;    // Waiting time
    int turnaround; // Turnaround time
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

bool compareBurst(const Process &a, const Process &b) {
    return a.burst < b.burst;
}

void calculateTimes(vector<Process> &processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    vector<bool> executed(n, false);
    
    while (completed != n) {
        vector<Process> readyQueue;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && !executed[i]) {
                readyQueue.push_back(processes[i]);
            }
        }
        
        if (!readyQueue.empty()) {
            sort(readyQueue.begin(), readyQueue.end(), compareBurst);
            
            for (int i = 0; i < n; i++) {
                if (processes[i].pid == readyQueue[0].pid) {
                    processes[i].completion = currentTime + processes[i].burst;
                    processes[i].turnaround = processes[i].completion - processes[i].arrival;
                    processes[i].waiting = processes[i].turnaround - processes[i].burst;
                    executed[i] = true;
                    currentTime = processes[i].completion;
                    completed++;
                    break;
                }
            }
        } else {
            currentTime++;
        }
    }
}

void printResults(const vector<Process> &processes) {
    float totalWaiting = 0, totalTurnaround = 0;
    
    cout << "\n+-----+---------+-------+------------+---------+-------------+\n";
    cout << "| PID | Arrival | Burst | Completion | Waiting | Turnaround  |\n";
    cout << "+-----+---------+-------+------------+---------+-------------+\n";
    
    for (const auto &p : processes) {
        cout << "| " << setw(3) << p.pid << " | "
             << setw(7) << p.arrival << " | "
             << setw(5) << p.burst << " | "
             << setw(10) << p.completion << " | "
             << setw(7) << p.waiting << " | "
             << setw(11) << p.turnaround << " |\n";
             
        totalWaiting += p.waiting;
        totalTurnaround += p.turnaround;
    }
    
    cout << "+-----+---------+-------+------------+---------+-------------+\n";
    
    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWaiting/processes.size() << endl;
    cout << "Average Turnaround Time: " << totalTurnaround/processes.size() << endl;
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Enter arrival time for process " << i+1 << ": ";
        cin >> processes[i].arrival;
        cout << "Enter burst time for process " << i+1 << ": ";
        cin >> processes[i].burst;
    }
    
    sort(processes.begin(), processes.end(), compareArrival);
    calculateTimes(processes);
    printResults(processes);
    
    return 0;
}