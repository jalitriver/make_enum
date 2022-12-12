#ifndef MAKE_ENUM_H_LWER8VDLTCWRMVF19GJNGDHC
#define MAKE_ENUM_H_LWER8VDLTCWRMVF19GJNGDHC

/*
 * Copyright (c) 2022 Paul Serice
 * 
 * This software is provided 'as-is', without any express or implied
 * warranty.  In no event will the author or authors be held liable for
 * any damages arising from the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 * 
 *     1. The origin of this software must not be misrepresented; you
 *        must not claim that you wrote the original software. If you use
 *        this software in a product, an acknowledgment in the product
 *        documentation would be appreciated but is not required.
 * 
 *     2. Altered source versions must be plainly marked as such and
 *        must not be misrepresented as being the original software.
 * 
 *     3. This notice may not be removed or altered from any source
 *        distribution.
 */

/**
 * Macros for C/C++ that are used to define enumerations and their
 * helper functions.
 *
 * Usage:
 * =====
 *
 * The macros are divided into "declaration" macros that belong in
 * header files and "definition" macros that belong in source files.
 * It is done this way because it is difficult to portably and safely
 * inline the helper functions in a header.  The following is
 * typically all you need to do to use these macros to declare and
 * define an enumeration along with all of its helper functions: <p>
 *
 * <code>
 *     // Put in header file.  Note that "EnumName" below is literally
 *     // just "EnumName".  The name of the enumeration will be passed
 *     // into the macro at the appropriate time along with the macro
 *     // X that will operate on each element.  The "MyEnum" below
 *     // however should be the name of your enumeration.
 *     #include "make_enum.h"
 *     #define MY_ENUM_ELEMENTS(EnumName, X)    \
 *         X(EnumName, FOO, 0)                  \
 *         X(EnumName, BAR, 1)                  \
 *         X(EnumName, BAZ, 2)
 *     MAKE_ENUM_DECLARATION(MyEnum, MY_ENUM_ELEMENTS)
 *
 *     // Put in source file.
 *     #include "my_header.h"
 *     MAKE_ENUM_DEFINITION(MyEnum, MY_ENUM_ELEMENTS)
 * </code>
 *
 * If you are using C++ scoped enumerations (i.e., <c>enum class</c>),
 * use the following macros instead placing the first in the header
 * file and the second in the source file.  Everything else is the
 * same: <p>
 *
 * <code>
 *     MAKE_ENUM_CLASS_DECLARATION(MyEnum, MY_ENUM_ELEMENTS)
 *     MAKE_ENUM_CLASS_DEFINITION(MyEnum, MY_ENUM_ELEMENTS)
 * <code>
 *
 *
 * C Helper Functions:
 * ==================
 *
 * The C helper functions are <c>EnumName_ToString()</c>,
 * <c>EnumName_FromString()</c>, and <c>EnumName_IsValid()</c> which
 * are summarized as follows (replace "EnumName" with the actual name
 * of the enumeration): <p>
 *
 * <pre>
 *   1) // Convert enumeration to string.  For example, if e is set to
 *      // MyEnum::FOO, this function will return "MyEnum::FOO" if
 *      // both with_enum_name is true and with_element_name are true.
 *      // It will return "MyEnum" if only with_enum_name is true.
 *      // It will return "FOO" if only with_element_name is true.
 *      // Finally, it will return an empty string if both
 *      // with_enum_name is true and with_element_name are false.
 *      // If e is invalid, an empty string is returned.
 *      const char*
 *      EnumName_ToString(enum EnumName e,
 *                        int with_enum_name,
 *                        int with_element_name);
 *
 *   2) // Convert string to enumeration.  Returns true and sets e to the
 *      // value of the enumeration if the conversion is successful;
 *      // otherwise, returns false.
 *      int
 *      EnumName_FromString(enum EnumName* e,
 *                          const char* s);
 *
 *   3) // Returns true if e is set to a valid enumeration false and
 *      // false otherwise.
 *      int
 *      EnumName_IsValid(enum EnumName e);
 * </pre>
 *
 *
 * C++ Helper Functions:
 * ====================
 *
 * The C++ helper functions include all the C helper functions listed
 * above plus the following overloaded functions: <p>
 *
 * <pre>

 *   1) // Convert enumeration to string.  Defaults to "FOO" for
 *      // <c>enum</c> and to "MyEnum::FOO" for <c>enum class</c>.
 *      std::string
 *      ToString(EnumName e,
 *               bool with_enum_name,
 *               bool with_element_name);
 *
 *   2) // Convert string to enumeration.
 *      bool
 *      FromString(EnumName& e,
 *                 const std::string& s)
 *
 *   3) // Insertion Operator
 *      std::ostream&
 *      operator<<(std::ostream& ostrm,
 *                 EnumName e);
 *
 *   4) // Extraction Operator
 *      std::istream&
 *      operator>>(std::istream& istrm,
 *                 EnumName& e);
 *
 *   5) // Returns true if e is set to a valid enumeration false and
 *      // false otherwise.
 *      bool
 *      IsValid(EnumName e);
 * </pre>
 *
 * @file
 */

