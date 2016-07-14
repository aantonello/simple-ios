/**
 * \file
 * Defines the SFWeakMap class.
 *
 * \author  Alessandro Antonello aantonello@paralaxe.com.br
 * \date    October 22, 2014
 * \since   Simple Framework 1.3
 * \copyright
 * 2014, Paralaxe Tecnologia. All rights reserved.
 */
#import "SFWeakMap.h"
#import "SFWeakList.h"

/* ===========================================================================
 * SFWeakMap EXTENSION
 * ======================================================================== */
@interface SFWeakMap () {
    NSMutableArray *m_keys;
    SFWeakList     *m_values;
}
/** \name Local Operations */ //@{
// - (uintptr_t)indexForKey:(NSString *)key;//{{{
/**
 * Finds the index of the specified key in the keys list.
 * @param key The key to find.
 * @returns The zero based index position of the key. Comparison is made by
 * its `isEqualToString:` selector. When the \a key is not found, is \b nil or
 * an empty string, the result is \b nil.
 * @since 1.3
 **/
- (uintptr_t)indexForKey:(NSString *)key;
//}}}
//@}
@end

/* ===========================================================================
 * SFWeakMap IMPLEMENTATION
 * ======================================================================== */
@implementation SFWeakMap
// Properties
/* property: count {{{ */
- (size_t)count { return (m_values ? m_values.count : 0); }
/* }}} property: count */
/* property: empty {{{ */
- (BOOL)empty { return (self.count == 0); }
/* }}} property: empty */

// Designated Initializers
// - (instancetype)initWithCapacity:(size_t)capacity;//{{{
- (instancetype)initWithCapacity:(size_t)capacity
{
    self = [super init];
    if (self)
    {
        m_keys = [[NSMutableArray alloc] initWithCapacity:capacity];
        m_values = [[SFWeakList alloc] initWithCapacity:capacity];
    }
    return self;
}
//}}}

// Getting a Value
// - (id)objectForKey:(id)key;//{{{
- (id)objectForKey:(id)key
{
    if (!m_keys || !m_values || !key) return nil;

    uintptr_t index = [m_keys indexOfObject:key];
    if (index == NSNotFound) return nil;

    return [m_values objectAtIndex:index];
}
//}}}
// - (id)valueForKey:(NSString *)key;//{{{
- (id)valueForKey:(NSString *)key
{
    if (!m_keys || !m_values || !key) return nil;
    if ([key length] == 0) return nil;

    uintptr_t index = [self indexForKey:key];
    if (index == NSNotFound) return nil;

    return [m_values objectAtIndex:index];
}
//}}}

// Adding Values
// - (BOOL)setObject:(id)object forKey:(id)key;//{{{
- (BOOL)setObject:(id)object forKey:(id)key
{
    if (!object || !key) return NO;

    if (!m_keys)
    {
        m_keys = [NSMutableArray new];
        m_values = [SFWeakList new];
    }

    uintptr_t index = [m_keys indexOfObject:key];
    if (index != NSNotFound)
        [m_values replaceObjectAtIndex:index withObject:object];
    else
    {
        [m_keys addObject:key];
        [m_values addObject:object];
    }
    return YES;
}
//}}}
// - (BOOL)setValue:(id)value forKey:(NSString *)key;//{{{
- (BOOL)setValue:(id)value forKey:(NSString *)key
{
    if (!value || !key) return NO;
    if ([key length] == 0) return NO;

    if (!m_keys)
    {
        m_keys = [NSMutableArray new];
        m_values = [SFWeakList new];
    }

    uintptr_t index = [self indexForKey:key];
    if (index != NSNotFound)
        [m_values replaceObjectAtIndex:index withObject:value];
    else
    {
        [m_keys addObject:key];
        [m_values addObject:value];
    }
    return YES;
}
//}}}

// Removing Key/Value Pairs
// - (id)removeObjectForKey:(id)key;//{{{
- (id)removeObjectForKey:(id)key
{
    if (!m_keys || !m_values || !key) return nil;

    uintptr_t index = [m_keys indexOfObject:key];
    if (index == NSNotFound) return nil;

    [m_keys removeObjectAtIndex:index];
    return [m_values removeObjectAtIndex:index];
}
//}}}
// - (id)removeValueForKey:(NSString *)key;//{{{
- (id)removeValueForKey:(NSString *)key
{
    if (!m_keys || !m_values || !key) return nil;
    if ([key length] == 0) return nil;

    uintptr_t index = [self indexForKey:key];
    if (index == NSNotFound) return nil;

    [m_keys removeObjectAtIndex:index];
    return [m_values removeObjectAtIndex:index];
}
//}}}
// - (void)removeAllObjects;//{{{
- (void)removeAllObjects
{
    if (m_keys)
        [m_keys removeAllObjects];

    if (m_values)
        [m_values removeAllObjects];
}
//}}}

// Local Operations
// - (uintptr_t)indexForKey:(NSString *)key;//{{{
- (uintptr_t)indexForKey:(NSString *)key
{
    if (!m_keys || !m_values || !key) return NSNotFound;
    if ([key length] == 0) return NSNotFound;

    size_t limit = self.count;
    NSString *stringKey;

    for (size_t i = 0; i < limit; ++i)
    {
        stringKey = (NSString *)[m_keys objectAtIndex:i];
        if ([stringKey isEqualToString:key])
            return i;
    }
    return NSNotFound;
}
//}}}

// NSObject: Overrides
// - (void)dealloc;//{{{
- (void)dealloc
{
    [m_keys release];
    [m_values release];
    [super dealloc];
}
//}}}

// Class Methods
// + (instancetype)weakMap;//{{{
+ (instancetype)weakMap
{
    return [[SFWeakMap new] autorelease];
}
//}}}
// + (instancetype)weakMapWithCapacity:(size_t)capacity;//{{{
+ (instancetype)weakMapWithCapacity:(size_t)capacity
{
    SFWeakMap *weakMap = [[SFWeakMap alloc] initWithCapacity:capacity];
    return [weakMap autorelease];
}
//}}}
@end
// vim:syntax=objc.doxygen
