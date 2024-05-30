///*
//* File: stm32f1_rc522.c
//* Author: Duong Bao Nguyen
//* Date: 4/18/2024
//* Description: This file are functions of RC522
//*/
//#include "stm32f1_rc522.h"


///*
// * Function name: RC522_SPI_Transfer
// * Function: wait 1 byte is stored in register MFRC522
// * Input: data --> data to send
// * Output: Byte revice form RFID
// */
//uint8_t RC522_SPI_Transfer(uint8_t data)
//{
//	/*uint8_t rx_data;
//	HAL_SPI_TransmitReceive(&hspi2,&data,&rx_data,1,100);
//	return rx_data;*/
//	while(SPI_I2S_GetFlagStatus(MFRC522_SPI, SPI_I2S_FLAG_TXE)==RESET);
//	SPI_I2S_SendData(MFRC522_SPI,data);

//	while(SPI_I2S_GetFlagStatus(MFRC522_SPI, SPI_I2S_FLAG_RXNE)==RESET);
//	return SPI_I2S_ReceiveData(MFRC522_SPI);
//}


///*
// * Function name: Write_MFRC5200
// * Function: wait 1 byte is stored in register MFRC522
// * Input: addr-> DIa write only, val-> Value to write
// * Output: No
// */
//void Write_MFRC522(uint8_t addr, uint8_t val)
//{
//	/* CS LOW */
//	GPIO_ResetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);
//	//The address is located:0XXXXXX0
//	RC522_SPI_Transfer((addr<<1)&0x7E);	
//	RC522_SPI_Transfer(val);
//	
//	/* CS HIGH */
//	GPIO_SetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);
//}

///*
// * Function name: Read_MFRC522
// * Function: A 1-byte doc is stored from a register MFRC522
// * Input: addr-> address doc
// * Output: value address
// */
//uint8_t Read_MFRC522(uint8_t addr)
//{
//	uint8_t val;

//	/* CS LOW */
//	GPIO_ResetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);
//	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_RESET);

//	//The address is located:1XXXXXX0
//	RC522_SPI_Transfer(((addr<<1)&0x7E) | 0x80);	
//	val = RC522_SPI_Transfer(0x00);
//	
//	/* CS HIGH */
//	GPIO_SetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);
//	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);
//	return val;	
//	
//}


///*
// * Function name: SetBitMask
// * Function: Set bits in an MFRC522 register
// * Input: reg - Registers settings; mask - value set
// * Output: No
// */
//void SetBitMask(uint8_t reg, uint8_t mask)  
//{
//    uint8_t tmp;
//    tmp = Read_MFRC522(reg);
//    Write_MFRC522(reg, tmp | mask);  // set bit mask
//}


///*
// * Function name: ClearBitMask
// * Function: Reset bit in register MFRC522
// * Input: reg - Dia register; mask - Value bit can clear
// * Output: No
// */
//void ClearBitMask(uint8_t reg, uint8_t mask)  
//{
//    uint8_t tmp;
//    tmp = Read_MFRC522(reg);
//    Write_MFRC522(reg, tmp & (~mask));  // clear bit mask
//} 



///*
// * Function name: AntennaOn
// * Function: Turn on antenna, should have at least 1 ms
// * Input: No
// * Output: No
// */
//void AntennaOn(void)
//{
//		Read_MFRC522(TxControlReg);
//		//	if (!(temp & 0x03))
//		//	{
//		//		SetBitMask(TxControlReg, 0x03);
//		//	}
//		SetBitMask(TxControlReg, 0x03);
//}


///*
// * Function name: AntennaOff
// * Function: Turn off antenna
// * Input: No
// * Output: No
// */
//void AntennaOff(void)
//{
//	ClearBitMask(TxControlReg, 0x03);
//}


///*
// * Function name: ResetMFRC522
// * Function: Restart RC522
// * Input: No
// * Output: No
// */
//void MFRC522_Reset(void)
//{
//    Write_MFRC522(CommandReg, PCD_RESETPHASE);
//}


///*
// * Function name: MFRC522_SPI_Init
// * Function: Start SPI
// * Input: No
// * Output: No
// */
//void MFRC522_SPI_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct;
//	SPI_InitTypeDef SPI_InitStruct;
//	
//	RCC_APB2PeriphClockCmd(MFRC522_SPI_GPIO_RCC | RCC_APB2Periph_AFIO,ENABLE);		// Enable clock GPIO
//	
//	if(MFRC522_SPI==SPI1)
//	{
//		RCC_APB2PeriphClockCmd(MFRC522_SPI_RCC,ENABLE);															// Enable clock SPI1
//	}
//	else
//	{
//		RCC_APB1PeriphClockCmd(MFRC522_SPI_RCC,ENABLE);																// Enable clock SPI2 or SPI3
//	}
//	
//	// Set digital pin B0 as OUTPUT to connect it to the RFID /ENABLE pin 
//	GPIO_InitStruct.GPIO_Pin = MFRC522_CS_PIN;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(MFRC522_CS_GPIO, &GPIO_InitStruct);
//	
//	GPIO_InitStruct.GPIO_Pin = MFRC522_RST_PIN;			// Set digital pin 10 , Not Reset and Power-down
//	GPIO_Init(MFRC522_RST_GPIO, &GPIO_InitStruct);
//	
//	GPIO_InitStruct.GPIO_Pin = MFRC522_SCK_PIN | MFRC522_MISO_PIN | MFRC522_MOSI_PIN;	// SCK, MISO, MOSI
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(MFRC522_SPI_GPIO, &GPIO_InitStruct);																	// init GPIO SPI

