#ifndef MAIN_WINDOW_HH
#define MAIN_WINDOW_HH

#include <QWidget>
#include <QPushButton>
#include <QInputDialog>
#include <QLabel>
#include <QString>

#include "words-manager.hh"

class QPushButton;
class QInputDialog;

class MainWindow : public QWidget
{
Q_OBJECT
public:
    MainWindow(WordsManager* words_manager, QWidget* parent = nullptr);

private:
    // Add an element in the list
    QPushButton* b_add_;
    // Show word element
    QLabel* show_word_;
    // Button to show next element
    QPushButton* b_next_;
    // Exit the program
    QPushButton* b_exit_;
    // Input Dialog to add a word
    QInputDialog* word_add_input_;

    // backend app
    WordsManager* words_manager_;

    // window size
    static const int width = 300;
    static const int height = 100;

    // button size
    static const int b_width = width / 3;
    static const int b_height = 30;

    // Ouput area size
    static const int o_width = width;
    static const int o_height = height - b_height - 10;

public slots:
    void exit_app();
    void next_word();
    void add_word();
};


#endif /* ENDIF MAIN_WINDOW_HH */
