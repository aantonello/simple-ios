# ============================================================================
# Makefile script.
# ============================================================================
.PHONY: debug release clean all docs install

# ----------------------------------------------------------------------------
# CONFIGURATION
# ----------------------------------------------------------------------------
LIBVER  = 2.0
BUILD   = 56
TARGET  = Simple
VERSION = A
ROOTDIR = .
PROJECT = $(ROOTDIR)/$(TARGET).xcodeproj
INSTALLDIR = $(WORKHOME)/libs/simple-$(LIBVER)/ios
HELPDIR = docs/help
DOCSDIR = simple-$(LIBVER)

# ----------------------------------------------------------------------------
# DEFAULT DIRECTORIES
# NOTE: BUILD_X86 and BUILD_ARM paths are defined in the project file.
# ----------------------------------------------------------------------------
BUILD_DIR = $(PWD)/build
BUILD_DBG = $(BUILD_DIR)/Debug
BUILD_REL = $(BUILD_DIR)/Release
DIST_DIR  = $(INSTALLDIR)/$(TARGET).framework

# ----------------------------------------------------------------------------
# Xcode Environment
# ----------------------------------------------------------------------------
PROJECT_TEMP_DIR=$(BUILD_DIR)/temp
ifeq ($(findstring debug,$(MAKECMDGOALS)),debug)
  CONFIGURATION_BUILD_DIR=$(BUILD_DIR)/Debug
  BUILT_PRODUCTS_DIR=$(BUILD_DIR)/Products/Debug
else
  CONFIGURATION_BUILD_DIR=$(BUILD_DIR)/Release
  BUILT_PRODUCTS_DIR=$(BUILD_DIR)/Products/Release
endif
XCENV=PROJECT_TEMP_DIR=$(PROJECT_TEMP_DIR) \
	  CONFIGURATION_BUILD_DIR=$(CONFIGURATION_BUILD_DIR) \
	  BUILT_PRODUCTS_DIR=$(BUILT_PRODUCTS_DIR)

ROOTS=OBJROOT=$(BUILD_DIR)/temp \
	  SYMROOT=$(BUILD_DIR)

# ----------------------------------------------------------------------------
# OUTPUT FILES
# ----------------------------------------------------------------------------
OUTSIM = $(BUILD_DBG)/$(TARGET).framework/$(TARGET)
OUTARM = $(BUILD_REL)/$(TARGET).framework/$(TARGET)
OUTPUT = $(DIST_DIR)/Versions/$(VERSION)/$(TARGET)

# ----------------------------------------------------------------------------
# MAKEFILE TARGETS
# ----------------------------------------------------------------------------
debug :
	xcodebuild -project "$(PROJECT)" -configuration Debug -target "$(TARGET)" -sdk iphonesimulator $(ROOTS)

release : debug
	xcodebuild -project "$(PROJECT)" -configuration Release -target "$(TARGET)" -sdk iphoneos $(XCENV)
	lipo -create "$(OUTSIM)" "$(OUTARM)" -output "$(OUTPUT)"

clean :
	rm -fR $(BUILD_DIR)

$(HELPDIR) :
	mkdir -p $@

$(DIST_DIR) :
	mkdir -p "$(DIST_DIR)"
	mkdir -p "$(DIST_DIR)/Versions"
	mkdir -p "$(DIST_DIR)/Versions/$(VERSION)"
	mkdir -p "$(DIST_DIR)/Versions/$(VERSION)/Resources"
	mkdir -p "$(DIST_DIR)/Versions/$(VERSION)/Headers"
	ln -s "$(VERSION)" "$(DIST_DIR)/Versions/Current"
	ln -s "Versions/Current/Headers" "$(DIST_DIR)/Headers"
	ln -s "Versions/Current/Resources" "$(DIST_DIR)/Resources"
	ln -s "Versions/Current/$(TARGET)" "$(DIST_DIR)/$(TARGET)"

install :
	rm -fR "$(INSTALLDIR)"
	mkdir -p "$(INSTALLDIR)"
	cp -R "$(DIST_DIR)" "$(INSTALLDIR)"

docs : $(HELPDIR)
	( cat Doxyfile ; echo "PROJECT_NUMBER=$(LIBVER).$(BUILD)" ) | doxygen -

docs-install:
	publish -doc plx/$(DOCSDIR) -f -q
	cp "$(HELPDIR)/simple.dxt" "$(INSTALLDIR)"