//	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
//	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
//	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
//	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
//	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
//	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
//	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
//	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
//	SPI_InitStruct.SPI_CRCPolynomial = 7;
//	SPI_Init(MFRC522_SPI, &SPI_InitStruct);

//	SPI_Cmd(MFRC522_SPI, ENABLE);
//}


///*
// * Function name: MFRC522_Init
// * Function: Start MFRC522
// * Input: No
// * Output: No
// */
//void MFRC522_Init(void)
//{

//	//GPIO_SetBits(MFRC522_CS_GPIO,MFRC522_CS_PIN);						// Activate the RFID reader
//	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_9,GPIO_PIN_SET);
//	//HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
//	
//	//GPIO_WriteBit(GPIOA,GPIO_Pin_9,Bit_SET);
//	//GPIO_WriteBit(GPIOA,GPIO_Pin_8,Bit_SET);
//	
//	//GPIO_SetBits(MFRC522_RST_GPIO,MFRC522_RST_PIN);					// not reset


//	MFRC522_SPI_Init();
//	GPIO_SetBits(MFRC522_CS_GPIO,MFRC522_CS_PIN);						// Activate the RFID reader
//	GPIO_SetBits(MFRC522_RST_GPIO,MFRC522_RST_PIN);	
//	MFRC522_Reset();


//	 	
//	//Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
//	Write_MFRC522(TModeReg, 0x8D);		//auto=1; f(Timer) = 6.78MHz/TPreScaler
//	Write_MFRC522(TPrescalerReg, 0x3E);	//TModeReg[3..0] + TPrescalerReg
//	Write_MFRC522(TReloadRegL, 30);           
//	Write_MFRC522(TReloadRegH, 0);
//	
//	Write_MFRC522(TxAutoReg, 0x40);		//100%ASK
//	Write_MFRC522(ModeReg, 0x3D);		//CRC Original value 0x6363	???

//	//ClearBitMask(Status2Reg, 0x08);		//MFCrypto1On=0
//	//Write_MFRC522(RxSelReg, 0x86);		//RxWait = RxSelReg[5..0]
//	//Write_MFRC522(RFCfgReg, 0x7F);   		//RxGain = 48dB

//	AntennaOn();		//Mo Anten
//}


///*
// * Function name: MFRC522_ToCard
// * Function: Information between RC522 and ISO14443
// * Input: command  - send to MF522,
// *			  sendData - Remittance sent to the state MFRC522, 
// *			  sendLen  - Send the message number
// *			  backData - BackData is returned
// *			  backLen  - Retrieve the data number
// * Output: MI_OK if successful
// */
//uint8_t MFRC522_ToCard(uint8_t command, uint8_t *sendData, uint8_t sendLen, uint8_t *backData, uint *backLen)
//{
//    uint8_t status = MI_ERR;
//    uint8_t irqEn = 0x00;
//    uint8_t waitIRq = 0x00;
//    uint8_t lastBits;
//    uint8_t n;
//    uint i;

//    switch (command)
//    {
//        case PCD_AUTHENT:		//Acknowledging the liver
//		{
//			irqEn = 0x12;
//			waitIRq = 0x10;
//			break;
//		}
//		case PCD_TRANSCEIVE:	// FIFO data collection
//		{
//			irqEn = 0x77;
//			waitIRq = 0x30;
//			break;
//		}
//		default:
//			break;
//    }
//   
//    Write_MFRC522(CommIEnReg, irqEn|0x80);	//Yeu cau ngat
//    ClearBitMask(CommIrqReg, 0x80);			//Clear all the bits
//    SetBitMask(FIFOLevelReg, 0x80);			//FlushBuffer=1, FIFO
//    
//	Write_MFRC522(CommandReg, PCD_IDLE);	//NO action; Huy bo lenh hien hanh	???

//	// Record in FIFO
//    for (i=0; i<sendLen; i++)
//    {   
//		Write_MFRC522(FIFODataReg, sendData[i]);    
//	}

