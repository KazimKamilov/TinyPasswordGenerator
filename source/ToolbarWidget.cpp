#include "ToolbarWidget.hpp"
#include "GeneratorFrame.hpp"

#include <QtGui/qevent.h>


void ToolbarWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::MouseButton::LeftButton)
		_mouse = event->localPos();
}

void ToolbarWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::MouseButton::LeftButton)
		_mouse = {0, 0};
}

void ToolbarWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::MouseButton::LeftButton)
	{
		auto position = event->localPos();
		position -= _mouse;

		_frame->move(_frame->pos() + QPoint {static_cast<int>(position.x()), static_cast<int>(position.y())});
	}
}
