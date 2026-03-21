/* ff
 * Copyright (C) 2024-2025 Killian Valverde.
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

#include <speed/speed.hpp>

namespace ff {

program::program(program_args& prog_args)
        : prog_args_(prog_args)
{
}

int program::execute()
{
    auto directory_iteratn = spd::fsys::directory_iteration(prog_args_.dir_pth)
            .case_insensitive(!prog_args_.case_sensitve)
            .absolute(!prog_args_.print_relative_pth);
    
    if (prog_args_.force_substr)
    {
        directory_iteratn.substring_to_match(prog_args_.str);
    }
    else if (prog_args_.force_wildcrd)
    {
        directory_iteratn.wildcard_to_match(prog_args_.str);
        colorize_file_nme_ = true;
    }
    else if (prog_args_.force_regx || is_regex(prog_args_.str))
    {
        directory_iteratn.regex_to_match(prog_args_.str);
        colorize_file_nme_ = true;
    }
    else if (is_wildcard(prog_args_.str))
    {
        directory_iteratn.wildcard_to_match(prog_args_.str);
        colorize_file_nme_ = true;
    }
    else
    {
        directory_iteratn.substring_to_match(prog_args_.str);
    }

    if (!prog_args_.case_sensitve && !prog_args_.no_colrs && !colorize_file_nme_)
    {
        spd::str::to_lower_inplace(prog_args_.str);
    }
    
    for (auto& pth : directory_iteratn)
    {
        print_path(pth);
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

void program::print_path(const std::filesystem::path& pth) const
{
    if (prog_args_.no_colrs)
    {
        std::cout << spd::cast::to_utf8(pth) << std::endl;
    }
    else if (colorize_file_nme_)
    {
        print_path_with_highlighted_file_name(pth);
    }
    else
    {
        print_path_with_highlighted_substring(pth);
    }
}

void program::print_path_with_highlighted_file_name(const std::filesystem::path& pth) const
{
    std::cout << spd::cast::to_utf8(pth.parent_path())
            << SPEED_PATH_SEPARATOR_CHAR
            << spd::ios::set_light_red_text
            << spd::cast::to_utf8(pth.filename())
            << spd::ios::set_default_text
            << spd::ios::newl;
}

void program::print_path_with_highlighted_substring(const std::filesystem::path& pth) const
{
    std::string raw_filenme = spd::cast::to_utf8(pth.filename());
    std::string filename;
    std::string_view raw_filenme_view;
    size_t match_pos;
    size_t cur_pos = 0;

    if (!prog_args_.case_sensitve)
    {
        filename = spd::str::to_lower(raw_filenme);
        raw_filenme_view = raw_filenme;
    }
    else
    {
        filename = std::move(raw_filenme);
        raw_filenme_view = filename;
    }

    std::cout << spd::cast::to_utf8(pth.parent_path()) << SPEED_PATH_SEPARATOR_CHAR;

    while ((match_pos = filename.find(prog_args_.str, cur_pos)) != std::string::npos)
    {
        std::cout << raw_filenme_view.substr(cur_pos, match_pos - cur_pos)
                  << spd::ios::set_light_red_text
                  << raw_filenme_view.substr(match_pos, prog_args_.str.length())
                  << spd::ios::set_default_text;

        cur_pos = match_pos + prog_args_.str.length();
    }

    std::cout << raw_filenme_view.substr(cur_pos) << std::endl;
}

}
