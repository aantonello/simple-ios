/**
 * @file
 * Defines the SFQueue Objective-C interface class.
 *
 * @author  Alessandro Antonello aantonello@paralaxe.com.br
 * @date    May 10, 2014
 * @since   Simple Framework 1.2
 *
 * \copyright
 * 2014, Paralaxe Tecnologia. All rights reserved.
 */
#import "SFQueue.h"

/* ===========================================================================
 * SFQueue EXTENSION
 * ======================================================================== */
@interface SFQueue () {
    NSMutableArray *m_array;
    NSLock         *m_lock;
}
@end

/* ---------------------------------------------------------------------------
 * IMPLEMENTATION
 * ------------------------------------------------------------------------ */
@implementation SFQueue
// Designated Initializers
// - (id)init;//{{{
- (id)init
{
    self = [super init];
    if (self)
    {
        m_lock  = [NSLock new];
        m_array = [NSMutableArray new];
    }
    return self;
}
//}}}

// NSObject: Overrides
// - (void)dealloc;//{{{
- (void)dealloc
{
    [m_array release];
    [m_lock release];
    [super dealloc];
}
//}}}

// Attributes
// - (size_t)count;//{{{
- (size_t)count
{
    size_t total = 0;

    [m_lock lock];
    total = ((m_array) ? [m_array count] : 0);
    [m_lock unlock];

    return total;
}
//}}}

// Queue Access
// - (id)firstObject;//{{{
- (id)firstObject
{
    id object = nil;

    [m_lock lock];
    object = (m_array ? [m_array firstObject] : nil);
    [m_lock unlock];

    return object;
}
//}}}
// - (id)pullObject;//{{{
- (id)pullObject
{
    id object = nil;

    [m_lock lock];
    object = (m_array ? [m_array firstObject] : nil);
    if (object != nil)
    {
        [object retain];
        [m_array removeObjectAtIndex:0];
        [object autorelease];
    }
    [m_lock unlock];

    return object;
}
//}}}
// - (void)pushObject:(id)object;//{{{
- (void)pushObject:(id)object
{
    [m_lock lock];
    
    if (!m_array) m_array = [NSMutableArray new];
    if ([m_array indexOfObjectIdenticalTo:object] == NSNotFound)
        [m_array addObject:object];

    [m_lock unlock];
}
//}}}
@end
// vim:syntax=objc.doxygen
