/**
 * \file
 * Defines the SFTime Objective-C interface class.
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
#import "SFTime.h"
#import "sfdebug.h"

/* ===========================================================================
 * datetime_t structure
 * ======================================================================== */
typedef struct datetime_t {
    uint16_t year;                      /**< Year number, from 0 to 9999.   */
    uint8_t  mon;                       /**< Month, from 1 to 12.           */
    uint8_t  day;                       /**< Day of the month, 1 to 31.     */
    uint8_t  hour;                      /**< Hour in the day.               */
    uint8_t  min;                       /**< Minutes of hour.               */
    uint8_t  sec;                       /**< Seconds in the minute.         */
    uint8_t  wday;                      /**< Day of the week, 1 is Sunday.  */
} datetime_t;

/* ===========================================================================
 * SFTime EXTENSION
 * ======================================================================== */
@interface SFTime () {
    datetime_t m_date;
}
/** @name Internal */ //@{
// - (void)setAsDate:(NSDate*)date;//{{{
/**
 * Set the internal value as the passed date.
 * The function decompose the date passed to its components and set the
 * internal values.
 * @param date The date to initialize internal values.
 * @return Nothing.
 * @since 1.3
 **/
- (void)setAsDate:(NSDate*)date;
//}}}
//@}
@end

/* ===========================================================================
 * SFTime IMPLEMENTATION
 * ======================================================================== */
@implementation SFTime
// Properties
// @property (nonatomic, readonly) NSInteger year;//{{{
- (NSInteger)year { return (NSInteger)m_date.year; }
//}}}
// @property (nonatomic, readonly) NSInteger month;//{{{
- (NSInteger)month { return (NSInteger)m_date.mon; }
//}}}
// @property (nonatomic, readonly) NSInteger day;//{{{
- (NSInteger)day { return (NSInteger)m_date.day; }
//}}}
// @property (nonatomic, readonly) NSInteger hour;//{{{
- (NSInteger)hour { return (NSInteger)m_date.hour; }
//}}}
// @property (nonatomic, readonly) NSInteger minute;//{{{
- (NSInteger)minute { return (NSInteger)m_date.min; }
//}}}
// @property (nonatomic, readonly) NSInteger seconds;//{{{
- (NSInteger)seconds { return (NSInteger)m_date.sec; }
//}}}
// @property (nonatomic, readonly) NSInteger weekday;//{{{
- (NSInteger)weekday { return (NSInteger)m_date.wday; }
//}}}
// @property (nonatomic, readonly) NSInteger dayOfYear;//{{{
- (NSInteger)dayOfYear {
    int monthDays[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};
    return monthDays[m_date.mon-1] + m_date.day + (self.leapYear && m_date.mon > 2 ? 1 : 0);
}
//}}}
// @property (nonatomic, readonly) BOOL      leapYear;//{{{
- (BOOL)leapYear { return [SFTime isLeapYear:(NSInteger)m_date.year]; }
//}}}

