//
//  Process.cpp
//  Procesos
//
//  Created by Krikor Bisdikian on 10/15/15.
//  Copyright © 2015 Krikor Bisdikian. All rights reserved.
//

#include "Process.h"

#include <iostream>

Process::Process(std::string _id, double _arrival, double _duration){
    id = _id;
    arrival= _arrival;
    duration = _duration;
}

bool Process::operator<(const Process & p)const { return this->duration< p.duration;}
bool Process::operator>(const Process & p)const{ return this->duration>p.duration;}
bool Process::operator==(const Process & p)const{ return this->duration==p.duration;}
bool Process::operator>=(const Process & p)const{ return this->duration>=p.duration;}
bool Process::operator<=(const Process & p)const{ return this->duration<=p.duration;}

double Process::print() const{
    std::cout<<this->id<<": "<<this->wait<<std::endl;
    
    return this->wait;
    
}
