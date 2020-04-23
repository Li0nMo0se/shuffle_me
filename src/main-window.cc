#include "main-window.hh"

MainWindow::MainWindow(WordsManager* words_manager, QWidget* parent)
 : QWidget(parent)
 , b_add_(new QPushButton("Add", this))
 , show_word_(new QLabel(this))
 , b_next_(new QPushButton("Next", this))
 , b_exit_(new QPushButton("Exit", this))
 , b_start_(new QPushButton("Start", this))
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

    // Show word area
    show_word_->setGeometry(width - o_width, height - o_height, o_width,
        o_height);
    show_word_->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

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
    std::string* next_str = words_manager_->next_word();
    // there is a next word, display it
    if (!next_str->empty())
    {
        show_word_->setText(QString::fromUtf8(next_str->data()));
        return;
    }
    // no next word
    show_word_->setText("You completed the whole list. Restart!");
    b_next_->setVisible(false);
    b_start_->setVisible(true);
    delete next_str;
}

void MainWindow::add_word()
{
    bool ok;
    QString text = QInputDialog::getText(word_add_input_, "Add a word",
        "Enter a word:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty())
        words_manager_->add_word(text.toUtf8().data());
}

void MainWindow::start()
{
    words_manager_->start(); // load from the file

    b_next_->setVisible(true);
    b_start_->setVisible(false);

    // display first word
    next_word();
}
