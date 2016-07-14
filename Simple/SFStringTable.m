/**
 * \file
 * Defines the SFStringTable class.
 *
 * \author  Alessandro Antonello aantonello@paralaxe.com.br
 * \date    October 04, 2014
 * \since   Simple Framework 1.3
 * \copyright
 * 2014, Paralaxe Tecnologia. All rights reserved.
 */
#import "SFImage.h"
#import "SFStringTable.h"
#import "SFString.h"
#import "sfdebug.h"
#import "SFWeakMap.h"

/**
 * \internal
 * @{ *//* ---------------------------------------------------------------- */
static NSString* const SF_STRINGTABLE_ELEMENT = @"stringtable";
static NSString* const SF_STRING_ELEMENT      = @"string";
static NSString* const SF_ID_ATTR             = @"id";
static NSString* const SF_VALUE_ATTR          = @"value";
static NSString* const SF_XML                 = @"xml";

typedef struct SF_STRING_TABLE {
    uintptr_t stringID;
    NSString *value;
} sf_table_t;

static SFWeakMap *s__stringTableMap = nil;
///@} internal

/* ===========================================================================
 * SFStringTable EXTENSION
 * ======================================================================== */
@interface SFStringTable () {
    sf_table_t *m_table;
    NSString   *m_fileName;
    size_t      m_count;
}
// Local Properties
// @property (nonatomic, retain) NSString* fileName;//{{{
/**
 * The original file of this string table.
 * This property is set by SFAssets interface when this SFStringTable object
 * is added to the cache. It is used to remove this SFStringTable instance
 * from the cache when it is deallocated.
 * @since 1.3
 **/
@property (nonatomic, retain) NSString* fileName;
//}}}
@end

/* ===========================================================================
 * SFStringTable IMPLEMENTATION
 * ======================================================================== */
@implementation SFStringTable
// Properties Implementation
/* property: count {{{ */
- (NSUInteger)count { return (NSUInteger)m_count; }
/* }}} property: count */

// Local Properties
/* property: fileName {{{ */
@synthesize fileName = m_fileName;
/* }}} property: fileName */

// Designated Initializers
// - (instancetype)initWithFile:(NSString*)fileName;//{{{
- (instancetype)initWithFile:(NSString*)fileName
{
    SFXMLFile *file = [[SFXMLFile alloc] initWithContentsOfFile:fileName error:NULL];
    self = [self initWithXml:file];
    [file release];

    return self;
}//}}}
// - (instancetype)initWithXml:(SFXMLFile*)xmlFile;//{{{
- (instancetype)initWithXml:(SFXMLFile*)xmlFile
{
    self = [super init];
    if (self && xmlFile)
    {
        if ([SF_STRINGTABLE_ELEMENT isEqualToString:[xmlFile elementName]])
        {
            m_count = xmlFile.numberOfChildren;
            m_table = (sf_table_t*)malloc(m_count * sizeof(sf_table_t));
            if (m_table == NULL)
                m_count = 0;
            else
            {
                SFXMLElement *element;
                NSString *value;
                uintptr_t index = 0;

                memset(m_table, 0, sizeof(sf_table_t) * m_count);

                for (size_t i = 0; i < m_count; ++i)
                {
                    element = [xmlFile elementAtIndex:i];
                    if (![SF_STRING_ELEMENT isEqualToString:element.elementName])
                        continue;

                    m_table[index].stringID = [element unsignedIntAttributeValue:SF_ID_ATTR];
                    value = [element attributeValue:SF_VALUE_ATTR];
                    if (value) m_table[index].value = [value retain];
                    index++;
                }
            }
        }
    }
    return self;
}//}}}

// Extractors
// - (NSString*)string:(NSUInteger)stringID;//{{{
- (NSString*)string:(NSUInteger)stringID
{
    for (size_t i = 0; i < m_count; ++i)
    {
        if (m_table[i].stringID == stringID)
            return m_table[i].value;
    }
    return nil;
}//}}}
// - (NSString*)stringAt:(NSUInteger)index;//{{{
- (NSString*)stringAt:(NSUInteger)index
{
    if (index >= m_count) return nil;
    return m_table[index].value;
}//}}}
// - (NSUInteger)identifierAt:(NSUInteger)index;//{{{
- (NSUInteger)identifierAt:(NSUInteger)index
{
    if (index >= m_count) return 0;
    return m_table[index].stringID;
}//}}}
// - (NSUInteger)indexOf:(NSUInteger)stringID;//{{{
- (NSUInteger)indexOf:(NSUInteger)stringID
{
    for (size_t i = 0; i < m_count; ++i)
    {
        if (stringID == m_table[i].stringID)
            return (NSUInteger)i;
    }
    return NSNotFound;
}//}}}

// NSObject: Overrides
// - (void)dealloc;//{{{
/**
 * Releases memory used by this object.
 *//* --------------------------------------------------------------------- */
