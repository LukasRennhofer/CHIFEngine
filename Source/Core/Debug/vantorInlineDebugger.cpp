/*
 *  ╔═══════════════════════════════════════════════════════════════╗
 *  ║                          ~ Vantor ~                           ║
 *  ║                                                               ║
 *  ║  This file is part of the Vantor Engine.                      ║
 *  ║  Automatically formatted by vantorFormat.py                   ║
 *  ║                                                               ║
 *  ╚═══════════════════════════════════════════════════════════════╝
 *
 *  Copyright (c) 2025 Lukas Rennhofer
 *  Licensed under the GNU General Public License, Version 3.
 *  See LICENSE file for more details.
 *
 *  Author: Lukas Rennhofer
 *  Date: 2025-05-12
 *
 *  File: vantorInlineDebugger.cpp
 *  Last Change: Automatically updated
 */

#include "vantorInlineDebugger.h"

// TODO: Adding Final version of debugger
namespace vantor::Debug
{

    void EnableDebugging(bool state) { DebuggingEnabled = state; }

    void EnableEngineDebugging(bool state) { EngineDebuggingEnabled = state; }

    void Breakpoint(std::string file, int line, bool inEngine = false)
    {
        if (inEngine && EngineDebuggingEnabled)
        {
            vantor::Backlog::Log(file, std::format("[Source::InEngine] Breakpoint hit at line {}", line), vantor::Backlog::LogLevel::DEBUG);
        }
        else
        {
            if (DebuggingEnabled)
            {
                vantor::Backlog::Log(file, std::format("Breakpoint hit at line {}", line), vantor::Backlog::LogLevel::DEBUG);
            }
        }
    }
} // namespace vantor::Debug
