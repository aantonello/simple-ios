/**
 * \file
 * Declares the SFTime Objective-C interface class.
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
 * \defgroup sf_time Date/Time Utility
 * Simple data and time storage and converter.
 * @{ *//* ---------------------------------------------------------------- */

/**
 * A moment in time.
 *//* --------------------------------------------------------------------- */
@interface SFTime : NSObject
// Properties
// @property (nonatomic, readonly) NSInteger year;//{{{
/**
 * Gets the year number of this date.
 **/
@property (nonatomic, readonly) NSInteger year;
//}}}
// @property (nonatomic, readonly) NSInteger month;//{{{
/**
 * Gets the month number of this date where 1 is January.
 **/
@property (nonatomic, readonly) NSInteger month;
//}}}
// @property (nonatomic, readonly) NSInteger day;//{{{
/**
 * Gets the day of the month from 1 to 31.
 **/
@property (nonatomic, readonly) NSInteger day;
//}}}
// @property (nonatomic, readonly) NSInteger hour;//{{{
/**
 * Gets the hour of the day, from 0 to 23.
 **/
@property (nonatomic, readonly) NSInteger hour;
//}}}
// @property (nonatomic, readonly) NSInteger minute;//{{{
/**
 * Gets the minute in the hour, from 0 to 59.
 **/
@property (nonatomic, readonly) NSInteger minute;
//}}}
// @property (nonatomic, readonly) NSInteger seconds;//{{{
/**
 * Gets the seconds in the minute, from 0 to 59.
 **/
@property (nonatomic, readonly) NSInteger seconds;
//}}}
// @property (nonatomic, readonly) NSInteger weekday;//{{{
/**
 * Gets the day of the week, 1 is Sunday, 7 is Saturday.
 **/
@property (nonatomic, readonly) NSInteger weekday;
//}}}
// @property (nonatomic, readonly) NSInteger dayOfYear;//{{{
/**
 * Gets the number of the day in the year.
 **/
@property (nonatomic, readonly) NSInteger dayOfYear;
//}}}
// @property (nonatomic, readonly) BOOL      leapYear;//{{{
/**
 * Gets a value indicating if the year in this object is a leap year.
 **/
@property (nonatomic, readonly) BOOL      leapYear;
//}}}

/** @name Designated Initializers */ //@{
// - (id)initWithYear:(int)year month:(int)month day:(int)day hour:(int)hour minute:(int)min seconds:(int)sec;//{{{
/**
 * Initializes the object with the information passed.
 * \param year The year of the time.
 * \param month The number of month. 1 is January, 12 is December.
 * \param day The month day.
 * \param hour The day hour.
 * \param min The minute in the hour.
 * \param sec Seconds in the minute.
 * \returns This object initialized.
 **/
- (id)initWithYear:(int)year month:(int)month day:(int)day hour:(int)hour minute:(int)min seconds:(int)sec;
//}}}
// - (id)initWithTime:(time_t)tt;//{{{
/**
 * Initializes the object with a \c time_t value.
 * \param tt The date value in a \c time_t data type.
 * \returns This object initialized.
 **/
- (id)initWithTime:(time_t)tt;
//}}}
// - (id)initWithAbsoluteTime:(CFAbsoluteTime)absoluteTime;//{{{
/**
 * Initializes the object with an \c CFAbsoluteTime value.
 * \param absoluteTime The time value in \c CFAbsoluteTime data type.
 * \returns This object initialized.
 **/
- (id)initWithAbsoluteTime:(CFAbsoluteTime)absoluteTime;
//}}}
// - (id)initWithDate:(NSDate*)date;//{{{
/**
 * Initializes with an \c NSDate date type.
 * \param date The \c NSDate information to inicialize this instance.
 * \returns This object initialized.
 **/
- (id)initWithDate:(NSDate*)date;
//}}}
//@}

/** @name Conversion Operations */ //@{
// - (time_t)cTime;//{{{
/**
 * Converts the time information in this object to a \c time_t data type.
 * @return The resulting \c time_t value.
 **/
- (time_t)cTime;
//}}}
// - (CFAbsoluteTime)absoluteTime;//{{{
/**
 * Converts the time information on this object to a \c CFAbsoluteTime data
 * type.
 * @returns The resulting \c CFAbsoluteTime.
 **/
- (CFAbsoluteTime)absoluteTime;
//}}}
// - (NSDate*)date;//{{{
/**
 * Converts this date/time information in an \c NSDate data type.
 * @return The resulting \c NSDate value.
 **/