- (void)dealloc
{
    if (m_fileName && s__stringTableMap)    /* We are in the cache. */
    {
        sftracef("Removing file '%s' from cache.\n", sfstr(m_fileName));
        [s__stringTableMap removeValueForKey:m_fileName];
    }

    if (m_table != NULL)
    {
        for (size_t i = 0; i < m_count; ++i) {
            [m_table[i].value release];
        }
        free(m_table);
    }
    [m_fileName release];
    [super dealloc];
}//}}}
@end

/* ===========================================================================
 * SFAssets IMPLEMENTATION
 * ======================================================================== */
@implementation SFAssets
// Local Operations
// + (NSString *)applicationSupportDirectory;//{{{
/**
 * Gets the directory for user files in the current application.
 * @note If the directory doesn't exists the function create it.
 * @since 1.3
 **/
+ (NSString *)applicationSupportDirectory
{
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSApplicationSupportDirectory,
                                                         NSUserDomainMask, YES);
    NSString* pathName = [paths objectAtIndex:0];
    NSFileManager* fileMan = [NSFileManager defaultManager];
    BOOL isDirectory = NO;

//    if ([paths count] == 1)
//        sftracef("NSSearchPathForDirectoriesInDomains() returned path:'%s'\n", sfT(pathName));
//    else
//    {
//        size_t limit = [paths count];
//        NSString *tempVal;
//
//        for (size_t i = 0; i < limit; ++i)
//        {
//            tempVal = (NSString *)[paths objectAtIndex:i];
//            sftracef("NSSearchPathForDirectoriesInDomains(%u): '%s'\n", sfT(tempVal));
//        }
//    }

    /* Create the directory if it doesn't exists. */
    if (![fileMan fileExistsAtPath:pathName isDirectory:&isDirectory])
    {
        NSError* err = nil;

        [fileMan createDirectoryAtPath:pathName withIntermediateDirectories:YES attributes:nil error:&err];
        if (err != nil) return nil;
    }
    return pathName;
}
//}}}

// Searching For Files
// + (NSString *)pathForUserFile:(NSString *)fileName usingLocale:(NSLocale *)locale;//{{{
+ (NSString *)pathForUserFile:(NSString *)fileName usingLocale:(NSLocale *)locale
{
    if (!fileName) return nil;
    if (!locale) locale = [NSLocale currentLocale];

    NSString *lang     = [locale objectForKey:NSLocaleLanguageCode];
    NSString *country  = [locale objectForKey:NSLocaleCountryCode];
    NSString *fileStem = [fileName stringByDeletingPathExtension];
    NSString *fileExt  = [fileName pathExtension];
    NSString *userPath = [SFAssets applicationSupportDirectory];
    NSFileManager *fileMan = [NSFileManager defaultManager];
    NSString *name;

    /* Try the first combination: language and country codes. */
    name = [NSString stringWithFormat:@"%@-%@_%@", fileStem, lang, country];
    name = [userPath stringByAppendingPathComponent:name];
    name = [name stringByAppendingPathExtension:fileExt];
    if ([fileMan fileExistsAtPath:name])
        return name;

    /* Try second combination: language code only. */
    name = [NSString stringWithFormat:@"%@-%@", fileStem, lang];
    name = [userPath stringByAppendingPathComponent:name];
    name = [name stringByAppendingPathExtension:fileExt];
    if ([fileMan fileExistsAtPath:name])
        return name;

    /* Last chance: file name only. */
    name = [userPath stringByAppendingPathComponent:fileName];
    if ([fileMan fileExistsAtPath:name])
        return name;

    sftracef(" | file not found: '%s'\n", sfstr(fileName));
    return nil;
}
//}}}
// + (NSString *)pathForUserFile:(NSString *)fileName localized:(BOOL)localized;//{{{
+ (NSString *)pathForUserFile:(NSString *)fileName localized:(BOOL)localized
{
    if (!fileName) return nil;
    if (localized) return [SFAssets pathForUserFile:fileName usingLocale:nil];

    NSString *userPath = [SFAssets applicationSupportDirectory];
    return [userPath stringByAppendingPathComponent:fileName];
}
//}}}
// + (NSString *)pathForResource:(NSString *)fileName usingLocale:(NSLocale *)locale;//{{{
+ (NSString *)pathForResource:(NSString *)fileName usingLocale:(NSLocale *)locale
{
    if (!fileName) return nil;
    if (!locale) locale = [NSLocale currentLocale];

    NSString *lang     = [locale objectForKey:NSLocaleLanguageCode];
    NSString *country  = [locale objectForKey:NSLocaleCountryCode];
    NSString *fileStem = [fileName stringByDeletingPathExtension];
    NSString *fileExt  = [fileName pathExtension];
    NSBundle *bundle   = [NSBundle mainBundle];
    NSString *name;

    /* Try the first combination: language and country codes. */
    name = [NSString stringWithFormat:@"%@-%@_%@", fileStem, lang, country];
    if ((name = [bundle pathForResource:name ofType:fileExt]) != nil)
        return name;

    /* Try second combination: language code only. */
    name = [NSString stringWithFormat:@"%@-%@", fileStem, lang];
    if ((name = [bundle pathForResource:name ofType:fileExt]) != nil)
        return name;

    /* Last try: file name only. */
    if ((name = [bundle pathForResource:fileStem ofType:fileExt]) != nil)
        return name;

    sftracef("Failed to find resource: '%s'\n", sfstr(fileName));
    return nil;
}
//}}}
// + (NSString *)pathForResource:(NSString *)fileName localized:(BOOL)localized;//{{{
+ (NSString *)pathForResource:(NSString *)fileName localized:(BOOL)localized
{
    if (!fileName) return nil;
    if (localized) return [SFAssets pathForResource:fileName usingLocale:nil];

    NSString *fileStem = [fileName stringByDeletingPathExtension];
    NSString *fileExt  = [fileName pathExtension];
    NSBundle *bundle   = [NSBundle mainBundle];
    NSString *name;

    if ((name = [bundle pathForResource:fileStem ofType:fileExt]) != nil)
        return name;

    sftracef(" | resource not found: '%s'\n", sfstr(fileName));
    return nil;
}
//}}}

