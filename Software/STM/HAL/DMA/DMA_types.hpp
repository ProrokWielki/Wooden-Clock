/**
 * DMA_types.hpp
 *
 *  Created on: 30-11-2018
 *  @author: Paweł Warzecha
 */

#ifndef HAL_DMA_DMA_TYPES_HPP_
#define HAL_DMA_DMA_TYPES_HPP_

/**
 * @brief DMA priorities
 */
typedef enum
{
    eDMALow,      //!< eDMALow low priority
    eDMAMedium,   //!< eDMAMedium medium priority
    eDMAHigh,     //!< eDMAHigh high priority
    eDMAVeryHigh  //!< eDMAVeryHigh very high priority
} DMAPriority_t;

/**
 * @brief DMA data size.
 */
typedef enum
{
    e8Bits,   //!< e8Bits 8 bits data size
    e16Bits,  //!< e16Bits 16 bits data size
    e32Bits   //!< e32Bits 32 bits data size
} DMASize_t;

/**
 * @brief DMA requests.
 */
typedef enum
{
    eRequest0,  //!< eRequest0 request 0
    eRequest1,  //!< eRequest1 request 1
    eRequest2,  //!< eRequest2 request 2
    eRequest3,  //!< eRequest3 request 3
    eRequest4,  //!< eRequest4 request 4
    eRequest5,  //!< eRequest5 request 5
    eRequest6,  //!< eRequest6 request 6
    eRequest7   //!< eRequest7 request 7
} DMARequest_t;

/**
 * @brief Read direciton
 */
typedef enum
{
    eReadFromPeriphearl,  //!< eReadFromPeriphearl read for peripheral
    eReadFromMemory       //!< eReadFromMemory read from memory
} DMAReadDirection_t;

/**
 * @brief DMA interrupts
 */
typedef enum
{
    eTransferError = DMA_CCR_TEIE_Pos,     //!< eTransferError transfer error interrupt
    eHalfTransfer = DMA_CCR_HTIE_Pos,      //!< eHalfTransfer half transfer interrupt
    eTransferCompleted = DMA_CCR_TCIE_Pos  //!< eTransferCompleted transfer complete interrupt
} DMAInterrupts_t;
#endif /* HAL_DMA_DMA_TYPES_HPP_ */
