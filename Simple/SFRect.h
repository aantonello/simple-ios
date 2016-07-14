/**
 * \file
 * Macros and functions to work with CGRect structure.
 *
 * \author Alessandro Antonello aantonello@paralaxe.com.br
 * \date   March 14, 2013
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#import <Foundation/Foundation.h>
#import <CoreGraphics/CGGeometry.h>

/**
 * \ingroup sf_general
 * Constants to be used with \c SFRect alignment operations.
 *//* --------------------------------------------------------------------- */
typedef NS_ENUM(NSUInteger, SFRectAlign) {
    // SFRectAlignLeft             = 0x0001,//{{{
    /**
     * Aligns the X coordinate of the object to match the X coordinate of the
     * referencing rectangle.
     * This flag changes only the x origin coordinate of the object making it
     * match the x origin coordinate of the referencing rectangle.
     **/
    SFRectAlignLeft             = 0x0001,
    //}}}
    // SFRectAlignTop              = 0x0002,//{{{
    /**
     * Aligns the Y coordinate of the object to match the Y coordinate of the
     * referencing rectangle.
     * This flag only changes the y origin coordinate of the object to match
     * the y origin coordinate of the referencing rectangle.
     **/
    SFRectAlignTop              = 0x0002,
    //}}}
    // SFRectAlignRight            = 0x0004,//{{{
    /**
     * Aligns the right most X coordinate of the object to macth the right
     * most X coordinate of the referencing rectangle.
     * This flag changes the x coordinate of the object so its right
     * coordinate (x + width) matches the right coordinate of the referencing
     * rectangle.
     **/
    SFRectAlignRight            = 0x0004,
    //}}}
    // SFRectAlignBottom           = 0x0008,//{{{
    /**
     * Aligns the bottom most Y coordinate of the object to match the bottom
     * most Y coordinate of the referencing rectangle.
     * This flag changes the Y origin coordinate of the object so its bottom
     * coordinate (y + height) matches the bottom coordinate of the
     * referencing rectangle.
     **/
    SFRectAlignBottom           = 0x0008,
    //}}}
    // SFRectAlignAtLeft           = 0x0010,//{{{
    /**
     * Aligns the object at the left side of the referencing rectangle.
     * This flag changes the x origin coordinate of the object so its right
     * coordinate (x + width) matches the x origin coordinate of the
     * referencing rectangle.
     **/
    SFRectAlignAtLeft           = 0x0010,
    //}}}
    // SFRectAlignAtTop            = 0x0020,//{{{
    /**
     * Aligns the object above the referencing rectangle.
     * This flag changes the y origin coordinate of the object so its bottom
     * coordinate (y + height) matches the y coordinate of the referencing
     * rectangle.
     **/
    SFRectAlignAtTop            = 0x0020,
    //}}}
    // SFRectAlignAtRight          = 0x0040,//{{{
    /**
     * Aligns the object at the right side of the referencing rectangle.
     * This flag changes the x origin coordinate of the object so its match
     * the right coordinate (x + width) of the referencing rectangle.
     **/
    SFRectAlignAtRight          = 0x0040,
    //}}}
    // SFRectAlignAtBottom         = 0x0080,//{{{
    /**
     * Aligns the object below the referencing rectangle.
     * The flag changes the y origin coordinate of the object so it matches
     * the bottom coordinate (y + height) of the referencing rectangle.
     **/
    SFRectAlignAtBottom         = 0x0080,
    //}}}
    // SFRectAlignCenterHorizontal = 0x0100,//{{{
    /**
     * Aligns the object in the center of the referencing rectangle
     * horizontaly.
     * This flag changes the x coordinate of the object so its center point
     * matches the center point of the referencing rectangle.
     **/
    SFRectAlignCenterHorizontal = 0x0100,
    //}}}
    // SFRectAlignCenterVertical   = 0x0200,//{{{
    /**
     * Aligns the object in the center of the referencing rectangle verticaly.
     * This flag changes the y coordinate of the object so its center point
     * matches the center point of the referencing rectangle.
     **/
    SFRectAlignCenterVertical   = 0x0200,
    //}}}
    // SFRectAlignCenter           = (0x0100 | 0x0200)//{{{
    /**
     * Aligns the object in the center of the referencing rectangle.
     **/
    SFRectAlignCenter           = (0x0100 | 0x0200)
    //}}}
};

/**
 * \ingroup sf_general
 * Constants to be used with \c SFRect stretching operations.
 *//* --------------------------------------------------------------------- */
