/**
 * @file
 * Defines the SFStream Objective-C interface class.
 *
 * @author  Alessandro Antonello aantonello@paralaxe.com.br
 * @date    May 06, 2014
 * @since   Simple Framework 1.2
 *
 * \copyright
 * 2014, Paralaxe Tecnologia. All rights reserved.
 */
#import "SFStream.h"
#import "sfdebug.h"

#include <stdlib.h>

/* ===========================================================================
 * SFStream EXTENSION
 * ======================================================================== */
@interface SFStream () {
    uint8_t *m_buffer;
    size_t   m_length;
    size_t   m_capacity;
    size_t   m_nextRead;
    size_t   m_nextWrite;
}
// Memory Management
// - (BOOL)increaseCapacityBy:(size_t)amount;//{{{
/**
 * Increases the size of the internal buffer when needed.
 * @param amount Amount of bytes to increase the current buffer capacity.
 * @return \b true if the operation succeed. \b false otherwise.
 **/
- (BOOL)increaseCapacityBy:(size_t)amount;
//}}}
@end
/* ---------------------------------------------------------------------------
 * SFStream Implementation 
 * ------------------------------------------------------------------------ */
@implementation SFStream
// Designated Initializers
// - (instancetype)initWithBytes:(const void*)data length:(size_t)size;//{{{
- (instancetype)initWithBytes:(const void*)data length:(size_t)size
{
    self = [self initWithCapacity:size];
    if (self)
    {
        [self write:data length:size];
    }
    return self;
}
//}}}
// - (instancetype)initWithData:(NSData *)data;//{{{
- (instancetype)initWithData:(NSData *)data
{
    return [self initWithBytes:[data bytes] length:[data length]];
}
//}}}
// - (instancetype)initWithStream:(SFStream *)stream;//{{{
- (instancetype)initWithStream:(SFStream *)stream
{
    size_t amount = [stream numberOfBytesAvailable];
    
    self = [self initWithCapacity:amount];
    if (self) {
        [self writeStream:stream length:amount];
    }
    return self;
}
//}}}
// - (instancetype)initWithCapacity:(size_t)capacity;//{{{
- (instancetype)initWithCapacity:(size_t)capacity
{
    self = [super init];
    if (self)
    {
        [self increaseCapacityBy:capacity];
    }
    return self;
}
//}}}

// NSObject: Overrides
// - (void)dealloc;//{{{
- (void)dealloc
{
    if (m_buffer != NULL)
        free(m_buffer);

    [super dealloc];
}
//}}}

// Memory Management
// - (BOOL)increaseCapacityBy:(size_t)amount;//{{{
- (BOOL)increaseCapacityBy:(size_t)amount
{
    size_t total = m_capacity + amount;
    uint8_t *ptr = NULL;

    ptr = (uint8_t *)realloc(m_buffer, total);
    if (ptr == NULL)
        return FALSE;

    m_buffer = ptr;
    m_capacity = total;
    return TRUE;
}
//}}}

// SFStreamProtocol: Properties Implementation
// - (size_t)capacity;//{{{
- (size_t)capacity {
    return m_capacity;
}
//}}}
// - (size_t)length;//{{{
- (size_t)length {
    return m_length;
}
//}}}

// SFStreamReaderProtocol Reading Information
// - (size_t)readPosition;//{{{
- (size_t)readPosition {
    return m_nextRead;
}
//}}}
// - (size_t)numberOfBytesAvailable;//{{{
- (size_t)numberOfBytesAvailable {
    return (m_length - m_nextRead);
}
//}}}
// - (BOOL)setReadPosition:(size_t)offset;//{{{
- (BOOL)setReadPosition:(size_t)offset
{
    if (offset > m_length) return NO;
    m_nextRead = offset;
    return YES;
}
//}}}

// SFStreamReaderProtocol Direct Access
// - (const uint8_t *)bytes;//{{{
- (const uint8_t *)bytes
{
    return (m_buffer + m_nextRead);
}
//}}}
// - (const uint8_t *)bytesAtIndex:(size_t)offset;//{{{
- (const uint8_t *)bytesAtIndex:(size_t)offset
{
    sfassert(offset < m_length, "SFStream::bytesAtIndex[] offset greater than length\n");
    if (offset >= m_length) return NULL;

    return (m_buffer + offset);
}
//}}}

