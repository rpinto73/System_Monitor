#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// DONE: Return the system's CPU
Processor& System::Cpu() { 
    Processor Proc1;
    cpu_ = Proc1;
    return cpu_; }

// DONE: Return a container composed of the system's processes
std::vector<Process>& System::Processes() { 
    vector<int> pids = LinuxParser::Pids();
    for (int pid : pids){
        Process proc2(pid);
        processes_.push_back(proc2);

    return processes_;

    // alternate way of writing this function:

    // for(int _pid: pids){
    //    processes_.emplace_back(_pid);}
    // return processes_; 
    }
}

// DONE: Return the system's kernel identifier (string)
std::string System::Kernel() { 
    return LinuxParser::Kernel(); 
    }

// DONE: Return the system's memory utilization
float System::MemoryUtilization() { 
    return LinuxParser::MemoryUtilization(); }

// DONE: Return the operating system name
std::string System::OperatingSystem() { 
    return LinuxParser::OperatingSystem(); 
    }

// DONE: Return the number of processes actively running on the system
int System::RunningProcesses() { 
    return LinuxParser::RunningProcesses(); 
    }

// DONE: Return the total number of processes on the system
int System::TotalProcesses() { 
    return LinuxParser::TotalProcesses(); 
    }

// DONE: Return the number of seconds since the system started running
long int System::UpTime() { 
    return LinuxParser::UpTime(); 
    }