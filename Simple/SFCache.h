/**
 * @file
 * Declares the SFCache Objective-C interface class.
 *
 * @author  Alessandro Antonello aantonello@paralaxe.com.br
 * @date    May 10, 2014
 * @since   Simple Framework 1.2
 *
 * \copyright
 * 2014, Paralaxe Tecnologia. All rights reserved.
 */
#import <Foundation/Foundation.h>

/**
 * \ingroup sf_general
 * A cache for reusable objects.
 * A cache is a place to put reusable objects that are often allocated and
 * deallocated. Within a cache the application can request an object that is
 * already allocated improving application performance and saving memory
 * fragmentation.
 *
 * The cache can have a limit of objects inside it. When that limit is
 * reached, no objects will be added to the cache. Allowing for strict memory
 * control. See #setLimitCount:.
 *
 * \par Overrides
 *
 * This interface overrides the NSObject `init` method building a cache
 * without limit. The designated initializer #initWithCapacity: will build
 * a cache setting the capacity as the cache limit.
 *
 * This class is thread safe.
 *//* --------------------------------------------------------------------- */
@interface SFCache : NSObject
// Attributes
// - (size_t)count;//{{{
/**
 * Returns the number of objects in cache.
 **/
- (size_t)count;
//}}}

/** \name Designated Initializers */ //@{
// - (instancetype)initWithCapacity:(size_t)capacity;//{{{
/**
 * Inicializes this instance setting its capacity.
 * @param capacity The capacity of this instance, in number of objects. This
 * value also sets the limit of objects held in the cache. You can change the
 * limit by sending the #setLimitCount: message to this object defining
 * another value.
 * @return This object initialized.
 * @since 1.3
 **/
- (instancetype)initWithCapacity:(size_t)capacity;
//}}}
//@}

/** \name Cache Limit */ //@{
// - (void)setLimitCount:(size_t)count;//{{{
/**
 * Sets the cache limit.
 * @param count The maximum number of objects in the cache. If zero no limit
 * will be applyed. The default limit value is zero.
 * @remarks No object will be added to the cache whe this limit is reached.
 * When this object is initialized with the #initWithCapacity: message the
 * capacity value is used as the cache limit.
 **/
- (void)setLimitCount:(size_t)count;
//}}}
// - (size_t)limitCount;//{{{
/**
 * Retrieves the current cache limit.
 * @return The maximum number of objects in the cache. The default value for
 * this limit is zero.
 **/
- (size_t)limitCount;
//}}}
//@}

/** \name Cache Access */ //@{
// - (void)addObject:(id)object;//{{{
/**
 * Adds an object to the cache.
 * @param object Object to be added to the cache. If it is already in the
 * cache, nothing is done.
 * @remarks If a limit is imposed, by setting a value other than zero in
 * #setLimitCount: no objects above the limit are added to the cache.
 **/
- (void)addObject:(id)object;
//}}}
// - (id)anyObject;//{{{
/**
 * Retrieves an object from the cache.
 * @return An object in the cache or \b nil if the cache is empty.
 * @remarks The object is removed from the cache by this operation. The
 * resulting object is temporary, that is, \c autorelease is called on it. If
 * you doesn't intend to return the object to the cache soon, you must \c
 * retain it.
 **/
- (id)anyObject;
//}}}
//@}
@end
// vim:ft=objc syntax=objc.doxygen
