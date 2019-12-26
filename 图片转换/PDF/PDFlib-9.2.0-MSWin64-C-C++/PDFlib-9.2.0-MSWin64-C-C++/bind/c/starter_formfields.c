/* 
 *
 * formfields starter:
 * create a linearized PDF (for fast delivery over the Web, also known
 * as "fast Web view") which is encrypted and contains some form fields.
 * A few lines of JavaScript are inserted as "page open" action to
 * automatically populate the date field with the current date.
 *
 * Required software: PDFlib/PDFlib+PDI/PPS 9
 * Required data: font file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pdflib.h"

int
main(void)
{
    /* This is where the data files are. Adjust as necessary. */
    const char* searchpath = "../data";

    PDF * p;
    char optlist[1024];
    int font, action;
    double llx=150, lly=550, urx=350, ury=575;

    /* JavaScript for automatically filling the date into a form field */
    const char * js =
        "var d = util.printd(\"mm/dd/yyyy\", new Date());"
        "var date = this.getField(\"date\");"
        "date.value = d;";

    /* create a new PDFlib object */
    if ((p = PDF_new()) == (PDF *) 0) {
        printf("Couldn't create PDFlib object (out of memory)!\n");
        return(2);
    }

    PDF_TRY(p) {
        /* This means we must check return values of load_font() etc. */
        sprintf(optlist, "errorpolicy=return SearchPath={{%s}}", searchpath);
        PDF_set_option(p, optlist);

        PDF_set_option(p, "stringformat=utf8");

        /* Prevent changes with a master password */
        sprintf(optlist,
                "linearize masterpassword=pdflib permissions={nomodify}");

        if (PDF_begin_document(p, "starter_formfields.pdf", 0, optlist) == -1) {
            printf("Error: %s\n", PDF_get_errmsg(p));
            PDF_delete(p);
            return(2);
        }

        PDF_set_info(p, "Creator", "PDFlib starter sample");
        PDF_set_info(p, "Title", "starter_formfields");

        sprintf(optlist, "script[%d]={%s}", (int) strlen(js), js);
        action = PDF_create_action(p, "JavaScript", optlist);

        sprintf(optlist, "width=a4.width height=a4.height action={open=%d}", action);
        PDF_begin_page_ext(p, 0, 0, optlist);

        font = PDF_load_font(p, "NotoSerif-Regular", 0, "winansi", "simplefont");

        if (font == -1) {
            printf("Error: %s\n", PDF_get_errmsg(p));
            PDF_delete(p);
            return(2);
        }

        PDF_setfont(p, font, 24);

        PDF_fit_textline(p, "Date: ", 0, 125, lly+5, "position={right bottom}");

        /* The tooltip will be used as rollover text for the field */
        sprintf(optlist, "tooltip={Date (will be filled automatically)} "
            "bordercolor={gray 0} font=%d", font);
        PDF_create_field(p, llx, lly, urx, ury, "date", 0, "textfield",optlist);

        lly-=100; ury-=100;
        PDF_fit_textline(p, "Name: ", 0, 125, lly+5, "position={right bottom}");

        sprintf(optlist, "tooltip={Enter your name here} "
            "bordercolor={gray 0} font=%d", font);
        PDF_create_field(p, llx, lly, urx, ury, "name", 0, "textfield",optlist);

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
