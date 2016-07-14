/**
 * \file
 * Defines the SFSender Objective-C interface class.
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
#import "SFSender.h"
#import "sfdebug.h"

/* ===========================================================================
 * SFMessage EXTENSION
 * ======================================================================== */
/** Message object. */
@interface SFMessage () {
    id         m_target;
    id         m_data;
    NSUInteger m_id;
    NSUInteger m_code;
    time_t     m_start;
    time_t     m_delay;
}
// PROPERTIES OVERRIDES
@property (nonatomic, readwrite) NSUInteger msgID;
@property (nonatomic, readwrite) NSUInteger code;
@property (nonatomic, readwrite, retain) id data;
@property (nonatomic, readwrite) time_t sentTime;

// Local Properties
// @property (nonatomic, assign) id target;//{{{
/**
 * Gets or sets the target of this message object.
 **/
@property (nonatomic, assign) id target;
//}}}
// @property (nonatomic) time_t delay;//{{{
/**
 * Gets or sets the delay configuration fo this message.
 **/
@property (nonatomic) time_t delay;
//}}}

// Operations
// - (void)dispatch;//{{{
/**
 * Dispatches the message to its handler.
 **/
- (void)dispatch;
//}}}
@end
/* ===========================================================================
 * SFMessage IMPLEMENTATION {{{
 * ======================================================================== */
@implementation SFMessage
// Properties
// @property (nonatomic, readonly) NSUInteger msgID;//{{{
@synthesize msgID = m_id;
//}}}
// @property (nonatomic, readonly) NSUInteger code;//{{{
@synthesize code = m_code;
//}}}
// @property (nonatomic, readonly) id data;//{{{
@synthesize data = m_data;
//}}}
// @property (nonatomic, readonly) time_t sentTime;//{{{
@synthesize sentTime = m_start;
//}}}

// Local Properties
// @property (nonatomic, assign) id target;//{{{
@synthesize target = m_target;
//}}}
// @property (nonatomic) time_t delay;//{{{
@synthesize delay = m_delay;
//}}}

// Operations
// - (void)dispatch;//{{{
- (void)dispatch
{
    if ([m_target conformsToProtocol:@protocol(SFMessageHandler)]) {
        [m_target handleMsg:self];
    }
}
//}}}
@end
/* SFMessage IMPLEMENTATION }}}
 * ======================================================================== */

/* ===========================================================================
 * SFMessageStack INTERFACE
 * ======================================================================== */
@interface SFMessageStack : NSObject {
    NSLock*  m_lock;
    NSMutableArray* m_array;
}
// Operations
// - (SFMessage*)pop;//{{{
/**
 * Pops one object from the stack.
 * The poped object is removed from the internal list.
 * \return The first XMessage object in the list. If the list is empty the
 * result is \b nil.
 **/
- (SFMessage*)pop;
//}}}
// - (void)push:(SFMessage*)msg;//{{{
/**
 * Adds an SFMessage object to the end of the stack.
 * \param msg The XMessage object to add. It will be retained in this
 * operation.
 **/
- (void)push:(SFMessage*)msg;
//}}}
// - (SFMessage*)messageWithID:(NSUInteger)msgID;//{{{
/**
 * Search for an SFMessage object with the specified message ID.
 * @param msgID The message identifier to find.
 * @return An SFMessage object with the identifier requested or \b nil, if
 * none was found.
 **/
- (SFMessage*)messageWithID:(NSUInteger)msgID;
//}}}
// - (SFMessage*)messageWithID:(NSUInteger)msgID toTarget:(id)target;//{{{
/**
 * Search of an SFMessage object with the passed properties.
 * @param msgID The message identifier to find.
 * @param target Target handler of the message.
 * @return If the object is found it will be returned. Otherwise the operation
 * returns \b nil.
 **/
- (SFMessage*)messageWithID:(NSUInteger)msgID toTarget:(id)target;
//}}}
// - (SFMessage*)messageWithID:(NSUInteger)msgID code:(NSUInteger)arg toTarget:(id)target;//{{{
/**
 * Search of an SFMessage object with the passed properties.
 * @param msgID The message identifier to find.
 * @param arg Numeric code passed through the message.
 * @param target Target handler of the message.
 * @return If the object is found it will be returned. Otherwise the operation
 * returns \b nil.
 **/
- (SFMessage*)messageWithID:(NSUInteger)msgID code:(NSUInteger)arg toTarget:(id)target;
//}}}
// - (void)remove:(SFMessage*)msg;//{{{
/**
 * Remove an SFMessage object from this list.
 * If the object isn't found in the list the operation does nothing.
 **/
