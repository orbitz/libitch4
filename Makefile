export CXXFLAGS = -std=c++0x -W -Wall -Wextra -pedantic
SUBDIRS = src tests


ifeq ($(LITTLE_ENDIAN),yes)
	export CXXFLAGS += -DLITTLE_ENDIAN
endif

ifeq ($(NDEBUG),yes)
	export CXXFLAGS += -DNDEBUG
endif

.PHONY : subdirs $(SUBDIRS)

subdirs : $(SUBDIRS)

$(SUBDIRS) :
	$(MAKE) -C $@

tests : src

.PHONY : clean
clean :
	for dir in $(SUBDIRS); do \
	  $(MAKE) -C $$dir clean; \
	done