typedef NS_ENUM(NSUInteger, SFRectStretch) {
    // SFRectStretchWidth  = 0x0001,//{{{
    /**
     * Matches the width of the object with the width of the referencing
     * rectangle.
     **/
    SFRectStretchWidth  = 0x0001,
    //}}}
    // SFRectStretchHeight = 0x0002,//{{{
    /**
     * Matches the height of the object with the height of the referencing
     * rectangle.
     **/
    SFRectStretchHeight = 0x0002,
    //}}}
    // SFRectStretchFit    = 0x0004,//{{{
    /**
     * Matches the width or height of the object with width or height of the
     * referencing rectangle.
     * The operation will choose which size to match based on keeping the
     * aspect ratio of the object. The object will fit inside the referencing
     * rectangle while its aspect ratio is preserved.
     **/
    SFRectStretchFit    = 0x0004,
    //}}}
    // SFRectStretchMatch  = (0x0001 | 0x0002)//{{{
    /**
     * Matches the width and height of the object with width and height of the
     * referencing rectangle.
     **/
    SFRectStretchMatch  = (0x0001 | 0x0002)
    //}}}
};

/**
 * \ingroup sf_general
 * Structure for rectangle coordinates.
 * This structure is similar with \c CGRect. The major differences are on its
 * members. This structure doesn't has others structures as its contents.
 * Instead it has four members of type \c CGFloat with the four coordinates of
 * the rectangle.
 * @since 1.3
 *//* --------------------------------------------------------------------- */
struct SF_RECT {
    CGFloat left;
    CGFloat top;
    CGFloat right;
    CGFloat bottom;
};
typedef struct SF_RECT rect_t;

/** \name Create a rect_t structure */ //@{
// rect_t SFRectMake(CGFloat l, CGFloat t, CGFloat r, CGFloat b);//{{{
/**
 * \ingroup sf_general
 * Builds an rect_t structure with the passed coordinates.
 * @param l Left coordinate.
 * @param t Top coordinate.
 * @param r Right coordinate.
 * @param b Bottom coordinate.
 * @returns The built rect_t structure.
 * @since 1.3
 **/
rect_t SFRectMake(CGFloat l, CGFloat t, CGFloat r, CGFloat b);
//}}}
// rect_t SFRectMakeWithOriginAndSize(CGPoint origin, CGSize size);//{{{
/**
 * \ingroup sf_general
 * Builds an rect_t structure from origin and size.
 * @param origin A CGPoint structure with the rectangle's origin.
 * @param size A CGSize structure with the rectangle's size. The values in
 * this structure will be translated into rect_t::right and rect_t::bottom
 * coordinates.
 * @return The rect_t structure created.
 * @since 1.3
 **/
rect_t SFRectMakeWithOriginAndSize(CGPoint origin, CGSize size);
//}}}
// rect_t SFRectMakeWithPosAndLength(CGFloat x, CGFloat y, CGFloat w, CGFloat h);//{{{
/**
 * \ingroup sf_general
 * Builds an rect_t structure with position and length.
 * @param x Left coordinate.
 * @param y Top coordinate.
 * @param w Horizontal length of the rectangle.
 * @param h Vertical length of the rectangle.
 * @return The rect_t structure created.
 * @remarks This function can be used as a drop in replacement of
 * \c CGRectMake().
 * @since 1.3
 **/
rect_t SFRectMakeWithPosAndLength(CGFloat x, CGFloat y, CGFloat w, CGFloat h);
//}}}
//@}

/** \name rect_t Members Access and Conversion */ //@{
// CGFloat SFRectMinX(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Gets the minimal horizontal coordinate of the rectangle.
 * @param sfRect Rectangle to get the minimal horizontal coordinate.
 * @return The minimal horizontal coordinate.
 * @remarks This is the same as rect_t::left member value. It serves as a drop
 * in replacement for \c CGRectGetMinX() function.
 * @since 1.3
 **/
CGFloat SFRectMinX(rect_t sfRect);
//}}}
// CGFloat SFRectMaxX(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Gets the maximum horizontal coordinate of the rectangle.
 * @param sfRect Rectangle to get the maximum horizontal coordinate.
 * @return The maximum horizontal coordinate.
 * @remarks This is the same as rect_t::right member value. It serves as
 * a drop in replacement for \c CGRectGetMaxX() function.
 * @since 1.3
 **/
CGFloat SFRectMaxX(rect_t sfRect);
//}}}
// CGFloat SFRectMinY(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Gets the minimal vertical coordinate of the rectangle.
 * @param sfRect Rectangle to get the minimal vertical coordinate.
 * @return The minimal vertical coordinate.
 * @remarks This is the same as rect_t::top member value. It serves as a drop
 * in replacement for \c CGRectGetMinY() function.
 * @since 1.3
 **/
CGFloat SFRectMinY(rect_t sfRect);
//}}}
// CGFloat SFRectMaxY(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Gets the maximum vertical coordinate of the rectangle.
 * @param sfRect Rectangle to get the maximum vertical coordinate.
 * @return The maximum vertical coordinate.
 * @remarks This is the same as rect_t::bottom member value. It serves as
 * a drop in replacement for \c CGRectGetMinY() function.
 * @since 1.3
 **/
CGFloat SFRectMaxY(rect_t sfRect);
//}}}
// CGFloat SFRectWidth(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Gets the horizontal length of the rectangle.
 * @param sfRect Rectangle to get the horizontal length.
 * @return The horizontal length of the passed rectangle.
 * @remarks This is the same as (rect_t::right - rect_t::left). It serves as
 * a drop in replacement for \c CGRectGetWidth() function.
 * @since 1.3
 **/
