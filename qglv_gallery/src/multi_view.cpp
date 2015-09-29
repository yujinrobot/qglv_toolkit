/**
 * @file /dslam_viewer/src/qgl_gallery/multi_view.cpp
 * 
 * @brief Short description of this file.
 **/
/*****************************************************************************
** Includes
*****************************************************************************/

#include <QtGui/qapplication.h>
#include <QSplitter>
#include <QGLViewer/qglviewer.h>
#include <QGLViewer/manipulatedCameraFrame.h>

using namespace qglviewer;

/*****************************************************************************
** MultiView
*****************************************************************************/

class Scene
{
public:
  void draw() const;
};

class MultiView : public QGLViewer
{
public:
  MultiView(const Scene* const s, int type, QWidget* parent, const QGLWidget* shareWidget=NULL);

protected :
  virtual void draw();

private:
  const Scene* const scene_;
};

/*****************************************************************************
** MultiView
*****************************************************************************/

MultiView::MultiView(const Scene* const s, int type, QWidget* parent, const QGLWidget* shareWidget)
  : QGLViewer(parent, shareWidget), scene_(s)
{
  setAxisIsDrawn();
  setGridIsDrawn();

  if (type < 3)
        {
          // Move camera according to viewer type (on X, Y or Z axis)
          camera()->setPosition(Vec((type==0)? 1.0 : 0.0, (type==1)? 1.0 : 0.0, (type==2)? 1.0 : 0.0));
          camera()->lookAt(sceneCenter());

          camera()->setType(Camera::ORTHOGRAPHIC);
          camera()->showEntireScene();

          // Forbid rotation
          WorldConstraint* constraint = new WorldConstraint();
          constraint->setRotationConstraintType(AxisPlaneConstraint::FORBIDDEN);
          camera()->frame()->setConstraint(constraint);
        }

  restoreStateFromFile();
}

void MultiView::draw()
{
  scene_->draw();
}

// Draws a spiral
void Scene::draw() const
{
  const float nbSteps = 200.0;
  glBegin(GL_QUAD_STRIP);
  for (float i=0; i<nbSteps; ++i)
        {
          float ratio = i/nbSteps;
          float angle = 21.0*ratio;
          float c = cos(angle);
          float s = sin(angle);
          float r1 = 1.0 - 0.8f*ratio;
          float r2 = 0.8f - 0.8f*ratio;
          float alt = ratio - 0.5f;
          const float nor = 0.5f;
          const float up = sqrt(1.0-nor*nor);
          glColor3f(1.0-ratio, 0.2f , ratio);
          glNormal3f(nor*c, up, nor*s);
          glVertex3f(r1*c, alt, r1*s);
          glVertex3f(r2*c, alt+0.05f, r2*s);
        }
  glEnd();
}

/*****************************************************************************
 ** Main
 *****************************************************************************/

int main(int argc, char** argv)
{
  QApplication application(argc,argv);

  // Create Splitters
  QSplitter *hSplit  = new QSplitter(Qt::Vertical);
  QSplitter *vSplit1 = new QSplitter(hSplit);
  QSplitter *vSplit2 = new QSplitter(hSplit);

  // Create the scene
  Scene* s = new Scene();

  // Instantiate the viewers.
  MultiView side  (s,0,vSplit1);
  MultiView top   (s,1,vSplit1, &side);
  MultiView front (s,2,vSplit2, &side);
  MultiView persp (s,3,vSplit2, &side);


  hSplit->setWindowTitle("multiView");

  // Set main QSplitter as the main widget.
  hSplit->show();

  return application.exec();
}
