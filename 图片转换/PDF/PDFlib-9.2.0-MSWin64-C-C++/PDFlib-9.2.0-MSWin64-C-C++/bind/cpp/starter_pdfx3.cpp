/* 
 * PDF/X-3 starter:
 * Create PDF/X-3 conforming output
 *
 * Required software: PDFlib/PDFlib+PDI/PPS 9
 * Required data: font file, image file, ICC profile
 *                (see www.pdflib.com for output intent ICC profiles)
 */


#include <iostream>
#include <sstream>

#include "pdflib.hpp"

using namespace std;
using namespace pdflib;

int
main(void)
{
    try {
        /* This is where the data files are. Adjust as necessary.*/
        const wstring searchpath = L"../data";

        PDFlib p;
        const wstring imagefile = L"nesrin.jpg";
        int font, image, spot, icc;
        wostringstream optlist;

        //  This means we must check return values of load_font() etc.
        p.set_option(L"errorpolicy=return");

        // Set the search path for fonts and PDF files
        optlist.str(L"");
        optlist << L"searchpath={{" << searchpath << L"}}";
        p.set_option(optlist.str());


        if (p.begin_document(L"starter_pdfx3.pdf", L"pdfx=PDF/X-3:2003")
                                                                    == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }

        p.set_info(L"Creator", L"PDFlib starter sample");
        p.set_info(L"Title", L"starter_pdfx3");

        /*
         * You can use one of the Standard output intents (e.g. for SWOP
         * printing) which do not require an ICC profile:

        p.load_iccprofile(L"CGATS TR 001", L"usage=outputintent");

         * However, if you use ICC or Lab color you must load an ICC
         * profile as output intent:
         */
        if (p.load_iccprofile(L"ISOcoated_v2_eci.icc", L"usage=outputintent") == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            wcerr << L"See www.pdflib.com for output intent ICC profiles." <<endl;
            return 2;
        }

        p.begin_page_ext(0,0, L"width=a4.width height=a4.height");

        /* Font embedding is required for PDF/X */
        font = p.load_font(L"NotoSerif-Regular", L"winansi", L"embedding");
        if (font == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }
        p.setfont(font, 24);

        spot = p.makespotcolor(L"PANTONE 123 C");
        p.setcolor(L"fill", L"spot", spot, 1.0, 0.0, 0.0);
        p.fit_textline(L"PDF/X-3:2003 starter", 50, 700, L"");

        /* The RGB image below needs an ICC profile; we use sRGB. */
        icc = p.load_iccprofile(L"sRGB", L"");
        if (icc == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }
        optlist.str(L"");
        optlist << L"iccprofile=" << icc;
        image = p.load_image(L"auto", imagefile, optlist.str());

        if (image == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }

        p.fit_image(image, 0.0, 0.0, L"scale=0.5");
        p.end_page_ext(L"");
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