//	//chay
//	Write_MFRC522(CommandReg, command);
//    if (command == PCD_TRANSCEIVE)
//    {    
//		SetBitMask(BitFramingReg, 0x80);		//StartSend=1,transmission of data starts  
//	}   
//    
//	//The team is allowed to be stored
//	i = 2000;	//i tuy thuoc tan so thach anh, thoi gian toi da cho the M1 la 25ms
//    do 
//    {
//		//CommIrqReg[7..0]
//		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
//        n = Read_MFRC522(CommIrqReg);
//        i--;
//    }
//    while ((i!=0) && !(n&0x01) && !(n&waitIRq));

//    ClearBitMask(BitFramingReg, 0x80);			//StartSend=0
//	
//    if (i != 0)
//    {    
//        if(!(Read_MFRC522(ErrorReg) & 0x1B))	//BufferOvfl Collerr CRCErr ProtecolErr
//        {
//            status = MI_OK;
//            if (n & irqEn & 0x01)
//            {   
//				status = MI_NOTAGERR;			//??   
//			}

//            if (command == PCD_TRANSCEIVE)
//            {
//               	n = Read_MFRC522(FIFOLevelReg);
//              	lastBits = Read_MFRC522(ControlReg) & 0x07;
//                if (lastBits)
//                {   
//					*backLen = (n-1)*8 + lastBits;   
//				}
//                else
//                {   
//					*backLen = n*8;   
//				}

//                if (n == 0)
//                {   
//					n = 1;    
//				}
//                if (n > MAX_LEN)
//                {   
//					n = MAX_LEN;   
//				}
//				
//				//FIFO doc in the received data
//                for (i=0; i<n; i++)
//                {   
//					backData[i] = Read_MFRC522(FIFODataReg);    
//				}
//            }
//        }
//        else
//        {   
//			status = MI_ERR;  
//		}
//        
//    }
//	
//    //SetBitMask(ControlReg,0x80);           //timer stops
//    //Write_MFRC522(CommandReg, PCD_IDLE); 

//    return status;
//}

///*
// * Fuction name: MFRC522_Request
// * Fuction: Show it, read it
// * Input: reqMode - Phat is able,
// *			 	TagType - Type of check
// *			 	0x4400 = Mifare_UltraLight
// *				0x0400 = Mifare_One(S50)
// *				0x0200 = Mifare_One(S70)
// *				0x0800 = Mifare_Pro(X)
// *				0x4403 = Mifare_DESFire
// * Output: MI_OK if the bar is curved
// */
//uint8_t MFRC522_Request(uint8_t reqMode, uint8_t *TagType)
//{
//	uint8_t status;  
//	uint backBits;			//The bits are manipulated

//	Write_MFRC522(BitFramingReg, 0x07);		//TxLastBists = BitFramingReg[2..0]	???
//	
//	TagType[0] = reqMode;
//	status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

//	if ((status != MI_OK) || (backBits != 0x10))
//	{    
//		status = MI_ERR;
//	}
//   
//	return status;
//}


///*
// * Function name: MFRC522_Anticoll
// * Function: Detect the collision, select and read the serial number
// * Input: serNum - Look up the serial the 4 byte, byte 5 is the ma checksum
// * Output: MI_OK if successful
// */
//uint8_t MFRC522_Anticoll(uint8_t *serNum)
//{
//    uint8_t status;
//    uint8_t i;
//		uint8_t serNumCheck=0;
//    uint unLen;
//    

//    //ClearBitMask(Status2Reg, 0x08);		//TempSensclear
//    //ClearBitMask(CollReg,0x80);			//ValuesAfterColl
//		Write_MFRC522(BitFramingReg, 0x00);		//TxLastBists = BitFramingReg[2..0]
// 
//    serNum[0] = PICC_ANTICOLL;
//    serNum[1] = 0x20;
//    status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

//    if (status == MI_OK)
//	{
//		//Check the serial number
//		for (i=0; i<4; i++)
//		{   
//		 	serNumCheck ^= serNum[i];
//		}
//		if (serNumCheck != serNum[i])
//		{   
//			status = MI_ERR;    
//		}
//    }

//    //SetBitMask(CollReg, 0x80);		//ValuesAfterColl=1

//    return status;
//} 


///*
// * Function name: CalulateCRC
// * Function: MFRC522 is a formula of RC522
// * Input: pIndata - Data CRC into calculator, wool - Data data, pOutData - CRC calculation
// * Output: No
// */
//void CalulateCRC(uint8_t *pIndata, uint8_t len, uint8_t *pOutData)
//{
//    uint8_t i, n;

//    ClearBitMask(DivIrqReg, 0x04);			//CRCIrq = 0
//    SetBitMask(FIFOLevelReg, 0x80);			//Con tro FIFO
//    //Write_MFRC522(CommandReg, PCD_IDLE);

//	//Record in FIFO
//    for (i=0; i<len; i++)
//    {   
//		Write_MFRC522(FIFODataReg, *(pIndata+i));   
//	}
//    Write_MFRC522(CommandReg, PCD_CALCCRC);

