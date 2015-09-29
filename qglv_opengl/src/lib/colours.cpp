/**
 * @file src/lib/colour.cpp
 **/

/*****************************************************************************
** Includes
*****************************************************************************/

#include "../../include/qglv/gl/headers.hpp"
#include "../../include/qglv/gl/colours.hpp"

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace qglv {

/*****************************************************************************
 ** Drawing methods
 *****************************************************************************/

void colour(enum Colour colour, const float& alpha) {
  switch (colour) {
    case Blue:
      glColor4f(0.0f, 0.0f, 1.0f, alpha);
      break;
    case DimGray:
      glColor4f(0.411f, 0.411f, 0.411f, alpha);
      break;
    case Gray19:
      glColor4f(0.188f, 0.188f, 0.188f, alpha);
      break;
    case GoldenBrown:
      glColor4f(0.6f, 0.4f, 0.08f, alpha);
      break;
    case Green:
      glColor4f(0.0f, 1.0f, 0.0f, alpha);
      break;
    case Magenta:
      glColor4f(1.0f, 0.0f, 1.0f, alpha);
      break;
    case Pink:
      glColor4f(1.0f, 0.078f, 0.57f, alpha);
      break;
    case Maroon:
      glColor4f(0.5f, 0.0f, 0.0f, alpha);
      break;
    case Orange:
      glColor4f(1.0f, 0.64f, 0.0f, alpha);
      break;
    case Red:
      glColor4f(1.0f, 0.0f, 0.0f, alpha);
      break;
    case White:
      glColor4f(1.0f, 1.0f, 1.0f, alpha);
      break;
    case Yellow:
      glColor4f(1.0f, 1.0f, 0.0f, alpha);
      break;
    default : // Red
      glColor4f(1.0f, 0.0f, 0.0f, alpha);
      break;
  }
}

void normalisedValueToRGB(const float& value, float& r, float& g, float& b) {
  float bounded_value = value;
  if( bounded_value < 0.0f ) {
    bounded_value = 0.0f;
  } else if ( bounded_value > 1.0f ) {
    bounded_value = 1.0f;
  }

  if( bounded_value < 0.25f )
  {
    r = 1.0f;
    g = bounded_value / 0.25f;
    b = 0.0f;
  }
  else if( bounded_value < 0.5f )
  {
    r = 1.0f - (bounded_value-0.25f) / 0.25f;
    g = 1.0f;
    b = 0.0f;
  }
  else if( bounded_value < 0.75f )
  {
    r = 0.0f;
    g = 1.0f;
    b = (bounded_value-0.5f)/0.25f;
  }
  else
  {
    r = 0.0f;
    g = 1.0f - (bounded_value-0.75f)/0.25f;
    b = 1.0f;
  }
};


} // namespace qglv

