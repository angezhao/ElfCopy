//
//  CaptureScreen.h
//  ElfCopy
//
//  Created by Ange Zhao on 14-6-10.
//
//

#ifndef __ElfCopy__CaptureScreen__
#define __ElfCopy__CaptureScreen__

#include <iostream>

class CaptureScreen
{
public:
    static void startRecord();
    static void stopRecord();
    static void drawFrame();
};

#endif /* defined(__ElfCopy__CaptureScreen__) */
