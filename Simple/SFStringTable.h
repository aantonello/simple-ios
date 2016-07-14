/**
 * @file
 * Declares the SFStringTable Objective-C interface class.
 *
 * @author  Alessandro Antonello aantonello@paralaxe.com.br
 * @date    October 04, 2014
 * @since   Simple Framework 1.3
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#import <Foundation/Foundation.h>
#import "SFXml.h"

/**
 * \defgroup sf_resources Resources
 * Localized resource support.
 * This module provides support for localizaed string resources. Although the
 * iOS and XCode already provide such support, that is based on the LC_MESSAGE
 * system with some changes done by Apple. The programmer almost never touch
 * the XML files generated and everything is kept automatic. Automation is
 * good to speed up things but doesn't provide flexibility and you almost
 * never can reuse code or data files.
 *
 * This modules has support to the same string table resources that are
 * supported by the old
 * <a href="https://github.com/aantonello/jguime">jGuiME</a> library providing
 * programmers to reuse string table files already made for the Android
 * environment.
 *
 * \par File Format
 *
 * A string table file is a standard XML file. By been a standard XML file it
 * can be used in any language that supports XML. In this library we use
 * SFXMLFile and SFXMLElement classes to read these files. The string table
 * file used has the following format:
 * ~~~~~~~~~~~~~~~~{.xml}
<?xml version="1.0" encoding="UTF-8" ?>
<stringtable version="1">
  <string id="1" value="text" />
  <string id="0x02" value="another text" />
</stringtable>
 * ~~~~~~~~~~~~~~~~
 * Extremely simple, the file has a root element called \c stringtable. This
 * root element has only one attribute named \c version. This attribute sets
 * the version of the string table file format. This is still in version 1.
 * The version was not changed since the file format was created for J2ME
 * supported phones.
 *
 * The \c stringtable element can have one or more \c string elements. Each
 * element has an identifier and a value. The identifier, identified by the \c
 * id attribute, is a number that can be in decimal, hexadecimal or octal. The
 * \c value attribute has the string related which that identifier.
 *
 * \par Localized Files
 *
 * The Java language allows us to organize resources into directories.
 * Unfortunately the iOS and OS X bundles don't allow us to do that. The
 * resources bundled with an application are all put in the same directory. To
 * be able to localize strings we need to provide files with different names.
 * Naming them according to the language they represent. This module supports
 * file names suffixes setting the language and country specification. The
 * language specification is a standard ISO 639-1 two letter identifier ("en"
 * for English, "pt" for Portuguese). The country specification is a standard
 * ISO-3166-1 two capital letters ("US" for United States, "BR" for Brazil).
 * The file name must be separated by the suffix with a dash ("-") and, after
 * the language/country suffix only the extension ".xml" must follow. Let us
 * see and example:
 * @code
strings-en_US.xml
strings-en_UK.xml
strings-pt_PO.xml
strings-pt_BR.xml
 * @endcode
 * In this example we have 4 files with two languages and four countries. The
 * "en" specifies the English language and are two versions of it. One for
 * United States country, defined by the "US" country code, and one for United
 * Kingdom, defined by "UK" code. Also we have two files for Portuguese
 * language, defined by the "pt" code. One for Portugal, recognized by the
 * "PO" country code, and another for Brazil, identified by the "BR" country
 * code.
 *
 * This module provides access to those files through the \c SFAssets class.
 * It is an interface with only static methods. Look at its documentation to
 * know more about the file loading facilities. When a string table file is
 * loaded it is encapsulated in a \c SFStringTable class. This class
 * automatically converts each string identifier into a integer number.
 * @{ *//* ---------------------------------------------------------------- */

/**
 * Encapsulates a string table XML file.
 * @since 1.3
 *//* --------------------------------------------------------------------- */
@interface SFStringTable : NSObject
// Properties
// @property (nonatomic, readonly) NSUInteger count;//{{{
/**
 * Retrieves the number of strings in this table.
 * @return The total number of strings found in the file or 0 when this object
 * is empty.
 * @since 1.3
 **/
@property (nonatomic, readonly) NSUInteger count;
//}}}

