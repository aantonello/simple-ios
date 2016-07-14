/**
 * \file
 * Defines the SFReachability class.
 *
 * \author  Alessandro Antonello aantonello@paralaxe.com.br
 * \date    May 08, 2014
 * \since   Simple Framework 1.2
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#import <SystemConfiguration/SystemConfiguration.h>
#import <SystemConfiguration/CaptiveNetwork.h>
#import "sfdebug.h"
#import "SFReachability.h"
#import "SFString.h"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* ===========================================================================
 * SFReachability EXTENSION
 * ======================================================================== */
@interface SFReachability () {
    SCNetworkReachabilityRef m_reachabilityRef;
    SEL m_action;
    id  m_target;
    SCNetworkReachabilityFlags m_reachabilityFlags;
}
// Querying Result
// - (void)setResult:(SCNetworkReachabilityFlags)flags;//{{{
/**
 * Sets the result of a reachability query and call the users function.
 * @param flags The reachability set of flags returned.
 **/
- (void)setResult:(SCNetworkReachabilityFlags)flags;
//}}}

// Hotspot Info
// + (NSString*)hotspotInfo:(NSString*)infoName;//{{{
/**
 * Retreives some information about the current network interface.
 * @param infoName The information to retrieve. Examples are
 * `kCNNetworkInfoKeySSID` and `kCNNetworkInfoKeyBSSID`.
 * @return A `NSString` object with the information requested or an empty
 * string when the information is not available or doesn't exists.
 * @since 1.3
 **/
+ (NSString*)hotspotInfo:(NSString*)infoName;
//}}}
@end

/* ===========================================================================
 * Callback Function {{{
 * ======================================================================== */
/**
 * \internal
 * @{ *//* ---------------------------------------------------------------- */

/**
 * Receives the result of the system reachability querying.
*//* --------------------------------------------------------------------- */
static void reachabilityResult(
        SCNetworkReachabilityRef ref,
        SCNetworkReachabilityFlags flags,
        void *info
        )
{
    SFReachability *reachabilityInfo = (__bridge SFReachability *)info;

    [reachabilityInfo setResult:flags];
}
///@} internal
/* Callback Function }}}
 * ======================================================================== */

/* ===========================================================================
 * SFReachability IMPLEMENTATION
 * ======================================================================== */
@implementation SFReachability
// Properties
// @property (nonatomic, readonly) SFReachabilityResult reachabilityStatus;//{{{
- (SFReachabilityResult)reachabilityStatus
{
    SFReachabilityResult result = SFReachabilityNotReachable;

    if ((m_reachabilityFlags & kSCNetworkReachabilityFlagsReachable) == 0)
        return result;

    if ((m_reachabilityFlags & kSCNetworkReachabilityFlagsIsDirect) ||
        !(m_reachabilityFlags & kSCNetworkReachabilityFlagsConnectionRequired))
        result = SFReachabilityViaWiFi;

    if (((m_reachabilityFlags & kSCNetworkReachabilityFlagsConnectionOnDemand) ||
        (m_reachabilityFlags & kSCNetworkReachabilityFlagsConnectionOnTraffic)) &&
        !(m_reachabilityFlags & kSCNetworkReachabilityFlagsInterventionRequired))
    {
        result = SFReachabilityViaWiFi;
    }

    if (m_reachabilityFlags & kSCNetworkReachabilityFlagsIsWWAN)
        result = SFReachabilityViaWAN;

    return result;
}
//}}}
// @property (nonatomic, readonly) BOOL connectionRequired;//{{{
- (BOOL)connectionRequired
{
    return (BOOL)((m_reachabilityFlags & kSCNetworkReachabilityFlagsConnectionRequired) != 0);
}
//}}}

// Designated Initializers
// - (instancetype)initWithHostName:(NSString*)hostName;//{{{
- (instancetype)initWithHostName:(NSString*)hostName
{
    self = [super init];
    if (self) {
        m_reachabilityRef = SCNetworkReachabilityCreateWithName(NULL, [hostName utf8Array]);
    }
    return self;
}
//}}}
// - (instancetype)initWithAddress:(NSString*)ipAddress;//{{{
- (instancetype)initWithAddress:(NSString*)ipAddress
{
    self = [super init];
    if (self)
    {
        struct sockaddr_in addr;

        memset(&addr, 0, sizeof(struct sockaddr_in));

        if (ipAddress == nil)
            addr.sin_addr.s_addr = INADDR_ANY;      /* Used to query WAN connections. */
        else if ([ipAddress isEqualToString:@"localhost"])
            addr.sin_addr.s_addr = htonl(IN_LINKLOCALNETNUM);   /* Used to query LAN connections. */
        else
            addr.sin_addr.s_addr = inet_addr([ipAddress utf8Array]);

        addr.sin_len    = sizeof(struct sockaddr_in);
        addr.sin_family = AF_INET;

        m_reachabilityRef = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (const struct sockaddr*)&addr);
        sftracef("m_reachabilityRef: %p\n", m_reachabilityRef);
    }
    return self;
}
//}}}

// NSObject Overrides
// - (void)dealloc;//{{{
- (void)dealloc
{
    [self stopNotifying];
    if (m_reachabilityRef != NULL)
        CFRelease(m_reachabilityRef);
    [super dealloc];
}
//}}}

