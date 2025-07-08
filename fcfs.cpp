#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
};

void calculateTimes(vector<Process>& processes) {
    int currentTime = 0;
    
    for (auto& p : processes) {
        if (p.arrivalTime > currentTime) {
            currentTime = p.arrivalTime;
        }
        p.completionTime = currentTime + p.burstTime;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
        p.waitingTime = p.turnaroundTime - p.burstTime;
        currentTime = p.completionTime;
    }
}

void printResults(const vector<Process>& processes) {
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;
    
    cout << "\nProcess ID | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time\n";
    cout << "----------------------------------------------------------------------------------------\n";
    
    for (const auto& p : processes) {
        cout << setw(10) << p.id << " | "
             << setw(12) << p.arrivalTime << " | "
             << setw(10) << p.burstTime << " | "
             << setw(15) << p.completionTime << " | "
             << setw(15) << p.turnaroundTime << " | "
             << setw(12) << p.waitingTime << "\n";
             
        totalWaitingTime += p.waitingTime;
        totalTurnaroundTime += p.turnaroundTime;
    }
    
    float avgWaitingTime = static_cast<float>(totalWaitingTime) / processes.size();
    float avgTurnaroundTime = static_cast<float>(totalTurnaroundTime) / processes.size();
    
    cout << "\nAverage Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turnaround Time: " << avgTurnaroundTime << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        cout << "\nEnter details for process " << i + 1 << ":\n";
        processes[i].id = i + 1;
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (processes[j].arrivalTime > processes[j + 1].arrivalTime) {
                swap(processes[j], processes[j + 1]);
            }
        }
    }
    calculateTimes(processes);
    printResults(processes);
    
    return 0;
}