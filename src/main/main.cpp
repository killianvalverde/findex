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
 * @file        main.cpp
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
                .description("Search for files matching the specified pattern. \n\n"
                        "ff automatically detects the type of pattern you want to use. "
                        "The detection works as follows: if the pattern starts with * and "
                        "ends with ^, it is interpreted as a regular expression. If that is "
                        "not the case and the pattern contains a wildcard operator, it is "
                        "interpreted as a wildcard. Otherwise, it is treated as a simple "
                        "substring. You can enforce a specific interpretation using the "
                        "arguments described in the options section.")
                .epilogue("Examples:\n"
                        "  ff \"main\"           Search for files containing \"main\" in "
                        "current directory\n"
                        "  ff \"*.cpp\" src/     Search for .cpp files in 'src' directory\n"
                        "  ff \"^test[0-9]+$\"   Search using regex for files like test1, "
                        "test23, etc.");

        ap.add_positional_arg("PATTERN")
                .description("Pattern which filenames must match in order to be displayed")
                .store_into(prog_args.str);

        ap.add_positional_arg("DIRECTORY")
                .description("Directory in which perform the operation.")
                .store_into(prog_args.dir_pth)
                .mandatory(false);

        ap.add_key_arg("-s", "--sub-string")
                .description("Enforce the sub string filter.")
                .store_presence(prog_args.force_substr);

        ap.add_key_arg("-w", "--wildcard")
                .description("Enforce the wildcard filter (supports * and ?).")
                .store_presence(prog_args.force_wildcrd);

        ap.add_key_arg("-x", "--regex")
                .description("Enforce the regex filter.")
                .store_presence(prog_args.force_regx);

        ap.add_key_arg("-S", "--case-sensitive")
                .description("Enable case-sensitive search.")
                .store_presence(prog_args.case_sensitve);

        ap.add_key_arg("-r", "--relative-path")
                .description("Print relative path of matching files.")
                .store_presence(prog_args.print_relative_pth);

        ap.add_key_arg("-n", "--no-colors")
                .description("Disable color output.")
                .store_presence(prog_args.no_colrs);
                
        ap.add_help_arg("-h", "--help")
                .description("Display this help and exit.");
                
        ap.add_version_arg("-v", "--version")
                .description("Output version information and exit.")
                .gplv3_version_information("0.0.0", "2024-2026", "Killian Valverde");
        
        ap.add_constraint("-s", "-w", "-x")
                .mutually_exclusive(true);
        
        ap.parse_args(argc, argv);
        
        ff::program prog(prog_args);
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
