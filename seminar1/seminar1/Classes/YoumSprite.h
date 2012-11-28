//
//  YoumSprite.h
//  Seminar1
//
//  Created by Tae-ho Lee on 12. 11. 28..
//
//

#ifndef Seminar1_YoumSprite_h
#define Seminar1_YoumSprite_h

#include "common.h"

class YoumSprite : public CCSprite {
private:
    int hp;
    
public:
    
    static YoumSprite* create(const char *pszFileName);
    
    // decrease hp
    void decrease_hp(int damage);
    bool is_alive();
};

#endif
