/**
 * \file
 * Declares the interfaces for simple XML support.
 *
 * \author Alessandro Antonello aantonello@paralaxe.com.br
 * \date   April 27, 2014
 * \since  Simple Framework 1.2
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>

/**
 * \defgroup sf_xml Simple XML Support
 * Objetive-C interfaces to support read and write XML files.
 * @{ *//* ---------------------------------------------------------------- */

/**
 * A simple XML node.
 * This interface allow to represent a simple XML node element with attributes
 * and values. Also it permits converting values from textual representation
 * to numeric, float, hex, binary and time values.
 *//* --------------------------------------------------------------------- */
@interface SFXMLElement : NSObject
// Properties
// @property (nonatomic, copy) NSString *elementName;//{{{
/**
 * Sets or gets the name of the \c TAG element in XML file.
 * @returns An NSString with this elements name or \b nil if this element
 * hasn't a name.
 **/
@property (nonatomic, copy) NSString *elementName;
//}}}
// @property (nonatomic, readonly) SFXMLElement *parentElement;//{{{
/**
 * Gets the parent element of this element.
 * This property is ready only. When used in the root element, it returns \b
 * nil.
 * @return A SFXMLElement object parent of this element or \b nil if this
 * element hasn't a parent (e.g. is the root element).
 **/
@property (nonatomic, readonly) SFXMLElement *parentElement;
//}}}
// @property (nonatomic, readonly) NSArray *children;//{{{
/**
 * Gets the array of children SFXMLElement objects.
 * @returns An NSArray with SFXMLElement objects or \b nil if this element
 * hasn't children.
 **/
@property (nonatomic, readonly) NSArray *children;
//}}}
// @property (nonatomic, readonly) NSDictionary *attributes;//{{{
/**
 * Gets a dictionary with this element attributes.
 * @returns A NSDictionary with attributes names and values or \b nil if this
 * element hasn't any attribute.
 **/
@property (nonatomic, readonly) NSDictionary *attributes;
//}}}
// @property (nonatomic, readonly) size_t numberOfAttributes;//{{{
/**
 * Return the number of attributes in this SFXMLElement object.
 * @returns The number of attributes.
 **/
@property (nonatomic, readonly) size_t numberOfAttributes;
//}}}
// @property (nonatomic, readonly) size_t numberOfChildren;//{{{
/**
 * Returns the number of children objects of this SFXMLElement.
 * @return The number of children.
 **/
@property (nonatomic, readonly) size_t numberOfChildren;
//}}}
// @property (nonatomic, readonly) BOOL hasChildren;//{{{
/**
 * Gets a value defining if this element has children or not.
 * @returns \b YES if this element has any child. Otherwise \b NO.
 **/
@property (nonatomic, readonly) BOOL hasChildren;
//}}}

/** @name Initialization */ //@{
// - (instancetype)initWithName:(NSString *)elementName;//{{{
/**
 * Initializes the objeto setting its element name.
 * @param elementName NSString with a name for this element.
 * @returns The initialized element.
 * @since 1.3
 **/
- (instancetype)initWithName:(NSString *)elementName;
//}}}
// - (instancetype)initWithName:(NSString *)elementName attributes:(NSDictionary *)attributesDict;//{{{
/**
 * Initializes this object setting its name and initial attributes.
 * @param elementName NSString with a name for this element.
 * @param attributesDict An NSDictionary with a set of attributes names and
 * values to initializes this element.
 * @returns The initialized element.
 * @since 1.3
 **/
- (instancetype)initWithName:(NSString *)elementName attributes:(NSDictionary *)attributesDict;
//}}}
// - (instancetype)initWithName:(NSString *)elementName attributes:(NSDictionary*)attributes children:(NSArray *)elements;//{{{
/**
 * Initializes this instance with passed attributes and children.
 * @param elementName \c NSString with this element's name. Used to write the
 * element in the XML file. If \b nil the element is created without a name.
 * @param attributes \c NSDictionary with the list of attributes. Each key is
 * used as the attribute name. Each value is the attribute's value. If \b nil
 * no attribute will be added to this element.
 * @param elements \c NSArray with a list of children elements. Each object of
 * this array must be a \c SFXMLElement object. Can be \b nil. In that case no
 * child element will be added to this instance.
 * @return This object initialized.
 * @remarks This initializer can be used to build a shallow copy of an
 * element. It is a shallow copy becouse the children elements are not
 * duplicated in this new initialized instance. Only its references are
 * retained.
 * @since 1.3
 **/
