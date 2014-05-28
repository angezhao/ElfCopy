#include "cocos2d.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include "JavaToC.h"
#include "JavaCall.h"

using namespace cocos2d;

extern "C"
{

	void Java_org_cocos2dx_cpp_AppActivity_setPhotoPath(JNIEnv *env, jobject thiz, jstring packageName)
	{
		const char *pkgName = env->GetStringUTFChars(packageName, NULL);
		setPhotoPath(pkgName);
		env->ReleaseStringUTFChars(packageName, pkgName);
	}

}
