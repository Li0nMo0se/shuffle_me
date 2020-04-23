#include <QApplication>

#include "main-window.hh"

int main(int argc, char **argv)
{
    QApplication app (argc, argv); // create the app

    Data<WordsManager::pair_t>* data = new Data<WordsManager::pair_t>;
    WordsManager* words_manager = new WordsManager(data);
    MainWindow main_window(words_manager);
    main_window.show();
    return app.exec(); // execute the app
}