- (instancetype)initWithName:(NSString *)elementName attributes:(NSDictionary*)attributes children:(NSArray *)elements;
//}}}
//@}

/** @name Setting Attributes */ //@{
// - (void)setAttribute:(NSString *)attributeName withValue:(NSString *)attributeValue;//{{{
/**
 * Add or change an attribute value.
 * @param attributeName NSString with attribute name.
 * @param attributeValue NSString with attribute value.
 * @remarks The operation will replace all invalid XML characters in the
 * attribute's value with percent entities. The replaceable characters are:
 * - **&**: ampersand.
 * - **"**: double quote.
 * - **'**: single quote.
 * - **<**: less than signal.
 * - **>**: greater than signal.
 * .
 * The operation uses NSString(SFString) category \c stringReplacingEntities
 * method.
 * @since 1.3
 **/
- (void)setAttribute:(NSString *)attributeName withValue:(NSString *)attributeValue;
//}}}
// - (void)setAttribute:(NSString *)attributeName withInt:(NSInteger)integerValue;//{{{
/**
 * Add or change an attribute value as an integer number.
 * @param attributeName NSString with attribute name.
 * @param integerValue Value for the attribute.
 * @since 1.3
 **/
- (void)setAttribute:(NSString *)attributeName withInt:(NSInteger)integerValue;
//}}}
// - (void)setAttribute:(NSString *)attributeName withUnsignedInt:(NSUInteger)integerValue;//{{{
/**
 * Add or change an attribute value as an unsigned integer number.
 * @param attributeName NSString with attribute name.
 * @param integerValue Value for the attribute.
 * @since 1.3
 **/
- (void)setAttribute:(NSString *)attributeName withUnsignedInt:(NSUInteger)integerValue;
//}}}
// - (void)setAttribute:(NSString *)attributeName withFloat:(CGFloat)floatValue;//{{{
/**
 * Add or change an attribute value as a floating point number.
 * @param attributeName NSString with attribute name.
 * @param floatValue Value for the attribute.
 * @since 1.3
 **/
- (void)setAttribute:(NSString *)attributeName withFloat:(CGFloat)floatValue;
//}}}
// - (void)setAttribute:(NSString *)attributeName withLong:(int64_t)longValue;//{{{
/**
 * Add or change an attribute value as an integer of 64 bits.
 * @param attributeName NSString with attribute name.
 * @param longValue Value for the attribute.
 * @since 1.3
 **/
- (void)setAttribute:(NSString *)attributeName withLong:(int64_t)longValue;
//}}}
// - (void)setAttribute:(NSString *)attributeName withUnsignedLong:(uint64_t)longValue;//{{{
/**
 * Add or change an attribute value as an unsigned integer of 64 bits.
 * @param attributeName NSString with attribute name.
 * @param longValue Value for the attribute.
 * @since 1.3
 **/
- (void)setAttribute:(NSString *)attributeName withUnsignedLong:(uint64_t)longValue;
//}}}
// - (void)setAttribute:(NSString *)attributeName withTime:(time_t)timeValue;//{{{
/**
 * Add or change an attribute value as a time value.
 * @param attributeName NSString with attribute name.
 * @param timeValue Value for the attribute.
 * @remarks The time value is converted to an integer of 64 bits for the
 * writting.
 * @since 1.3
 **/
- (void)setAttribute:(NSString *)attributeName withTime:(time_t)timeValue;
//}}}
//@}

/** @name Getting Attributes */ //@{
// - (BOOL)hasAttribute:(NSString *)attributeName;//{{{
/**
 * Checks the existence of an attribute by name.
 * @param attributeName NSString with the attribute's name.
 * @return \b YES if the attribute exists. Otherwise \b NO.
 * @since 1.3
 **/