// Loading Images
// + (UIImage*)imageNamed:(NSString*)name;//{{{
+ (UIImage*)imageNamed:(NSString*)name
{
    NSLocale *locale  = [NSLocale currentLocale];
    NSString *lang    = [locale objectForKey:NSLocaleLanguageCode];
    NSString *country = [locale objectForKey:NSLocaleCountryCode];
    NSString *_name;
    UIImage  *image;

    /* Check if we have a file with language and country codes. */
    _name = [NSString stringWithFormat:@"%@-%@_%@", name, lang, country];
    image = [UIImage imageNamed:_name];
    if (image != nil) return image;

    /* Check if there is an image with language code. */
    _name = [NSString stringWithFormat:@"%@-%@", name, lang];
    image = [UIImage imageNamed:_name];
    if (image != nil) return image;

    /* Return the default image. */
    return [UIImage imageNamed:name];
}//}}}

// Loading XML Files
// + (SFXMLFile *)xmlFileNamed:(NSString *)name;//{{{
+ (SFXMLFile *)xmlFileNamed:(NSString *)name
{
    /* Check if this name has an extension. If it does not, we append one. */
    if ([[name pathExtension] isEmpty])
        name = [name stringByAppendingPathExtension:SF_XML];

    NSString *fileName = [SFAssets pathForResource:name localized:YES];
    if (!fileName) {
        sftracef("Resource file not found: %s\n", sfstr(name));
        return nil;
    }

    SFXMLFile *xmlFile;
    NSError   *error = nil;

    xmlFile = [[SFXMLFile alloc] initWithContentsOfFile:fileName
                                                  error:&error];

    if (error != nil)
    {
        [xmlFile release];
        sftracef("Error loading file %s:\n\t%s\n\n", sfstr(name), sfstr([error description]));
        return nil;
    }
    return [xmlFile autorelease];
}
//}}}
// + (SFXMLFile *)userXmlFileNamed:(NSString *)name;//{{{
+ (SFXMLFile *)userXmlFileNamed:(NSString *)name
{
    /* Check if this name has an extension. If it does not, we append one. */
    if ([[name pathExtension] isEmpty])
        name = [name stringByAppendingPathExtension:SF_XML];

    NSString *fileName = [SFAssets pathForUserFile:name localized:YES];
    if (!fileName) return nil;

    SFXMLFile *xmlFile;
    NSError   *error = nil;

    xmlFile = [[SFXMLFile alloc] initWithContentsOfFile:fileName
                                                  error:&error];

    if (error != nil)
    {
        [xmlFile release];
        sftracef("Error loading file %s:\n\t%s\n\n", sfstr(name), sfstr([error description]));
        return nil;
    }
    return [xmlFile autorelease];
}
//}}}

// String Resources Operations
// + (SFStringTable*)stringTable:(NSString*)name;//{{{
+ (SFStringTable*)stringTable:(NSString*)name
{
    SFStringTable *table = nil;

    if (s__stringTableMap)      /* Do we have a cache? */
    {
        table = (SFStringTable*)[s__stringTableMap valueForKey:name];
        if (table)
        {
//            sftracef("Returning file '%s' from cache.\n", sfstr(name));
            return table;
        }
    }

    SFXMLFile *file = [SFAssets xmlFileNamed:name];
    if (!file) return [[SFStringTable new] autorelease];    /* Not found. */

    table = [[SFStringTable alloc] initWithXml:file];

    /* We must put this new file in the cache. */
    if (!s__stringTableMap)
        s__stringTableMap = [SFWeakMap new];

    sftracef("Putting file '%s' in the cache.\n", sfstr(name));
    [s__stringTableMap setValue:table forKey:name];
    table.fileName = name;

    return [table autorelease];
}//}}}
// + (NSString*)stringWithID:(NSUInteger)stringID fromFile:(NSString*)name;//{{{
+ (NSString*)stringWithID:(NSUInteger)stringID fromFile:(NSString*)name
{
    SFStringTable *table = [SFAssets stringTable:name];
    if (table == nil) return nil;

    return [table string:stringID];
}//}}}
@end
// vim:syntax=objc.doxygen
