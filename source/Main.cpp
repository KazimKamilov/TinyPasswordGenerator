#include <QApplication>
#include <QResource>
#include "GeneratorFrame.hpp"

#ifdef WIN32
int WinMain(int argc, char* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	QApplication application(argc, argv);
	application.setWindowIcon(QIcon(":/res/app.ico"));

	GeneratorFrame frame;
	frame.show();

	return application.exec();
}
