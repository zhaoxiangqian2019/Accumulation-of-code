/* 
 * PDFlib client: block processing example in C
 */

#include <stdio.h>
#include <stdlib.h>

#include "pdflib.h"

int
main(void)
{
    PDF 	*p;
    int 	i, blockcontainer, page;

    /*
     * This is where font/image/PDF input files live. Adjust as necessary.
     * Note that this directory must also contain the font files.
     */

    const char* searchpath = "../data";

    const char 	*infile = "boilerplate.pdf";

    typedef struct { const char *name; const char *value; } blockdata;

    const blockdata data[] = {
    { "name",			"Victor Kraxi" },
    { "business.title",		"Chief Paper Officer" },
    { "business.address.line1",	"17, Aviation Road" },
    { "business.address.city",	"Paperfield" },
    { "business.telephone.voice","phone +1 234 567-89" },
    { "business.telephone.fax",	"fax +1 234 567-98" },
    { "business.email",		"victor@kraxi.com" },
    { "business.homepage",	"www.kraxi.com" },
    };

#define BLOCKCOUNT (sizeof(data)/sizeof(data[0]))

    /* create a new PDFlib object */
    if ((p = PDF_new()) == (PDF *) 0)
    {
        printf("Couldn't create PDFlib object (out of memory)!\n");
        return(2);
    }

    PDF_TRY(p) {
	char optlist[256];

	/* This means we must check return values of load_font() etc. */
	/* Set the search path for fonts and PDF files */
        sprintf(optlist, "errorpolicy=return SearchPath={{%s}}", searchpath);
	PDF_set_option(p, optlist);

	PDF_set_option(p, "stringformat=utf8");

	if (PDF_begin_document(p, "businesscard.pdf", 0, "") == -1) {
	    printf("Error: %s\n", PDF_get_errmsg(p));
	    return(2);
	}

	PDF_set_info(p, "Creator", "businesscard");
	PDF_set_info(p, "Author", "Thomas Merz");
	PDF_set_info(p, "Title", "PDFlib block processing sample");

	blockcontainer = PDF_open_pdi_document(p, infile, 0, "");
	if (blockcontainer == -1) {
	    printf("Error: %s\n", PDF_get_errmsg(p));
	    return(2);
        }

	page = PDF_open_pdi_page(p, blockcontainer, 1, "");
	if (page == -1) {
	    printf("Error: %s\n", PDF_get_errmsg(p));
	    return(2);
	}

	PDF_begin_page_ext(p, 20, 20, "");		/* dummy page size */

	/* This will adjust the page size to the block container's size. */
	PDF_fit_pdi_page(p, page, 0, 0, "adjustpage");

	/* Fill all text blocks with dynamic data */
	for (i = 0; i < (int) BLOCKCOUNT; i++) {
	    if (PDF_fill_textblock(p, page, data[i].name, data[i].value, 0,
		    "embedding encoding=unicode") == -1) {
		printf("Warning: %s\n", PDF_get_errmsg(p));
	    }
	}

	PDF_end_page_ext(p, "");
	PDF_close_pdi_page(p, page);

	PDF_end_document(p, "");
	PDF_close_pdi_document(p, blockcontainer);
    }

    PDF_CATCH(p) {
        printf("PDFlib exception occurred in businesscard sample:\n");
        printf("[%d] %s: %s\n",
	    PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
        PDF_delete(p);
        return(2);
    }

    PDF_delete(p);

    return 0;
}
