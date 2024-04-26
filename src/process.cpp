#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "process.h"
#include "linux_parser.h"


using std::string;
using std::to_string;
using std::vector;

// DONE: Return this process's ID
int Process::Pid() { 
    return pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    int uptime = UpTime();
    string line, pid, brackets, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, utime, stime, cutime, cstime, starttime, rest;
    std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid_) +  LinuxParser::kStatFilename);
    if (filestream.is_open()) {
        std::getline(filestream, line);
        std::istringstream linestream(line);
        linestream >> pid >> brackets >> val1 >> val2 >> val3 >> val4>> val5 >> val6 >> val7 >> val8>> val9 >> val10 >> utime >> stime>> cutime >> cstime>> starttime >> rest;
        float total_time, seconds;
        total_time = stof(utime) + stof(stime) + stof(cutime) + stof(cstime);
        seconds = uptime - stof(starttime);
        return total_time/seconds;
    }
    return 0;
}

// DONE: Return the command that generated this process
string Process::Command() { 
    return LinuxParser::Command(pid_); 
    }

// DONE: Return this process's memory utilization
string Process::Ram() { return 
    LinuxParser::Ram(pid_); 
    }

// DONE: Return the user (name) that generated this process
string Process::User() { 
    return LinuxParser::User(pid_); }

// DONE: Return the age of this process (in seconds)
long int Process::UpTime() { 
    return LinuxParser::UpTime() - LinuxParser::UpTime(pid_); 
    }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
//bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }