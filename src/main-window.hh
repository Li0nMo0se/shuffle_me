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
    // flag to display/hide answer
    bool answer_is_displayed_ = false;

    // Add an element in the list
    QPushButton* b_add_;
    // Show question label
    QLabel* question_label_;
    // Show answer label
    QLabel* answer_label_;
    // Button to show next element
    QPushButton* b_next_;
    // Exit the program
    QPushButton* b_exit_;
    // Start the program
    QPushButton* b_start_;
    // Button to show the answer
    QPushButton* b_show_answer_;
    // Input Dialog to add a word
    QInputDialog* word_add_input_;

    // backend app
    WordsManager* words_manager_;

    // window size
    static const int width = 400;
    static const int height = 100;

    // button size
    static const int b_width = width / 4;
    static const int b_height = 30;

    // Ouput area size
    static const int label_width = width;
    static const int label_height = (height - b_height - 2 * 10) / 2;

private:
    // helper methods
    // hide answer field
    void hide_answer();
    // show answer field
    void show_answer();

public slots:
    void exit_app();
    void next_word();
    void add_word();
    void start();
    void switch_answer();
};


#endif /* ENDIF MAIN_WINDOW_HH */
