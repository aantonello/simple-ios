/**
 * \file
 * Declares the SFWeakList Objective-C interface class.
 *
 * \author  Alessandro Antonello aantonello@paralaxe.com.br
 * \date    October 21, 2014
 * \since   Simple Framework 1.3
 * \copyright
 * 2014, Paralaxe Tecnologia. All rights reserved.
 */
#import <Foundation/Foundation.h>

/**
 * \ingroup sf_general
 * A list of unowned objects.
 * The SFWeakList interface builds a list of unowned objects. This means that
 * an object added to the list don't have its reference counting incremented.
 * The `retain` message is not sent. This list allows to place objects shared
 * by several parts of an application. When the last reference is released,
 * the object instance should be removed from the list, thus, removing it from
 * memory.
 *
 * The SFWeakList interface doesn't keep track of the reference count of its
 * elements. So its a responsibility of the object it self to know that it is
 * placed in the list and that it must remove it self from the list when it
 * will be released. But that is not too hard to accomplish. What the object
 * need to do is just override the NSObject `dealloc` selector and remove it
 * self from the list when the selector is called.
 *
 * \par Overrides
 *
 * The `init` selector of NSObject is overrode to build an empty list.
 *
 * \par Implementations
 *
 * - `[NSCopying copyWithZone:(NSZone*)]`: allows for copying of the entire
 *   list. Notice that objects in this list are never \e retained by this
 *   operation.
 * - `[NSMutableCopying mutableCopyWithZone:(NSZone*)]`: does the same thing
 *   as `copyWithZone:`. This is implemented only for compatibility with Apple
 *   mutable and immutable objects.
 * - `[NSFastEnumeration countByEnumeratingWithState:objects:count:]`:
 *   allowing this list to be used in fast enumerations algorithms like:
 *   ~~~~~~~~~~~~~~~~
 *   for (id object : list)
 *       // do something with object
 *   ~~~~~~~~~~~~~~~~
 * .
 * @note No exception is thrown by this interface.
 *//* --------------------------------------------------------------------- */
@interface SFWeakList : NSObject <NSCopying, NSFastEnumeration, NSMutableCopying>
// Properties
// @property (nonatomic, readonly) size_t count;//{{{
/**
 * Number of objects in the list.
 * @since 1.3
 **/
@property (nonatomic, readonly) size_t count;
//}}}
// @property (nonatomic, readonly) BOOL empty;//{{{
/**
 * Checks whether this object is empty.
 * @returns \b YES if the list of objects in this instance is empty. Otherwise
 * \b NO.
 * @since 1.3
 **/
@property (nonatomic, readonly) BOOL empty;
//}}}

/** \name Designated Initializers */ //@{
// - (instancetype)initWithCapacity:(size_t)capacity;//{{{
/**
 * Initializes this instance setting its initial capacity.
 * @param capacity The initial capacity of the list in number of objects.
 * @returns This object initialized.
 * @since 1.3
 **/
- (instancetype)initWithCapacity:(size_t)capacity;
//}}}
// - (instancetype)initWithArray:(NSArray *)array;//{{{
/**
 * Initializes this instance with the object of an array.
 * @param array \c NSArray with objects to initialize this list.
 * @returns This object initialized.
 * @note Objects in the \a array are \b not retained in this operation.
 * @since 1.3
 **/
- (instancetype)initWithArray:(NSArray *)array;
//}}}
// - (instancetype)initWithList:(SFWeakList *)list;//{{{
/**
 * Initializes this objects instance with objects in another list.
 * @param list \c SFWeakList with objects to initialize this object's list.
 * @returns This object initialized.
 * @remarks The memory pointer is duplicated but the objects are not. The
 * objects pointed by \a list will be the same as this object.
 * @note Objects in the \a list are \b not retained in this operation.
 * @since 1.3
 **/
- (instancetype)initWithList:(SFWeakList *)list;
//}}}
//@}

/** \name Finding Objects in the List */ //@{
// - (intptr_t)indexOfObject:(id)object;//{{{
/**
 * Finds the index position of an object.
 * @param object The object which index position should be returned. The
 * comparison is made by means of `isEqual` message. For each object in the
 * list the `isEqual` message is sent passing the \a object as its parameter.
 * The first that results is \b YES will stop the search.
 * @return The index position of the object or \b -1 if it is not found or \a
 * object is \b nil.
 * @since 1.3
 **/