- (BOOL)hasAttribute:(NSString *)attributeName;
//}}}
// - (NSString *)attributeValue:(NSString *)attributeName;//{{{
/**
 * Gets the value of an attribute.
 * @param attributeName NSString with the name of the attribute.
 * @return On success an NSString object with the attribute's value. On
 * failure, the function returns \b nil.
 * @since 1.3
 **/
- (NSString *)attributeValue:(NSString *)attributeName;
//}}}
// - (NSInteger)intAttributeValue:(NSString *)attributeName;//{{{
/**
 * Gets the value of an attribute as a signed integer.
 * @param attributeName NSString with the name of the attribute.
 * @return An integer representing the attribute's value.
 * @remarks This function will call #intAttributeValue:usingDefault: passing
 * \b 0 in the \a defaultValue parameter.
 * @since 1.3
 **/
- (NSInteger)intAttributeValue:(NSString *)attributeName;
//}}}
// - (NSUInteger)unsignedIntAttributeValue:(NSString *)attributeName;//{{{
/**
 * Gets the value of an attribute as an unsigned integer.
 * @param attributeName NSString with the name of the attribute.
 * @return An unsigned integer representing the attribute's value.
 * @remarks This function will call #unsignedIntAttributeValue:usingDefault:
 * passing \b 0 in the \a defaultValue parameter.
 * @since 1.3
 **/
- (NSUInteger)unsignedIntAttributeValue:(NSString *)attributeName;
//}}}
// - (CGFloat)floatAttributeValue:(NSString *)attributeName;//{{{
/**
 * Gets the value of an attribute as a floating point number.
 * @param attributeName NSString with the name of the attribute.
 * @return An floating point number representing the attribute's value.
 * @remarks This function will call #floatAttributeValue:usingDefault:
 * passing \b 0 in the \a defaultValue parameter.
 * @since 1.3
 **/
- (CGFloat)floatAttributeValue:(NSString *)attributeName;
//}}}
// - (int64_t)longAttributeValue:(NSString *)attributeName;//{{{
/**
 * Gets the value of an attribute as a 64 bits signed integer number.
 * @param attributeName NSString with the name of the attribute.
 * @return A 64 bit integer number representing the attribute's value.
 * @remarks This function will call #longAttributeValue:usingDefault:
 * passing \b 0 in the \a defaultValue parameter.
 * @since 1.3
 **/
- (int64_t)longAttributeValue:(NSString *)attributeName;
//}}}
// - (uint64_t)unsignedLongAttributeValue:(NSString *)attributeName;//{{{
/**
 * Gets the value of an attribute as a 64 bit unsigned integer number.
 * @param attributeName NSString with the name of the attribute.
 * @return A 64 bit unsigned integer number representing the attribute's
 * value.
 * @remarks This function will call #unsignedLongAttributeValue:usingDefault:
 * passing \b 0 in the \a defaultValue parameter.
 * @since 1.3
 **/
- (uint64_t)unsignedLongAttributeValue:(NSString *)attributeName;
//}}}
// - (time_t)timeAttributeValue:(NSString *)attributeName;//{{{
/**
 * Gets the value of an attribute as a \c time_t variable.
 * @param attributeName NSString with the name of the attribute.
 * @returns The value of the attribute named \a attributeName as a \c time_t
 * variable.
 * @note The \c time_t values are stored as unsigned long long integer
 * (uint64_t values).
 * @remarks This function will call #timeAttributeValue:usingDefault:
 * passing \b 0 in the \a defaultValue parameter.
 * @since 1.3
 **/
- (time_t)timeAttributeValue:(NSString *)attributeName;
//}}}
// - (BOOL)boolAttributeValue:(NSString *)attributeName;//{{{
/**
 * Gets a boolean value from an attribute.
 * @param attributeName NSString with attribute's name.
 * @return \b YES if the content of the attribute is recognized as a \b truth
 * value. Othersize \b NO. \c NO is also returned if the attribute doesn't
 * exist.
 * @remarks The function recognizes only 3 strings as boolean values equals \b
 * truth. They are: "true", "yes" and "1". Any other value is considered as \b
 * false.
 * @since 1.3
 **/
