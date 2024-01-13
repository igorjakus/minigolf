/**
 * OpenAL cross platform audio library
 * Copyright (C) 1999-2007 by authors.
 * This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the
 *  Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 * Or go to http://www.gnu.org/copyleft/lgpl.html
 */

#include "config.h"

#include "alconfig.h"

#ifdef _WIN32
#include <windows.h>
#include <shlobj.h>
#endif
#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <istream>
#include <limits>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "alfstream.h"
#include "alstring.h"
#include "core/helpers.h"
#include "core/logging.h"
#include "strutils.h"

#if defined(ALSOFT_UWP)
#include <winrt/Windows.Media.Core.h> // !!This is important!!
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
using namespace winrt;
#endif

namespace {

struct ConfigEntry {
    std::string key;
    std::string value;
};
std::vector<ConfigEntry> ConfOpts;


std::string &lstrip(std::string &line)
{
    size_t pos{0};
    while(pos < line.length() && std::isspace(line[pos]))
        ++pos;
    line.erase(0, pos);
    return line;
}

bool readline(std::istream &f, std::string &output)
{
    while(f.good() && f.peek() == '\n')
        f.ignore();

    return std::getline(f, output) && !output.empty();
}

std::string expdup(std::string_view str)
{
    std::string output;

    while(!str.empty())
    {
        if(auto nextpos = str.find('$'))
        {
            output += str.substr(0, nextpos);
            if(nextpos == std::string_view::npos)
                break;

            str.remove_prefix(nextpos);
        }

        str.remove_prefix(1);
        if(str.front() == '$')
        {
            output += '$';
            str.remove_prefix(1);
            continue;
        }

        const bool hasbraces{str.front() == '{'};
        if(hasbraces) str.remove_prefix(1);

        size_t envend{0};
        while(std::isalnum(str[envend]) || str[envend] == '_')
            ++envend;
        if(hasbraces && str[envend] != '}')
            continue;
        const std::string envname{str.substr(0, envend)};
        if(hasbraces) ++envend;
        str.remove_prefix(envend);

        if(auto envval = al::getenv(envname.c_str()))
            output += *envval;
    }

    return output;
}

void LoadConfigFromFile(std::istream &f)
{
    std::string curSection;
    std::string buffer;

    while(readline(f, buffer))
    {
        if(lstrip(buffer).empty())
            continue;

        if(buffer[0] == '[')
        {
            auto endpos = buffer.find(']', 1);
            if(endpos == 1 || endpos == std::string::npos)
            {
                ERR(" config parse error: bad line \"%s\"\n", buffer.c_str());
                continue;
            }
            if(buffer[endpos+1] != '\0')
            {
                size_t last{endpos+1};
                while(last < buffer.size() && std::isspace(buffer[last]))
                    ++last;

                if(last < buffer.size() && buffer[last] != '#')
                {
                    ERR(" config parse error: bad line \"%s\"\n", buffer.c_str());
                    continue;
                }
            }

            auto section = std::string_view{buffer}.substr(1, endpos-1);
            auto generalName = std::string_view{"general"};

            curSection.clear();
            if(section.size() != generalName.size()
                || al::strncasecmp(section.data(), generalName.data(), section.size()) != 0)
            {
                do {
                    auto nextp = section.find('%');
                    if(nextp == std::string_view::npos)
                    {
                        curSection += section;
                        break;
                    }

                    curSection += section.substr(0, nextp);
                    section.remove_prefix(nextp);

                    if(((section[1] >= '0' && section[1] <= '9') ||
                        (section[1] >= 'a' && section[1] <= 'f') ||
                        (section[1] >= 'A' && section[1] <= 'F')) &&
                       ((section[2] >= '0' && section[2] <= '9') ||
                        (section[2] >= 'a' && section[2] <= 'f') ||
                        (section[2] >= 'A' && section[2] <= 'F')))
                    {
                        int b{0};
                        if(section[1] >= '0' && section[1] <= '9')
                            b = (section[1]-'0') << 4;
                        else if(section[1] >= 'a' && section[1] <= 'f')
                            b = (section[1]-'a'+0xa) << 4;
                        else if(section[1] >= 'A' && section[1] <= 'F')
                            b = (section[1]-'A'+0x0a) << 4;
                        if(section[2] >= '0' && section[2] <= '9')
                            b |= (section[2]-'0');
                        else if(section[2] >= 'a' && section[2] <= 'f')
                            b |= (section[2]-'a'+0xa);
                        else if(section[2] >= 'A' && section[2] <= 'F')
                            b |= (section[2]-'A'+0x0a);
                        curSection += static_cast<char>(b);
                        section.remove_prefix(3);
                    }
                    else if(section[1] == '%')
                    {
                        curSection += '%';
                        section.remove_prefix(2);
                    }
                    else
                    {
                        curSection += '%';
                        section.remove_prefix(1);
                    }
                } while(!section.empty());
            }

            continue;
        }

        auto cmtpos = std::min(buffer.find('#'), buffer.size());
        while(cmtpos > 0 && std::isspace(buffer[cmtpos-1]))
            --cmtpos;
        if(!cmtpos) continue;
        buffer.erase(cmtpos);

        auto sep = buffer.find('=');
        if(sep == std::string::npos)
        {
            ERR(" config parse error: malformed option line: \"%s\"\n", buffer.c_str());
            continue;
        }
        auto keypart = std::string_view{buffer}.substr(0, sep++);
        while(!keypart.empty() && std::isspace(keypart.back()))
            keypart.remove_suffix(1);
        if(keypart.empty())
        {
            ERR(" config parse error: malformed option line: \"%s\"\n", buffer.c_str());
            continue;
        }
        auto valpart = std::string_view{buffer}.substr(sep);
        while(!valpart.empty() && std::isspace(valpart.front()))
            valpart.remove_prefix(1);

        std::string fullKey;
        if(!curSection.empty())
        {
            fullKey += curSection;
            fullKey += '/';
        }
        fullKey += keypart;

        if(valpart.size() > std::numeric_limits<int>::max())
        {
            ERR(" config parse error: value too long in line \"%s\"\n", buffer.c_str());
            continue;
        }
        if(valpart.size() > 1)
        {
            if((valpart.front() == '"' && valpart.back() == '"')
                || (valpart.front() == '\'' && valpart.back() == '\''))
            {
                valpart.remove_prefix(1);
                valpart.remove_suffix(1);
            }
        }

        TRACE(" setting '%s' = '%.*s'\n", fullKey.c_str(), static_cast<int>(valpart.size()),
            valpart.data());

        /* Check if we already have this option set */
        auto find_key = [&fullKey](const ConfigEntry &entry) -> bool
        { return entry.key == fullKey; };
        auto ent = std::find_if(ConfOpts.begin(), ConfOpts.end(), find_key);
        if(ent != ConfOpts.end())
        {
            if(!valpart.empty())
                ent->value = expdup(valpart);
            else
                ConfOpts.erase(ent);
        }
        else if(!valpart.empty())
            ConfOpts.emplace_back(ConfigEntry{std::move(fullKey), expdup(valpart)});
    }
    ConfOpts.shrink_to_fit();
}

const char *GetConfigValue(const std::string_view devName, const std::string_view blockName,
    const std::string_view keyName)
{
    if(keyName.empty())
        return nullptr;

    auto generalName = std::string_view{"general"};
    std::string key;
    if(!blockName.empty() && (blockName.size() != generalName.size() ||
        al::strncasecmp(blockName.data(), generalName.data(), blockName.size()) != 0))
    {
        key = blockName;
        if(!devName.empty())
        {
            key += '/';
            key += devName;
        }
        key += '/';
        key += keyName;
    }
    else
    {
        if(!devName.empty())
        {
            key = devName;
            key += '/';
        }
        key += keyName;
    }

    auto iter = std::find_if(ConfOpts.cbegin(), ConfOpts.cend(),
        [&key](const ConfigEntry &entry) -> bool
        { return entry.key == key; });
    if(iter != ConfOpts.cend())
    {
        TRACE("Found option %s = \"%s\"\n", key.c_str(), iter->value.c_str());
        if(!iter->value.empty())
            return iter->value.c_str();
        return nullptr;
    }

    if(devName.empty())
        return nullptr;
    return GetConfigValue({}, blockName, keyName);
}

} // namespace