// Designated Initializers
// - (id)initWithYear:(int)year month:(int)month day:(int)day hour:(int)hour minute:(int)min seconds:(int)sec;//{{{
- (id)initWithYear:(int)year month:(int)month day:(int)day hour:(int)hour minute:(int)min seconds:(int)sec
{
    self = [super init];
    if (self)
    {
        m_date.year = (uint16_t)((year < 0 || year > 9999) ? 0 : year);
        m_date.mon  = (uint8_t)((month < 1 || month > 12) ? 1 : month);
        m_date.day  = (uint8_t)((day < 1 || day > 31) ? 1 : day);
        m_date.hour = (uint8_t)((hour < 0 || hour > 23) ? 0 : hour);
        m_date.min  = (uint8_t)((min < 0 || min > 59) ? 0 : min);
        m_date.sec  = (uint8_t)((sec < 0 || sec > 59) ? 0 : sec);

        /* Computation to find the weekday. */
        intptr_t daysSince1970 = ((m_date.year - 1969) / 4);

        daysSince1970 = (m_date.year * 365) + daysSince1970 + self.dayOfYear;
        m_date.wday   = (uint8_t)((daysSince1970 - 4) % 7);
    }
    return self;
}
//}}}
// - (id)initWithTime:(time_t)tt;//{{{
- (id)initWithTime:(time_t)tt
{
    self = [super init];
    if (self)
    {
        struct tm* ptm;

        ptm = gmtime(&tt);

        m_date.year = (uint16_t)ptm->tm_year + 1900;
        m_date.mon  = (uint8_t)ptm->tm_mon + 1;
        m_date.day  = (uint8_t)ptm->tm_mday;
        m_date.hour = (uint8_t)ptm->tm_hour;
        m_date.min  = (uint8_t)ptm->tm_min;
        m_date.sec  = (uint8_t)ptm->tm_sec;
        m_date.wday = (uint8_t)(ptm->tm_wday <= 6 ? ptm->tm_wday + 1 : 7);
    }
    return self;
}
//}}}
// - (id)initWithAbsoluteTime:(CFAbsoluteTime)absoluteTime;//{{{
- (id)initWithAbsoluteTime:(CFAbsoluteTime)absoluteTime
{
    self = [super init];
    if (self)
    {
        NSDate *absDate = [[NSDate alloc] initWithTimeIntervalSinceReferenceDate:(NSTimeInterval)absoluteTime];
        [self setAsDate:absDate];
    }
    return self;
}
//}}}
// - (id)initWithDate:(NSDate*)date;//{{{
- (id)initWithDate:(NSDate*)date
{
    self = [super init];
    if (self) {
        [self setAsDate:date];
    }
    return self;
}
//}}}

// Conversion Operations
// - (time_t)cTime;//{{{
- (time_t)cTime
{
    struct tm tmt;

    tmt.tm_year = m_date.year - 1900;
    tmt.tm_mon  = m_date.mon - 1;
    tmt.tm_mday = m_date.day;
    tmt.tm_hour = m_date.hour;
    tmt.tm_min  = m_date.min;
    tmt.tm_sec  = m_date.sec;

    time_t tt = mktime(&tmt);

    /* mktime() converts the value to localtime. That is not what we want. We
     * need no convertion of the current value. So convert it back.
     * Note: tm_gmtoff is a field present in Mac OS X and iOS.
     */
    return (tt + tmt.tm_gmtoff);
}
//}}}
// - (CFAbsoluteTime)absoluteTime;//{{{
- (CFAbsoluteTime)absoluteTime
{
    NSDateComponents *comps = [[NSDateComponents alloc] init];

    comps.year   = m_date.year;
    comps.month  = m_date.mon;
    comps.day    = m_date.day;
    comps.hour   = m_date.hour;
    comps.minute = m_date.min;
    comps.second = m_date.sec;

    NSCalendar *cal = [NSCalendar currentCalendar];
    NSDate    *date = [cal dateFromComponents:comps];

    return date.timeIntervalSinceReferenceDate;
//    CFGregorianDate gd;
//
//    gd.year   = m_date.year;
//    gd.month  = m_date.mon;
//    gd.day    = m_date.day;
//    gd.hour   = m_date.hour;
//    gd.minute = m_date.min;
//    gd.second = m_date.sec;
//
//    return CFGregorianDateGetAbsoluteTime(gd, NULL);
}
//}}}
// - (NSDate*)date;//{{{
- (NSDate*)date
{
    CFAbsoluteTime abst = [self absoluteTime];
    return [NSDate dateWithTimeIntervalSinceReferenceDate:abst];
}
//}}}
// - (NSString*)stringWithFormat:(NSString*)formatSpec;//{{{
- (NSString*)stringWithFormat:(NSString*)formatSpec
{
    struct tm tmt;
    size_t length   = [formatSpec length] + 40;
    const char* fmt = [formatSpec cStringUsingEncoding:NSUTF8StringEncoding];
    char* buffer = (char*)malloc( length );

    tmt.tm_year = m_date.year - 1900;
    tmt.tm_mon  = m_date.mon - 1;
    tmt.tm_mday = m_date.day;
    tmt.tm_hour = m_date.hour;
    tmt.tm_min  = m_date.min;
    tmt.tm_sec  = m_date.sec;
    tmt.tm_isdst = 0;

    /* These two fields are present only in Mac OS X and iOS. */
    tmt.tm_gmtoff = 0;
    tmt.tm_zone   = "GMT";

    strftime(buffer, length, fmt, &tmt);

    NSString* result = [NSString stringWithCString:buffer encoding:NSUTF8StringEncoding];
    free(buffer);

    return result;
}
//}}}