- (intptr_t)indexOfObject:(id)object;
//}}}
// - (intptr_t)indexOfObjectIdenticalTo:(id)object;//{{{
/**
 * Finds the index position of an object.
 * @param object The object which index position should be returned. The
 * comparison is made by reference address.
 * @return The index position of the object or \b -1 if it is not found or \a
 * object is \b nil.
 * @since 1.3
 **/
- (intptr_t)indexOfObjectIdenticalTo:(id)object;
//}}}
// - (intptr_t)indexOfObjectPassingTest:(BOOL (^)(id obj, uintptr_t index, BOOL *stop))test;//{{{
/**
 * Search of the index of an object passing in the given test.
 * @param test A //block// operation to test the objects in the list. In this
 * operation will be passed:
 * @arg \b obj The object in the list.
 * @arg \b index The index position of the passed object.
 * @arg \b stop A pointer to a \b BOOL variable. If this variable returns with
 * \b YES value the iteration will stop and the index position of the object
 * will be returned by this method. While this argument returns with \b NO the
 * iteration will continue until the end of the list.
 * @return The index position of the object that passes the test or \b -1 of
 * none object passes the test.
 * @since 1.3
 **/
- (intptr_t)indexOfObjectPassingTest:(BOOL (^)(id obj, uintptr_t index, BOOL *stop))test;
//}}}
//@}

/** \name Querying the List */ //@{
// - (BOOL)containsObject:(id)object;//{{{
/**
 * Checks whether an object lies in this list.
 * @param object The object to be checked. Cannot be \b nil.
 * @return \b YES when the passed object is in the list. \b No otherwise.
 * @remarks The operations checks the objects presence through its `isEqual`
 * selector implementation.
 * @since 1.3
 **/
- (BOOL)containsObject:(id)object;
//}}}
// - (id)firstObject;//{{{
/**
 * Retrieves the first object in the list.
 * @return The first object in the list or \b nil when the list is empty.
 * @since 1.3
 **/
- (id)firstObject;
//}}}
// - (id)lastObject;//{{{
/**
 * Last object in the list.
 * @return The last object in the list or \b nil when the list is empty.
 * @since 1.3
 **/
- (id)lastObject;
//}}}
// - (id)objectAtIndex:(uintptr_t)index;//{{{
/**
 * Object in the specified index.
 * @param index Zero based index position of the required object.
 * @return The object in the requested position or \b nil when the passed \a
 * index is invalid.
 * @since 1.3
 **/
- (id)objectAtIndex:(uintptr_t)index;
//}}}
//@}

/** \name Adding Objects */ //@{
// - (BOOL)addObject:(id)object;//{{{
/**
 * Append an object at the end of the list.
 * @param object Object to be appended. This object will not be retained in
 * this operation.
 * @returns \b YES means success. \b NO when \a object is \b nil.
 * @since 1.3
 **/
- (BOOL)addObject:(id)object;
//}}}
// - (intptr_t)insertObject:(id)object atIndex:(uintptr_t)index;//{{{
/**
 * Inserts an object in a given position.
 * @param object The object to be inserted in the list.
 * @param index Zero based index of the position where the object should be
 * inserted. If this value is greater than the number of objects in the list,
 * the \a object will be appended at the end of the list.
 * @returns The final position where the object was inserted. This can be
 * equals to \a index or another value when the object is appended at the end
 * of the list. Also the operation will return -1 if \a object was \b nil.
 * @note The \a object is not retained in this operation.
 * @since 1.3
 **/
- (intptr_t)insertObject:(id)object atIndex:(uintptr_t)index;
//}}}
//@}

/** \name Removing Objects */ //@{
// - (void)removeAllObjects;//{{{
/**
 * Clears the list removing all objects on it.
 * @remarks Objects are not released since they were not retained when put on
 * the list. All internally allocated memory will be released.
 * @since 1.3
 **/
- (void)removeAllObjects;
//}}}
// - (id)removeFirstObject;//{{{
/**
 * Removes the first object in the list.
 * @returns The removed object or \b nil if there is no objects in the list.
 * @remarks The object is not released since it was not retained when put on
 * the list.
 * @since 1.3
 **/
