#include <string.h>
#include <jni.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


char* jstring_to_pchar(JNIEnv* env, jstring str)
{
	char* pstr = NULL;
	jclass clsstring = (*env)->FindClass(env, "java/lang/String");
	jstring strencode = (*env)->NewStringUTF(env, "utf-8");
	jmethodID mid = (*env)->GetMethodID(env, clsstring, "getBytes",
		        "(Ljava/lang/String;)[B");
	jbyteArray byteArray = (jbyteArray)(
		        (*env)->CallObjectMethod(env, str, mid, strencode));
	jsize size = (*env)->GetArrayLength(env, byteArray);
	jbyte* pbyte = (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);
	if (size > 0)
	{
		pstr = (char*) malloc(size);
		memcpy(pstr, pbyte, size);
	}
	return pstr;
}
void Java_mobile_android_s3c6410_leds_ndk_S3C6410LedsMain_strLeds(
        JNIEnv* env, jobject thiz, jstring str)
{

	int dev;
	dev = open("/dev/s3c6410_leds", O_WRONLY);
	char* pstr = jstring_to_pchar(env, str);
	if (pstr != NULL)
	{
		write(dev,pstr, strlen(pstr));
	}
	close(dev);
}

void Java_mobile_android_s3c6410_leds_ndk_S3C6410LedsMain_cmdLeds(
        JNIEnv* env, jobject thiz, jint cmd, jint arg)
{

	int dev;
	dev = open("/dev/s3c6410_leds", O_WRONLY);
    ioctl(dev, cmd, arg);
	close(dev);
}
