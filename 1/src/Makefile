HEADERS = BrushConfigUI.h correlation.h FltDesignUI.h HelpPageUI.h ImageLib/FileIO.h ImageLib/Image.h ImageLib/RefCntMem.h ImgFilterUI.h ImgFltAux.h imgflt.h ImgView.h iScissor.h PriorityQueue.h ScissorPanelUI.h
CPPS = BrushConfigUI.cpp correlation.cpp FltDesignUI.cpp HelpPageUI.cpp ImageLib/FileIO.cpp ImageLib/Image.cpp ImageLib/RefCntMem.cpp ImgFilterUI.cpp ImgFltAux.cpp ImgFltMain.cpp ImgView.cpp iScissor.cpp ScissorPanelUI.cpp
OBJS = BrushConfigUI.o correlation.o FltDesignUI.o HelpPageUI.o ImageLib/FileIO.o ImageLib/Image.o ImageLib/RefCntMem.o ImgFilterUI.o ImgFltAux.o ImgFltMain.o ImgView.o iScissor.o ScissorPanelUI.o
INCS = 

UNAME := $(shell uname)
# Flags for Linux
ifeq ($(UNAME), Linux)
LIBS = -L$(HOME)/local/lib -lfltk -L/usr/X11R6/lib -lX11
CFLAGS = -g
endif
# Flags for OSX
ifeq ($(UNAME), Darwin)
#CFLAGS =  -g `fltk-config --cxxflags `
CFLAGS =  -g "-I/usr/local/Cellar/fltk/1.3.0/include -Os -w -pipe -Qunused-arguments -mmacosx-version-min=10.8 -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_THREAD_SAFE -D_REENTRANT"
LIBS = `fltk-config --libs` -framework Cocoa
#LIBS = -L/usr/local/Cellar/fltk/1.3.0/lib -lfltk
endif

scissors: $(OBJS)
	g++ -g -o $@ $(OBJS) $(CFLAGS) $(LIBS)

clean:
	touch scissors foo.o ImageLib/foo.o
	rm scissors *.o */*.o

.PHONY: clean

BrushConfigUI.o: BrushConfigUI.cpp BrushConfigUI.h imgflt.h \
  ImageLib/Image.h ImageLib/RefCntMem.h ImageLib/Image.inl \
  ImageLib/FileIO.h PriorityQueue.h ImgFilterUI.h FltDesignUI.h \
  HelpPageUI.h ScissorPanelUI.h ImgView.h correlation.h ImgFltAux.h iScissor.h
	g++ -g -o $@ -c BrushConfigUI.cpp $(CFLAGS) $(INCS)

correlation.o: correlation.cpp correlation.h imgflt.h ImageLib/Image.h \
  ImageLib/RefCntMem.h ImageLib/Image.inl ImageLib/FileIO.h \
  PriorityQueue.h ImgFilterUI.h FltDesignUI.h \
  BrushConfigUI.h HelpPageUI.h ScissorPanelUI.h ImgView.h ImgFltAux.h iScissor.h
	g++ -g -o $@ -c correlation.cpp $(CFLAGS) $(INCS)

FltDesignUI.o: FltDesignUI.cpp FltDesignUI.h imgflt.h ImageLib/Image.h \
  ImageLib/RefCntMem.h ImageLib/Image.inl ImageLib/FileIO.h \
  PriorityQueue.h ImgFilterUI.h BrushConfigUI.h HelpPageUI.h \
  ScissorPanelUI.h ImgView.h correlation.h ImgFltAux.h iScissor.h
	g++ -g -o $@ -c FltDesignUI.cpp $(CFLAGS) $(INCS)

HelpPageUI.o: HelpPageUI.cpp HelpPageUI.h
	g++ -g -o $@ -c HelpPageUI.cpp $(CFLAGS) $(INCS)

ImgFilterUI.o: ImgFilterUI.cpp ImgFilterUI.h imgflt.h ImageLib/Image.h \
  ImageLib/RefCntMem.h ImageLib/Image.inl ImageLib/FileIO.h \
  PriorityQueue.h FltDesignUI.h BrushConfigUI.h HelpPageUI.h \
  ScissorPanelUI.h ImgView.h correlation.h ImgFltAux.h iScissor.h
	g++ -g -o $@ -c ImgFilterUI.cpp $(CFLAGS) $(INCS)

ImgFltAux.o: ImgFltAux.cpp ImgFltAux.h
	g++ -g -o $@ -c ImgFltAux.cpp $(CFLAGS) $(INCS)

ImgFltMain.o: ImgFltMain.cpp imgflt.h ImageLib/Image.h \
  ImageLib/RefCntMem.h ImageLib/Image.inl ImageLib/FileIO.h \
  PriorityQueue.h ImgFilterUI.h FltDesignUI.h \
  BrushConfigUI.h HelpPageUI.h ScissorPanelUI.h ImgView.h \
  correlation.h ImgFltAux.h iScissor.h
	g++ -g -o $@ -c ImgFltMain.cpp $(CFLAGS) $(INCS)

ImgView.o: ImgView.cpp ImgView.h imgflt.h ImageLib/Image.h \
  ImageLib/RefCntMem.h ImageLib/Image.inl ImageLib/FileIO.h \
  PriorityQueue.h ImgFilterUI.h FltDesignUI.h BrushConfigUI.h \
  HelpPageUI.h ScissorPanelUI.h correlation.h ImgFltAux.h iScissor.h
	g++ -g -o $@ -c ImgView.cpp $(CFLAGS) $(INCS)

iScissor.o: iScissor.cpp correlation.h imgflt.h ImageLib/Image.h \
  ImageLib/RefCntMem.h ImageLib/Image.inl ImageLib/FileIO.h \
  PriorityQueue.h ImgFilterUI.h FltDesignUI.h \
  BrushConfigUI.h HelpPageUI.h ScissorPanelUI.h ImgView.h ImgFltAux.h iScissor.h
	g++ -g -o $@ -c iScissor.cpp $(CFLAGS) $(INCS)

ScissorPanelUI.o: ScissorPanelUI.cpp ScissorPanelUI.h imgflt.h \
  ImageLib/Image.h ImageLib/RefCntMem.h ImageLib/Image.inl \
  ImageLib/FileIO.h PriorityQueue.h ImgFilterUI.h FltDesignUI.h \
  BrushConfigUI.h HelpPageUI.h ImgView.h correlation.h ImgFltAux.h iScissor.h
	g++ -g -o $@ -c ScissorPanelUI.cpp $(CFLAGS) $(INCS)

ImageLib/FileIO.o: ImageLib/FileIO.cpp ImageLib/Image.h ImageLib/RefCntMem.h \
  ImageLib/Image.inl ImageLib/FileIO.h
	g++ -g -o $@ -c ImageLib/FileIO.cpp $(CFLAGS) $(INCS)

ImageLib/Image.o: ImageLib/Image.cpp ImageLib/Image.h ImageLib/RefCntMem.h \
  ImageLib/Image.inl
	g++ -g -o $@ -c ImageLib/Image.cpp $(CFLAGS) $(INCS)

ImageLib/RefCntMem.o: ImageLib/RefCntMem.cpp ImageLib/RefCntMem.h
	g++ -g -o $@ -c ImageLib/RefCntMem.cpp $(CFLAGS) $(INCS)

