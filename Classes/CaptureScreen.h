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
    static void stopRecord(const char * audioPath);
    static void drawFrame();
    static void saveVideo();
};

#endif /* defined(__ElfCopy__CaptureScreen__) */
