#ifndef MOZC_CLIENT_MOZC_CLIENT_H_
#define MOZC_CLIENT_MOZC_CLIENT_H_

#include <memory>
#include <string>
#include <string_view>

#include "protocol/commands.pb.h"
#include "protocol/config.pb.h"

namespace mozc {
namespace client {
class Client;
}  // namespace client

class MozcClient {
 public:
  MozcClient();
  ~MozcClient() = default;

  // Initializes `request_` with the flag.
  // This function should be called before EnsureSession.
  void InitRequestForSvsJapanese(bool use_svs);

  bool EnsureConnection();

  bool EnsureSession();

  bool CheckVersionOrRestartServer();

  bool SendKeyWithContext(const commands::KeyEvent& key,
                          const commands::Context& context,
                          commands::Output* output);
  bool TestSendKeyWithContext(const commands::KeyEvent& key,
                              const commands::Context& context,
                              commands::Output* output);
  bool SendCommandWithContext(const commands::SessionCommand& command,
                              const commands::Context& context,
                              commands::Output* output);

  bool IsDirectModeCommand(const commands::KeyEvent& key) const;

  bool GetConfig(config::Config* config);
  bool SetConfig(const config::Config& config);

  bool ClearUserHistory();
  bool ClearUserPrediction();
  bool ClearUnusedUserPrediction();
  bool Shutdown();
  bool SyncData();
  bool Reload();
  bool Cleanup();

  bool NoOperation();
  bool PingServer() const;

  void Reset();

  void EnableCascadingWindow(bool enable);

  void set_restricted(bool restricted);
  void set_suppress_error_dialog(bool suppress);
  void set_client_capability(const commands::Capability& capability);

  bool LaunchTool(const std::string& mode, std::string_view arg);
  bool LaunchToolWithProtoBuf(const commands::Output& output);
  // Converts Output message from server to corresponding mozc_tool arguments
  // If launch_tool_mode is not set or NO_TOOL is set or an invalid value is
  // set, this function will return false and do nothing.
  static bool TranslateProtoBufToMozcToolArg(const commands::Output& output,
                                             std::string* mode);

  bool OpenBrowser(const std::string& url);

 private:
  std::unique_ptr<client::Client> client_;
};
}  // namespace mozc

#endif  // MOZC_CLIENT_MOZC_CLIENT_H_
