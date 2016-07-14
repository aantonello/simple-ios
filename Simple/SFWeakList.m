/**
 * \file
 * Defines the SFWeakList class.
 *
 * \author  Alessandro Antonello aantonello@paralaxe.com.br
 * \date    Outubro 21, 2014
 * \since   Simple Framework 1.3
 * \copyright
 * 2014, Paralaxe Tecnologia. All rights reserved.
 */
#import "SFWeakList.h"

/* ===========================================================================
 * SFWeakList EXTENSION
 * ======================================================================== */
@interface SFWeakList () {
    id    *m_list;
    size_t m_length;
    size_t m_count;
}
/** \name Local Operations */ //@{
// - (BOOL)growListBy:(size_t)amount;//{{{
/**
 * Increases the allocated memory if needed.
 * @param amount Number of objects that will be added to the list.
 * @return \b YES when the memory could be allocated successfuly or \b NO when
 * the allocation fails.
 * @since 1.3
 **/
- (BOOL)growListBy:(size_t)amount;
//}}}
//@}
@end

/* ===========================================================================
 * SFWeakList IMPLEMENTATION
 * ======================================================================== */
@implementation SFWeakList
// Properties
/* property: count {{{ */
@synthesize count = m_count;
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
        m_list = (id *)malloc(capacity * sizeof(id));
        if (m_list) {
            memset(m_list, 0, sizeof(id) * capacity);
        }

        m_length = capacity;
        m_count  = 0;
    }
    return self;
}
//}}}
// - (instancetype)initWithArray:(NSArray *)array;//{{{
- (instancetype)initWithArray:(NSArray *)array
{
    self = [self initWithCapacity:[array count]];
    if (self)
    {
        size_t limit = [array count];

        for (size_t i = 0; i < limit; ++i)
            m_list[i] = [array objectAtIndex:i];
    }
    return self;
}
//}}}
// - (instancetype)initWithList:(SFWeakList *)list;//{{{
- (instancetype)initWithList:(SFWeakList *)list
{
    self = [self initWithCapacity:[list count]];
    if (self)
    {
        size_t limit = list.count;

        for (size_t i = 0; i < limit; ++i)
            m_list[i] = [list objectAtIndex:i];
    }
    return self;
}
//}}}

// Finding Objects in the List
// - (intptr_t)indexOfObject:(id)object;//{{{
- (intptr_t)indexOfObject:(id)object
{
    size_t limit = m_count;
    id element;

    for (size_t i = 0; i < limit; ++i)
    {
        element = m_list[i];
        if ([element isEqual:object])
            return (intptr_t)i;
    }
    return -1;
}
//}}}
// - (intptr_t)indexOfObjectIdenticalTo:(id)object;//{{{
- (intptr_t)indexOfObjectIdenticalTo:(id)object
{
    size_t limit = m_count;

    for (size_t i = 0; i < limit; ++i)
    {
        if (object == m_list[i])
            return (intptr_t)i;
    }
    return -1;
}
//}}}
// - (intptr_t)indexOfObjectPassingTest:(BOOL (^)(id obj, uintptr_t index, BOOL *stop))test;//{{{
- (intptr_t)indexOfObjectPassingTest:(BOOL (^)(id obj, uintptr_t index, BOOL *stop))test
{
    size_t limit = m_count;
    BOOL stop = NO;

    for (size_t i = 0; i < limit; ++i)
    {
        if (test(m_list[i], i, &stop) || stop)
            return (intptr_t)i;
    }
    return -1;
}
//}}}

// Querying the List
// - (BOOL)containsObject:(id)object;//{{{
- (BOOL)containsObject:(id)object
{
    return ([self indexOfObject:object] >= 0);
}
//}}}
// - (id)firstObject;//{{{
- (id)firstObject
{
    return [self objectAtIndex:0];
}
//}}}
// - (id)lastObject;//{{{
- (id)lastObject
{
    if (!m_count) return nil;
    return m_list[m_count - 1];
}
//}}}
// - (id)objectAtIndex:(uintptr_t)index;//{{{
- (id)objectAtIndex:(uintptr_t)index
{
    if (index >= m_count) return nil;
    return m_list[index];
}
//}}}

// Adding Objects
// - (BOOL)addObject:(id)object;//{{{
- (BOOL)addObject:(id)object
{
    if (!object || ![self growListBy:1])
        return NO;

    m_list[m_count] = object;
    m_count++;
    
    return YES;
}
//}}}
// - (intptr_t)insertObject:(id)object atIndex:(uintptr_t)index;//{{{
- (intptr_t)insertObject:(id)object atIndex:(uintptr_t)index
{
    if (!object || ![self growListBy:1])
        return -1;

    if (index >= m_count)
    {
        [self addObject:object];
        return (intptr_t)(m_count - 1);
    }

    memmove((m_list + (index + 1)), (m_list + index), ((m_count - index) * sizeof(id)));
    m_list[index] = object;
    m_count++;

    return (intptr_t)index;
}
//}}}

