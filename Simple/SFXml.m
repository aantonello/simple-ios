/**
 * \file
 * Defines the interfaces to simple XML files manipulation.
 *
 * \author  Alessandro Antonello aantonello@paralaxe.com.br
 * \date    March 14, 2013
 * \since   Simple Framework 1.1
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#include <stdlib.h>
#include <unistd.h>

#import "sfstd.h"
#import "sfdebug.h"
#import "SFXml.h"
#import "SFString.h"

/* ===========================================================================
 * SFXMLElement Interface Extension
 * ======================================================================== */
@interface SFXMLElement () {
    NSMutableDictionary *m_attributes;
    NSMutableArray      *m_children;
    SFXMLElement        *m_parent;
    NSString            *m_name;
}
// Private Properties
@property (nonatomic, readwrite) SFXMLElement *parentElement;

// Private Initialization
// - (instancetype)initWithName:(NSString *)elementName attributes:(NSDictionary *)attributesDict parent:(SFXMLElement *)parentElement;//{{{
/**
 * Initializes this object setting its name and initial attributes.
 * @param elementName NSString with a name for this element.
 * @param attributesDict An NSDictionary with a set of attributes names and
 * values to initializes this element.
 * @param parentElement The SFXMLElement object acting as parent of this
 * object.
 * @returns The initialized element.
 * @since 1.3
 **/
- (instancetype)initWithName:(NSString *)elementName
                  attributes:(NSDictionary *)attributesDict
                      parent:(SFXMLElement *)parentElement;
//}}}

// Attributes Rewrite
// - (void)setAttributes:(NSDictionary *)attributesDict;//{{{
/**
 * Changes the set of attributes of this XML element.
 * @param attributesDict NSDictionary with new set of attributes. This set
 * will completely overwrite the current set, if there is one.
 * @since 1.3
 **/
- (void)setAttributes:(NSDictionary *)attributesDict;
//}}}
@end
/* ===========================================================================
 * SFXMLElement Implementation {{{
 * ======================================================================== */
@implementation SFXMLElement
/* ---------------------------------------------------------------------------
 * Properties
 * ------------------------------------------------------------------------ */

// @property (nonatomic, copy) NSString *elementName;//{{{
@synthesize elementName = m_name;
//}}}
// @property (nonatomic, readonly) SFXMLElement *parentElement;//{{{
@synthesize parentElement = m_parent;
//}}}
// @property (nonatomic, readonly) NSArray *children;//{{{
- (NSArray *)children { return m_children; }
//}}}
// @property (nonatomic, readonly) NSDictionary *attributes;//{{{
- (NSDictionary *)attributes { return m_attributes; }
//}}}
// @property (nonatomic, readonly) size_t numberOfAttributes;//{{{
- (uintptr_t)numberOfAttributes {
    return ((m_attributes) ? [m_attributes count] : 0);
}
//}}}
// @property (nonatomic, readonly) size_t numberOfChildren;//{{{
- (uintptr_t)numberOfChildren {
    return ((m_children) ? [m_children count] : 0);
}
//}}}
// @property (nonatomic, readonly) BOOL hasChildren;//{{{
- (BOOL)hasChildren { return (BOOL)(self.numberOfChildren > 0); }
//}}}

/* ---------------------------------------------------------------------------
 * NSObject: Overrides
 * ------------------------------------------------------------------------ */

// - (void)dealloc//{{{
- (void)dealloc
{
    [m_name release];
    [m_children release];
    [m_attributes release];
    [super dealloc];
}
//}}}

/* ---------------------------------------------------------------------------
 * Public: Initialization
 * ------------------------------------------------------------------------ */

