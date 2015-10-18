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


class Process {
    public:
    std::string id;
    double arrival;
    double duration;
    double wait;
    
    Process(){};
    Process(std::string _id, double _arrival, double _duration);
    
    
    bool operator<(const Process & p) const;
    bool operator>(const Process & p) const;
    bool operator==(const Process & p)const;
    bool operator>=(const Process & p)const;
    bool operator<=(const Process & p)const;
    
    double print() const;
    
};

#endif /* Process_h */
