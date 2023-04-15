#include <iostream>
#include <queue>
using namespace std;
struct Process
{
    int pid;            
    int priority;       
    int burst_time;     
    int remaining_time; 
    int quantum;        
    Process(int pid, int priority, int burst_time, int quantum)
    {
        this->pid = pid;
        this->priority = priority;
        this->burst_time = burst_time;
        this->remaining_time = burst_time;
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
struct CompareRR
{
    bool operator()(const Process &p1, const Process &p2)
    {
        return p1.remaining_time < p2.remaining_time;
    }
};

int main()
{
    int num_processes, quantum;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the time quantum for round robin scheduling: ";
    cin >> quantum;
    priority_queue<Process, vector<Process>, ComparePriority> q1;
    priority_queue<Process, vector<Process>, CompareRR> q2;
    for (int i = 0; i < num_processes; i++)
    {
        int pid, priority, burst_time;
        cout << "Enter details for process " << i + 1 << endl;
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
            cout << "Executing process " << p.pid << " from queue 1 at time " << current_time << endl;
            int execution_time = min(p.remaining_time, 2);
            current_time += execution_time;
            p.remaining_time -= execution_time;

            if (p.remaining_time > 0)
            {
                p.priority = 1;
                p.quantum = quantum;
                q2.push(p);
            }
            else
            {
                cout << "Process " << p.pid << " completed at time " << current_time << endl;
            }
        }
        else if (!q2.empty())
        {
        
            Process p = q2.top();
            q2.pop();
            cout << "Executing process " << p.pid << " from queue 2 at time " << current_time << endl;

            int execution_time = min(p.remaining_time, p.quantum);
            current_time += execution_time;
            p.remaining_time -= execution_time;

            if (p.remaining_time > 0)
            {
                p.quantum *= 2;
                q1.push(p);
            }
            else
            {
             
                cout << "Process " << p.pid << " completed at time " << current_time << endl;
            }
        }
    }

    return 0;
}
