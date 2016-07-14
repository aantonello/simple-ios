/**
 * \file
 * Declares the SFWeakMap Objective-C interface class.
 *
 * \author  Alessandro Antonello aantonello@paralaxe.com.br
 * \date    October 22, 2014
 * \since   Simple Framework 1.3
 * \copyright
 * 2014, Paralaxe Tecnologia. All rights reserved.
 */
#import <Foundation/Foundation.h>

/**
 * \ingroup sf_general
 * Key and Value pairs in a weak reference list.
 * This interface builds a dictionary like object with a list of key and value
 * pairs in weak reference. By *weak reference* we mean that the reference
 * counting of objects added in this map are not increased. No `retain` calls
 * are made. Is the responsibility of each added object to remove it self
 * before it is deallocated.
 *
 * Although the values are not *retained* by this interface the keys are. This
 * allows for a more transparent use of this interface when an object is
 * shared by several others objects and it is recognized by a single key.
 * Users of the shared object doesn't need to know the object's key. Also they
 * don't need to know when to remove the object from the shared cache. It is
 * the responsibility of the shared object to remove it self from the cache
 * when its `dealloc` message is called. When an object is removed from the
 * cache its key is automatically removed too.
 *//* --------------------------------------------------------------------- */
@interface SFWeakMap : NSObject
// Properties
// @property (nonatomic, readonly) size_t count;//{{{
/**
 * Number of key/value pairs in this object.
 * @since 1.3
 **/
@property (nonatomic, readonly) size_t count;
//}}}
// @property (nonatomic, readonly) BOOL empty;//{{{
/**
 * Checks whether this object is empty or not.
 * @returns \b YES when there is no object in this cache. Otherwise \b NO.
 * @since 1.3
 **/
@property (nonatomic, readonly) BOOL empty;
//}}}

/** \name Designated Initializers */ //@{
// - (instancetype)initWithCapacity:(size_t)capacity;//{{{
/**
 * Initializes an instance of this interface with the specified capacity.
 * @param capacity Initial capacity of this object.
 * @returns This object initialized.
 * @since 1.3
 **/
- (instancetype)initWithCapacity:(size_t)capacity;
//}}}
//@}

/** \name Getting a Value */ //@{
// - (id)objectForKey:(id)key;//{{{
/**
 * Gets the object associated with a key.
 * @param key The key object indexing the requested object.
 * @return The value object associated with the passed key. When the \a key is
 * not found or is \b nil the result is \b nil.
 * @remarks In this operation the \a key is searched using its implementation
 * of `isEqual` message.
 * @note The returned object is not owned by this map.
 * @since 1.3
 **/
- (id)objectForKey:(id)key;
//}}}
// - (id)valueForKey:(NSString *)key;//{{{
/**
 * Gets the object associated with a key.
 * @param key The string object indexing the requested value.
 * @return The value object associated with the passed key. When the \a key is
 * not found, is \b nil or an empty string the result is \b nil.
 * @remarks In this operation the \a key is searched using its message
 * `isEqualToString:`. This follows the rules defined by \c NSDictionary
 * interface.
 * @note The returned object is not owned by this map.
 * @since 1.3
 **/
- (id)valueForKey:(NSString *)key;
//}}}
//@}

/** \name Adding Values */ //@{
// - (BOOL)setObject:(id)object forKey:(id)key;//{{{
/**
 * Add or replace a key/value pair of objects.
 * @param object The value object. This object is not *retained* in this
 * operation.
 * @param key The key object. This object is retained in this operation.
 * @return When succeeds the result is \b YES. The function will fails when \a
 * object or \a key is \b nil.
 * @remarks If the \a key is already in the cache its content will be replaced
 * by the object passed in the \a object parameter. Otherwise a new entry will
 * be added for the pair.
 * @since 1.3
 **/
- (BOOL)setObject:(id)object forKey:(id)key;
//}}}
// - (BOOL)setValue:(id)value forKey:(NSString *)key;//{{{
/**
 * Add or replace a key/value pair of objects.
 * @param value The value object. This object is not *retained* in this
 * operation.
 * @param key The key object. This object is retained in this operation.
 * @return When succeeds the result is \b YES. The function will fails when \a
 * value or \a key is \b nil and when \a key is an empty string.
 * @remarks If the \a key is already in the cache its content will be replaced
 * by the object passed in the \a value parameter. Otherwise a new entry will
 * be added for the pair.
 * @since 1.3
 **/
- (BOOL)setValue:(id)value forKey:(NSString *)key;
//}}}
//@}

/** \name Removing Key/Value Pairs */ //@{
// - (id)removeObjectForKey:(id)key;//{{{
/**
 * Remove a key/value pair from this map cache.
 * @param key The key object of the pair. It will be searched through its
 * `isEqual:` message implementation.
 * @return The value associated with the \a key object. When \a key is not
 * found or is \b nil the result will be \b nil.
 * @remarks The \a key object is also removed. Since its reference counting is
 * increased when it was added to this map the `release` message will be sent
 * to it. The value object's reference was not *retained* the it was added to
 * this map. No `release` message will be sent to it.
 * @since 1.3
 **/
- (id)removeObjectForKey:(id)key;
//}}}
// - (id)removeValueForKey:(NSString *)key;//{{{
/**
 * Remove a key/value pair from this map cache.
 * @param key The key object of the pair. It will be searched through its
 * `isEqualToString:` message implementation.
 * @return The value associated with the \a key object. When \a key is not
 * found, is an empty string or \b nil the result will be \b nil.
 * @remarks The \a key object is also removed. Since its reference counting is
 * increased when it was added to this map the `release` message will be sent
 * to it. The value object's reference was not *retained* the it was added to
 * this map. No `release` message will be sent to it.
 * @since 1.3
 **/
- (id)removeValueForKey:(NSString *)key;
//}}}
// - (void)removeAllObjects;//{{{
/**
 * Remove all key/value pairs from this map.
 * Releases the memory allocated internally and send a `release` message to
 * all *key* objects.
 * @since 1.3
 **/
- (void)removeAllObjects;
//}}}
//@}

// Class Methods
// + (instancetype)weakMap;//{{{
/**
 * Builds an instance of this interface.
 * @return The built object.
 * @since 1.3
 **/
+ (instancetype)weakMap;
//}}}
// + (instancetype)weakMapWithCapacity:(size_t)capacity;//{{{
/**
 * Builds an instance of this interface.
 * @param capacity The initial capacity of the map object.
 * @return The built object.
 * @since 1.3
 **/
+ (instancetype)weakMapWithCapacity:(size_t)capacity;
//}}}
@end
// vim:ft=objc syntax=objc.doxygen
