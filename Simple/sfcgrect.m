/**
 * @file
 * Functions and macros to work with CGRect structure.
 *
 * @author Alessandro Antonello aantonello@paralaxe.com.br
 * @date   Fevereiro 04, 2015
 * @since  Simple Framework 1.3
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#include "sfcgrect.h"
#include "SFRect.h"

// CGRect cgrect_inflate(CGRect source, CGFloat dx, CGFloat dy, CGFloat rx, CGFloat ry);//{{{
CGRect cgrect_inflate(CGRect source, CGFloat dx, CGFloat dy, CGFloat rx, CGFloat ry)
{
    return CGRectMake(source.origin.x - dx, source.origin.y - dy,
                      source.size.width + dx + rx, source.size.height + dy + ry);
}
//}}}
// CGRect cgrect_align(CGRect source, int align, CGRect reference);//{{{
CGRect cgrect_align(CGRect source, int align, CGRect reference)
{
    if ((align & SFRectAlignLeft) == SFRectAlignLeft) {
        source.origin.x = reference.origin.x;
    }

    if ((align & SFRectAlignAtLeft) == SFRectAlignAtLeft) {
        cgrect_right_at(source, reference.origin.x);
    }

    if ((align & SFRectAlignTop) == SFRectAlignTop) {
        source.origin.y = reference.origin.y;
    }

    if ((align & SFRectAlignAtTop) == SFRectAlignAtTop) {
        cgrect_bottom_at(source, reference.origin.y);
    }

    if ((align & SFRectAlignRight) == SFRectAlignRight) {
        cgrect_right_at(source, cgrect_right(reference));
    }

    if ((align & SFRectAlignAtRight) == SFRectAlignAtRight) {
        source.origin.x = cgrect_right(reference);
    }

    if ((align & SFRectAlignBottom) == SFRectAlignBottom) {
        cgrect_bottom_at(source, cgrect_bottom(reference));
    }

    if ((align & SFRectAlignAtBottom) == SFRectAlignAtBottom) {
        source.origin.y = cgrect_bottom(reference);
    }

    if ((align & SFRectAlignCenterHorizontal) == SFRectAlignCenterHorizontal) {
        source.origin.x = ((reference.size.width / 2) - (source.size.width / 2)) + reference.origin.x;
    }

    if ((align & SFRectAlignCenterVertical) == SFRectAlignCenterVertical) {
        source.origin.y = ((reference.size.height / 2) - (source.size.height / 2)) + reference.origin.y;
    }
    return source;
}
//}}}
// CGRect cgrect_fit(CGRect source, int flags, CGRect reference);//{{{
CGRect cgrect_fit(CGRect source, int flags, CGRect reference)
{
    if (flags & SFRectStretchWidth) {
        source.size.width = reference.size.width;
    }

    if (flags & SFRectStretchHeight) {
        source.size.height = reference.size.height;
    }

    if (flags & SFRectStretchFit)
    {
        /* First we must match one of its size. Then check again to keep the
         * aspect ratio.
         */
        if (source.size.width > source.size.height) /* source is larger than tall. */
        {
            source.size.height = ((source.size.height * reference.size.width) / source.size.width);
            source.size.width  = reference.size.width;
        }
        else
        {
            source.size.width  = ((source.size.width * reference.size.height) / source.size.height);
            source.size.height = reference.size.height;
        }

        /* Some times we need more than one step. */
        while ((source.size.width > reference.size.width) ||
               (source.size.height > reference.size.height))
        {
            if (source.size.width > reference.size.width)
            {
                source.size.height = ((source.size.height * reference.size.width) / source.size.width);
                source.size.width  = reference.size.width;
            }
            else if (source.size.height > reference.size.height)
            {
                source.size.width  = ((source.size.width * reference.size.height) / source.size.height);
                source.size.height = reference.size.height;
            }
        }
    }
    return source;
}
//}}}
// CGRect cgrect_centralize(CGRect source, CGPoint center);//{{{
CGRect cgrect_centralize(CGRect source, CGPoint center)
{
    source.origin.x = center.x - (source.size.width / 2);
    source.origin.y = center.y - (source.size.height / 2);
    return source;
}
//}}}

