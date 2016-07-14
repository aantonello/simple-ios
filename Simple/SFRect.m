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
#import "SFRect.h"

/* ===========================================================================
 * SF_RECT Functions
 * ======================================================================== */
// rect_t SFRectMake(CGFloat l, CGFloat t, CGFloat r, CGFloat b);//{{{
rect_t SFRectMake(CGFloat l, CGFloat t, CGFloat r, CGFloat b)
{
    rect_t rc;
    rc.left = l; rc.top = t; rc.right = r; rc.bottom = b;
    return rc;
}
//}}}
// rect_t SFRectMakeWithOriginAndSize(CGPoint origin, CGSize size);//{{{
rect_t SFRectMakeWithOriginAndSize(CGPoint origin, CGSize size)
{
    rect_t rc;
    rc.left = origin.x; rc.top = origin.y;
    rc.right = rc.left + size.width;
    rc.bottom = rc.top + size.height;

    return rc;
}
//}}}
// rect_t SFRectMakeWithPosAndLength(CGFloat x, CGFloat y, CGFloat w, CGFloat h);//{{{
rect_t SFRectMakeWithPosAndLength(CGFloat x, CGFloat y, CGFloat w, CGFloat h)
{
    rect_t rc;

    rc.left = x; rc.top = y; rc.right = x + w; rc.bottom = y + h;
    return rc;
}
//}}}

// CGFloat SFRectMinX(rect_t sfRect);//{{{
CGFloat SFRectMinX(rect_t sfRect) {
    return sfRect.left;
}
//}}}
// CGFloat SFRectMaxX(rect_t sfRect);//{{{
CGFloat SFRectMaxX(rect_t sfRect) {
    return sfRect.right;
}
//}}}
// CGFloat SFRectMinY(rect_t sfRect);//{{{
CGFloat SFRectMinY(rect_t sfRect) {
    return sfRect.top;
}
//}}}
// CGFloat SFRectMaxY(rect_t sfRect);//{{{
CGFloat SFRectMaxY(rect_t sfRect) {
    return sfRect.bottom;
}
//}}}
// CGFloat SFRectWidth(rect_t sfRect);//{{{
CGFloat SFRectWidth(rect_t sfRect) {
    return (sfRect.right - sfRect.left);
}
//}}}
// CGFloat SFRectHeight(rect_t sfRect);//{{{
CGFloat SFRectHeight(rect_t sfRect) {
    return (sfRect.bottom - sfRect.top);
}
//}}}

// CGPoint SFRectGetOrigin(rect_t sfRect);//{{{
CGPoint SFRectGetOrigin(rect_t sfRect) {
    return CGPointMake(sfRect.left, sfRect.top);
}
//}}}
// rect_t  SFRectSetOrigin(rect_t sfRect, CGPoint origin);//{{{
rect_t  SFRectSetOrigin(rect_t sfRect, CGPoint origin)
{
    CGFloat width = SFRectWidth(sfRect);
    CGFloat height = SFRectHeight(sfRect);

    return SFRectMakeWithPosAndLength(origin.x, origin.y, width, height);
}
//}}}
// CGSize  SFRectGetSize(rect_t sfRect);//{{{
CGSize  SFRectGetSize(rect_t sfRect) {
    return CGSizeMake(SFRectWidth(sfRect), SFRectHeight(sfRect));
}
//}}}
// rect_t  SFRectSetSize(rect_t sfRect, CGSize size);//{{{
rect_t  SFRectSetSize(rect_t sfRect, CGSize size)
{
    sfRect.right = sfRect.left + size.width;
    sfRect.bottom = sfRect.top + size.height;

    return sfRect;
}
//}}}
// CGPoint SFRectGetCenter(rect_t sfRect);//{{{
CGPoint SFRectGetCenter(rect_t sfRect)
{
    return CGPointMake(SFRectWidth(sfRect) / 2 + sfRect.left,
                       SFRectHeight(sfRect) / 2 + sfRect.top);
}
//}}}
// rect_t  SFRectSetCenter(rect_t sfRect, CGPoint center);//{{{
rect_t  SFRectSetCenter(rect_t sfRect, CGPoint center)
{
    CGPoint currentCenter = SFRectGetCenter(sfRect);

    currentCenter.x = (center.x - currentCenter.x);
    currentCenter.y = (center.y - currentCenter.y);

    return SFRectMove(sfRect, currentCenter.x, currentCenter.y);
}
//}}}

