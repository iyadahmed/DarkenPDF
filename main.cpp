#include <cstdio>
#include <cstdlib>

#include <poppler.h>
#include <cairo.h>
#include <cairo-pdf.h>

#include "lib.hpp"

int main(int argc, char *argv[]) {
    PopplerDocument *document;
    GError *error;
    const char *pdf_file;
    gchar *absolute, *uri;
    int num_pages;

    if (argc != 2) {
        printf("Expected arguments: input_file.pdf\n");
        return 0;
    }

    pdf_file = argv[1];
    error = nullptr;

    if (g_path_is_absolute(pdf_file)) {
        absolute = g_strdup(pdf_file);
    } else {
        gchar *dir = g_get_current_dir();
        absolute = g_build_filename(dir, pdf_file, (gchar *) nullptr);
        free(dir);
    }

    uri = g_filename_to_uri(absolute, nullptr, &error);
    free(absolute);
    if (uri == nullptr) {
        printf("%s\n", error->message);
        return 1;
    }

    document = poppler_document_new_from_file(uri, nullptr, &error);
    if (document == nullptr) {
        printf("%s\n", error->message);
        return 1;
    }
    free(uri);

    num_pages = poppler_document_get_n_pages(document);
    if (num_pages < 1) {
        printf("empty PDF\n");
        return 1;
    }

    PopplerPage *first_page = poppler_document_get_page(document, 0);
    if (first_page == nullptr) {
        printf("poppler fail: page not found\n");
        return 1;
    }

    double pdf_width, pdf_height;
    poppler_page_get_size(first_page, &pdf_width, &pdf_height);
    g_object_unref(first_page);

    cairo_surface_t *output_pdf_surface = cairo_pdf_surface_create("output.pdf", IMAGE_DPI * pdf_width / 72.0,
                                                                   IMAGE_DPI * pdf_height / 72.0);
    cairo_t *cr = cairo_create(output_pdf_surface);

    for (int page_index = 0; page_index < num_pages; page_index++) {
        cairo_surface_t *surface = poppler_document_get_page_as_cairo_image_surface(document, page_index);
        cairo_image_surface_adjust_brightness_contrast(surface, 10, -100);

        cairo_set_source_surface(cr, surface, 0, 0);
        cairo_paint(cr);
        cairo_show_page(cr);

        cairo_surface_destroy(surface);
    }

    cairo_destroy(cr);
    cairo_surface_flush(output_pdf_surface);
    cairo_surface_destroy(output_pdf_surface);

    g_object_unref(document);

    return 0;
}