- (BOOL)boolAttributeValue:(NSString *)attributeName;
//}}}
// - (NSInteger)intAttributeValue:(NSString *)attributeName usingDefault:(intptr_t)defaultValue;//{{{
/**
 * Gets the value of an attribute as a signed integer number.
 * @param attributeName NSString with the name of the attribute.
 * @param defaultValue Value that will be returned when the attribute is
 * missing or could not be converted to a number.
 * @return The number within the attribute's value.
 * @since 1.3
 **/
- (NSInteger)intAttributeValue:(NSString *)attributeName usingDefault:(intptr_t)defaultValue;
//}}}
// - (NSUInteger)unsignedIntAttributeValue:(NSString *)attributeName usingDefault:(uintptr_t)defaultValue;//{{{
/**
 * Gets the value of an attribute as an unsigned integer number.
 * @param attributeName NSString with the name of the attribute.
 * @param defaultValue Value that will be returned when the attribute is
 * missing or could not be converted to a number.
 * @return The number within the attribute's value.
 * @since 1.3
 **/
- (NSUInteger)unsignedIntAttributeValue:(NSString *)attributeName usingDefault:(uintptr_t)defaultValue;
//}}}
// - (CGFloat)floatAttributeValue:(NSString *)attributeName usingDefault:(CGFloat)defaultValue;//{{{
/**
 * Gets the value of an attribute as a floating point number.
 * @param attributeName NSString with the name of the attribute.
 * @param defaultValue Value that will be returned when the attribute is
 * missing or could not be converted to a number.
 * @return The number within the attribute's value.
 * @since 1.3
 **/
- (CGFloat)floatAttributeValue:(NSString *)attributeName usingDefault:(CGFloat)defaultValue;
//}}}
// - (int64_t)longAttributeValue:(NSString *)attributeName usingDefault:(int64_t)defaultValue;//{{{
/**
 * Gets the value of an attribute as a signed 64 bit integer number.
 * @param attributeName NSString with the name of the attribute.
 * @param defaultValue Value that will be returned when the attribute is
 * missing or could not be converted to a number.
 * @return The number within the attribute's value.
 * @since 1.3
 **/
- (int64_t)longAttributeValue:(NSString *)attributeName usingDefault:(int64_t)defaultValue;
//}}}
// - (uint64_t)unsignedLongAttributeValue:(NSString *)attributeName usingDefault:(uint64_t)defaultValue;//{{{
/**
 * Gets the value of an attribute as an unsigned 64 bit integer number.
 * @param attributeName NSString with the name of the attribute.
 * @param defaultValue Value that will be returned when the attribute is
 * missing or could not be converted to a number.
 * @return The number within the attribute's value.
 * @since 1.3
 **/
- (uint64_t)unsignedLongAttributeValue:(NSString *)attributeName usingDefault:(uint64_t)defaultValue;
//}}}
// - (time_t)timeAttributeValue:(NSString *)attributeName usingDefault:(time_t)defaultValue;//{{{
/**
 * Gets the value of an attribute as time value.
 * @param attributeName NSString with the name of the attribute.
 * @param defaultValue Value that will be returned when the attribute is
 * missing or could not be converted to a \c time_t value.
 * @return The time within the attribute's value.
 * @remarks \c time_t values are stored as unsigned 64 bits numbers. So using
 * #unsignedLongAttributeValue:usingDefault: has the same result as this
 * function.
 * @since 1.3
 **/
- (time_t)timeAttributeValue:(NSString *)attributeName usingDefault:(time_t)defaultValue;
//}}}
// - (BOOL)boolAttributeValue:(NSString *)attributeName usingDefault:(BOOL)defaultValue;//{{{
/**
 * Gets a boolean value from an attribute.
 * @param attributeName NSString with attribute's name.
 * @param defaultValue The value to be returned when the attribute doesn't
 * exist.
 * @return \b YES if the content of the attribute is recognized as a \b truth
 * value. Othersize \b NO.
 * @remarks The function recognizes only 3 strings as boolean values equals \b
 * truth. They are: "true", "yes" and "1". Any other value is considered as \b
 * false.
 * @since 1.3
 **/
