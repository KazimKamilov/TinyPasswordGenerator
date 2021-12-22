#ifndef _TINY_PASSWORD_GENERATOR_FRAME_HPP_
#define _TINY_PASSWORD_GENERATOR_FRAME_HPP_

#include <memory>
#include <string>

#include <QMainWindow>
#include <stdint.h>

class QWidget;
class QVBoxLayout;
class QHBoxLayout;
class QSpacerItem;
class QLabel;
class QToolButton;
class QGroupBox;
class QRadioButton;
class QLineEdit;
class QTextEdit;
class QSpinBox;
class QPushButton;
class ToolbarWidget;
class Generator;

enum class GeneratorMode : uint16_t
{
	NUMBERS = 0u,
	LOWCASE_LETTERS,
	UPPERCASE_LETTERS,
	SPECIAL_SYMBOLS,
	JUST_LETTERS,
	LOWCASE_LETTERS_AND_NUMBERS,
	UPPERCASE_LETTERS_AND_NUMBERS,
	LETTERS_AND_NUMBERS,
	ALL
};

class GeneratorFrame final : public QMainWindow
{
	Q_OBJECT

public:
	GeneratorFrame() noexcept;
	virtual ~GeneratorFrame() noexcept;

	GeneratorMode getGeneratorMode() const;
	uint32_t getPasswordLength() const noexcept;
	std::string getSpecialSymbols() const noexcept;

private:
	void createUI() noexcept;
	void setupLabels() noexcept;
	void connectActions() noexcept;

private:
	std::unique_ptr<Generator> _generator;

	QWidget* _center_widget = nullptr;
	QVBoxLayout* _center_layout = nullptr;
	QWidget* _header_widget = nullptr;
	QVBoxLayout* _header_layout = nullptr;
	ToolbarWidget* _toolbar = nullptr;
	QHBoxLayout* _toolbar_layout = nullptr;
	QSpacerItem* _sizer1 = nullptr;
	QLabel* _header_lbl1 = nullptr;
	QSpacerItem* _sizer0 = nullptr;
	QWidget* _window_ctrl_widget = nullptr;
	QVBoxLayout* _sys_btn_layout = nullptr;
	QWidget* _window_btn_widget = nullptr;
	QHBoxLayout* _sys_layout = nullptr;
	QToolButton* _minimize_btn = nullptr;
	QToolButton* _close_btn = nullptr;
	QSpacerItem* _wnd_ctrl_spacer = nullptr;
	QWidget* _working_widget = nullptr;
	QVBoxLayout* _working_layout = nullptr;
	QGroupBox* _variants_group = nullptr;
	QVBoxLayout* _variants_layout = nullptr;
	QRadioButton* _radio_numbers = nullptr;
	QRadioButton* _radio_low_letters = nullptr;
	QRadioButton* _radio_upper_letters = nullptr;
	QRadioButton* _radio_symbols = nullptr;
	QRadioButton* _radio_letters = nullptr;
	QRadioButton* _radio_low_letters_and_numbers = nullptr;
	QRadioButton* _radio_upper_letters_and_numbers = nullptr;
	QRadioButton* _radio_letters_and_numbers = nullptr;
	QRadioButton* _radio_all = nullptr;
	QGroupBox* _symbols_group = nullptr;
	QVBoxLayout* _symbols_layout = nullptr;
	QLineEdit* _symbols_line = nullptr;
	QTextEdit* _pass_line = nullptr;
	QWidget* _control_widget = nullptr;
	QHBoxLayout* _control_layout = nullptr;
	QSpinBox* _length_spin = nullptr;
	QLabel* _length_label = nullptr;
	QSpacerItem* _sizer2 = nullptr;
	QPushButton* _generate_btn = nullptr;

};

#endif
