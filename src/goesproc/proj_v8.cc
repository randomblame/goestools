#include "proj.h"

#include <cstring>
#include <sstream>

namespace {

std::string toProjStr(
  const std::map<std::string, std::string>& args) {
  std::stringstream ss;
  for (const auto& arg : args) {
    ss << " +" << arg.first << "=" << arg.second;
  }
  return ss.str();
}

std::string pj_error(PJ* P, std::string prefix = "proj: ") {
  std::stringstream ss;
  ss << prefix << proj_errno(P);
  return ss.str();
}

} // namespace

Proj::Proj(const std::string args) {
  proj_ = proj_create(0, args.c_str());
  if (!proj_) {
    throw std::runtime_error(pj_error(0, "proj initialization error: "));
  }
}

Proj::Proj(const std::map<std::string, std::string>& args)
  : Proj(toProjStr(args)) {
}

Proj::~Proj() {
  proj_destroy(proj_);
}

std::tuple<double, double> Proj::fwd(double lon, double lat) {
  PJ_COORD in = {{ lon, lat, 0, 0 }};
  PJ_COORD out = proj_trans(proj_, PJ_DIRECTION::PJ_FWD, in);
  return std::make_tuple<double, double>(std::move(out.uv.u), std::move(out.uv.v));
}

std::tuple<double, double> Proj::inv(double x, double y) {
  PJ_COORD in = {{ x, y, 0, 0 }};
  PJ_COORD out = proj_trans(proj_, PJ_DIRECTION::PJ_INV, in);
  return std::make_tuple<double, double>(std::move(out.uv.u), std::move(out.uv.v));
}