- (id)removeFirstObject;
//}}}
// - (id)removeLastObject;//{{{
/**
 * Removes the last object in the list.
 * @returns The removed object or \b nil if there is no objects in the list.
 * @remarks The object is not released since it was not retained when put on
 * the list.
 * @since 1.3
 **/
- (id)removeLastObject;
//}}}
// - (BOOL)removeObject:(id)object;//{{{
/**
 * Removes an object from the list.
 * @param object The object to be removed. This instance will be searched in
 * the list using its `isEqual` message implementation. If this parameter is
 * \b nil, nothing will be done.
 * @return \b YES when the object is removed. Otherwise \b NO.
 * @note The object is not released since it was not retained when put in the
 * list.
 * @since 1.3
 **/
- (BOOL)removeObject:(id)object;
//}}}
// - (BOOL)removeObjectIdenticalTo:(id)object;//{{{
/**
 * Removes an object from the list.
 * @param object The object to be removed. This instance will be searched in
 * the list through its pointer address (reference). This means that this
 * parameter must be the proper object in the list.
 * @return \b YES when the object is removed. Otherwise \b NO.
 * @note The object is not released since it was not retained when put in the
 * list.
 * @since 1.3
 **/
- (BOOL)removeObjectIdenticalTo:(id)object;
//}}}
// - (id)removeObjectAtIndex:(uintptr_t)index;//{{{
/**
 * Remove an object at the specified location.
 * @param index Zero based index of the object to be removed.
 * @return The object that was removed from the list. \b nil when \a index is
 * invalid (pointing to a location out side the list boundaries).
 * @note The object is not released since it was not retained when put in the
 * list.
 * @since 1.3
 **/
- (id)removeObjectAtIndex:(uintptr_t)index;
//}}}
//@}

/** \name Replacing Objects */ //@{
// - (void)setList:(SFWeakList *)list;//{{{
/**
 * Sets the list of objects in this instance.
 * @param list Another `SFWeakList` object with which list will replace the
 * list of this list.
 * @remarks This operation also changes the capacity of the list to match the
 * number of elements in the passed object.
 * @note References are not retained nor released by this operation.
 * @since 1.3
 **/
- (void)setList:(SFWeakList *)list;
//}}}
// - (id)replaceObjectAtIndex:(uintptr_t)index withObject:(id)object;//{{{
/**
 * Replaces an object in a given position by another object.
 * @param index Zero based index of the position of the object to be replaced.
 * @param object The object to replace the one in the list.
 * @return The object that was removed from the list. When \a index points to
 * a place out side the list or \a object is \b nil the result will be \b nil.
 * @note References are not retained nor released by this operation.
 * @since 1.3
 **/
- (id)replaceObjectAtIndex:(uintptr_t)index withObject:(id)object;
//}}}
//@}

// Class Methods
// + (instancetype)weakList;//{{{
/**
 * Builds a SFWeakList object.
 * @since 1.3
 **/
+ (instancetype)weakList;
//}}}
// + (instancetype)weakListWithCapacity:(size_t)capacity;//{{{
/**
 * Builds a SFWeakList object with an initial capacity.
 * @param capacity The initial capacity of the list in number of objects.
 * @returns The built object.
 * @since 1.3
 **/
+ (instancetype)weakListWithCapacity:(size_t)capacity;
//}}}
// + (instancetype)weakListWithArray:(NSArray *)array;//{{{
/**
 * Builds a SFWeakList object using objects in an array.
 * @param array \c NSArray with objects to initialize the SFWeakList object.
 * @returns The built object.
 * @note Objects in the \a array are \b not retained in this operation.
 * @since 1.3
 **/
+ (instancetype)weakListWithArray:(NSArray *)array;
//}}}
// + (instancetype)weakListWithList:(SFWeakList *)list;//{{{
/**
 * Builds a SFWeakList object using another SFWeakList object.
 * @param list \c SFWeakList with objects to initialize the built object's
 * list.
 * @returns The built object.
 * @remarks The memory pointer is duplicated but the objects are not. The
 * objects pointed by \a list will be the same as the returned object.
 * @note Objects in the \a list are \b not retained in this operation.
 * @since 1.3
 **/
+ (instancetype)weakListWithList:(SFWeakList *)list;
//}}}
@end
// vim:ft=objc syntax=objc.doxygen