// - (instancetype)initWithName:(NSString *)elementName//{{{
- (instancetype)initWithName:(NSString *)elementName
{
    return [self initWithName:elementName attributes:nil parent:nil];
}
//}}}
// - (instancetype)initWithName:(NSString *)elementName attributes:(NSDictionary *)attributesDict//{{{
- (instancetype)initWithName:(NSString *)elementName attributes:(NSDictionary *)attributesDict
{
    return [self initWithName:elementName attributes:attributesDict parent:nil];
}
//}}}
// - (instancetype)initWithName:(NSString *)elementName attributes:(NSDictionary*)attributes children:(NSArray *)elements;//{{{
- (instancetype)initWithName:(NSString *)elementName attributes:(NSDictionary*)attributes
                    children:(NSArray *)elements
{
    self = [self initWithName:elementName attributes:attributes parent:nil];
    if (self && elements)
    {
        m_children = [[NSMutableArray alloc] initWithCapacity:[elements count]];
        [m_children setArray:elements];
    }
    return self;
}
//}}}

/* ---------------------------------------------------------------------------
 * Private: Initialization
 * ------------------------------------------------------------------------ */

// - (instancetype)initWithName:(NSString *)elementName attributes:(NSDictionary *)attributesDict parent:(SFXMLElement *)parentElement;//{{{
- (instancetype)initWithName:(NSString *)elementName
                  attributes:(NSDictionary *)attributesDict
                      parent:(SFXMLElement *)parentElement
{
    self = [self init];
    if (self)
    {
        if (elementName) {
            m_name = [[NSString alloc] initWithString:elementName];
        }

        if (attributesDict) {
            m_attributes = [NSMutableDictionary new];
            [m_attributes setDictionary:attributesDict];
        }

        if (parentElement) {
            m_parent = parentElement;
            [parentElement appendElement:self];
        }
    }
    return self;
}
//}}}

/* ---------------------------------------------------------------------------
 * Private: Attribute Rewrite
 * ------------------------------------------------------------------------ */

// - (void)setAttributes:(NSDictionary *)attributesDict;//{{{
- (void)setAttributes:(NSDictionary *)attributesDict
{
    if (!m_attributes) m_attributes = [NSMutableDictionary new];
    [m_attributes setDictionary:attributesDict];
}
//}}}

/* ---------------------------------------------------------------------------
 * Public: Writting Operations
 * ------------------------------------------------------------------------ */

