/* definitions */
#include "pch.h"
#ifdef _WIN32
#define EXPORT extern "C" __declspec(dllexport)
#else
#define EXPORT extern "C"
#endif /* _WIN32 */

#define LOGFILENAME "MessageLogMaster.txt"         /* ログファイルのファイル名 */
#define PLUGINLOGMESSAGE_NAME "LogMessageMaster"   /* プラグインの名前 */

/* ログファイル関係のメッセージタイプ（自由に内部メッセージタイプを設定できる） */
#define MMDAGENT_EVENT_FILEOPEN "LOGMESSAGE_EVENT_FILEOPEN"
#define MMDAGENT_EVENT_FILECLOSE "LOGMESSAGE_EVENT_FILECLOSE"

/* headers */
#include "MMDAgent.h"
#include <fstream>
#include <ctime>

/* variables */
static bool enable;
static std::ofstream ofs;
static time_t t;
static tm* x;


EXPORT void extAppStart(MMDAgent* mmdagent)
{
    if (mmdagent == nullptr) {
        printf("Error: mmdagent instance is null.\n");
        return;
    }

    enable = true;

    
    const char* fileName = LOGFILENAME;

   
    ofs.open(fileName, std::ios::out | std::ios::app);
    if (!ofs) {

        mmdagent->sendMessage(MMDAGENT_EVENT_FILEOPEN, "%s can not be opened!", fileName);
    }
    else {
       
        mmdagent->sendMessage(MMDAGENT_EVENT_FILEOPEN, "%s can be opened", fileName);

      
        t = time(0);
        char buf[32];
        ctime_s(buf, sizeof(buf), &t);

   
        ofs << buf;
        ofs << "[[Start]]" << std::endl;
    }
}


EXPORT void extProcMessage(MMDAgent* mmdagent, const char* type, const char* args)
{
    if (enable && type != nullptr) {
        
        ofs << type << "|" << (args ? args : "null") << std::endl;

    }
}


EXPORT void extAppEnd(MMDAgent* mmdagent)
{
    ofs << "[[End]]" << std::endl;
    ofs << std::endl;

 
    ofs.close();

}


EXPORT void extUpdate(MMDAgent* mmdagent, double deltaFrame)
{
  
}


EXPORT void extRender(MMDAgent* mmdagent)
{
   
}