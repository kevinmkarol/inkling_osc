/*
 * Copyright (C) 2013  Roel Janssen <roel@moefel.org>
 *
 * This file originally part of InklingReader
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * @file   datatypes/tilt.h
 * @brief  A datatype to store tilt data.
 * @author Roel Janssen
 * @namespace datatypes
 */

#ifndef DATATYPES_TILT_H
#define DATATYPES_TILT_H

/**
 * This struct contains the variables that can be extracted for tilt data.
 */
typedef struct
{
  unsigned char type;
  unsigned char x;
  unsigned char y;
} dt_tilt;

#endif//DATATYPES_TILT_H
