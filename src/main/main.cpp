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
 * @file        main/main.hpp
 * @brief       main entry point.
 * @author      Killian Valverde
 * @date        2024/11/07
 */

#include <speed/speed.hpp>

#include "../findex/program.hpp"


int main(int argc, char* argv[])
{
    std::string messge;
    int retv;
    
    try 
    {
        findex::program_args prog_args;
        spd::ap::arg_parser ap("findex");
        
        ap.add_help_menu()
                .description("Search for files that match specified criteria.");
                
        ap.add_help_arg("--help", "-h")
                .description("Display this help and exit.");
                
        ap.add_version_arg("--version", "-v")
                .description("Output version information and exit.")
                .gplv3_version_information("0.0.0", "2024", "Killian Valverde");

        ap.parse_args(argc, argv);
        
        findex::program prog(std::move(prog_args));
                
        return prog.execute();
    }
    catch (const findex::exception_base& e)
    {
        messge = e.what();
        retv = 1;
    }
    catch (const std::exception& e)
    {
        messge = e.what();
        retv = -1;
    }
    catch (...)
    {
        messge = "Unknown error";
        retv = -1;
    }
    
    std::cerr << spd::ios::newl
              << spd::ios::set_light_red_text << "findex: "
              << spd::ios::set_default_text << messge
              << std::endl;

    return retv;
}
