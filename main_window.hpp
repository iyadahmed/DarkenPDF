#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QtWidgets>
#include <poppler.h>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handle_open_pdf_button();

private:
    PopplerDocument *m_current_open_pdf = nullptr;
    QImage *m_current_pdf_page_image = nullptr;
    int m_current_pdf_page_index = 0;
};

#endif // MAIN_WINDOW_HPP