// Operations
// - (void)changeYear:(int)year month:(int)month day:(int)day;//{{{
- (void)changeYear:(int)year month:(int)month day:(int)day
{
    m_date.year = ((year < 0 || year > 9999) ? 0 : year);
    m_date.mon  = ((month < 1 || month > 12) ? 1 : month);
    m_date.day  = ((day < 1 || day > 31) ? 1 : day);
}
//}}}
// - (void)changeHour:(int)hour minute:(int)min seconds:(int)sec;//{{{
- (void)changeHour:(int)hour minute:(int)min seconds:(int)sec
{
    m_date.hour = hour;
    m_date.min  = min;
    m_date.sec  = sec;
}
//}}}

// Attributes
// - (BOOL)isSameDate:(SFTime*)dateTime;//{{{
- (BOOL)isSameDate:(SFTime*)dateTime
{
    if (dateTime == nil) return NO;
    return ((dateTime.year == self.year) && (dateTime.month == self.month) && (dateTime.day == self.day));
}
//}}}
// - (BOOL)isSameTime:(SFTime*)dateTime;//{{{
- (BOOL)isSameTime:(SFTime*)dateTime
{
    if (dateTime == nil) return NO;
    return ((dateTime.hour == self.hour) && (dateTime.minute == self.minute) && (dateTime.seconds == self.seconds));
}
//}}}
// - (BOOL)isEqualTo:(SFTime*)dateTime;//{{{
- (BOOL)isEqualTo:(SFTime*)dateTime
{
    return ([self isSameDate:dateTime] && [self isSameTime:dateTime]);
}
//}}}
// - (BOOL)isValid;//{{{
- (BOOL)isValid
{
    return ([self cTime] > 0);
}
//}}}

// Class Methods
// + (SFTime*)now;//{{{
+ (SFTime*)now
{
    CFAbsoluteTime abst = CFAbsoluteTimeGetCurrent();

    return [[[SFTime alloc] initWithAbsoluteTime:abst] autorelease];
}
//}}}
// + (SFTime*)dateTimeWithTime:(time_t)tt;//{{{
+ (SFTime*)dateTimeWithTime:(time_t)tt
{
    SFTime* dt = [[SFTime alloc] initWithTime:tt];
    return [dt autorelease];
}
//}}}
// + (SFTime*)dateTimeWithAbsoluteTime:(CFAbsoluteTime)abst;//{{{
+ (SFTime*)dateTimeWithAbsoluteTime:(CFAbsoluteTime)abst
{
    SFTime* dt = [[SFTime alloc] initWithAbsoluteTime:abst];
    return [dt autorelease];
}
//}}}
// + (SFTime*)dateTimeWithDate:(NSDate*)date;//{{{
+ (SFTime*)dateTimeWithDate:(NSDate*)date
{
    SFTime* dt = [[SFTime alloc] initWithDate:date];
    return [dt autorelease];
}
//}}}
// + (BOOL)isLeapYear:(NSInteger)year;//{{{
+ (BOOL)isLeapYear:(NSInteger)year
{
    return (((year & 3) == 0) && (((year % 100) != 0) || ((year % 400) == 0)));
}
//}}}

// Internal
// - (void)setAsDate:(NSDate*)date;//{{{
- (void)setAsDate:(NSDate*)date
{
    NSCalendar *cal = [NSCalendar currentCalendar];
    unsigned flags  = NSCalendarUnitYear | NSCalendarUnitMonth | NSCalendarUnitDay |
                      NSCalendarUnitHour | NSCalendarUnitMinute | NSCalendarUnitSecond |
                      NSCalendarUnitWeekday;
    NSDateComponents *comp = [cal components:flags fromDate:date];

    m_date.year = (uint16_t)comp.year;
    m_date.mon  = (uint8_t)comp.month;
    m_date.day  = (uint8_t)comp.day;
    m_date.hour = (uint8_t)comp.hour;
    m_date.min  = (uint8_t)comp.minute;
    m_date.sec  = (uint8_t)comp.second;
    m_date.wday = (uint8_t)comp.weekday;
}
//}}}
@end
// vim:syntax=objc.doxygen
