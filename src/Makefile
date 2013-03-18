SOURCES = itch_message_parser.cc itch_parser.cc
OBJECTS = $(patsubst %.cc,%.o,$(SOURCES))
CPPFLAGS ?= -I.
CXXFLAGS ?= -O3 -std=c++0x -W -Wall -Wextra -pedantic

.PHONY : all
all : $(OBJECTS) libitch4.a

libitch4.a : $(OBJECTS)
	ar rcs libitch4.a $(OBJECTS)

$(OBJECTS) : $(SOURCES)

itch_message_parser.cc : itch_parser.hh itch_buffer.hh itch_message_types.hh endian_conversion.hh

itch_parser.cc : itch_parser.hh itch_message_parser.hh ascii_table.hh

itch_parser.hh : itch_buffer.hh

itch_buffer.hh : itch_message_types.hh

itch_message_types.hh : max_integer.hh itch_types.hh

itch_types.hh : fixed_array.hh ascii_table.hh

endian_conversion.hh : 

.PHONY : clean
clean : 
	-rm *.o libitch4.a