#include <stddef.h>
#include <string.h>

#ifdef __cplusplus
#include <iostream>
#include <string>
#endif

/************************************************************************
 * ToString() -- You should not need to use these macros directly.
 ************************************************************************/

/**
 * Internal macro for declaring the <c>EnumName_ToString()</c>
 * function.  <c>EnumName</c> should be the same as the values passed
 * into the corresponding call to <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 */
#define MAKE_ENUM_TO_STRING_DECLARATION_BASE(EnumName)  \
    const char*                                         \
    EnumName##_ToString(enum EnumName e,                \
                        int with_enum_name,             \
                        int with_element_name);

#ifndef __cplusplus
/**
 * C version of internal macro for declaring the
 * <c>EnumName_ToString()</c> function for an <c>enum</c>.
 * <c>EnumName</c> should be the same as the values passed into the
 * corresponding call to <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 */
#define MAKE_ENUM_TO_STRING_DECLARATION(EnumName)   \
    MAKE_ENUM_TO_STRING_DECLARATION_BASE(EnumName)
#else
/**
 * C++ version of internal macro for declaring the
 * <c>EnumName_ToString()</c> function as well as overloaded
 * <c>ToString()</c> and <c>operator<<()</c> functions for an
 * <c>enum</c>.  <c>EnumName</c> should be the same as the values
 * passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 */
#define MAKE_ENUM_TO_STRING_DECLARATION(EnumName)   \
    MAKE_ENUM_TO_STRING_DECLARATION_BASE(EnumName)  \
                                                    \
    std::string                                     \
    ToString(EnumName e,                            \
             bool with_enum_name = false,           \
             bool with_element_name = true);        \
                                                    \
    std::ostream&                                   \
    operator<<(std::ostream& ostrm,                 \
               EnumName e);

/**
 * C++ version of internal macro for declaring the
 * <c>EnumName_ToString()</c> function as well as overloaded
 * <c>ToString()</c> and <c>operator<<()</c> functions for an
 * <c>enum</c>.  <c>EnumName</c> should be the same as the values
 * passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 */
#define MAKE_ENUM_CLASS_TO_STRING_DECLARATION(EnumName) \
    MAKE_ENUM_TO_STRING_DECLARATION_BASE(EnumName)      \
                                                        \
    std::string                                         \
    ToString(EnumName e,                                \
             bool with_enum_name = true,                \
             bool with_element_name = true);            \
                                                        \
    std::ostream&                                       \
    operator<<(std::ostream& ostrm,                     \
               EnumName e);
#endif

/**
 * Internal X macro for converting the enumeration element
 * <c>ElementName</c> for the enumeration <c>EnumName</c> to a string.
 *
 * @param EnumName enumeration name
 * @param ElementName enumeration element name
 * @param ElementValue enumeration element element (not used)
 */
