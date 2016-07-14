/**
 * \file
 * Declares the interfaces, constants, structures and variables to the streams
 * module.
 *
 * \author Alessandro Antonello aantonello@paralaxe.com.br
 * \date   May 06, 2014
 * \since  Simple Framework 1.2
 *
 * \copyright
 * This file is provided in hope that it will be useful to someone. It is
 * offered in public domain. You may use, modify or distribute it freely.
 *
 * The code is provided "AS IS". There is no warranty at all, of any kind. You
 * may change it if you like. Or just use it as it is.
 */
#import <Foundation/Foundation.h>

/**
 * \ingroup sf_networking
 * The base stream protocol.
 * All interfaces in this module implements this protocol.
 *//* --------------------------------------------------------------------- */
@protocol SFStreamProtocol
// - (size_t)capacity;//{{{
/**
 * Gets the total capacity of storage in the stream.
 * The capacity is the amount of allocated memory for the stream buffer. Does
 * not mean that the stream has this amount of valid data. The valid data is
 * defined by #length message.
 * @return A \c size_t value with the stream capacity in bytes.
 **/
- (size_t)capacity;
//}}}
// - (size_t)length;//{{{
/**
 * Gets the current length of the stream buffer.
 * This operation returns the amount of valid data in the buffer.
 * @return A \c size_t value with the current buffer length in bytes.
 **/
- (size_t)length;
//}}}
@end

/**
 * \ingroup sf_networking
 * The stream reader protocol.
 * This protocol is implementend in all streams that are used to read data.
 *//* --------------------------------------------------------------------- */
@protocol SFStreamReaderProtocol
/** @name Reading Information */ //@{
// - (size_t)readPosition;//{{{
/**
 * Gets the next reading position.
 * When this value is 0, the next call to one of the reading operations will
 * read starting in the firts byte of the buffer.
 * @return An offset, when 0 is the first position in the stream, defining the
 * next reading position in the buffer.
 **/
- (size_t)readPosition;
//}}}
// - (size_t)numberOfBytesAvailable;//{{{
/**
 * Gets the number of bytes available to read.
 * @returns The number of bytes still available to read in the buffer. This is
 * a difference between the length of the buffer and the next reading
 * position.
 **/
- (size_t)numberOfBytesAvailable;
//}}}
// - (BOOL)setReadPosition:(size_t)offset;//{{{
/**
 * Enables the current reading position to change.
 * @param offset The next reading position in the stream. Must be between 0
 * and the length minus 1. Whe \a offset is out of stream bounds the function
 * fails and the current read position is not changed.
 * @return \b YES when the position is changed. \b NO otherwise.
 **/
- (BOOL)setReadPosition:(size_t)offset;
//}}}
//@}

/** @name Direct Access */ //@{
// - (const uint8_t *)bytes;//{{{
/**
 * Direct access the stream data.
 * @return A pointer to the first byte in the next reading position. The
 * result is \c const so you do not change the memory content. The resulting
 * address is valid only until the underling stream is released or its
 * content is changed, which can invalidated completely the returned address.
 * Use it only for temporary access.
 **/
- (const uint8_t *)bytes;
//}}}
// - (const uint8_t *)bytesAtIndex:(size_t)offset;//{{{
/**
 * Direct access the stream data.
 * @param offset Position offset, from the start of the buffer (position 0)
 * for the address to return. The next reading position will not be changed or
 * used by this operation.
 * @return A pointer to the first byte in the offset position requested. The
 * result is \c const so you do not change the memory content. The resulting
 * address is valid only until the underling stream is released or its
 * content is changed, which can invalidated completely the returned address.
 * Use it only for temporary access.
 *
 * If \a offset pass the length of the stream data an <b>Assertion Failed</b>
 * will be raised in debug mode. In this case the result will be \b NULL in
 * all modes.
 **/
- (const uint8_t *)bytesAtIndex:(size_t)offset;
//}}}
//@}