// SFStreamReaderProtocol Basic Reading Operations
// - (size_t)read:(void *)buffer length:(size_t)length;//{{{
- (size_t)read:(void *)buffer length:(size_t)length
{
    if ((buffer == NULL) || (length == 0) || (m_buffer == NULL))
        return 0;

    if (length > [self numberOfBytesAvailable])
        length = [self numberOfBytesAvailable];

    memcpy(buffer, (m_buffer + m_nextRead), length);
    m_nextRead += length;

    return length;
}
//}}}
// - (uint8_t)readByte;//{{{
- (uint8_t)readByte
{
    uint8_t buffer = (uint8_t)0;

    [self read:&buffer length:sizeof(uint8_t)];
    return buffer;
}
//}}}
// - (uint16_t)readShort;//{{{
- (uint16_t)readShort
{
    uint16_t buffer;

    if ([self read:&buffer length:sizeof(uint16_t)] == sizeof(uint16_t))
        return buffer;

    return (uint16_t)0;
}
//}}}
// - (uint32_t)readInt;//{{{
- (uint32_t)readInt
{
    uint32_t buffer;

    if ([self read:&buffer length:sizeof(uint32_t)] == sizeof(uint32_t))
        return buffer;

    return (uint32_t)0;
}
//}}}
// - (uint64_t)readLong;//{{{
- (uint64_t)readLong
{
    uint64_t buffer;

    if ([self read:&buffer length:sizeof(uint64_t)] == sizeof(uint64_t))
        return buffer;

    return (uint64_t)0;
}
//}}}
// - (float)readFloat;//{{{
- (float)readFloat
{
    float buffer;

    if ([self read:&buffer length:sizeof(float)] == sizeof(float))
        return buffer;

    return (float)0.0;
}
//}}}
// - (double)readDouble;//{{{
- (double)readDouble
{
    double buffer;

    if ([self read:&buffer length:sizeof(double)] == sizeof(double))
        return buffer;

    return 0.0;
}
//}}}
// - (void)purgeReadBytes;//{{{
- (void)purgeReadBytes
{
    size_t bytesToMove = [self numberOfBytesAvailable];

    if ((m_buffer == NULL) || (m_nextRead == 0))
        return;

    memmove(m_buffer, (m_buffer + m_nextRead), bytesToMove);
    if (m_nextWrite <= m_nextRead)
        m_nextWrite = 0;
    else
        m_nextWrite -= m_nextRead;

    m_length -= m_nextRead;
    m_nextRead = 0;
}
//}}}

// SFStreamReaderProtocol Big-Endian to Host Conversions
// - (uint16_t)readBigEndianShort;//{{{
- (uint16_t)readBigEndianShort
{
    return NSSwapBigShortToHost([self readShort]);
}
//}}}
// - (uint32_t)readBigEndianInt;//{{{
- (uint32_t)readBigEndianInt
{
    return NSSwapBigIntToHost([self readInt]);
}
//}}}
// - (uint64_t)readBigEndignLong;//{{{
- (uint64_t)readBigEndignLong
{
    return NSSwapBigLongLongToHost([self readLong]);
}
//}}}
// - (float)readBigEndianFloat;//{{{
- (float)readBigEndianFloat
{
    NSSwappedFloat swappedFloat = { 0 };

    [self read:&swappedFloat length:sizeof(NSSwappedFloat)];
    return NSSwapBigFloatToHost(swappedFloat);
}
//}}}
// - (double)readBigEndianDouble;//{{{
- (double)readBigEndianDouble
{
    NSSwappedDouble swappedDouble = { 0 };

    [self read:&swappedDouble length:sizeof(NSSwappedDouble)];
    return NSSwapBigDoubleToHost(swappedDouble);
}
//}}}

