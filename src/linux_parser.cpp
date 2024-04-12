#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// DONE: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  std::string line;
  std::string key;
  std::string value;
  float memUtil = 0 ;
  float memTotal = 0 ;
  float memFree = 0 ;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ') ;
      std::istringstream linestream(line);
      
      while (linestream >> key >> value) { 
        if (key == "MemTotal") {
          memTotal = std::stof(value);
        }
        if (key == "MemFree") {
          memFree = std::stof(value);
        }
      }
      memUtil = (memTotal-memFree)/memTotal ;
    }
  return memUtil;   
  }

// DONE: Read and return the system uptime
long LinuxParser::UpTime() { 
    long uptime_l = 0;
    std::string uptime; 
    std::string idleTime;
    std::string line;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
    if (stream.is_open()) {
        std::getline(stream, line);
        std::istringstream linestream(line);
        while(linestream >> uptime >> idleTime){            
            uptime_l = std::stol(uptime);
        }  //convert string to long
    
    }  
  return uptime_l;
 }

// DONE: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  std::string line, cpu, val_user, val_nice, val_system, val_idle, val_iowait, val_irq, val_softirq, val8, val9, val10;
  long total_jiffies = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> val_user>>val_nice>>val_system>>val_idle>>val_iowait>>val_irq>>val_softirq>>val8>>val9>>val10;
    if(cpu == "cpu"){
    total_jiffies += stol(val_user)+ stol(val_nice)+ stol(val_system)+ stol(val_idle)+ stol(val_iowait)+ stol(val_irq)+ stol(val_softirq)+ stol(val8)+ stol(val9)+ stol(val10);}
  }
  return total_jiffies;
  }

// DONE: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  std::string line, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12, val13, val14, val15, val16, val17,valrest;
  long total_ticks = 0;
  long total_jiffies=0;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >>val1>>val2>>val3>>val4>>val5>>val6>>val7>>val8>>val9>>val10>>val11>>val12>>val13>>val14>>val5>>val16>>val17>>valrest;
    
    total_ticks += stol(val14)+ stol(val15)+ stol(val16)+ stol(val17);
    
    total_jiffies = total_ticks/sysconf(_SC_CLK_TCK);
  }
  return total_jiffies;

 }

// DONE: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  std::string line, cpu, val_user, val_nice, val_system, val_rest;
  long total_jiffies = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> val_user>>val_nice>>val_system>>val_rest;
    if(cpu == "cpu"){
    total_jiffies += stol(val_user)+ stol(val_nice)+ stol(val_system);}
  }
  return total_jiffies;
 }

// DONE: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
  std::string line, cpu, val_user, val_nice, val_system, val_idle, val_iowait, val_irq, val_softirq, val8, val9, val10;
  long total_jiffies = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> val_user>>val_nice>>val_system>>val_idle>>val_iowait>>val_irq>>val_softirq>>val8>>val9>>val10;
    if(cpu == "cpu"){
    total_jiffies += stol(val_idle);}
  }
  return total_jiffies;
}

// DONE: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  vector<string> cpuUtilizationVec;
  string line, cpu, val_user, val_nice, val_system, val_idle, val_iowait, val_irq, val_softirq, val_steal, val_guest, val_guest_nice;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> val_user>>val_nice>>val_system>>val_idle>>val_iowait>>val_irq>>val_softirq>>val_steal>>val_guest>>val_guest_nice;
    if (cpu == "cpu"){
    cpuUtilizationVec.push_back(val_user);
    cpuUtilizationVec.push_back(val_nice);
    cpuUtilizationVec.push_back(val_system);
    cpuUtilizationVec.push_back(val_idle);
    cpuUtilizationVec.push_back(val_iowait);
    cpuUtilizationVec.push_back(val_irq);
    cpuUtilizationVec.push_back(val_softirq);
    cpuUtilizationVec.push_back(val_steal);
    cpuUtilizationVec.push_back(val_guest);
    cpuUtilizationVec.push_back(val_guest_nice);
    }
  }
  return cpuUtilizationVec;
 }

// DONE: Read and return the total number of processes
int LinuxParser::TotalProcesses() {   
  std::string line, key, value;
  float totalProcesses = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          totalProcesses = std::stof(value);
        }
      }
    }
return totalProcesses;
}

// DONE: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  std::string line, key, value;
  float runningProcesses = 0;
  std::ifstream stream(kProcDirectory + kStatFilename);
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          runningProcesses = std::stof(value);
        }
      }
    }
  return runningProcesses; 
   }

// DONE: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Command(int pid) {
  std::string line;
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) +  LinuxParser::kCmdlineFilename);
  if (filestream.is_open()) {
      std::getline(filestream, line);
      std::istringstream linestream(line);
      linestream >> line;
  }
  return line;
 }

// DONE: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Ram(int pid) { 
  std::string line, key, value;
  long mem_util;
  std::ifstream stream(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatusFilename);
  while (std::getline(stream, line)) {
    std::istringstream linestream(line);
    while (linestream >> key >> value) {
      if (key == "VmSize:") {
        mem_util = std::stol(value)/1000; //conversion to MB
      }
    }
  }
  return to_string(mem_util);

 }

// DONE: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
std::string LinuxParser::Uid(int pid) { 
  std::string line, key, value, uid1, uidrest;
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) +  LinuxParser::kStatusFilename);
  if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
        std::replace(line.begin(), line.end(), ' ', '_');
        std::replace(line.begin(), line.end(), '=', ' ');
        std::replace(line.begin(), line.end(), '"', ' ');
        std::istringstream linestream(line);
        while (linestream >> key >> uid1 >> uidrest) {
            if (key == "Uid:") {
               return uid1;
        }
      }
    }    
  }
  return "No User ID found for PID " + to_string(pid);
 }

// DONE: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
  string uid = Uid(pid);
  string line, name, passwd, gid, value, val ;
  std::ifstream filestream(LinuxParser::kPasswordPath);
  if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
        std::replace(line.begin(), line.end(), ':', ' ');
        std::istringstream linestream(line);
        while (linestream >> name >> passwd >> gid >> value >> val) {
            if (gid == uid) {
               return name;
          }
        }
      }
    }
  return "No user name found";

 }

// DONE: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  std::string line, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10, val11, val12, 
  val13, val14, val15, val16, val17, val18, val19, val20, val21, val22, valrest;
  string value; 
  std::ifstream filestream(kProcDirectory + std::to_string(pid) + kStatFilename); 
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >>val1>>val2>>val3>>val4>>val5>>val6>>val7>>val8>>val9>>val10>>val11>>val12>>val13>>val14>>val5>>
      val16>>val17>>val18>> val19>> val20>> val21>> val22>> valrest; //val22 is uptime in clock ticks
  
    return stol(val22)/sysconf(_SC_CLK_TCK); 
  }
return 0;
}
