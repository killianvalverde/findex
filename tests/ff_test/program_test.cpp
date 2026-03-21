/* ff
 * Copyright (C) 2025 Killian Valverde.
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
 * @file        program_test.cpp
 * @brief       program unit test.
 * @author      Killian Valverde
 * @date        2025/08/02
 */

#include <gtest/gtest.h>

#include "ff/ff.hpp"

TEST(ff_program, execute)
{
    int ret = -1;
    ff::program_args prog_args;
    ff::program prog(prog_args);
    
    EXPECT_NO_THROW(ret = prog.execute());
    EXPECT_TRUE(ret == 0);
}
