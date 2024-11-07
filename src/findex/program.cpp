/* findex
 * Copyright (C) 2024 Killian Valverde.
 *
 * This file is part of findex.
 *
 * findex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * findex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with findex. If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file        findex/program.cpp
 * @brief       program class implementation.
 * @author      Killian Valverde
 * @date        2024/11/07
 */

#include "program.hpp"


namespace findex {


program::program(program_args&& prog_args)
        : prog_args_(std::move(prog_args))
{
}


int program::execute()
{
    spd::fsys::directory_iteration target_directory_iteratn(prog_args_.target_directory_pth);
    
    target_directory_iteratn.case_sensitive(prog_args_.case_sensitve);
    
    if (!prog_args_.sub_str.empty())
    {
        target_directory_iteratn.substring_to_match(prog_args_.sub_str);
    }
    else if (!prog_args_.wildcrd.empty())
    {
        target_directory_iteratn.regex_to_match(prog_args_.wildcrd);
    }
    else if (!prog_args_.regx.empty())
    {
        target_directory_iteratn.regex_to_match(prog_args_.regx);
    }
    
    for (auto directory_it = target_directory_iteratn.begin();
         !directory_it.end();
         ++directory_it)
    {
        if (!prog_args_.print_absolute_pth)
        {
            print_path(*directory_it);
        }
        else
        {
            print_path(std::filesystem::absolute(*directory_it));
        }
    }
    
    std::flush(std::cout);
    
    return 0;
}


void program::print_path(const std::filesystem::path& pth) const
{
    if (prog_args_.no_colrs)
    {
        std::cout << spd::cast::type_cast<std::string>(pth.c_str()) << std::endl;
        return;
    }
    else if (!prog_args_.sub_str.empty())
    {
        print_path_with_highlighted_substring_match(pth);
    }
    else if (!prog_args_.wildcrd.empty())
    {
        print_path_with_highlighted_wildcard_match(pth);
    }
    else if (!prog_args_.regx.empty())
    {
        print_path_with_highlighted_regex_match(pth);
    }
}


void program::print_path_with_highlighted_substring_match(const std::filesystem::path &pth) const
{
    auto raw_filenme = spd::cast::type_cast<std::string>(pth.filename().native());
    std::string filenme;
    std::string sub_str;
    size_t match_strt;
    size_t pos = 0;
    
    if (!prog_args_.case_sensitve)
    {
        filenme = spd::str::tolower(raw_filenme);
        sub_str = spd::str::tolower(prog_args_.sub_str);
    }
    else
    {
        filenme = raw_filenme;
        sub_str = prog_args_.sub_str;
    }
    
    std::cout << spd::cast::type_cast<std::string>(pth.parent_path().c_str())
              << SPEED_SYSTEM_FILESYSTEM_SLASH_CHAR;
    
    while ((match_strt = filenme.find(sub_str, pos)) != std::string::npos)
    {
        std::cout << raw_filenme.substr(pos, match_strt - pos)
                  << spd::ios::set_light_red_text
                  << raw_filenme.substr(match_strt, sub_str.length())
                  << spd::ios::set_default_text;
        
        pos = match_strt + sub_str.length();
    }
    
    std::cout << raw_filenme.substr(pos) << std::endl;
}


void program::print_path_with_highlighted_wildcard_match(const std::filesystem::path &pth) const
{
    std::cout << spd::cast::type_cast<std::string>(pth.parent_path().c_str())
              << SPEED_SYSTEM_FILESYSTEM_SLASH_CHAR
              << spd::ios::set_light_red_text
              << spd::cast::type_cast<std::string>(pth.filename().c_str())
              << spd::ios::set_default_text;
}


void program::print_path_with_highlighted_regex_match(const std::filesystem::path &pth) const
{
    print_path_with_highlighted_wildcard_match(pth);
}


}
