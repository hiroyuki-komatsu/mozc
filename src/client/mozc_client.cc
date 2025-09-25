#include "client/mozc_client.h"

#include <memory>
#include <string>
#include <string_view>

#include "client/client.h"
#include "protocol/commands.pb.h"
#include "protocol/config.pb.h"

namespace mozc {
MozcClient::MozcClient() : client_(std::make_unique<client::Client>()) {}

void MozcClient::InitRequestForSvsJapanese(bool use_svs) {
  client_->InitRequestForSvsJapanese(use_svs);
}

bool MozcClient::EnsureConnection() { return client_->EnsureConnection(); }

bool MozcClient::EnsureSession() { return client_->EnsureSession(); }

bool MozcClient::CheckVersionOrRestartServer() {
  return client_->CheckVersionOrRestartServer();
}

bool MozcClient::SendKeyWithContext(const commands::KeyEvent& key,
                                    const commands::Context& context,
                                    commands::Output* output) {
  return client_->SendKeyWithContext(key, context, output);
}
bool MozcClient::TestSendKeyWithContext(const commands::KeyEvent& key,
                                        const commands::Context& context,
                                        commands::Output* output) {
  return client_->TestSendKeyWithContext(key, context, output);
}
bool MozcClient::SendCommandWithContext(const commands::SessionCommand& command,
                                        const commands::Context& context,
                                        commands::Output* output) {
  return client_->SendCommandWithContext(command, context, output);
}

bool MozcClient::IsDirectModeCommand(const commands::KeyEvent& key) const {
  return client_->IsDirectModeCommand(key);
}

bool MozcClient::GetConfig(config::Config* config) {
  return client_->GetConfig(config);
}
bool MozcClient::SetConfig(const config::Config& config) {
  return client_->SetConfig(config);
}

bool MozcClient::ClearUserHistory() { return client_->ClearUserHistory(); }
bool MozcClient::ClearUserPrediction() {
  return client_->ClearUserPrediction();
}
bool MozcClient::ClearUnusedUserPrediction() {
  return client_->ClearUnusedUserPrediction();
}
bool MozcClient::Shutdown() { return client_->Shutdown(); }
bool MozcClient::SyncData() { return client_->SyncData(); }
bool MozcClient::Reload() { return client_->Reload(); }
bool MozcClient::Cleanup() { return client_->Cleanup(); }

bool MozcClient::NoOperation() { return client_->NoOperation(); }
bool MozcClient::PingServer() const { return client_->PingServer(); }

void MozcClient::Reset() { client_->Reset(); }

void MozcClient::EnableCascadingWindow(bool enable) {
  client_->EnableCascadingWindow(enable);
}

void MozcClient::set_restricted(bool restricted) {
  client_->set_restricted(restricted);
}
void MozcClient::set_suppress_error_dialog(bool suppress) {
  client_->set_suppress_error_dialog(suppress);
}
void MozcClient::set_client_capability(const commands::Capability& capability) {
  client_->set_client_capability(capability);
}

bool MozcClient::LaunchTool(const std::string& mode, std::string_view arg) {
  return client_->LaunchTool(mode, arg);
}
bool MozcClient::LaunchToolWithProtoBuf(const commands::Output& output) {
  return client_->LaunchToolWithProtoBuf(output);
}
// Converts Output message from server to corresponding mozc_tool arguments
// If launch_tool_mode is not set or NO_TOOL is set or an invalid value is
// set, this function will return false and do nothing.
bool MozcClient::TranslateProtoBufToMozcToolArg(const commands::Output& output,
                                                std::string* mode) {
  return client::Client::TranslateProtoBufToMozcToolArg(output, mode);
}

bool MozcClient::OpenBrowser(const std::string& url) {
  return client_->OpenBrowser(url);
}

}  // namespace mozc
