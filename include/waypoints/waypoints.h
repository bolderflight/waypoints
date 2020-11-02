/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#ifndef INCLUDE_WAYPOINTS_WAYPOINTS_H_
#define INCLUDE_WAYPOINTS_WAYPOINTS_H_

#include <cstdint>
#include "Eigen/Core"
#include "Eigen/Dense"

/* Waypoint class */
class Waypoint {
 public:
  Waypoint() {}
  Waypoint(double lat_rad, double lon_rad, float alt_m) : lat_(lat_rad), lon_(lon_rad), alt_(alt_m) {}
  double lat_rad() {return lat_;}
  double lon_rad() {return lon_;}
  float alt_m() {return alt_;}
  void lat_rad(double val) {lat_ = val;}
  void lon_rad(double val) {lon_ = val;}
  void alt_m(float val) {alt_ = val;}

 private:
  double lat_ = 0, lon_ = 0;
  float alt_ = 0;
};

/* Waypoint storage and logic for retrieving the current, next, and previous waypoints */
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
  void closed_path(bool val) {closed_path_ = val;}
  bool closed_path() {return closed_path_;}
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
  bool At(std::size_t index, Waypoint *ptr) {
    if (!ptr) {return false;}
    if (size_) {
      if (index < size_) {
        *ptr = waypoints_[index];
        return true;
      }
    }
    return false;
  }
  std::size_t Size() {return size_;}
  std::size_t Capacity() {return capacity_;}
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

#endif  // INCLUDE_WAYPOINTS_WAYPOINTS_H_