// - (void)writeToString:(NSMutableString *)output indent:(uintptr_t)level//{{{
- (void)writeToString:(NSMutableString *)output indent:(uintptr_t)level
{
    intptr_t indent = (intptr_t)(2 * level);
    NSString *padding = [@" " stringByPaddingToLength:indent withString:@" " startingAtIndex:0];

    [output appendFormat:@"%@<%@", padding, m_name];

    if ([self numberOfAttributes] > 0)
    {
        NSArray *keys = [m_attributes allKeys];
        size_t  limit = [keys count];
        NSString *name;
        NSString *value;

        for (size_t u = 0; u < limit; u++)
        {
            name  = (NSString*)[keys objectAtIndex:u];
            value = (NSString*)[m_attributes valueForKey:name];

            [output appendFormat:@" %@=\"%@\"", name, [value stringReplacingEntities]];
        }
    }

    if (![self hasChildren])
        [output appendString:@"/>\n"];
    else
    {
        size_t count = [self numberOfChildren];
        SFXMLElement *childElement;

        [output appendString:@">\n"];

        for (size_t x = 0; x < count; x++)
        {
            childElement = (SFXMLElement *)[m_children objectAtIndex:x];
            [childElement writeToString:output indent:(level + 1)];
        }

        [output appendFormat:@"%@</%@>\n", padding, m_name];
    }
}
//}}}
// - (void)writeToStream:(NSOutputStream *)output indent:(uintptr_t)level//{{{
- (void)writeToStream:(NSOutputStream *)output indent:(uintptr_t)level
{
    intptr_t indent = (intptr_t)(2 * level);
    NSString *padding = [@" " stringByPaddingToLength:indent withString:@" " startingAtIndex:0];
    NSMutableString *buffer = [[NSMutableString alloc] initWithCapacity:128];

    [buffer appendFormat:@"%@<%@", padding, m_name];
    if ([self numberOfAttributes] > 0)
    {
        [m_attributes enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
            NSString *value = (NSString *)obj;
            [buffer appendFormat:@" %@=\"%@\"", key, [value stringReplacingEntities]];
        }];
    }

    if (![self hasChildren])
        [buffer appendString:@"/>\n"];
    else
        [buffer appendString:@">\n"];

    size_t   byteLen = [buffer lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    const char *data = [buffer utf8Array];

    [output write:(const uint8_t*)data maxLength:byteLen];
    [buffer release];

    if ([self hasChildren])
    {
        size_t count = [self numberOfChildren];
        SFXMLElement *child;

        for (size_t x = 0; x < count; x++)
        {
            child = (SFXMLElement*)[m_children objectAtIndex:x];
            [child writeToStream:output indent:(level + 1)];
        }

        buffer = [[NSMutableString alloc] initWithCapacity:(indent + [m_name length] + 4)];
        [buffer appendFormat:@"%@</%@>\n", padding, m_name];

        byteLen = [buffer lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
        data    = [buffer utf8Array];

        [output write:(const uint8_t*)data maxLength:byteLen];
        [buffer release];
    }
}
//}}}
// - (void)writeToLogUsingIndent:(uintptr_t)level//{{{
- (void)writeToLogUsingIndent:(uintptr_t)level
{
    intptr_t indent = (intptr_t)(2 * level);
    NSString *padding = [@" " stringByPaddingToLength:indent withString:@" " startingAtIndex:0];
    NSMutableString *buffer = [[NSMutableString alloc] initWithCapacity:128];

    [buffer appendFormat:@"%@<%@", padding, m_name];
    if ([self numberOfAttributes] > 0)
    {
        [m_attributes enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
            NSString *value = (NSString *)obj;
            [buffer appendFormat:@" %@=\"%@\"", key, [value stringReplacingEntities]];
        }];
    }

    if (![self hasChildren])
        [buffer appendString:@"/>\n"];
    else
        [buffer appendString:@">\n"];

    sfdebug("%s", [buffer utf8Array]);
    [buffer release];

    if ([self hasChildren])
    {
        size_t count = [self numberOfChildren];
        SFXMLElement *child;

        for (size_t x = 0; x < count; x++)
        {
            child = (SFXMLElement*)[m_children objectAtIndex:x];
            [child writeToLogUsingIndent:(level + 1)];
        }

        buffer = [[NSMutableString alloc] initWithCapacity:(indent + [m_name length] + 4)];
        [buffer appendFormat:@"%@</%@>\n", padding, m_name];

        sfdebug("%s", [buffer utf8Array]);
        [buffer release];
    }
}
//}}}

/* ---------------------------------------------------------------------------
 * Public: Setting Attributes
 * ------------------------------------------------------------------------ */