/** @name Basic Reading Operations */ //@{
// - (size_t)read:(void *)buffer length:(size_t)length;//{{{
/**
 * Reads one or more bytes starting from the current reading position.
 * @param buffer Address to store the read bytes.
 * @param length Number of bytes to read. Cannot be greater than
 * #numberOfBytesAvailable. If so, only the number of bytes available will be
 * stored in \a buffer.
 * @return The function returns the number of bytes stored in \a buffer
 * address. This value can be equal or less the value of \a length parameter.
 * @remarks The read position is updated after this operation, with the real
 * number of bytes read.
 **/
- (size_t)read:(void *)buffer length:(size_t)length;
//}}}
// - (uint8_t)readByte;//{{{
/**
 * Read one byte of the stream and return it.
 * @return The one byte read.
 * @remarks The current read position is updated after this operation.
 **/
- (uint8_t)readByte;
//}}}
// - (uint16_t)readShort;//{{{
/**
 * Reads 2 bytes from the stream and return an unsigned short int value.
 * @return An unsigned short value built from the value of 2 bytes from the
 * stream. The host byte order is used to combine the two bytes into the
 * unsigned short value.
 * @remarks The read position is updated by 2 after this operation returns.
 **/
- (uint16_t)readShort;
//}}}
// - (uint32_t)readInt;//{{{
/**
 * Reads four bytes from the stream and returns an unsigned int value.
 * @returns An unsigned int value built from four bytes. The host byte order
 * is used to combine the bytes into the unsigned int value.
 * @remarks The read position is updated by 4 after this operation returns.
 **/
- (uint32_t)readInt;
//}}}
// - (uint64_t)readLong;//{{{
/**
 * Reads eigth bytes from the stream and returns an unsigned long long value.
 * @returns An unsigned long long value built from eight bytes. The host byte
 * order is used to combine the bytes into the unsigned long long value.
 * @remarks The read position is updated by 8 after this operation returns.
 **/
- (uint64_t)readLong;
//}}}
// - (float)readFloat;//{{{
/**
 * Reads four bytes from the stream and returns float value.
 * @returns A float value built from four bytes. The host byte order
 * is used to combine the bytes into the float value.
 * @remarks The read position is updated by 4 after this operation returns.
 **/
- (float)readFloat;
//}}}
// - (double)readDouble;//{{{
/**
 * Reads eight bytes from the stream and returns a double value.
 * @returns A double value built from eight bytes. The host byte order
 * is used to combine the bytes into the double value.
 * @remarks The read position is updated by 8 after this operation returns.
 **/
- (double)readDouble;
//}}}
// - (void)purgeReadBytes;//{{{
/**
 * Purge the data already read in this stream.
 * Implementations may call this method automatically after a reading
 * operation. Be carefull with its usage. All data between the buffer start
 * and the next reading position will be removed becaming unaccesible.
 **/
- (void)purgeReadBytes;
//}}}
//@}

@optional
/** @name Big-Endian to Host Conversions */ //@{
// - (uint16_t)readBigEndianShort;//{{{
/**
 * Reads two bytes from the stream.
 * @returns An unsigned short value built from the 2 bytes read. This function
 * assumes that the value is stored in \b big-endian byte order and will
 * convert it to host byte order.
 * @remarks The read position is updated by 2 after this operation returns.
 **/
- (uint16_t)readBigEndianShort;
//}}}
// - (uint32_t)readBigEndianInt;//{{{
/**
 * Reads four bytes from the stream.
 * @returns An unsigned int value built from the 4 bytes read. This function
 * assumes that the value is stored in \b big-endian byte order and will
 * convert it to host byte order.
 * @remarks The read position is updated by 4 after this operation returns.
 **/