- (BOOL)boolAttributeValue:(NSString *)attributeName usingDefault:(BOOL)defaultValue;
//}}}
//@}

/** @name Getting Child Element */ //@{
// - (SFXMLElement *)elementAtIndex:(uintptr_t)index;//{{{
/**
 * Get an element positioned in the specified index.
 * @param index Zero based index of the position of the element to get.
 * @return The element requested or \b nil when the passed \a index is invalid
 * (out of list bounds).
 * @since 1.3
 **/
- (SFXMLElement *)elementAtIndex:(uintptr_t)index;
//}}}
// - (SFXMLElement *)elementWithName:(NSString *)elementName afterNode:(SFXMLElement *)nodeElement;//{{{
/**
 * Retrieves an element with the specified name.
 * @param elementName NSString with the element's name. If not passed, the name
 * of the element will be not important.
 * @param nodeElement An element the preceeds the requested element. Useful
 * when several siblings elements have the same name. The function gets the
 * element right after this one, them compares its name with the \a
 * elementName argument, if they match, the element will be returned.
 * Otherwise the function gets the next element and restarts. When \a
 * elementName is \b nil, the function just gets the next element and returns.
 * @returns The \c SFXMLElement found or \b nil if there is no match.
 * @since 1.3
 **/
- (SFXMLElement *)elementWithName:(NSString *)elementName afterNode:(SFXMLElement *)nodeElement;
//}}}
// - (SFXMLElement *)firstChild;//{{{
/**
 * Returns the first child element of this one.
 * @returns The element at the position zero. If this element has no children,
 * \b nil will be returned.
 * @since 1.3
 **/
- (SFXMLElement *)firstChild;
//}}}
// - (SFXMLElement *)lastChild;//{{{
/**
 * Returns the last child element of this one.
 * @returns The element in the last position of the children list or \b nil if
 * this element has no children.
 * @since 1.3
 **/
- (SFXMLElement *)lastChild;
//}}}
// - (intptr_t)indexOfElement:(SFXMLElement *)nodeElement;//{{{
/**
 * Discover the index position of an element.
 * @param nodeElement The element which position should be returned.
 * @returns The index position of the element, zero based. Or -1 if the passed
 * \a nodeElement doesn't belong in this element's children list.
 * @remarks The element is compared by its object's instance. No calls to \c
 * isEqual function will be made.
 * @since 1.3
 **/
- (intptr_t)indexOfElement:(SFXMLElement *)nodeElement;
//}}}
//@}

/** @name Setting Child Element */ //@{
// - (BOOL)appendElement:(SFXMLElement *)nodeElement;//{{{
/**
 * Appends an element to this children list.
 * @param nodeElement Element to be appended.
 * @returns \b TRUE means success. \b FALSE is only returned if \a nodeElement
 * is \b nil.
 * @since 1.3
 **/
- (BOOL)appendElement:(SFXMLElement *)nodeElement;
//}}}
// - (BOOL)insertElement:(SFXMLElement *)nodeElement atIndex:(uintptr_t)index;//{{{
/**
 * Inserts an element at the specified position.
 * @param nodeElement Element to be inserted. Cannot be \b nil.
 * @param index Zero based index of the position to insert the new element.
 * Existing elements at this position will be shifted one index further.
 * @returns \b TRUE means success. \b FALSE means failure. The operation will
 * fail if \a nodeElement is \b nil or if \a index is greater than the number
 * of child elements.
 * @since 1.3
 **/
- (BOOL)insertElement:(SFXMLElement *)nodeElement atIndex:(uintptr_t)index;
//}}}
// - (SFXMLElement *)appendElementWithName:(NSString *)elementName;//{{{
/**
 * Creates and appends a new element into this one.
 * @param elementName NSString with the name of the new element.
 * @return When succeeded the function returns the created element. Otherwise
 * the function returns \b nil.
 * @since 1.3
 **/
