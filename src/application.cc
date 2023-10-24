/**
 * Copyright (C) Ramenu
 * 
 * This file is part of applauncher.
 * 
 * applauncher is free software: you can redistribute it and/or modify it under the terms of the 
 * GNU General Public License as published by the Free Software Foundation, either version 
 * 3 of the License, or (at your option) any later version.
 * 
 * applauncher is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with applauncher. If 
 * not, see <https://www.gnu.org/licenses/>.
 */

#include "application.h"
#include "global.h"
#include <cstdlib>
#include <string>
#include <filesystem>

namespace std_fs = std::filesystem;

static gchar *g_key_get_string(GKeyFile *handle, 
                               const char *path,
                               const gchar *group_name, 
                               const gchar *key, 
                               GError **err) noexcept
{
    if (handle == nullptr) {
        g_error("BUG: GKeyFile handle is null");
        exit(EXIT_FAILURE);
    }

    gchar *str = g_key_file_get_string(handle, group_name, key, err);
    if constexpr (DEBUG)
        if (str == nullptr)
            g_warning("failed to get %s %s from %s", group_name, key, path);

    return str;
}

static inline bool is_valid_application(const application_info &app) noexcept
{
    return app.name() != nullptr && app.icon() != nullptr && 
           app.exec() != nullptr && app.comment() != nullptr;
}

static inline gchar **g_key_parse_array(const gchar *str) noexcept
{
    if (str == nullptr || strcmp(str, "(null)") == 0)
        return nullptr;
    gchar **tokens = g_strsplit(str, ";", -1);
    return tokens;
}

application_info::application_info(const char *path) noexcept
{
    GError *error = nullptr;
    _handle = g_key_file_new();

    if (!g_key_file_load_from_file(_handle, path, G_KEY_FILE_NONE, &error)) {
        if constexpr (DEBUG)
            g_warning("failed to load application file %s: %s", path, error->message);
        g_error_free(error);
        return;
    }

    _name = g_key_get_string(_handle, path, "Desktop Entry", "Name", nullptr);
    _exec = g_key_get_string(_handle, path, "Desktop Entry", "Exec", nullptr);
    _type = g_key_get_string(_handle, path, "Desktop Entry", "Type", nullptr);
    _comment = g_key_get_string(_handle, path, "Desktop Entry", "Comment", nullptr);
    _icon = g_key_get_string(_handle, path, "Desktop Entry", "Icon", nullptr);
    _categories = g_key_parse_array(g_key_get_string(_handle, path, "Desktop Entry", "Categories", nullptr));
}

application_info::~application_info() noexcept
{
    if (_handle != nullptr) g_key_file_free(_handle);
    if (_name != nullptr) g_free(_name);
    if (_exec != nullptr) g_free(_exec);
    if (_type != nullptr) g_free(_type);
    if (_comment != nullptr) g_free(_comment);
    if (_icon != nullptr) g_free(_icon);
    if (_categories != nullptr) g_strfreev(_categories);
}

std::vector<application_info> get_global_applications() noexcept
{
    std::vector<application_info> apps;

    for (auto const &entry : std_fs::directory_iterator("/usr/share/applications")) {
        if (entry.path().extension() == ".desktop") {
            application_info app {entry.path().c_str()};
            if (is_valid_application(app))
                apps.emplace_back(std::move(app));
        }
    }

    return apps;
}