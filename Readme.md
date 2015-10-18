About
=====

This repository contains rendering api for methods and objects we use within the qglviewer framework.
This includes (simply because we don't have enough to warrant additional repositories):

* Pure opengl primitives and objects
* Qt-Opencv widgets
* PCL renderings on a gl canvas

Usage
=====

Methods and headers are arranged in the following fashion:

* One namespace for everything: qglv.
* One core header for each package, e.g. <qglv/opengl.hpp>, <qglv/opencv.hpp>.
* The gl header organiser in <qglv/gl/headers.hpp> contains the correct mix and sequence of gl headers we use.

If building your own gl classes:

* Make sure you call the gl headers first so you don't end up with GL/Glew conflicts.

Creating an application with a qglviewer with lots of lighting/keyboard/mouse/... settings appropriate
for our use cases, simply inherit our QGLViewer first:

```
#include <qglv/opengl.hpp>
#include <qglv/extras.hpp>

class MyQGLViewerCanvas : public qglv::QGLViewer
```

Dev Notes
=========

Methods and classes are usually grouped in the following header directories
(independent of package name):

* `include/qglv/gl` : for gl-like methods (e.g. qglv::moveTo(...))
* `include/qglv/primitives` : for basic renderings, e.g. arrows frames
* `include/qglv/objects` : for complicated objects that follow a typical init into a gl generated list, followed by a `draw()` function.
* `include/qglv/widgets` : for qt widgets, frames, etc.

To put what where? Packages are organised according to their dependencies. This is important so we don't
rope in a huge dependency tree for people when they don't want it. e.g. why bring in the humungous block that
is opencv if you don't use the qglv opencv widget? Even more important for pcl.

* To add a primitive/object that is only dependent on gl, put it in `qglv_opengl`.
* To add an primitive/object/widget dependent on qglviewer api, put it in `qglv_extras`.
* A nice thing to do is transition objects from qglv_extras -> qglv_opengl as we can.
* To add a primitive/object/widget dependent on opencv, put it in `qglv_opencv`
* To add a primitive/object/widget dependent on pcl, put it in `qglv_pcl`