// rect_t SFRectOffset(rect_t sfRect, CGFloat dx, CGFloat dy);//{{{
rect_t SFRectOffset(rect_t sfRect, CGFloat dx, CGFloat dy)
{
    sfRect.left += dx; sfRect.right += dx;
    sfRect.top += dy; sfRect.bottom += dy;

    return sfRect;
}
//}}}
// rect_t SFRectMove(rect_t sfRect, CGFloat x, CGFloat y);//{{{
rect_t SFRectMove(rect_t sfRect, CGFloat x, CGFloat y)
{
    CGSize size = SFRectGetSize(sfRect);
    return SFRectMakeWithPosAndLength(x, y, size.width, size.height);
}
//}}}
// rect_t SFRectDeflate(rect_t sfRect, CGFloat l, CGFloat t, CGFloat r, CGFloat b);//{{{
rect_t SFRectDeflate(rect_t sfRect, CGFloat l, CGFloat t, CGFloat r, CGFloat b)
{
    sfRect.left += l;
    sfRect.top  += t;
    sfRect.right -= r;
    sfRect.bottom -= b;

    return sfRect;
}
//}}}
// rect_t SFRectAlignAt(rect_t sfRect, SFRectAlign flags, rect_t reference);//{{{
rect_t SFRectAlignAt(rect_t sfRect, SFRectAlign flags, rect_t reference)
{
    if ((flags & SFRectAlignLeft) == SFRectAlignLeft)
        sfRect = SFRectMove(sfRect, reference.left, sfRect.top);

    if ((flags & SFRectAlignTop) == SFRectAlignTop)
        sfRect = SFRectMove(sfRect, sfRect.left, reference.top);

    if ((flags & SFRectAlignRight) == SFRectAlignRight)
        sfRect = SFRectMove(sfRect, (reference.right - SFRectWidth(sfRect)), sfRect.top);

    if ((flags & SFRectAlignBottom) == SFRectAlignBottom)
        sfRect = SFRectMove(sfRect, sfRect.left, (reference.bottom - SFRectHeight(sfRect)));

    if ((flags & SFRectAlignCenterHorizontal) == SFRectAlignCenterHorizontal)
        sfRect = SFRectMove(sfRect, ((SFRectWidth(sfRect) / 2) - (SFRectWidth(reference) / 2)),
                            sfRect.top);

    if ((flags & SFRectAlignCenterVertical) == SFRectAlignCenterVertical)
        sfRect = SFRectMove(sfRect, sfRect.left,
                            ((SFRectHeight(sfRect) / 2) - (SFRectHeight(reference) / 2)));

    return sfRect;
}
//}}}
// rect_t SFRectFit(rect_t sfRect, SFRectStretch flags, rect_t ref);//{{{
rect_t SFRectFit(rect_t sfRect, SFRectStretch flags, rect_t ref)
{
    CGSize rcSize = SFRectGetSize(sfRect);
    CGSize rfSize = SFRectGetSize(ref);

    if ((flags & SFRectStretchWidth) == SFRectStretchWidth)
        sfRect = SFRectSetSize(sfRect, CGSizeMake(rfSize.width, rcSize.height));

    if ((flags & SFRectStretchHeight) == SFRectStretchHeight)
        sfRect = SFRectSetSize(sfRect, CGSizeMake(rcSize.width, rfSize.height));

    if ((flags & SFRectStretchFit) == SFRectStretchFit)
    {
        if ((rfSize.width != rcSize.width) || (rfSize.height != rcSize.height))
        {
            if (rcSize.width > rcSize.height)
            {
                rcSize.height = ((rcSize.height * rfSize.width) / rcSize.width);
                rcSize.width  = rfSize.width;
            }
            else
            {
                rcSize.width  = ((rcSize.width * rfSize.height) / rcSize.height);
                rcSize.height = rfSize.height;
            }
            sfRect = SFRectSetSize(sfRect, rcSize);
        }
    }
    return sfRect;
}
//}}}
// rect_t SFRectIntersect(rect_t rc1, rect_t rc2);//{{{
rect_t SFRectIntersect(rect_t rc1, rect_t rc2)
{
    CGRect temp = CGRectIntersection(SFRectToCGRect(rc1), SFRectToCGRect(rc2));
    return (CGRectIsNull(temp) ? SFRectMake(0, 0, 0, 0) : CGRectToSFRect(temp));
}
//}}}
// rect_t SFRectUnion(rect_t rc1, rect_t rc2);//{{{
rect_t SFRectUnion(rect_t rc1, rect_t rc2)
{
    CGRect temp = CGRectUnion(SFRectToCGRect(rc1), SFRectToCGRect(rc2));
    return CGRectToSFRect(temp);
}
//}}}