CGFloat SFRectWidth(rect_t sfRect);
//}}}
// CGFloat SFRectHeight(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Gets the vertical length of the rectangle.
 * @param sfRect Rectangle to get the vertical length.
 * @return The vertical length of the passed rectangle.
 * @remarks This is the same as (rect_t::bottom - rect_t::top). It serves as
 * a drop in replacement for \c CGRectGetHeight() function.
 * @since 1.3
 **/
CGFloat SFRectHeight(rect_t sfRect);
//}}}

// CGPoint SFRectGetOrigin(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Retrieves the origin point of the rectangle.
 * @param sfRect rect_t to retrieve the origin point.
 * @return A \c CGPoint structure with the origin point of the rectangle.
 * @since 1.3
 **/
CGPoint SFRectGetOrigin(rect_t sfRect);
//}}}
// rect_t  SFRectSetOrigin(rect_t sfRect, CGPoint origin);//{{{
/**
 * \ingroup sf_general
 * Changes the origin point of the rectangle.
 * @param sfRect rect_t whose origin point should be changed.
 * @param origin \c CGPoint structure with the new origin point.
 * @return A new rect_t with the coordinates changed.
 * @remarks Changing the origin point will change the rect_t::left and
 * rect_t::top coordinates and also the rect_t::right and rect_t::bottom
 * coordinates. The effect is the same as changing the origin of a \c CGRect
 * structure with, in fact, changes the rectangle's position.
 * @since 1.3
 **/
rect_t  SFRectSetOrigin(rect_t sfRect, CGPoint origin);
//}}}
// CGSize  SFRectGetSize(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Retrieves the size of the rectangle.
 * @param sfRect rect_t structure with size should be retrieved.
 * @return A \c CGSize structure with the size of the rectangle.
 * @since 1.3
 **/
CGSize  SFRectGetSize(rect_t sfRect);
//}}}
// rect_t  SFRectSetSize(rect_t sfRect, CGSize size);//{{{
/**
 * \ingroup sf_general
 * Changes the size of the passed rectangle.
 * @param sfRect rect_t structure to change its size.
 * @param size \c CGSize with the new size for the rectangle.
 * @return An rect_t structure with the new size.
 * @remarks Only rect_t::right and rect_t::bottom coordinates are changed in
 * this operation.
 * @since 1.3
 **/
rect_t  SFRectSetSize(rect_t sfRect, CGSize size);
//}}}
// CGPoint SFRectGetCenter(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Retrieves the center point of the passed rectangle.
 * @param sfRect rect_t to get the center point.
 * @return \c CGPoint structure with the center position of the \a sfRect
 * rectangle.
 * @since 1.3
 **/
CGPoint SFRectGetCenter(rect_t sfRect);
//}}}
// rect_t  SFRectSetCenter(rect_t sfRect, CGPoint center);//{{{
/**
 * \ingroup sf_general
 * Centers the rectangle at the given point.
 * @param sfRect Rectangle to center.
 * @param center \c CGPoint structure with coordinates of the new center
 * position for the \a sfRect rectangle.
 * @return A rect_t structure with the same width and height of \a sfRect
 * argument centered in the \a center point passed.
 * @since 1.3
 **/
rect_t  SFRectSetCenter(rect_t sfRect, CGPoint center);
//}}}
//@}

/** \name Working With Rectangles */ //@{
// rect_t SFRectOffset(rect_t sfRect, CGFloat dx, CGFloat dy);//{{{
/**
 * Moves the rectangle by the passed offsets.
 * @param sfRect Rectangle to move.
 * @param dx Distance to move in the horizontal coordinate.
 * @param dy Distance to move in the vertical coordinate.
 * @return An \c rect_t structure with the coordinates of the passed \a sfRect
 * rectangle moved by the extent requested.
 * @since 1.3
 **/
rect_t SFRectOffset(rect_t sfRect, CGFloat dx, CGFloat dy);
//}}}
// rect_t SFRectMove(rect_t sfRect, CGFloat x, CGFloat y);//{{{
/**
 * Moves a rectangle for the given coordinates.
 * @param sfRect Rectangle to move.
 * @param x The horizontal coordinate to move the rectangle to.
 * @param y The vertical coordinate to move the rectangle to.
 * @return \c rect_t structure with the new coordinates.
 * @since 1.3
 **/
rect_t SFRectMove(rect_t sfRect, CGFloat x, CGFloat y);
//}}}
// rect_t SFRectDeflate(rect_t sfRect, CGFloat l, CGFloat t, CGFloat r, CGFloat b);//{{{
/**
 * \ingroup sf_general
 * Deflate or inflate the given rectangle.
 * @param sfRect Rectangle to be deflated or inflated.
 * @param l Amount to be added to the rectangle's \e left coordinate.
 * @param t Amount to be added to the rectangle's \e top coordinate.
 * @param r Amount to be subtracted from the rectangle's \e right coordinate.
 * @param b Amount to be subtracted from the rectangle's \e bottom coordinate.
 * @return An rect_t structure with the coordinates of the \a sfRect rectangle
 * changed according the parameters passed.
 * @since 1.3
 **/
