/* 
 * PDF/A-2b starter:
 * Create PDF/A-2b conforming output with layers, transparency and
 * PDF/A attachments.
 *
 * Required software: PDFlib/PDFlib+PDI/PPS 9
 * Required data: font file, image file, ICC output intent profile
 *               (see www.pdflib.com for output intent ICC profiles)
 */

#include <iostream>
#include <string>

#include "pdflib.hpp"

using namespace std;
using namespace pdflib;

int
main(void)
{
    /* This is where the data files are. Adjust as necessary.*/
    const wstring searchpath = L"../data";

    const wstring imagefile = L"zebra.tif";
    const wstring attachments[] = { L"lionel.pdf"};
    const size_t attachment_count  =
            sizeof(attachments) / sizeof(attachments[0]);
    wostringstream optlist;
    PDFlib p;
    int font, image, gstate;
    int layer_english, layer_german, layer_french, layer_image;
    int textflow;
    double width, height;
    size_t i;

    try {
        //  This means we must check return values of load_font() etc.
        p.set_option(L"errorpolicy=return");

        // Set the search path for fonts and PDF files
        optlist.str(L"");
        optlist << L"searchpath={{" << searchpath << L"}}";
        p.set_option(optlist.str());


        /* Initially display the layer panel and show the full page */
        if (p.begin_document(L"starter_pdfa2b.pdf",
                L"openmode=layers viewerpreferences={fitwindow=true} "
                L"pdfa=PDF/A-2b") == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }

        p.set_info(L"Creator", L"PDFlib starter sample");
        p.set_info(L"Title", L"starter_pdfa2b");

        if (p.load_iccprofile(L"sRGB", L"usage=outputintent") == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            wcerr << L"See www.pdflib.com for output intent ICC profiles." << endl;
            return 2;
        }

        /* Define the layers, with only English and image layers switched on. */
        layer_english = p.define_layer(L"English text", L"");
        layer_german  = p.define_layer(L"German text", L"defaultstate=false");
        layer_french  = p.define_layer(L"French text", L"defaultstate=false");
        layer_image   = p.define_layer(L"Images", L"");

        /* Define a radio button relationship for the language layers, so only
         * one language can be switched on at a time.
         */
        optlist.str(L"");
        optlist << L"group={" << layer_english << L" " << layer_german
		<< L" " << layer_french << L"}";
        p.set_layer_dependency(L"Radiobtn", optlist.str());


        p.begin_page_ext(0,0, L"width=a4.width height=a4.height");

        /* Font embedding is required for PDF/A */
        font = p.load_font(L"NotoSerif-Regular", L"winansi", L"embedding");

        if (font == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }

        optlist.str(L"");
        optlist << L"font=" << font << " fontsize=24";

        p.begin_layer(layer_english);
        textflow = p.create_textflow(
                L"PDF/A-2b starter sample with layers, transparency "
                L"and attachments", optlist.str());
        p.fit_textflow(textflow, 50, 650, 550, 700, L"");
        p.delete_textflow(textflow);

        p.begin_layer(layer_german);
        textflow = p.create_textflow(
                L"PDF/A-2b Starter-Beispiel mit Ebenen, Transparenz "
                L"und Anlagen", optlist.str());
        p.fit_textflow(textflow, 50, 650, 550, 700, L"");
        p.delete_textflow(textflow);

        p.begin_layer(layer_french);
        textflow = p.create_textflow(
                L"PDF/A-2b starter exemple avec des calques, "
                L"de la transparence et des annexes", optlist.str());
        p.fit_textflow(textflow, 50, 650, 550, 700, L"");
        p.delete_textflow(textflow);

        p.begin_layer(layer_image);

        p.setfont(font, 48);

        image = p.load_image(L"auto", imagefile, L"");

        if (image == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }

        width = p.info_image(image, L"width", L"");
        height = p.info_image(image, L"height", L"");

        /* Place the image on the page and close it */
        p.fit_image(image, 0.0, 0.0, L"");
        p.close_image(image);

        /* Set transparency in the graphics state */
        gstate = p.create_gstate(L"opacityfill=0.5");
        p.set_gstate(gstate);

        /* Place a transparent diagonal stamp across the image area, in
         * different colors
         */
        optlist.str(L"");
        optlist << L"boxsize={" << width << L" " << height << L"} stamp=ll2ur";

        p.begin_layer(layer_english);
        p.setcolor(L"fill", L"Lab", 100, 28, 75, 0);
        p.fit_textline(L"Transparent text", 0, 0, optlist.str());

        p.begin_layer(layer_german);
        p.setcolor(L"fill", L"Lab", 33.725, 5, -52, 0);
        p.fit_textline(L"Transparenter Text", 0, 0, optlist.str());

        p.begin_layer(layer_french);
        p.setcolor(L"fill", L"Lab", 0, 0, 0, 0);
        p.fit_textline(L"Texte transparent", 0, 0, optlist.str());

        /* Close all layers */
        p.end_layer();

        p.end_page_ext(L"");

        /* Construct option list with attachment handles. The attachments must
         * be PDF/A-1 or PDF/A-2 files.
         */
        optlist.str(L"");
        optlist << L"attachments={";
        for (i = 0; i < attachment_count; i += 1) {
            const int attachment_handle =
                    p.load_asset(L"Attachment", attachments[i],
                                L"description={This is a PDF/A attachment}");

            if (attachment_handle == -1) {
                wcerr << L"Error loading attachment: " << p.get_errmsg() << endl;
                return 2;
            }

            optlist << " " << attachment_handle;
        }
        optlist << "}";

        p.end_document(optlist.str());
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