- (void)remove:(SFMessage*)msg;
//}}}
@end
/* ===========================================================================
 * SFMessage IMPLEMENTATION {{{
 * ======================================================================== */
@implementation SFMessageStack
// Operations
// - (SFMessage*)pop;//{{{
- (SFMessage*)pop
{
    if ((m_array == nil) || ([m_array count] == 0)) return nil;

    SFMessage* msg = nil;
    [m_lock lock];
    msg = (SFMessage*)[m_array objectAtIndex:0];
    [msg retain];
    [m_array removeObject:msg];
    [m_lock unlock];

    return [msg autorelease];
}
//}}}
// - (void)push:(SFMessage*)msg;//{{{
- (void)push:(SFMessage*)msg
{
    sfassert(msg != nil, "SFMessageStack::push\n");
    if (m_array == nil) {
        m_array = [[NSMutableArray alloc] initWithCapacity:1];
        m_lock  = [[NSLock alloc] init];
    }

    [m_lock lock];
    [m_array addObject:msg];
    [m_lock unlock];
}
//}}}
// - (SFMessage*)messageWithID:(NSUInteger)msgID;//{{{
- (SFMessage*)messageWithID:(NSUInteger)msgID
{
    if (m_array == nil) return nil;

    [m_lock lock];

    SFMessage *result = nil;
    size_t     limit  = [m_array count];

    for (size_t i = 0; i < limit; ++i)
    {
        result = (SFMessage*)[m_array objectAtIndex:i];
        if (msgID == result.msgID)
            break;

        result = nil;
    }
    [m_lock unlock];

    return result;
}
//}}}
// - (SFMessage*)messageWithID:(NSUInteger)msgID toTarget:(id)target;//{{{
- (SFMessage*)messageWithID:(NSUInteger)msgID toTarget:(id)target
{
    if (m_array == nil) return nil;

    [m_lock lock];

    SFMessage *result = nil;
    size_t     limit  = [m_array count];

    for (size_t i = 0; i < limit; ++i)
    {
        result = (SFMessage *)[m_array objectAtIndex:i];
        if ((msgID == result.msgID) && (target == result.target))
            break;

        result = nil;
    }
    [m_lock unlock];
    return result;
}
//}}}
// - (SFMessage*)messageWithID:(NSUInteger)msgID code:(NSUInteger)arg toTarget:(id)target;//{{{
- (SFMessage*)messageWithID:(NSUInteger)msgID code:(NSUInteger)arg toTarget:(id)target
{
    if (m_array == nil) return nil;

    [m_lock lock];

    SFMessage* result = nil;
    size_t     limit  = [m_array count];

    for (size_t i = 0; i < limit; ++i)
    {
        result = (SFMessage *)[m_array objectAtIndex:i];
        if ((msgID == result.msgID) && (arg == result.code) && (target == result.target))
            break;

        result = nil;
    }
    [m_lock unlock];
    return result;
}
//}}}
// - (void)remove:(SFMessage*)msg;//{{{
- (void)remove:(SFMessage*)msg
{
    if ((m_array == nil) || ([m_array count] == 0)) return;
    [m_lock lock];
    [m_array removeObject:msg];
    [m_lock unlock];
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
@end
/* SFMessage IMPLEMENTATION }}}
 * ======================================================================== */

/* ===========================================================================
 * SFBroadcastChannels Interface {{{
 * ======================================================================== */

/**
 * Hold the list of channels and targets.
 *//* --------------------------------------------------------------------- */
@interface SFBroadcastChannels : NSObject {
    NSMutableDictionary *m_channels;
    NSLock *m_lock;
}
// Add Remove Targets
- (BOOL)addTarget:(id)target onChannel:(NSString *)channel;
- (BOOL)removeTarget:(id)target fromChannel:(NSString *)channel;
- (void)removeChannel:(NSString*)channel;

// Requesting targets
- (NSArray*)targetsForChannel:(NSString *)channel;
@end
/* ---------------------------------------------------------------------------
 * SFBroadcastChannels Implementation {{{
 * ------------------------------------------------------------------------ */
@implementation SFBroadcastChannels
/* ------------------------------------------------------------------------ */
/*! \name NSObject Overrides *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */

/**
 * Initializes the object.
 * @returns The object initialized.
 *//* --------------------------------------------------------------------- */
- (instancetype)init
{
    self = [super init];
    if (self)
    {
        m_channels = [NSMutableDictionary new];
        m_lock     = [NSLock new];
    }
    return self;
}

/**
 * Releases memory used by this object.
 *//* --------------------------------------------------------------------- */
- (void)dealloc
{
    [m_channels release];
    [m_lock release];
    [super dealloc];
}
///@} NSObject Overrides /*}}}*/
/* ------------------------------------------------------------------------ */
/*! \name Add Remove Targets *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */

/**
 * Add a target to a channels list.
 * @param target The target handler to add in the channel list. This object
 * will be retained in this operation.
 * @param channel The channel name.
 * @return \b YES if the target was successfuly added to the channels list.
 * Otherwise \b NO.
 *//* --------------------------------------------------------------------- */
- (BOOL)addTarget:(id)target onChannel:(NSString *)channel
{
    if (!m_channels) m_channels = [NSMutableDictionary new];

    [m_lock lock];

    NSMutableArray *array = (NSMutableArray *)[m_channels valueForKey:channel];
    if (array == nil)
    {
        array = [NSMutableArray new];
        [m_channels setValue:array forKey:channel];
        [array release];
    }

    if ([array indexOfObjectIdenticalTo:target] == NSNotFound)
        [array addObject:target];

    [m_lock unlock];
    return YES;
}

/**
 * Remove a target from a channel list.
 * @param target The target handler to remove from the list.
 * @param channel The name of the channel where the target was added.
 * @return \b YES if the target was found in the named channel. \b NO
 * otherwise.
 *//* --------------------------------------------------------------------- */
- (BOOL)removeTarget:(id)target fromChannel:(NSString *)channel
{
    if (!m_channels) return NO;

    [m_lock lock];

    BOOL result = NO;
    NSMutableArray *array = (NSMutableArray *)[m_channels valueForKey:channel];
    if (array != nil)
    {
        NSUInteger index = [array indexOfObjectIdenticalTo:target];
        if (index != NSNotFound)
        {
            [array removeObjectAtIndex:index];
            result = YES;
        }
    }
    [m_lock unlock];
    return result;
}

/**
 * Remove a channel from the list of broadcast channels.
 * @param channel NSString with the channel name. If this channel is not found
 * nothing will be done.
 *//* --------------------------------------------------------------------- */
- (void)removeChannel:(NSString*)channel
{
    if (!m_channels || !channel) return;

    [m_lock lock];
    [m_channels removeObjectForKey:channel];
    [m_lock unlock];
}
///@} Add Remove Targets /*}}}*/
/* ------------------------------------------------------------------------ */
/*! \name Requesting targets *//*{{{*/ //@{
/* ------------------------------------------------------------------------ */

/**
 * Searches for the list of targets in a channel.
 * @param channel The channel name.
 * @return An NSArray object with the list of targets added to the given
 * channel or \b nil if the channel was not found.
 *//* --------------------------------------------------------------------- */
- (NSArray*)targetsForChannel:(NSString *)channel
{
    NSArray *result = nil;

    [m_lock lock];

    NSMutableArray *array = (NSMutableArray *)[m_channels valueForKey:channel];
    if (array != nil)
        result = [NSArray arrayWithArray:array];

    [m_lock unlock];
    return result;
}
///@} Requesting targets /*}}}*/
/* ------------------------------------------------------------------------ */
@end
// SFBroadcastChannels Implementation }}}
/* ------------------------------------------------------------------------ */
/* SFBroadcastChannels Interface }}}
 * ======================================================================== */

@class SFSender;
static SFSender* g_sender = nil;

/* ===========================================================================
 * SFSender EXTENSION
 * ======================================================================== */
@interface SFSender () {
    SFMessageStack* m_stockStack;
    SFMessageStack* m_sentStack;
    SFBroadcastChannels *m_channels;
}
// PROPERTIES
// @property (nonatomic, readonly) SFMessageStack* stock;//{{{
/**
 * Gets the stock of messages objects.
 **/
@property (nonatomic, readonly) SFMessageStack* stock;
//}}}
// @property (nonatomic, readonly) SFMessageStack* sent;//{{{
/**
 * Gets the list of sent messages.
 **/
@property (nonatomic, readonly) SFMessageStack* sent;
//}}}
// @property (nonatomic, readonly) SFBroadcastChannels* channels;//{{{
/**
 * Gets the list of broadcast channels.
 **/
@property (nonatomic, readonly) SFBroadcastChannels* channels;
//}}}

// LOCAL OPERATIONS
// - (void)sendMessage:(SFMessage*)msg;//{{{
/**
 * Process and dispatches a message to it's handler.
 * This operation always run in the main application thread. When the sent
 * message has a delay it is dispatched again to be completed after the passed
 * delay. Otherwise it will be processed immediatly.
 * \param msg The message to process and dispatch.
 **/
- (void)sendMessage:(SFMessage*)msg;
//}}}
// - (void)sentMessage:(SFMessage*)msg;//{{{
/**
 * Process the message dispatching it to its target handler.
 * \param msg The message to dispatch.
 **/
- (void)sentMessage:(SFMessage*)msg;
//}}}

// STATIC METHODS
// + (SFSender*)currentSender;//{{{
/**
 * Gets the single SFSender instance.
 * There is only one instance per application.
 **/
+ (SFSender*)currentSender;
//}}}
@end

/* ===========================================================================
 * SFSender IMPLEMENTATION
 * ======================================================================== */
@implementation SFSender
// Properties
// @property (nonatomic, readonly) SFMessageStack* stock;//{{{
- (SFMessageStack *)stock {
    if (m_stockStack == nil) m_stockStack = [SFMessageStack new];
    return m_stockStack;
}
//}}}
// @property (nonatomic, readonly) SFMessageStack* sent;//{{{
- (SFMessageStack *)sent {
    if (m_sentStack == nil) m_sentStack = [SFMessageStack new];
    return m_sentStack;
}
//}}}
// @property (nonatomic, readonly) SFBroadcastChannels* channels;//{{{
- (SFBroadcastChannels *)channels {
    if (m_channels == nil) m_channels = [SFBroadcastChannels new];
    return m_channels;
}
//}}}

// Local Operations
// - (void)sendMessage:(SFMessage*)msg//{{{
- (void)sendMessage:(SFMessage*)msg
{
    if (!msg.delay)
        [self sentMessage:msg];
    else
    {
        CFTimeInterval interval = (((CFTimeInterval)msg.delay) / 1000.0);
        [self performSelector:@selector(sentMessage:) withObject:msg afterDelay:interval];
    }
}
//}}}
// - (void)sentMessage:(SFMessage*)msg;//{{{
- (void)sentMessage:(SFMessage*)msg
{
    [msg retain];
    [m_sentStack remove:msg];
    [msg dispatch];
    [m_stockStack push:msg];
    msg.data = nil;
    [msg release];
}
//}}}

// NSObject: Overrides
// - (void)dealloc;//{{{
- (void)dealloc
{
    [m_stockStack release];
    [m_sentStack release];
    [m_channels release];
    [super dealloc];
}
//}}}

// Class Methods
// + (SFSender*)currentSender;//{{{
+ (SFSender*)currentSender
{
    if (g_sender == nil) {
        g_sender = [[SFSender alloc] init];
    }
    return g_sender;
}
//}}}

// Broadcast Channels
// + (BOOL)registerTarget:(id)target forChannel:(NSString *)broadcastChannelName;//{{{
+ (BOOL)registerTarget:(id)target forChannel:(NSString *)broadcastChannelName
{
    SFSender *sender = [SFSender currentSender];
    SFBroadcastChannels *channels = [sender channels];
    return [channels addTarget:target onChannel:broadcastChannelName];
}
//}}}
// + (BOOL)removeTarget:(id)target fromChannel:(NSString *)broadcastChannelName;//{{{
+ (BOOL)removeTarget:(id)target fromChannel:(NSString *)broadcastChannelName
{
    SFSender *sender = [SFSender currentSender];
    SFBroadcastChannels *channels = [sender channels];

    return [channels removeTarget:target fromChannel:broadcastChannelName];
}
//}}}
// + (void)removeBroadcastChannel:(NSString *)channelName;//{{{
+ (void)removeBroadcastChannel:(NSString *)channelName
{
    SFBroadcastChannels *channels = [[SFSender currentSender] channels];

    [channels removeChannel:channelName];
}
//}}}

// Sending Messages
// + (void)send:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler;//{{{
+ (void)send:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler
{
    if ((handler == nil) || ![handler conformsToProtocol:@protocol(SFMessageHandler)])
        return;

    SFSender*  sender = [SFSender currentSender];
    SFMessage* theMsg = [[sender stock] pop];

    if (theMsg == nil) {
        theMsg = [[[SFMessage alloc] init] autorelease];
    }

    theMsg.target   = handler;
    theMsg.msgID    = msgID;
    theMsg.code     = arg;
    theMsg.data     = data;
    theMsg.delay    = 0;
    theMsg.sentTime = (time_t)(CFAbsoluteTimeGetCurrent() * 1000.0);

    [[sender sent] push:theMsg];
    [sender performSelectorOnMainThread:@selector(sendMessage:) withObject:theMsg waitUntilDone:YES];
}
//}}}
// + (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler;//{{{
+ (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler
{
    [SFSender post:msgID code:arg data:data toTarget:handler afterDelay:0.0];
}
//}}}
// + (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler afterDelay:(double)delay;//{{{
+ (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data toTarget:(id)handler afterDelay:(double)delay
{
    if ((handler == nil) || ![handler conformsToProtocol:@protocol(SFMessageHandler)])
        return;

    SFSender*  sender = [SFSender currentSender];
    SFMessage* theMsg = [[sender stock] pop];

    if (theMsg == nil) {
        theMsg = [[[SFMessage alloc] init] autorelease];
    }

    theMsg.target   = handler;
    theMsg.msgID    = msgID;
    theMsg.code     = arg;
    theMsg.data     = data;
    theMsg.delay    = (time_t)(delay * 1000.0);
    theMsg.sentTime = (time_t)(CFAbsoluteTimeGetCurrent() * 1000.0);

    [[sender sent] push:theMsg];
    [sender performSelectorOnMainThread:@selector(sendMessage:) withObject:theMsg waitUntilDone:NO];
}
//}}}
// + (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data onChannel:(NSString*)broadcastChannel;//{{{
+ (void)post:(NSUInteger)msgID code:(NSUInteger)arg data:(id)data onChannel:(NSString*)broadcastChannel
{
    SFSender *sender = [SFSender currentSender];
    NSArray  *array  = [[sender channels] targetsForChannel:broadcastChannel];

    if ((array == nil) || ([array count] == 0))
        return;     /* Nothing to be done. */

    size_t limit = [array count];

    for (size_t x = limit; x > 0; x--)
        [SFSender post:msgID code:arg data:data toTarget:[array objectAtIndex:(x-1)]];
}
//}}}

// Cancelling Messages
// + (void)cancel:(NSInteger)msgID;//{{{
+ (void)cancel:(NSInteger)msgID
{
    SFSender *sender = [SFSender currentSender];
    SFMessageStack *sentMessages = [sender sent];
    SFMessageStack *messageStock = [sender stock];
    SFMessage *theMsg;

    while ((theMsg = [sentMessages messageWithID:msgID]) != nil)
    {
        [theMsg retain];
        [NSObject cancelPreviousPerformRequestsWithTarget:sender
                                                 selector:@selector(sentMessage:)
                                                   object:theMsg];
        [sentMessages remove:theMsg];
        [messageStock push:theMsg];
        [theMsg release];
    }
}
//}}}
// + (void)cancel:(NSInteger)msgID forTarget:(id)handler;//{{{
+ (void)cancel:(NSInteger)msgID forTarget:(id)handler
{
    if (!handler) return;

    SFSender *sender = [SFSender currentSender];
    SFMessageStack *sentMessages = [sender sent];
    SFMessageStack *messageStock = [sender stock];
    SFMessage *theMsg;

    while ((theMsg = [sentMessages messageWithID:msgID toTarget:handler]) != nil)
    {
        [theMsg retain];
        [NSObject cancelPreviousPerformRequestsWithTarget:sender
                                                 selector:@selector(sentMessage:)
                                                   object:theMsg];
        [sentMessages remove:theMsg];
        [messageStock push:theMsg];
        [theMsg release];
    }
}
//}}}
// + (void)cancel:(NSInteger)msgID code:(NSUInteger)arg forTarget:(id)handler;//{{{
+ (void)cancel:(NSInteger)msgID code:(NSUInteger)arg forTarget:(id)handler
{
    if (!handler) return;

    SFSender *sender = [SFSender currentSender];
    SFMessageStack *sentMessages = [sender sent];
    SFMessageStack *messageStock = [sender stock];
    SFMessage *theMsg;

    while ((theMsg = [sentMessages messageWithID:msgID code:arg toTarget:handler]) != nil)
    {
        [theMsg retain];
        [NSObject cancelPreviousPerformRequestsWithTarget:sender
                                                 selector:@selector(sentMessage:)
                                                   object:theMsg];
        [sentMessages remove:theMsg];
        [messageStock push:theMsg];
        [theMsg release];
    }
}
//}}}
@end
// vim:syntax=objc.doxygen
