#include "processor.h"
#include "linux_parser.h"
#include <vector>

// DONE: Return the aggregate CPU utilization
float Processor::Utilization() { 
    float totalCPUjiffies = 0;

    std::vector<std::string> CpuJiffiesVector = LinuxParser::CpuUtilization();

    for (std::string jiffy: CpuJiffiesVector){
    
        totalCPUjiffies += std::stof(jiffy);
    }
    
    return (100*LinuxParser::TotalProcesses()/ totalCPUjiffies);
    }