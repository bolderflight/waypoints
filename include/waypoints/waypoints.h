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

#ifndef INCLUDE_WAYPOINTS_WAYPOINTS_H_
#define INCLUDE_WAYPOINTS_WAYPOINTS_H_

#include <cstdint>
#include <array>

namespace bfs {

/* Waypoint class */
class Waypoint {
 public:
  Waypoint() {}
  Waypoint(const double lat_rad, const double lon_rad, const float alt_m) :
    lat_(lat_rad), lon_(lon_rad), alt_(alt_m) {}
  double lat_rad() const {return lat_;}
  double lon_rad() const {return lon_;}
  float alt_m() const {return alt_;}
  void lat_rad(const double val) {lat_ = val;}
  void lon_rad(const double val) {lon_ = val;}
  void alt_m(const float val) {alt_ = val;}

 private:
  double lat_ = 0, lon_ = 0;
  float alt_ = 0;
};

/*
* Waypoint storage and logic for retrieving the current, next, and
* previous waypoints
*/
template<std::size_t N>
class Waypoints {
 public:
  bool Add(const Waypoint &ref) {
    if (size_ < capacity_) {
      waypoints_[size_++] = ref;
      return true;
    }
    return false;
  }
  void closed_path(const bool val) {closed_path_ = val;}
  bool closed_path() const {return closed_path_;}
  bool Advance() {
    if (size_) {
      if (current_index_ < size_ - 1) {
        current_index_++;
        return true;
      }
      if (closed_path_) {
        current_index_ = 0;
        return true;
      }
    }
    return false;
  }
  bool Current(Waypoint *ptr) {
    if (!ptr) {return false;}
    if (size_) {
      *ptr = waypoints_[current_index_];
      return true;
    }
    return false;
  }
  bool Next(Waypoint *ptr) {
    if (!ptr) {return false;}
    if (size_) {
      if (current_index_ < size_ - 1) {
        *ptr = waypoints_[current_index_ + 1];
        return true;
      }
      if (closed_path_) {
        *ptr = waypoints_[0];
        return true;
      }
    }
    return false;
  }
  bool Previous(Waypoint *ptr) {
    if (!ptr) {return false;}
    if (size_) {
      if (current_index_ > 0) {
        *ptr = waypoints_[current_index_ - 1];
        return true;
      }
      if (closed_path_) {
        *ptr = waypoints_[size_ - 1];
        return true;
      }
    }
    return false;
  }
  bool At(const std::size_t index, Waypoint *ptr) {
    if (!ptr) {return false;}
    if (size_) {
      if (index < size_) {
        *ptr = waypoints_[index];
        return true;
      }
    }
    return false;
  }
  std::size_t Size() const {return size_;}
  std::size_t Capacity() const {return capacity_;}
  void Clear() {
    closed_path_ = false;
    current_index_ = 0;
    size_ = 0;
  }

 private:
  /* Whether the last waypoint loops around to the first */
  bool closed_path_ = false;
  /* Current waypoint */
  std::size_t current_index_ = 0;
  /* Size and capacity */
  std::size_t capacity_ = N;
  std::size_t size_ = 0;
  /* Underlying storage */
  std::array<Waypoint, N> waypoints_;
};

}  // namespace bfs

#endif  // INCLUDE_WAYPOINTS_WAYPOINTS_H_
