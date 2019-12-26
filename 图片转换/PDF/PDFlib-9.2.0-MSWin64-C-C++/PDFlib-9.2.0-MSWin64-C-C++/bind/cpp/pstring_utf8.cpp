// Demonstration of "user converter" for the PDFlib C++ binding:
// Customize the C++ binding so that it accepts UTF-8 strings as input.
//
// Note: This example does not work on EBCDIC platforms. To make this work,
// all string literals would have to be explicitly encoded with escape
// sequences, e.g. "Hello world" --> "\x48\x65\x6c\x6c6f\x20\x77\72\x6c\x64"
//
// required software: PDFlib/PDFlib+PDI/PPS 9
// required data: none

#include <iostream>

#include "pdflib.hpp"

using namespace std;
using namespace pdflib;


/*
 * Declarations in order to avoid cluttering the code with template-specific
 * syntax. A new string type "utf8_string" is defined as a typedef to make
 * them clearly visible, but this would not be strictly necessary, and
 * std::string could be used as well.
 */
typedef basic_string<char> utf8_string;
class UTF8Converter;
typedef basic_PDFlib<utf8_string, UTF8Converter> UTF8PDFlib;

/*
 * This is a very basic demonstration of the concept of converters that can
 * be plugged into the basic_PDFlib class as a template parameter. It enables
 * the usage of UTF-8 strings with PDFlib. For this type of strings the
 * converter class almost has nothing to do.
 *
 * In the general case the class could take an arbitrary string encoding and
 * convert it to the required encodings. It could check the input parameters for
 * valid encoding, and it should throw a basic_PDFlib<pstring, conv>::Exception
 * to indicate the failure (see comment in convert_to_pdf_bytes() below).
 */
class UTF8Converter
{
public:
    /*
     * Instruct PDFlib to call the user-specified converter routines
     */
    static bool do_conversion()
    {
        return true;
    }

    /*
     * Perform conversion from UTF-8 string to a sequence of bytes. This will
     * be used on parameters that can contain only 7-bit ASCII, so the
     * conversion can simply pass through the string.
     */
    static void
    convert_to_pdf_bytes(const UTF8PDFlib&,
                            const utf8_string& in, string& out)
    {
        /*
         * Here we could check the input string for valid encoding. In case
         * of an error we would throw an exception like this:
         *
         * throw UTF8PDFlib::Exception("Invalid UTF-8 string", -1,
         *                "UTF8Converter::convert_to_pdf_bytes", 0);
         */
        out = in;
    }

    /*
     * Perform conversion from user-defined UTF-8 string to a std::string
     * containg UTF-8. We can simply copy the string.
     */
    static void
    convert_to_pdf_utf8(const UTF8PDFlib&, const utf8_string& in, string& out)
    {
        out = in;
    }

    /*
     * Perform conversion from user-defined UTF-8 string to a std::string
     * containing UTF-16. Here we use the PDFlib-supplied conversion routine.
     */
    static void
    convert_to_pdf_utf16(const UTF8PDFlib& p,
                            const utf8_string& in, string& out)
    {
        out = p.convert_to_unicode("utf8", in, "outputformat=utf16");
    }
        
    /*
     * Perform conversion from UTF-8 to a user-defined UTF-8 string. We
     * can simply copy the string.
     */
    static void
    convert_to_pstring(const UTF8PDFlib&,
                            const char *utf8_in, utf8_string& out)
    {
        out.assign(utf8_in);
    }
};

int
main(void)
{
    try {
        /*  This is where the data files are. Adjust as necessary. */
        const utf8_string searchpath = "../data";
        UTF8PDFlib p;
        const utf8_string imagefile = "nesrin.jpg";
        int font, image;

        stringstream optlist;

        //  This means we must check return values of load_font() etc.
        p.set_option("errorpolicy=return");

        // Set the search path for fonts and PDF files
        optlist.str("");
        optlist << "searchpath=" << searchpath;
        p.set_option(optlist.str());

        if (p.begin_document("pstring_utf8.pdf", "") == -1) {
            cerr << "Error: " << p.get_errmsg() << endl;
            return 2;
        }

        p.set_info("Creator", "PDFlib user-defined string converter sample");
        p.set_info("Title", "pstring_utf8");

        image = p.load_image("auto", imagefile, "");

        if (image == -1) {
            cerr << "Error: " << p.get_errmsg() << endl;
            return 2;
        }

        p.begin_page_ext(0,0, "width=a4.width height=a4.height");

        font = p.load_font("Helvetica", "unicode", "");
        if (font == -1) {
            cerr << "Error: " << p.get_errmsg() << endl;
            return 2;
        }

        p.setfont(font, 24);

        p.set_text_pos(50, 700);
        p.show("Hello world!");
        p.continue_text("This program has its strings encoded as UTF-8.");
        p.continue_text("Some characters beyond 0x7f: "
                        "\xc3\xb6\xc3\xa4\xc3\xbc \xc2\xbc\xc2\xbd\xc2\xbe");

        p.fit_image(image, 0.0, 0.0, "scale=0.25");

        p.end_page_ext("");

        p.close_image(image);
        p.end_document("");
    }
    catch (UTF8PDFlib::Exception &ex) {
        cerr << "PDFlib exception occurred:" << endl
             << "[" << ex.get_errnum() << "] " << ex.get_apiname()
             << ": " << ex.get_errmsg() << endl;
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
