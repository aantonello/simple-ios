/**
 * @file
 * Declares the SFQueue Objective-C interface class.
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
 * SFQueue is a synchronized First In/First Out queue of objects.
 * By been synchronized, the access to objects in the queue is available by
 * any thread. Despite holding the objects in an indexed way, the objects
 * cannot be accessed in an indexed manner. Also, an object can be in the
 * queue only once. That is, when one object is pushed to the queue \c SFQueue
 * checkes whether the object is already there or not. Only one instance of
 * the same object is allowed.
 *
 * Objects can be retrieved without remove them from the queue. Or can be
 * retrieved and removed at same time. Any kind of object can be held in the
 * queue.
 *
 * Despite the queue access is synchronized, the objects that it held are not.
 * So, be careful. Don't share a queue of objects in multiple threads when you
 * access an object living it in the queue. When sharing a queue with multiple
 * threads use SFQueue::pullObject. It will removes the object from the queue
 * before returning it.
 *//* --------------------------------------------------------------------- */
@interface SFQueue : NSObject
/** @name Attributes */ //@{
// - (size_t)count;//{{{
/**
 * Gets the current number of objects in this queue.
 * @return The number of objects in this queue.
 **/
- (size_t)count;
//}}}
//@}

/** @name Queue Access */ //@{
// - (id)firstObject;//{{{
/**
 * Retrieves the first object in the queue without removing it.
 * @return The first object in the queue or \b nil if the queue is empty.
 **/
- (id)firstObject;
//}}}
// - (id)pullObject;//{{{
/**
 * Retrieves and removes the first object in the queue.
 * @return The first object in the queue. It will be `autorelease`d by this
 * operation. If you intend to hold it, you must call `retain` on it. If the
 * queue is empty, the result will be \b nil.
 **/
- (id)pullObject;
//}}}
// - (void)pushObject:(id)object;//{{{
/**
 * Pushes one object to the end of the queue.
 * @param object Object to be added in the end of the queue. The object is
 * retained in this process.
 * @remarks If \a object already exists in the queue the function does
 * nothing.
 **/
- (void)pushObject:(id)object;
//}}}
//@}
@end
// vim:ft=objc syntax=objc.doxygen