- (uint32_t)readBigEndianInt;
//}}}
// - (uint64_t)readBigEndignLong;//{{{
/**
 * Reads eight bytes from the stream.
 * @returns An unsigned long long value built from the 8 bytes read. This
 * function assumes that the value is stored in \b big-endian byte order and
 * will convert it to host byte order.
 * @remarks The read position is updated by 8 after this operation returns.
 **/
- (uint64_t)readBigEndignLong;
//}}}
// - (float)readBigEndianFloat;//{{{
/**
 * Reads four bytes from the stream.
 * @returns A float value built from the 4 bytes read. This function
 * assumes that the value is stored in \b big-endian byte order and will
 * convert it to host byte order.
 * @remarks The read position is updated by 4 after this operation returns.
 **/
- (float)readBigEndianFloat;
//}}}
// - (double)readBigEndianDouble;//{{{
/**
 * Reads eight bytes from the stream.
 * @returns A double value built from the 8 bytes read. This function
 * assumes that the value is stored in \b big-endian byte order and will
 * convert it to host byte order.
 * @remarks The read position is updated by 8 after this operation returns.
 **/
- (double)readBigEndianDouble;
//}}}
//@}

/** @name Little-Endian to Host Conversions */ //@{
// - (uint16_t)readLittleEndianShort;//{{{
/**
 * Reads two bytes from the stream.
 * @returns An unsigned short value built from the 2 bytes read. This function
 * assumes that the value is stored in \b little-endian byte order and will
 * convert it to host byte order.
 * @remarks The read position is updated by 2 after this operation returns.
 **/
- (uint16_t)readLittleEndianShort;
//}}}
// - (uint32_t)readLittleEndianInt;//{{{
/**
 * Reads four bytes from the stream.
 * @returns An unsigned int value built from the 4 bytes read. This function
 * assumes that the value is stored in \b little-endian byte order and will
 * convert it to host byte order.
 * @remarks The read position is updated by 4 after this operation returns.
 **/
- (uint32_t)readLittleEndianInt;
//}}}
// - (uint64_t)readLittleEndianLong;//{{{
/**
 * Reads eight bytes from the stream.
 * @returns An unsigned long long value built from the 8 bytes read. This
 * function assumes that the value is stored in \b little-endian byte order
 * and will convert it to host byte order.
 * @remarks The read position is updated by 8 after this operation returns.
 **/
- (uint64_t)readLittleEndianLong;
//}}}
// - (float)readLittleEndianFloat;//{{{
/**
 * Reads four bytes from the stream.
 * @returns A float value built from the 4 bytes read. This function
 * assumes that the value is stored in \b little-endian byte order and will
 * convert it to host byte order.
 * @remarks The read position is updated by 4 after this operation returns.
 **/
- (float)readLittleEndianFloat;
//}}}
// - (double)readLittleEndianDouble;//{{{
/**
 * Reads eight bytes from the stream.
 * @returns A double value built from the 8 bytes read. This function
 * assumes that the value is stored in \b little-endian byte order and will
 * convert it to host byte order.
 * @remarks The read position is updated by 8 after this operation returns.
 **/
- (double)readLittleEndianDouble;
//}}}
//@}
@end

/**
 * \ingroup sf_networking
 * The stream writer protocol.
 * Implemented in interfaces used to write streams.
 *//* --------------------------------------------------------------------- */
@protocol SFStreamWriterProtocol
/** @name Writting Information */ //@{
// - (size_t)writePosition;//{{{
/**
 * Gets the next write position.
 * When this operation returns 0, the next write operation will start in the
 * beginning of the stream buffer.
 * @return The next write position from the start of the stream.
 **/
- (size_t)writePosition;
//}}}
// - (BOOL)setWritePosition:(size_t)offset;//{{{
/**
 * Changes the write position.
 * @param offset An offset, from the start of the stream, to position the next
 * write operation. This canno be greater than the length of the stream. If so
 * the operation will fail and the write position will not be changed.
 * @return \b YES when the position is changed. Otherwise \b NO.
 **/