// Asynchronous Notifications
// - (BOOL)startNotifying:(id)target selector:(SEL)action;//{{{
- (BOOL)startNotifying:(id)target selector:(SEL)action
{
    SCNetworkReachabilityContext context = { 0, (__bridge void*)self, NULL, NULL, NULL };

    m_target = target;
    m_action = action;

    if (!SCNetworkReachabilitySetCallback(m_reachabilityRef, reachabilityResult, &context))
    {
        sftrace("SCNetworkReachabilitySetCallback() FAILED!\n");
        return NO;
    }

    if (!SCNetworkReachabilityScheduleWithRunLoop(m_reachabilityRef, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode))
    {
        sftrace("SCNetworkReachabilityScheduleWithRunLoop() FAILED!\n");
        return NO;
    }

    return YES;
}
//}}}
// - (void)stopNotifying;//{{{
- (void)stopNotifying
{
    if (m_reachabilityRef == NULL)
        return;

    SCNetworkReachabilityUnscheduleFromRunLoop(m_reachabilityRef, CFRunLoopGetCurrent(), kCFRunLoopDefaultMode);
}
//}}}

// Synchronous Information
// - (SFReachabilityResult)currentStatus;//{{{
- (SFReachabilityResult)currentStatus
{
    if (m_reachabilityRef == NULL)
    {
        sftracef("SCNetworkReachabilityRef is NULL!\n");
        return SFReachabilityNotReachable;
    }

    if (!SCNetworkReachabilityGetFlags(m_reachabilityRef, &m_reachabilityFlags))
    {
        sftracef("SCNetworkReachabilityGetFlags() FAILED!\n");
        return SFReachabilityNotReachable;
    }
    return self.reachabilityStatus;
}
//}}}

// Specialized Instances
// + (instancetype)reachabilityForInternetConnection;//{{{
+ (instancetype)reachabilityForInternetConnection
{
    SFReachability *reachability;

    reachability = [[SFReachability alloc] initWithAddress:nil];
    return [reachability autorelease];
}
//}}}
// + (instancetype)reachabilityForLocalConnection;//{{{
+ (instancetype)reachabilityForLocalConnection
{
    SFReachability *reachability;

    reachability = [[SFReachability alloc] initWithAddress:@"localhost"];
    return [reachability autorelease];
}
//}}}

// Information
// + (NSString*)hotspotInfo:(NSString*)infoName;//{{{
+ (NSString*)hotspotInfo:(NSString*)infoName
{
    NSArray *array = (__bridge NSArray*)CNCopySupportedInterfaces();

    if (array == nil)
    {
        sftracef("CNCopySupportedInterfaces() returns nil\n");
        return [NSString string];
    }
    else if ([array count] == 0)
    {
        sftracef("CNCopySupportedInterfaces() array is empty\n");
        [array release];
        return [NSString string];
    }

    NSString *serviceSet;
    CFStringRef interfaceName = (CFStringRef)[array objectAtIndex:0];
    NSDictionary *networkDict = (__bridge NSDictionary*)CNCopyCurrentNetworkInfo(interfaceName);

    interfaceName = (CFStringRef)[networkDict valueForKey:infoName];
    if (interfaceName)
        serviceSet = [[[NSString alloc] initWithString:(__bridge NSString*)interfaceName] autorelease];
    else
        serviceSet = [NSString string];

    [networkDict release];
    [array release];
    return serviceSet;
}
//}}}
// + (NSString*)currentSSID;//{{{
+ (NSString*)currentSSID
{
    NSString* const ssidInfoKey = (__bridge NSString* const)kCNNetworkInfoKeySSID;
    return [SFReachability hotspotInfo:ssidInfoKey];
}
//}}}
// + (NSString*)currentBSSID;//{{{
+ (NSString*)currentBSSID
{
    NSString* const bssidInfoKey = (__bridge NSString* const)kCNNetworkInfoKeyBSSID;
    return [SFReachability hotspotInfo:bssidInfoKey];
}
//}}}

// Querying Result
// - (void)setResult:(SCNetworkReachabilityFlags)flags;//{{{
- (void)setResult:(SCNetworkReachabilityFlags)flags
{
    m_reachabilityFlags = flags;
#ifdef DEBUG
    sftracef("\n\t| m_reachabilityFlags: ");
    if ((m_reachabilityFlags & kSCNetworkReachabilityFlagsReachable) == 0)
    {
        sfdebug("Not Reachable!\n");
        return;
    }

    if (m_reachabilityFlags & kSCNetworkReachabilityFlagsIsWWAN)
    {
        sfdebug("Reachable via WAN\n");
        return;
    }

    if ((m_reachabilityFlags & kSCNetworkReachabilityFlagsIsDirect) ||
        !(m_reachabilityFlags & kSCNetworkReachabilityFlagsConnectionRequired))
    {
        sfdebug("Direct connection fia LAN\n");
        return;
    }

    if (((m_reachabilityFlags & kSCNetworkReachabilityFlagsConnectionOnDemand) ||
        (m_reachabilityFlags & kSCNetworkReachabilityFlagsConnectionOnTraffic)) &&
        !(m_reachabilityFlags & kSCNetworkReachabilityFlagsInterventionRequired))
    {
        sfdebug("Direct connection fia LAN\n");
    }
#endif

    if ((m_target) && (m_action))
        [m_target performSelector:m_action withObject:self afterDelay:0.0];
}
//}}}
@end
// vim:syntax=objc.doxygen
