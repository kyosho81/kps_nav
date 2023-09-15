

#ifndef ABSTRACTRENDERER_H_
#define ABSTRACTRENDERER_H_

#ifndef Q_MOC_RUN 
#include <GL/gl.h>
#include <GL/glu.h>
#endif
#include <flirt/gui/Color.h>

class AbstractRenderer {
    public:
	virtual ~AbstractRenderer() { }
	virtual void render() = 0;
};

#endif

