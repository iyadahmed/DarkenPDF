#pragma once

#include <cmath>
#include <cstdio>

#include <cairo.h>
#include <poppler.h>

#define IMAGE_DPI 170

void cairo_image_surface_adjust_brightness_contrast(cairo_surface_t *surface, int contrast_factor = 1,
                                                    int brightness_offset = 0)
{
    cairo_surface_flush(surface);
    unsigned char *data = cairo_image_surface_get_data(surface);
    if (data == nullptr)
    {
        printf("Failed to get image data\n");
    }
    else
    {
        unsigned char *iter = data;
        int stride = cairo_image_surface_get_stride(surface);
        int image_height = cairo_image_surface_get_height(surface);
        while (iter < (data + stride * image_height))
        {
            for (int i = 0; i < 3; i++)
            {
                unsigned char &c = (*iter);
                int c_remapped = (static_cast<int>(c) - 127 + brightness_offset) * contrast_factor + 127;
                c = std::min(std::max(c_remapped, 0), 255);
                iter++;
            }
            iter++; // Skip alpha
        }
    }
    cairo_surface_mark_dirty(surface);
}

cairo_surface_t *poppler_document_get_page_as_cairo_image_surface(PopplerDocument *document, int page_index)
{
    PopplerPage *page = poppler_document_get_page(document, page_index);
    if (page == nullptr)
    {
        printf("Failed to get page: %d\n", page_index);
        return nullptr;
    }

    double width, height;
    poppler_page_get_size(page, &width, &height);

    /* For correct rendering of PDF, the PDF is first rendered to a
     * transparent image (all alpha = 0). */
    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, IMAGE_DPI * width / 72.0,
                                                          IMAGE_DPI * height / 72.0);
    cairo_t *cr = cairo_create(surface);
    cairo_scale(cr, IMAGE_DPI / 72.0, IMAGE_DPI / 72.0);
    cairo_save(cr);
    poppler_page_render(page, cr);
    cairo_restore(cr);
    g_object_unref(page);

    /* Then the image is painted on top of a white "page". Instead of
     * creating a second image, painting it white, then painting the
     * PDF image over it we can use the CAIRO_OPERATOR_DEST_OVER
     * operator to achieve the same effect with the one image. */
    cairo_set_operator(cr, CAIRO_OPERATOR_DEST_OVER);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);

    cairo_status_t status = cairo_status(cr);
    if (status)
    {
        printf("%s\n", cairo_status_to_string(status));
    }

    cairo_destroy(cr);
    return surface;
}