//	// Let the CRC computer complete
//    i = 0xFF;
//    do 
//    {
//        n = Read_MFRC522(DivIrqReg);
//        i--;
//    }
//    while ((i!=0) && !(n&0x04));			//CRCIrq = 1

//	//Doc results in CRC calculation
//    pOutData[0] = Read_MFRC522(CRCResultRegL);
//    pOutData[1] = Read_MFRC522(CRCResultRegM);
//}


///*
// * Function name: MFRC522_SelectTag
// * Function: read the right way
// * Input:serNum--So serial the
// * Output: Use the same amount of inspection
// */
//uint8_t MFRC522_SelectTag(uint8_t *serNum)
//{
//	uint8_t i;
//	uint8_t status;
//	uint8_t size;
//	uint recvBits;
//	uint8_t buffer[9]; 

//	//ClearBitMask(Status2Reg, 0x08);			//MFCrypto1On=0

//    buffer[0] = PICC_SElECTTAG;
//    buffer[1] = 0x70;
//    for (i=0; i<5; i++)
//    {
//    	buffer[i+2] = *(serNum+i);
//    }
//	CalulateCRC(buffer, 7, &buffer[7]);		//??
//    status = MFRC522_ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);
//    
//    if ((status == MI_OK) && (recvBits == 0x18))
//    {   
//		size = buffer[0]; 
//	}
//    else
//    {   
//		size = 0;    
//	}

//    return size;
//}


///*
// * Function name: MFRC522_Auth
// * Function: Identify the bad face
// * Input:    authMode - Check your password
//                 0x60 = Film confirmation A
//                 0x61 = Film confirmation B
//             BlockAddr - Addresses
//             Sectorkey - The shadow area
//             serNum - So serial the, 4 bytes
// * Output: MI_OK if successful
// */
//uint8_t MFRC522_Auth(uint8_t authMode, uint8_t BlockAddr, uint8_t *Sectorkey, uint8_t *serNum)
//{
//    uint8_t status;
//    uint recvBits;
//    uint8_t i;
//	uint8_t buff[12]; 

//	//Confirmation + Address + password + quick number
//    buff[0] = authMode;
//    buff[1] = BlockAddr;
//    for (i=0; i<6; i++)
//    {    
//		buff[i+2] = *(Sectorkey+i);   
//	}
//    for (i=0; i<4; i++)
//    {    
//		buff[i+8] = *(serNum+i);   
//	}
//    status = MFRC522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);

//    if ((status != MI_OK) || (!(Read_MFRC522(Status2Reg) & 0x08)))
//    {   
//		status = MI_ERR;   
//	}
//    
//    return status;
//}


///*
// * Function name: MFRC522_Read
// * Function: Doc with data
// * Input: blockAddr - Address location; recvData - Retrieve document output
// * Output: MI_OK if successful
// */
//uint8_t MFRC522_Read(uint8_t blockAddr, uint8_t *recvData)
//{
//    uint8_t status;
//    uint unLen;

//    recvData[0] = PICC_READ;
//    recvData[1] = blockAddr;
//    CalulateCRC(recvData,2, &recvData[2]);
//    status = MFRC522_ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

//    if ((status != MI_OK) || (unLen != 0x90))
//    {
//        status = MI_ERR;
//    }
//    
//    return status;
//}


///*
// * Function name: MFRC522_Write
// * Function: wait repeats data
// * Input: blockAddr - locations; writeData - write data
// * Output: MI_OK if successful
// */
//uint8_t MFRC522_Write(uint8_t blockAddr, uint8_t *writeData)
//{
//    uint8_t status;
//    uint recvBits;
//    uint8_t i;
//	uint8_t buff[18]; 
//    
//    buff[0] = PICC_WRITE;
//    buff[1] = blockAddr;
//    CalulateCRC(buff, 2, &buff[2]);
//    status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

//    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
//    {   
//		status = MI_ERR;   
//	}
//        
//    if (status == MI_OK)
//    {
//        for (i=0; i<16; i++)		//16 FIFO bytes recorded
//        {    
//        	buff[i] = *(writeData+i);   
//        }
//        CalulateCRC(buff, 16, &buff[16]);
//        status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);
//        
//		if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
//        {   
//			status = MI_ERR;   
//		}
//    }
//    
//    return status;
//}


///*
// * Function name: MFRC522_Halt
// * Function: Dua the vao ngu dong
// * Input: NO.
// * Output: NO.
// */
//void MFRC522_Halt(void)
//{
//	uint unLen;
//	uint8_t buff[4]; 

//	buff[0] = PICC_HALT;
//	buff[1] = 0;
//	CalulateCRC(buff, 2, &buff[2]);
// 
//	MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
//}

///*
// * Function name: MFRC522_StopCrypto1
// * Function: Stop active RFID card
// * Input: NO.
// * Output: NO.
// */
//void MFRC522_StopCrypto1(void) {
//	// Clear MFCrypto1On bit
//	ClearBitMask(Status2Reg, 0x08); // Status2Reg[7..0] bits are: TempSensClear I2CForceHS reserved reserved   MFCrypto1On ModemState[2:0]
//} // End PCD_StopCrypto1()












