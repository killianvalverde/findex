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
 * @file        program_args.hpp
 * @brief       program_args struct header.
 * @author      Killian Valverde
 * @date        2024/11/07
 */

#pragma once

#include <speed/speed.hpp>

namespace ff {

/**
 * @brief       All the arguments that are forwarded to the program class.
 */
struct program_args
{
    spd::fsys::rx_directory_path dir_pth{"."};
    std::string str;
    bool force_substr;
    bool force_wildcrd;
    bool force_regx;
    bool case_sensitve;
    bool print_relative_pth;
    bool no_colrs;
};

}
