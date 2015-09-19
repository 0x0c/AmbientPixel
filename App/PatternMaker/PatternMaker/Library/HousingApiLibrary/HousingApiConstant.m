//
//  HousingApiConstant.m
//  HousingApiLibrary
//
//  Created by Daiwa House Industry Co., Ltd. on 2015/02/05.
//  Copyright (c) 2015 Daiwa House Industry Co., Ltd. All rights reserved.
//

#import "HousingApiConstant.h"

//Rest Command
NSString* const kLocalCommandRestGet = @"/smart/rest/request?deviceid=%@&type=get&key=%@";
NSString* const kLocalCommandRestSet = @"/smart/rest/request?deviceid=%@&type=set&key=%@&value=%@";
NSString* const kLocalCommandRestCodeGet = @"/smart/rest/request?deviceid=%@&type=codeget&key=%@";
NSString* const kLocalCommandRestCodeSet = @"/smart/rest/request?deviceid=%@&type=codeset&key=%@&value=%@";

//Airsuite Command
NSString* const kLocalCommandAirsuiteGetInfo = @"/smart/airsuite?type=deviceget&key=airconinfo";
NSString* const kLocalCommandAirsuiteSetInfo = @"/smart/airsuite?type=deviceset&deviceid=%@&kind=%@";
NSString* const kLocalCommandAirsuiteSetHumidity = @"/smart/airsuite?type=deviceset&deviceid=%@&humidity=%@";
NSString* const kLocalCommandAirsuiteSetPlace = @"/smart/airsuite?type=deviceset&deviceid=%@&place=%@";
NSString* const kLocalCommandAirsuiteGet = @"/smart/airsuite?type=%@&key=%@";
NSString* const kLocalCommandAirsuiteSet = @"/smart/airsuite?type=%@&key=%@&value=%@";

//History Command
NSString* const kLocalCommandHistoryGet = @"/smart/history?type=get&key=%@&target=%@";

NSString* const kLocalCommandDelimiter = @",";

//Device ID
NSString* const kLocalDeviceIdMainBoard = @"lite.boardMeter_1_1";
NSString* const kLocalDeviceIdSolarBoard = @"lite.boardMeter_1_3";
NSString* const kLocalDeviceIdEneBoard = @"lite.boardMeter_1_4";
NSString* const kLocalDeviceIdBattery = @"lite.battery_1_1";
NSString* const kLocalDeviceIdSwitch = @"lite.switch_%d_1";
NSString* const kLocalDeviceIdAircon = @"lite.aircon_1_1";
NSString* const kLocalDeviceIdLed = @"lite.ledLight_1_1";
NSString* const kLocalDeviceIdSmartMeter = @"lite_smartMeter";
NSString* const kLocalDeviceIdWaterHeater = @"lite.electric_water_heater";
NSString* const kLocalDeviceIdEV = @"lite.EV_charger_discharger";


//key [共通]
NSString* const kLocalKeyInstantPower = @"instantPower";
NSString* const kLocalKeyOperationStatus = @"operationStatus";
NSString* const kLocalKeyCurrentMode = @"currentmode";
NSString* const KLocalKeyConnectedDevice = @"connectedDevice";

//valule [共通]
NSString* const kLocalValueOn = @"ON";
NSString* const kLocalValueOff = @"OFF";


//[boardMeter]
//key
NSString* const kLocalKeyBranchCircuit = @"branchCircuit_%d";
NSString* const kLocalKeyBranchCircuitVoltage = @"branchCircuitVoltage_%d";


//[Battery]
//key
NSString* const kLocalKeyBatteryInstantChargeAndDisCharge = @"instantChargeAndDisCharge";
NSString* const kLocalKeyBatterySoc = @"soc";
NSString* const kLocalKeyBatteryState = @"state";
//NSString* const kLocalKeyBatteryAlarm = @"alarm";


