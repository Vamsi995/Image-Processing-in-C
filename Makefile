LIBDIR := lib
OBJDIR := obj
EXEDIR := bin
LIBSO  := lib.so
SOBJ   := s_obj


EXE := $(EXEDIR)/Iprocess
LIBS := $(addprefix $(LIBDIR)/,libmatrixmath.a libtransformation.a libIO.a)
SRCS := $(wildcard src/*.c)
HEADERS := $(wildcard include/*.h)
OBJS := $(addprefix $(OBJDIR)/,$(patsubst src/%.c,%.o,$(SRCS)))

vpath %.c src
vpath %.h include



all: build run
	@echo "Finished Successfully"

.PHONY: build	
build: obj/main.o liba | $(EXEDIR)
	gcc -o $(EXE) -I include $< -L lib -lmatrixmath -ltransformation -lIO -lm

$(OBJDIR)/%.o: src/%.c matrix.h transformation.h | $(OBJDIR)
	gcc -o $@ -c -I include $<
	
# $(LIBDIR)/libmatrixmath.a: obj/matrix.o include/matrix.h include/transformation.h | $(LIBDIR)
# 	ar rcs $@ $^

# $(LIBDIR)/libtransformation.a: obj/transformation.o obj/matrix.o include/matrix.h include/transformation.h | $(LIBDIR) 
# 	ar rcs $@ $^

.PHONY: liba
liba: obj/matrix.o obj/transformation.o obj/IO.o include/matrix.h include/transformation.h | $(LIBDIR)
	ar rcs $(LIBDIR)/libmatrixmath.a obj/matrix.o include/matrix.h include/transformation.h
	ar rcs $(LIBDIR)/libtransformation.a $^
	ar rcs $(LIBDIR)/libIO.a obj/IO.o include/IO.h



$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(EXEDIR):
	mkdir -p $(EXEDIR)

$(LIBSO):
	mkdir -p $(LIBSO) 

$(SOBJ):
	mkdir -p $(SOBJ)


.PHONY: run
run:
	./bin/Iprocess Images/input.ppm run

.PHONY: T1
T1:
	./bin/Iprocess Images/input.ppm T1


.PHONY: T2
T2:
	./bin/Iprocess Images/input.ppm T2


.PHONY: clean
clean:
	rm -rf $(EXEDIR) $(OBJDIR) $(LIBDIR)
	rm -rf $(LIBSO) $(SOBJ)



.PHONY: libso
libso: s_obj/matrix.o s_obj/transformation.o |$(LIBSO)
	gcc -shared -o lib.so/libmatrixmath.so      s_obj/matrix.o 
	gcc -shared -o lib.so/libtransformation.so  s_obj/transformation.o

s_obj/matrix.o:  src/matrix.c   include/matrix.h include/transformation.h include/types.h  |$(SOBJ)
	gcc -fPIC -c -I ./include/ src/matrix.c -o s_obj/matrix.o

s_obj/transformation.o:  src/transformation.c     include/matrix.h  include/transformation.h include/types.h    
	gcc -fPIC -c -I ./include/ src/transformation.c -o s_obj/transformation.o


