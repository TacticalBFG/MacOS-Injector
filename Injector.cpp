//
//  main.cpp
//  injector
//
//  Created by Owner on 7/19/20.
//  Copyright © 2020 Marco Villasuso. All rights reserved.
//

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <errno.h>
#include <libproc.h>
#include <unistd.h>
#include <vector>


std::vector<int> getPids(const char *name)
{
    std::vector<int> pidList;
    
    pid_t pids[2048];
    int bytes = proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    int nprocs = bytes / sizeof(pids[0]);
    for (int i = 0; i < nprocs; i++) {
        struct proc_bsdinfo proc;
        int st = proc_pidinfo(pids[i], PROC_PIDTBSDINFO, 0,
                              &proc, PROC_PIDTBSDINFO_SIZE);
        if (st == PROC_PIDTBSDINFO_SIZE) {
            if (strcmp(name, proc.pbi_name) == 0)
                pidList.push_back(pids[i]);
        }
    }
    
    return pidList;
}

int main() {
    system("clear"); /* Just looks cleaner cuz apple outputs all this text when u launch it */
    
    printf("~~ Helicity MacOS   -   Injecting; please wait. ~~\r\n\r\n");
    std::vector<int> list = getPids("RobloxPlayer");
    if (list.empty()) {
        std::cerr << "No Roblox process found.\n";
        return 1;
    }
    
    int rbxProc = list[list.size()-1];  // The actual client will always be the last process
    
    char pathbuff[PROC_PIDPATHINFO_MAXSIZE];
    
    int pret = proc_pidpath (getpid(), pathbuff, sizeof(pathbuff));
    if ( pret <= 0 ) {
        std::cerr << "Issue with proc_pidpath: " << strerror(errno) << std::endl;
        return 1;
    } else {
        std::string spath(pathbuff);
        spath = spath.substr(0,spath.find_last_of('/'))+"/Bin/";

        std::string cmd = spath + "./ShellInject.sh " + std::to_string(rbxProc);
        system(cmd.c_str()); /* Finish injection with shell script */
        
        printf("\r\n\r\n\r\n--- Injected! ---\r\n");
    }
    return 0;
}
