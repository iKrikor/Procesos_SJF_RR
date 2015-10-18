//
//  main.cpp
//  Procesos
//
//  Created by Krikor Bisdikian on 10/15/15.
//  Copyright © 2015 Krikor Bisdikian. All rights reserved.
//

#include <iostream>
#include "Process.h"
#include <queue>    
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> split(const std::string &s, char delim);

void getProcess(std::queue<Process> & process_start,double & quantum);
void nextArrives(std::list<Process> & process_queue, Process & next);
void incrementWait(std::list<Process> & process_queue);
bool compDouble(double a, double b);

int main(int argc, const char * argv[]) {

    
    std::list<Process> process_queue;
    std::queue<Process> process_start;
    std::vector<Process> terminados;
    double quantum;
    double time=0;
    Process excecuting;
    excecuting.duration=0;
    
    getProcess(process_start, quantum);
    
    
    while (!process_start.empty() || !process_queue.empty())
    {
//        std::cout<<" "<<time;
        
        if (process_start.empty())
        {
            if (compDouble(excecuting.duration,0)) {
                terminados.push_back(excecuting);
                std::cout<<" "<<time<<" "<<std::flush;
                excecuting=process_queue.front();
                process_queue.pop_front();
                std::cout<<"||"<<" "<<time<<" "<<std::flush;
                std::cout<<excecuting.id<<std::flush;
            }
        } else if (!process_queue.empty())
        {
            if (compDouble(excecuting.duration,0))
            {
                terminados.push_back(excecuting);
                if (process_start.front().arrival==time)
                {
                    if (process_start.front()<process_queue.front())
                    {
                        std::cout<<" "<<time<<" "<<std::flush;
                        excecuting=process_start.front();
                        process_start.pop();
                        std::cout<<"||"<<" "<<time<<" "<<std::flush;
                        std::cout<<excecuting.id<<std::flush;
                        
                    }else
                    {
                        std::cout<<" "<<time<<" "<<std::flush;
                        excecuting=process_queue.front();
                        process_queue.pop_front();
                        std::cout<<"||"<<" "<<time<<" "<<std::flush;
                        std::cout<<excecuting.id<<std::flush;
                        nextArrives(process_queue, process_start.front());
                        process_start.pop();
                        
                    }
                } else
                {
                    std::cout<<" "<<time<<" "<<std::flush;
                    excecuting=process_queue.front();
                    process_queue.pop_front();
                    std::cout<<"||"<<" "<<time<<" "<<std::flush;
                    std::cout<<excecuting.id<<std::flush;
                }
            } else if (compDouble(process_start.front().arrival,time))
            {
                if (process_start.front()<process_queue.front() && process_start.front()<excecuting)
                {
                    nextArrives(process_queue, excecuting);
                    std::cout<<" "<<time<<" "<<std::flush;
                    excecuting= process_start.front();
                    process_start.pop();
                    std::cout<<"||"<<" "<<time<<" "<<std::flush;
                    std::cout<<excecuting.id<<std::flush;
                    
                } else if (excecuting<=process_start.front() && excecuting<=process_queue.front())
                {
                    nextArrives(process_queue, process_start.front());
                    process_start.pop();
                } else
                {
                    Process aux;
                    std::cout<<" "<<time<<" "<<std::flush;
                    aux = excecuting;
                    excecuting=process_queue.front();
                    process_queue.pop_front();
                    nextArrives(process_queue, aux);
                    nextArrives(process_queue, process_start.front());
                    process_start.pop();
                    std::cout<<"||"<<" "<<time<<" "<<std::flush;
                    std::cout<<excecuting.id<<std::flush;
                    
                }
            }
        } else {
            if (compDouble(excecuting.duration,0))
            {
                terminados.push_back(excecuting);
                if (compDouble(process_start.front().arrival,time)) {
                    std::cout<<" "<<time<<" "<<std::flush;
                    excecuting = process_start.front();
                    process_start.pop();
                    std::cout<<"||"<<" "<<time<<" "<<std::flush;
                    std::cout<<excecuting.id<<std::flush;
                }else
                {
                    std::cout<<" "<<time<<" "<<std::flush;
                    std::cout<<"||"<<" "<<time<<" "<<std::flush;
                    std::cout<<"No process"<<std::flush;
                }
            }else if (compDouble(process_start.front().arrival,time))
            {
                if (process_start.front()<excecuting) {
                    nextArrives(process_queue, excecuting);
                    std::cout<<" "<<time<<" "<<std::flush;
                    excecuting=process_start.front();
                    process_start.pop();
                    std::cout<<"||"<<" "<<time<<" "<<std::flush;
                    std::cout<<excecuting.id<<std::flush;
                    
                }else
                {
                    nextArrives(process_queue, process_start.front());
                    process_start.pop();
                }
            }
        }

        time+=0.1;
        incrementWait(process_queue);
        excecuting.duration-=0.1;

        
        
    }
    std::cout<<" "<<time<<"||"<<std::endl;
    
    double wait;
    int c=0;
    for(auto i: terminados){
        wait+=i.print();
        c++;
    }
    
    std::cout<<"Tiempo promedio de espera: "<<wait/c<<std::endl;
    
    return 0;
}

bool compDouble(double a, double b){
    if (fabs(a-b) <1e-2) {
        return true;
    }else{
        return false;
    }
}


std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void nextArrives(std::list<Process> & process_queue, Process & next)
{
    
    if (process_queue.empty())
    {
        process_queue.push_back(next);
        return;
    }else
    {
        for (std::list<Process>::iterator it = process_queue.begin(); it != process_queue.end(); it++)
        {
            if (next<=*it)
            {
                process_queue.insert(it, next);
                return;
            }
        }
        process_queue.push_back(next);
        return;
    }
}

void incrementWait(std::list<Process> & process_queue){
    
    if (!process_queue.empty())
    {
    
        for (std::list<Process>::iterator it = process_queue.begin(); it != process_queue.end(); it++)
        {
            it->wait+=0.1;
        }
    }
}


void getProcess(std::queue<Process> & process_start, double & quantum){
    std::vector<std::string> text;
    bool p=true;
    
    std::string line;
    std::ifstream myfile;
    myfile.open("/Users/iKrikor/Library/Mobile\ Documents/com\~apple\~CloudDocs/Tec/5to\ Semestre/Sistemas\ Operativos/Procesos/Procesos/procesos.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line))
        {
            if(!p){
                text = split(line, ' ');
                
                process_start.push(Process(text[0],stof(text[1]), stof(text[2])));
            }else {
                quantum = stof(line);
            }
            p=false;
        }
        myfile.close();
    }else{
        std::cout<<"Unable"<<std::endl;
    }
    
    
}