// - (void)setAttribute:(NSString *)attributeName withValue:(NSString *)attributeValue//{{{
- (void)setAttribute:(NSString *)attributeName withValue:(NSString *)attributeValue
{
    if (!m_attributes)
        m_attributes = [NSMutableDictionary new];

    [m_attributes setValue:attributeValue forKey:attributeName];
}
//}}}
// - (void)setAttribute:(NSString *)attributeName withInt:(NSInteger)integerValue//{{{
- (void)setAttribute:(NSString *)attributeName withInt:(NSInteger)integerValue
{
    [self setAttribute:attributeName withValue:[NSString stringWithFormat:@"%ld", (long)integerValue]];
}
//}}}
// - (void)setAttribute:(NSString *)attributeName withUnsignedInt:(NSUInteger)integerValue//{{{
- (void)setAttribute:(NSString *)attributeName withUnsignedInt:(NSUInteger)integerValue
{
    [self setAttribute:attributeName withValue:[NSString stringWithFormat:@"%lu", (unsigned long)integerValue]];
}
//}}}
// - (void)setAttribute:(NSString *)attributeName withFloat:(CGFloat)floatValue//{{{
- (void)setAttribute:(NSString *)attributeName withFloat:(CGFloat)floatValue
{
    [self setAttribute:attributeName withValue:[NSString stringWithFormat:@"%01.6f", floatValue]];
}
//}}}
// - (void)setAttribute:(NSString *)attributeName withLong:(int64_t)longValue//{{{
- (void)setAttribute:(NSString *)attributeName withLong:(int64_t)longValue
{
    [self setAttribute:attributeName withValue:[NSString stringWithFormat:@"%lld", longValue]];
}
//}}}
// - (void)setAttribute:(NSString *)attributeName withUnsignedLong:(uint64_t)longValue//{{{
- (void)setAttribute:(NSString *)attributeName withUnsignedLong:(uint64_t)longValue
{
    [self setAttribute:attributeName withValue:[NSString stringWithFormat:@"%llu", longValue]];
}
//}}}
// - (void)setAttribute:(NSString *)attributeName withTime:(time_t)timeValue//{{{
- (void)setAttribute:(NSString *)attributeName withTime:(time_t)timeValue
{
    [self setAttribute:attributeName withUnsignedLong:(uint64_t)timeValue];
}
//}}}

/* ---------------------------------------------------------------------------
 * Public: Getting Attributes
 * ------------------------------------------------------------------------ */

