//
//  krachObject.h
//  esoterionUniverse
//
//  Created by Borut Kumperscak on 25/07/2015.
//
//

#ifndef __esoterionUniverse__krachObject__
#define __esoterionUniverse__krachObject__

#include <stdio.h>

class krachObject {
    
public:
    krachObject();
    ~krachObject();
    
    void setup();
    void update();
    
    void setParam(int _param, float _val);
    float getParam(int _param);

};



#endif /* defined(__esoterionUniverse__krachObject__) */
