/* ff
 * Copyright (C) 2024-2026 Killian Valverde.
 *
 * This file is part of ff.
 *
 * ff is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ff is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ff. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file        program.cpp
 * @brief       program class implementation.
 * @author      Killian Valverde
 * @date        2024/11/07
 */

#include "program.hpp"

namespace ff {

program::program(program_args& prog_args)
        : prog_args_(prog_args)
{
}

int program::execute()
{
    auto directory_iter = spd::fsys::directory_iteration(prog_args_.dir_pth)
            .case_insensitive(!prog_args_.case_sens)
            .absolute(!prog_args_.print_relative_pth);
    
    if (prog_args_.force_substr)
    {
        directory_iter.substring_to_match(prog_args_.str);
    }
    else if (prog_args_.force_wildcrd)
    {
        directory_iter.wildcard_to_match(prog_args_.str);
        colorize_file_nme_ = true;
    }
    else if (prog_args_.force_regx || is_regex(prog_args_.str))
    {
        directory_iter.regex_to_match(prog_args_.str);
        colorize_file_nme_ = true;
    }
    else if (is_wildcard(prog_args_.str))
    {
        directory_iter.wildcard_to_match(prog_args_.str);
        colorize_file_nme_ = true;
    }
    else
    {
        directory_iter.substring_to_match(prog_args_.str);
    }

    if (!prog_args_.case_sens && !prog_args_.no_colrs && !colorize_file_nme_)
    {
        spd::str::to_lower_inplace(prog_args_.str);
    }
    
    for (auto& directory_ent : directory_iter)
    {
        print_path(directory_ent);
    }
    
    std::flush(std::cout);
    return 0;
}

bool program::is_wildcard(const std::string& str) const noexcept
{
    return std::ranges::any_of(str, [](char c)
    {
        return c == '*' || c == '?';
    });
}

bool program::is_regex(const std::string& str) const noexcept
{
    if (str.length() <= 1)
    {
        return false;
    }
    
    return str.front() == '^' && str.back() == '$';
}

void program::print_path(
        const spd::fsys::directory_iteration::directory_entity& directory_ent
) const
{
    if (prog_args_.no_colrs)
    {
        std::cout << directory_ent.get_utf8_path() << std::endl;
    }
    else if (colorize_file_nme_)
    {
        print_path_with_highlighted_file_name(directory_ent);
    }
    else
    {
        print_path_with_highlighted_substring(directory_ent);
    }
}

void program::print_path_with_highlighted_file_name(
        const spd::fsys::directory_iteration::directory_entity& directory_ent
) const
{
    std::cout << spd::ios::set_cyan_text
            << directory_ent.get_utf8_parent_path()
            << SPEED_PATH_SEPARATOR_CHAR;

    if (directory_ent.is_directory())
    {
        std::cout << spd::ios::set_brown_text;
    }
    else
    {
        std::cout << spd::ios::set_default_text;
    }

    std::cout << directory_ent.get_utf8_filename()
            << spd::ios::set_default_text
            << spd::ios::newl;
}

void program::print_path_with_highlighted_substring(
        const spd::fsys::directory_iteration::directory_entity& directory_ent
) const
{
    std::string raw_filenme = directory_ent.get_utf8_filename();
    std::string filename;
    std::string_view raw_filenme_view;
    size_t match_pos;
    size_t cur_pos = 0;
    bool is_directory = directory_ent.is_directory();

    auto use_filename_color = [&is_directory]()
    {
        if (is_directory)
        {
            std::cout << spd::ios::set_brown_text;
        }
        else
        {
            std::cout << spd::ios::set_default_text;
        }
    };

    if (!prog_args_.case_sens)
    {
        filename = spd::str::to_lower(raw_filenme);
        raw_filenme_view = raw_filenme;
    }
    else
    {
        filename = std::move(raw_filenme);
        raw_filenme_view = filename;
    }

    std::cout << spd::ios::set_cyan_text
            << directory_ent.get_utf8_parent_path()
            << SPEED_PATH_SEPARATOR_CHAR;

    while ((match_pos = filename.find(prog_args_.str, cur_pos)) != std::string::npos)
    {
        use_filename_color();
        std::cout << raw_filenme_view.substr(cur_pos, match_pos - cur_pos)
                << spd::ios::set_light_red_text
                << raw_filenme_view.substr(match_pos, prog_args_.str.length());

        cur_pos = match_pos + prog_args_.str.length();
    }

    use_filename_color();
    std::cout << raw_filenme_view.substr(cur_pos)
            << spd::ios::set_default_text
            << std::endl;
}

}
