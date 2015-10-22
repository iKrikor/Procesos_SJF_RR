//
//  SJF.h
//  Procesos
//
//  Created by Krikor Bisdikian on 10/19/15.
//  Copyright © 2015 Krikor Bisdikian. All rights reserved.
//

#ifndef SJF_h
#define SJF_h

#include <queue>
#include "Process.h"
#include <list>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <math.h>

class SJF {
    
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    
    std::vector<std::string> split(const std::string &s, char delim);
    
    void getProcess(std::queue<Process> & process_start,double & quantum);
    void nextArrives(std::list<Process> & process_queue, Process & next);
    void incrementWait(std::list<Process> & process_queue);
    bool compDouble(double a, double b);
    
    //Estructura de lista para la cola ordenada (para poder iterar sobre ella)
    std::list<Process> process_queue;
    //Estructura de cola para los procesos iniciales
    std::queue<Process> process_start;
    //Guardamos los procesos terminados ya que el tiempo de espera se almacena en ellos
    std::vector<Process> terminados;
    double quantum;
    double time=0;
    Process excecuting;
public:
    
    void excecute();

    
};


#endif /* SJF_h */