#define X_MAKE_ENUM_TO_STRING(EnumName,                     \
                              ElementName,                  \
                              ElementValue)                 \
    case ElementName:                                       \
        if (with_enum_name && with_element_name) {          \
            result = #EnumName "::" #ElementName;           \
        } else if (with_enum_name && !with_element_name) {  \
            result = #EnumName;                             \
        } else if (!with_enum_name && with_element_name) {  \
            result = #ElementName;                          \
        } else {                                            \
            result = "";                                    \
        }                                                   \
        break;

#ifdef __cplusplus
/**
 * Internal X macro for converting the enumeration element
 * <c>ElementName</c> for the scoped enumeration <c>EnumName</c> to a
 * string.
 *
 * @param EnumName enumeration name
 * @param ElementName enumeration element name
 * @param ElementValue enumeration element element (not used)
 */
#define X_MAKE_ENUM_CLASS_TO_STRING(EnumName,               \
                                    ElementName,            \
                                    ElementValue)           \
    case EnumName::ElementName:                             \
        if (with_enum_name && with_element_name) {          \
            result = #EnumName "::" #ElementName;           \
        } else if (with_enum_name && !with_element_name) {  \
            result = #EnumName;                             \
        } else if (!with_enum_name && with_element_name) {  \
            result = #ElementName;                          \
        } else {                                            \
            result = "";                                    \
        }                                                   \
        break;
#endif  /*  __cplusplus  */

/**
 * Internal macro for defining the <c>EnumName_ToString()</c> function
 * for an <c>enum</c>.  <c>EnumName</c> and <c>EnumElements</c> should
 * be the same as the values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 * @param X macro to apply to each element
 */
#define MAKE_ENUM_TO_STRING_DEFINITION_BASE_C(EnumName,     \
                                              EnumElements, \
                                              X)            \
    const char*                                             \
    EnumName##_ToString(enum EnumName e,                    \
                        int with_enum_name,                 \
                        int with_element_name)              \
    {                                                       \
        const char* result = "";                            \
        switch (e) {                                        \
            EnumElements(EnumName, X)                       \
        default:                                            \
            result = "";                                    \
            break;                                          \
        }                                                   \
        return result;                                      \
    }

#ifdef __cplusplus
/**
 * Internal macro for defining the overloaded <c>ToString()</c> and
 * <c>operator<<()</c> functions for an <c>enum</c> or an <c>enum
 * class</c>.  <c>EnumName</c> and <c>EnumElements</c> should be the
 * same as the values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c> or
 * <c>MAKE_ENUM_CLASS_DECLARATION()</c>. <p>
 *
 * This macro works for both <c>enum</c> and <c>enum class</c>
 * enumerations because the enum logic is in the
 * <c>EnumName_ToString()</c> function which is defined elsewhere.
 * Also, the *declaration* macros are responsible for setting the
 * default values differently for <c>enum</c> and <c>enum class</c> so
 * the former default to generating just the element name (e.g.,
 * "FOO") while the later default to generating the full, scoped name
 * (e.g., "MyEnum::FOO"). <p>
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_TO_STRING_DEFINITION_BASE_CXX(EnumName,       \
                                                EnumElements)   \
    std::string                                                 \
    ToString(EnumName e,                                        \
             bool with_enum_name,                               \
             bool with_element_name)                            \
    {                                                           \
        return EnumName##_ToString(e,                           \
                                   with_enum_name,              \
                                   with_element_name);          \
    }                                                           \
                                                                \
    std::ostream&                                               \
    operator<<(std::ostream& ostrm,                             \
               EnumName e)                                      \
    {                                                           \
        ostrm << ToString(e);                                   \
        return ostrm;                                           \
    }
#endif

#ifndef __cplusplus
/**
 * C version of internal macro for defining the
 * <c>EnumName_ToString()</c> function for an <c>enum</c>.
 * <c>EnumName</c> and <c>EnumElements</c> should be the same as the
 * values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_TO_STRING_DEFINITION(EnumName,                    \
                                       EnumElements)                \
    MAKE_ENUM_TO_STRING_DEFINITION_BASE_C(EnumName,                 \
                                          EnumElements,             \
                                          X_MAKE_ENUM_TO_STRING)
#else
/**
 * C++ version of internal macro for defining the
 * <c>EnumName_ToString()</c> function as well as overloaded
 * <c>ToString()</c> and <c>operator<<()</c> functions for an
 * <c>enum</c>.  <c>EnumName</c> and <c>EnumElements</c> should be the
 * same as the values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_TO_STRING_DEFINITION(EnumName,                    \
                                       EnumElements)                \
    MAKE_ENUM_TO_STRING_DEFINITION_BASE_C(EnumName,                 \
                                          EnumElements,             \
                                          X_MAKE_ENUM_TO_STRING)    \
    MAKE_ENUM_TO_STRING_DEFINITION_BASE_CXX(EnumName, EnumElements)

/**
 * Internal macro for defining the <c>EnumName_ToString()</c> function
 * as well as overloaded <c>ToString()</c> and <c>operator<<()</c>
 * functions for an <c>enum class</c>.  <c>EnumName</c> and
 * <c>EnumElements</c> should be the same as the values passed into
 * the corresponding call to <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_CLASS_TO_STRING_DEFINITION(EnumName,                  \
                                             EnumElements)              \
    MAKE_ENUM_TO_STRING_DEFINITION_BASE_C(EnumName,                     \
                                          EnumElements,                 \
                                          X_MAKE_ENUM_CLASS_TO_STRING)  \
    MAKE_ENUM_TO_STRING_DEFINITION_BASE_CXX(EnumName, EnumElements)
#endif  /*  __cplusplus  */

