#include "Pelco_D.h"
#include "Pelco_P.h"

#ifndef STAGELENS_H
#define STAGELENS_H

class CStageLens
{
	public:
		CStageLens() { Protocol_ID = PELCO_D; };
		~CStageLens() {};
	public:
		enum PROTOCOL {
				PELCO_D,		// Pelco_D, 
				PELCO_D_1,		// Pelco_D_1,
				PELCO_P,		// Pelco_P, 
				PELCO_P_1,		// Pelco_P_1, 
				PELCO_P_2,		// Pelco_P_2,
				XENON,			// Xenon, 
				PICO2000,		// Pico2000,
				PICASO,			// Picaso,
				KODICOM_RX,		// Kodicom_RX, 
				KODICOM_KRE,	// Kodicom_KRE,
				KALATAL,		// Kalatal,
				VICON,			// Vicon,
				SCANDOME_II,	// ScanDome_II
		};
	enum PresetAction {PresetAction_Set,PresetAction_Clear,PresetAction_Goto};
	enum PatternAction {PatternAction_Start,PatternAction_Stop,PatternAction_Run};

	public:
			void SetSpeed(int nSpeed = 0x17){m_nSpeed = nSpeed;}
			void SetProtocol(PROTOCOL Protocol);
			void Up(UINT deviceAddress);
			void TopRight(UINT deviceAddress);
			void Right(UINT deviceAddress);
			void BottomRight(UINT deviceAddress);
			void Down(UINT deviceAddress);
			void BottomLeft(UINT deviceAddress);
			void Left(UINT deviceAddress);
			void TopLeft(UINT deviceAddress);
			void AutoScan(UINT deviceAddress);
			void ManualScan(UINT deviceAddress);
			void FocusPlus(UINT deviceAddress);
			void FocusMinus(UINT deviceAddress);
			void ZoomPlus(UINT deviceAddress);
			void ZoomMinus(UINT deviceAddress);
			void IrisPlus(UINT deviceAddress);
			void IrisMinus(UINT deviceAddress);
			void SearchLightON(UINT deviceAddress);
			void SearchLightOFF(UINT deviceAddress);
			void RainBrushON(UINT deviceAddress);
			void RainBrushOFF(UINT deviceAddress);
			void Noop(UINT deviceAddress);
			void PreSet(UINT deviceAddress, BYTE preset, PresetAction action);
			void Pattern(UINT deviceAddress,PatternAction action);
	private:
			void UnPackMessage(void);
	private:
			PROTOCOL	Protocol_ID;
			
			Pelco_D_Protocol::CPelco_D	Pelco_D;
			Pelco_P_Protocol::CPelco_P	Pelco_P;
//			BYTE		*SendMessagePtr;
	public:
			int			 m_nSpeed;//×ªËÙ
			BYTE		 *Message;
			UINT		 Len;
};

#endif