rect_t SFRectDeflate(rect_t sfRect, CGFloat l, CGFloat t, CGFloat r, CGFloat b);
//}}}
// rect_t SFRectAlignAt(rect_t sfRect, SFRectAlign flags, rect_t reference);//{{{
/**
 * \ingroup sf_general
 * Aligns a rectangle with a reference rectangle.
 * @param sfRect Rectangle to be aligned.
 * @param flags Bit flags for the alignment operation. This value is
 * a combination of the SFRectAlign enumeration values.
 * @param reference The reference rectangle to align the \a sfRect parameter.
 * @return A new rect_t structure with aligned according with the passed
 * values.
 * @since 1.3
 **/
rect_t SFRectAlignAt(rect_t sfRect, SFRectAlign flags, rect_t reference);
//}}}
// rect_t SFRectFit(rect_t sfRect, SFRectStretch flags, rect_t ref);//{{{
/**
 * \ingroup sf_general
 * Sizes one rectangle according to another rectangle as reference.
 * @param sfRect Rectangle to be resized.
 * @param flags Set of flags defining how \a sfRect will be stretched. Valid
 * values are combinations of SFRectStretch enumeration values.
 * @param ref The rectangle for reference.
 * @return A new \c rect_t structure with the changes made.
 * @remarks You cannot combine \c SFRectStretchMatch with \c SFRectStretchFit.
 * Doing so will not keep this objects aspect ratio because \c
 * SFRectStretchMatch takes precedense.
 * @since 1.3
 **/
rect_t SFRectFit(rect_t sfRect, SFRectStretch flags, rect_t ref);
//}}}
// rect_t SFRectIntersect(rect_t rc1, rect_t rc2);//{{{
/**
 * \ingroup sf_general
 * Builds a rectangle by the intersection of two another rectangles.
 * @param rc1 First rectangle.
 * @param rc2 Second rectangle.
 * @return A rectangle built from the intersection of the passed rectangles.
 * If the two rectangles does not intersect, the resulting rectangle will be
 * empty.
 * @since 1.3
 **/
rect_t SFRectIntersect(rect_t rc1, rect_t rc2);
//}}}
// rect_t SFRectUnion(rect_t rc1, rect_t rc2);//{{{
/**
 * \ingroup sf_general
 * Builds a rectangle by the union of two others rectangles.
 * @param rc1 First rectangle.
 * @param rc2 Second rectangle.
 * @return A rectangle built from the union of the passed rectangles.
 * @since 1.3
 **/
rect_t SFRectUnion(rect_t rc1, rect_t rc2);
//}}}
//@}

/** \name Conversions */ //@{
// CGRect SFRectToCGRect(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Converts a \c rect_t structure into a \c CGRect structure.
 * @param sfRect \c rect_t structure to convert.
 * @return The \c CGRect structure.
 * @since 1.3
 **/
CGRect SFRectToCGRect(rect_t sfRect);
//}}}
// rect_t CGRectToSFRect(CGRect rect);//{{{
/**
 * \ingroup sf_general
 * Converts a \c CGRect structure into a \c rect_t structure.
 * @param rect \c CGRect structure to convert.
 * @return The \c rect_t structure.
 * @since 1.3
 **/
rect_t CGRectToSFRect(CGRect rect);
//}}}
//@}

/** \name Information */ //@{
// BOOL SFRectIsEmpty(rect_t sfRect);//{{{
/**
 * \ingroup sf_general
 * Check if the passed rectangle is empty.
 * @param sfRect \c rect_t to be checked.
 * @returns \b YES if the passed argument has no horizontal or vertical
 * length. Otherwise \b NO.
 * @since 1.3
 **/
BOOL SFRectIsEmpty(rect_t sfRect);
//}}}
// BOOL SFRectHasPoint(rect_t sfRect, CGPoint point);//{{{
/**
 * \ingroup sf_general
 * Checks whether a point lies into the passed rectangle.
 * @param sfRect \c rect_t structure to check.
 * @param point \c CGPoint to be checked.
 * @return \b YES if the \a point coordinates are inside the \a sfRect
 * structure boundaries. Othersize \b NO.
 * @since 1.3
 **/
BOOL SFRectHasPoint(rect_t sfRect, CGPoint point);
//}}}
// BOOL SFRectContainsRect(rect_t sfRect, rect_t rect);//{{{
/**
 * \ingroup sf_general
 * Checks whether a rectangle contains another rectangle.
 * @param sfRect Rectangle to check.
 * @param rect Rectangle with coordinates to be checked.
 * @return \b YES if \a sfRect contains all the coordinates of \a rect. \b NO
 * otherwise.
 * @remarks All the coordinates of \a rect structure must be inside the \a
 * sfRect structure for this function returns \b YES.
 * @since 1.3
 **/