/************************************************************************
 * FromString() -- You should not need to use these macros directly.
 ************************************************************************/

/**
 * Internal macro for declaring the <c>EnumName_FromString()</c>
 * function.  <c>EnumName</c> should be the same as the values passed
 * into the corresponding call to <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 */
#define MAKE_ENUM_FROM_STRING_DECLARATION_BASE(EnumName) \
    int                                                  \
    EnumName##_FromString(enum EnumName* e,              \
                          const char* s);

#ifndef __cplusplus
/**
 * C version of internal macro for declaring the
 * <c>EnumName_FromString()</c> function.  <c>EnumName</c> should be
 * the same as the values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 */
#define MAKE_ENUM_FROM_STRING_DECLARATION(EnumName) \
    MAKE_ENUM_FROM_STRING_DECLARATION_BASE(EnumName)
#else
/**
 * C++ version of internal macro for declaring the
 * <c>EnumName_FromString()</c> function as well as overloaded
 * <c>FromString()</c> and <c>operator>>()</c> functions.
 * <c>EnumName</c> should be the same as the values passed into the
 * corresponding call to <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 */
#define MAKE_ENUM_FROM_STRING_DECLARATION(EnumName)     \
    MAKE_ENUM_FROM_STRING_DECLARATION_BASE(EnumName)    \
                                                        \
    bool                                                \
    FromString(EnumName& e,                             \
               const std::string& s);                   \
                                                        \
    std::istream&                                       \
    operator>>(std::istream& istrm,                     \
               EnumName& e);
#endif

/**
 * Internal X macro for converting the string <c>s</c> to an
 * enumeration.  This works for both the scoped and unscoped
 * enumeration names, e.g., "MyEnum::FOO" and "FOO".
 *
 * @param EnumName enumeration name
 * @param ElementName enumeration element name
 * @param ElementValue enumeration element element (not used)
 */
