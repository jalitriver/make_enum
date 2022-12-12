#include "my_enums.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>

int
main(int argc,
     char* argv[])
{
    int rv = 0;
    MyEnum1 e1;
    MyEnum2 e2;
    const char* s = NULL;

    try {

        // EnumName_FromString()
        s = "FOO";
        if (!MyEnum1_FromString(&e1, s)) {
            std::ostringstream errmsg;
            errmsg << "MyEnum1_FromString: " << s;
            throw std::runtime_error(errmsg.str());
        }

        s = "MyEnum2::SPAM";
        if (!MyEnum2_FromString(&e2, s)) {
            std::ostringstream errmsg;
            errmsg << "MyEnum2_FromString: " << s;
            throw std::runtime_error(errmsg.str());
        }
    
        // EnumName_ToString() with and without enum name and element name.
        std::cout << "EnumName_ToString():" << std::endl;
        std::cout << "    e1 = " << MyEnum1_ToString(e1, 1, 1) << std::endl;
        std::cout << "    e1 = " << MyEnum1_ToString(e1, 1, 0) << std::endl;
        std::cout << "    e1 = " << MyEnum1_ToString(e1, 0, 1) << std::endl;
        std::cout << "    e2 = " << MyEnum2_ToString(e2, 1, 1) << std::endl;
        std::cout << "    e2 = " << MyEnum2_ToString(e2, 1, 0) << std::endl;
        std::cout << "    e2 = " << MyEnum2_ToString(e2, 0, 1) << std::endl;
    
        // FromString()
        s = "BAR";
        if (!FromString(e1, s)) {
            std::ostringstream errmsg;
            errmsg << "FromString: " << s;
            throw std::runtime_error(errmsg.str());
        }

        s = "MyEnum2::EGGS";
        if (!FromString(e2, s)) {
            std::ostringstream errmsg;
            errmsg << "FromString: " << s;
            throw std::runtime_error(errmsg.str());
        }
    
        // ToString() with and without enum name and element name.
        std::cout << "ToString():" << std::endl;
        std::cout << "    e1 = " << ToString(e1) << " (default)" << std::endl;
        std::cout << "    e1 = " << ToString(e1, 1, 1) << std::endl;
        std::cout << "    e1 = " << ToString(e1, 1, 0) << std::endl;
        std::cout << "    e1 = " << ToString(e1, 0, 1) << std::endl;
        std::cout << "    e2 = " << ToString(e2) << " (default)" << std::endl;
        std::cout << "    e2 = " << ToString(e2, 1, 1) << std::endl;
        std::cout << "    e2 = " << ToString(e2, 1, 0) << std::endl;
        std::cout << "    e2 = " << ToString(e2, 0, 1) << std::endl;

        // operator>>()
        s = "FOO";
        std::istringstream istrm(s);
        istrm >> e1;
        if (!istrm) {
            std::ostringstream errmsg;
            errmsg << "operator>>(): " << s;
            throw std::runtime_error(errmsg.str());
        }
        istrm.clear();

        s = "MyEnum2::SPAM";
        istrm.str(s);
        istrm >> e2;
        if (!istrm) {
            std::ostringstream errmsg;
            errmsg << "operator>>(): " << s;
            throw std::runtime_error(errmsg.str());
        }
    
        // operator<<()
        std::cout << "operator<<():" << std::endl;
        std::cout << "    e1 = " << e1 << std::endl;
        std::cout << "    e2 = " << e2 << std::endl;
    
        // EnumName_IsValid()
        std::cout << "EnumName_IsValid():" << std::endl;
        std::cout << "    (MyEnum1)2 -> "
                  << MyEnum1_IsValid((enum MyEnum1)2)
                  << std::endl;
        std::cout << "    (MyEnum2)2 -> "
                  << MyEnum2_IsValid((enum MyEnum2)2)
                  << std::endl;

        // IsValid()
        std::cout << std::boolalpha;
        std::cout << "IsValid():" << std::endl;
        std::cout << "    (MyEnum1)2 -> " << IsValid((enum MyEnum1)2)
                  << std::endl;
        std::cout << "    (MyEnum2)2 -> " << IsValid((enum MyEnum2)2)
                  << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "*** Error: " << e.what() << std::endl;
        rv = 1;
    }

    return rv;
}