// - (BOOL)hasAttribute:(NSString *)attributeName//{{{
- (BOOL)hasAttribute:(NSString *)attributeName
{
    if (!m_attributes) return NO;
    return ([m_attributes objectForKey:attributeName] != nil);
}
//}}}
// - (NSString *)attributeValue:(NSString *)attributeName//{{{
- (NSString *)attributeValue:(NSString *)attributeName
{
    if (!m_attributes) return nil;

    return (NSString *)[m_attributes valueForKey:attributeName];
}
//}}}
// - (NSInteger)intAttributeValue:(NSString *)attributeName//{{{
- (NSInteger)intAttributeValue:(NSString *)attributeName
{
    return [self intAttributeValue:attributeName usingDefault:0];
}
//}}}
// - (NSUInteger)unsignedIntAttributeValue:(NSString *)attributeName//{{{
- (NSUInteger)unsignedIntAttributeValue:(NSString *)attributeName
{
    return [self unsignedIntAttributeValue:attributeName usingDefault:0];
}
//}}}
// - (CGFloat)floatAttributeValue:(NSString *)attributeName//{{{
- (CGFloat)floatAttributeValue:(NSString *)attributeName
{
    return [self floatAttributeValue:attributeName usingDefault:0.0];
}
//}}}
// - (int64_t)longAttributeValue:(NSString *)attributeName//{{{
- (int64_t)longAttributeValue:(NSString *)attributeName
{
    return [self longAttributeValue:attributeName usingDefault:0];
}
//}}}
// - (uint64_t)unsignedLongAttributeValue:(NSString *)attributeName//{{{
- (uint64_t)unsignedLongAttributeValue:(NSString *)attributeName
{
    return [self unsignedLongAttributeValue:attributeName usingDefault:0];
}
//}}}
// - (time_t)timeAttributeValue:(NSString *)attributeName//{{{
- (time_t)timeAttributeValue:(NSString *)attributeName
{
    return [self timeAttributeValue:attributeName usingDefault:0];
}
//}}}
// - (BOOL)boolAttributeValue:(NSString *)attributeName//{{{
- (BOOL)boolAttributeValue:(NSString *)attributeName
{
    return [self boolAttributeValue:attributeName usingDefault:NO];
}
//}}}
// - (NSInteger)intAttributeValue:(NSString *)attributeName usingDefault:(intptr_t)defaultValue//{{{
- (NSInteger)intAttributeValue:(NSString *)attributeName usingDefault:(intptr_t)defaultValue
{
    NSString *attributeValue = [self attributeValue:attributeName];

    if (!attributeValue) return defaultValue;

    char *tail = NULL;
    const char *value = [attributeValue utf8Array];
    NSInteger result;

    errno = 0;
    result = strtol(value, &tail, 0);
    if ((tail != NULL) && ((*tail) != '\0') && (errno != 0))
        return defaultValue;

    return result;
}
//}}}
// - (NSUInteger)unsignedIntAttributeValue:(NSString *)attributeName usingDefault:(uintptr_t)defaultValue//{{{
- (NSUInteger)unsignedIntAttributeValue:(NSString *)attributeName usingDefault:(uintptr_t)defaultValue
{
    return [self intAttributeValue:attributeName usingDefault:defaultValue];
}
//}}}
// - (CGFloat)floatAttributeValue:(NSString *)attributeName usingDefault:(CGFloat)defaultValue//{{{
- (CGFloat)floatAttributeValue:(NSString *)attributeName usingDefault:(CGFloat)defaultValue
{
    NSString *attributeValue = [self attributeValue:attributeName];

    if (!attributeValue) return defaultValue;

    return (CGFloat)[attributeValue doubleValue];
}
//}}}
// - (int64_t)longAttributeValue:(NSString *)attributeName usingDefault:(int64_t)defaultValue//{{{
- (int64_t)longAttributeValue:(NSString *)attributeName usingDefault:(int64_t)defaultValue
{
    NSString *attributeValue = [self attributeValue:attributeName];

    if (!attributeValue) return defaultValue;

    char *tail = NULL;
    const char *value = [attributeValue utf8Array];
    int64_t result;

    errno = 0;
    result = strtoll(value, &tail, 0);
    if ((tail != NULL) && ((*tail) != '\0') && (errno != 0))
        return defaultValue;

    return result;
}
//}}}
// - (uint64_t)unsignedLongAttributeValue:(NSString *)attributeName usingDefault:(uint64_t)defaultValue//{{{
- (uint64_t)unsignedLongAttributeValue:(NSString *)attributeName usingDefault:(uint64_t)defaultValue
{
    NSString *attributeValue = [self attributeValue:attributeName];

    if (!attributeValue) return defaultValue;

    char *tail = NULL;
    const char *value = [attributeValue utf8Array];
    uint64_t result;

    errno = 0;
    result = strtoull(value, &tail, 0);
    if ((tail != NULL) && ((*tail) != '\0') && (errno != 0))
        return defaultValue;

    return result;
}
//}}}
// - (time_t)timeAttributeValue:(NSString *)attributeName usingDefault:(time_t)defaultValue//{{{
- (time_t)timeAttributeValue:(NSString *)attributeName usingDefault:(time_t)defaultValue
{
    return (time_t)[self unsignedLongAttributeValue:attributeName usingDefault:(uint64_t)defaultValue];
}
//}}}
// - (BOOL)boolAttributeValue:(NSString *)attributeName usingDefault:(BOOL)defaultValue//{{{
- (BOOL)boolAttributeValue:(NSString *)attributeName usingDefault:(BOOL)defaultValue
{
    NSString *value = [self attributeValue:attributeName];
    if (!value) return defaultValue;

    return ([value isSameAsString:@"true"] || [value isSameAsString:@"yes"]
            || [value isSameAsString:@"1"]);
}
//}}}

/* ---------------------------------------------------------------------------
 * Public: Getting Child Element
 * ------------------------------------------------------------------------ */