// SFStreamReaderProtocol Little-Endian to Host Conversions
// - (uint16_t)readLittleEndianShort;//{{{
- (uint16_t)readLittleEndianShort
{
    return NSSwapLittleShortToHost([self readShort]);
}
//}}}
// - (uint32_t)readLittleEndianInt;//{{{
- (uint32_t)readLittleEndianInt
{
    return NSSwapLittleIntToHost([self readInt]);
}
//}}}
// - (uint64_t)readLittleEndianLong;//{{{
- (uint64_t)readLittleEndianLong
{
    return NSSwapLittleLongLongToHost([self readLong]);
}
//}}}
// - (float)readLittleEndianFloat;//{{{
- (float)readLittleEndianFloat
{
    NSSwappedFloat swappedFloat = { 0 };

    [self read:&swappedFloat length:sizeof(NSSwappedFloat)];
    return NSSwapLittleFloatToHost(swappedFloat);
}
//}}}
// - (double)readLittleEndianDouble;//{{{
- (double)readLittleEndianDouble
{
    NSSwappedDouble swappedDouble = { 0 };

    [self read:&swappedDouble length:sizeof(NSSwappedDouble)];
    return NSSwapLittleDoubleToHost(swappedDouble);
}
//}}}

// SFStreamWriterProtocol Writting Information
// - (size_t)writePosition;//{{{
- (size_t)writePosition {
    return m_nextWrite;
}
//}}}
// - (BOOL)setWritePosition:(size_t)offset;//{{{
- (BOOL)setWritePosition:(size_t)offset
{
    if (offset > m_capacity) return NO;
    m_nextWrite = offset;
    return YES;
}
//}}}

// SFStreamWriterProtocol Direct Access
// - (void *)bufferWithLength:(size_t)length;//{{{
- (void *)bufferWithLength:(size_t)length
{
    if (length == 0)
        return NULL;
    else if (length > (m_capacity - m_nextWrite)) {
        if (![self increaseCapacityBy:(length - (m_capacity - m_nextWrite))])
            return NULL;
    }
    return (void *)(m_buffer + m_nextWrite);
}
//}}}

// SFStreamWriterProtocol Basic Writting Operations
// - (size_t)write:(const void*)data length:(size_t)size;//{{{
- (size_t)write:(const void*)data length:(size_t)size
{
    if ((data == NULL) || (size == 0))
        return 0;

    size_t available = (m_capacity - m_nextWrite);

    if (size > available)
    {
        if (![self increaseCapacityBy:(size - available)])
            return (size_t)0;
    }

    memcpy((m_buffer + m_nextWrite), data, size);
    m_nextWrite += size;
    if (m_nextWrite > m_length)
        m_length = m_nextWrite;
    return size;
}
//}}}
// - (void)writeByte:(uint8_t)data;//{{{
- (void)writeByte:(uint8_t)data
{
    [self write:&data length:sizeof(uint8_t)];
}
//}}}
// - (void)writeShort:(uint16_t)data;//{{{
- (void)writeShort:(uint16_t)data
{
    [self write:&data length:sizeof(uint16_t)];
}
//}}}
// - (void)writeInt:(uint32_t)data;//{{{
- (void)writeInt:(uint32_t)data
{
    [self write:&data length:sizeof(uint32_t)];
}
//}}}
// - (void)writeLong:(uint64_t)data;//{{{
- (void)writeLong:(uint64_t)data
{
    [self write:&data length:sizeof(uint64_t)];
}
//}}}
// - (void)writeFloat:(float)data;//{{{
- (void)writeFloat:(float)data
{
    [self write:&data length:sizeof(float)];
}
//}}}
// - (void)writeDouble:(double)data;//{{{
- (void)writeDouble:(double)data
{
    [self write:&data length:sizeof(double)];
}
//}}}

// SFStreamWriterProtocol Host to Big-Endian Conversions
// - (void)writeBigEndianShort:(uint16_t)data;//{{{
- (void)writeBigEndianShort:(uint16_t)data
{
    [self writeShort:NSSwapHostShortToBig(data)];
}
//}}}
// - (void)writeBigEndianInt:(uint32_t)data;//{{{
- (void)writeBigEndianInt:(uint32_t)data
{
    [self writeInt:NSSwapHostIntToBig(data)];
}
//}}}
// - (void)writeBigEndianLong:(uint64_t)data;//{{{
- (void)writeBigEndianLong:(uint64_t)data
{
    [self writeLong:NSSwapHostLongLongToBig(data)];
}
//}}}
// - (void)writeBigEndianFloat:(float)data;//{{{
- (void)writeBigEndianFloat:(float)data
{
    NSSwappedFloat swappedFloat = NSSwapHostFloatToBig(data);
    [self write:&swappedFloat length:sizeof(NSSwappedFloat)];
}
//}}}
// - (void)writeBigEndianDouble:(double)data;//{{{
- (void)writeBigEndianDouble:(double)data
{
    NSSwappedDouble swappedDouble = NSSwapHostDoubleToBig(data);
    [self write:&swappedDouble length:sizeof(NSSwappedDouble)];
}
//}}}

