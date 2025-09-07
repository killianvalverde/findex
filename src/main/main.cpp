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
 * @file        main.hpp
 * @brief       main entry point.
 * @author      Killian Valverde
 * @date        2024/11/07
 */

#define SPEED_CROSSPLATFORM_UNICODE_MAIN
#include <speed/speed.hpp>

#include "../ff/ff.hpp"

int main(int argc, char* argv[])
{
    try
    {
        ff::program_args prog_args;
        spd::ap::arg_parser ap("ff");
        
        ap.add_help_menu()
                .description("Search for files that match specified criteria.");

        ap.add_positional_arg("SUB-STRING")
                .description("Sub-string to search in the file names.")
                .store_into(prog_args.str);

        ap.add_positional_arg("DIR")
                .description("Directory in which perform the operation.")
                .store_into(prog_args.dir_pth)
                .mandatory(false);

        ap.add_key_arg("-s", "--sub-string")
                .description("Enforce the sub string filter.")
                .store_presence(prog_args.force_substr);

        ap.add_key_arg("-w", "--wildcard")
                .description("Enforce the wildcard filter. Only * and ? characters are supported.")
                .store_presence(prog_args.force_wildcrd);

        ap.add_key_arg("-x", "--regex")
                .description("Enforce the regex filter.")
                .store_presence(prog_args.force_regx);

        ap.add_key_arg("-S", "--case-sensitive")
                .description("Enable case-sensitive search.")
                .store_presence(prog_args.case_sensitve);

        ap.add_key_arg("-a", "--absolute-path")
                .description("Print the absolute path of the matching files.")
                .store_presence(prog_args.print_absolute_pth);

        ap.add_key_arg("-n", "--no-colors")
                .description("Disable color output in print statements.")
                .store_presence(prog_args.no_colrs);
                
        ap.add_help_arg("-h", "--help")
                .description("Display this help and exit.");
                
        ap.add_version_arg("-v", "--version")
                .description("Output version information and exit.")
                .gplv3_version_information("0.0.0", "2024-2025", "Killian Valverde");
        
        ap.add_constraint("-s", "-w", "-x")
                .mutually_exclusive(true);
        
        ap.parse_args(argc, argv);
        
        ff::program prog(std::move(prog_args));
        return prog.execute();
    }
    catch (const std::exception& e)
    {
        spd::ios::print_error_and_exit(std::cerr, "ff", e.what(), 1);
    }
    catch (...)
    {
        spd::ios::print_error_and_exit(std::cerr, "ff", "Unknown error", 1);
    }
}
