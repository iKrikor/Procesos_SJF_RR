//
//  Process.h
//  Procesos
//
//  Created by Krikor Bisdikian on 10/15/15.
//  Copyright © 2015 Krikor Bisdikian. All rights reserved.
//

#ifndef Process_h
#define Process_h
#include <string>


//Clase proceso con su constructor y overload de los operadores logicos
class Process {
    public:
    std::string id;
    double arrival;
    double duration;
    double wait=0;
    
    Process(){};
    Process(std::string _id, double _arrival, double _duration);
    
    
    bool operator<(const Process & p) const;
    bool operator>(const Process & p) const;
    bool operator==(const Process & p)const;
    bool operator>=(const Process & p)const;
    bool operator<=(const Process & p)const;
    
    //Función que imprime el nombre y le tiempo de espera y regresa este ultimo
    double print() const;
    
};

#endif /* Process_h */