#include "stm32f1_rc522.h"

/*
 * Ten ham:Write_MFRC5200
 * Chuc nang: Viet 1 byte du lieu vao thanh ghi MFRC522
 * Input:addr-> DIa chi ghi, val-> Gia tri de ghi
 * Tra ve: Khong
 */
uint8_t RC522_SPI_Transfer(uint8_t data)
{
	while(SPI_I2S_GetFlagStatus(MFRC522_SPI, SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(MFRC522_SPI,data);

	while(SPI_I2S_GetFlagStatus(MFRC522_SPI, SPI_I2S_FLAG_RXNE)==RESET);
	return SPI_I2S_ReceiveData(MFRC522_SPI);
}

/*
 * Ten ham:Write_MFRC5200
 * Chuc nang: Viet 1 byte du lieu vao thanh ghi MFRC522
 * Input:addr-> DIa chi ghi, val-> Gia tri de ghi
 * Tra ve: Khong
 */
void Write_MFRC522(uchar addr, uchar val)
{
	/* CS LOW */
	GPIO_ResetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);

	//Dinh dang dia chi:0XXXXXX0
	RC522_SPI_Transfer((addr<<1)&0x7E);	
	RC522_SPI_Transfer(val);
	
	/* CS HIGH */
	GPIO_SetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);
}


/*
 * Ten ham:Read_MFRC522
 * Chuc nang:Doc 1 byte du lieu tu 1 thanh ghi MFRC522
 * Input:addr-> dia chi doc
 * Tra ve: Gia tri trong thanh ghi doc ve
 */
uchar Read_MFRC522(uchar addr)
{
	uchar val;

	/* CS LOW */
	GPIO_ResetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);

	//Dinh dang dia chi:1XXXXXX0
	RC522_SPI_Transfer(((addr<<1)&0x7E) | 0x80);	
	val = RC522_SPI_Transfer(0x00);
	
	/* CS HIGH */
	GPIO_SetBits(MFRC522_CS_GPIO, MFRC522_CS_PIN);
	
	return val;	
	
}


/*
 * Ten ham:SetBitMask
 * Chuc nang:Set bit trong mot thanh ghi MFRC522
 * Input:reg--Thanh ghi cai dat; mask--gia tri set
 * Tra ve: Khong
 */
void SetBitMask(uchar reg, uchar mask)  
{
    uchar tmp;
    tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp | mask);  // set bit mask
}


/*
 * Ten ham:ClearBitMask
 * Chuc nang:Reset bit trong thanh ghi MFRC522
 * Input:reg--Dia chi thanh ghi; mask--Gia tri bit can clear
 * Tra ve: Khong
 */
void ClearBitMask(uchar reg, uchar mask)  
{
    uchar tmp;
    tmp = Read_MFRC522(reg);
    Write_MFRC522(reg, tmp & (~mask));  // clear bit mask
} 


/*
 * Ten Ham:AntennaOn
 * Chuc Nang:Mo anten, nen co it nhat 1 ms
 * Input: khong
 * Tra ve: khong
 */
void AntennaOn(void)
{
	uchar temp;

	temp = Read_MFRC522(TxControlReg);
//	if (!(temp & 0x03))
//	{
//		SetBitMask(TxControlReg, 0x03);
//	}
	SetBitMask(TxControlReg, 0x03);
}


/*
 * Ten ham:AntennaOff
 * chuc nang:Dong Anten, nen co it nhat 1 ms
 * Input:khong
 * Tra ve: khong
 */
void AntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}


/*
 * Ten ham:ResetMFRC522
 * Chuc nang:Khoi dong lai RC522
 * Input: Khong
 * Return: Khong
 */
void MFRC522_Reset(void)
{
    Write_MFRC522(CommandReg, PCD_RESETPHASE);
}

/*
 * Ten ham:MFRC522_SPI_Init
 * Chuc nang:Khoi tao SPI
 * Input: Khong
 * Tra va: Khong
 */
void MFRC522_SPI_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	SPI_InitTypeDef SPI_InitStruct;
	
	RCC_APB2PeriphClockCmd(MFRC522_SPI_GPIO_RCC | RCC_APB2Periph_AFIO,ENABLE);		// Enable clock GPIO
	
	if(MFRC522_SPI==SPI1)
	{
		RCC_APB2PeriphClockCmd(MFRC522_SPI_RCC,ENABLE);																// Enable clock SPI1
	}
	else
	{
		RCC_APB1PeriphClockCmd(MFRC522_SPI_RCC,ENABLE);																// Enable clock SPI2 or SPI3
	}
	
	GPIO_InitStruct.GPIO_Pin = MFRC522_SCK_PIN | MFRC522_MISO_PIN | MFRC522_MOSI_PIN;	// SCK, MISO, MOSI
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(MFRC522_SPI_GPIO, &GPIO_InitStruct);																	// init GPIO SPI

	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8;
	SPI_InitStruct.SPI_Direction= SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStruct.SPI_CRCPolynomial = 7;
	SPI_Init(MFRC522_SPI, &SPI_InitStruct);

	SPI_Cmd(MFRC522_SPI, ENABLE);
}

