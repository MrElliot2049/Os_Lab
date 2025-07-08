#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    bool executed;
};

bool compareArrival(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurst(const Process &a, const Process &b) {
    return a.burstTime > b.burstTime;
}

void calculateTimes(vector<Process>& processes) {
    int currentTime = 0;
    int completed = 0;
    int n = processes.size();
    
    for (auto& p : processes) {
        p.executed = false;
    }
    
    while (completed != n) {
        vector<Process> available;
        
        for (auto& p : processes) {
            if (p.arrivalTime <= currentTime && !p.executed) {
                available.push_back(p);
            }
        }
        
        if (!available.empty()) {
            sort(available.begin(), available.end(), compareBurst);
            
            Process& p = available[0];
            
            for (auto& original : processes) {
                if (original.id == p.id && !original.executed) {
                    original.completionTime = currentTime + original.burstTime;
                    original.turnaroundTime = original.completionTime - original.arrivalTime;
                    original.waitingTime = original.turnaroundTime - original.burstTime;
                    original.executed = true;
                    currentTime = original.completionTime;
                    completed++;
                    break;
                }
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
    }
    
    sort(processes.begin(), processes.end(), compareArrival);
    calculateTimes(processes);
    printResults(processes);
    
    return 0;
}