#define X_MAKE_ENUM_FROM_STRING(EnumName,                       \
                                ElementName,                    \
                                ElementValue)                   \
    else if ((strcmp(s, #EnumName "::" #ElementName) == 0) ||   \
             (strcmp(s, #ElementName) == 0))                    \
    {                                                           \
        *e = ElementName;                                       \
        result = 1;                                             \
    }

#ifdef __cplusplus
/**
 * Internal X macro for converting the string <c>s</c> to an
 * enumeration.  This works for both the scoped and unscoped
 * enumeration names, e.g., "MyEnum::FOO" and "FOO".
 *
 * @param EnumName enumeration name
 * @param ElementName enumeration element name
 * @param ElementValue enumeration element element (not used)
 */
#define X_MAKE_ENUM_CLASS_FROM_STRING(EnumName,                 \
                                      ElementName,              \
                                      ElementValue)             \
    else if ((strcmp(s, #EnumName "::" #ElementName) == 0) ||   \
             (strcmp(s, #ElementName) == 0))                    \
    {                                                           \
        *e = EnumName::ElementName;                             \
        result = 1;                                             \
    }
#endif  /*  __cplusplus  */

/**
 * Internal macro for defining the <c>EnumName_FromString()</c>
 * function for an <c>enum</c>.  <c>EnumName</c> and
 * <c>EnumElements</c> should be the same as the values passed into
 * the corresponding call to <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 * @param X macro to apply to each element
 */
#define MAKE_ENUM_FROM_STRING_DEFINITION_BASE_C(EnumName,       \
                                                EnumElements,   \
                                                X)              \
    int                                                         \
    EnumName##_FromString(enum EnumName* e,                     \
                          const char* s)                        \
    {                                                           \
        int result = 0;                                         \
                                                                \
        if (!s || !e) {                                         \
            goto out;                                           \
        }                                                       \
        EnumElements(EnumName, X)                               \
                                                                \
     out:                                                       \
        return result;                                          \
    }

#ifdef __cplusplus
/**
 * Internal macro for defining the overloaded <c>FromString()</c> and
 * <c>operator>>()</c> functions for an <c>enum</c> or an <c>enum
 * class</c>.  <c>EnumName</c> and <c>EnumElements</c> should be the
 * same as the values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c> or
 * <c>MAKE_ENUM_CLASSDECLARATION()</c>. <p>
 *
 * This macro works for both <c>enum</c> and <c>enum class</c>
 * enumerations because the enum logic is in the
 * <c>EnumName_FromString()</c> function which is defined
 * elsewhere. <p>
 */
#define MAKE_ENUM_FROM_STRING_DEFINITION_BASE_CXX(EnumName,     \
                                                  EnumElements) \
    bool                                                        \
    FromString(EnumName& e,                                     \
               const std::string& s)                            \
    {                                                           \
        return (bool)EnumName##_FromString(&e, s.c_str());      \
    }                                                           \
                                                                \
    std::istream&                                               \
    operator>>(std::istream& istrm,                             \
               EnumName& e)                                     \
    {                                                           \
        std::string token;                                      \
        istrm >> token;                                         \
        if (!FromString(e, token)) {                            \
            istrm.setstate(std::ios::failbit);                  \
        }                                                       \
        return istrm;                                           \
    }
#endif

#ifndef __cplusplus
/**
 * C version of internal macro for defining the
 * <c>EnumName_FromString()</c> function for an <c>enum</c>.
 * <c>EnumName</c> and <c>EnumElements</c> should be the same as the
 * values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 * @param X macro to apply to each element
 */
#define MAKE_ENUM_FROM_STRING_DEFINITION(EnumName,                    \
                                         EnumElements)                \
    MAKE_ENUM_FROM_STRING_DEFINITION_BASE_C(EnumName,                 \
                                            EnumElements,             \
                                            X_MAKE_ENUM_FROM_STRING)
#else
/**
 * C++ version of internal macro for defining the
 * <c>EnumName_FromString()</c> function as well as overloaded
 * <c>FromString()</c> and <c>operator>>()</c> functions for an
 * <c>enum</c>.  <c>EnumName</c> and <c>EnumElements</c> should be the
 * same as the values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 * @param X macro to apply to each element
 */
#define MAKE_ENUM_FROM_STRING_DEFINITION(EnumName,                    \
                                         EnumElements)                \
    MAKE_ENUM_FROM_STRING_DEFINITION_BASE_C(EnumName,                 \
                                            EnumElements,             \
                                            X_MAKE_ENUM_FROM_STRING)  \
    MAKE_ENUM_FROM_STRING_DEFINITION_BASE_CXX(EnumName, EnumElements)

/**
 * Internal macro for defining the <c>EnumName_FromString()</c>
 * function as well as overloaded <c>FromString()</c> and
 * <c>operator>>()</c> functions for an <c>enum class</c>.
 * <c>EnumName</c> and <c>EnumElements</c> should be the same as the
 * values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_CLASS_FROM_STRING_DEFINITION(EnumName,                   \
                                               EnumElements)               \
    MAKE_ENUM_FROM_STRING_DEFINITION_BASE_C(EnumName,                      \
                                            EnumElements,                  \
                                            X_MAKE_ENUM_CLASS_FROM_STRING) \
    MAKE_ENUM_FROM_STRING_DEFINITION_BASE_CXX(EnumName, EnumElements)
#endif  /*  __cplusplus  */

/************************************************************************
 * IsValid() -- You should not need to use these macros directly.
 ************************************************************************/

/**
 * Internal macro for declaring the <c>EnumName_IsValid()</c>
 * function.  <c>EnumName</c> should be the same as the values passed
 * into the corresponding call to <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 */
#define MAKE_ENUM_IS_VALID_DECLARATION_BASE(EnumName)   \
    int                                                 \
    EnumName##_IsValid(enum EnumName e);

#ifndef __cplusplus
/**
 * C version of internal macro for declaring the
 * <c>EnumName_IsValid()</c> function.  <c>EnumName</c> should be the
 * same as the values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 */
#define MAKE_ENUM_IS_VALID_DECLARATION(EnumName)   \
    MAKE_ENUM_IS_VALID_DECLARATION_BASE(EnumName)
#else
/**
 * C++ version of internal macro for declaring the
 * <c>EnumName_IsValid()</c> function and an overloaded
 * <c>IsValid()</c> function.  <c>EnumName</c> should be the same as
 * the values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 */
#define MAKE_ENUM_IS_VALID_DECLARATION(EnumName)   \
    MAKE_ENUM_IS_VALID_DECLARATION_BASE(EnumName)  \
                                                   \
    bool                                           \
    IsValid(EnumName e);
#endif

/**
 * Internal X macro for determining if the value of the enumeration
 * maps to an enumeration element.
 *
 * @param EnumName enumeration name (not used)
 * @param ElementName enumeration element name
 * @param ElementValue enumeration element element (not used)
 */
#define X_MAKE_ENUM_IS_VALID(EnumName,          \
                             ElementName,       \
                             ElementValue)      \
    case ElementName:

#ifdef __cplusplus
/**
 * Internal X macro for determining if the value of the scoped
 * enumeration maps to an enumeration element.
 *
 * @param EnumName enumeration name
 * @param ElementName enumeration element name
 * @param ElementValue enumeration element element (not used)
 */
#define X_MAKE_ENUM_CLASS_IS_VALID(EnumName,        \
                                   ElementName,     \
                                   ElementValue)    \
    case EnumName::ElementName:
#endif  /*  __cplusplus  */

/**
 * Internal macro for defining the <c>EnumName_IsValid()</c> function
 * for an <c>enum</c>.  <c>EnumName</c> and <c>EnumElements</c> should
 * be the same as the values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 * @param X macro to apply to each element
 */
#define MAKE_ENUM_IS_VALID_DEFINITION_BASE_C(EnumName,      \
                                             EnumElements,  \
                                             X)             \
    int                                                     \
    EnumName##_IsValid(enum EnumName e)                     \
    {                                                       \
        int result = 0;                                     \
        switch (e) {                                        \
            EnumElements(EnumName, X)                       \
            result = 1;                                     \
            break;                                          \
        default:                                            \
            result = 0;                                     \
        }                                                   \
        return result;                                      \
    }

#ifdef __cplusplus
/**
 * Internal macro for defining the overloaded <c>IsValid()</c>
 * function for an <c>enum</c> or an <c>enum class</c>.
 * <c>EnumName</c> and <c>EnumElements</c> should be the same as the
 * values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c> or
 * <c>MAKE_ENUM_CLASS_DECLARATION()</c>. <p>
 *
 * This macro works for both <c>enum</c> and <c>enum class</c>
 * enumerations because the enum logic is in the
 * <c>EnumName_FromString()</c> function which is defined
 * elsewhere. <p>
 */
#define MAKE_ENUM_IS_VALID_DEFINITION_BASE_CXX(EnumName,        \
                                               EnumElements)    \
    bool                                                        \
    IsValid(EnumName e)                                         \
    {                                                           \
        return (bool)EnumName##_IsValid(e);                     \
    }
