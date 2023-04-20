/*
Design a scheduling program to implements a Queue with two levels: 
Level 1: Fixed priority preemptive Scheduling 
Level 2: Round Robin Scheduling 
For a Fixed priority preemptive Scheduling (Queue 1), the Priority 0 is highest priority. 
If one process P1 is scheduled and running, another process P2 with higher priority comes.
The New process (high priority) process P2 preempts currently running process P1 and process P1
will go to second level queue. Time for which process will strictly execute must be considered 
in the multiples of 2. All the processes in the second level queue will complete their execution 
according to round robin scheduling. 
Consider: 
1. Queue 2 will be processed after Queue 1 becomes empty. 
2. Priority of Queue 2 has lower priority than in Queue 1. 
*/
#include <iostream>
#include <queue>
using namespace std;
struct Process
{
    int pid;            
    int priority;       
    int burst_time;     
    int rem_time; 
    int quantum;        
    Process(int pid, int priority, int burst_time, int quantum)
    {
        this->pid = pid;
        this->priority = priority;
        this->burst_time = burst_time;
        this->rem_time = burst_time;
        this->quantum = quantum;
    }
};
struct ComparePriority
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.priority > p2.priority;
    }
};
struct Compareroundrobin
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.rem_time < p2.rem_time;
    }
};

int main()
{
    int nump, quantum;
    cout << "Enter the number of process: ";
    cin >> nump;
    cout << "Enter the quantum time: ";
    cin >> quantum;
    priority_queue<Process, vector<Process>, ComparePriority> q1;
    priority_queue<Process, vector<Process>, Compareroundrobin> q2;
    for (int i = 0; i < nump; i++)
    {
        int pid, priority, burst_time;
        cout << "Enter details of process " << i + 1 << endl;
        cout << "Process ID: ";
        cin >> pid;
        cout << "Priority: ";
        cin >> priority;
        cout << "Burst Time: ";
        cin >> burst_time;
        q1.push(Process(pid, priority, burst_time, quantum));
    }

    int current_time = 0;
    while (!q1.empty() || !q2.empty())
    {

        if (!q1.empty())
        {
            Process p = q1.top();
            q1.pop();
            cout << "From queue 1 process " << p.pid << " is getting executed at time " << current_time << endl;
            int execution_time = min(p.rem_time, 2);
            current_time += execution_time;
            p.rem_time -= execution_time;

            if (p.rem_time > 0)
            {
                p.priority = 1;
                p.quantum = quantum;
                q2.push(p);
            }
            else
            {
                cout << "Process " << p.pid << " gets completed at " << current_time << endl;
            }
        }
        else if (!q2.empty())
        {
        
            Process p = q2.top();
            q2.pop();
            cout << "From queue 2 process " << p.pid << " is getting executed at time " << current_time << endl;

            int execution_time = min(p.rem_time, p.quantum);
            current_time += execution_time;
            p.rem_time -= execution_time;

            if (p.rem_time > 0)
            {
                p.quantum *= 2;
                q1.push(p);
            }
            else
            {
             
                cout << "Process " << p.pid << " gets completed at " << current_time << endl;
            }
        }
    }

    return 0;
}