// - (SFXMLElement *)elementAtIndex:(uintptr_t)index//{{{
- (SFXMLElement *)elementAtIndex:(uintptr_t)index
{
    if (!m_children) return nil;

    @try { return (SFXMLElement*)[m_children objectAtIndex:index]; }
    @catch (NSException *ex) {
        /* Don't bother with this kind of exception. */
        return nil;
    }
}
//}}}
// - (SFXMLElement *)elementWithName:(NSString *)elementName afterNode:(SFXMLElement *)nodeElement//{{{
- (SFXMLElement *)elementWithName:(NSString *)elementName afterNode:(SFXMLElement *)nodeElement
{
    intptr_t index = ([self indexOfElement:nodeElement] + 1);

    if (!elementName) {
        return [self elementAtIndex:index];
    }

    SFXMLElement *element;
    size_t limit = self.numberOfChildren;

    for (size_t i = index; i < limit; ++i)
    {
        element = (SFXMLElement *)[m_children objectAtIndex:i];
        if ([elementName isEqualToString:element.elementName])
            return element;
    }
    return nil;
}
//}}}
// - (SFXMLElement *)firstChild//{{{
- (SFXMLElement *)firstChild
{
    return [self elementAtIndex:0];
}
//}}}
// - (SFXMLElement *)lastChild//{{{
- (SFXMLElement *)lastChild
{
    if (!m_children) return nil;
    return (SFXMLElement*)[m_children lastObject];
}
//}}}
// - (intptr_t)indexOfElement:(SFXMLElement *)nodeElement//{{{
- (intptr_t)indexOfElement:(SFXMLElement *)nodeElement
{
    if (!m_children) return -1;

    uintptr_t index = [m_children indexOfObjectIdenticalTo:nodeElement];

    return ((index == NSNotFound) ? -1 : (intptr_t)index);
}
//}}}

/* ---------------------------------------------------------------------------
 * Public: Setting Child Element
 * ------------------------------------------------------------------------ */

// - (BOOL)appendElement:(SFXMLElement *)nodeElement//{{{
- (BOOL)appendElement:(SFXMLElement *)nodeElement
{
    if (!nodeElement) return FALSE;
    if (!m_children) m_children = [NSMutableArray new];

    [m_children addObject:nodeElement];
    nodeElement.parentElement = self;
    return TRUE;
}
//}}}
// - (BOOL)insertElement:(SFXMLElement *)nodeElement atIndex:(uintptr_t)index//{{{
- (BOOL)insertElement:(SFXMLElement *)nodeElement atIndex:(uintptr_t)index
{
    if ((!nodeElement) || (index > self.numberOfChildren))
        return FALSE;

    if (!m_children) return [self appendElement:nodeElement];

    @try { [m_children insertObject:nodeElement atIndex:index]; }
    @catch (NSException *ex) {
        /* Ignored exception. */
        return FALSE;
    }
    nodeElement.parentElement = self;
    return TRUE;
}
//}}}
// - (SFXMLElement *)appendElementWithName:(NSString *)elementName//{{{
- (SFXMLElement *)appendElementWithName:(NSString *)elementName
{
    SFXMLElement *nodeElement = [SFXMLElement elementWithName:elementName];

    if ([self appendElement:nodeElement])
        return nodeElement;

    return nil;
}
//}}}
// - (SFXMLElement *)replaceElementAtIndex:(uintptr_t)index withElement:(SFXMLElement *)node//{{{
- (SFXMLElement *)replaceElementAtIndex:(uintptr_t)index withElement:(SFXMLElement *)node
{
    if (!m_children || !node) return nil;

    SFXMLElement *element = [self elementAtIndex:index];
    if (!element) return nil;

    [element retain];

    @try { [m_children replaceObjectAtIndex:index withObject:node]; }
    @catch (NSException *ex) {
        [element release];      /* Still in the array. */
        return nil;
    }

    element.parentElement = nil;
    node.parentElement = self;

    return [element autorelease];
}
//}}}
// - (SFXMLElement *)removeElementAtIndex:(uintptr_t)index//{{{
- (SFXMLElement *)removeElementAtIndex:(uintptr_t)index
{
    SFXMLElement *element = [self elementAtIndex:index];
    if (!element) return nil;

    [element retain];
    [m_children removeObject:element];

    element.parentElement = nil;
    return [element autorelease];
}
//}}}
// - (BOOL)removeElement:(SFXMLElement *)nodeElement//{{{
- (BOOL)removeElement:(SFXMLElement *)nodeElement
{
    if ([self indexOfElement:nodeElement] < 0)
        return FALSE;

    nodeElement.parentElement = nil;
    [m_children removeObject:nodeElement];
    return TRUE;
}
//}}}