#endif

#ifndef __cplusplus
/**
 * C version of internal macro for defining the
 * <c>EnumName_IsValid()</c> function for an <c>enum</c>.
 * <c>EnumName</c> and <c>EnumElements</c> should be the same as the
 * values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_IS_VALID_DEFINITION(EnumName,                 \
                                      EnumElements)             \
    MAKE_ENUM_IS_VALID_DEFINITION_BASE_C(EnumName,              \
                                       EnumElements,            \
                                       X_MAKE_ENUM_IS_VALID)
#else
/**
 * C++ version of internal macro for defining the
 * <c>EnumName_IsValid()</c> function as well as an overloaded
 * <c>IsValid()</c> function for an <c>enum class</c>.
 * <c>EnumName</c> and <c>EnumElements</c> should be the same as the
 * values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_IS_VALID_DEFINITION(EnumName,                     \
                                      EnumElements)                 \
    MAKE_ENUM_IS_VALID_DEFINITION_BASE_C(EnumName,                  \
                                         EnumElements,              \
                                         X_MAKE_ENUM_IS_VALID)      \
    MAKE_ENUM_IS_VALID_DEFINITION_BASE_CXX(EnumName, EnumElements)

/**
 * C++ version of internal macro for defining the
 * <c>EnumName_IsValid()</c> function as well as an overloaded
 * <c>IsValid()</c> function for an <c>enum class</c>.
 * <c>EnumName</c> and <c>EnumElements</c> should be the same as the
 * values passed into the corresponding call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_CLASS_IS_VALID_DEFINITION(EnumName,               \
                                            EnumElements)           \
    MAKE_ENUM_IS_VALID_DEFINITION_BASE_C(EnumName,                  \
                                       EnumElements,                \
                                       X_MAKE_ENUM_CLASS_IS_VALID)  \
    MAKE_ENUM_IS_VALID_DEFINITION_BASE_CXX(EnumName, EnumElements)
#endif  /*  __cplusplus  */

