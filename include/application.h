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

class application_info
{
    private:
        GKeyFile *_handle {nullptr};
        gchar *_name {nullptr};
        gchar *_exec {nullptr};
        gchar *_icon {nullptr};
        gchar *_type {nullptr};
        gchar **_categories {nullptr};
    public:
        explicit application_info(const char *path) noexcept;
        ~application_info() noexcept;
        application_info(const application_info&) = delete;
        application_info& operator=(const application_info&) = delete;
        application_info(application_info&&) = delete;
        application_info& operator=(application_info&&) = delete;
        const gchar *name() const noexcept { return _name; }
        const gchar *exec() const noexcept { return _exec; }
        const gchar *icon() const noexcept { return _icon; }
        const gchar *type() const noexcept { return _type; }
};
#endif // APPLAUNCHER_APPLICATION_H
