/* 
 * PDFlib+PDI client: invoice generation demo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "pdflib.h"

const double x_table = 55;
const double tablewidth = 475;

const double y_address = 682;
const double x_salesrep = 455;
const double y_invoice = 542;
const double imagesize = 90;

const double fontsize = 11;
const double fontsizesmall = 9;

const char  *fontname= "NotoSerif-Regular";

char        basefontoptions[256];

/* -----------------------------------
 * Place company stationery as background
 * -----------------------------------
 */
static void
create_stationery(PDF *p)
{
    const char *sender =
        "Kraxi Systems, Inc. &#x2022; 17, Aviation Road &#x2022; Paperfield";
    const char *stationeryfontname= "NotoSerif-Regular";

    const char *stationeryfilename = "kraxi_logo.pdf";

    const double y_company_logo = 748;

    const char *senderfull =
        "17, Aviation Road\n"
        "Paperfield<nextline leading=50%><nextparagraph leading=120%>"
        "Phone 7079-4301\n"
        "Fax 7079-4302<nextline leading=50%><nextparagraph leading=120%>"
        "info@kraxi.com\n"
        "www.kraxi.com\n";

    int         page, stationery;
    char        optlist[256];
    int         tf;

    stationery = PDF_open_pdi_document(p, stationeryfilename, 0, "");
    page = PDF_open_pdi_page(p, stationery, 1, "");

    PDF_fit_pdi_page(p, page, 0, y_company_logo,
            "boxsize={595 85} position={65 center}");
    PDF_close_pdi_page(p, page);
    PDF_close_pdi_document(p, stationery);

    sprintf(optlist, "%s fontsize=%f fontname=%s charref=true",
            basefontoptions, fontsizesmall, stationeryfontname);
    PDF_fit_textline(p, sender, 0, x_table, y_address + fontsize,
            optlist);

    /* -----------------------------------
     * Print full company contact details
     * -----------------------------------
     */
    sprintf(optlist,
            "%s fontname=%s leading=125%% fillcolor={cmyk 0.64 0.55 0.52 0.27}",
            basefontoptions, stationeryfontname);
    tf = PDF_create_textflow(p, senderfull, 0, optlist);
    PDF_fit_textflow(p, tf, x_salesrep, y_address,
            x_salesrep+imagesize, y_address + 150, "verticalalign=bottom");
    PDF_delete_textflow(p, tf);
}

/* -----------------------------------
 * Place address and header text
 * -----------------------------------
 */
