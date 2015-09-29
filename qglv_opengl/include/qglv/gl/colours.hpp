/**
 * @file include/qglv/gl/colour.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_GL_COLOUR_HPP_
#define qglv_GL_COLOUR_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

/*****************************************************************************
** Namespace
*****************************************************************************/

namespace qglv {

enum Colour {
  Blue,
  DimGray,     // http://www.color-hex.com/color/696969
  Gray19,      // http://www.color-hex.com/color/303030
  GoldenBrown, // http://www.rapidtables.com/web/color/Gold_Color.htm
  Green,
  Magenta,
  Maroon,
  Orange,
  Pink,
  Red,
  White,
  Yellow
};

enum AxisColourScheme {
  AxisColourRGB,
  AxisColourFadedBlue,
  AxisColourGolden,
  AxisColourGreen,
  AxisColourBlue,
  AxisColourRed,
  AxisColourMagenta,
  AxisColourGray,
  AxisColourWhite,
};

/**
 * @brief Emulates glColor4f, but with the qglv Colour enums.
 * @param colour
 * @param alpha
 */
void colour(enum Colour colour, const float& alpha=1.0f);

/**
 * @brief Converts a float between 0.0 and 1.0 to rgb.
 *
 * If it happens to fall outside that range, it just resets the
 * value to the appropriate boundary value.
 *
 * @param value : normalised value (should be between 0.0 and 1.0)
 * @param r
 * @param g
 * @param b
 */
void normalisedValueToRGB(const float& value, float& r, float& g, float& b);

} // namespace qglv

#endif /* qglv_GL_COLOUR_HPP_ */