// CGRect SFRectToCGRect(rect_t sfRect);//{{{
CGRect SFRectToCGRect(rect_t sfRect)
{
    return CGRectMake(sfRect.left, sfRect.top, SFRectWidth(sfRect), SFRectHeight(sfRect));
}
//}}}
// rect_t CGRectToSFRect(CGRect rect);//{{{
rect_t CGRectToSFRect(CGRect rect)
{
    return SFRectMakeWithOriginAndSize(rect.origin, rect.size);
}
//}}}

// BOOL SFRectIsEmpty(rect_t sfRect);//{{{
BOOL SFRectIsEmpty(rect_t sfRect)
{
    return ((SFRectWidth(sfRect) < 0) || (SFRectHeight(sfRect) < 0));
}
//}}}
// BOOL SFRectHasPoint(rect_t sfRect, CGPoint point);//{{{
BOOL SFRectHasPoint(rect_t sfRect, CGPoint point)
{
    return (((point.x >= sfRect.left) && (point.x <= sfRect.right)) &&
            ((point.y >= sfRect.top) && (point.y <= sfRect.bottom)));
}
//}}}
// BOOL SFRectContainsRect(rect_t sfRect, rect_t rect);//{{{
BOOL SFRectContainsRect(rect_t sfRect, rect_t rect)
{
    CGPoint start = CGPointMake(rect.left, rect.top);
    CGPoint end   = CGPointMake(rect.right, rect.bottom);

    return (SFRectHasPoint(sfRect, start) && SFRectHasPoint(sfRect, end));
}
//}}}

// NSString *SFRectFormat(rect_t sfRect, NSString *format);//{{{
NSString *SFRectFormat(rect_t sfRect, NSString *format)
{
    char buffer[512];
    char *ptr, *end;
    const char *data = [format cStringUsingEncoding:NSUTF8StringEncoding];
    char c;

    ptr = buffer;
    end = (ptr + 511);

    while (((c = *data++) != '\0') && (ptr < end))
    {
        if (c != '%')
            *ptr++ = c;
        else
        {
            switch (c)
            {
            case 'l':
                ptr += sprintf(ptr, "%d", ((int)sfRect.left));
                break;
            case 't':
                ptr += sprintf(ptr, "%d", ((int)sfRect.top));
                break;
            case 'r':
                ptr += sprintf(ptr, "%d", ((int)sfRect.right));
                break;
            case 'b':
                ptr += sprintf(ptr, "%d", ((int)sfRect.bottom));
                break;
            case 'w':
                ptr += sprintf(ptr, "%d", ((int)SFRectWidth(sfRect)));
                break;
            case 'h':
                ptr += sprintf(ptr, "%d", ((int)SFRectHeight(sfRect)));
                break;
            case 'C':
                ptr += sprintf(ptr, "%dx%d : %dx%d", ((int)sfRect.left),
                               ((int)sfRect.top), ((int)sfRect.right),
                               ((int)sfRect.bottom));
                break;
            case 'R':
                ptr += sprintf(ptr, "%d, %d : %d, %d", ((int)sfRect.left),
                               ((int)sfRect.top), ((int)SFRectWidth(sfRect)),
                               ((int)SFRectHeight(sfRect)));
                break;
            default:
                *ptr++ = c;
            }
        }
    }
    *end = '\0';

    return [NSString stringWithCString:buffer encoding:NSUTF8StringEncoding];
}
//}}}

/* ===========================================================================
 * SFRect Extension
 * ======================================================================== */
@interface SFRect () {
    CGRect m_rect;
}
@end

/* ===========================================================================
 * SFRect Implementation
 * ======================================================================== */
