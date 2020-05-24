#include "words-manager.hh"
#include "main-window.hh"

MainWindow::MainWindow(WordsManager* words_manager, QWidget* parent)
 : QWidget(parent)
 , answer_is_displayed_(false)
 , b_add_(new QPushButton("Add", this))
 , question_label_(new QLabel(this))
 , answer_label_(new QLabel(this))
 , b_next_(new QPushButton("Next", this))
 , b_exit_(new QPushButton("Exit", this))
 , b_start_(new QPushButton("Start", this))
 , b_show_answer_(new QPushButton("Show answer", this))
 , word_add_input_(new QInputDialog(this))
 , words_manager_(words_manager)
{
    // Size of the main window
    this->setFixedSize(width, height);

    // Add Button
    b_add_->setGeometry(0, 0, b_width, b_height);
    connect(b_add_, SIGNAL(clicked()), this, SLOT(add_word()));

    // Next Button
    b_next_->setGeometry(b_width, 0, b_width, b_height);
    b_next_->setVisible(false);
    connect(b_next_, SIGNAL(clicked()), this, SLOT(next_word()));

    // Start Button
    b_start_->setGeometry(b_width, 0, b_width, b_height); // same as next button
    connect(b_start_, SIGNAL(clicked()), this, SLOT(start()));

    // Exit Button
    b_exit_->setGeometry(width - b_width, 0, b_width, b_height);
    connect(b_exit_, SIGNAL(clicked()), this, SLOT(exit_app()));

    // Show question area
    question_label_->setGeometry(0, b_height + 10, label_width, label_height);
    question_label_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    question_label_->setStyleSheet(QString::fromStdString("font-size: "
        + std::to_string(label_font_size) + "px;"));
    question_label_->setWordWrap(true);

    // Show answer area
    answer_label_->setGeometry(0, b_height + 10 + label_height,
        label_width, label_height);
    answer_label_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    answer_label_->setVisible(false);
    answer_label_->setStyleSheet(QString::fromStdString("font-size: "
        + std::to_string(label_font_size) + "px;"));
    answer_label_->setWordWrap(true);


    // Show answer button
    b_show_answer_->setGeometry(2 * b_width, 0, b_width, b_height);
    connect(b_show_answer_, SIGNAL(clicked()), this, SLOT(switch_answer()));

    // Input Dialog
    word_add_input_->setInputMode(QInputDialog::TextInput);
}

void MainWindow::exit_app()
{
    delete words_manager_;
    exit(0);
}

void MainWindow::next_word()
{
    hide_answer();
    WordsManager::pair_t* pair = words_manager_->next_word();
    // there is a next word, display it
    if (!pair->first.empty())
    {
        question_label_->setText(QString::fromUtf8(pair->first.data()));
        answer_label_->setText(QString::fromUtf8(pair->second.data()));
    }
    else
    {
        // no next word
        question_label_->setText("You completed the whole list. Restart!");
        b_next_->setVisible(false);
        b_start_->setVisible(true);
    }
    delete pair;
}

void MainWindow::add_word()
{
    bool ok;
    QString question = QInputDialog::getText(word_add_input_, "Add a question",
        "Enter a question:", QLineEdit::Normal, "", &ok);
    if (!ok || question.isEmpty())
        return;
    QString answer = QInputDialog::getText(word_add_input_, "Add an answer to "
        + question, "Enter an answer:",
        QLineEdit::Normal, "", &ok);
    if (!ok || answer.isEmpty())
        return;
    words_manager_->add_pair(question.toUtf8().data(),
        answer.toUtf8().data());
}

void MainWindow::start()
{
    words_manager_->start(); // load from the file

    b_next_->setVisible(true);
    b_start_->setVisible(false);

    // display first word
    next_word();
}

void MainWindow::hide_answer()
{
    b_show_answer_->setText("show answer");
    answer_label_->setVisible(false);
    answer_is_displayed_ = false;
}

void MainWindow::show_answer()
{
    b_show_answer_->setText("hide answer");
    answer_label_->setVisible(true);
    answer_is_displayed_ = true;
}

void MainWindow::switch_answer()
{
    if (answer_is_displayed_)
        hide_answer();
    else
        show_answer();
}
