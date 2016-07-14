/**
 * \file
 * Declares the SFReachability Objective-C interface class.
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
#import <CoreFoundation/CoreFoundation.h>

/**
 * \ingroup sf_networking
 * \defgroup sf_reachability_consts Constants
 * Enumerations and constants for this group.
 * @{ *//* ---------------------------------------------------------------- */
typedef NS_ENUM(NSInteger, SFReachabilityResult) {
    SFReachabilityNotReachable = 0,         /**< Address not reachable.     */
    SFReachabilityViaWiFi = 1,              /**< Reachable via WiFi.        */
    SFReachabilityViaWAN = 2                /**< Reachable via WAN.         */
};
///@} sf_reachability_consts

/**
 * \ingroup sf_networking
 * API to detect reachability of a host or network.
 *//* --------------------------------------------------------------------- */
@interface SFReachability : NSObject
// Properties
// @property (nonatomic, readonly) SFReachabilityResult reachabilityStatus;//{{{
/**
 * Gets the result of reachability quering.
 * @returns One of the possible values of \c SFReachabilityResult enumeration.
 **/
@property (nonatomic, readonly) SFReachabilityResult reachabilityStatus;
//}}}
// @property (nonatomic, readonly) BOOL connectionRequired;//{{{
/**
 * Sets when a connection is required.
 * An WiFi or WAN interface may be available but not ready yet without a
 * connection.
 * @returns \b true if a connection is required. Otherwise \b false.
 **/
@property (nonatomic, readonly) BOOL connectionRequired;
//}}}

/** @name Designated Initializers */ //@{
// - (instancetype)initWithHostName:(NSString*)hostName;//{{{
/**
 * Initializes this object to test the reachability of a host name.
 * @param hostName NSString with the name of the host to test. Must not be an
 * IP address or \b nil.
 * @return This object initialized.
 * @remarks To start the notification cycle you need to call
 * #startNotifying:selector:.
 **/
- (instancetype)initWithHostName:(NSString*)hostName;
//}}}
// - (instancetype)initWithAddress:(NSString*)ipAddress;//{{{
/**
 * Initializes this object to test the reachability of an IP address.
 * @param ipAddress NSString with the address to test. Must not be \b nil.
 * @returns This object initialized.
 * @remarks To start the notification cycle you need to call
 * #startNotifying:selector:.
 **/
- (instancetype)initWithAddress:(NSString*)ipAddress;
//}}}
//@}

/** @name Asynchronous Notifications */ //@{
// - (BOOL)startNotifying:(id)target selector:(SEL)action;//{{{
/**
 * Starts the notification query.
 * @param target The object to call on each notification.
 * @param action The selector to call on each notification. Must accept a
 * single argument that is this object instance.
 * @remarks The query is done in the current thread, queued in the run loop.
 * When the query is done the \a target \a action will be called and the
 * properties of this object can be checked to see if the host is reachable or
 * not and why.
 **/
- (BOOL)startNotifying:(id)target selector:(SEL)action;
//}}}
// - (void)stopNotifying;//{{{
/**
 * Stop the querying process.
 * This call will remove the queries queued in the current run loop. But will
 * not release any memory allocated.
 **/
- (void)stopNotifying;
//}}}
//@}

/** @name Synchronous Information */ //@{
// - (SFReachabilityResult)currentStatus;//{{{
/**
 * Retrieves the current communication status.
 * @return A set of flags defining the reachability of the address used to
 * initialize this object.
 * @remarks This operation will check the status synchronous. That is, the
 * current thread will stop until an answer is received. Use with caution.
 * @since 1.3
 **/
- (SFReachabilityResult)currentStatus;
//}}}
//@}

/** @name Specialized Instances */ //@{
// + (instancetype)reachabilityForInternetConnection;//{{{
/**
 * Builds a SFReachability object to query for an Internet connection.
 * Can be used for applications that need to know if there is an Internet
 * connection available.
 * @returns A temporary instance of a SFReachability object.
 **/
+ (instancetype)reachabilityForInternetConnection;
//}}}
// + (instancetype)reachabilityForLocalConnection;//{{{
/**
 * Builds a SFReachability object to query the availability of a local
 * network.
 * Can be used for applications that need to know whether a local network is
 * available.
 * @returns A temporary instance of a SFReachability object.
 **/
+ (instancetype)reachabilityForLocalConnection;
//}}}
//@}

/** @name Information */ //@{
// + (NSString*)currentSSID;//{{{
/**
 * Returns the SSID value of the current WiFi hotspot.
 * @return An NSString object with the value of the current WiFi SSID. Or an
 * empty string, if the system query fails.
 * @remarks The result can return a valid SSID even when there is no WiFi
 * available. So this request must be combined with the result \c
 * SCReachabilityViaWiFi from #reachabilityStatus property.
 **/
+ (NSString*)currentSSID;
//}}}
// + (NSString*)currentBSSID;//{{{
/**
 * Returns the BSSID value of the current WiFi hotspot.
 * @return An NSString object with the value of the BSSID of the WiFi hotspot
 * or an empty string if the system query fails.
 * @remarks The result can return a valid BSSID even when there is no WiFi
 * available. So this request must be combined with the result \c
 * SCReachabilityViaWiFi from #reachabilityStatus property.
 * @since 1.3
 **/
+ (NSString*)currentBSSID;
//}}}
//@}
@end
// vim:ft=objc syntax=objc.doxygen