static void
create_header(PDF *p)
{
    const char *salesrepfilename = "sales_rep4.jpg";
    const char *salesrepname = "Lucy Irwin";
    const char *salesrepcaption = "Local sales rep:";
    const char *invoiceheader = "INVOICE 2012-03";

    const char *months[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    const char *address =
        "John Q. Doe\n"
        "255 Customer Lane\n"
        "Suite B\n"
        "12345 User Town\n"
        "Everland";

    char        optlist[256];
    char        buf[256];
    time_t      timer;
    struct tm   ltime;
    int         salesrepimage;
    int         tf;

    /* -----------------------------------
     * Print address
     * -----------------------------------
     */
    sprintf(optlist, "%s leading=120%%", basefontoptions);

    tf = PDF_create_textflow(p, address, 0, optlist);
    PDF_fit_textflow(p, tf,
            x_table, y_address, x_table+tablewidth/2, y_address-100, "");
    PDF_delete_textflow(p, tf);

    /* -----------------------------------
     * Place name and image of local sales rep
     * -----------------------------------
     */
    sprintf(optlist, "%s fontsize=%f", basefontoptions, fontsizesmall);
    PDF_fit_textline(p, salesrepcaption, 0, x_salesrep, y_address-fontsizesmall,
            optlist);
    PDF_fit_textline(p, salesrepname, 0, x_salesrep, y_address-2*fontsizesmall,
            optlist);

    salesrepimage = PDF_load_image(p, "auto", salesrepfilename, 0, "");

    sprintf(optlist, "boxsize={%f %f} fitmethod=meet", imagesize, imagesize);
    PDF_fit_image(p, salesrepimage,
            x_salesrep, y_address-3*fontsizesmall-imagesize, optlist);
    PDF_close_image(p, salesrepimage);

    /* -----------------------------------
     * Print the header and date
     * -----------------------------------
     */

    /* Add a bookmark with the header text */
    PDF_create_bookmark(p, invoiceheader, 0, "");

    sprintf(optlist, "%s", basefontoptions);
    PDF_fit_textline(p, invoiceheader, 0, x_table, y_invoice, optlist);

    time(&timer);
    ltime = *localtime(&timer);
    sprintf(buf, "%s %d, %d",
                months[ltime.tm_mon], ltime.tm_mday, ltime.tm_year + 1900);

    sprintf(optlist, "position {100 0} %s", basefontoptions);
    PDF_fit_textline(p, buf, 0, x_table+tablewidth, y_invoice, optlist);
}


int
main(void)
{
    /* This is where font/image/PDF input files live. Adjust as necessary. */
    const char* searchpath = "../data";

    const char	*closingtext =
        "Terms of payment: <fillcolor={rgb 1 0 0}>30 days net. "
        "<fillcolor={gray 0}>90 days warranty starting at the day of sale. "
        "This warranty covers defects in workmanship only. "
        "Kraxi Systems, Inc. will, at its option, repair or replace the "
        "product under the warranty. This warranty is not transferable. "
        "No returns or exchanges will be accepted for wet products.";

    typedef struct { const char *name; double price; int quantity; }
        articledata;

    const articledata data[] = {
        { "Super Kite",		20,	2},
        { "Turbo Flyer",	40,	5},
        { "Giga Trash",		180,	1},
        { "Bare Bone Kit",	50,	3},
        { "Nitty Gritty",	20,    10},
        { "Pretty Dark Flyer",	75,	1},
        { "Free Gift",		0,	1},
    };
#define ARTICLECOUNT (sizeof(data)/sizeof(data[0]))

    static const char *headers[] = {
        "ITEM", "DESCRIPTION", "QUANTITY", "PRICE", "AMOUNT"
    };
#define COLUMNCOUNT (sizeof(headers)/sizeof(headers[0]))

    static const char *alignments[] = {
        "right", "left", "right", "right", "right"
    };

    PDF         *p;
    int         i, pagecount=0;
    int         row, col, tbl;
    const char *result;
    double      total;
    char        buf[256];
    int         tf;

    /* create a new PDFlib object */
    if ((p = PDF_new()) == (PDF *) 0)
    {
        printf("Couldn't create PDFlib object (out of memory)!\n");
        return(2);
    }

    PDF_TRY(p) {
    char optlist[256];

        sprintf(optlist, "SearchPath={{%s}}", searchpath);
    PDF_set_option(p, optlist);

    /* This line is required to avoid problems on Japanese systems */
    PDF_set_option(p, "hypertextencoding=host");

    /* This mean we don't have to check error return values, but will
     * get an exception in case of runtime problems.
     */
    PDF_set_option(p, "errorpolicy=exception");

        PDF_begin_document(p, "invoice.pdf", 0, "");

    PDF_set_info(p, "Creator", "invoice");
    PDF_set_info(p, "Author", "Thomas Merz");
    PDF_set_info(p, "Title", "PDFlib invoice generation demo");

        sprintf(basefontoptions,
            "fontname=%s fontsize=%f embedding "
            "textformat=utf8 "
            "encoding=unicode",
            fontname, fontsize);

        /* -----------------------------------
         * Create and place table with article list
         * -----------------------------------
         */
        /* ---------- Header row */
        row = 1;
        tbl = -1;

        for (col=1; col <= (int) COLUMNCOUNT; col++)
        {
            sprintf(optlist, "fittextline={position={%s center} %s} margin=2",
                alignments[col-1], basefontoptions);
            tbl = PDF_add_table_cell(p, tbl, col, row, headers[col-1], 0,
            optlist);
        }
        row++;

        /* ---------- Data rows: one for each article */
        total = 0;

        for (i = 0; i < (int) ARTICLECOUNT; i++) {
            double sum = data[i].price * data[i].quantity;
            col = 1;

            /* column 1: ITEM */
            sprintf(buf, "%d", i+1);
            sprintf(optlist,
                "fittextline={position={%s center} %s} margin=2",
                alignments[col-1], basefontoptions);
            tbl = PDF_add_table_cell(p, tbl, col++, row, buf, 0, optlist);

            /* column 2: DESCRIPTION */
            sprintf(optlist,
                "fittextline={position={%s center} %s} colwidth=50%% margin=2",
                alignments[col-1], basefontoptions);
            tbl = PDF_add_table_cell(p, tbl, col++, row, data[i].name, 0,
                    optlist);

            /* column 3: QUANTITY */
            sprintf(buf, "%d", data[i].quantity);
            sprintf(optlist,
                "fittextline={position={%s center} %s} margin=2",
                alignments[col-1], basefontoptions);
            tbl = PDF_add_table_cell(p, tbl, col++, row, buf, 0, optlist);

            /* column 4: PRICE */
            sprintf(buf, "%.2f", data[i].price);
            sprintf(optlist,
                "fittextline={position={%s center} %s} margin=2",
                alignments[col-1], basefontoptions);
            tbl = PDF_add_table_cell(p, tbl, col++, row, buf, 0, optlist);

            /* column 5: AMOUNT */
            sprintf(buf, "%.2f", sum);
            sprintf(optlist,
                "fittextline={position={%s center} %s} margin=2",
                alignments[col-1], basefontoptions);
            tbl = PDF_add_table_cell(p, tbl, col++, row, buf, 0, optlist);

            total += sum;
            row++;
        }

        /* ---------- Print total in the rightmost column */
        sprintf(buf, "%.2f", total);
        sprintf(optlist,
            "fittextline={position={%s center} %s} margin=2",
            alignments[COLUMNCOUNT-1], basefontoptions);
        tbl = PDF_add_table_cell(p, tbl, COLUMNCOUNT, row++, buf, 0, optlist);


        /* ---------- Footer row with terms of payment */
        sprintf(optlist, "%s alignment=justify leading=120%%", basefontoptions);
        tf = PDF_create_textflow(p, closingtext, 0, optlist);

        sprintf(optlist,
                "rowheight=1 margin=2 margintop=%f textflow=%d colspan=%d ",
                2*fontsize, tf, (int) COLUMNCOUNT);
        tbl = PDF_add_table_cell(p, tbl, 1, row++, "", 0, optlist);


        /* ---------- Place the table instance(s), creating pages as required */
        do {
            double top;

            PDF_begin_page_ext(p, 0, 0, "width=a4.width height=a4.height");

            if (++pagecount == 1)
            {
                create_stationery(p);
                create_header(p);
                top = y_invoice - 3*fontsize;
            }
            else
            {
                top = 50;
            }

            /* Place the table on the page; Shade every other row. */
            sprintf(optlist,
                    "header=1 fill={{area=rowodd fillcolor={gray 0.9}}} ");

            result = PDF_fit_table(p, tbl,
                    x_table, top, x_table+tablewidth, 20, optlist);

            if (!strcmp(result, "_error"))
            {
                printf("Couldn't place table: %s\n", PDF_get_errmsg(p));
                PDF_delete(p);
                return(2);
            }

            PDF_end_page_ext(p, "");
        } while (!strcmp(result, "_boxfull"));

        PDF_delete_table(p, tbl, "");

        PDF_end_document(p, "");
    }

    PDF_CATCH(p) {
        printf("PDFlib exception occurred in invoice sample:\n");
        printf("[%d] %s: %s\n",
        PDF_get_errnum(p), PDF_get_apiname(p), PDF_get_errmsg(p));
        PDF_delete(p);
        return(2);
    }

    PDF_delete(p);

    return 0;
}
