/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include "waypoints/waypoints.h"
#include <iostream>

int main() {
  /* Define a waypoint */
  Waypoint point;
  /* Container to hold up to 10 waypoints */
  Waypoints<10> active_waypoints;
  /* Fill three dummy waypoints */
  for (int i = 0; i < 3; i++) {
    Waypoint point(i, i, i);
    active_waypoints.Add(point);
  }
  /* Set to a closed path */
  active_waypoints.closed_path(true);
  /* 
  * Retrieve the previous, current, and next waypoints, 
  * advancing the current waypoint each step 
  */
  for (int i = 0; i < 3; i++) {
    Waypoint prev, current, next;
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
