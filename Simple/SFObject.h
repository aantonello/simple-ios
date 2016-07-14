/**
 * \file
 * Declares the SFObject Objective-C interface class.
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
#import <UIKit/UIKit.h>

/**
 * \defgroup sf_categories Categories
 * Some SF operations added to Objective-C classes.
 * @{ *//* ---------------------------------------------------------------- */

/**
 * NSObject Simple additions.
 *//* --------------------------------------------------------------------- */
@interface NSObject (SFObject)
/** @name Operations */ //@{
// - (void)schedule:(SEL)sel passing:(id)object delay:(CFTimeInterval)interval;//{{{
/**
 * Schedule a selector to run after the specified delay.
 * \param sel The selector to run.
 * \param object Argument to be passed to the selector. If the selector
 * doesn't need any argument pass \b nil to this value.
 * \param interval Interval, in seconds, to wait until run the selector.
 * \remarks This function replaces the message
 * <code>performSelector:withObject:afterDelay</code> of the \c NSObject
 * interface.
 **/
- (void)schedule:(SEL)sel passing:(id)object delay:(CFTimeInterval)interval;
//}}}
// - (void)unschedule:(SEL)sel passed:(id)object;//{{{
/**
 * Unschedule a selector previous scheduled.
 * \param sel The selector to unschedule.
 * \param object The object that was passed to the scheduled selector.
 * \remarks This functions replaces the \c NSObject class message
 * <code>cancelPreviousPerformRequestsWithTarget:selector:object</code>. The
 * target argumento of that function will always be \e self.
 **/
- (void)unschedule:(SEL)sel passed:(id)object;
//}}}
//@}
@end
///@} sf_categories
// vim:ft=objc syntax=objc.doxygen