- (BOOL)setWritePosition:(size_t)offset;
//}}}
//@}

/** @name Direct Access */ //@{
// - (void *)bufferWithLength:(size_t)length;//{{{
/**
 * Provices write access to the internal stream buffer.
 * @param length The length required for writing operation. The operation
 * garantees that the resulting address will have this amount of memory
 * available.
 * @return An address pointing to a writable memory buffer. The write position
 * will be taken into account in the resulting pointer. You can update the
 * write position before and later using #setWritePosition:.
 *
 * If \a length is zero the function could return an address after the
 * internal buffer length. Which is dangerous. For this reason if \a length
 * parameter is zero the function returns \b NULL.
 *
 * The function will also return \b NULL if there is no memory available.
 **/
- (void *)bufferWithLength:(size_t)length;
//}}}
//@}

/** @name Basic Writting Operations */ //@{
// - (size_t)write:(const void*)data length:(size_t)size;//{{{
/**
 * Write bytes to the stream.
 * @param data Address with the bytes to be written.
 * @param size Length of bytes to write in the stream.
 * @return Number of bytes actualy written.
 * @remarks The capacity of the stream is automaticaly increased if more
 * memory is need to write the total amount of bytes passed. So, the operation
 * will return a value less than \a size parameter if there is no memory
 * available.
 *
 * The write position is update by the number of total bytes written.
 **/
- (size_t)write:(const void*)data length:(size_t)size;
//}}}
// - (void)writeByte:(uint8_t)data;//{{{
/**
 * Writes a single byte to the stream.
 * @param data Value of the byte to be written.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeByte:(uint8_t)data;
//}}}
// - (void)writeShort:(uint16_t)data;//{{{
/**
 * Writes two bytes to the stream.
 * @param data Unsigned short value to be written.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeShort:(uint16_t)data;
//}}}
// - (void)writeInt:(uint32_t)data;//{{{
/**
 * Writes four bytes to the stream.
 * @param data Unsigned int value to be written.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeInt:(uint32_t)data;
//}}}
// - (void)writeLong:(uint64_t)data;//{{{
/**
 * Writes eight bytes to the stream.
 * @param data Unsigned long long value to be written.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeLong:(uint64_t)data;
//}}}
// - (void)writeFloat:(float)data;//{{{
/**
 * Writes four bytes to the stream.
 * @param data Float value to be written.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeFloat:(float)data;
//}}}
// - (void)writeDouble:(double)data;//{{{
/**
 * Writes eight bytes to the stream.
 * @param data Double value to be written.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeDouble:(double)data;
//}}}
//@}

@optional
/** @name Host to Big-Endian Conversions */ //@{
// - (void)writeBigEndianShort:(uint16_t)data;//{{{
/**
 * Writes two bytes in the stream.
 * @param data Unsigned short value to be written. The function will convert
 * this value from <b>host byte order</b> to <b>big-endian byte order</b> if
 * needed.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeBigEndianShort:(uint16_t)data;
//}}}
// - (void)writeBigEndianInt:(uint32_t)data;//{{{
/**
 * Writes four bytes in the stream.
 * @param data Unsigned int value to be written. The function will convert
 * this value from <b>host byte order</b> to <b>big-endian byte order</b> if
 * needed.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeBigEndianInt:(uint32_t)data;
//}}}
// - (void)writeBigEndianLong:(uint64_t)data;//{{{
/**
 * Writes eight bytes in the stream.
 * @param data Unsigned long long value to be written. The function will
 * convert this value from <b>host byte order</b> to <b>big-endian byte
 * order</b> if needed.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeBigEndianLong:(uint64_t)data;
//}}}
// - (void)writeBigEndianFloat:(float)data;//{{{
/**
 * Writes four bytes in the stream.
 * @param data Float value to be written. The function will convert this value
 * from <b>host byte order</b> to <b>big-endian byte order</b> if needed.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeBigEndianFloat:(float)data;
//}}}
// - (void)writeBigEndianDouble:(double)data;//{{{
/**
 * Writes eight bytes in the stream.
 * @param data Double value to be written. The function will convert this
 * value from <b>host byte order</b> to <b>big-endian byte order</b> if
 * needed.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeBigEndianDouble:(double)data;
//}}}
//@}

/** @name Host to Little-Endian Conversions */ //@{
// - (void)writeLittleEndianShort:(uint16_t)data;//{{{
/**
 * Writes two bytes in the stream.
 * @param data Unsigned short value to be written. The function will convert
 * this value from <b>host byte order</b> to <b>little-endian byte order</b>
 * if needed.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeLittleEndianShort:(uint16_t)data;
//}}}
// - (void)writeLittleEndianInt:(uint32_t)data;//{{{
/**
 * Writes four bytes in the stream.
 * @param data Unsigned int value to be written. The function will convert
 * this value from <b>host byte order</b> to <b>little-endian byte order</b>
 * if needed.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeLittleEndianInt:(uint32_t)data;
//}}}
// - (void)writeLittleEndianLong:(uint64_t)data;//{{{
/**
 * Writes eight bytes in the stream.
 * @param data Unsigned long long value to be written. The function will
 * convert this value from <b>host byte order</b> to <b>little-endian byte
 * order</b> if needed.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeLittleEndianLong:(uint64_t)data;
//}}}
// - (void)writeLittleEndianFloat:(float)data;//{{{
/**
 * Writes four bytes in the stream.
 * @param data Float value to be written. The function will convert this value
 * from <b>host byte order</b> to <b>little-endian byte order</b> if needed.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeLittleEndianFloat:(float)data;
//}}}
// - (void)writeLittleEndianDouble:(double)data;//{{{
/**
 * Writes eight bytes in the stream.
 * @param data Double value to be written. The function will convert this
 * value from <b>host byte order</b> to <b>little-endian byte order</b> if
 * needed.
 * @remarks The write position is updated after this operation.
 **/
