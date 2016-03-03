/**
 * @file /include/qglv/objects/potential_field.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_OBJECTS_POTENTIAL_FIELD_HPP_
#define qglv_OBJECTS_POTENTIAL_FIELD_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <limits>
#include <memory>
#include <vector>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Potential Field
*****************************************************************************/

/**
 * For drawing two dimensional arrays of squares filled with a
 * colour reflecting each cell's value.
 */
class PotentialField {

public:
  PotentialField(const unsigned int& nx,
                 const unsigned int& ny,
                 const float& resolution,
                 const std::vector<unsigned char>& potential_array
                );

  PotentialField(const unsigned int& nx,
                 const unsigned int& ny,
                 const float& resolution,
                 const std::vector<float>& potential_array);
  virtual ~PotentialField();
  void draw();

  unsigned int number_of_cells_x, number_of_cells_y;
  float resolution;

private:
  virtual void _glGenLists();
  int gl_id; /**< @brief Opengl id starting point for the lists. **/
  unsigned int gl_vertex_buffer_id, gl_index_buffer_id;
  std::vector< float > values;

  template<typename element_type>
  void _init(const std::vector<element_type>& potential_array) {
    // normalise
    float min_value = std::numeric_limits<float>::max();
    float max_value = std::numeric_limits<float>::min();
    for ( const auto& value : potential_array ) {
      if ( value != std::numeric_limits<float>::infinity() ) {
        if ( value < min_value ) { min_value = value; }
        if ( value > max_value ) { max_value = value; }
      }
    }
    // normalise from 0.3->0.8
    float range = (max_value > min_value) ? (max_value - min_value) : 1.0;
    for ( unsigned int i = 0; i < potential_array.size(); ++i ) {
      if ( potential_array[i] == std::numeric_limits<float>::infinity() ) {
        values[i] = 0.0;
      } else {
        values[i] = 0.1 + 0.8*(potential_array[i] - min_value)/range;
      }
    }
  //  for ( unsigned int y = 0; y < number_of_cells_y; ++y) {
  //    std::cout << y << ": ";
  //    for ( unsigned int x = 0; x < number_of_cells_x; ++x) {
  //      std::cout << values[y*number_of_cells_y + x] << " ";
  //    }
  //    std::cout << std::endl;
  //  }
    // TODO check that values is the correct size.
  }
};

/*****************************************************************************
 ** Typedefs
 *****************************************************************************/

typedef std::shared_ptr<PotentialField> PotentialFieldPtr;

/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace qglv

#endif /* qglv_OBJECTS_POTENTIAL_FIELD_HPP_ */