/** \name Designated Initializers */ //@{
// - (instancetype)initWithFile:(NSString*)fileName;//{{{
/**
 * Initializes this object with a file name.
 * @param fileName Name of the file to load. This must be the complete file
 * name, including language and country specifications if applicable. The
 * '.xml' extension can be omitted.
 * @return This object initialized.
 * @remarks If the passed \a fileName is valid the function will load it with
 * an \c SFXMLFile object. The operation is completed by passing that object
 * to the #initWithXml: initializer.
 * @since 1.3
 **/
- (instancetype)initWithFile:(NSString*)fileName;
//}}}
// - (instancetype)initWithXml:(SFXMLFile*)xmlFile;//{{{
/**
 * Initializes this instance with a XML object.
 * @param xmlFile A \c SFXMLFile object with a valid string table.
 * @return This object initialized.
 * @remarks The operation parses the file loading the strings on it. The \a
 * xmlFile object passed can be released after the operation returns.
 * @since 1.3
 **/
- (instancetype)initWithXml:(SFXMLFile*)xmlFile;
//}}}
//@}

/** \name Extractors */ //@{
// - (NSString*)string:(NSUInteger)stringID;//{{{
/**
 * Retrieves a string having the passed identifier.
 * @param stringID An integer identifying the string to retrieve.
 * @return A temporary \c NSString object with the string requested. The
 * object is valid as long as the \c SFStringTable is valid. So, the returned
 * object is not a copy but the internal reference variable. If the passed
 * identifier is not found the result is \b nil.
 * @since 1.3
 **/
- (NSString*)string:(NSUInteger)stringID;
//}}}
// - (NSString*)stringAt:(NSUInteger)index;//{{{
/**
 * Retrieves a string at the specified position.
 * @param index Zero based position of the string to return.
 * @return A temporary \c NSString object with the string requested. The
 * object is valid as long as the \c SFStringTable is valid. So, the returned
 * object is not a copy but the internal reference variable. If the passed
 * identifier is not found the result is \b nil.
 * @remarks This operation is useful if you need to iterate over all the
 * strings in the string table file.
 * @since 1.3
 **/
- (NSString*)stringAt:(NSUInteger)index;
//}}}
// - (NSUInteger)identifierAt:(NSUInteger)index;//{{{
/**
 * Retrieves the identifier of an string.
 * @param index Zero based position of the identifier to retrieve.
 * @return Identifiers must be greater than zero. When a valid position is
 * passed the identifier at that position is returned. Otherwise zero is
 * returned.
 * @since 1.3
 **/
- (NSUInteger)identifierAt:(NSUInteger)index;
//}}}
// - (NSUInteger)indexOf:(NSUInteger)stringID;//{{{
/**
 * Retrieves the index position of the specified string identifier.
 * @param stringID The string identifier to find.
 * @return The zero based position of the identifier means success. When the
 * passed \a stringID is invalid (not found) the result is the \c NSNotFound
 * constant value.
 * @since 1.3
 **/
- (NSUInteger)indexOf:(NSUInteger)stringID;
//}}}
//@}
@end

/**
 * Provides access to localized resources and files.
 * The localization is done by appending a suffix in the file names. The
 * suffixes can be an ISO 639-1 tow letter language code like "en", "fr" or
 * "pt". To make it more specific, a two letter ISO 3166-1 country code can
 * be appended with an underscore separator. For example, to localize an image
 * for French you could call it "image-fr.png". For Canada, the two letter
 * country code can be appended: "image-fr_CA.png". For images with double
 * size, the "@2x" suffix must follow the localizing identification. Same for
 * "@3x" images:
 * @code
an_english_image-en_US.png
an_english_image-en_US@2x.png
an_english_image-en_US@3x.png
 * @endcode
 * All functions that search for a file works at some level of try and error.
 * So if you know that the file is not localized you should pass \b NO to
 * functions that allow you to define when the file is localized or not. This
 * saves some time.
 *
 * \par String Tables
 *
 * Although iOS and Mac OS provides ways to localize string resources this
 * library supplies a system more flexible and user friendly. String tables
 * are simple and simpler XML files. Each string in a file has a numeric
 * identifier and its correspondent string value. The @ref sf_resources group
 * documentation has the format used for string tables.
 *
 * There are two ways to load a string table file. First, using the
 * %SFStringTable interface provides flexibility because the file doesn't need
 * to live in the resources area of the application. But doesn't provide the
 * facilities to search for localized versions. Using %SFStringTable directly
 * you can load any string table file in any place as long as you know the
 * complete file name and extension.
 *
 * Using the %SFAssets interface provides three benefits:
 * -# Just the file name, with extension, should be passed. The interface will
 *    search for the file in the resources area of the application.
 * -# The file can be localized. That means several localized versions of the
 *    file can be shipped with the application. %SFAssets will search for the
 *    file correspondent to the current locale language and country.
 * -# %SFStringTable objects are kept in cache. While they are in use by the
 *    application they are kept available by the %SFAssets interface. This
 *    means you can load the same file a hundred times and only one
 *    %SFStringTable object will be created and shared across all calls. Since
 *    a %SFStringTable object is immutable you can use it among several
 *    threads without having to synchronize access to it.
 * .
 * The cache facility is provided by two operations: #stringTable: and
 * #stringWithID:fromFile:. Both will search the cache first. When the last
 * instance of %SFStringTable object is released by the application it is
 * removed from the cache releasing all allocated memory.
 * @since 1.3
 *//* --------------------------------------------------------------------- */