#ifdef _WIN32
void ReadALConfig()
{
#if !defined(_GAMING_XBOX)
    {
#if !defined(ALSOFT_UWP)
        WCHAR buffer[MAX_PATH];
        if (!SHGetSpecialFolderPathW(nullptr, buffer, CSIDL_APPDATA, FALSE))
            return;
#else
        winrt::Windows::Storage::ApplicationDataContainer localSettings = winrt::Windows::Storage::ApplicationData::Current().LocalSettings();
        auto buffer = Windows::Storage::ApplicationData::Current().RoamingFolder().Path();
#endif
        std::string filepath{wstr_to_utf8(buffer)};
        filepath += "\\alsoft.ini";

        TRACE("Loading config %s...\n", filepath.c_str());
        al::ifstream f{filepath};
        if(f.is_open())
            LoadConfigFromFile(f);
    }
#endif


    std::string ppath{GetProcBinary().path};
    if(!ppath.empty())
    {
        ppath += "\\alsoft.ini";
        TRACE("Loading config %s...\n", ppath.c_str());
        al::ifstream f{ppath};
        if(f.is_open())
            LoadConfigFromFile(f);
    }

    if(auto confpath = al::getenv(L"ALSOFT_CONF"))
    {
        TRACE("Loading config %s...\n", wstr_to_utf8(confpath->c_str()).c_str());
        al::ifstream f{*confpath};
        if(f.is_open())
            LoadConfigFromFile(f);
    }
}

#else

