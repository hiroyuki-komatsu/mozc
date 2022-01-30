// Copyright 2010-2021, Google Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Google Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include <QGuiApplication>
#include <QTextCodec>
#include <QTranslator>
#include <string>

#include "base/logging.h"
#include "base/system_util.h"
#include "gui/base/singleton_window_helper.h"
#include "gui/base/util.h"
#include "gui/dictionary_tool/dictionary_tool.h"

#ifdef OS_WIN
#include "base/win_util.h"
#endif  // OS_WIN

int RunDictionaryTool(int argc, char *argv[]) {
#ifdef OS_WIN
  // For MSIMEImportIterator.
  mozc::ScopedCOMInitializer com_initializer;
#endif  // OS_WIN

  Q_INIT_RESOURCE(qrc_dictionary_tool);
  auto app = mozc::gui::GuiUtil::InitQt(argc, argv);

  std::string name = "dictionary_tool.";
  name += mozc::SystemUtil::GetDesktopNameAsString();
  mozc::gui::SingletonWindowHelper window_helper(name);
  if (window_helper.FindPreviousWindow()) {
    // already running
    window_helper.ActivatePreviousWindow();
    return -1;
  }

  mozc::gui::GuiUtil::InstallTranslator("dictionary_tool");
  mozc::gui::DictionaryTool window;

  if (!window.IsAvailable()) {
    LOG(ERROR) << "DictionaryTool is not available.";
    return -1;
  }

  window.show();
  window.raise();

  return app->exec();
}
