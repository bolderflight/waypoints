# waypoints
Library to store and retrieve waypoint data.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

## Installation
CMake is used to build this library, which is exported as a library target called *waypoints*. The header is added as:

```
#include "waypoints/waypoints.h"
```

Note that you'll need CMake version 3.13 or above; it is recommended to build and install CMake from source, directions are located in the [CMake GitLab repository](https://github.com/Kitware/CMake).

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library and an example executable called *waypoints_example*. The example executable source file is located at *examples/waypoints_example.cc*. This code is built and tested on AMD64 and AARCH64 systems running Linux and on AMD64 systems running the Windows Subsystem for Linux (WSL).

## Waypoint
This class defines a single waypoint using Latitude, Longitude, Altitude (LLA) coordinates.

### Methods

**Waypoint()** Constructs an empty *Waypoint* object.

```C++
Waypoint point;
```

**Waypoint(double lat_rad, double lon_rad, float alt_m)** Constructs a *Waypoint* object, setting the latitude (rad), longitude (rad), and altitude (m).

```C++
Waypoint point(global::conversions::Deg_to_Rad(44.9739904036), global::conversions::Deg_to_Rad(-93.2277273172), 100.0);
```

**double lat_rad()** Returns the waypoint's latitude, rad.

```C++
std::cout << point.lat_rad() << std::endl;
```

**double lon_rad()** Returns the waypoint's longitude, rad.

```C++
std::cout << point.lon_rad() << std::endl;
```

**float alt_m()** Returns the waypoint's altitude, m.

```C++
std::cout << point.alt_m() << std::endl;
```

**void lat_rad(double val)** Sets the waypoint's latitude, rad.

```C++
point.lat_rad(global::conversions::Deg_to_Rad(44.9739904036));
```

**void lon_rad(double val)** Sets the waypoint's longitude, rad.

```C++
point.lon_rad(global::conversions::Deg_to_Rad(-93.2277273172));
```

**void alt_m(float val)** Sets the Waypoint's altitude, m.

```C++
point.alt_m(100.0);
```

## Waypoints
This class defines a container for waypoints. The container capacity is templated. Methods are provided for:
   * Adding waypoints into the container.
   * Retrieving the current, next, and previous waypoint.
   * Advancing the current waypoint.
   * Treating the set of waypoints as a closed path, with the aircraft moving from the last waypoint back to the first, or an open path.

### Methods

**Waypoints<std::size_t N>** Constructs a *Waypoints* object. The capacity of the container is provided as a template parameter.

```C++
Waypoints<10> active_waypoints;
```

**bool Add(const Waypoint &ref)** Adds a waypoint into the container. Returns true on success or false on failure. Failure would indicate that the contianer is full.

```C++
Waypoint point(global::conversions::Deg_to_Rad(44.9739904036), global::conversions::Deg_to_Rad(-93.2277273172), 100.0);
active_waypoints.Add(point);
```

**void closed_path(bool val)** Sets whether the set of waypoints should be considered a closed path (true) or open path (false). With a closed path, when the aircraft reaches the end of the defined waypoints, it will proceed to the first waypoint.

```C++
active_waypoints.closed_path(true);
```

**bool closed_path()** Returns whether the set of waypoints is considered a closed path (true) or open path (false).

```C++
std::cout << active_waypoints.closed_path() << std::endl;
```

**bool Advance()** Advances the current waypoint to the next waypoint in the set. Returns true on success or false on failure. Failure would indicate that the aircraft has reached the end of an open path of waypoints.

```C++
active_waypoints.Advance();
```

**bool Current(Waypoint &ast;ptr)** Sets the *Waypoint* object pointed to by *ptr* to the value of the current waypoint. Returns true on success or false on failure. Failure would indicate that no waypoints have been defined.

```C++
/* Retrieve the current waypoint */
Waypoint point;
bool status = active_waypoints.Current(&point);
```

**bool Next(Waypoint &ast;ptr)** Sets the *Waypoint* object pointed to by *ptr* to the value of the next waypoint. Returns true on success or false on failure. Failure would indicate that no waypoints have been defined or the aircraft is at the end of an open path.

```C++
/* Retrieve the next waypoint */
Waypoint point;
bool status = active_waypoints.Next(&point);
```

**bool Prev(Waypoint &ast;ptr)** Sets the *Waypoint* object pointed to by *ptr* to the value of the previous waypoint. Returns true on success or false on failure. Failure would indicate that no waypoints have been defined or the aircraft is at the beginning of an open path.

```C++
/* Retrieve the previous waypoint */
Waypoint point;
bool status = active_waypoints.Prev(&point);
```

**bool At(std::size_t index, Waypoint &ast;ptr)** Sets the *Waypoint* object pointed to by *ptr* to the value of the waypoint at the given index. Returns true on success or false on failure. Failure would indicate that the index is out of bounds.

```C++
/* Retrieve the waypoint at index 1 */
Waypoint point;
bool status = active_waypoints.At(1, &point);
```

**std::size_t Size()** Returns the current number of waypoints stored in the container.

```C++
std::cout << active_waypoints.Size() << std::endl;
```

**std::size_t Capacity()** Returns the capacity of the container.

```C++
std::cout << active_waypoints.Capacity() << std::endl;
```

**void Clear()** Clears the container and sets the path to an open path, which is the default option.

```C++
active_waypoints.Clear();
```