void ReadALConfig()
{
    const char *str{"/etc/openal/alsoft.conf"};

    TRACE("Loading config %s...\n", str);
    al::ifstream f{str};
    if(f.is_open())
        LoadConfigFromFile(f);
    f.close();

    std::string confpaths{al::getenv("XDG_CONFIG_DIRS").value_or("/etc/xdg")};
    /* Go through the list in reverse, since "the order of base directories
     * denotes their importance; the first directory listed is the most
     * important". Ergo, we need to load the settings from the later dirs
     * first so that the settings in the earlier dirs override them.
     */
    std::string fname;
    while(!confpaths.empty())
    {
        auto next = confpaths.find_last_of(':');
        if(next < confpaths.length())
        {
            fname = confpaths.substr(next+1);
            confpaths.erase(next);
        }
        else
        {
            fname = confpaths;
            confpaths.clear();
        }

        if(fname.empty() || fname.front() != '/')
            WARN("Ignoring XDG config dir: %s\n", fname.c_str());
        else
        {
            if(fname.back() != '/') fname += "/alsoft.conf";
            else fname += "alsoft.conf";

            TRACE("Loading config %s...\n", fname.c_str());
            f = al::ifstream{fname};
            if(f.is_open())
                LoadConfigFromFile(f);
        }
        fname.clear();
    }

#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    if(mainBundle)
    {
        unsigned char fileName[PATH_MAX];
        CFURLRef configURL;

        if((configURL=CFBundleCopyResourceURL(mainBundle, CFSTR(".alsoftrc"), CFSTR(""), nullptr)) &&
           CFURLGetFileSystemRepresentation(configURL, true, fileName, sizeof(fileName)))
        {
            f = al::ifstream{reinterpret_cast<char*>(fileName)};
            if(f.is_open())
                LoadConfigFromFile(f);
        }
    }
#endif

    if(auto homedir = al::getenv("HOME"))
    {
        fname = *homedir;
        if(fname.back() != '/') fname += "/.alsoftrc";
        else fname += ".alsoftrc";

        TRACE("Loading config %s...\n", fname.c_str());
        f = al::ifstream{fname};
        if(f.is_open())
            LoadConfigFromFile(f);
    }

    if(auto configdir = al::getenv("XDG_CONFIG_HOME"))
    {
        fname = *configdir;
        if(fname.back() != '/') fname += "/alsoft.conf";
        else fname += "alsoft.conf";
    }
    else
    {
        fname.clear();
        if(auto homedir = al::getenv("HOME"))
        {
            fname = *homedir;
            if(fname.back() != '/') fname += "/.config/alsoft.conf";
            else fname += ".config/alsoft.conf";
        }
    }
    if(!fname.empty())
    {
        TRACE("Loading config %s...\n", fname.c_str());
        f = al::ifstream{fname};
        if(f.is_open())
            LoadConfigFromFile(f);
    }

    std::string ppath{GetProcBinary().path};
    if(!ppath.empty())
    {
        if(ppath.back() != '/') ppath += "/alsoft.conf";
        else ppath += "alsoft.conf";

        TRACE("Loading config %s...\n", ppath.c_str());
        f = al::ifstream{ppath};
        if(f.is_open())
            LoadConfigFromFile(f);
    }

    if(auto confname = al::getenv("ALSOFT_CONF"))
    {
        TRACE("Loading config %s...\n", confname->c_str());
        f = al::ifstream{*confname};
        if(f.is_open())
            LoadConfigFromFile(f);
    }
}
#endif

std::optional<std::string> ConfigValueStr(const std::string_view devName,
    const std::string_view blockName, const std::string_view keyName)
{
    if(const char *val{GetConfigValue(devName, blockName, keyName)})
        return val;
    return std::nullopt;
}

std::optional<int> ConfigValueInt(const std::string_view devName, const std::string_view blockName,
    const std::string_view keyName)
{
    if(const char *val{GetConfigValue(devName, blockName, keyName)})
        return static_cast<int>(std::strtol(val, nullptr, 0));
    return std::nullopt;
}

std::optional<unsigned int> ConfigValueUInt(const std::string_view devName,
    const std::string_view blockName, const std::string_view keyName)
{
    if(const char *val{GetConfigValue(devName, blockName, keyName)})
        return static_cast<unsigned int>(std::strtoul(val, nullptr, 0));
    return std::nullopt;
}

std::optional<float> ConfigValueFloat(const std::string_view devName,
    const std::string_view blockName, const std::string_view keyName)
{
    if(const char *val{GetConfigValue(devName, blockName, keyName)})
        return std::strtof(val, nullptr);
    return std::nullopt;
}

std::optional<bool> ConfigValueBool(const std::string_view devName,
    const std::string_view blockName, const std::string_view keyName)
{
    if(const char *val{GetConfigValue(devName, blockName, keyName)})
        return al::strcasecmp(val, "on") == 0 || al::strcasecmp(val, "yes") == 0
            || al::strcasecmp(val, "true")==0 || atoi(val) != 0;
    return std::nullopt;
}

bool GetConfigValueBool(const std::string_view devName, const std::string_view blockName,
    const std::string_view keyName, bool def)
{
    if(const char *val{GetConfigValue(devName, blockName, keyName)})
        return (al::strcasecmp(val, "on") == 0 || al::strcasecmp(val, "yes") == 0
            || al::strcasecmp(val, "true") == 0 || atoi(val) != 0);
    return def;
}
