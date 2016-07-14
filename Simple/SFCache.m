/**
 * @file
 * Defines the SFCache Objective-C interface class.
 *
 * @author  Alessandro Antonello aantonello@paralaxe.com.br
 * @date    May 10, 2014
 * @since   Simple Framework 1.2
 *
 * \copyright
 * 2014, Paralaxe Tecnologia. All rights reserved.
 */
#import "SFCache.h"

/* ===========================================================================
 * SFCache EXTENSION
 * ======================================================================== */
@interface SFCache () {
    NSMutableSet *m_cache;
    NSLock       *m_lock;
    size_t m_limit;
}
@end

/* ---------------------------------------------------------------------------
 * IMPLEMENTATION
 * ------------------------------------------------------------------------ */
@implementation SFCache
// Initialization
// - (id)init;//{{{
- (id)init
{
    self = [super init];
    if (self)
    {
        m_limit = 0;
        m_cache = [NSMutableSet new];
        m_lock  = [NSLock new];
    }
    return self;
}
//}}}
// - (instancetype)initWithCapacity:(size_t)capacity;//{{{
- (instancetype)initWithCapacity:(size_t)capacity
{
    self = [self init];
    if (self)
    {
        m_limit = capacity;
    }
    return self;
}
//}}}

// NSObject: Overrides
// - (void)dealloc;//{{{
- (void)dealloc
{
    [m_cache release];
    [m_lock release];
    [super dealloc];
}
//}}}

// Attributes
// - (size_t)count;//{{{
- (size_t)count
{
    size_t result = 0;

    [m_lock lock];
    result = (size_t)(m_cache ? [m_cache count] : 0);
    [m_lock unlock];

    return result;
}
//}}}

// Cache Limit
// - (void)setLimitCount:(size_t)count;//{{{
- (void)setLimitCount:(size_t)count
{
    [m_lock lock];
    m_limit = count;
    [m_lock unlock];
}
//}}}
// - (size_t)limitCount;//{{{
- (size_t)limitCount
{
    return m_limit;
}
//}}}

// Cache Access
// - (void)addObject:(id)object;//{{{
- (void)addObject:(id)object
{
    [m_lock lock];
    if ((m_limit > 0) && ([m_cache count] < m_limit))
        [m_cache addObject:object];
    [m_lock unlock];
}
//}}}
// - (id)anyObject;//{{{
- (id)anyObject
{
    id object = nil;

    [m_lock lock];
    object = [m_cache anyObject];
    if (object)
    {
        [object retain];
        [m_cache removeObject:object];
        [object autorelease];
    }
    [m_lock unlock];

    return object;
}
//}}}
@end
// vim:syntax=objc.doxygen