- (NSDate*)date;
//}}}
// - (NSString*)stringWithFormat:(NSString*)formatSpec;//{{{
/**
 * Formats the date information into a string.
 * \param formatSpec Format specification. Supports the same format specifiers
 * as the \c strftime() standard C function.
 * @returns \c NSString with the formated value requested.
 **/
- (NSString*)stringWithFormat:(NSString*)formatSpec;
//}}}
//@}

/** @name Operations */ //@{
// - (void)changeYear:(int)year month:(int)month day:(int)day;//{{{
/**
 * Change the date parte of the information in this object.
 * \param year the Year number to set.
 * \param month The month to set. Valid months are from 1 to 12.
 * \param day The month day. From 1 to 31.
 **/
- (void)changeYear:(int)year month:(int)month day:(int)day;
//}}}
// - (void)changeHour:(int)hour minute:(int)min seconds:(int)sec;//{{{
/**
 * Change the time parte of the information in this object.
 * \param hour Hour of the day, from 0 to 23.
 * \param min Minute of the hour, from 0 to 59.
 * \param sec Seconds of the minute, from 0 to 59.
 **/
- (void)changeHour:(int)hour minute:(int)min seconds:(int)sec;
//}}}
//@}

/** @name Attributes */ //@{
// - (BOOL)isSameDate:(SFTime*)dateTime;//{{{
/**
 * Checks where the date information is equal to the passed object.
 * \param dateTime SFTime instance with information to check for equality.
 * Only the date part of the objects are compared.
 * \return \b YES if the two objects points to the same day, month and year.
 * Otherwise, \b NO.
 **/
- (BOOL)isSameDate:(SFTime*)dateTime;
//}}}
// - (BOOL)isSameTime:(SFTime*)dateTime;//{{{
/**
 * Checks where the time information is equal on both objects.
 * \param dateTime SFTime instance with information to check for equality.
 * Only the time part of the objects are compared.
 * \return \b YES if the two objects points to the same hour, minute and
 * second. Otherwise, \b NO.
 **/
- (BOOL)isSameTime:(SFTime*)dateTime;
//}}}
// - (BOOL)isEqualTo:(SFTime*)dateTime;//{{{
/**
 * Checks where the objects points to the same moment in time.
 * \param dateTime SFTime instance to compare to this object.
 * \return \b YES if the two objects points to the same moment in time, taking
 * account of date and time. Otherwise, \b NO.
 **/
- (BOOL)isEqualTo:(SFTime*)dateTime;
//}}}
// - (BOOL)isValid;//{{{
/**
 * Checks whether the date inside this object is valid.
 * By definition, a date of 1970-1-1 is invalid sinse its from a zero value \c
 * SFAbsoluteTime or \c time_t.
 * @returns \b YES when the object has a valid value. \b NO otherwise.
 **/
- (BOOL)isValid;
//}}}
//@}

// Class Methods
// + (SFTime*)now;//{{{
/**
 * Returns a \c SFTime object with the current local date and time.
 **/
+ (SFTime*)now;
//}}}
// + (SFTime*)dateTimeWithTime:(time_t)tt;//{{{
/**
 * Builds a SFTime object with a time in a \c time_t format.
 * @returns A temporary \c SFTime object with the passed value.
 **/
+ (SFTime*)dateTimeWithTime:(time_t)tt;
//}}}
// + (SFTime*)dateTimeWithAbsoluteTime:(CFAbsoluteTime)abst;//{{{
/**
 * Builds a SFTime object with an \c CFAbsoluteTime value.
 * @returns A temporary \c SFTime object with the passed value.
 **/
+ (SFTime*)dateTimeWithAbsoluteTime:(CFAbsoluteTime)abst;
//}}}
// + (SFTime*)dateTimeWithDate:(NSDate*)date;//{{{
/**
 * Builds a SFTime object with an \c NSDate value.
 * @returns A temporary \c SFTime object with the passed value.
 **/
+ (SFTime*)dateTimeWithDate:(NSDate*)date;
//}}}
// + (BOOL)isLeapYear:(NSInteger)year;//{{{
/**
 * Check if a year is a leap year.
 * @param year The year number, from 1 to 9999.
 * @returns \b YES when the passed year is a leap year. \b NO otherwise.
 **/
+ (BOOL)isLeapYear:(NSInteger)year;
//}}}
@end
///@} sf_time
// vim:ft=objc syntax=objc.doxygen