// Removing Objects
// - (void)removeAllObjects;//{{{
- (void)removeAllObjects
{
    m_count = 0;
}
//}}}
// - (id)removeFirstObject;//{{{
- (id)removeFirstObject
{
    if (!m_count || (m_list == NULL))
        return nil;

    id object = m_list[0];

    memmove(m_list, (m_list + 1), ((m_count - 1) * sizeof(id)));
    m_count--;

    return object;
}
//}}}
// - (id)removeLastObject;//{{{
- (id)removeLastObject
{
    if (!m_count || !m_list) return nil;

    id object = m_list[m_count - 1];

    m_count--;
    return object;
}
//}}}
// - (BOOL)removeObject:(id)object;//{{{
- (BOOL)removeObject:(id)object
{
    intptr_t index = [self indexOfObject:object];
    if (index < 0) return NO;

    [self removeObjectAtIndex:index];
    return YES;
}
//}}}
// - (BOOL)removeObjectIdenticalTo:(id)object;//{{{
- (BOOL)removeObjectIdenticalTo:(id)object
{
    intptr_t index = [self indexOfObjectIdenticalTo:object];
    if (index < 0) return NO;

    [self removeObjectAtIndex:index];
    return YES;
}
//}}}
// - (id)removeObjectAtIndex:(uintptr_t)index;//{{{
- (id)removeObjectAtIndex:(uintptr_t)index
{
    if (index >= m_count) return nil;

    id object = m_list[index];

    memmove((m_list + index), (m_list + (index + 1)), ((m_count - 1) * sizeof(id)));
    m_count--;

    return object;
}
//}}}

// Replacing Objects
// - (void)setList:(SFWeakList *)list;//{{{
- (void)setList:(SFWeakList *)list
{
    size_t limit = list.count;
    id *temp = (id *)realloc(m_list, limit * sizeof(id));

    if (!temp) return;

    for (size_t i = 0; i < limit; ++i)
        m_list[i] = [list objectAtIndex:i];

    m_count  = limit;
    m_length = limit;
}
//}}}
// - (id)replaceObjectAtIndex:(uintptr_t)index withObject:(id)object;//{{{
- (id)replaceObjectAtIndex:(uintptr_t)index withObject:(id)object
{
    if (index >= m_count) return nil;

    id element = m_list[index];

    m_list[index] = object;
    return element;
}
//}}}

// Local Operations
// - (BOOL)growListBy:(size_t)amount;//{{{
- (BOOL)growListBy:(size_t)amount
{
    if ((m_count + amount) <= m_length)
        return YES;

    size_t total = (m_count + amount);
    id *temp = (id *)realloc(m_list, total * sizeof(id));
    if (temp == NULL) return NO;

    m_length = total;
    m_list   = temp;

    return YES;
}
//}}}

// NSCopying: Implementation
// - (id)copyWithZone:(NSZone*)zone;//{{{
- (id)copyWithZone:(NSZone*)zone
{
#pragma unused(zone)
    return [SFWeakList weakListWithList:self];
}
//}}}

// NSMutableCopying: Implementation
// - (id)mutableCopyWithZone:(NSZone *)zone;//{{{
- (id)mutableCopyWithZone:(NSZone *)zone
{
#pragma unuzed(zone)
    return [SFWeakList weakListWithList:self];
}
//}}}

// NSFastEnumeration: Implementation
// - (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state objects:(id [])stack count:(NSUInteger)len;//{{{
- (NSUInteger)countByEnumeratingWithState:(NSFastEnumerationState *)state
                                  objects:(id [])stack count:(NSUInteger)len
{
    uintptr_t index = state->state;
    size_t    limit = index + len;

    limit = MIN(limit, m_count);

    for (size_t i = index; i < limit; ++i)
        stack[i] = m_list[i];

    state->state = limit;
    return limit;
}
//}}}

// NSObject: Overrides
// - (void)dealloc;//{{{
- (void)dealloc
{
    if (m_list) free(m_list);
    [super dealloc];
}
//}}}

// Class Methods
// + (instancetype)weakList;//{{{
+ (instancetype)weakList
{
    return [[SFWeakList new] autorelease];
}
//}}}
// + (instancetype)weakListWithCapacity:(size_t)capacity;//{{{
+ (instancetype)weakListWithCapacity:(size_t)capacity
{
    SFWeakList *list = [[SFWeakList alloc] initWithCapacity:capacity];
    return [list autorelease];
}
//}}}
// + (instancetype)weakListWithArray:(NSArray *)array;//{{{
+ (instancetype)weakListWithArray:(NSArray *)array
{
    SFWeakList *list = [[SFWeakList alloc] initWithArray:array];
    return [list autorelease];
}
//}}}
// + (instancetype)weakListWithList:(SFWeakList *)list;//{{{
+ (instancetype)weakListWithList:(SFWeakList *)list
{
    SFWeakList *weakList = [[SFWeakList alloc] initWithList:list];
    return [weakList autorelease];
}
//}}}
@end
// vim:syntax=objc.doxygen