/*
 * Ten ham:InitMFRC522
 * Chuc nang:Khoi tao RC522
 * Input: Khong
 * Tra va: Khong
 */
void MFRC522_Init(void)
{
	/* Khoi tao SPI */
	GPIO_InitTypeDef GPIO_InitStructure;
	/* GPIOD Periph clock enable */
  RCC_APB2PeriphClockCmd(MFRC522_CS_RCC | MFRC522_RST_RCC, ENABLE);

  /* Configure CS is output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = MFRC522_CS_PIN;				// Set digital pin 10 as OUTPUT to connect it to the RFID /ENABLE pin 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(MFRC522_CS_GPIO, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = MFRC522_RST_PIN;			// Set digital pin 10 , Not Reset and Power-down
	GPIO_Init(MFRC522_RST_GPIO, &GPIO_InitStructure);
	
	GPIO_SetBits(MFRC522_CS_GPIO,MFRC522_CS_PIN);						// Activate the RFID reader
	GPIO_SetBits(MFRC522_RST_GPIO,MFRC522_RST_PIN);					// not reset

		// spi config
	MFRC522_SPI_Init();
	
	MFRC522_Reset();
	 	
	//Timer: TPrescaler*TreloadVal/6.78MHz = 24ms
	Write_MFRC522(TModeReg, 0x8D);		//Tauto=1; f(Timer) = 6.78MHz/TPreScaler
	Write_MFRC522(TPrescalerReg, 0x3E);	//TModeReg[3..0] + TPrescalerReg
	Write_MFRC522(TReloadRegL, 30);           
	Write_MFRC522(TReloadRegH, 0);
	
	Write_MFRC522(TxAutoReg, 0x40);		//100%ASK
	Write_MFRC522(ModeReg, 0x3D);		//CRC Gia tri ban dau 0x6363	???

	//ClearBitMask(Status2Reg, 0x08);		//MFCrypto1On=0
	//Write_MFRC522(RxSelReg, 0x86);		//RxWait = RxSelReg[5..0]
	//Write_MFRC522(RFCfgReg, 0x7F);   		//RxGain = 48dB

	AntennaOn();		//Mo Anten
}

/*
 * Ten ham:MFRC522_ToCard
 * Chuc nang:truyen thong giua RC522 va the ISO14443
 * Input:command--lenh gui den MF522,
 *			 sendData--Du lieu gui den the bang MFRC522, 
 *			 sendLen--Chieu dai du lieu gui 
 *			 backData--Du lieu nhan duoc tro lai
 *			 backLen--Tra ve do dai bit cua du lieu
 * Tra ve: MI_OK neu thanh cong
 */
uchar MFRC522_ToCard(uchar command, uchar *sendData, uchar sendLen, uchar *backData, uint *backLen)
{
    uchar status = MI_ERR;
    uchar irqEn = 0x00;
    uchar waitIRq = 0x00;
    uchar lastBits;
    uchar n;
    uint i;

    switch (command)
    {
        case PCD_AUTHENT:		//Xac nhan the gan
		{
			irqEn = 0x12;
			waitIRq = 0x10;
			break;
		}
		case PCD_TRANSCEIVE:	// Gui du lieu FIFO
		{
			irqEn = 0x77;
			waitIRq = 0x30;
			break;
		}
		default:
			break;
    }
   
    Write_MFRC522(CommIEnReg, irqEn|0x80);	//Yeu cau ngat
    ClearBitMask(CommIrqReg, 0x80);			//Clear tat ca cac bit yeu cau ngat
    SetBitMask(FIFOLevelReg, 0x80);			//FlushBuffer=1, Khoi tao FIFO
    
	Write_MFRC522(CommandReg, PCD_IDLE);	//NO action; Huy bo lenh hien hanh	???

	// Ghi du lieu vao FIFO
    for (i=0; i<sendLen; i++)
    {   
		Write_MFRC522(FIFODataReg, sendData[i]);    
	}

	//chay
	Write_MFRC522(CommandReg, command);
    if (command == PCD_TRANSCEIVE)
    {    
		SetBitMask(BitFramingReg, 0x80);		//StartSend=1,transmission of data starts  
	}   
    
	//Cho doi de nhan duoc du lieu day du
	i = 2000;	//i tuy thuoc tan so thach anh, thoi gian toi da cho the M1 la 25ms
    do 
    {
		//CommIrqReg[7..0]
		//Set1 TxIRq RxIRq IdleIRq HiAlerIRq LoAlertIRq ErrIRq TimerIRq
        n = Read_MFRC522(CommIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitIRq));

    ClearBitMask(BitFramingReg, 0x80);			//StartSend=0
	
    if (i != 0)
    {    
        if(!(Read_MFRC522(ErrorReg) & 0x1B))	//BufferOvfl Collerr CRCErr ProtecolErr
        {
            status = MI_OK;
            if (n & irqEn & 0x01)
            {   
				status = MI_NOTAGERR;			//??   
			}

            if (command == PCD_TRANSCEIVE)
            {
               	n = Read_MFRC522(FIFOLevelReg);
              	lastBits = Read_MFRC522(ControlReg) & 0x07;
                if (lastBits)
                {   
					*backLen = (n-1)*8 + lastBits;   
				}
                else
                {   
					*backLen = n*8;   
				}

                if (n == 0)
                {   
					n = 1;    
				}
                if (n > MAX_LEN)
                {   
					n = MAX_LEN;   
				}
				
				//Doc FIFO trong cac du lieu nhan duoc
                for (i=0; i<n; i++)
                {   
					backData[i] = Read_MFRC522(FIFODataReg);    
				}
            }
        }
        else
        {   
			status = MI_ERR;  
		}
        
    }
	
    //SetBitMask(ControlReg,0x80);           //timer stops
    //Write_MFRC522(CommandReg, PCD_IDLE); 

    return status;
}

/*
 * Ten ham:MFRC522_Request
 * Chuc nang:Phat hien the, doc loai the
 * Input:reqMode--Phat hien co the,
 *			 TagType--Loai the tra ve
 *			 	0x4400 = Mifare_UltraLight
 *				0x0400 = Mifare_One(S50)
 *				0x0200 = Mifare_One(S70)
 *				0x0800 = Mifare_Pro(X)
 *				0x4403 = Mifare_DESFire
 * Return: MI_OK neu thanh cong
 */
uchar MFRC522_Request(uchar reqMode, uchar *TagType)
{
	uchar status;  
	uint backBits;			//cac bit du lieu nhan duoc

	Write_MFRC522(BitFramingReg, 0x07);		//TxLastBists = BitFramingReg[2..0]	???
	
	TagType[0] = reqMode;
	status = MFRC522_ToCard(PCD_TRANSCEIVE, TagType, 1, TagType, &backBits);

	if ((status != MI_OK) || (backBits != 0x10))
	{    
		status = MI_ERR;
	}
   
	return status;
}


/*
 * Ten ham:MFRC522_Anticoll
 * Chuc nang:Phat hien chong va cham, chon the va doc so serial the
 * Input:serNum--Tra ve serial the 4 byte, byte 5 la ma checksum
 * Tra ve: MI_OK neu thanh cong
 */
uchar MFRC522_Anticoll(uchar *serNum)
{
    uchar status;
    uchar i;
	uchar serNumCheck=0;
    uint unLen;
    

    //ClearBitMask(Status2Reg, 0x08);		//TempSensclear
    //ClearBitMask(CollReg,0x80);			//ValuesAfterColl
	Write_MFRC522(BitFramingReg, 0x00);		//TxLastBists = BitFramingReg[2..0]
 
    serNum[0] = PICC_ANTICOLL;
    serNum[1] = 0x20;
    status = MFRC522_ToCard(PCD_TRANSCEIVE, serNum, 2, serNum, &unLen);

    if (status == MI_OK)
	{
		//Kiem tra so serial the
		for (i=0; i<4; i++)
		{   
		 	serNumCheck ^= serNum[i];
		}
		if (serNumCheck != serNum[i])
		{   
			status = MI_ERR;    
		}
    }

    //SetBitMask(CollReg, 0x80);		//ValuesAfterColl=1

    return status;
} 


/*
 * Ten Ham:CalulateCRC
 * Chuc nang:MFRC522 tinh toan RC522
 * Input:pIndata--Du lieu CRC vao can tinh toan,len--Chieu dai du lieu,pOutData--Ket qua tinh toan CRC
 * Tra ve: Khong
 */
void CalulateCRC(uchar *pIndata, uchar len, uchar *pOutData)
{
    uchar i, n;

    ClearBitMask(DivIrqReg, 0x04);			//CRCIrq = 0
    SetBitMask(FIFOLevelReg, 0x80);			//Con tro FIFO
    //Write_MFRC522(CommandReg, PCD_IDLE);

	//Ghi du lieu vao FIFO
    for (i=0; i<len; i++)
    {   
		Write_MFRC522(FIFODataReg, *(pIndata+i));   
	}
    Write_MFRC522(CommandReg, PCD_CALCCRC);

	// Cho cho viec tinh toan CRC hoan tat
    i = 0xFF;
    do 
    {
        n = Read_MFRC522(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));			//CRCIrq = 1

	//Doc ket qua tinh toan CRC
    pOutData[0] = Read_MFRC522(CRCResultRegL);
    pOutData[1] = Read_MFRC522(CRCResultRegM);
}


/*
 * Ten ham:MFRC522_SelectTag
 * Chuc nang:Lua chon the, doc dung luong bo nho the
 * Input:serNum--So serial the
 * Tra ve:Dung luong the tra ve thanh cong
 */
uchar MFRC522_SelectTag(uchar *serNum)
{
	uchar i;
	uchar status;
	uchar size;
	uint recvBits;
	uchar buffer[9]; 

	//ClearBitMask(Status2Reg, 0x08);			//MFCrypto1On=0

    buffer[0] = PICC_SElECTTAG;
    buffer[1] = 0x70;
    for (i=0; i<5; i++)
    {
    	buffer[i+2] = *(serNum+i);
    }
	CalulateCRC(buffer, 7, &buffer[7]);		//??
    status = MFRC522_ToCard(PCD_TRANSCEIVE, buffer, 9, buffer, &recvBits);
    
    if ((status == MI_OK) && (recvBits == 0x18))
    {   
		size = buffer[0]; 
	}
    else
    {   
		size = 0;    
	}

    return size;
}


/*
 * Ten Ham:MFRC522_Auth
 * Chuc nang:Xac nhan mat khau the
 * Input:authMode--Che do xac thuc mat khau
                 0x60 = Xac nhan phim A
                 0x61 = Xac nhan phim B
             BlockAddr--Cac khoi dia chi
             Sectorkey--Khu vuc mat khau
             serNum--So serial the, 4 byte
 * Tra ve:MI_OK neu thanh cong
 */
uchar MFRC522_Auth(uchar authMode, uchar BlockAddr, uchar *Sectorkey, uchar *serNum)
{
    uchar status;
    uint recvBits;
    uchar i;
	uchar buff[12]; 

	//Xac nhan lenh + Khoi dia chi + mat khau + so nhanh
    buff[0] = authMode;
    buff[1] = BlockAddr;
    for (i=0; i<6; i++)
    {    
		buff[i+2] = *(Sectorkey+i);   
	}
    for (i=0; i<4; i++)
    {    
		buff[i+8] = *(serNum+i);   
	}
    status = MFRC522_ToCard(PCD_AUTHENT, buff, 12, buff, &recvBits);

    if ((status != MI_OK) || (!(Read_MFRC522(Status2Reg) & 0x08)))
    {   
		status = MI_ERR;   
	}
    
    return status;
}


/*
 * Ten ham:MFRC522_Read
 * Chuc nang: Doc khoi du lieu
 * Input:blockAddr--Cac khoi dia chi;recvData--Khoi du lieu doc ra
 * Tra ve: MI_OK neu thanh cong
 */
uchar MFRC522_Read(uchar blockAddr, uchar *recvData)
{
    uchar status;
    uint unLen;

    recvData[0] = PICC_READ;
    recvData[1] = blockAddr;
    CalulateCRC(recvData,2, &recvData[2]);
    status = MFRC522_ToCard(PCD_TRANSCEIVE, recvData, 4, recvData, &unLen);

    if ((status != MI_OK) || (unLen != 0x90))
    {
        status = MI_ERR;
    }
    
    return status;
}


/*
 * Ten ham:MFRC522_Write
 * Chuc nang:Viet khoi du lieu
 * Input:blockAddr--cac khoi dia chi;writeData--du lieu ghi
 * Tra ve: MI_OK neu thanh cong
 */
uchar MFRC522_Write(uchar blockAddr, uchar *writeData)
{
    uchar status;
    uint recvBits;
    uchar i;
	uchar buff[18]; 
    
    buff[0] = PICC_WRITE;
    buff[1] = blockAddr;
    CalulateCRC(buff, 2, &buff[2]);
    status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff, &recvBits);

    if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
    {   
		status = MI_ERR;   
	}
        
    if (status == MI_OK)
    {
        for (i=0; i<16; i++)		//16 byte FIFO ghi du lieu vao
        {    
        	buff[i] = *(writeData+i);   
        }
        CalulateCRC(buff, 16, &buff[16]);
        status = MFRC522_ToCard(PCD_TRANSCEIVE, buff, 18, buff, &recvBits);
        
		if ((status != MI_OK) || (recvBits != 4) || ((buff[0] & 0x0F) != 0x0A))
        {   
			status = MI_ERR;   
		}
    }
    
    return status;
}


/*
 * Ten ham:MFRC522_Halt
 * CHuc nang: Dua the vao ngu dong
 * Input: Khong
 * Tra ve: Khong
 */
void MFRC522_Halt(void)
{
	uint unLen;
	uchar buff[4]; 

	buff[0] = PICC_HALT;
	buff[1] = 0;
	CalulateCRC(buff, 2, &buff[2]);
 
	MFRC522_ToCard(PCD_TRANSCEIVE, buff, 4, buff,&unLen);
}
