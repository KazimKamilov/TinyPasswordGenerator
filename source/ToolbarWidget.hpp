#ifndef _TINY_PASSWORD_GENERATOR_TOOLBAR_WIDGET_HPP_
#define _TINY_PASSWORD_GENERATOR_TOOLBAR_WIDGET_HPP_

#include <QtWidgets/QWidget>


class GeneratorFrame;

/**
	Tricky class for possibility to drag application window by header panel.
*/
class ToolbarWidget final : public QWidget
{
public:
	ToolbarWidget(QWidget* parent, GeneratorFrame* frame) noexcept :
		QWidget(parent), _frame(frame)
	{
	}

protected:
	virtual void mousePressEvent(QMouseEvent* event) override;
	virtual void mouseReleaseEvent(QMouseEvent* event) override;
	virtual void mouseMoveEvent(QMouseEvent* event) override;

private:
	GeneratorFrame* _frame = nullptr;
	QPointF _mouse {0.0f, 0.0f};

};

#endif