/************************************************************************
 * MAKE_ENUM_DECLARATION() Family of Macros
 ************************************************************************/

/**
 * X macro for adding the enumeration element <c>ElementName</c> to an
 * enumeration and assigning it the value <c>ElementValue</c>.
 *
 * @param EnumName enumeration name (not used)
 * @param ElementName enumeration element name
 * @param ElementValue enumeration element element
 */
#define X_MAKE_ENUM_DECLARATION(EnumName, ElementName, ElementValue) \
    ElementName = (ElementValue),

/**
 * Declare only the enumeration <c>EnumName</c> having elements
 * <c>EnumElements</c>.  The enumeration will be of type
 * <c>EnumType</c> which should be <c>enum</c> for C/C++ code or
 * <c>enum class</c> for C++ code.
 *
 * @param EnumType enumeration type (enum or enum class)
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_DECLARATION_ONLY(EnumType, EnumName, EnumElements)    \
    EnumType EnumName {                                                 \
        EnumElements(EnumName, X_MAKE_ENUM_DECLARATION)                 \
    };

/**
 * Declare the <c>enum</c> enumeration <c>EnumName</c> having elements
 * <c>EnumElements</c>.  This macro belongs in your header file along
 * with <c>MAKE_ENUM_DEFINITION()</c> in your source file.  Both
 * <c>EnumName</c> and <c>EnumElements</c> should match whatever will
 * be passed into <c>MAKE_ENUM_DEFINITION()</c>. <p>
 *
 * The following code example shows how to declare an enumeration
 * along with all of its helper functions.  Do *not* replace
 * "EnumName" in the example below with the name of your enumeration,
 * but *do* replace "MyEnum" with the name of your enumeration: <p>
 *
 * <code>
 *     #define MY_ENUM_ELEMENTS(EnumName, X) \
 *         X(EnumName, FOO, 0) \
 *         X(EnumName, BAR, 1) \
 *         X(EnumName, BAZ, 2)
 *     MAKE_ENUM_DECLARATION(MyEnum, MY_ENUM_ELEMENTS)
 * </code>
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_DECLARATION(EnumName, EnumElements)           \
    MAKE_ENUM_DECLARATION_ONLY(enum, EnumName, EnumElements)    \
    MAKE_ENUM_TO_STRING_DECLARATION(EnumName)                   \
    MAKE_ENUM_FROM_STRING_DECLARATION(EnumName)                 \
    MAKE_ENUM_IS_VALID_DECLARATION(EnumName)

#ifdef __cplusplus
/**
 * Declare the <c>enum class</c> enumeration <c>EnumName</c> having
 * elements <c>EnumElements</c>.  This macro belongs in your header
 * file along with <c>MAKE_ENUM_CLASS_DEFINITION()</c> in your source
 * file.  Both <c>EnumName</c> and <c>EnumElements</c> should match
 * whatever will be passed into <c>MAKE_ENUM_CLASS_DEFINITION()</c>. <p>
 *
 * The following code example shows how to declare an enumeration
 * along with all of its helper functions.  Do *not* replace
 * "EnumName" in the example below with the name of your enumeration,
 * but *do* replace "MyEnum" with the name of your enumeration: <p>
 *
 * <code>
 *     #define MY_ENUM_ELEMENTS(EnumName, X) \
 *         X(EnumName, FOO, 0) \
 *         X(EnumName, BAR, 1) \
 *         X(EnumName, BAZ, 2)
 *     MAKE_ENUM_CLASS_DECLARATION(MyEnum, MY_ENUM_ELEMENTS)
 * </code>
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_CLASS_DECLARATION(EnumName, EnumElements)         \
    MAKE_ENUM_DECLARATION_ONLY(enum class, EnumName, EnumElements)  \
    MAKE_ENUM_CLASS_TO_STRING_DECLARATION(EnumName)                 \
    MAKE_ENUM_FROM_STRING_DECLARATION(EnumName)                     \
    MAKE_ENUM_IS_VALID_DECLARATION(EnumName)
#endif  /*  __cplusplus  */

