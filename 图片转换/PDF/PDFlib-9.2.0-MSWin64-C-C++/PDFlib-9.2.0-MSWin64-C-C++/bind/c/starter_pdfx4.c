/* 
 * PDF/X-4 starter:
 * Create PDF/X-4 conforming output with layers and transparency
 *
 * A low-level layer is created for each of several languages, as well
 * as an image layer.
 *
 * The document contains transparent text which is allowed in
 * PDF/X-4, but not earlier PDF/X standards.
 *
 * Required software: PDFlib/PDFlib+PDI/PPS 9
 * Required data: font file, image file, ICC output intent profile
 *                (see www.pdflib.com for output intent ICC profiles)
 */

#include <stdio.h>
#include <stdlib.h>

#include "pdflib.h"


int
main(void)
{
    /* This is where the data files are. Adjust as necessary.*/
    const char * searchpath = "../data";
    const char * imagefile = "zebra.tif";

    PDF *p;
    char optlist[1024];

    int font, image, icc, gstate;
    int layer_english, layer_german, layer_french, layer_image;
    double width, height;

    /* create a new PDFlib object */
    if ((p = PDF_new()) == (PDF *) 0) {
        printf("Couldn't create PDFlib object (out of memory)!\n");
        return(2);
    }

    PDF_TRY(p) {
        /* This means we must check return values of load_font() etc. */
        PDF_set_option(p, "errorpolicy=return");

        sprintf(optlist, "SearchPath={{%s}}", searchpath);
        PDF_set_option(p, optlist);

        if (PDF_begin_document(p, "starter_pdfx4.pdf", 0, "pdfx=PDF/X-4")
                == -1) {
            printf("Error: %s\n", PDF_get_errmsg(p));
            PDF_delete(p);
            return(2);
        }

        PDF_set_info(p, "Creator", "PDFlib starter sample");
        PDF_set_info(p, "Title", "starter_pdfx4");

        if (PDF_load_iccprofile(p, "ISOcoated_v2_eci.icc", 0,
                "usage=outputintent") == -1)
        {
            printf("Error: %s\n", PDF_get_errmsg(p));
            printf("See www.pdflib.com for output intent ICC profiles.\n");
            PDF_delete(p);
            return(2);
        }

        /* Define the layers; "defaultstate" specifies whether or not
         * the layer is visible when the page is opened.
         */

        layer_english = PDF_define_layer(p, "English text", 0,
            "defaultstate=true");
        layer_german  = PDF_define_layer(p, "German text", 0,
            "defaultstate=false");
        layer_french  = PDF_define_layer(p, "French text", 0,
            "defaultstate=false");

    /* Define a radio button relationship for the language layers  */
        sprintf(optlist,
            "group={%d %d %d}",
            layer_english, layer_german, layer_french);
        PDF_set_layer_dependency(p, "Radiobtn", optlist);

        layer_image   = PDF_define_layer(p, "Images", 0,
            "defaultstate=true");

        PDF_begin_page_ext(p, 0,0, "width=a4.width height=a4.height");

        /* Font embedding is required for PDF/X */
        font = PDF_load_font(p, "NotoSerif-Regular", 0,
                "winansi", "embedding");

        if (font == -1) {
            printf("Error: %s\n", PDF_get_errmsg(p));
            PDF_delete(p);
            return(2);
        }

        PDF_setfont(p, font, 24);

        PDF_begin_layer(p, layer_english);

        PDF_fit_textline(p, "PDF/X-4 starter sample with layers",
            0, 50, 700, "");

        PDF_begin_layer(p, layer_german);
        PDF_fit_textline(p, "PDF/X-4 Starter-Beispiel mit Ebenen",
            0, 50, 700, "");

        PDF_begin_layer(p, layer_french);
        PDF_fit_textline(p, "PDF/X-4 Starter exemple avec des calques",
            0, 50, 700, "");

        PDF_begin_layer(p, layer_image);

        PDF_setfont(p, font, 48);

        /* The RGB image needs an ICC profile; we use sRGB. */
        icc = PDF_load_iccprofile(p, "sRGB", 0, "");
        if (icc == -1) {
            printf("Error: %s\n", PDF_get_errmsg(p));
            PDF_delete(p);
            return(2);
        }
        sprintf(optlist, "iccprofile=%d", icc);
        image = PDF_load_image(p, "auto", imagefile, 0, optlist);

        if (image == -1) {
            printf("Error: %s\n", PDF_get_errmsg(p));
            PDF_delete(p);
            return(2);
        }

        /* Place a diagonal stamp across the image area */
        width = PDF_info_image(p, image, "width", "");
        height = PDF_info_image(p, image, "height", "");

        sprintf(optlist, "boxsize={%f %f} stamp=ll2ur", width, height);
        PDF_fit_textline(p, "Zebra", 0, 0, 0, optlist);

        /* Set transparency in the graphics state */
        gstate = PDF_create_gstate(p, "opacityfill=0.5");
        PDF_set_gstate(p, gstate);

        /* Place the image on the page and close it */
        PDF_fit_image(p, image, (double) 0.0, (double) 0.0, "");
        PDF_close_image(p, image);

        /* Close all layers */
        PDF_end_layer(p);

        PDF_end_page_ext(p, "");

        PDF_end_document(p, "");
    }

    PDF_CATCH(p) {
        printf("PDFlib exception occurred:\n");
        printf("[%d] %s: %s\n",
            PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
        PDF_delete(p);
        return(2);
    }

    PDF_delete(p);

    return 0;
}
