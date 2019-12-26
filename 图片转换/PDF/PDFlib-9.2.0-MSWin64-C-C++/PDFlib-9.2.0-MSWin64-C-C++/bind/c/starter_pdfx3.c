/* 
 * PDF/X-3 starter:
 * Create PDF/X-3 conforming output
 *
 * Required software: PDFlib/PDFlib+PDI/PPS 9
 * Required data: font file, image file, ICC profile
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
    const char * imagefile = "nesrin.jpg";

    PDF *p;
    char optlist[1024];

    int font, image, spot, icc;

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

        if (PDF_begin_document(p, "starter_pdfx3.pdf", 0, "pdfx=PDF/X-3:2003")
                == -1) {
            printf("Error: %s\n", PDF_get_errmsg(p));
            PDF_delete(p);
            return(2);
        }

        PDF_set_info(p, "Creator", "PDFlib starter sample");
        PDF_set_info(p, "Title", "starter_pdfx3");


        if (PDF_load_iccprofile(p, "ISOcoated_v2_eci.icc", 0,
                "usage=outputintent") == -1)
        {
            printf("Error: %s\n", PDF_get_errmsg(p));
            printf("See www.pdflib.com for output intent ICC profiles.\n");
            PDF_delete(p);
            return(2);
        }

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

        spot = PDF_makespotcolor(p, "PANTONE 123 C", 0);
        PDF_setcolor(p, "fill", "spot", spot, 1.0, 0.0, 0.0);
        PDF_fit_textline(p, "PDF/X-3:2003 starter", 0, 50, 700, "");

        /* The RGB image below needs an ICC profile; we use sRGB. */
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

        PDF_fit_image(p, image, (float) 0.0, (float) 0.0, "scale=0.5");

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
