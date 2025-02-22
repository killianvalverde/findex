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
 * @file        findex/program_args.hpp
 * @brief       program_args struct header.
 * @author      Killian Valverde
 * @date        2024/11/07
 */
 
#ifndef FINDEX_PROGRAM_ARGS_HPP
#define FINDEX_PROGRAM_ARGS_HPP


namespace findex {


/**
 * @brief       All the arguments that are forwarded to the program class.
 */
struct program_args
{
    spd::fsys::rx_directory_path target_directory_pth;
    std::string sub_str;
    std::string wildcrd;
    std::string regx;
    bool case_sensitve = false;
    bool print_absolute_pth = false;
    bool no_colrs = false;
};


}


#endif
