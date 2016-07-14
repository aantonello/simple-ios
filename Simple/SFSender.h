/**
 * \file
 * Declares the SFSender Objective-C interface class.
 *
 * \author  Alessandro Antonello aantonello@paralaxe.com.br
 * \date    March 14, 2013
 * \since   Simple Framework 1.1
 * \version 2.0 Added support to broadcast messages.
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#import <Foundation/Foundation.h>

/**
 * \defgroup sf_msgs Message System
 * The message system is a general purpose notification system.
 * This system uses the standard pool of messages from Mac OS or iOS to queue
 * notifications in the main run loop. Also it has support of sending messages
 * from a parallel thread to objects running in the main thread.
 *
 * Messages have an ID, a numeric code and an object argument. Only the ID
 * is required, which can just inform about an event. There are no predefined
 * IDs, but this library reserves some identifier for future use. See \ref
 * sf_msgs_constants and the documentation of \c SFMessage.
 *
 * Messages can be sent to a single target or in a broadcast fation. To send
 * messages in broadcast the application defines a broadcast channel name and
 * interested objects will register to receive messages from that broadcast
 * channel. See the documentation of \c SFSender object to learn more.
 * @{ *//* ---------------------------------------------------------------- */

/**
 * \defgroup sf_msgs_constants Message System Constants
 * Reserved messages IDs.
 * This library doesn't use any ID for internal communication but reserve some
 * space to be used in the future. Reminded that message identifiers and
 * numeric codes are unsigned integer numbers. The user space starts at \c
 * SFMESSAGE_USER.
 * @{ *//* ---------------------------------------------------------------- */
#define SFMESSAGE_USER      0x00001000  /**< Users messages starts here.    */
///@} sf_msgs_constants
///@} sf_msgs

/**
 * \ingroup sf_msgs
 * Message object.
 * This object holds the message data and some extra information. Not all
 * properties have meaninful values. This depends on the nature of the message
 * and its origin.
 *//* --------------------------------------------------------------------- */
@interface SFMessage : NSObject
// Properties
// @property (nonatomic, readonly) NSUInteger msgID;//{{{
/**
 * The message identifier.
 * This is the only value that is mandatory to send a message.
 **/
@property (nonatomic, readonly) NSUInteger msgID;
//}}}
// @property (nonatomic, readonly) NSUInteger code;//{{{
/**
 * The message code.
 **/
@property (nonatomic, readonly) NSUInteger code;
//}}}
// @property (nonatomic, readonly) id data;//{{{
/**
 * Any object transmited with the message.
 * The lifetime of this object is managed internally. Don't retain or release
 * it unless you know what you are doing. Can be \b nil.
 **/
@property (nonatomic, readonly) id data;
//}}}
// @property (nonatomic, readonly) time_t sentTime;//{{{
/**
 * Time when the message was sent.
 * The value of this property is automatically defined by \c SFSender
 * interface. It's value is obtained using \c localtime() standard C function.
 **/
@property (nonatomic, readonly) time_t sentTime;
//}}}
@end

/**
 * \ingroup sf_msgs
 * Messages sender.
 * This class is singleton. Only one instance of it exists in the current
 * application. The application will deal with it only by its static methods.
 * The management of messages and channels are all done internally.
 *//* --------------------------------------------------------------------- */
@interface SFSender : NSObject
/** @name Broadcast Channels */ //@{
// + (BOOL)registerTarget:(id)target forChannel:(NSString *)broadcastChannelName;//{{{
/**
 * Register an object to receive messages from a broadcast channel.
 * @param target Target handler to register to. This object is retained in
 * this operation.
 * @param broadcastChannelName NSString with the name of the broadcast
 * channel.
 * @return \b YES when the registry was done. Otherwise \b NO.
 **/
+ (BOOL)registerTarget:(id)target forChannel:(NSString *)broadcastChannelName;
//}}}
// + (BOOL)removeTarget:(id)target fromChannel:(NSString *)broadcastChannelName;//{{{
/**
 * Removes an object from a broadcast channel.
 * @param target The target handler to remove from the channel list.
 * @param broadcastChannelName Name of the channel were the \a target was
 * registered.
 * @return \b YES if the target was successfuly removed from the channel. \b
 * NO when the target was not found or the channel does not exists.
 **/
+ (BOOL)removeTarget:(id)target fromChannel:(NSString *)broadcastChannelName;
//}}}
// + (void)removeBroadcastChannel:(NSString *)channelName;//{{{
/**
 * Removes a channel from the broadcast interface.
 * @param channelName NSString with the channel name.
 * @remarks All registered targets in this channel will be released.
 **/
+ (void)removeBroadcastChannel:(NSString *)channelName;
//}}}
//@}