- (SFXMLElement *)appendElementWithName:(NSString *)elementName;
//}}}
// - (SFXMLElement *)replaceElementAtIndex:(uintptr_t)index withElement:(SFXMLElement *)node;//{{{
/**
 * Replaces an element in the specified position with the passed in new
 * element.
 * @param index Zero based index of the element that will be removed from the
 * list.
 * @param node The new element to be positioned in the passed \a index.
 * @returns SFXMLElement object removed from the list. The returned element
 * will have a temporary life time. That is, \c autorelease will be sent.
 *
 * If \a node is \b nil or \a index if invalid, the function will fail and \b
 * nil will be returned.
 * @since 1.3
 **/
- (SFXMLElement *)replaceElementAtIndex:(uintptr_t)index withElement:(SFXMLElement *)node;
//}}}
// - (SFXMLElement *)removeElementAtIndex:(uintptr_t)index;//{{{
/**
 * Remove an element at the specified index.
 * @param index Zero based position of the element to be removed.
 * @return On success the function returns the removed element. The result
 * will have a temporary life time, that is, \c autorelease will be sent to
 * it. If the \a index is invalid the function returns \b nil.
 * @since 1.3
 **/
- (SFXMLElement *)removeElementAtIndex:(uintptr_t)index;
//}}}
// - (BOOL)removeElement:(SFXMLElement *)nodeElement;//{{{
/**
 * Remove an element from this element's children list.
 * @param nodeElement SFXMLElement that should be removed.
 * @returns \b TRUE when the function succeeds. \b FALSE means the passed
 * element doesn't belong to this element's children list.
 * @since 1.3
 **/
- (BOOL)removeElement:(SFXMLElement *)nodeElement;
//}}}
//@}

/** @name Sibling Element */ //@{
// - (SFXMLElement *)siblingElement;//{{{
/**
 * Get the element right after this one in the parent's children list.
 * @return The element after this one in the parent's children list or \b nil
 * if this element has no parent or it is the last element of it's parent
 * children list.
 * @since 1.3
 **/
- (SFXMLElement *)siblingElement;
//}}}
// - (SFXMLElement *)nextSibling;//{{{
/**
 * Get the element right after this one in the parent's element list.
 * @return An \c SFXMLElement reference or \b nil when no next element exists.
 * @since 1.3
 **/
- (SFXMLElement *)nextSibling;
//}}}
// - (SFXMLElement *)prevSibling;//{{{
/**
 * Get the element right before this one in the parent's element list.
 * @return An \c SFXMLElement reference or \b nil when no previous element
 * exists.
 * @since 1.3
 **/
- (SFXMLElement *)prevSibling;
//}}}
//@}

/** @name Writting Operations */ //@{
// - (void)writeToString:(NSMutableString *)output indent:(uintptr_t)level;//{{{
/**
 * Writes the contents of this object into a string in memory.
 * @param output NSMutableString where the content of this object should be
 * stored.
 * @param level Indentation level. This value counts as 2 spaces in the
 * output.
 * @since 1.3
 **/
- (void)writeToString:(NSMutableString *)output indent:(uintptr_t)level;
//}}}
// - (void)writeToStream:(NSOutputStream *)output indent:(uintptr_t)level;//{{{
/**
 * Writes the content of this object into the passed stream.
 * @param output The stream to write to.
 * @param level Indentation level. This value counts as 2 spaces in the
 * output.
 * @since 1.3
 **/
- (void)writeToStream:(NSOutputStream *)output indent:(uintptr_t)level;
//}}}
// - (void)writeToLogUsingIndent:(uintptr_t)level;//{{{
/**
 * Writes this objects data to the logging output.
 * @param level Indentation level. This value counts as 2 spaces in the
 * output.
 * @since 1.3
 **/
- (void)writeToLogUsingIndent:(uintptr_t)level;
//}}}
//@}

// Class Methods
// + (SFXMLElement *)elementWithName:(NSString *)elementName;//{{{
/**
 * Builds an SFXMLElement object with the passed name.
 * @param elementName NSString with a name to the object.
 * @returns The created, temporary, SFXMLElement.
 * @since 1.3
 **/
+ (SFXMLElement *)elementWithName:(NSString *)elementName;
//}}}
@end

/**
 * Represents a simple XML file.
 * This interface allows to read and write XML files in a simple way. It
 * extends SFXMLElement to also represent the root element of the XML file.
 *//* --------------------------------------------------------------------- */