/* ---------------------------------------------------------------------------
 * Public: Sibling Element
 * ------------------------------------------------------------------------ */

// - (SFXMLElement *)siblingElement//{{{
- (SFXMLElement *)siblingElement
{
    if (!m_parent) return nil;
    return [m_parent elementWithName:nil afterNode:self];
}
//}}}
// - (SFXMLElement *)nextSibling;//{{{
- (SFXMLElement *)nextSibling
{
    if (!m_parent) return nil;
    intptr_t index = [m_parent indexOfElement:self];

    if (index < 0) return nil;
    return [m_parent elementAtIndex:(index + 1)];
}
//}}}
// - (SFXMLElement *)prevSibling;//{{{
- (SFXMLElement *)prevSibling
{
    if (!m_parent) return nil;
    intptr_t index = [m_parent indexOfElement:self];

    if (index <= 0) return nil;
    return [m_parent elementAtIndex:(index - 1)];
}
//}}}

/* ---------------------------------------------------------------------------
 * Public: Class Methods
 * ------------------------------------------------------------------------ */

// + (SFXMLElement *)elementWithName:(NSString *)elementName//{{{
+ (SFXMLElement *)elementWithName:(NSString *)elementName
{
    SFXMLElement *element = [[SFXMLElement alloc] initWithName:elementName];
    return [element autorelease];
}
//}}}

@end
/* SFXMLElement Implementation }}}
 * ======================================================================== */

/* ===========================================================================
 * SFXMLFile Interface Extension
 * ======================================================================== */
@interface SFXMLFile () < NSXMLParserDelegate > {
    NSString *m_fileName;
}
@end

/* ===========================================================================
 * SFXMLFILE Implementation
 * ======================================================================== */
@implementation SFXMLFile
/* ------------------------------------------------------------------------ */
/* name Properties *//*{{{*/
/* ------------------------------------------------------------------------ */

/**
 * Gets the name of the file used to load the XML data.
 *//* --------------------------------------------------------------------- */
@synthesize fileName = m_fileName;
// Properties /*}}}*/
/* ------------------------------------------------------------------------ */
/*! \name NSObject Overrides *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */

/**
 * Releases memory used by this object.
 *//* --------------------------------------------------------------------- */
- (void)dealloc
{
    [m_fileName release];
    [super dealloc];
}
///@} NSObject Overrides /*}}}*/
/* ------------------------------------------------------------------------ */
/*! \name Initialization *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */
// - (instancetype)initWithContentsOfFile:(NSString *)fileName error:(NSError **)pError//{{{
- (instancetype)initWithContentsOfFile:(NSString *)fileName error:(NSError **)pError
{
    NSData *data = [NSData dataWithContentsOfFile:fileName options:NSDataReadingMappedIfSafe error:pError];

    if (!data)
        return [super init];
    else
    {
        self = [self initWithData:data error:pError];
        if (self) m_fileName = [fileName retain];

        return self;
    }
}
//}}}
// - (instancetype)initWithData:(NSData *)data error:(NSError **)pError//{{{
- (instancetype)initWithData:(NSData *)data error:(NSError **)pError
{
    self = [super init];
    if (self)
    {
        NSError *error = nil;
        NSXMLParser *parser;

        parser = [[NSXMLParser alloc] initWithData:data];

        [parser setDelegate:self];
        [parser setShouldProcessNamespaces:NO];
        [parser setShouldReportNamespacePrefixes:NO];
        [parser setShouldResolveExternalEntities:NO];
        [parser parse];

        error = [parser parserError];
        if (error != nil) {
            if (pError != NULL) *pError = error;
        }
        [parser release];
    }
    return self;
}
//}}}

///@} Initialization /*}}}*/
/* ------------------------------------------------------------------------ */
/*! \name Writting *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */

// - (void)writeToLog//{{{
- (void)writeToLog
{
    [self writeToLogUsingIndent:0];
}
//}}}
// - (BOOL)writeToString:(NSMutableString *)output//{{{
- (BOOL)writeToString:(NSMutableString *)output
{
    [super writeToString:output indent:0];
    return TRUE;
}
//}}}
// - (BOOL)writeToStream:(NSOutputStream *)output//{{{
- (BOOL)writeToStream:(NSOutputStream *)output
{
    [super writeToStream:output indent:0];
    return TRUE;
}
//}}}
// - (BOOL)writeToFile:(NSString *)fileName//{{{
- (BOOL)writeToFile:(NSString *)fileName
{
    NSOutputStream *stream;

    if (fileName && ([fileName length] > 0))
    {
        [m_fileName release];
        m_fileName = [[NSString alloc] initWithString:fileName];
    }

    stream = [[NSOutputStream alloc] initToFileAtPath:m_fileName append:NO];

    [stream open];

    NSString *header = @"<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
    size_t byteLen   = [header lengthOfBytesUsingEncoding:NSUTF8StringEncoding];
    const char *data = [header utf8Array];

    [stream write:(const uint8_t *)data maxLength:byteLen];
    [self writeToStream:stream];

    [stream close];
    [stream release];

    return TRUE;
}
//}}}
///@} Writting /*}}}*/
/* ------------------------------------------------------------------------ */
/*! \name NSXMLParserDelegate Implementation *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */

/**
 * Sent by the parser object to the delegate when it begins parsing a
 * document.
 * @param parser A parser object.
 *//* --------------------------------------------------------------------- */
- (void)parserDidStartDocument:(NSXMLParser *)parser
{
    self.parentElement = nil;
}

/**
 * Sent by a parser object to its delegate when it encounters a start tag for
 * a given element.
 * @param parser A parser object.
 * @param elementName A string that is the name of an element (in its start
 * tag).
 * @param namespaceURI If namespace processing is turned on, contains the URI
 * for the current namespace as a string object.
 * @param qualifiedName If namespace processing is turned on, contains the
 * qualified name for the current namespace as a string object.
 * @param attributeDict A dictionary that contains any attributes associated
 * with the element. Keys are the names of attributes, and values are
 * attribute values.
 *//* --------------------------------------------------------------------- */
- (void)parser:(NSXMLParser *)parser didStartElement:(NSString *)elementName
  namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qualifiedName
    attributes:(NSDictionary *)attributeDict
{
    if (self.parentElement)
    {
        SFXMLElement *element = [[SFXMLElement alloc] initWithName:elementName
                                                        attributes:attributeDict
                                                            parent:self.parentElement];
        self.parentElement = element;
        [element release];
    }
    else
    {
        /* Root element (our selves). */
        self.elementName = elementName;
        [super setAttributes:attributeDict];
        self.parentElement = self;
    }
}

/**
 * Sent by a parser object to its delegate when it encounters an end tag for a
 * specific element.
 * @param parser A parser object.
 * @param elementName A string that is the name of an element (in its end
 * tag).
 * @param namespaceURI If namespace processing is turned on, contains the URI
 * for the current namespace as a string object.
 * @param qName If namespace processing is turned on, contains the qualified
 * name for the current namespace as a string object.
 *//* --------------------------------------------------------------------- */
- (void)parser:(NSXMLParser *)parser didEndElement:(NSString *)elementName
  namespaceURI:(NSString *)namespaceURI qualifiedName:(NSString *)qName
{
    if (self.parentElement)
        self.parentElement = [[self parentElement] parentElement];
}

/**
 * Sent by the parser object to the delegate when it has successfully
 * completed parsing.
 * @param parser A parser object.
 *//* --------------------------------------------------------------------- */
- (void)parserDidEndDocument:(NSXMLParser *)parser
{
    self.parentElement = nil;
}
///@} NSXMLParserDelegate Implementation /*}}}*/
/* ------------------------------------------------------------------------ */
@end