@implementation SFRect
// Properties
/* property: left {{{ */
- (CGFloat)left { return m_rect.origin.x; }
- (void)setLeft:(CGFloat)left {
    m_rect.origin.x = left;
}
/* }}} left property */
/* property: top {{{ */
- (CGFloat)top { return m_rect.origin.y; }
- (void)setTop:(CGFloat)top {
    m_rect.origin.y = top;
}
/* }}} top property */
/* property: width {{{ */
- (CGFloat)width { return m_rect.size.width; }
- (void)setWidth:(CGFloat)width {
    m_rect.size.width = width;
}
/* }}} width property */
/* property: height {{{ */
- (CGFloat)height { return m_rect.size.height; }
- (void)setHeight:(CGFloat)height {
    m_rect.size.height = height;
}
/* }}} height property */
/* property: right {{{ */
- (CGFloat)right { return (m_rect.size.width + m_rect.origin.x); }
- (void)setRight:(CGFloat)right {
    m_rect.size.width = (right - m_rect.origin.x);
}
/* }}} right property */
/* property: bottom {{{ */
- (CGFloat)bottom { return (m_rect.origin.y + m_rect.size.height); }
- (void)setBottom:(CGFloat)bottom {
    m_rect.size.height = (bottom - m_rect.origin.y);
}
/* }}} bottom */
/* property: origin {{{ */
- (CGPoint)origin { return m_rect.origin; }
- (void)setOrigin:(CGPoint)origin {
    m_rect.origin = origin;
}
/* }}} origin */
/* property: size {{{ */
- (CGSize)size { return m_rect.size; }
- (void)setSize:(CGSize)size {
    m_rect.size = size;
}
/* }}} size */
/* property: center {{{ */
- (CGPoint)center {
    return CGPointMake((self.width / 2 + self.left), (self.height / 2 + self.top));
}
- (void)setCenter:(CGPoint)center {
    m_rect.origin.x = (center.x - (self.width / 2));
    m_rect.origin.y = (center.y - (self.height / 2));
}
/* }}} center */
/* property: rect {{{ */
- (CGRect)rect { return m_rect; }
- (void)setRect:(CGRect)rect {
    m_rect = rect;
}
/* }}} rect */

// Designated Initializations
/* - initWithCGRect:(CGRect)rect {{{ */
- (instancetype)initWithCGRect:(CGRect)rect
{
    self = [self init];
    if (self) {
        m_rect = rect;
    }
    return self;
}
/* }}} initWithCGRect:(CGRect)rect */
/* - initWithOrigin:(CGPoint)origin andSize:(CGSize)size; {{{ */
- (instancetype)initWithOrigin:(CGPoint)origin andSize:(CGSize)size
{
    self = [self init];
    if (self)
    {
        m_rect.origin = origin;
        m_rect.size   = size;
    }
    return self;
}
/* }}} initWithOrigin:(CGPoint)origin andSize:(CGSize)size; */
/* - initWithMinX:(CGFloat)l minY:(CGFloat)t maxX:(CGFloat)r maxY:(CGFloat)b; {{{ */
- (instancetype)initWithMinX:(CGFloat)l minY:(CGFloat)t maxX:(CGFloat)r maxY:(CGFloat)b
{
    self = [self init];
    if (self)
    {
        m_rect.origin.x = l;
        m_rect.origin.y = t;
        m_rect.size.width = (r - l);
        m_rect.size.height = (b - t);
    }
    return self;
}
/*}}}*/
// - initWithMinX:(CGFloat)l minY:(CGFloat)t width:(CGFloat)w height:(CGFloat)h;//{{{
- (instancetype)initWithMinX:(CGFloat)l minY:(CGFloat)t width:(CGFloat)w height:(CGFloat)h
{
    self = [self init];
    if (self)
    {
        m_rect.origin.x = l;
        m_rect.origin.y = t;
        m_rect.size.width  = w;
        m_rect.size.height = h;
    }
    return self;
}
//}}}

