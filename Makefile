# ============================================================================
# Makefile script.
# ============================================================================
.PHONY: debug release clean docs

# ----------------------------------------------------------------------------
# CONFIGURATION
# ----------------------------------------------------------------------------
ifeq ($(findstring release,$(MAKECMDGOALS)),release)
CONFIG=Release
else
CONFIG=Debug
endif

LIBVER  = 2.0
BUILD   = 56
TARGET  = Simple
VERSION = A
ROOTDIR = .
OUTDIR  = $(PWD)/build
PROJECT = $(ROOTDIR)/$(TARGET).xcodeproj
FRMKSIM = $(OUTDIR)/$(CONFIG)-iphonesimulator/$(TARGET).framework
FRMKIOS = $(OUTDIR)/$(CONFIG)-iphoneos/$(TARGET).framework
BINDIR  = $(OUTDIR)/$(CONFIG)
LIBDIR  = $(WORKHOME)/libs/$(TARGET)-$(LIBVER)
DISTDIR = $(LIBDIR)/$(CONFIG)
DISTFMK = $(DISTDIR)/$(TARGET).framework
HELPDIR = docs/help
DOCSDIR = $(TARGET)-$(LIBVER)

# ----------------------------------------------------------------------------
# Xcode Environment
# ----------------------------------------------------------------------------
XCENV=OBJROOT=$(OUTDIR) SYMROOT=$(OUTDIR) DSTROOT=$(OUTDIR)

# ----------------------------------------------------------------------------
# OUTPUT FILES
# ----------------------------------------------------------------------------
OUTSIM = $(FRMKSIM)/$(TARGET)
OUTIOS = $(FRMKIOS)/$(TARGET)
OUTPUT = $(BINDIR)/$(TARGET)

# ----------------------------------------------------------------------------
# MAKEFILE TARGETS
# ----------------------------------------------------------------------------
$(BINDIR) :
	mkdir -p $(BINDIR)

$(DISTDIR) :
	mkdir -p $(DISTDIR)

clean :
	rm -fR $(OUTDIR)

build-sim :
	xcodebuild -project "$(PROJECT)" -configuration $(CONFIG) -sdk iphonesimulator $(XCENV)

build-ios :
	xcodebuild -project "$(PROJECT)" -configuration $(CONFIG) -sdk iphoneos $(XCENV)

build-lib : $(BINDIR)
	lipo -create "$(OUTSIM)" "$(OUTIOS)" -output "$(OUTPUT)"

install : $(DISTDIR)
	cp -R $(FRMKIOS) $(DISTDIR)
	cp $(OUTPUT) $(DISTFMK)/$(TARGET)

debug-sim : build-sim

debug-ios : build-ios

release-sim : build-sim

release-ios : build-ios

debug : build-sim build-ios build-lib

release : build-sim build-ios build-lib

debug-install : debug install

release-install : release install

$(HELPDIR) :
	mkdir -p $@

docs : $(HELPDIR)
	( cat doxyfile ; echo "PROJECT_NUMBER=$(LIBVER).$(BUILD)" ) | doxygen -

docs-install:
	publish -doc plx/$(DOCSDIR) -f -q
	cp "$(HELPDIR)/$(TARGET).dxt" "$(LIBDIR)"

help :
	@echo "$(TARGET).framework makefile targets:\n"\
		 "clean            Erases everything below 'build' directory.\n"\
		 "debug-sim        Build 'Debug' configuration for Simulator only.\n"\
		 "debug-ios        Build 'Debug' configuration for iOS only.\n"\
		 "debug            Build 'Debug' configuration for Simulator and iOS.\n"\
		 "debug-install    Build and publishes the 'Debug' configuration.\n"\
		 "release-sim      Build 'Release' configuration for Simulator only.\n"\
		 "release-ios      Build 'Release' configuration for iOS only.\n"\
		 "release          Build 'Release' configuration for Simulator and iOS.\n"\
		 "release-install  Build and publishes the 'Release' configuration.\n"\
		 "\n"\
		 "The 'debug-install' or 'release-install' can only install after both\n"\
		 "simulator and iOS targats are built. Each configuration is put in a\n"\
		 "different distribution directory:\n"\
		 "For 'Debug' configuration:\n"\
		 "'$(LIBDIR)/Debug'\n"\
		 "For 'Release' configuration:\n"\
		 "'$(LIBDIR)/Release'\n"