- (void)writeLittleEndianDouble:(double)data;
//}}}
//@}
@end

/*
 * A readonly memory stream.
 *//* --------------------------------------------------------------------- */
// @interface SFStreamReader : NSObject <SFStreamProtocol, SFStreamReaderProtocol>
// Initialization
//- (instancetype)initWithBytes:(const void*)data length:(size_t)size;
//- (instancetype)initWithData:(NSData *)data;
//@end

/*
 * A write only memory stream.
 *//* --------------------------------------------------------------------- */
//@interface SFStreamWriter : NSObject <SFStreamProtocol, SFStreamWriterProtocol>
// Initialization
//- (instancetype)initWithCapacity:(size_t)capacity;
//@end

/**
 * \ingroup sf_networking
 * A read-write memory stream.
 *//* --------------------------------------------------------------------- */
@interface SFStream : NSObject <SFStreamProtocol, SFStreamReaderProtocol, SFStreamWriterProtocol>
/** @name Designated Initializers */ //@{
// - (instancetype)initWithBytes:(const void*)data length:(size_t)size;//{{{
/**
 * Initializes the object with bytes from a memory location.
 * @param data Memory location of data to copy.
 * @param size Amount of bytes to store in the stream.
 * @return This object initialized.
 **/
- (instancetype)initWithBytes:(const void*)data length:(size_t)size;
//}}}
// - (instancetype)initWithData:(NSData *)data;//{{{
/**
 * Initializes the object with bytes from a NSData object.
 * @param data NSData object with content will be stored in this stream.
 * @return This object initialized.
 **/
- (instancetype)initWithData:(NSData *)data;
//}}}
// - (instancetype)initWithStream:(SFStream *)stream;//{{{
/**
 * Initializes the object copying data from another SFStream object.
 * @param stream SFStrem with data to copy.
 * @return This object initialized.
 * @remarks The copy will start at the current read position. All available
 * bytes will be read.
 **/
