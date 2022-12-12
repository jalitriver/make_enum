EXECS = main_c main_cxx

CPPFLAGS = -I../include
CFLAGS = -g -Wall
CXXFLAGS = -std=c++11 $(CFLAGS)

all: $(EXECS)
	@echo "Done."

# Build directly from source without explicit object files.
main_c: main_c.c my_enums.c my_enums.h ../include/make_enum.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ main_c.c my_enums.c $(LDFLAGS)

# Build directly from source without explicit object files.
main_cxx: main_cxx.cpp my_enums.cpp my_enums.hpp ../include/make_enum.h
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $@ main_cxx.cpp my_enums.cpp $(LDFLAGS)

clean:
	-$(RM) $(EXECS) $(DEPS)

.PHONEY: all clean