BOOL SFRectContainsRect(rect_t sfRect, rect_t rect);
//}}}
//@}

/** \name Formating */ //@{
// NSString *SFRectFormat(rect_t sfRect, NSString *format);//{{{
/**
 * \ingroup sf_general
 * Formats the coordinates of the rectangle into a string.
 * @param sfRect Rectangle to be formated.
 * @param format A \c NSString object with the formating specification. The
 * specification is a series of characters preceeded by a percent sign. The
 * following characters are accepted:
 * - `l`: Will format the left most coordinate as decimal value.
 * - `t`: Will format the top most coordinate as decimal value.
 * - `r`: Will format the right most coordinate as decimal value.
 * - `b`: Will format the bottom most coordinate as decimal value.
 * - `w`: Will format the width length as decimal value.
 * - `h`: Will format the height length as decimal value.
 * - 'C': Formats the coordinates of the object as of the specification
 *        "%lx%t : %rx%b" was passed.
 * - 'R': Formats the rectangle information of the object as of the
 *        specification "%l, %t : %w, %h" was passed.
 * .
 * @returns A `NSString` object with the coordinates formated as specified.
 * @since 1.3
 **/
NSString *SFRectFormat(rect_t sfRect, NSString *format);
//}}}
//@}

/**
 * \ingroup sf_general
 * Interface implementing the simple \c CGRect structure.
 * This interface brings functionality and behavior similar to the CGRect
 * structure by packing all its members into properties and methods.
 *//* --------------------------------------------------------------------- */
@interface SFRect : NSObject
/** \name Properties */ //@{
// @property (nonatomic, assign) CGFloat left;//{{{
/**
 * Gets or sets the left most coordinate of this object.
 * Changing this value has the effect of move the rectangle horizontally.
 **/
@property (nonatomic, assign) CGFloat left;
//}}}
// @property (nonatomic, assign) CGFloat top;//{{{
/**
 * Gets or sets the top most coordinate of this object.
 * Changing this value has the effect of move the rectangle vertically.
 **/
@property (nonatomic, assign) CGFloat top;
//}}}
// @property (nonatomic, assign) CGFloat width;//{{{
/**
 * Gets or sets the width of this object.
 * Changing this value changes the width of the rectangle which will change
 * its SFRect::right position.
 **/
@property (nonatomic, assign) CGFloat width;
//}}}
// @property (nonatomic, assign) CGFloat height;//{{{
/**
 * Gets or sets the height of this object.
 * Changing this value changes the height of the rectangle which will change
 * its SFRect::bottom position.
 **/
@property (nonatomic, assign) CGFloat height;
//}}}
// @property (nonatomic, assign) CGFloat right;//{{{
/**
 * Gets or sets the right most coordinate of this object.
 * Changing this value doesn't moves the rectangle. Instead its width is
 * streched according to the coordinate defined here.
 **/
@property (nonatomic, assign) CGFloat right;
//}}}
// @property (nonatomic, assign) CGFloat bottom;//{{{
/**
 * Gets or sets the bottom coordinate of this object.
 * Changing this value doesn't moves the rectangle. Instead its height is
 * streched according to the coordinate defined here.
 **/
@property (nonatomic, assign) CGFloat bottom;
//}}}
// @property (nonatomic, assign) CGPoint origin;//{{{
/**
 * Gets or sets the origin coordinate of this object.
 **/
@property (nonatomic, assign) CGPoint origin;
//}}}
// @property (nonatomic, assign) CGSize  size;//{{{
/**
 * Gets or sets the size of this object.
 **/
@property (nonatomic, assign) CGSize  size;
//}}}
// @property (nonatomic, assign) CGPoint center;//{{{
/**
 * Gets or sets the central point of this object.
 * When setting this property it changes the left and top coordinates of this
 * object so its center matchs the value defined.
 **/
@property (nonatomic, assign) CGPoint center;
//}}}
// @property (nonatomic, assign) CGRect  rect;//{{{
/**
 * Sets or retrives the underlying CGRect structure of this object.
 **/
@property (nonatomic, assign) CGRect  rect;
//}}}
//@}

/** \name Designated Initializations */ //@{
// - (instancetype)initWithCGRect:(CGRect)rect;//{{{
/**
 * Initializes this object by copying the coordinates of the passed \c CGRect
 * structure.
 * @param rect A \c CGRect structure which coordinates will be used to
 * initialize this object coordinates.
 * @return This object initialized.
 **/
- (instancetype)initWithCGRect:(CGRect)rect;
//}}}
// - (instancetype)initWithOrigin:(CGPoint)origin andSize:(CGSize)size;//{{{
/**
 * Initializes this object with origin and size.
 * @param origin A \c CGPoint structure to initialize the origin of this
 * object.
 * @param size A \c CGSize structure to initialize the size of this object.
 * @return This object initialized.
 **/
