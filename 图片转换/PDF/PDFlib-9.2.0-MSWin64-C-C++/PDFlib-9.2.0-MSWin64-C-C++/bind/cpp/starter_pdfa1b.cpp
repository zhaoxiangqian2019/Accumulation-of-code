/* 
 * PDF/A starter:
 * Create PDF/A-1b conforming output
 *
 * Required software: PDFlib/PDFlib+PDI/PPS 9
 * Required data: font file, image file
 */

#include <iostream>

#include "pdflib.hpp"

using namespace std;
using namespace pdflib;

int
main(void)
{
    try {
        /* This is where the data files are. Adjust as necessary. */
        const wstring searchpath = L"../data";

        PDFlib p;
        const wstring imagefile = L"nesrin.jpg";

        int font;
        int image;

        wostringstream optlist;

        //  This means we must check return values of load_font() etc.
        p.set_option(L"errorpolicy=return");

        // Set the search path for fonts and PDF files
        optlist.str(L"");
        optlist << L"searchpath={{" << searchpath << L"}}";
        p.set_option(optlist.str());


        if (p.begin_document(L"starter_pdfa1b.pdf",
                                        L"pdfa=PDF/A-1b:2005") == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }

        /*
         * We use sRGB as output intent since it allows the color
         * spaces CIELab, ICC-based, grayscale, and RGB.
         *
         * If you need CMYK color you must use a CMYK output profile.
         */

        if (p.load_iccprofile(L"sRGB", L"usage=outputintent") == -1) {
                wcerr << L"Error: " << p.get_errmsg() << endl;
                wcerr << L"See www.pdflib.com for output intent ICC profiles." << endl;
                return 2;
        }

        p.set_info(L"Creator", L"PDFlib starter sample");
        p.set_info(L"Title", L"starter_pdfa1b");

        p.begin_page_ext(0,0, L"width=a4.width height=a4.height");

        /* Font embedding is required for PDF/A */
        font = p.load_font(L"NotoSerif-Regular", L"winansi", L"embedding");
        if (font == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }
        p.setfont(font, 24);

        p.fit_textline(L"PDF/A-1b:2005 starter", 50, 700, L"");

        /* We can use an RGB image since we already supplied an
         * output intent profile.
         */
        image = p.load_image(L"auto", imagefile, L"");

        if (image == -1){
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }

        /* Place the image at the bottom of the page */
        p.fit_image(image, 0.0, 0.0, L"scale=0.5");

        p.end_page_ext(L"");
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