//[Aircon]
//key
NSString* const kLocalKeyAirconTemperature = @"temperature";
NSString* const kLocalKeyAirconHumidity = @"humidity";
NSString* const kLocalKeyAirconSwing = @"swing";
NSString* const kLocalKeyAirconAirFlow = @"airFlow";
NSString* const kLocalKeyAirconPurifier = @"purifier";
NSString* const kLocalKeyAirconPowersave = @"powersave";
NSString* const kLocalKeyAirconInTemperature = @"indoorTemperature";
NSString* const kLocalKeyAirconOutTemperature = @"outdoorTemperature";
//NSString* const kLocalKeyAirconCool = @"coolingOriginal%d";
//NSString* const kLocalKeyAirconSaveRunning = @"saveRunning";
//value
//currentMode
NSString* const kLocalValAirconCurModeAuto = @"auto";
NSString* const kLocalValAirconCurModeCool = @"cooling";
NSString* const kLocalValAirconCurModeHeat = @"heating";
NSString* const kLocalValAirconCurModeHumidity = @"dehumidification";
NSString* const kLocalValAirconCurModeVentilation = @"ventilation";
//airFlow
NSString* const kLocalValAirconAirFlow0 = @"0";
NSString* const kLocalValAirconAirFlow1 = @"1";
NSString* const kLocalValAirconAirFlow2 = @"2";
NSString* const kLocalValAirconAirFlow3 = @"3";
NSString* const kLocalValAirconAirFlow4 = @"4";
NSString* const kLocalValAirconAirFlow5 = @"5";
NSString* const kLocalValAirconAirFlow6 = @"6";
//swing
NSString* const kLocalValAirconSwingVertical = @"vertical";
NSString* const kLocalValAirconSwingHorizontal = @"horizontal";
NSString* const kLocalValAirconSwingVandH = @"verticalAndHorizontal";


//[LED]
//key
NSString* const kLocalKeyLedCodegetState = @"80";
//value
NSString* const kLocalValLedCodegetStateOn = @"30";
NSString* const kLocalValLedCodegetStateOff = @"31";


//[瞬間式給湯器]
//key
NSString* const kLocalKeyWaterHeaterStatus = @"heatingStatus";
NSString* const kLocalKeyWaterHeaterBathStatus = @"bathwaterHeatingStatus";
NSString* const kLocalKeyWaterHeaterAutoMode = @"autoMode";
NSString* const kLocalKeyWaterHeaterHeatSetting = @"heatingSetting";
NSString* const kLocalKeyWaterHeaterReHeat = @"daytimeReheating";
NSString* const kLocalKeyWaterHeaterHotStatus = @"hotWaterSupplyStatus";
NSString* const kLocalKeyWaterHeaterHeating = @"heating";
//value
NSString* const kLocalValWaterHeaterHeatSettingAuto = @"auto";
NSString* const kLocalValWaterHeaterHeatSettingManual = @"manual";
NSString* const kLocalValWaterHeaterHeatSettingStop = @"stop";
NSString* const kLocalValWaterHeaterReHeatPermit = @"permitted";
NSString* const kLocalValWaterHeaterReHeatNoPermit = @"not_permitted";
NSString* const kLocalValWaterHeaterHeatStart = @"start";
NSString* const kLocalValWaterHeaterHeatStop = @"stop";


//EV
//key
NSString* const kLocalKeyEVDischargeCapacity = @"dischargeableCapacity";
NSString* const kLocalKeyEVRemainDischargeCapacity = @"remainingDischargeableCapacity";
NSString* const kLocalKeyEVRateChargeCapacity = @"ratedChargeCapacity";
NSString* const kLocalKeyEVRateDisChargeCapacity = @"ratedDischargeCapacity";
NSString* const kLocalKeyEVOperationMode = @"operationMode";
//value
NSString* const kLocalValEVOperationModeRapidCharge = @"rapidCharging";
NSString* const kLocalValEVOperationModeCharge = @"charging";
NSString* const kLocalValEVOperationModeDisCharge = @"discharging";
NSString* const kLocalValEVOperationModeStandby = @"standby";


//[history]
//key
NSString* const kLocalKeyHistorySolarPower = @"solarPower";
NSString* const kLocalKeyHistorySolarPowerSell = @"solarPowerSelling";
NSString* const kLocalKeyHistoryBatteryPowerCharge = @"batteryPowerCharge";
NSString* const kLocalKeyHistoryBatteryPowerDischarge = @"batteryPowerDischarge";
NSString* const kLocalKeyHistoryFuelCellPower = @"fuelCellPower";
NSString* const kLocalKeyHistoryMainPower = @"mainPower";
NSString* const kLocalKeyHistoryBranch = @"branchCircuitPower_%d";
NSString* const kLocalKeyHistoryGas = @"gasConsumption";
NSString* const kLocalKeyHistoryWater = @"waterConsumption";
NSString* const kLocalKeyHistorySmartMeter = @"smartMeter";
NSString* const kLocalKeyHistorySmartMeterSell = @"smartMeterSelling";



//element
NSString* const kLocalElementResultset = @"resultset";
NSString* const kLocalElementResult = @"result";
NSString* const kLocalElementMessage = @"message";
NSString* const kLocalElementSize = @"size";
NSString* const kLocalElementDataSet = @"dataset";
NSString* const kLocalElementData = @"data";
NSString* const kLocalElementKey = @"key";
NSString* const kLocalElementValue = @"value";
NSString* const kLocalElementErrorCode = @"errorCode";



@implementation HousingApiConstant


@end