- (instancetype)initWithOrigin:(CGPoint)origin andSize:(CGSize)size;
//}}}
// - (instancetype)initWithMinX:(CGFloat)x minY:(CGFloat)y maxX:(CGFloat)r maxY:(CGFloat)b;//{{{
/**
 * Initializes this object with the passed coordinates.
 * @param l The left most x coordinate to initialize the #left property of
 * this object.
 * @param t The top most y coordinate to initialize the #top property of this
 * object.
 * @param r The right most x coordinate to initialize the #right property of
 * this object.
 * @param b The bottom most y coordinate to initialize the #bottom property of
 * this object.
 * @return This object initialized.
 **/
- (instancetype)initWithMinX:(CGFloat)l minY:(CGFloat)t maxX:(CGFloat)r maxY:(CGFloat)b;
//}}}
// - (instancetype)initWithMinX:(CGFloat)x minY:(CGFloat)y width:(CGFloat)w height:(CGFloat)h;//{{{
/**
 * Initialize this object with the passed coordinates and sizes.
 * @param l The left most x coordinate to initialize the #left property of
 * this object.
 * @param t The top most y coordinate to initialize the #top property of this
 * object.
 * @param w The width to initialize the #width property of this object.
 * @param h The height to initialize the #height property of this object.
 * @return This object initialized.
 **/
- (instancetype)initWithMinX:(CGFloat)l minY:(CGFloat)t width:(CGFloat)w height:(CGFloat)h;
//}}}
//@}

/** \name Helper Operations */ //@{
// - (SFRect*)deflateLeft:(CGFloat)l top:(CGFloat)t right:(CGFloat)r bottom:(CGFloat)b;//{{{
/**
 * Changes the coordinates of this object by the amount passed.
 * @param l Amount to be added to the #left coordinate of this object.
 * @param t Amount to be added to the #top coordinate of this object.
 * @param r Amount to be subtracted from the #right coordinate of this object.
 * @param b Amount to be subtracted from the #bottom coordinate of this
 * object.
 * @return This object with its coordinates changed according to the passed
 * values.
 * @remarks Deflating a rectangle means shriking its size. By passing negative
 * values in the parameter the effect is inverse, increasing the rectangle's
 * size.
 * @note The changes are made *in loco*. That is, the returned reference is
 * this object after the change.
 **/
- (SFRect*)deflateLeft:(CGFloat)l top:(CGFloat)t right:(CGFloat)r bottom:(CGFloat)b;
//}}}
// - (SFRect*)align:(SFRectAlign)flags atRect:(SFRect*)rect;//{{{
/**
 * Aligns this object with another \c SFRect object as reference.
 * @param flags Set of flags defining the way this object will be aligned to
 * the referencing rectangle. This parameter accept combinations of the
 * SFRectAlign enum values.
 * @param rect The rectangle for reference.
 * @return This object after changes made.
 * @remarks Not all values of \c SFRectAlign can be combined. For example,
 * combining \c SFRectAlingLeft with \c SFRectAlignAtLeft will be the result
 * as of only \c SFRectAlignAtLeft was passed.
 **/
- (SFRect*)align:(SFRectAlign)flags atRect:(SFRect*)rect;
//}}}
// - (SFRect*)align:(SFRectAlign)flags atCGRect:(CGRect)rect;//{{{
/**
 * Aligns this object with a \c CGRect structure as reference.
 * @param flags Set of flags defining the way this object will be aligned to
 * the referencing rectangle. This parameter accept combinations of the
 * SFRectAlign enum values.
 * @param rect The rectangle for reference.
 * @return This object after changes made.
 * @remarks Not all values of \c SFRectAlign can be combined. For example,
 * combining \c SFRectAlingLeft with \c SFRectAlignAtLeft will be the result
 * as of only \c SFRectAlignAtLeft was passed.
 * @note The changes are made *in loco*. That is, the returned reference is
 * this object after the change.
 **/
- (SFRect*)align:(SFRectAlign)flags atCGRect:(CGRect)rect;
//}}}
// - (SFRect*)stretch:(SFRectStretch)flags atRect:(SFRect*)rect;//{{{
/**
 * Sizes this object according to another rectangle as reference.
 * @param flags Set of flags defining how this object will be stretched. Valid
 * values are combinations of \c SFRectStretch enumeration values.
 * @param rect The rectangle for reference.
 * @return This object after changes made.
 * @remarks You cannot combine \c SFRectStretchMatch with \c SFRectStretchFit.
 * Doing so will not keep this objects aspect ratio because \c
 * SFRectStretchMatch takes precedense.
 * @note The changes are made *in loco*. That is, the returned reference is
 * this object after the change.
 **/
- (SFRect*)stretch:(SFRectStretch)flags atRect:(SFRect*)rect;
//}}}
// - (SFRect*)stretch:(SFRectStretch)flags atCGRect:(CGRect)rect;//{{{
/**
 * Sizes this object according to another rectangle as reference.
 * @param flags Set of flags defining how this object will be stretched. Valid
 * values are combinations of \c SFRectStretch enumeration values.
 * @param rect The rectangle for reference.
 * @return This object after changes made.
 * @remarks You cannot combine \c SFRectStretchMatch with \c SFRectStretchFit.
 * Doing so will not keep this objects aspect ratio because \c
 * SFRectStretchMatch takes precedense.
 * @note The changes are made *in loco*. That is, the returned reference is
 * this object after the change.
 **/
