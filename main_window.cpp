#include <poppler.h>
#include <cairo.h>
#include <cairo-pdf.h>

#include <QtWidgets>

#include "main_window.hpp"

MainWindow::MainWindow(QWidget *parent)
{
    setWindowTitle("Darken PDF");

    QHBoxLayout *main_layout = new QHBoxLayout;
    setLayout(main_layout);

    QWidget *preview_widget = new QWidget;
    QWidget *controls_widget = new QWidget;
    main_layout->addWidget(controls_widget, 1);
    main_layout->addWidget(preview_widget, 2);

    QHBoxLayout *preview_layout = new QHBoxLayout;
    preview_layout->setAlignment(Qt::AlignmentFlag::AlignCenter);

    QLabel *preview_label = new QLabel("Preview");
    preview_label->setEnabled(false);
    preview_layout->addWidget(preview_label);
    preview_widget->setLayout(preview_layout);

    QVBoxLayout *controls_layout = new QVBoxLayout;
    controls_layout->setAlignment(Qt::AlignmentFlag::AlignTop);
    controls_widget->setLayout(controls_layout);

    QSlider *brightness_slider = new QSlider(Qt::Orientation::Horizontal);
    brightness_slider->setEnabled(false);

    QSlider *contrast_slider = new QSlider(Qt::Orientation::Horizontal);
    contrast_slider->setEnabled(false);

    QLabel *brightness_label = new QLabel("Brightness");
    brightness_label->setEnabled(false);

    QLabel *contrast_label = new QLabel("Contrast");
    contrast_label->setEnabled(false);

    controls_layout->addWidget(brightness_label);
    controls_layout->addWidget(brightness_slider);
    controls_layout->addWidget(contrast_label);
    controls_layout->addWidget(contrast_slider);

    QPushButton *open_pdf_button = new QPushButton("Open PDF");
    controls_layout->addWidget(open_pdf_button);

    connect(open_pdf_button, &QPushButton::released, this, &MainWindow::handle_open_pdf_button);
}

MainWindow::~MainWindow()
{
    if (m_current_open_pdf != nullptr)
    {
        g_object_unref(m_current_open_pdf);
    }
}

void MainWindow::handle_open_pdf_button()
{
    GError *error;

    QString pdf_file_path = QFileDialog::getOpenFileName(nullptr, "Open PDF file", "", "*.pdf");
    std::string s_pdf_file_path = pdf_file_path.toStdString();
    gchar *uri = g_filename_to_uri(s_pdf_file_path.c_str(), nullptr, &error);
    if (uri == nullptr)
    {
        printf("Failed to get URI from file path: %s\n", error->message);
        return;
    }

    m_current_open_pdf = poppler_document_new_from_file(uri, nullptr, &error);
    if (m_current_open_pdf == nullptr)
    {
        printf("Failed to open PDF: %s\n", error->message);
        return;
    }
    free(uri);
}