// SFStreamWriterProtocol Host to Little-Endian Conversions
// - (void)writeLittleEndianShort:(uint16_t)data;//{{{
- (void)writeLittleEndianShort:(uint16_t)data
{
    [self writeShort:NSSwapHostShortToLittle(data)];
}
//}}}
// - (void)writeLittleEndianInt:(uint32_t)data;//{{{
- (void)writeLittleEndianInt:(uint32_t)data
{
    [self writeInt:NSSwapHostIntToLittle(data)];
}
//}}}
// - (void)writeLittleEndianLong:(uint64_t)data;//{{{
- (void)writeLittleEndianLong:(uint64_t)data
{
    [self writeLong:NSSwapHostLongLongToLittle(data)];
}
//}}}
// - (void)writeLittleEndianFloat:(float)data;//{{{
- (void)writeLittleEndianFloat:(float)data
{
    NSSwappedFloat swappedFloat = NSSwapHostFloatToLittle(data);
    [self write:&swappedFloat length:sizeof(NSSwappedFloat)];
}
//}}}
// - (void)writeLittleEndianDouble:(double)data;//{{{
- (void)writeLittleEndianDouble:(double)data
{
    NSSwappedDouble swappedDouble = NSSwapHostDoubleToLittle(data);
    [self write:&swappedDouble length:sizeof(NSSwappedDouble)];
}
//}}}

// NSData Handling
// - (NSData *)dataFromReadingBytes:(intptr_t)amount;//{{{
- (NSData *)dataFromReadingBytes:(intptr_t)amount
{
    size_t total = (size_t)amount;
    size_t available = [self numberOfBytesAvailable];

    if (amount < 0) total = available;

    if ((total > available) || (total == 0) || (available == 0))
        return nil;

    NSData *data = [NSData dataWithBytes:(m_buffer + m_nextRead) length:total];

    m_nextRead += total;
    return data;
}
//}}}
// - (size_t)writeData:(NSData *)data startingAt:(uintptr_t)index length:(size_t)amount;//{{{
- (size_t)writeData:(NSData *)data startingAt:(uintptr_t)index length:(size_t)amount
{
    if ((data == nil) || (index >= [data length]) || (amount == 0))
        return 0;

    size_t total = ([data length] - index);
    const uint8_t *ptr = [data bytes];

    if (total < amount) amount = total;
    return [self write:(ptr + index) length:amount];
}
//}}}

// SFStream Handling
// - (SFStream *)streamFromReadingBytes:(intptr_t)amount;//{{{
- (SFStream *)streamFromReadingBytes:(intptr_t)amount
{
    size_t total = [self numberOfBytesAvailable];

    if (amount > 0) {
        if (total < (size_t)amount)
            return nil;
        else
            total = (size_t)amount;
    }

    SFStream *stream = [[SFStream alloc] initWithBytes:(m_buffer + m_nextRead) length:total];
    m_nextRead += total;

    return [stream autorelease];
}
//}}}
// - (size_t)writeStream:(SFStream *)stream length:(size_t)amount;//{{{
- (size_t)writeStream:(SFStream *)stream length:(size_t)amount
{
    if ((stream == nil) || ([stream numberOfBytesAvailable] == 0))
        return 0;

    amount = ((amount > [stream numberOfBytesAvailable]) ? [stream numberOfBytesAvailable] : amount);
    if (amount == 0)
        return 0;

    if (amount > (m_capacity - m_nextWrite)) {
        if (![self increaseCapacityBy:(amount - (m_capacity - m_nextWrite))])
            return 0;
    }

    amount = [self write:[stream bytes] length:amount];
    [stream setReadPosition:([stream readPosition] + amount)];

    return amount;
}
//}}}

// Reseting
// - (void)reset;//{{{
- (void)reset
{
    m_nextRead = 0;
    m_nextWrite = 0;
    m_length = 0;
}
//}}}
@end
// vim:syntax=objc.doxygen
