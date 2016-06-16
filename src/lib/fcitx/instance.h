/*
 * Copyright (C) 2016~2016 by CSSlayer
 * wengxt@gmail.com
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; see the file COPYING. If not,
 * see <http://www.gnu.org/licenses/>.
 */
#ifndef _FCITX_INSTANCE_H_
#define _FCITX_INSTANCE_H_

#include <memory>
#include <fcitx-utils/macros.h>
#include <fcitx-utils/handlertable.h>
#include "event.h"
#include "fcitxcore_export.h"
#include "globalconfig.h"

namespace fcitx {

class InputContext;
class KeyEvent;
class InstancePrivate;
class EventLoop;
class AddonManager;
class InputContextManager;
class InputMethodManager;
class GlobalConfig;
typedef std::function<void(Event &event)> EventHandler;
enum class EventWatcherPhase { PreInputMethod, InputMethod, PostInputMethod, Default = PostInputMethod };

class FCITXCORE_EXPORT Instance {
public:
    Instance(int argc, char *argv[]);
    ~Instance();

    void setSignalPipe(int fd);
    int exec();
    bool willTryReplace() const;

    EventLoop &eventLoop();
    AddonManager &addonManager();
    InputContextManager &inputContextManager();
    InputMethodManager &inputMethodManager();
    GlobalConfig &globalConfig();

    bool postEvent(Event &event);
    bool postEvent(Event &&event) { return postEvent(event); }

    HandlerTableEntry<EventHandler> *watchEvent(EventType type, EventWatcherPhase phase, EventHandler callback);
    void unwatchEvent(int id);

    void exit();
    void restart();
    void configure();
    void configureAddon(const std::string &addon);
    void configureInputMethod(const std::string &imName);
    std::string currentUI();
    std::string addonForInputMethod(const std::string &imName);
    void activate();
    void deactivate();
    void toggle();
    void resetInputMethodList();
    int state();
    void reloadConfig();
    void reloadAddonConfig(const std::string &addonName);
    std::string currentInputMethod();
    void setCurrentInputMethod(const std::string &imName);

private:
    void initialize();
    void handleSignal();
    void save();

    std::unique_ptr<InstancePrivate> d_ptr;
    FCITX_DECLARE_PRIVATE(Instance);
};
};

#endif // _FCITX_INSTANCE_H_
