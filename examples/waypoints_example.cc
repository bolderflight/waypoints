/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#include "waypoints/waypoints.h"
#include <iostream>

int main() {
  /* Define a waypoint */
  bfs::Waypoint point;
  /* Container to hold up to 10 waypoints */
  bfs::Waypoints<10> active_waypoints;
  /* Fill three dummy waypoints */
  for (int i = 0; i < 3; i++) {
    bfs::Waypoint point(i, i, i);
    active_waypoints.Add(point);
  }
  /* Set to a closed path */
  active_waypoints.closed_path(true);
  /* 
  * Retrieve the previous, current, and next waypoints, 
  * advancing the current waypoint each step 
  */
  for (int i = 0; i < 3; i++) {
    bfs::Waypoint prev, current, next;
    std::cout << active_waypoints.Previous(&prev) << "\t";
    std::cout << active_waypoints.Current(&current) << "\t";
    std::cout << active_waypoints.Next(&next) << "\t";
    std::cout << prev.lat_rad() << "\t";
    std::cout << current.lat_rad() << "\t";
    std::cout << next.lat_rad() << "\t";
    std::cout << active_waypoints.Advance() << "\n";
  }

  return 0;
}