/** @name Sending Messages */ //@{
// + (void)send:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler;//{{{
/**
 * Sends a message to the given target.
 * @param msgID The message identifier.
 * @param arg Numeric message code.
 * @param data Object message argument. Can be \b nil.
 * @param handler The target object to handle the message. Must conform with
 * the \c SFMessageHandler protocol.
 * @remarks The function will create and configure a \c SFMessage object to
 * hold the message data. This object will be sent to the handler through the
 * \c handleMsg: protocol selector. Notice that this selector always runs in
 * the main thread. The function waits until it is processed.
 **/
+ (void)send:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler;
//}}}
// + (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler;//{{{
/**
 * Posts a message to the given target.
 * @param msgID The message identifier.
 * @param arg Numeric message code.
 * @param data Object message argument. Can be \b nil.
 * @param handler The target object to handle the message. Must conform with
 * the \c SFMessageHandler protocol.
 * @remarks The function operates exactly like #send:code:data:toTarget:
 * except that it does not wait to the message handling before return. So the
 * call is put in the top of the run loop in the main thread and the function
 * returns.
 **/
+ (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler;
//}}}
// + (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler afterDelay:(double)delay;//{{{
/**
 * Posts a message to the given target.
 * @param msgID The message identifier.
 * @param arg Numeric message code.
 * @param data Object message argument. Can be \b nil.
 * @param handler The target object to handle the message. Must conform with
 * the \c SFMessageHandler protocol.
 * @param delay An CFTimeInterval (double) value with the interval to wait
 * before sending the message to the target.
 * @remarks The function operates exactly like #send:code:data:toTarget:
 * except that it does not wait to the message handling before return. So the
 * call is put in the top of the run loop in the main thread and the function
 * returns.
 **/
+ (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler afterDelay:(double)delay;
//}}}
// + (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data onChannel:(NSString*)broadcastChannel;//{{{
/**
 * Posts a message to all targets registered to the given channel.
 * @param msgID The message identifier.
 * @param arg Numeric message code.
 * @param data Object message argument. Can be \b nil.
 * @param broadcastChannel The channel to sent the message to.
 * @remarks Each registered handler in the channel will receive its own copy
 * of the \c SFMessage object. The messages are sent in LIFO (Last In First
 * Out) order. That is, the last registered handler will receive the message
 * first.
 **/
+ (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data onChannel:(NSString*)broadcastChannel;
//}}}
//@}

/** @name Cancelling Messages */ //@{
// + (void)cancel:(NSInteger)msgID;//{{{
/**
 * Cancel all messages with the specified ID.
 * @param msgID Identifier of the message to be cancelled.
 * @remarks Only messages with a delay can be cancelled. Message without
 * delay, even when they are waiting in the main threads run loop, are
 * considered sent and cannot be cancelled.
 * @note All messages found with the specified ID will be cancelled, regarding
 * the target or any other argument passed to it.
 **/
+ (void)cancel:(NSInteger)msgID;
//}}}
// + (void)cancel:(NSInteger)msgID forTarget:(id)handler;//{{{
/**
 * Cancel all messages with the specified properties.
 * @param msgID Identifier of the message to be cancelled.
 * @param handler The target handler for the message. If \b nil the function
 * does nothing.
 * @remarks Only messages with a delay can be cancelled. Message without
 * delay, even when they are waiting in the main threads run loop, are
 * considered sent and cannot be cancelled.
 * @note All messages found with the specified ID, sent to the specified
 * handler, will be cancelled.
 **/
+ (void)cancel:(NSInteger)msgID forTarget:(id)handler;
//}}}
// + (void)cancel:(NSInteger)msgID code:(NSUInteger)arg forTarget:(id)handler;//{{{
/**
 * Cancel all messages with the specified properties.
 * @param msgID Identifier of the message to be cancelled.
 * @param arg The numeric code passed with the message.
 * @param handler The target handler for the message. If \b nil the function
 * does nothing.
 * @remarks Only messages with a delay can be cancelled. Message without
 * delay, even when they are waiting in the main threads run loop, are
 * considered sent and cannot be cancelled.
 * @note All messages found with the specified properties, sent to the
 * specified handler, will be cancelled.
 **/
+ (void)cancel:(NSInteger)msgID code:(NSUInteger)arg forTarget:(id)handler;
//}}}
//@}
@end

/**
 * \ingroup sf_msgs
 * Protocol to be implemented to handle messages.
 * Only one function should be implemented so objects can handle messages sent
 * by this message system.
 *//* --------------------------------------------------------------------- */
@protocol SFMessageHandler
// - (void)handleMsg:(SFMessage*)message;//{{{
/**
 * Receives messages sent by \c SFSender interface.
 * All messages are handle by this only selector. They can be sent directly to
 * the object implementing this protocol or through a broadcast channel.
 * @param message An \c SFMessage object with the message data.
 *//* --------------------------------------------------------------------- */
- (void)handleMsg:(SFMessage*)message;
//}}}
@end
// vim:ft=objc syntax=objc.doxygen
