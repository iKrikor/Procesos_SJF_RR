//
//  SJF.cpp
//  Procesos
//
//  Created by Krikor Bisdikian on 10/19/15.
//  Copyright © 2015 Krikor Bisdikian. All rights reserved.
//

#include "SJF.h"
#include <iostream>

void SJF::excecute(){
    excecuting.duration=0;
    
    //Funcion que lee del archivo
    getProcess(process_start, quantum);
    
    //El ciclo no acaba hasta que las dos colas estén libres
    while (!process_start.empty() || !process_queue.empty())
    {
        //Si la cola inicial está vacia se revisa cuando acaba el proceso y se pone a ejecutar el siguiente
        if (process_start.empty())
        {
            if (compDouble(excecuting.duration,0)) {
                //Se guarda el que se terminó de ejecutar, se imprime el tiempo en que acabó y se saca el siguiente de la cola.
                terminados.push_back(excecuting);
                std::cout<<" "<<time<<" "<<std::flush;
                excecuting=process_queue.front();
                process_queue.pop_front();
                std::cout<<"||"<<" "<<time<<" "<<std::flush;
                std::cout<<excecuting.id<<std::flush;
            }
            //Si la cola inicial no está vacía, verificamos que la cola de procesos no esté vacía
        } else if (!process_queue.empty())
        {
            //Si se terminó de ejecutar un proceso
            if (compDouble(excecuting.duration,0))
            {
                //Lo guardamos
                terminados.push_back(excecuting);
                //Vemos si ya llegó uno nuevo
                if (compDouble(process_start.front().arrival,time))
                {
                    //Si es menor lo ejecutamos, si no lo ponemos en la cola y ejecutamos el primero de la cola.
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
                    //Si no llega ningun proceso cuando se termina de ejecutar uno, ejecutamos el siguiente
                    std::cout<<" "<<time<<" "<<std::flush;
                    excecuting=process_queue.front();
                    process_queue.pop_front();
                    std::cout<<"||"<<" "<<time<<" "<<std::flush;
                    std::cout<<excecuting.id<<std::flush;
                }
                //Si llega un proceso mientras se ejecuta el otro.
            } else if (compDouble(process_start.front().arrival,time))
            {
                //Revisamos cual de entre el que se ejecuta, el menor de la cola o el que acaba de llegar es menor y se ejecuta este. Poniendo en la cola los demás.
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
            //Si la cola que tiene procesos está vacía
        } else {
            //Si se termina de ejecutar un proceso, lo gurardamos
            if (compDouble(excecuting.duration,0))
            {
                terminados.push_back(excecuting);
                //Vemos si llegó uno nuevo y lo corremos, si no se imprime que no hay más procesos.
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
                //Si se está ejecutando un proceso y llega uno nuevo, se ve el menor y se ejecuta. El otro se pone en la cola
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
        
        //Se incrementa el tiempo de 0.1 en 0.1 segundos
        time+=0.1;
        //Función que incrementa el tiempo de espera de los procesos en la cola
        incrementWait(process_queue);
        //Le quita 0.1 al tiempo de ejecución.
        excecuting.duration-=0.1;
        
    }
    
    
    
    //Agrega el tiempo que quedó por ejecutarse del ultimo proceso
    std::cout<<" "<<time+excecuting.duration<<"||"<<std::endl;
    
    //Lo guarda
    terminados.push_back(excecuting);
    
    //Cuenta el tiempo de espera y saca el promedio
    double wait;
    int c=0;
    for(auto i: terminados){
        wait+=i.print();
        c++;
    }
    
    std::cout<<"Tiempo promedio de espera: "<<wait/c<<std::endl;
}


//Compara double para quitar la limitante de que no son exactos
bool SJF::compDouble(double a, double b){
    if (fabs(a-b) <1e-4) {
        return true;
    }else{
        return false;
    }
}

//Función que separa strings y las guarda en vectores
std::vector<std::string> & SJF::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> SJF::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


//Funcion que agrega elementos a la cola de manera ordenada
void SJF::nextArrives(std::list<Process> & process_queue, Process & next)
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

//Función que aumenta el tiempo de espera
void SJF::incrementWait(std::list<Process> & process_queue){
    
    if (!process_queue.empty())
    {
        
        for (std::list<Process>::iterator it = process_queue.begin(); it != process_queue.end(); it++)
        {
            it->wait+=0.1;
        }
    }
}



void SJF::getProcess(std::queue<Process> & process_start, double & quantum){
    std::vector<std::string> text;
    bool p=true;
    
    std::string line;
    std::ifstream myfile;
    myfile.open("./procesos.txt");
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