@interface SFXMLFile : SFXMLElement
// Properties
// @property (nonatomic, readonly) NSString *fileName;//{{{
/**
 * Gets the name of the file used to load the XML data.
 * This name is available only when the object is initialized with
 * #initWithContentsOfFile:error: or after a call to #writeToFile:.
 **/
@property (nonatomic, readonly) NSString *fileName;
//}}}

// Initialization
// - (instancetype)initWithContentsOfFile:(NSString *)fileName error:(NSError **)pError;//{{{
/**
 * Initializes this object with the contents of a file.
 * @param fileName NSString with the name of the file to read.
 * @param pError Optional pointer to a variable of \c NSError type. If the
 * function fails, this parameter will point to an \c NSError object with the
 * failure cause.
 * @returns The function always returns a valid SFXMLFile object.
 * @remarks When the file pointed by \a fileName doesn't exists the resulting
 * object will be empty. As of this the root element has no name and no
 * attributes. There will be no children in this case.
 * @note When the file pointed by \a fileName doesn't exists or cannot be read
 * the \a pError parameter will return non empty if passed.
 * @since 1.2
 **/
- (instancetype)initWithContentsOfFile:(NSString *)fileName error:(NSError **)pError;
//}}}
// - (instancetype)initWithData:(NSData *)data error:(NSError **)pError;//{{{
/**
 * Initializes this object with the passed data.
 * @param data NSData object with data to be read.
 * @param pError Optional pointer to a variable of \c NSError type. If the
 * function fails, this parameter will point to an \c NSError object with the
 * failure cause.
 * @returns The function always returns a valid SFXMLFile object.
 * @remarks When the data pointed by \a data parameter has no valid XML file
 * or has malformed XML data the result object will be empty. As of this, the
 * root element has no name and no attributes. There will be no children in
 * this case. When that happens the variable pointed by \a pError parameter
 * will return non empty.
 * @since 1.2
 **/
- (instancetype)initWithData:(NSData *)data error:(NSError **)pError;
//}}}

// Writting
// - (void)writeToLog;//{{{
/**
 * Writes the contents of this object to the logging output.
 * This operation is only useful in debug mode.
 * @since 1.2
 **/
- (void)writeToLog;
//}}}
// - (BOOL)writeToString:(NSMutableString *)output;//{{{
/**
 * Writes the contents of this file to a string.
 * @param output NSMutableString to store the contents of this file. The XML
 * data is appended to this object. If it has content it still remains.
 * @return \b TRUE on success \b FALSE on failure.
 * @remarks The XML header will not be written in this operation. That is:
 * <pre>
<?xml version="1.0" encoding="UTF-8" ?>
 * </pre>
 * Will not be written.
 *
 * The string is written using UTF-8 encoding.
 * @since 1.2
 **/
- (BOOL)writeToString:(NSMutableString *)output;
//}}}
// - (BOOL)writeToStream:(NSOutputStream *)output;//{{{
/**
 * Writes the contents of this file to a stream.
 * @param output NSOutputStream to write this object to. The XML data is
 * appended to this object.
 * @returns \b TRUE on success. \b FALSE on failure.
 * @remarks The XML header will not be written in this operation. That is:
 * <pre>
<?xml version="1.0" encoding="UTF-8" ?>
 * </pre>
 * Will not be written.
 *
 * The data is written using UTF-8 encoding.
 * @since 1.2
 **/
- (BOOL)writeToStream:(NSOutputStream *)output;
//}}}
// - (BOOL)writeToFile:(NSString *)fileName;//{{{
/**
 * Writes the contents of this object to a file.
 * @param fileName NSString with the file name to store this object's data.
 * Can be \b nil if the file to write is the same passed in the
 * initialization. If the file exists, it will be overwritten.
 * @return \b TRUE on success. \b FALSE on failure.
 * @remarks The XML header will be written in this operation. That is:
 * <pre>
<?xml version="1.0" encoding="UTF-8" ?>
 * </pre>
 * Will be written in the final file.
 *
 * The data is written using UTF-8 encoding.
 * @since 1.2
 **/
- (BOOL)writeToFile:(NSString *)fileName;
//}}}
@end
///@} sf_xml
