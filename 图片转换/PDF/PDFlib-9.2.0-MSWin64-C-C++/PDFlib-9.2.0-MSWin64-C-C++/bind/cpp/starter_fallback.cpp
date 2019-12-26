/* 
 * Starter sample for fallback fonts
 *
 * Required software: PDFlib/PDFlib+PDI/PPS 9
 * Required data: suitable fonts, Japanese CMaps
 */

#include <iostream>
#include <string>

#include "pdflib.hpp"

using namespace std;
using namespace pdflib;

int
main(void)
{
    /* This is where the data files are. Adjust as necessary. */
    const wstring searchpath = L"../data";
    const wstring outfile = L"starter_fallback.pdf";

    wostringstream optlist;
    PDFlib p;
    int row, col, table, test;
    const double llx=30, lly=50, urx=800, ury=570;
    wstring result;

    const wstring header[] = {
        L"Use case",
        L"Option list for the 'fallbackfonts' option",
        L"Base font",
        L"With fallback font"
    };
    const int MAXCOL = sizeof(header) / sizeof(header[0]);

    typedef struct {
        const wstring usecase;
        const wstring fontname;
        const wstring encoding;
        const wstring fallbackoptions;
        const wstring text;
    } testcase;

    const testcase testcases[] = {
    { /* Add Euro glyph to an encoding which doesn't support it */
      L"Extend 8-bit encoding",
      L"Helvetica",
      L"iso8859-1",
      L"{fontname=Helvetica encoding=unicode forcechars=euro}",
      /* Reference Euro glyph by name (since it is missing from the encoding) */
       L"123&euro;"
    },
    {
      L"Use Euro glyph from another font",
      L"Courier",
      L"unicode",
      L"{fontname=Helvetica encoding=unicode forcechars=euro textrise=-5%}",
       L"123&euro;"
    },
    {
      L"Add enlarged pictogram",
      L"NotoSerif-Regular",
      L"unicode",
      /* U+261E = WHITE RIGHT POINTING INDEX */
      L"{fontname=ZapfDingbats encoding=unicode forcechars=U+261E fontsize=150% "
      L"textrise=-15%}",
       L"hand symbol: &#x261E;"
    },
    {
      L"Add enlarged symbol glyph",
      L"NotoSerif-Regular",
      L"unicode",
      L"{fontname=Symbol encoding=unicode forcechars=U+2663 fontsize=125%}",
       L"club symbol: &#x2663;"
    },
    { /* Hebrew characters missing in the font will be pulled from Hebrew */
      L"Add Hebrew characters to Latin font",
      L"NotoSerif-Regular",
      L"unicode",
      L"{fontname=NotoSerifHebrew-Regular encoding=unicode}",
       L"Hebrew: \u05D0"
    },
    { /* Font with end-user defined character (EUDC) */
      L"Gaiji with EUDC font",
      L"KozMinProVI-Regular",
      L"unicode",
      L"{fontname=EUDC encoding=unicode forcechars=U+E000 fontsize=140% "
      L"textrise=-20%}",
       L"Gaiji: &#xE000;"
    },
    { L"Replace Latin characters in CJK font",
      L"KozMinProVI-Regular",
      L"unicode",
      L"{fontname=Courier encoding=unicode forcechars={U+0020-U+007E}}",
       L"Latin and &#x65E5;&#x672C;&#x8A9E;"
    },
    };
    const int n_testcases = sizeof(testcases) / sizeof(testcases[0]);

    try {
        /* This means that formatting and other errors will raise an
         * exception. This simplifies our sample code, but is not
         * recommended for production code.
         */
        p.set_option(L"errorpolicy=exception");

        // Set the search path for fonts and PDF files
        optlist.str(L"");
        optlist << L"searchpath={{" << searchpath << L"}} charref=true glyphcheck=replace";
        p.set_option(optlist.str());


        /* Set an output path according to the name of the topic */
        if (p.begin_document(outfile, L"") == -1) {
            wcerr << L"Error: " << p.get_errmsg() << endl;
            return 2;
        }

        p.set_info(L"Creator", L"PDFlib starter sample");
        p.set_info(L"Title", L"starter_fallback");

        /* Start Page */
        p.begin_page_ext(0, 0, L"width=a4.height height=a4.width");

        table = -1;

        /* Table header */
        for (row=1, col=1; col <= MAXCOL; col++)
        {
            optlist.str(L"");
            optlist << L"fittextline={fontname=NotoSerif-Regular encoding=unicode "
                       L"fontsize=10} margin=4";
            table = p.add_table_cell(table, col, row, header[col-1],
                    optlist.str());
        }

        /* Create fallback samples, one use case per row */
        for (row=2, test=0; test < n_testcases; row++, test++)
        {
            col=1;

            /* Column 1: description of the use case */
            optlist.str(L"");
            optlist << L"fittextline={fontname=NotoSerif-Regular encoding=unicode "
                       L"fontsize=10} margin=4";
            table = p.add_table_cell(table, col++, row,
                testcases[test].usecase, optlist.str());

            /* Column 2: reproduce option list literally */
            optlist.str(L"");
            optlist << L"fittextline={fontname=NotoSerif-Regular encoding=unicode "
                       L"fontsize=10} margin=4";
            table = p.add_table_cell(table, col++, row,
                testcases[test].fallbackoptions, optlist.str());

            /* Column 3: text with base font */
            optlist.str(L"");
            optlist << L"fittextline={fontname=" << testcases[test].fontname
                << L" encoding=" << testcases[test].encoding
                << L" fontsize=10 replacementchar=? } margin=4";
            table = p.add_table_cell(table, col++, row,
                    testcases[test].text, optlist.str());

            /* Column 4: text with base font and fallback fonts */
            optlist.str(L"");
            optlist << L"fittextline={fontname=" << testcases[test].fontname
                << L" encoding=" << testcases[test].encoding
                << L" fontsize=10 fallbackfonts={"
                << testcases[test].fallbackoptions << L"}} margin=4";
            table = p.add_table_cell(table, col++, row,
               testcases[test].text, optlist.str());
        }

        /* Place the table */
        optlist.str(L"");
        optlist << L"header=1 fill={{area=rowodd "
                   L"fillcolor={gray 0.9}}} stroke={{line=other}} ";
        result = p.fit_table(table, llx, lly, urx, ury, optlist.str());

        if (result == L"_error")
        {
            wcerr << L"Couldn't place table: " << p.get_errmsg() << endl;
            return 2;
        }

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