// Helper Operations
// - (SFRect*)deflateLeft:(CGFloat)l top:(CGFloat)t right:(CGFloat)r bottom:(CGFloat)b;//{{{
- (SFRect*)deflateLeft:(CGFloat)l top:(CGFloat)t right:(CGFloat)r bottom:(CGFloat)b
{
    m_rect.origin.x += l;
    m_rect.origin.y += t;
    m_rect.size.width -= (l + r);
    m_rect.size.height -= (t + b);

    return self;
}
//}}}
// - (SFRect*)align:(SFRectAlign)flags atRect:(SFRect*)rect;//{{{
- (SFRect*)align:(SFRectAlign)flags atRect:(SFRect*)rect
{
    return [self align:flags atCGRect:rect.rect];
}
//}}}
// - (SFRect*)align:(SFRectAlign)flags atCGRect:(CGRect)rect;//{{{
- (SFRect*)align:(SFRectAlign)flags atCGRect:(CGRect)rect
{
    if ((flags & SFRectAlignLeft) == SFRectAlignLeft)
        self.left = rect.origin.x;

    if ((flags & SFRectAlignTop) == SFRectAlignTop)
        self.top = rect.origin.y;

    if ((flags & SFRectAlignRight) == SFRectAlignRight)
        self.right = (rect.origin.x + rect.size.width);

    if ((flags & SFRectAlignBottom) == SFRectAlignBottom)
        self.bottom = (rect.origin.y + rect.size.height);

    if ((flags & SFRectAlignAtLeft) == SFRectAlignAtLeft)
        self.right = rect.origin.x;

    if ((flags & SFRectAlignAtTop) == SFRectAlignAtTop)
        self.bottom = rect.origin.y;

    if ((flags & SFRectAlignAtRight) == SFRectAlignAtRight)
        self.left = (rect.origin.x + rect.size.width);

    if ((flags & SFRectAlignAtBottom) == SFRectAlignAtBottom)
        self.top = (rect.origin.y + rect.size.height);

    if ((flags & SFRectAlignCenterHorizontal) == SFRectAlignCenterHorizontal)
        self.left = ((self.width / 2) - (rect.size.width / 2)) + rect.origin.x;

    if ((flags & SFRectAlignCenterVertical) == SFRectAlignCenterVertical)
        self.top = ((self.height / 2) - (rect.size.height / 2)) + rect.origin.y;

    return self;
}
//}}}
// - (SFRect*)stretch:(SFRectStretch)flags atRect:(SFRect*)rect;//{{{
- (SFRect*)stretch:(SFRectStretch)flags atRect:(SFRect*)rect
{
    return [self stretch:flags atCGRect:rect.rect];
}
//}}}
// - (SFRect*)stretch:(SFRectStretch)flags atCGRect:(CGRect)rect;//{{{
- (SFRect*)stretch:(SFRectStretch)flags atCGRect:(CGRect)rect
{
    if ((flags & SFRectStretchWidth) == SFRectStretchWidth)
        self.width = rect.size.width;

    if ((flags & SFRectStretchHeight) == SFRectStretchHeight)
        self.height = rect.size.height;

    if ((flags & SFRectStretchFit) == SFRectStretchFit)
    {
        if ((rect.size.width != self.width) || (rect.size.height != self.height))
        {
            if (self.width > self.height)
            {
                self.height = ((self.height * rect.size.width) / self.width);
                self.width  = rect.size.width;
            }
            else
            {
                self.width  = ((self.width * rect.size.height) / self.height);
                self.height = rect.size.height;
            }
        }
    }
    return self;
}
//}}}

// Builds a new SFRect instance
// - (SFRect*)rectByDeflatingLeft:(CGFloat)l top:(CGFloat)t right:(CGFloat)r bottom:(CGFloat)b;//{{{
- (SFRect*)rectByDeflatingLeft:(CGFloat)l top:(CGFloat)t right:(CGFloat)r bottom:(CGFloat)b
{
    SFRect *sfRect = [SFRect rectWithCGRect:self.rect];
    return [sfRect deflateLeft:l top:t right:r bottom:b];
}
//}}}
// - (SFRect*)rectByAlign:(SFRectAlign)flags atRect:(SFRect*)rect;//{{{
- (SFRect*)rectByAlign:(SFRectAlign)flags atRect:(SFRect*)rect
{
    return [self rectByAlign:flags atCGRect:rect.rect];
}
//}}}
// - (SFRect*)rectByAlign:(SFRectAlign)flags atCGRect:(CGRect)rect;//{{{
- (SFRect*)rectByAlign:(SFRectAlign)flags atCGRect:(CGRect)rect
{
    SFRect *sfRect = [SFRect rectWithCGRect:rect];
    return [sfRect align:flags atCGRect:rect];
}
//}}}
// - (SFRect*)rectByStretch:(SFRectStretch)flags atRect:(SFRect*)rect;//{{{
- (SFRect*)rectByStretch:(SFRectStretch)flags atRect:(SFRect*)rect
{
    return [self rectByStretch:flags atCGRect:rect.rect];
}
//}}}
// - (SFRect*)rectByStretch:(SFRectStretch)flags atCGRect:(CGRect)rect;//{{{
- (SFRect*)rectByStretch:(SFRectStretch)flags atCGRect:(CGRect)rect
{
    SFRect *sfRect = [SFRect rectWithCGRect:rect];
    return [sfRect stretch:flags atCGRect:rect];
}
//}}}
// - (SFRect*)rectByIntersectingWithRect:(CGRect)rect;//{{{
- (SFRect*)rectByIntersectingWithRect:(CGRect)rect
{
    CGRect intersectRect = CGRectIntersection(self.rect, rect);
    return (CGRectIsNull(intersectRect) ? nil : [SFRect rectWithCGRect:intersectRect]);
}
//}}}
// - (SFRect*)rectByUnionWithRect:(CGRect)rect;//{{{
- (SFRect*)rectByUnionWithRect:(CGRect)rect
{
    CGRect unionRect = CGRectUnion(self.rect, rect);
    return [SFRect rectWithCGRect:unionRect];
}
//}}}

