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

#include <iostream>
#include <vector>

#include "pdflib.hpp"

using namespace std;
using namespace pdflib;

int
main(void)
{
    /* This is where the data files are. Adjust as necessary. */
    const wstring searchpath = L"../data";
    const wstring outfile = L"starter_block.pdf";
    const wstring infile = L"block_template.pdf";
    const wstring imagefile = L"new.jpg";

    PDFlib p;
    int indoc, image;

    /* Names of the person-related blocks contained on the imported page */
    const wstring addressblocks[] = {
        L"name", L"street", L"city"
    };
    const int no_of_address_blocks =
                sizeof(addressblocks) / sizeof(addressblocks[0]);

    /* Personalization data for the recipients */
    const wstring recipients[][3] = {
        {L"Mr Maurizio Moroni", L"Strada Provinciale 124", L"Reggio Emilia"},
        {L"Ms Dominique Perrier", L"25, rue Lauriston", L"Paris"},
        {L"Mr Liu Wong", L"55 Grizzly Peak Rd.", L"Butte"}
    };
    const int no_of_recipients = sizeof(recipients) / sizeof(recipients[0]);

    typedef struct {
        wstring blockname;      /* name of the Block */
        wstring contents;       /* Text for filling the Block */
    } blockdata_s;

    /* Static text simulates database-driven main contents */
    const blockdata_s blockdata[] = {
        { L"intro", L"Dear Paper Planes Fan," },
        { L"announcement",
            L"Our <fillcolor=red>BEST PRICE OFFER<fillcolor=black> includes today:"
            L"\n\n"
            L"Long Distance Glider\nWith this paper rocket you can send all your "
            L"messages even when sitting in a hall or in the cinema pretty near "
            L"the back.\n\n"
            L"Giant Wing\nAn unbelievable sailplane! It is amazingly robust and "
            L"can even do aerobatics. But it is best suited to gliding.\n\n"
            L"Cone Head Rocket\nThis paper arrow can be thrown with big swing. "
            L"We launched it from the roof of a hotel. It stayed in the air a "
            L"long time and covered a considerable distance.\n\n"
            L"Super Dart\nThe super dart can fly giant loops with a radius of 4 "
            L"or 5 meters and cover very long distances. Its heavy cone point is "
            L"slightly bowed upwards to get the lift required for loops.\n\n"
            L"Visit us on our Web site at www.kraxi.com!"},
        { L"goodbye", L"Yours sincerely,\nVictor Kraxi" }
    };
    const int no_of_text_blocks = sizeof(blockdata) / sizeof(blockdata[0]);

    wostringstream buf;

    try {

        //  This means we must check return values of load_font() etc.
        p.set_option(L"errorpolicy=return");

        // Set the search path for fonts and PDF files
        buf.str(L"");
        buf << L"searchpath={{" << searchpath << L"}}";
        p.set_option(buf.str());

        if (p.begin_document(outfile,
                L"destination={type=fitwindow} pagelayout=singlepage") == -1)
        {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }

        p.set_info(L"Creator", L"PDFlib starter sample");
        p.set_info(L"Title", L"starter_block");

        /* Open the Block template which contains PDFlib Blocks */
        indoc = p.open_pdi_document(infile, L"");
        if (indoc == -1)
        {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }

        int no_of_input_pages =
                (int) p.pcos_get_number(indoc, L"length:pages");

        /* Add 1 because we use the 1-based page number as array index */
        vector<int> pagehandles(no_of_input_pages + 1);

        /* Prepare all pages of the input document. We assume a small
         * number of input pages and a large number of generated output
         * pages. Therefore it makes sense to keep the input pages
         * open instead of opening the pages again for each recipient.
         */
        int pageno;
        for (pageno = 1; pageno <= no_of_input_pages; pageno++)
        {
            /* Open the next page and prepare it for cloning the page size */
            pagehandles[pageno] = p.open_pdi_page(indoc, pageno,
                                        L"cloneboxes");

            if (pagehandles[pageno] == -1)
            {
                wcerr << L"Error: " << p.get_errmsg() << endl;
                return 2;
            }
        }

        image = p.load_image(L"auto", imagefile, L"");

        if (image == -1)
        {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 3;
        }

        /* Duplicate input pages for each recipient and fill Blocks */
        for (int i = 0; i < no_of_recipients; i++)
        {
            /* Loop over all pages of the input document */
            for (pageno = 1; pageno <= no_of_input_pages; pageno++)
            {
                wstring objtype;

                /* Start the next output page. The dummy size will be
                 * replaced with the cloned size of the input page.
                 */
                p.begin_page_ext(10, 10, L"");

                /* Place the imported page on the output page and clone all
                 * page boxes which are present in the input page; this will
                 * override the dummy size used in begin_page_ext().
                 */
                p.fit_pdi_page(pagehandles[pageno], 0, 0, L"cloneboxes");

                /* Option list for text Blocks */
                wstring optlist = L"encoding=winansi embedding";

                /* Loop over all recipient-specific Blocks. Fill each
                 * Block with the corresponding person's address data.
                 */
                int j;
                wostringstream pcos_optlist;
                for (j = 0; j < no_of_address_blocks; j++)
                {
                    /* Check whether the Block is present on the imported page;
                     * type "dictionary" means that the Block is present.
                     */
                    pcos_optlist.str(L"");
                    pcos_optlist << L"type:pages[" << (pageno - 1)
                            << L"]/blocks/" << addressblocks[j];
                    objtype = p.pcos_get_string(indoc, pcos_optlist.str());
                    if (objtype == L"dict")
                    {
                        if (p.fill_textblock(pagehandles[pageno],
                                addressblocks[j], recipients[i][j],
                                optlist) == -1)
                            wcerr << L"Warning: " << p.get_errmsg() << endl;
                    }
                }

                /* Loop over the remaining text Blocks. These are filled with
                 * the same data for each recipient.
                 */
                for (j = 0; j < no_of_text_blocks; j++)
                {
                    /* Check whether the Block is present on the page */
                    pcos_optlist.str(L"");
                    pcos_optlist << L"type:pages[" << (pageno - 1)
                            << L"]/blocks/" << blockdata[j].blockname;
                    objtype = p.pcos_get_string(indoc, pcos_optlist.str());
                    if (objtype == L"dict")
                    {
                        /* Fill the dataset contents into the Block */
                        if (p.fill_textblock(pagehandles[pageno],
                                blockdata[j].blockname, blockdata[j].contents,
                                optlist) == -1)
                            wcerr << L"Warning: " << p.get_errmsg() << endl;
                    }
                }

                /* Fill the icon Block if it is present on the imported page */
                pcos_optlist.str(L"");
                pcos_optlist << L"type:pages[" << (pageno - 1)
                        << L"]/blocks/icon";
                objtype = p.pcos_get_string(indoc, pcos_optlist.str());
                if (objtype == L"dict")
                {
                    if (p.fill_imageblock(pagehandles[pageno],
                            L"icon", image, L"") == -1)
                        wcerr << L"Warning: " << p.get_errmsg() << endl;
                }

                p.end_page_ext(L"");
            }
        }

        /* Close all input pages */
        for (pageno = 1; pageno <= no_of_input_pages; pageno++)
        {
            p.close_pdi_page(pagehandles[pageno]);
        }

        p.close_pdi_document(indoc);
        p.close_image(image);

        p.end_document(L"");
    }
    catch (PDFlib::Exception &ex) {
        wcerr << L"PDFlib exception occurred:" << endl
              << L"[" << ex.get_errnum() << L"] " << ex.get_apiname()
              << L": " << ex.get_errmsg() << endl;
        return 99;
    }
    catch (exception &e) {
        cerr << "C++ exception occurred: " << e.what() << endl;
        return 99;
    }
    catch (...) {
        cerr << "Generic C++ exception occurred!" << endl;
        return 99;
    }

    return 0;
}
