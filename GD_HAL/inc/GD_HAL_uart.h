#ifndef _GD_HAL_UART_H
#define _GD_HAL_UART_H

#include "gd32f4xx.h"

/**
 * @brief  HAL Status structures definition
 */
typedef enum
{
	HAL_OK       = 0x00U,
	HAL_ERROR    = 0x01U,
	HAL_BUSY     = 0x02U,
	HAL_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;

typedef struct
{
  __IO uint32_t SR;         /*!< USART Status register,                   Address offset: 0x00 */
  __IO uint32_t DR;         /*!< USART Data register,                     Address offset: 0x04 */
  __IO uint32_t BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  __IO uint32_t CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  __IO uint32_t CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  __IO uint32_t CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  __IO uint32_t GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} USART_TypeDef;

typedef struct
{
  uint32_t BaudRate;                  /*!< This member configures the UART communication baud rate.
                                           The baud rate is computed using the following formula:
                                           - IntegerDivider = ((PCLKx) / (8 * (OVR8+1) * (huart->Init.BaudRate)))
                                           - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 8 * (OVR8+1)) + 0.5
                                           Where OVR8 is the "oversampling by 8 mode" configuration bit in the CR1 register. */

  uint32_t WordLength;                /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UART_Word_Length */

  uint32_t StopBits;                  /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_Stop_Bits */

  uint32_t Parity;                    /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */

  uint32_t Mode;                      /*!< Specifies whether the Receive or Transmit mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_Mode */

  uint32_t HwFlowCtl;                 /*!< Specifies whether the hardware flow control mode is enabled or disabled.
                                           This parameter can be a value of @ref UART_Hardware_Flow_Control */

  uint32_t OverSampling;              /*!< Specifies whether the Over sampling 8 is enabled or disabled, to achieve higher speed (up to fPCLK/8).
                                           This parameter can be a value of @ref UART_Over_Sampling */
} UART_InitTypeDef;


typedef enum
{
  HAL_UART_STATE_RESET             = 0x00U,    /*!< Peripheral is not yet Initialized
                                                   Value is allowed for gState and RxState */
  HAL_UART_STATE_READY             = 0x20U,    /*!< Peripheral Initialized and ready for use
                                                   Value is allowed for gState and RxState */
  HAL_UART_STATE_BUSY              = 0x24U,    /*!< an internal process is ongoing
                                                   Value is allowed for gState only */
  HAL_UART_STATE_BUSY_TX           = 0x21U,    /*!< Data Transmission process is ongoing
                                                   Value is allowed for gState only */
  HAL_UART_STATE_BUSY_RX           = 0x22U,    /*!< Data Reception process is ongoing
                                                   Value is allowed for RxState only */
  HAL_UART_STATE_BUSY_TX_RX        = 0x23U,    /*!< Data Transmission and Reception process is ongoing
                                                   Not to be used for neither gState nor RxState.
                                                   Value is result of combination (Or) between gState and RxState values */
  HAL_UART_STATE_TIMEOUT           = 0xA0U,    /*!< Timeout state
                                                   Value is allowed for gState only */
  HAL_UART_STATE_ERROR             = 0xE0U     /*!< Error
                                                   Value is allowed for gState only */
} HAL_UART_StateTypeDef;

/**
  * @brief HAL UART Reception type definition
  * @note  HAL UART Reception type value aims to identify which type of Reception is ongoing.
  *        It is expected to admit following values :
  *           HAL_UART_RECEPTION_STANDARD         = 0x00U,
  *           HAL_UART_RECEPTION_TOIDLE           = 0x01U,
  */
typedef uint32_t HAL_UART_RxTypeTypeDef;


typedef struct __UART_HandleTypeDef
{
  USART_TypeDef                 *Instance;        /*!< UART registers base address        */

  UART_InitTypeDef              Init;             /*!< UART communication parameters      */

  const uint8_t                 *pTxBuffPtr;      /*!< Pointer to UART Tx transfer Buffer */

  uint16_t                      TxXferSize;       /*!< UART Tx Transfer size              */

  __IO uint16_t                 TxXferCount;      /*!< UART Tx Transfer Counter           */

  uint8_t                       *pRxBuffPtr;      /*!< Pointer to UART Rx transfer Buffer */

  uint16_t                      RxXferSize;       /*!< UART Rx Transfer size              */

  __IO uint16_t                 RxXferCount;      /*!< UART Rx Transfer Counter           */

  __IO HAL_UART_RxTypeTypeDef ReceptionType;      /*!< Type of ongoing reception          */

//  DMA_HandleTypeDef             *hdmatx;          /*!< UART Tx DMA Handle parameters      */
//
//  DMA_HandleTypeDef             *hdmarx;          /*!< UART Rx DMA Handle parameters      */
//
//  HAL_LockTypeDef               Lock;             /*!< Locking object                     */

  __IO HAL_UART_StateTypeDef    gState;           /*!< UART state information related to global Handle management
                                                       and also related to Tx operations.
                                                       This parameter can be a value of @ref HAL_UART_StateTypeDef */

  __IO HAL_UART_StateTypeDef    RxState;          /*!< UART state information related to Rx operations.
                                                       This parameter can be a value of @ref HAL_UART_StateTypeDef */

  __IO uint32_t                 ErrorCode;        /*!< UART Error code                    */


} UART_HandleTypeDef;

//-------------------------------------------------------------------------------------------//
///** @defgroup UART_Error_Code UART Error Code
//  * @{
//  */
//#define HAL_UART_ERROR_NONE              0x00000000U   /*!< No error            */
//#define HAL_UART_ERROR_PE                0x00000001U   /*!< Parity error        */
//#define HAL_UART_ERROR_NE                0x00000002U   /*!< Noise error         */
//#define HAL_UART_ERROR_FE                0x00000004U   /*!< Frame error         */
//#define HAL_UART_ERROR_ORE               0x00000008U   /*!< Overrun error       */
//#define HAL_UART_ERROR_DMA               0x00000010U   /*!< DMA transfer error  */
//
///** @defgroup UART_Word_Length UART Word Length
//  * @{
//  */
//#define UART_WORDLENGTH_8B                  0x00000000U
//#define UART_WORDLENGTH_9B                  ((uint32_t)USART_CR1_M)

//-------------------------------------------------------------------------------------------//

/* Initialization/de-initialization functions  **********************************/
HAL_StatusTypeDef HAL_UART_Init(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_HalfDuplex_Init(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_LIN_Init(UART_HandleTypeDef *huart, uint32_t BreakDetectLength);
//HAL_StatusTypeDef HAL_MultiProcessor_Init(UART_HandleTypeDef *huart, uint8_t Address, uint32_t WakeUpMethod);
HAL_StatusTypeDef HAL_UART_DeInit(UART_HandleTypeDef *huart);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart);

/** @addtogroup UART_Exported_Functions_Group2 IO operation functions
  * @{
  */

/* IO operation functions *******************************************************/
HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size, uint32_t Timeout);
HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
//HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
//HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
//HAL_StatusTypeDef HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, const uint8_t *pData, uint16_t Size);
//HAL_StatusTypeDef HAL_UART_Receive_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
//HAL_StatusTypeDef HAL_UART_DMAPause(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_UART_DMAResume(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_UART_DMAStop(UART_HandleTypeDef *huart);
//
//HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint16_t *RxLen,
//                                           uint32_t Timeout);
//HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
//HAL_StatusTypeDef HAL_UARTEx_ReceiveToIdle_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
//
///* Transfer Abort functions */
//HAL_StatusTypeDef HAL_UART_Abort(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_UART_AbortTransmit(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_UART_AbortReceive(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_UART_Abort_IT(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_UART_AbortTransmit_IT(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_UART_AbortReceive_IT(UART_HandleTypeDef *huart);
//
//void HAL_UART_IRQHandler(UART_HandleTypeDef *huart);
//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);
//void HAL_UART_TxHalfCpltCallback(UART_HandleTypeDef *huart);
//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
//void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart);
//void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart);
//void HAL_UART_AbortCpltCallback(UART_HandleTypeDef *huart);
//void HAL_UART_AbortTransmitCpltCallback(UART_HandleTypeDef *huart);
//void HAL_UART_AbortReceiveCpltCallback(UART_HandleTypeDef *huart);
//
//void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
//
///**
//  * @}
//  */
//
///** @addtogroup UART_Exported_Functions_Group3
//  * @{
//  */
///* Peripheral Control functions  ************************************************/
//HAL_StatusTypeDef HAL_LIN_SendBreak(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_MultiProcessor_EnterMuteMode(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_MultiProcessor_ExitMuteMode(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_HalfDuplex_EnableTransmitter(UART_HandleTypeDef *huart);
//HAL_StatusTypeDef HAL_HalfDuplex_EnableReceiver(UART_HandleTypeDef *huart);
///**
//  * @}
//  */
//
///** @addtogroup UART_Exported_Functions_Group4
//  * @{
//  */
///* Peripheral State functions  **************************************************/
//HAL_UART_StateTypeDef HAL_UART_GetState(UART_HandleTypeDef *huart);
//uint32_t              HAL_UART_GetError(UART_HandleTypeDef *huart);



#endif /* _GD_HAL_UART_H */