- (instancetype)initWithStream:(SFStream *)stream;
//}}}
// - (instancetype)initWithCapacity:(size_t)capacity;//{{{
/**
 * Initializes the object with an initial buffer capacity.
 * @param capacity The initial memory capacity for this stream.
 * @return This object initialized.
 **/
- (instancetype)initWithCapacity:(size_t)capacity;
//}}}
//@}

/** @name NSData Handling */ //@{
// - (NSData *)dataFromReadingBytes:(intptr_t)amount;//{{{
/**
 * Reads data from this stream returning a NSData object containing the data.
 * @param amount The amount of bytes to read. This must be a number between 0
 * and the total number of bytes available (#numberOfBytesAvailable). With the
 * exception of \b -1, that instructs the operation to read all bytes
 * available.
 * @return A temporary \c NSData object with the read bytes. If the operation
 * reads 0 bytes or there is no data available in this stream, the operation
 * returns \b nil.
 * @remarks The read position will be updated with the final amount of data
 * read.
 **/
- (NSData *)dataFromReadingBytes:(intptr_t)amount;
//}}}
// - (size_t)writeData:(NSData *)data startingAt:(uintptr_t)index length:(size_t)amount;//{{{
/**
 * Writes this stream with data from a NSData object.
 * @param data NSData object with data to copy.
 * @param index Zero based index with the byte offset to start the copy on the
 * \a data object.
 * @param amount Total amount of bytes to copy, starting from \a index offset.
 * @return The total amount of bytes read from \a data object and copyed to
 * this stream.
 * @remarks When \a data is \b nil, \a index is beond the NSData boundaries or
 * \a amount is zero, the function does nothing and returns zero. If you pass
 * \c UINTPTR_MAX in the \a amount parameter the operation will copy all bytes
 * starting from \a index till the end of the \c NSData object.
 *
 * The operation updated the write position and the length of the stream, if
 * it is necessary.
 **/
- (size_t)writeData:(NSData *)data startingAt:(uintptr_t)index length:(size_t)amount;
//}}}
//@}

/** @name SFStream Handling */ //@{
// - (SFStream *)streamFromReadingBytes:(intptr_t)amount;//{{{
/**
 * Build another SFStream object with data read from this stream.
 * @param amount The total number of bytes to read starting from the read
 * position.
 * @return A temporary \c SFStream object with the data read.
 * @remarks \a amount can be less than zero indicating that all available
 * bytes should be used to create the new \c SFStream object. Otherwise, if \a
 * amount is greater than the number of bytes available, the function fails
 * returning \b nil.
 *
 * The read position will be updated with the total number of bytes read after
 * this operation returns.
 **/
- (SFStream *)streamFromReadingBytes:(intptr_t)amount;
//}}}
// - (size_t)writeStream:(SFStream *)stream length:(size_t)amount;//{{{
/**
 * Writes data from another SFStream object to this stream.
 * @param stream SFStream object with data to copy to this one.
 * @param amount Total number of bytes to copy from \a stream. \c UINTPTR_MAX
 * can be used to copy the entire stream.
 * @return The final amount of bytes copyed from \a stream.
 * @remarks If \a stream is \b nil or \a amount is zero nothing is done and
 * the operation returns zero. The copy always starts from the reading
 * position of \a stream parameter. The bytes are copyed starting in the next
 * write position of this stream. The write position and length of this stream
 * are updated if needed.
 **/
- (size_t)writeStream:(SFStream *)stream length:(size_t)amount;
//}}}
//@}

/** @name Reseting */ //@{
// - (void)reset;//{{{
/**
 * Resets both read and write position.
 * Also the function sets the length of the stream to zero. Still, memory will
 * not be dealocated. The capacity remains the same.
 **/
- (void)reset;
//}}}
//@}
@end
// vim:ft=objc syntax=objc.doxygen