@interface SFAssets : NSObject
/** \name Searching For Files */ //@{
// + (NSString *)pathForUserFile:(NSString *)fileName usingLocale:(NSLocale *)locale;//{{{
/**
 * Retrieves the absolute path for a file in user domain.
 * @param fileName The file name. Cannot be \b nil.
 * @param locale The locale to localize the file name. When this parameter is
 * \b nil the default locale will be used.
 * @return An \c NSString with the absolute file path.
 * @remarks This function checks for file to exists.
 * The \a locale argument sets the \c NSLocale instance to be used to localize
 * the file. The localization is made by appending the suffix with language
 * and country codes to the file name but before the extension. For example, if
 * the passed name is "some_file.txt" the localized version for US English
 * locale will be "some_file-en_US.txt". The function checks if this file
 * exists and, when not, it tries a variation of the name without the country
 * code. In the previous example the function will try the name
 * "some_file-en.txt". If that also fails the function will try the name
 * alone, as of passed through \a fileName argument. When all tries fails, the
 * result is \b nil.
 * @note To get the absolute path for a user file without checking for its
 * existance use the #pathForUserFile:localized: passing \b NO to the
 * \e localized parameter.
 * @since 1.3
 **/
+ (NSString *)pathForUserFile:(NSString *)fileName usingLocale:(NSLocale *)locale;
//}}}
// + (NSString *)pathForUserFile:(NSString *)fileName localized:(BOOL)localized;//{{{
/**
 * Retrieves the absolute path for a file in user domain.
 * @param fileName The file name. Cannot be \b nil.
 * @param localized Set to \b YES to search for a version of the file in the
 * default locale. Set to \b NO to get the absolute path of the file without
 * localization and without checking for its existance.
 * @return The result of this operation will vary according to the value
 * passed through \a localized parameter. When \b YES is set then the function
 * will behave just like #pathForUserFile:usingLocale:. When \b NO is set the
 * function will not check for the file existance and will never fails.
 * @since 1.3
 **/
+ (NSString *)pathForUserFile:(NSString *)fileName localized:(BOOL)localized;
//}}}
// + (NSString *)pathForResource:(NSString *)fileName usingLocale:(NSLocale *)locale;//{{{
/**
 * Gets the absolute path for a file in the application resource bundle.
 * @param fileName File name. Cannot be \b nil. Can have extension.
 * @param locale The locale to localize the file name. When this parameter is
 * \b nil the default locale will be used.
 * @return An \c NSString with the absolute file path or \b nil if the file
 * doesn't exists.
 * @remarks
 * The \a locale argument sets the \c NSLocale instance to be used to localize
 * the file. The localization is made by appending the suffix with language
 * and country codes to the file name but before the extension. For example, if
 * the passed name is "some_file.txt" the localized version for US English
 * locale will be "some_file-en_US.txt". The function checks if this file
 * exists and, when not, it tries a variation of the name without the country
 * code. In the previous example the function will try the name
 * "some_file-en.txt". If that also fails the function will try the name
 * alone, as of passed through \a fileName argument. When all tries fails, the
 * result is \b nil.
 * @since 1.3
 **/
