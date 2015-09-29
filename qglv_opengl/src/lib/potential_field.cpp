/**
 * @file /src/lib/potential_field.cpp
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <limits>
#include <numeric>

#include "../../include/qglv/gl/headers.hpp"
#include "../../include/qglv/objects/potential_field.hpp"

/*****************************************************************************
 ** Macros
 *****************************************************************************/

#define BUFFER_OFFSET(bytes) ((GLubyte*) NULL + (bytes))

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {

/*****************************************************************************
** Implementation
*****************************************************************************/

PotentialField::PotentialField(const unsigned int& nx,
                               const unsigned int& ny,
                               const float& resolution,
                               const std::vector<unsigned char>& potential_array
                              )
: gl_id(-1)
, gl_vertex_buffer_id(0)
, gl_index_buffer_id(0)
, number_of_cells_x(nx)
, number_of_cells_y(ny)
, resolution(resolution)
, values(potential_array.size())
{
  _init(potential_array, std::numeric_limits<float>::max());
}

PotentialField::PotentialField(const unsigned int& nx,
                               const unsigned int& ny,
                               const float& resolution,
                               const std::vector<float>& potential_array,
                               const float& threshold
                              )
: gl_id(-1)
, gl_vertex_buffer_id(0)
, gl_index_buffer_id(0)
, number_of_cells_x(nx)
, number_of_cells_y(ny)
, resolution(resolution)
, values(potential_array.size())
{
  _init(potential_array, threshold);
}

PotentialField::~PotentialField() {
  if ( gl_id > 0 ) {
    glDeleteLists(gl_id, 1);
  }
  if ( gl_vertex_buffer_id > 0 ) {
    ::glDeleteBuffers(1, &gl_vertex_buffer_id);
  }
  if ( gl_index_buffer_id > 0 ) {
    ::glDeleteBuffers(1, &gl_index_buffer_id);
  }
}

void PotentialField::draw() {
  if ( gl_id == -1 ) {
    _glGenLists();
  }
  ::glCallList(gl_id);
}

void PotentialField::_glGenLists() {
  float alpha = 0.3;
  const int position_data_size_in_elements = 2;
  const int normal_data_size_in_elements = 0; //3;
  const int color_data_size_in_elements = 4;  // DJS : 4 for alpha

  int floats_per_vertex = position_data_size_in_elements + normal_data_size_in_elements + color_data_size_in_elements;
  int x_length = number_of_cells_x + 1;  // no. of vertices along the x-side
  int y_length = number_of_cells_y + 1;  // no. of vertices along the y-side

  /********************
   ** Build Vertices
   ********************/
  std::vector<float> vertice_array(x_length*y_length*floats_per_vertex);
  int index = 0;
  for ( int y = 0; y < y_length; ++y) {
    for ( int x = 0; x < x_length; ++x) {
      //position
      vertice_array[index++] = x*resolution;
      vertice_array[index++] = y*resolution;
//      vertice_array[index++] = 0.0; // only 2d drawing here
      // normals
//      vertice_array[index++] = 0.0;
//      vertice_array[index++] = 0.0;
//      vertice_array[index++] = 1.0;
      // colour
      float intensity = 0.0;
      if ( ( x > 0 ) && (y > 0) && (x < (x_length - 1)) && (y < (y_length - 1)) ) {
        std::vector<float> sub_intensities;
        float i;
        if ( (i = values[(y-1)*number_of_cells_x + (x-1)]) > 0.0 ) { sub_intensities.push_back(i); }
        if ( (i = values[(y-1)*number_of_cells_x + (x)]) > 0.0 ) { sub_intensities.push_back(i); }
        if ( (i = values[(y)*number_of_cells_x + (x-1)]) > 0.0 ) { sub_intensities.push_back(i); }
        if ( (i = values[(y)*number_of_cells_x + (x)]) > 0.0 ) { sub_intensities.push_back(i); }
        if ( sub_intensities.size() > 0 ) {
          intensity = std::accumulate(sub_intensities.begin(), sub_intensities.end(), 0.0) / static_cast<float>(sub_intensities.size());
        }
      }
      if ( intensity == 0.0 ) {
        vertice_array[index++] = 0.2;
        vertice_array[index++] = 0.2;
        vertice_array[index++] = 0.2;
      } else {
        // float r, g, b;
        // dslam_common::valueToRgb()((1.0 - intensity)*(1.0 - intensity), r, g, b);
        // vertice_array[index++] = r;
        // vertice_array[index++] = g;
        // vertice_array[index++] = b;
        vertice_array[index++] = intensity;
        vertice_array[index++] = 0.0;
        vertice_array[index++] = 1.0 - intensity;
      }
      vertice_array[index++] = alpha;  // uncomment and set colour_data_size_in_elements to 4
    }
  }

  /********************
   ** Build Index Data
   ********************/
  const int number_of_strips_required = y_length - 1;
  const int number_of_degenerates_required = 2*(number_of_strips_required - 1);
  const int number_of_vertices_per_strip = 2*x_length;
  // opengl index data must be unsigned bytes or shorts
  std::vector<unsigned int> index_array(number_of_vertices_per_strip*number_of_strips_required + number_of_degenerates_required);
  index = 0;
  for ( int y = 0; y < number_of_strips_required; ++y) {
    if ( y > 0 ) {
      // degenerate, repeat first vertex
      index_array[index++] = static_cast<unsigned int>(y*y_length);
    }
    for ( int x = 0; x < x_length; ++x) {
      // one part of the strip
      index_array[index++] = static_cast<unsigned int>((y*y_length) + x);
      index_array[index++] = static_cast<unsigned int>(((y+1)*y_length) + x);
    }
    if ( y < y_length - 2) {
      index_array[index++] = static_cast<unsigned int>(((y + 1) * y_length) + (x_length - 1));
    }
  }

  // Create a vertex attributes buffer (e.g. position, colour etc)
  if ( gl_vertex_buffer_id > 0 ) {
    glDeleteBuffers(1, &gl_vertex_buffer_id);
  }
  glGenBuffers(1, &gl_vertex_buffer_id);
  glBindBuffer(GL_ARRAY_BUFFER, gl_vertex_buffer_id);  // make it the active buffer
  glBufferData(GL_ARRAY_BUFFER, vertice_array.size() * sizeof(float), vertice_array.data(), GL_STATIC_DRAW); // add the data to the buffer
//  glBindBuffer(GL_ARRAY_BUFFER, 0); // release the buffer (i.e. make it not active)

  // Create an index buffer (https://www.opengl.org/sdk/docs/man/html/glBindBuffer.xhtml)
  if ( gl_index_buffer_id > 0 ) {
    glDeleteBuffers(1, &gl_index_buffer_id);
  }
  glGenBuffers(1, &gl_index_buffer_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_index_buffer_id);  // make it the active buffer
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_array.size() * sizeof(unsigned int), index_array.data(), GL_STATIC_DRAW); // add the data to the buffer
//  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // release the buffer (i.e. make it not active)

  int stride = floats_per_vertex*sizeof(float);
  int index_count = index_array.size();

  gl_id = ::glGenLists(1);
  glNewList( gl_id, GL_COMPILE );
  glPushMatrix();
  // nvidia defaults for built-in attribute indices : https://www.opengl.org/sdk/docs/tutorials/ClockworkCoders/attributes.php
  // 0 - gl_Vertex, 2 - gl_Normal, 3 - gl_Color
  // how to actually get the built-in attribute indices without guessing like this?
  //  * you have to use glVertexPointer, glColorPointer for built-ins (glVertexAttribPointer is for custom attributes)
  //    * nvidia aliases to these, so its just a lucky chance
  //  * built-ins are deprecated and you will eventually have to supply your own (hopefully some system will add reasonable default shaders)

  // Attributes - legacy built-in calls
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(position_data_size_in_elements, GL_FLOAT, stride, BUFFER_OFFSET(0));
  glEnableClientState(GL_COLOR_ARRAY);
  glColorPointer(color_data_size_in_elements, GL_FLOAT, stride, BUFFER_OFFSET((position_data_size_in_elements+normal_data_size_in_elements)*sizeof(float)));

  // Attributes - future custom attribute call (using nvidia aliases to built-ins)
  // glEnableVertexAttribArray(0);
  // glVertexAttribPointer(0, position_data_size_in_elements, GL_FLOAT, false, stride, 0);
  // glVertexAttribPointer(2, normal_data_size_in_elements, GL_FLOAT, false, stride, BUFFER_OFFSET(position_data_size_in_elements*sizeof(float)));
  // glEnableVertexAttribArray(2);
  // glEnableVertexAttribArray(3);
  // glVertexAttribPointer(3, color_data_size_in_elements, GL_FLOAT, false, stride, BUFFER_OFFSET((position_data_size_in_elements+normal_data_size_in_elements)*sizeof(float)));

  glBindBuffer(GL_ARRAY_BUFFER, gl_vertex_buffer_id);  // make it the active buffer
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_index_buffer_id);  // make it the active buffer
  glDrawElements(GL_TRIANGLE_STRIP, index_count, GL_UNSIGNED_INT, 0); // UNSIGNED_SHORT is faster, but only goes up to 65k indices.
  glBindBuffer(GL_ARRAY_BUFFER, 0); // release the buffer (i.e. make it not active)
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); // release the buffer (i.e. make it not active)

  // legacy built-in attribute usage
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisableClientState(GL_COLOR_ARRAY);
  // future custom attribute usage
  //glDisableVertexAttribArray(0);
  //glDisableVertexAttribArray(1);
  //glDisableVertexAttribArray(3);
  glPopMatrix();
  glEndList();
}

/*****************************************************************************
 ** Trailers
 *****************************************************************************/

} // namespace dslam_viewer
