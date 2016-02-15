/*
 * Copyright (C) 2016  Kevin M. Karol <kevinmkarol@gmail.com>
 *
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

#ifndef DATATYPES_INKLINGOSC_H
#define DATATYPES_INKLINGOSC_H

#include "../datatypes/coordinate.h"
#include "../datatypes/tilt.h"

/**
 * This struct contains the common element in all datatypes defined here: a 
 * specifier for which type of element the struct is. In a list, these structs 
 * are all pointers to void. To know which type a struct is, the 'type' field 
 * is used.
 */
typedef struct
{
  dt_tilt tilt;
  dt_coordinate coordinate;
} dt_inkling_osc;

#endif//DATATYPES_INKLINGOSC_H