+ (NSString *)pathForResource:(NSString *)fileName usingLocale:(NSLocale *)locale;
//}}}
// + (NSString *)pathForResource:(NSString *)fileName localized:(BOOL)localized;//{{{
/**
 * Gets the absolute path for a file in the application resource bundle.
 * @param fileName File name. Cannot be \b nil. Can have extension.
 * @param localized Set to \b YES to search for a version of the file in the
 * default locale. Set to \b NO to get the absolute path of the file without
 * localization.
 * @return An \c NSString with the absolute file path or \b nil if one was not
 * found. A file must exists for the function to return a meaningful value.
 * @since 1.3
 **/
+ (NSString *)pathForResource:(NSString *)fileName localized:(BOOL)localized;
//}}}
//@}

/** \name Loading Images */ //@{
// + (UIImage*)imageNamed:(NSString*)name;//{{{
/**
 * Loads an image from a resource.
 * @param name The image file name. If you pass just the name prefix the
 * function will search for a name matching the current language and country
 * code. If a file with the prefix, language and country code is not found,
 * the function will search for a file with only the language suffix. If that
 * doesn't work either, the fall back will be the simple name passed.
 * @return The \c UIImage object with the image requested. If a file is not
 * found, the result will be a \b nil reference.
 * @remarks If you want to load an image that is not localized use the
 * `UIImage imageNamed:` method instead.
 * @sa [UIImage Class Reference](https://developer.apple.com/library/ios/documentation/UIKit/Reference/UIImage_Class/index.html#//apple_ref/doc/uid/TP40006890)
 * @since 1.3
 **/
+ (UIImage*)imageNamed:(NSString*)name;
//}}}
//@}

/** \name Loading XML Files */ //@{
// + (SFXMLFile *)xmlFileNamed:(NSString *)name;//{{{
/**
 * Loads an XML File.
 * @param name The file name. The function will try to find a localized
 * version of the passed name appending the language and country code in the
 * string. If none file is found the function tries only the language code. If
 * that fails too the passed name is tried alone.
 * @return If a file is found the result will be a temporary SFXMLFile with
 * the file contents. Otherwise the result will be \b nil.
 * @remarks This function assumes that the file is located in the
 * application's resource bundle. To load a file in the application support
 * directory use #userXmlFileNamed: instead.
 * @since 1.3
 **/
+ (SFXMLFile *)xmlFileNamed:(NSString *)name;
//}}}
// + (SFXMLFile *)userXmlFileNamed:(NSString *)name;//{{{
/**
 * Loads an XML File.
 * @param name The file name. The function will try to find a localized
 * version of the passed name appending the language and country code in the
 * string. If none file is found the function tries only the language code. If
 * that fails too the passed name is tried alone.
 * @return If a file is found the result will be a temporary SFXMLFile with
 * the file contents. Otherwise the result will be \b nil.
 * @remarks This function assumes that the file is located in the
 * application's support directory. To load a file in the application's
 * resource use #xmlFileNamed: instead.
 * @since 1.3
 **/
+ (SFXMLFile *)userXmlFileNamed:(NSString *)name;
//}}}
//@}

/** \name String Resources Operations */ //@{
// + (SFStringTable*)stringTable:(NSString*)name;//{{{
/**
 * Loads a string table from an XML file in the resource bundle.
 * @param name The file name, with extension, without path information. The
 * file will be searched in the resource area of the application bundle.
 * @return A \c SFStringTable object. If the file is not found the function
 * will return an empty \c SFStringTable object.
 * @remarks The function will try to find a localized version of the file
 * using the selector #pathForResource:usingLocale:. The current locale will
 * be used.
 * @since 1.3
 **/
+ (SFStringTable*)stringTable:(NSString*)name;
//}}}
// + (NSString*)stringWithID:(NSUInteger)stringID fromFile:(NSString*)name;//{{{
/**
 * A shortcut operation to load a string from a string table file.
 * @param stringID The integer identifier of the string to return.
 * @param name The file name, with extension, without path information. The
 * file will be searched in the resource area of the application bundle.
 * @return A \c NSString object containing the requested string means success.
 * If the file or identifier are not found, the result will be an empty
 * \c NSString object.
 * @remarks The function will try to find a localized version of the file
 * using the selector #pathForResource:usingLocale:. The current locale will
 * be used.
 * @since 1.3
 **/
+ (NSString*)stringWithID:(NSUInteger)stringID fromFile:(NSString*)name;
//}}}
//@}
@end
///@} sf_resources
// vim:ft=objc syntax=objc.doxygen