/************************************************************************
 * MAKE_ENUM_DEFINITION() Family of Macros
 ************************************************************************/

/**
 * Define the help functions for the enumeration <c>EnumName</c>
 * having elements <c>EnumElements</c>.  This macro belongs in your
 * source file along with <c>MAKE_ENUM_DECLARATION()</c> in your
 * header file.  Both <c>EnumName</c> and <c>EnumElements</c> should
 * match whatever was passed into an earlier call to
 * <c>MAKE_ENUM_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_DEFINITION(EnumName, EnumElements)            \
    MAKE_ENUM_TO_STRING_DEFINITION(EnumName, EnumElements)      \
    MAKE_ENUM_FROM_STRING_DEFINITION(EnumName, EnumElements)    \
    MAKE_ENUM_IS_VALID_DEFINITION(EnumName, EnumElements)

#ifdef __cplusplus
/**
 * Define the help functions for the scoped enumeration (i.e., <c>enum
 * class</c>) <c>EnumName</c> having elements <c>EnumElements</c>.
 * This macro belongs in your source file along with
 * <c>MAKE_ENUM_CLASS_DECLARATION()</c> in your header file.  Both
 * <c>EnumName</c> and <c>EnumElements</c> should match whatever was
 * passed into an earlier call to
 * <c>MAKE_ENUM_CLASS_DECLARATION()</c>.
 *
 * @param EnumName enumeration name
 * @param EnumElements enumeration elements
 */
#define MAKE_ENUM_CLASS_DEFINITION(EnumName, EnumElements)          \
    MAKE_ENUM_CLASS_TO_STRING_DEFINITION(EnumName, EnumElements)    \
    MAKE_ENUM_CLASS_FROM_STRING_DEFINITION(EnumName, EnumElements)  \
    MAKE_ENUM_CLASS_IS_VALID_DEFINITION(EnumName, EnumElements)
#endif  /*  __cplusplus  */

#endif  /*  MAKE_ENUM_H_LWER8VDLTCWRMVF19GJNGDHC  */
