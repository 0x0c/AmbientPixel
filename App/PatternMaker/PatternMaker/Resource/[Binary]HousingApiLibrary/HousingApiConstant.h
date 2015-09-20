//
//  HousingConstant.h
//  HousingApiLibrary
//
//  Created by Daiwa House Industry Co., Ltd. on 2015/02/05.
//  Copyright (c) 2015 Daiwa House Industry Co., Ltd. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface HousingApiConstant : NSObject

//Rest Command
extern NSString* const kLocalCommandRestGet;
extern NSString* const kLocalCommandRestSet;
extern NSString* const kLocalCommandRestCodeGet;
extern NSString* const kLocalCommandRestCodeSet;

//Airsuite Command
extern NSString* const kLocalCommandAirsuiteGetInfo;
extern NSString* const kLocalCommandAirsuiteSetInfo;
extern NSString* const kLocalCommandAirsuiteSetHumidity;
extern NSString* const kLocalCommandAirsuiteSetPlace;
extern NSString* const kLocalCommandAirsuiteGet;
extern NSString* const kLocalCommandAirsuiteSet;

//History Command
extern NSString* const kLocalCommandHistoryGet;

extern NSString* const kLocalCommandDelimiter;

//Device ID
extern NSString* const kLocalDeviceIdMainBoard;
extern NSString* const kLocalDeviceIdSolarBoard;
extern NSString* const kLocalDeviceIdEneBoard;
extern NSString* const kLocalDeviceIdBattery;
extern NSString* const kLocalDeviceIdSwitch;
extern NSString* const kLocalDeviceIdAircon;
extern NSString* const kLocalDeviceIdLed;
extern NSString* const kLocalDeviceIdSmartMeter;
extern NSString* const kLocalDeviceIdWaterHeater;
extern NSString* const kLocalDeviceIdEV;


//key [共通]
extern NSString* const kLocalKeyInstantPower;
extern NSString* const kLocalKeyOperationStatus;
extern NSString* const kLocalKeyCurrentMode;
extern NSString* const KLocalKeyConnectedDevice;

//valule [共通]
extern NSString* const kLocalValueOn;
extern NSString* const kLocalValueOff;


//[boardMeter]
//key
extern NSString* const kLocalKeyBranchCircuit;
extern NSString* const kLocalKeyBranchCircuitVoltage;


//[Battery]
//key
extern NSString* const kLocalKeyBatteryAlarm;
extern NSString* const kLocalKeyBatteryInstantChargeAndDisCharge;
extern NSString* const kLocalKeyBatterySoc;
extern NSString* const kLocalKeyBatteryState;


//[Aircon]
//key
extern NSString* const kLocalKeyAirconTemperature;
extern NSString* const kLocalKeyAirconHumidity;
extern NSString* const kLocalKeyAirconSwing;
extern NSString* const kLocalKeyAirconAirFlow;
extern NSString* const kLocalKeyAirconPurifier;
extern NSString* const kLocalKeyAirconPowersave;
extern NSString* const kLocalKeyAirconInTemperature;
extern NSString* const kLocalKeyAirconOutTemperature;

extern NSString* const kLocalKeyAirconCool;
extern NSString* const kLocalKeyAirconSaveRunning;
//value
//currentMode
extern NSString* const kLocalValAirconCurModeAuto;
extern NSString* const kLocalValAirconCurModeCool;
extern NSString* const kLocalValAirconCurModeHeat;
extern NSString* const kLocalValAirconCurModeHumidity;
extern NSString* const kLocalValAirconCurModeVentilation;
//airFlow
extern NSString* const kLocalValAirconAirFlow0;
extern NSString* const kLocalValAirconAirFlow1;
extern NSString* const kLocalValAirconAirFlow2;
extern NSString* const kLocalValAirconAirFlow3;
extern NSString* const kLocalValAirconAirFlow4;
extern NSString* const kLocalValAirconAirFlow5;
extern NSString* const kLocalValAirconAirFlow6;
//swing
extern NSString* const kLocalValAirconSwingVertical;
extern NSString* const kLocalValAirconSwingHorizontal;
extern NSString* const kLocalValAirconSwingVandH;


//[LED]
//key
extern NSString* const kLocalKeyLedCodegetState;
//value
extern NSString* const kLocalValLedCodegetStateOn;
extern NSString* const kLocalValLedCodegetStateOff;


//[瞬間式給湯器]
//key
extern NSString* const kLocalKeyWaterHeaterStatus;
extern NSString* const kLocalKeyWaterHeaterBathStatus;
extern NSString* const kLocalKeyWaterHeaterAutoMode;
extern NSString* const kLocalKeyWaterHeaterHeatSetting;
extern NSString* const kLocalKeyWaterHeaterHeating;
extern NSString* const kLocalKeyWaterHeaterReHeat;
extern NSString* const kLocalKeyWaterHeaterHotStatus;
//value
extern NSString* const kLocalValWaterHeaterHeatSettingAuto;
extern NSString* const kLocalValWaterHeaterHeatSettingManual;
extern NSString* const kLocalValWaterHeaterHeatSettingStop;
extern NSString* const kLocalValWaterHeaterReHeatPermit;
extern NSString* const kLocalValWaterHeaterReHeatNoPermit;
extern NSString* const kLocalValWaterHeaterHeatStart;
extern NSString* const kLocalValWaterHeaterHeatStop;


//EV
//key
extern NSString* const kLocalKeyEVDischargeCapacity;
extern NSString* const kLocalKeyEVRemainDischargeCapacity;
extern NSString* const kLocalKeyEVRateChargeCapacity;
extern NSString* const kLocalKeyEVRateDisChargeCapacity;
extern NSString* const kLocalKeyEVOperationMode;
//value
extern NSString* const kLocalValEVOperationModeRapidCharge;
extern NSString* const kLocalValEVOperationModeCharge;
extern NSString* const kLocalValEVOperationModeDisCharge;
extern NSString* const kLocalValEVOperationModeStandby;


//[history]
//key
extern NSString* const kLocalKeyHistorySolarPower;
extern NSString* const kLocalKeyHistorySolarPowerSell;
extern NSString* const kLocalKeyHistoryBatteryPowerCharge;
extern NSString* const kLocalKeyHistoryBatteryPowerDischarge;
extern NSString* const kLocalKeyHistoryFuelCellPower;
extern NSString* const kLocalKeyHistoryMainPower;
extern NSString* const kLocalKeyHistoryBranch;
extern NSString* const kLocalKeyHistoryGas;
extern NSString* const kLocalKeyHistoryWater;
extern NSString* const kLocalKeyHistorySmartMeter;
extern NSString* const kLocalKeyHistorySmartMeterSell;



//element
extern NSString* const kLocalElementResultset;
extern NSString* const kLocalElementResult;
extern NSString* const kLocalElementMessage;
extern NSString* const kLocalElementSize;
extern NSString* const kLocalElementDataSet;
extern NSString* const kLocalElementData;
extern NSString* const kLocalElementKey;
extern NSString* const kLocalElementValue;
extern NSString* const kLocalElementErrorCode;


@end

