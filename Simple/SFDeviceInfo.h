/**
 * @file
 * Declares the SFDeviceInfo class interface.
 *
 * @author Alessandro Antonello aantonello@paralaxe.com.br
 * @date   February 05, 2015
 * @since  Simple Framework 1.3
 *
 * @copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */

/**
 * @defgroup sf_information Information
 * This groups has macros and interfaces for device information.
 * The set of classes defined here (currently one) could be joined in the @ref
 * sf_resources group. But we found better to create a group on their own so,
 * if more interfaces are added, doesn't interfere with resources management
 * it self.
 **/

/* ===========================================================================
 * SFDeviceInfo Interface
 * ======================================================================== */

/**
 * @ingroup sf_information
 * This interface contains information about the running device.
 * The information provided is a set of joint between UIDevice and UIScreen
 * standard iOS interfaces.
 *
 * This interface is not meant to be allocated. All possible information is
 * given in class methods and can be used alone.
 * @since 1.3
 *//* --------------------------------------------------------------------- */
@interface SFDeviceInfo : NSObject
/** @name Device Information */ //@{
// + (NSString *)deviceName;//{{{
/**
 * Name of the device.
 * This is an arbitrary string and can be found in the settings application
 * under options "General" -> "About".
 * @returns A temporary \c NSString object with the device name.
 * @since 1.3
 **/
+ (NSString *)deviceName;
//}}}
// + (NSString *)deviceModel;//{{{
/**
 * A string identifying the device model.
 * The result can be a value like `@"iPhone"` or `@"iPod touch"`.
 * @return A temporary \c NSString object with the device model.
 * @since 1.3
 **/
+ (NSString *)deviceModel;
//}}}
// + (NSString *)systemName;//{{{
/**
 * Name of the operating system.
 * @return A temporary \c NSString object with the name of operating system.
 * This is almost always "iOS".
 * @since 1.3
 **/
+ (NSString *)systemName;
//}}}
// + (NSString *)systemVersion;//{{{
/**
 * A string representation of the current system version.
 * @return A temporary \c NSString object with the version number
 * representation like "2.0".
 * @since 1.3
 **/
+ (NSString *)systemVersion;
//}}}
// + (BOOL)deviceIsTablet;//{{{
/**
 * Checks whether the current device is an iPad device.
 * @returns \b YES when the current user interface idiom is for iPad devices.
 * @since 1.3
 **/
+ (BOOL)deviceIsTablet;
//}}}
// + (BOOL)deviceIsPhone;//{{{
/**
 * Checks whether the current device is an iPhone or iPod touch device.
 * @returns \b YES when the current user interface idiom is designed for
 * iPhone or iPod touch devices.
 * @since 1.3
 **/
+ (BOOL)deviceIsPhone;
//}}}
//@}

/** @name Main Screen Information */ //@{
// + (CGRect)screenBounds;//{{{
/**
 * Gets the bounding rectangle of the main screen in points.
 * @return A \c CGRect structure with the measures of the main screen.
 * @remarks This value can change when the orientation of the device changes.
 * @since 1.3
 **/
+ (CGRect)screenBounds;
//}}}
// + (CGRect)applicationFrame;//{{{
/**
 * The application frame, in points.
 * @return A \c CGRect structure with the dimensions of the current
 * application main Window.
 * @remarks On some devices this measure can be different from the screen
 * bounds. The returned value take into account the current screen
 * orientation.
 * @since 1.3
 **/
+ (CGRect)applicationFrame;
//}}}
// + (CGFloat)screenScale;//{{{
/**
 * The scale aplyed in the device.
 * @returns A \c CGFloat value with the scale factor used to convert logical
 * coordinates into physical coordinates used in the screen. In standard
 * device resolutions this value is equals to \b 1.0 and 1 logical point is
 * 1 physical pixel. This value can also be \b 2.0, on retina displays and
 * other values on other phones.
 * @since 1.3
 **/
+ (CGFloat)screenScale;
//}}}
// + (CGFloat)aspectRatio;//{{{
/**
 * The aspect ratio of a pixel.
 * @returns A \c CGFloat factor result of the calculation `x/y` where \b x is
 * the pixel width and \b y is the pixel height.
 * @since 1.3
 **/
+ (CGFloat)aspectRatio;
//}}}
//@}
@end
