#pragma once

#if PROJ_VERSION_MAJOR < 4
#error "proj version >= 4 required"
#else
#define PROJ_COORD_FACTOR .017453292519943296
// Assume proj continues to ship with a backwards compatibility layer.
// See for a migration guide https://proj.org/development/migration.html.

#endif

#include <map>
#include <string>
#include <tuple>
#include <vector>

#include <proj.h>

class Proj {
public:
  explicit Proj(const std::string args);

  explicit Proj(const std::map<std::string, std::string>& args);

  ~Proj();

  std::tuple<double, double> fwd(double lon, double lat);

  std::tuple<double, double> inv(double x, double y);

protected:
  PJ* proj_;
};
