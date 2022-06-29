#include "../ta-utils.h"
#include "imgui.h"
#include <functional>
#include <vector>

#if defined(_WIN32) || defined(__APPLE__)
#define USE_NFD
#endif

#ifdef USE_NFD
#include <atomic>
#include <thread>

#ifdef __APPLE__
#define NFD_NON_THREADED
#endif

#else
namespace pfd {
  class open_file;
  class save_file;
}
#endif

typedef std::function<void(const char*)> FileDialogSelectCallback;

class FurnaceGUIFileDialog {
  bool sysDialog;
  bool opened;
  bool saving;
  String curPath;
  String fileName;
#ifdef USE_NFD
  std::thread* dialogO;
  std::thread* dialogS;
  std::atomic<bool> dialogOK;
  String nfdResult;
#else
  pfd::open_file* dialogO;
  pfd::save_file* dialogS;
#endif
  public:
    bool openLoad(String header, std::vector<String> filter, const char* noSysFilter, String path, double dpiScale, FileDialogSelectCallback clickCallback=NULL);
    bool openSave(String header, std::vector<String> filter, const char* noSysFilter, String path, double dpiScale);
    bool accepted();
    void close();
    bool render(const ImVec2& min, const ImVec2& max);
    bool isOpen();
    String getPath();
    String getFileName();
    explicit FurnaceGUIFileDialog(bool system):
      sysDialog(system),
      opened(false),
      saving(false),
      dialogO(NULL),
      dialogS(NULL) {}
};
