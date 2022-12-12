# make_enum

Macros for C/C++ that are used to define enumerations and their helper
functions.  The `enum` macros should work with any standards compliant
C/C++ compiler.  The `enum class` macros require a C++11 compiler.
The macros have been tested with GCC, Clang, and MSVC++.

## Setup

Just add [make_enum.h](include/make_enum.h) to your project.  There is no
compilation step.  The macros in `make_enum.h` cause the C/C++
preprocess to automatically generate the code and pass it directly to
the compiler as part of the compilation unit.

## Usage

The macros in `make_enum.h` are divided into "declaration" macros
(that belong in header files) and "definition" macros (that belong in
source files).  It is done this way because it is difficult to
portably and safely inline the helper functions in a header.  The
following is typically all you need to do to use these macros to
declare and define an enumeration along with all of its helper
functions:

### Header File

As show below, set up a `FOREACH` macro that can apply an `X` macro
for each element in the enumeration.  In order to generate element
names like `"MyEnum::FOO"`, an additional `EnumName` parameter needs
to be passed through the `FOREACH` macro to the `X` macro.  Then, add
the either the `MAKE_ENUM_DECLARATION()` or
`MAKE_ENUM_CLASS_DECLARATION` to your header to declare the
enumeration and its helper functions:

  ```cpp
  #include "make_enum.h"
  #define FOREACH_IN_MY_ENUM(EnumName, X) \
      X(EnumName, FOO, 0)                 \
      X(EnumName, BAR, 1)                 \
      X(EnumName, BAZ, 2)
  MAKE_ENUM_DECLARATION(MyEnum, FOREACH_IN_MY_ENUM)
  ```

Replace `MyEnum` and `FOREACH_IN_MY_ENUM` above with the name and
elements of the enumeration.

For scoped enumerations in modern C++, use
`MAKE_ENUM_CLASS_DECLARATION()` instead of `MAKE_ENUM_DECLARATION()`.

See [X Macros](https://en.wikipedia.org/wiki/X_Macro) on Wikipedia for
more information on how X Macros work.

### Source File

Add the corresponding `MAKE_ENUM_DEFINITION()` or
`MAKE_ENUM_CLASS_DEFINITION()` to your source file to define the
helper functions:

  ```cpp
  #include "my_header.h"
  MAKE_ENUM_DEFINITION(MyEnum, FOREACH_IN_MY_ENUM)
  ```
  
Replace `FOREACH_IN_MY_ENUM` with the name of the `FOREACH` macro that
was passed into the corresponding `MAKE_ENUM_DEFINITION()` call in the
header file.

For scoped enumerations in modern C++, use
`MAKE_ENUM_CLASS_DEFINITION()` instead of `MAKE_ENUM_DEFINITION()`.

## Helper Functions

### C Helper Functions

The following C helper functions are generated for each enumeration
where `<EnumName>` should be replaced with the name of the
enumeration:

  *  ```cpp
     const char*
     <EnumName>_ToString(enum EnumName e,
                         int with_enum_name,
                         int with_element_name);
     ```

  * ```cpp
    int
    <EnumName>_FromString(enum EnumName* e,
                          const char* s);
    ```

  * ```cpp
    int
    <EnumName>_IsValid(enum EnumName e);
    ```

### C++ Helper Functions

The C++ helper functions include all of the C helper functions plus
the following overloaded functions that do not include the name of the
enumeration in the name of the function:

  * ```cpp
    std::string
    ToString(EnumName e,
             bool with_enum_name,
             bool with_element_name);
    ```

      If e is an `enum`, `ToString(e)` defaults to return just the
      element name, e.g., `FOO`.  If e is an `ename class`,
      `ToString(e)` defaults to return the scoped name, e.g.,
      `MyEnum::FOO`.

  * ```cpp
    bool
    FromString(EnumName& e,
               const std::string& s)
    ```

  * ```cpp
    std::ostream&
    operator<<(std::ostream& ostrm,
               EnumName e);
    ```

  * ```cpp
    std::istream&
    operator>>(std::istream& istrm,
               EnumName& e);
    ```

  * ```cpp
    bool
    IsValid(EnumName e);
    ```
