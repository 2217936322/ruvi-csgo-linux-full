//
//  ruvi base
//

#pragma once

// includes
#include "../memory/memory.hh"
#include <string>

enum material_flags_t {

  MATERIAL_VAR_DEBUG                    = (1 << 0),
  MATERIAL_VAR_NO_DEBUG_OVERRIDE        = (1 << 1),
  MATERIAL_VAR_NO_DRAW                  = (1 << 2),
  MATERIAL_VAR_USE_IN_FILLRATE_MODE     = (1 << 3),
  MATERIAL_VAR_VERTEXCOLOR              = (1 << 4),
  MATERIAL_VAR_VERTEXALPHA              = (1 << 5),
  MATERIAL_VAR_SELFILLUM                = (1 << 6),
  MATERIAL_VAR_ADDITIVE                 = (1 << 7),
  MATERIAL_VAR_ALPHATEST                = (1 << 8),
  MATERIAL_VAR_MULTIPASS                = (1 << 9),
  MATERIAL_VAR_ZNEARER                  = (1 << 10),
  MATERIAL_VAR_MODEL                    = (1 << 11),
  MATERIAL_VAR_FLAT                     = (1 << 12),
  MATERIAL_VAR_NOCULL                   = (1 << 13),
  MATERIAL_VAR_NOFOG                    = (1 << 14),
  MATERIAL_VAR_IGNOREZ                  = (1 << 15),
  MATERIAL_VAR_DECAL                    = (1 << 16),
  MATERIAL_VAR_ENVMAPSPHERE             = (1 << 17),
  MATERIAL_VAR_NOALPHAMOD               = (1 << 18),
  MATERIAL_VAR_ENVMAPCAMERASPACE        = (1 << 19),
  MATERIAL_VAR_BASEALPHAENVMAPMASK      = (1 << 20),
  MATERIAL_VAR_TRANSLUCENT              = (1 << 21),
  MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
  MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING  = (1 << 23),
  MATERIAL_VAR_OPAQUETEXTURE            = (1 << 24),
  MATERIAL_VAR_ENVMAPMODE               = (1 << 25),
  MATERIAL_VAR_SUPPRESS_DECALS          = (1 << 26),
  MATERIAL_VAR_HALFLAMBERT              = (1 << 27),
  MATERIAL_VAR_WIREFRAME                = (1 << 28),
};

class i_material_var {
public:
  void set_float_value(float value) {
    return memory::vfunc<4, void>(this, value);
  }
};

class i_material {
public:
  const char* get_name() {
    return memory::vfunc<0, const char*>(this);
  }

  const char* get_texture_group_name() {
    return memory::vfunc<1, const char*>(this);
  }

  void increment_reference_count() { return memory::vfunc<4, void>(this); }

  void alpha_modulate(float alpha) {
    return memory::vfunc<27, void>(this, alpha);
  }

  void color_modulate(float red, float green, float blue) {
    return memory::vfunc<28, void>(this, red, green, blue);
  }

  void set_material_flag(material_flags_t flag, bool onoff) {
    return memory::vfunc<29, void>(this, flag, onoff);
  }
};