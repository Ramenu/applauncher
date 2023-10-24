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

#ifndef APPLAUNCHER_APPLICATION_H
#define APPLAUNCHER_APPLICATION_H

#include <gio/gio.h>
#include <gtk/gtk.h>
#include <vector>

class application_info
{
    private:
        GKeyFile *_handle {nullptr};
        gchar *_name {nullptr};
        gchar *_exec {nullptr};
        gchar *_type {nullptr};
        gchar *_comment {nullptr};
        gchar *_icon {nullptr};
        gchar **_categories {nullptr};
    public:
        explicit application_info(const char *path) noexcept;
        ~application_info() noexcept;
        application_info(const application_info&) = delete;
        application_info& operator=(const application_info&) = delete;
        application_info(application_info &&other) noexcept {
            _handle = other._handle;
            _name = other._name;
            _exec = other._exec;
            _icon = other._icon;
            _type = other._type;
            _categories = other._categories;
            _comment = other._comment;
            other._handle = nullptr;
            other._name = nullptr;
            other._exec = nullptr;
            other._icon = nullptr;
            other._type = nullptr;
            other._categories = nullptr;
            other._comment = nullptr;
        }
        application_info& operator=(application_info &&other) noexcept {
            _handle = other._handle;
            _name = other._name;
            _exec = other._exec;
            _icon = other._icon;
            _type = other._type;
            _comment = other._comment;
            _categories = other._categories;
            other._handle = nullptr;
            other._name = nullptr;
            other._exec = nullptr;
            other._icon = nullptr;
            other._type = nullptr;
            other._categories = nullptr;
            other._comment = nullptr;
            return *this;
        }
        const auto *name() const noexcept { return _name; }
        auto *exec() const noexcept { return _exec; }
        const auto *type() const noexcept { return _type; }
        const auto *icon() const noexcept { return _icon; }
        const auto *comment() const noexcept { return _comment; }
};

std::vector<application_info> get_global_applications() noexcept;

#endif // APPLAUNCHER_APPLICATION_H