- (SFRect*)stretch:(SFRectStretch)flags atCGRect:(CGRect)rect;
//}}}
//@}

/** \name Builds a new SFRect instance */ //@{
// - (SFRect*)rectByDeflatingLeft:(CGFloat)l top:(CGFloat)t right:(CGFloat)r bottom:(CGFloat)b;//{{{
/**
 * Changes the coordinates of this object by the amount passed.
 * @param l Amount to be added to the #left coordinate of this object.
 * @param t Amount to be added to the #top coordinate of this object.
 * @param r Amount to be subtracted from the #right coordinate of this object.
 * @param b Amount to be subtracted from the #bottom coordinate of this
 * object.
 * @return A new \c SFRect object with its coordinates made by applying the
 * amounts on this object instance.
 * @remarks Deflating a rectangle means shriking its size. By passing negative
 * values in the parameter the effect is inverse, increasing the rectangle's
 * size.
 * @note This object coordinates remains unchanged.
 **/
- (SFRect*)rectByDeflatingLeft:(CGFloat)l top:(CGFloat)t right:(CGFloat)r bottom:(CGFloat)b;
//}}}
// - (SFRect*)rectByAlign:(SFRectAlign)flags atRect:(SFRect*)rect;//{{{
/**
 * Aligns this object with another \c SFRect object as reference.
 * @param flags Set of flags defining the way this object will be aligned to
 * the referencing rectangle. This parameter accept combinations of the
 * SFRectAlign enum values.
 * @param rect The rectangle for reference.
 * @return A new \c SFRect object with its coordinates made by the alignment
 * of this object with the referencing rectangle.
 * @remarks Not all values of \c SFRectAlign can be combined. For example,
 * combining \c SFRectAlingLeft with \c SFRectAlignAtLeft will be the result
 * as of only \c SFRectAlignAtLeft was passed.
 * @note This object coordinates remain unchanged.
 **/
- (SFRect*)rectByAlign:(SFRectAlign)flags atRect:(SFRect*)rect;
//}}}
// - (SFRect*)rectByAlign:(SFRectAlign)flags atCGRect:(CGRect)rect;//{{{
/**
 * Aligns this object with another \c SFRect object as reference.
 * @param flags Set of flags defining the way this object will be aligned to
 * the referencing rectangle. This parameter accept combinations of the
 * SFRectAlign enum values.
 * @param rect The rectangle for reference.
 * @return A new \c SFRect object with its coordinates made by the alignment
 * of this object with the referencing rectangle.
 * @remarks Not all values of \c SFRectAlign can be combined. For example,
 * combining \c SFRectAlingLeft with \c SFRectAlignAtLeft will be the result
 * as of only \c SFRectAlignAtLeft was passed.
 * @note This object coordinates remain unchanged.
 **/
- (SFRect*)rectByAlign:(SFRectAlign)flags atCGRect:(CGRect)rect;
//}}}
// - (SFRect*)rectByStretch:(SFRectStretch)flags atRect:(SFRect*)rect;//{{{
/**
 * Sizes this object according to another rectangle as reference.
 * @param flags Set of flags defining how this object will be stretched. Valid
 * values are combinations of \c SFRectStretch enumeration values.
 * @param rect The rectangle for reference.
 * @return A new \c SFRect object by stretching the coordinates of this
 * rectangle according to the parameter passed.
 * @remarks You cannot combine \c SFRectStretchMatch with \c SFRectStretchFit.
 * Doing so will not keep this objects aspect ratio because \c
 * SFRectStretchMatch takes precedense.
 * @note This object coordinates remain unchanged.
 **/
- (SFRect*)rectByStretch:(SFRectStretch)flags atRect:(SFRect*)rect;
//}}}
// - (SFRect*)rectByStretch:(SFRectStretch)flags atCGRect:(CGRect)rect;//{{{
/**
 * Sizes this object according to another rectangle as reference.
 * @param flags Set of flags defining how this object will be stretched. Valid
 * values are combinations of \c SFRectStretch enumeration values.
 * @param rect The rectangle for reference.
 * @return A new \c SFRect object by stretching the coordinates of this
 * rectangle according to the parameter passed.
 * @remarks You cannot combine \c SFRectStretchMatch with \c SFRectStretchFit.
 * Doing so will not keep this objects aspect ratio because \c
 * SFRectStretchMatch takes precedense.
 * @note This object coordinates remain unchanged.
 **/
- (SFRect*)rectByStretch:(SFRectStretch)flags atCGRect:(CGRect)rect;
//}}}
// - (SFRect*)rectByIntersectingWithRect:(CGRect)rect;//{{{
/**
 * Retrieves a rectangle made by the intersection of this object with the
 * passed rectangle.
 * @param rect A \c CGRect structure.
 * @return An object built by the intersection between this object and a
 * rectangle structure. If there is no intercection the result will be \b nil.
 * @note This object coordinates remain unchanged.
 **/
