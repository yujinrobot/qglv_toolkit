/**
 * @file /include/qglv/gallery.hpp
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef qglv_GALLERY_HPP_
#define qglv_GALLERY_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

#include <QGLViewer/qglviewer.h>
#include <QtGui/QWidget>
#include <QtCore/QString>

/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace qglv {
namespace gallery {

/*****************************************************************************
** Interface
*****************************************************************************/

/**
 * Special class for the qgl_gallery demos that must be exposed here rather
 * than the demo cpp files (like the others) since it needs to be findable
 * the designer ui file as a promoted widget type.
 */
class Interface : public QGLViewer
{
public:
  Interface(QWidget *parent);

protected :
  virtual void draw();
  virtual QString helpString() const;
};

} // gallery
} // qglv

#endif /* qglv_GALLERY_HPP_ */