// Information
// - (BOOL)containsPoint:(CGPoint)point;//{{{
- (BOOL)containsPoint:(CGPoint)point
{
    return CGRectContainsPoint(self.rect, point);
}
//}}}
// - (BOOL)containsRect:(CGRect)rect;//{{{
- (BOOL)containsRect:(CGRect)rect
{
    return CGRectContainsRect(self.rect, rect);
}
//}}}

// Formating Operations
// - (NSString*)stringWithFormat:(NSString*)spec;//{{{
- (NSString*)stringWithFormat:(NSString*)spec
{
    char buffer[512];
    char *ptr, *end;
    const char *data = [spec cStringUsingEncoding:NSUTF8StringEncoding];
    char c;

    ptr = buffer;
    end = (ptr + 511);

    while (((c = *data++) != '\0') && (ptr < end))
    {
        if (c != '%')
            *ptr++ = c;
        else
        {
            switch (c)
            {
            case 'l':
                ptr += sprintf(ptr, "%d", ((int)self.left));
                break;
            case 't':
                ptr += sprintf(ptr, "%d", ((int)self.top));
                break;
            case 'r':
                ptr += sprintf(ptr, "%d", ((int)self.right));
                break;
            case 'b':
                ptr += sprintf(ptr, "%d", ((int)self.bottom));
                break;
            case 'w':
                ptr += sprintf(ptr, "%d", ((int)self.width));
                break;
            case 'h':
                ptr += sprintf(ptr, "%d", ((int)self.height));
                break;
            case 'C':
                ptr += sprintf(ptr, "%dx%d : %dx%d", ((int)self.left), ((int)self.top), ((int)self.right), ((int)self.bottom));
                break;
            case 'R':
                ptr += sprintf(ptr, "%d, %d : %d, %d", ((int)self.left), ((int)self.top), ((int)self.width), ((int)self.height));
                break;
            default:
                *ptr++ = c;
            }
        }
    }
    *end = '\0';

    return [NSString stringWithCString:buffer encoding:NSUTF8StringEncoding];
}
//}}}

// Class Methods
// + (instancetype)rectWithCGRect:(CGRect)rect;//{{{
+ (instancetype)rectWithCGRect:(CGRect)rect
{
    SFRect *sfRect = [[SFRect alloc] initWithCGRect:rect];
    return [sfRect autorelease];
}
//}}}
// + (instancetype)rectWithOrigin:(CGPoint)origin andSize:(CGSize)size;//{{{
+ (instancetype)rectWithOrigin:(CGPoint)origin andSize:(CGSize)size
{
    SFRect *sfRect = [[SFRect alloc] initWithOrigin:origin andSize:size];
    return [sfRect autorelease];
}
//}}}
// + (instancetype)rectWithMinX:(CGFloat)l minY:(CGFloat)t maxX:(CGFloat)r maxY:(CGFloat)b;//{{{
+ (instancetype)rectWithMinX:(CGFloat)l minY:(CGFloat)t maxX:(CGFloat)r maxY:(CGFloat)b
{
    SFRect *sfRect = [[SFRect alloc] initWithMinX:l minY:t maxX:r maxY:b];
    return [sfRect autorelease];
}
//}}}
// + (instancetype)rectWithMinX:(CGFloat)l minY:(CGFloat)t width:(CGFloat)w height:(CGFloat)h;//{{{
+ (instancetype)rectWithMinX:(CGFloat)l minY:(CGFloat)t width:(CGFloat)w height:(CGFloat)h
{
    SFRect *sfRect = [[SFRect alloc] initWithMinX:l minY:t width:w height:h];
    return [sfRect autorelease];
}
//}}}
@end