- (SFRect*)rectByIntersectingWithRect:(CGRect)rect;
//}}}
// - (SFRect*)rectByUnionWithRect:(CGRect)rect;//{{{
/**
 * Builds an object by the union of this instance with a \c CGRect structure.
 * @param rect A \c CGRect structure to union with this object.
 * @return A new \c SFRect instance with the union of both rectangles.
 **/
- (SFRect*)rectByUnionWithRect:(CGRect)rect;
//}}}
//@}

/** \name Information */ //@{
// - (BOOL)containsPoint:(CGPoint)point;//{{{
/**
 * Checks whether this object contains the given point.
 * @param point \c CGPoint with coordinates to be checked.
 * @return \b YES if the \a point is located in this object coordinates. \b NO
 * otherwise.
 **/
- (BOOL)containsPoint:(CGPoint)point;
//}}}
// - (BOOL)containsRect:(CGRect)rect;//{{{
/**
 * Checks whether this object contains the given rectangle.
 * @param rect \c CGRect structure with coordinates to be checked.
 * @return \b YES if this object contains all the coordinates of the passed
 * rectangle. \b NO otherwise.
 **/
- (BOOL)containsRect:(CGRect)rect;
//}}}
//@}

/** \name Formating Operations */ //@{
// - (NSString*)stringWithFormat:(NSString*)spec;//{{{
/**
 * Formats the coordinates of this object into a string.
 * @param spec A \c NSString object with the formating specification. The
 * specification is a series of characters preceeded by a percent sign. The
 * following characters are accepted:
 * - `l`: Will format the left most coordinate as decimal value.
 * - `t`: Will format the top most coordinate as decimal value.
 * - `r`: Will format the right most coordinate as decimal value.
 * - `b`: Will format the bottom most coordinate as decimal value.
 * - `w`: Will format the width length as decimal value.
 * - `h`: Will format the height length as decimal value.
 * - 'C': Formats the coordinates of the object as of the specification
 *        "%lx%t : %rx%b" was passed.
 * - 'R': Formats the rectangle information of the object as of the
 *        specification "%l, %t : %w, %h" was passed.
 * .
 * @returns A \c NSString object with the coordinates formated as specified.
 * @remarks This object overrides the \c description method of \c NSObject by
 * returning a string with the following format:
 * "<SFRect [memory address]> { %lx%t : %rx%b (%w %h) }"
 **/
- (NSString*)stringWithFormat:(NSString*)spec;
//}}}
//@}

/** \name Class Methods */ //@{
// + (instancetype)rectWithCGRect:(CGRect)rect;//{{{
/**
 * Builds an object by copying the coordinates of the passed \c CGRect
 * structure.
 * @param rect A \c CGRect structure which coordinates will be used to
 * initialize this object coordinates.
 * @return The new \c SFRect object created.
 **/
+ (instancetype)rectWithCGRect:(CGRect)rect;
//}}}
// + (instancetype)rectWithOrigin:(CGPoint)origin andSize:(CGSize)size;//{{{
/**
 * Build an object with origin and size.
 * @param origin A \c CGPoint structure to initialize the origin of this
 * object.
 * @param size A \c CGSize structure to initialize the size of this object.
 * @return The new \c SFRect object created.
 **/
+ (instancetype)rectWithOrigin:(CGPoint)origin andSize:(CGSize)size;
//}}}
// + (instancetype)rectWithMinX:(CGFloat)l minY:(CGFloat)t maxX:(CGFloat)r maxY:(CGFloat)b;//{{{
/**
 * Build an object with the passed coordinates.
 * @param l The left most x coordinate to initialize the #left property of
 * the object.
 * @param t The top most y coordinate to initialize the #top property of the
 * object.
 * @param r The right most x coordinate to initialize the #right property of
 * the object.
 * @param b The bottom most y coordinate to initialize the #bottom property of
 * the object.
 * @return The new \c SFRect object created.
 **/
+ (instancetype)rectWithMinX:(CGFloat)l minY:(CGFloat)t maxX:(CGFloat)r maxY:(CGFloat)b;
//}}}
// + (instancetype)rectWithMinX:(CGFloat)l minY:(CGFloat)t width:(CGFloat)w height:(CGFloat)h;//{{{
/**
 * Build an object with the passed coordinates and sizes.
 * @param l The left most x coordinate to initialize the #left property of
 * the object.
 * @param t The top most y coordinate to initialize the #top property of the
 * object.
 * @param w The width to initialize the #width property of the object.
 * @param h The height to initialize the #height property of the object.
 * @return The new \c SFRect object created.
 **/
+ (instancetype)rectWithMinX:(CGFloat)l minY:(CGFloat)t width:(CGFloat)w height:(CGFloat)h;
//}}}
//@}
@end
// vim:ft=objc syntax=objc.doxygen
