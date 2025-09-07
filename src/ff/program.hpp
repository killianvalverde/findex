/* ff
 * Copyright (C) 2024 Killian Valverde.
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
 * @file        program.hpp
 * @brief       program class header.
 * @author      Killian Valverde
 * @date        2024/11/07
 */

#pragma once

#include "program_args.hpp"

/**
 * @brief       Contians all ff resources.
 */
namespace ff {

class program
{
public:
    /**
     * @brief       Constructor with parameters.
     * @param       prog_args : The program arguments.
     */
    explicit program(program_args&& prog_args);
    
    /**
     * @brief       Execute the program.
     * @return      The value that represents if the program succeed.
     */
    int execute();

private:
    bool is_wildcard(const std::string& str) const noexcept;
    
    bool is_regex(const std::string& str) const noexcept;
    
    void print_path(const std::filesystem::path& actual_pth) const;
    
    void print_path_with_highlighted_substring(const std::filesystem::path& pth) const;
    
    void print_path_with_highlighted_file_name(const std::filesystem::path& pth) const;
    
    void print_path_with_highlighted_regex_match(const std::filesystem::path& pth) const;

private:
    /** The program arguments. */
    program_args prog_args_;
    
    bool colorize_file_nme_ = false;
};

}
