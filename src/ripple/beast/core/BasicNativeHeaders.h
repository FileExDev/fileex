

#ifndef BEAST_MODULE_CORE_NATIVE_BASICNATIVEHEADERS_H_INCLUDED
#define BEAST_MODULE_CORE_NATIVE_BASICNATIVEHEADERS_H_INCLUDED

#include <ripple/beast/core/Config.h>

#undef T

#if BEAST_MAC || BEAST_IOS

 #if BEAST_IOS
  #ifdef __OBJC__
    #import <Foundation/Foundation.h>
    #import <UIKit/UIKit.h>
    #import <CoreData/CoreData.h>
    #import <MobileCoreServices/MobileCoreServices.h>
  #endif
  #include <sys/fcntl.h>
 #else
  #ifdef __OBJC__
    #define Point CarbonDummyPointName
    #define Component CarbonDummyCompName
    #import <Cocoa/Cocoa.h>
    #import <CoreAudio/HostTime.h>
    #undef Point
    #undef Component
  #endif
  #include <sys/dir.h>
 #endif

 #include <sys/socket.h>
 #include <sys/sysctl.h>
 #include <sys/stat.h>
 #include <sys/param.h>
 #include <sys/mount.h>
 #include <sys/utsname.h>
 #include <sys/mman.h>
 #include <fnmatch.h>
 #include <utime.h>
 #include <dlfcn.h>
 #include <ifaddrs.h>
 #include <net/if_dl.h>
 #include <mach/mach_time.h>
 #include <mach-o/dyld.h>
 #include <objc/runtime.h>
 #include <objc/objc.h>
 #include <objc/message.h>

#elif BEAST_WINDOWS
 #if BEAST_MSVC
  #ifndef _CPPRTTI
   #error "Beast requires RTTI!"
  #endif

  #ifndef _CPPUNWIND
   #error "Beast requires RTTI!"
  #endif

  #pragma warning (push)
  #pragma warning (disable : 4100 4201 4514 4312 4995)
 #endif

 #define STRICT 1
 #define WIN32_LEAN_AND_MEAN 1
 #ifndef _WIN32_WINNT
  #if BEAST_MINGW
   #define _WIN32_WINNT 0x0501
  #else
   #define _WIN32_WINNT 0x0600
  #endif
 #endif
 #define _UNICODE 1
 #define UNICODE 1
 #ifndef _WIN32_IE
  #define _WIN32_IE 0x0400
 #endif

 #include <windows.h>
 #include <shellapi.h>
 #include <tchar.h>
 #include <stddef.h>
 #include <ctime>
 #include <wininet.h>
 #include <nb30.h>
 #include <iphlpapi.h>
 #include <mapi.h>
 #include <float.h>
 #include <process.h>
 #pragma warning ( push )
 #pragma warning ( disable: 4091 )
 #include <shlobj.h>
 #pragma warning ( pop )
 #include <shlwapi.h>
 #include <mmsystem.h>

 #if BEAST_MINGW
  #include <basetyps.h>
 #else
  #include <crtdbg.h>
  #include <comutil.h>
 #endif

 #undef PACKED

 #if BEAST_MSVC
  #pragma warning (pop)
  #pragma warning (4: 4511 4512 4100 )  
 #endif

 #if BEAST_MSVC && ! BEAST_DONT_AUTOLINK_TO_WIN32_LIBRARIES
  #pragma comment (lib, "kernel32.lib")
  #pragma comment (lib, "user32.lib")
  #pragma comment (lib, "wininet.lib")
  #pragma comment (lib, "advapi32.lib")
  #pragma comment (lib, "ws2_32.lib")
  #pragma comment (lib, "version.lib")
  #pragma comment (lib, "shlwapi.lib")
  #pragma comment (lib, "winmm.lib")

  #ifdef _NATIVE_WCHAR_T_DEFINED
   #ifdef _DEBUG
    #pragma comment (lib, "comsuppwd.lib")
   #else
    #pragma comment (lib, "comsuppw.lib")
   #endif
  #else
   #ifdef _DEBUG
    #pragma comment (lib, "comsuppd.lib")
   #else
    #pragma comment (lib, "comsupp.lib")
   #endif
  #endif
 #endif

#elif BEAST_LINUX || BEAST_BSD
 #include <sched.h>
 #include <pthread.h>
 #include <sys/time.h>
 #include <errno.h>
 #include <sys/stat.h>
 #include <sys/ptrace.h>
 #include <sys/wait.h>
 #include <sys/mman.h>
 #include <fnmatch.h>
 #include <utime.h>
 #include <pwd.h>
 #include <fcntl.h>
 #include <dlfcn.h>
 #include <netdb.h>
 #include <arpa/inet.h>
 #include <netinet/in.h>
 #include <sys/types.h>
 #include <sys/ioctl.h>
 #include <sys/socket.h>
 #include <net/if.h>
 #include <sys/file.h>
 #include <signal.h>
 #include <stddef.h>

 #if BEAST_BSD
  #include <dirent.h>
  #include <ifaddrs.h>
  #include <net/if_dl.h>
  #include <kvm.h>
  #include <langinfo.h>
  #include <sys/cdefs.h>
  #include <sys/param.h>
  #include <sys/mount.h>
  #include <sys/types.h>
  #include <sys/sysctl.h>

  extern char** environ;

 #else
  #include <sys/dir.h>
  #include <sys/vfs.h>
  #include <sys/sysinfo.h>
  #include <sys/prctl.h>
 #endif

#elif BEAST_ANDROID
 #include <jni.h>
 #include <pthread.h>
 #include <sched.h>
 #include <sys/time.h>
 #include <utime.h>
 #include <errno.h>
 #include <fcntl.h>
 #include <dlfcn.h>
 #include <sys/stat.h>
 #include <sys/statfs.h>
 #include <sys/ptrace.h>
 #include <sys/sysinfo.h>
 #include <sys/mman.h>
 #include <pwd.h>
 #include <dirent.h>
 #include <fnmatch.h>
 #include <sys/wait.h>
#endif

#undef max
#undef min
#undef direct
#undef check


#include <ripple/beast/core/LexicalCast.h>
#include <ripple/beast/core/SemanticVersion.h>

#include <locale>
#include <cctype>

#if ! BEAST_BSD
 #include <sys/timeb.h>
#endif

#if ! BEAST_ANDROID
 #include <cwctype>
#endif

#if BEAST_WINDOWS
 #include <ctime>
 #include <winsock2.h>
 #include <ws2tcpip.h>

 #if ! BEAST_MINGW
  #pragma warning ( push )
  #pragma warning ( disable: 4091 )
  #include <Dbghelp.h>
  #pragma warning ( pop )

  #if ! BEAST_DONT_AUTOLINK_TO_WIN32_LIBRARIES
   #pragma comment (lib, "DbgHelp.lib")
  #endif
 #endif

 #if BEAST_MINGW
  #include <ws2spi.h>
 #endif

#else
 #if BEAST_LINUX || BEAST_ANDROID
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <unistd.h>
  #include <netinet/in.h>
 #endif

 #if BEAST_LINUX
  #include <langinfo.h>
 #endif

 #include <pwd.h>
 #include <fcntl.h>
 #include <netdb.h>
 #include <arpa/inet.h>
 #include <netinet/tcp.h>
 #include <sys/time.h>
 #include <net/if.h>
 #include <sys/ioctl.h>
#endif	

#if BEAST_MAC || BEAST_IOS
 #include <xlocale.h>
 #include <mach/mach.h>
#endif

#if BEAST_ANDROID
 #include <android/log.h>
#endif

#endif   








