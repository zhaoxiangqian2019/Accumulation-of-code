/* 
 * Block starter:
 * Import a PDF page containing Blocks and fill text and image
 * Blocks with some data. For each recipient of the simulated
 * mailing a separate page with personalized information is
 * generated.
 * A real-world application would fill the Blocks with data from
 * some external data source. We simulate this with static data.
 *
 * Required software: PPS 9
 * Required data: input PDF, image
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "pdflib.h"


int
main(void)
{
    /* This is where the data files are. Adjust as necessary. */
    const char *searchpath = "../data";
    const char *outfile = "starter_block.pdf";
    const char *infile = "block_template.pdf";
    const char *imagefile = "new.jpg";

    PDF *p;
    int i, j, no_of_input_pages, pageno, *pagehandles, indoc, image;
    char optlist[1024];

    /* Names of the recipient-specific Blocks contained on the imported page */
    const char *addressblocks[] = {
        "name", "street", "city"
    };
    const int no_of_address_blocks =
            sizeof(addressblocks) / sizeof(addressblocks[0]);

    /* Personalization data for the recipients */
    const char *recipients[][3] = {
        {"Mr Maurizio Moroni", "Strada Provinciale 124", "Reggio Emilia"},
        {"Ms Dominique Perrier", "25, rue Lauriston", "Paris"},
        {"Mr Liu Wong", "55 Grizzly Peak Rd.", "Butte"}
    };
    const int no_of_recipients = sizeof(recipients) / sizeof(recipients[0]);

    typedef struct {
        const char *blockname;      /* name of the Block */
        const char *contents;       /* Text for filling the Block */
    } blockdata_s;

    /* Static text simulates database-driven main contents */
    const blockdata_s blockdata[] = {
        { "intro", "Dear Paper Planes Fan," },
        { "announcement",
        "Our <fillcolor=red>BEST PRICE OFFER<fillcolor=black> includes today:"
        "\n\n"
        "Long Distance Glider\nWith this paper rocket you can send all your "
        "messages even when sitting in a hall or in the cinema pretty near "
        "the back.\n\n"
        "Giant Wing\nAn unbelievable sailplane! It is amazingly robust and "
        "can even do aerobatics. But it is best suited to gliding.\n\n"
        "Cone Head Rocket\nThis paper arrow can be thrown with big swing. "
        "We launched it from the roof of a hotel. It stayed in the air a "
        "long time and covered a considerable distance.\n\n"
        "Super Dart\nThe super dart can fly giant loops with a radius of 4 "
        "or 5 meters and cover very long distances. Its heavy cone point is "
        "slightly bowed upwards to get the lift required for loops.\n\n"
        "Visit us on our Web site at www.kraxi.com!"
        },
        { "goodbye", "Yours sincerely,\nVictor Kraxi" }
    };

    const int no_of_text_blocks = sizeof(blockdata) / sizeof(blockdata[0]);

    /* create a new PDFlib object */
    if ((p = PDF_new()) == (PDF *) 0)
    {
        printf("Error: couldn't create PDFlib object (out of memory)!\n");
        return(2);
    }

    PDF_TRY(p)
    {
        sprintf(optlist, "SearchPath={{%s}}", searchpath);
        PDF_set_option(p, optlist);

        /* This means we must check return values of load_font() etc. */
        PDF_set_option(p, "errorpolicy=return");

        if (PDF_begin_document(p, outfile, 0,
                "destination={type=fitwindow} pagelayout=singlepage") == -1)
        {
            printf("Error: %s\n", PDF_get_errmsg(p));
            PDF_delete(p);
            return(2);
        }

        PDF_set_info(p, "Creator", "PDFlib starter sample");
        PDF_set_info(p, "Title", "starter_block");

        /* Open the Block template which contains PDFlib Blocks */
        indoc = PDF_open_pdi_document(p, infile, 0, "");
        if (indoc == -1)
        {
            printf("Error: %s\n", PDF_get_errmsg(p));
            PDF_delete(p);
            return(2);
        }

        no_of_input_pages = (int) PDF_pcos_get_number(p, indoc, "length:pages");

        /* Add 1 because we use the 1-based page number as array index */
        pagehandles = (int *) malloc((no_of_input_pages+1) * sizeof(int));
        if (pagehandles == NULL)
        {
            printf("Error: couldn't allocate page handle array!\n");
            return(3);
        }

        /* Prepare all pages of the input document. We assume a small
         * number of input pages and a large number of generated output
         * pages. Therefore it makes sense to keep the input pages
         * open instead of opening the pages again for each recipient.
         */
        for (pageno = 1; pageno <= no_of_input_pages; pageno++)
        {
            /* Open the next page and prepare it for cloning the page size */
            pagehandles[pageno] = PDF_open_pdi_page(p, indoc, pageno,
                                        "cloneboxes");

            if (pagehandles[pageno] == -1)
            {
                printf("Error: %s\n", PDF_get_errmsg(p));
                PDF_delete(p);
                return(2);
            }
        }

        image = PDF_load_image(p, "auto", imagefile, 0, "");

        if (image == -1)
        {
            printf("Error: %s\n", PDF_get_errmsg(p));
            return(3);
        }

        /* Duplicate input pages for each recipient and fill Blocks */
        for (i = 0; i < no_of_recipients; i++)
        {
            /* Loop over all pages of the input document */
            for (pageno = 1; pageno <= no_of_input_pages; pageno++)
            {
                const char *objtype;

                /* Start the next output page. The dummy size will be
                 * replaced with the cloned size of the input page.
                 */
                PDF_begin_page_ext(p, 10, 10, "");

                /* Place the imported page on the output page and clone all
                 * page boxes which are present in the input page; this will
                 * override the dummy size used in begin_page_ext().
                 */
                PDF_fit_pdi_page(p, pagehandles[pageno], 0, 0, "cloneboxes");

                /* Option list for text Blocks */
                strcpy(optlist, "encoding=winansi embedding");

                /* Loop over all recipient-specific Blocks. Fill each
                 * Block with the corresponding person's address data.
                 */
                for (j = 0; j < no_of_address_blocks; j++)
                {
                    /* Check whether the Block is present on the imported page;
                     * type "dictionary" means that the Block is present.
                     */
                    objtype = PDF_pcos_get_string(p, indoc,
                                "type:pages[%d]/blocks/%s",
                                pageno-1, addressblocks[j]);
                    if (!strcmp(objtype, "dict"))
                    {
                        if (PDF_fill_textblock(p, pagehandles[pageno],
                                addressblocks[j], recipients[i][j], 0,
                                optlist) == -1)
                            printf("Warning: %s\n", PDF_get_errmsg(p));
                    }
                }

                /* Loop over the remaining text Blocks. These are filled with
                 * the same data for each recipient.
                 */
                for (j = 0; j < no_of_text_blocks; j++)
                {
                    /* Check whether the Block is present on the page */
                    objtype = PDF_pcos_get_string(p, indoc,
                                "type:pages[%d]/blocks/%s",
                                pageno-1, blockdata[j].blockname);
                    if (!strcmp(objtype, "dict"))
                    {
                        /* Fill the dataset contents into the Block */
                        if (PDF_fill_textblock(p, pagehandles[pageno],
                                blockdata[j].blockname, blockdata[j].contents,
                                0, optlist) == -1)
                            printf("Warning: %s\n", PDF_get_errmsg(p));
                    }
                }

                /* Fill the icon Block if it is present on the imported page */
                objtype = PDF_pcos_get_string(p, indoc,
                            "type:pages[%d]/blocks/icon", pageno-1);
                if (!strcmp(objtype, "dict"))
                {
                    if (PDF_fill_imageblock(p, pagehandles[pageno],
                            "icon", image, "") == -1)
                        printf("Warning: %s\n", PDF_get_errmsg(p));
                }

                PDF_end_page_ext(p, "");
            }
        }

        /* Close all input pages */
        for (pageno = 1; pageno <= no_of_input_pages; pageno++)
        {
            PDF_close_pdi_page(p, pagehandles[pageno]);
        }

        free(pagehandles);

        PDF_close_pdi_document(p, indoc);
        PDF_close_image(p, image);

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
