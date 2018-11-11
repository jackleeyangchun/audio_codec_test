#include <stdio.h>
#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/poll.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cutils/str_parms.h>
#include <cutils/sockets.h>

#include <system/audio.h>
#include <hardware/audio.h>

#include <hardware/hardware.h>
#include <cutils/log.h>
#include <dlfcn.h>
 
#define FNLOG()             ALOGV("%s", __FUNCTION__);
#define DEBUG(fmt, ...)     ALOGV("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)
#define INFO(fmt, ...)      ALOGI("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)
#define ERROR(fmt, ...)     ALOGE("%s: " fmt,__FUNCTION__, ## __VA_ARGS__) 
 
 
typedef int (*fn_sbc_codec_init)();
typedef int (*fn_sbc_codec_proc)(unsigned char *pBuf, unsigned int BufLen);

void *hDll = NULL;
fn_sbc_codec_init sbc_codec_init = NULL;
fn_sbc_codec_proc sbc_codec_proc = NULL;

int load_customer_library()
{
    int ret = 0;

    if (!hDll) {
        hDll = dlopen("/system/lib/libsbcdec.so", RTLD_NOW);
        if (!hDll) {
            ALOGI("Fail to load libsbcdec.so file (%s)", dlerror());
        } else {
            sbc_codec_init = (fn_sbc_codec_init) dlsym(hDll, "sbc_codec_init");
            sbc_codec_proc = (fn_sbc_codec_proc) dlsym(hDll, "sbc_codec_proc");
        }
		
        if (sbc_codec_init && sbc_codec_proc) {
            ret = 1;
        } else {
            ALOGI("Load libsbcdec.so function fail");
        }
    }
	
    return ret;
}
 
int main(int argc, char* argv[])
{
	unsigned char pBuf[10];
	unsigned int BufLen = 10;
	printf("%s,%d\n",__FILE__, __LINE__);
	
	load_customer_library();
	
	sbc_codec_init();
	
	sbc_codec_proc(pBuf,BufLen);
	
    return 0;
}

