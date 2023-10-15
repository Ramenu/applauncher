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
#include <cstdlib>
#include <string>

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
    if (str == nullptr && err != nullptr) {
        g_error("failed to get %s %s from %s: %s", group_name, str, path, (*err)->message);
        exit(EXIT_FAILURE);
    }

    if (strcmp(str, "(null)") == 0)
        g_warning("got null string for %s %s from %s", group_name, key, path);

    return str;
}

static inline gchar **g_key_parse_array(const gchar *str) noexcept
{
    gchar **tokens = g_strsplit(str, ";", -1);
    return tokens;
}

application_info::application_info(const char *path) noexcept
{
    GError *error = nullptr;
    _handle = g_key_file_new();
    if (!g_key_file_load_from_file(_handle, path, G_KEY_FILE_NONE, &error)) {
        g_error("failed to load application file: %s", error->message);
        g_error_free(error);
        exit(EXIT_FAILURE);
    }
    _name = g_key_get_string(_handle, path, "Desktop Entry", "Name", nullptr);
    _exec = g_key_get_string(_handle, path, "Desktop Entry", "Exec", nullptr);
    _type = g_key_get_string(_handle, path, "Desktop Entry", "Type", nullptr);
    _icon = g_key_get_string(_handle, path, "Desktop Entry", "Icon", nullptr);
    _categories = g_key_parse_array(g_key_get_string(_handle, path, "Desktop Entry", "Categories", nullptr));
}

application_info::~application_info() noexcept
{
    if (_handle != nullptr) g_key_file_free(_handle);
    if (_name != nullptr) g_free(_name);
    if (_exec != nullptr) g_free(_exec);
    if (_icon != nullptr) g_free(_icon);
    if (_type != nullptr) g_free(_type);
    if (_categories != nullptr) g_strfreev(_categories);
}
