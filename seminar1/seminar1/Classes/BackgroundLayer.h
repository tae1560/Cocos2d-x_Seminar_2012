//
//  BackgroundLayer.h
//  Seminar1
//
//  Created by Tae-ho Lee on 12. 11. 28..
//
//

#ifndef Seminar1_BackgroundLayer_h
#define Seminar1_BackgroundLayer_h

// 재윤's TODO:
// UNTIL 1차 : 12/21 2차 : 12/26
// 총알을 맞았으면 빵빵 터졌으면 좋겠고요
// 당연히 소리도 빵빵 터져야 되구요
// 브금 있어야 하고요
// 자이로 스코프 써주세요
// 친구들과 대결하고 싶어요. (MULTIPLAY)
// 기록은 페북에다 올리고 싶어요
// 안드로이드에다가 심고 아이폰도 보고 싶구요 윈도우폰도?? 되면 좋겠네요

#include "common.h"

class BackgroundLayer : public CCLayer {
    float background_size;
    
public:
    bool init();
    
    void myScheduler(float dt);
};

#endif
