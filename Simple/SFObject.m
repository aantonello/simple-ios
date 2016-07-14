/**
 * \file
 * Defines the SFObject Objective-C category extension for
 * NSObject interface.
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
#import "SFObject.h"

/* ===========================================================================
 * SFObject CATEGORY EXTENSION
 * ======================================================================== */
@implementation NSObject (SFObject)
// Operations
// - (void)schedule:(SEL)sel passing:(id)object delay:(CFTimeInterval)interval;//{{{
- (void)schedule:(SEL)sel passing:(id)object delay:(CFTimeInterval)interval
{
    [self performSelector:sel withObject:object afterDelay:interval];
}
//}}}
// - (void)unschedule:(SEL)sel passed:(id)object;//{{{
- (void)unschedule:(SEL)sel passed:(id)object
{
    [NSObject cancelPreviousPerformRequestsWithTarget:self selector:sel object:object];
}
//}}}
@end
// vim:syntax=objc.doxygen
