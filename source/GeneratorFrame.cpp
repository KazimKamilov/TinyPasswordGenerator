#include "GeneratorFrame.hpp"
#include "ToolbarWidget.hpp"
#include "Generator.hpp"

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>


GeneratorFrame::GeneratorFrame() noexcept : QMainWindow(nullptr, Qt::FramelessWindowHint),
	_generator(std::make_unique<Generator>(this))
{
	this->createUI();
	this->setupLabels();
	this->connectActions();
}

GeneratorFrame::~GeneratorFrame() noexcept
{
}

void GeneratorFrame::connectActions() noexcept
{
	this->connect(_minimize_btn, &QToolButton::clicked, [this]() { this->showMinimized(); });
	this->connect(_close_btn, &QToolButton::clicked, [this]() { this->close(); });

	this->connect(_generate_btn, &QToolButton::clicked, [this]()
	{
		const auto password = _generator->make();

		_pass_line->setText(QString::fromStdString(password));
	});
}

void GeneratorFrame::createUI() noexcept
{
	this->setEnabled(true);
	this->resize(525, 584);
	QFont font;
	font.setStyleStrategy(QFont::PreferDefault);
	this->setFont(font);
	this->setContextMenuPolicy(Qt::NoContextMenu);
	this->setAutoFillBackground(false);
	this->setStyleSheet({
		"background-color: rgb(64, 64, 64);\n"
		"color: rgb(255, 255, 255);\n"
		"border-style: none;"
	});

	_center_widget = new QWidget(this);

	_center_layout = new QVBoxLayout(_center_widget);
	_center_layout->setContentsMargins(0, 0, 0, 0);

	_header_widget = new QWidget(_center_widget);
	_header_widget->setMinimumSize(QSize(0, 36));
	_header_widget->setMaximumSize(QSize(16777215, 60));

	_header_layout = new QVBoxLayout(_header_widget);
	_header_layout->setSpacing(0);
	_header_layout->setContentsMargins(0, 0, 0, 0);

	_toolbar = new ToolbarWidget(_header_widget, this);
	_toolbar->setStyleSheet({
		"background-color: rgb(55, 55, 55);\n"
		"border-style: none;\n"
	});

	_toolbar_layout = new QHBoxLayout(_toolbar);
	_toolbar_layout->setSpacing(0);
	_toolbar_layout->setContentsMargins(0, 0, 0, 0);

	_sizer1 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

	_toolbar_layout->addItem(_sizer1);

	_header_lbl1 = new QLabel(_toolbar);

	QFont font2;
	font2.setFamily(QString::fromUtf8("Segoe UI"));
	font2.setPointSize(11);
	font2.setBold(true);
	font2.setWeight(75);
	font2.setStyleStrategy(QFont::PreferAntialias);
	_header_lbl1->setFont(font2);

	_toolbar_layout->addWidget(_header_lbl1);

	_sizer0 = new QSpacerItem(100, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	_toolbar_layout->addItem(_sizer0);

	_window_ctrl_widget = new QWidget(_toolbar);

	_sys_btn_layout = new QVBoxLayout(_window_ctrl_widget);

	_window_btn_widget = new QWidget(_window_ctrl_widget);

	_sys_layout = new QHBoxLayout(_window_btn_widget);
	_sys_layout->setSpacing(2);

	_sys_layout->setContentsMargins(1, 1, 1, 1);
	_minimize_btn = new QToolButton(_window_btn_widget);
	_minimize_btn->setMinimumSize(QSize(26, 26));

	QIcon icon1;
	icon1.addFile(QString::fromUtf8(":/res/minimize.png"), QSize(), QIcon::Normal, QIcon::Off);

	_minimize_btn->setIcon(icon1);
	_minimize_btn->setIconSize(QSize(20, 20));

	_sys_layout->addWidget(_minimize_btn);

	_close_btn = new QToolButton(_window_btn_widget);
	_close_btn->setMinimumSize(QSize(26, 26));

	QIcon icon2;
	icon2.addFile(QString::fromUtf8(":/res/close.png"), QSize(), QIcon::Normal, QIcon::Off);

	_close_btn->setIcon(icon2);
	_close_btn->setIconSize(QSize(20, 20));

	_sys_layout->addWidget(_close_btn);

	_sys_btn_layout->addWidget(_window_btn_widget);

	_wnd_ctrl_spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

	_sys_btn_layout->addItem(_wnd_ctrl_spacer);

	_toolbar_layout->addWidget(_window_ctrl_widget);

	_header_layout->addWidget(_toolbar);

	_center_layout->addWidget(_header_widget);

	_working_widget = new QWidget(_center_widget);

	_working_layout = new QVBoxLayout(_working_widget);
	_working_layout->setContentsMargins(6, 6, 6, 6);

	_variants_group = new QGroupBox(_working_widget);
	_variants_group->setStyleSheet({
		"background-color: rgb(75, 75, 75);\n"
		"color: rgb(255, 255, 255);\n"
		"border-style: solid;\n"
		"border-radius: 4px;"
	});

	_variants_layout = new QVBoxLayout(_variants_group);
	_variants_layout->setContentsMargins(-1, 20, -1, -1);
	_radio_numbers = new QRadioButton(_variants_group);

	_variants_layout->addWidget(_radio_numbers);

	_radio_low_letters = new QRadioButton(_variants_group);

	_variants_layout->addWidget(_radio_low_letters);

	_radio_upper_letters = new QRadioButton(_variants_group);

	_variants_layout->addWidget(_radio_upper_letters);

	_radio_symbols = new QRadioButton(_variants_group);

	_variants_layout->addWidget(_radio_symbols);

	_radio_letters = new QRadioButton(_variants_group);

	_variants_layout->addWidget(_radio_letters);

	_radio_low_letters_and_numbers = new QRadioButton(_variants_group);

	_variants_layout->addWidget(_radio_low_letters_and_numbers);

	_radio_upper_letters_and_numbers = new QRadioButton(_variants_group);

	_variants_layout->addWidget(_radio_upper_letters_and_numbers);

	_radio_letters_and_numbers = new QRadioButton(_variants_group);

	_variants_layout->addWidget(_radio_letters_and_numbers);

	_radio_all = new QRadioButton(_variants_group);
	_radio_all->setChecked(true);

	_variants_layout->addWidget(_radio_all);

	_working_layout->addWidget(_variants_group);

	_symbols_group = new QGroupBox(_working_widget);
	_symbols_group->setStyleSheet(
		{"background-color: rgb(75, 75, 75);\n"
		"color: rgb(255, 255, 255);\n"
		"border-style: solid;\n"
		"border-radius: 4px;"
	});

	_symbols_layout = new QVBoxLayout(_symbols_group);
	_symbols_layout->setContentsMargins(-1, 20, -1, -1);
	_symbols_line = new QLineEdit(_symbols_group);

	QFont font3;
	font3.setPointSize(12);

	_symbols_line->setFont(font3);
	_symbols_line->setStyleSheet({
		"background-color: rgb(80, 80, 80);\n"
		"color: rgb(255, 255, 255);\n"
		"border-style: solid;\n"
		"border-radius: 2px;\n"
		"border-color: rgb(90, 90, 90);"
	});

	_symbols_layout->addWidget(_symbols_line);

	_working_layout->addWidget(_symbols_group);

	_pass_line = new QTextEdit(_working_widget);
	_pass_line->setFont(font3);
	_pass_line->setStyleSheet({
		"background-color: rgb(75, 75, 75);\n"
		"color: rgb(255, 255, 255);\n"
		"border-style: solid;\n"
		"border-radius: 4px;"
	});

	_pass_line->setReadOnly(true);

	_working_layout->addWidget(_pass_line);

	_control_widget = new QWidget(_working_widget);
	_control_widget->setStyleSheet({
		"background-color: rgb(75, 75, 75);\n"
		"color: rgb(255, 255, 255);\n"
		"border-style: solid;\n"
		"border-radius: 4px;"
	});

	_control_layout = new QHBoxLayout(_control_widget);
	_length_spin = new QSpinBox(_control_widget);
	_length_spin->setMinimumSize(QSize(50, 24));

	QFont font4;
	font4.setPointSize(10);

	_length_spin->setFont(font4);

	_length_spin->setStyleSheet({
		"background-color: rgb(80, 80, 80);\n"
		"color: rgb(255, 255, 255);\n"
		"border-style: solid;\n"
		"border-radius: 2px;\n"
		"border-color: rgb(90, 90, 90);"
	});

	_length_spin->setAlignment(Qt::AlignCenter);
	_length_spin->setValue(6);
	_length_spin->setMinimum(1);
	_length_spin->setMaximum(512);

	_control_layout->addWidget(_length_spin);

	_length_label = new QLabel(_control_widget);

	QFont font5;
	font5.setPointSize(9);
	_length_label->setFont(font5);

	_control_layout->addWidget(_length_label);

	_sizer2 = new QSpacerItem(156, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

	_control_layout->addItem(_sizer2);

	_generate_btn = new QPushButton(_control_widget);
	_generate_btn->setMinimumSize(QSize(75, 28));
	_generate_btn->setFont(font4);
	_generate_btn->setStyleSheet({
		"background-color: rgb(80, 80, 80);\n"
		"color: rgb(255, 255, 255);\n"
		"border-style: solid;\n"
		"border-radius: 2px;\n"
		"border-color: rgb(90, 90, 90);"
	});

	_control_layout->addWidget(_generate_btn);

	_working_layout->addWidget(_control_widget);

	_center_layout->addWidget(_working_widget);

	this->setCentralWidget(_center_widget);

	QMetaObject::connectSlotsByName(this);
}

void GeneratorFrame::setupLabels() noexcept
{
	_header_lbl1->setText(QCoreApplication::translate("this", "Tiny Password Generator", nullptr));
	_variants_group->setTitle(QCoreApplication::translate("this", "Variants", nullptr));
	_radio_numbers->setText(QCoreApplication::translate("this", "Only numbers", nullptr));
	_radio_low_letters->setText(QCoreApplication::translate("this", "Lowercase letters", nullptr));
	_radio_upper_letters->setText(QCoreApplication::translate("this", "Uppercase letters", nullptr));
	_radio_symbols->setText(QCoreApplication::translate("this", "Special symbols", nullptr));
	_radio_letters->setText(QCoreApplication::translate("this", "Lowercase and uppercase letters", nullptr));
	_radio_low_letters_and_numbers->setText(QCoreApplication::translate("this", "Lowercase letters and numbers", nullptr));
	_radio_upper_letters_and_numbers->setText(QCoreApplication::translate("this", "Uppercase letters and numbers", nullptr));
	_radio_letters_and_numbers->setText(QCoreApplication::translate("this", "Lowercase, uppercase letters and numbers", nullptr));
	_radio_all->setText(QCoreApplication::translate("this", "All of them", nullptr));
	_symbols_group->setTitle(QCoreApplication::translate("this", "Special Symbols", nullptr));
	_symbols_line->setText(QCoreApplication::translate("this", "!@#$%^&_", nullptr));
	_pass_line->setPlaceholderText(QCoreApplication::translate("this", "Generated password will be here...", nullptr));
	_length_label->setText(QCoreApplication::translate("this", "Password length(512 symbols max)", nullptr));
	_generate_btn->setText(QCoreApplication::translate("this", "Generate!", nullptr));
}

GeneratorMode GeneratorFrame::getGeneratorMode() const
{
	uint32_t mode = 0u;

	for (const auto& child : _variants_group->children())
	{
		auto radio = qobject_cast<QRadioButton*>(child);

		if (!radio)
			continue;

		if (radio->isChecked())
			return static_cast<GeneratorMode>(mode);

		++mode;
	}

	throw std::exception("Unknown radio selected!");
}

uint32_t GeneratorFrame::getPasswordLength() const noexcept
{
	return static_cast<uint32_t>(_length_spin->value());
}

std::string GeneratorFrame::getSpecialSymbols() const noexcept
{
	return _symbols_line->text().toStdString();
}
