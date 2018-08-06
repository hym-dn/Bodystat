#include<Windows.h>
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary> <para> Bodystat SDK </para>		   
///			  <para> (C) 2010-2015 Bodystat (Isle of Man) Ltd. All rights reserved. </para>  
///			  <para> Use subject to license. </para>
///	<para></para>		  
///			  <para> Web: http://www.bodystat.com	</para>
///			  <para> Email: info@bodystat.com	</para>
///			  <para> Tel: +44 (0)1624 629 571	</para>
///			  <para> Fax: +44 (0)1624 611 544	</para>
///	<para></para>
///			  <para> Version	</para>
/// 		  <para> 1.39 (31/Aug/2015)	</para>
/// 		  <para> 	  Improved MST Bluetooth capabilities for more optimised download. </para>
/// 		  <para> 1.38 (12/Aug/2015)	</para>
/// 		  <para> 	  Improved com port installation timeout detection method. </para>
/// 		  <para> 	  Fixed communication timeout with MST devices over Bluetooth. </para>
/// 		  <para> 1.37 (20/July/2015)	</para>
/// 		  <para> 	  Automatic pairing of QST/MST models is now supported. </para>
/// 		  <para> 	  Added C# sample for Bluetooth communication with MST/QST models. </para>
/// 		  <para> 1.36 (09/May/2014)	</para>
/// 		  <para> 	  Selected download is now passed through to the results form in the C# sample.	</para>
///			  <para> 	  Fixed error in VB.Net wrapper (preventing download working) in the VB.Net sample.	</para>
/// 		  <para> 	  Fixed some missing normals for MST device.	</para>
///			  <para> 1.35 (10/Mar/2014)	</para>
///			  <para> 	  Added Cole methods for ECW/ICW calculations used in the MST device.	</para>
///			  <para> 	  Fixed a memory pointer issue for the detected bodystat device info structure.	</para>
///			  <para> 1.34 (12/Nov/2013)	</para>
///			  <para> 	  Exposed Bluetooth API search timeout values to the SDK	</para>
///			  <para> 1.33 (28/Sep/2012)	</para>
///			  <para> 	  Removed overly aggressive constraints on measurement parameters in CalculateResults and CalculateNormals()	</para>
///			  <para> 	  Added ECW and ICW to MDD results.	</para>
///			  <para> 	  Updated MFC/VB/C# samples to support ECW and ICW for MDD results.	</para>
///			  <para> 	  Renamed Illness Maker(TM) to Prediction Marker(TM) - naming/labeling change only, code left unchanged to avoid breaking change.	</para>
///			  <para> 1.32 (08/Aug/2011)	</para>
///			  <para> 	  Corrected a bug in which GetBodystatDevice could erroneously return success with an invalid device even though no device was found  	</para>
///			  <para> 	  Corrected message box title when pairing new devices  	</para>
///			  <para> 	  Updated C# wrapper with get/set accessors for databinding [Breaking Change: Minor refactoring will be required to accommodate new accessor names] 	</para>
///			  <para> 	  Updated C# wrapper with additional wrappers for calls with StringBuilder parameters (now callable directly with string parameters) 	</para>
///			  <para> 	  Updated C# wrapper to force imports as Cdecl types 	</para>
///			  <para> 	  Fixed bug in C# wrapper causing invalid parameter error during download 	</para>
///			  <para> 	  Updated VB wrapper to force imports as Cdecl types 	</para>
///			  <para> 	  Updated C# WinForms sample to use new string wrappers 	</para>
///			  <para> 1.31 (26/Oct/2010)	</para>
///			  <para> 	  Added C# wrapper and C# WinForms sample 	</para>
///			  <para> 	  Added initial support for Equistat devices 	</para>
///			  <para> 1.30 (29/Aug/2010)	</para>
///			  <para> 	  Added VB.Net wrapper and VB WinForms sample 	</para>
///			  <para> 1.29 (30/Jun/2010)	</para>
///			  <para> 	  Initial Release 	</para>
///	</summary>
////////////////////////////////////////////////////////////////////////////////////////////////////


// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the BODYSTATSDK_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// BODYSTATSDK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef BODYSTATSDK_EXPORTS
#define BODYSTATSDK_API extern "C" __declspec(dllexport)
#else
#define BODYSTATSDK_API extern "C" __declspec(dllimport)
#endif

#if _MSC_VER > 1000
#pragma once
#endif

#include <math.h>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/// <property name="title" value="Bodystat API" />
/// <property name="toctitle" value="Bodystat API" />
/// 
/// <summary>
/// This is the main namespace for the Bodystat API.
/// 
/// The entire functions within the Bodystat API are enclosed
/// within the 'Bodystat' namespace.
/// </summary>                                               
namespace Bodystat
{

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	BSGender: Enumerated values that represent a person's gender. </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
enum BSGender{ 			BSFemale = 0,			// Female
						BSMale = 1				// Male
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// <para> BSDeviceModel: Enumerated values that represent the various different models of the Bodystat
/// devices over the years. </para>
/// <para> Suffix: The suffix after the model indicates specific hardware variations regarding connectivity: </para>
/// 	<para> OPTO indicates model communicates via opto-isolated serial. </para>
///		<para> DIU indicates model communicates via a data interface unit (induction interface) </para>
/// 	<para> BT indicates model communicates via Bluetooth serial port. </para>
/// </summary>
///
/// <remarks>	Note that not all models are supported by this SDK. Some are listed for historic reference only. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
enum BSDeviceModel{		BSUnknown		= 0,		// Unknown model
						BS1500_OPTO		= 1,		// Bodystat 1500 with opto-isolated interface (legacy)
						BSMDD_OPTO	= 2,			// Bodystat MDD with opto-isolated interface (legacy)
						BS1500_DIU		= 3,		// Bodystat 1500 with data interface unit (legacy)
						BSMDD_DIU	= 4,			// Bodystat MDD with data interface unit (legacy)
						BSDualScan_OPTO	= 5,		// Bodystat DualScan with opto-isolated interface (legacy)
						BSDualScan_DIU	= 6,		// Bodystat DualScan with data interface unit (legacy)
						BSQuadScan_DIU	= 7,		// Bodystat QuadScan with data interface unit (legacy)
						BSMultiScan_DIU	= 8,		// Bodystat MultiScan with data interface unit (legacy)
						BS1500_BT		= 9,		// Bodystat 1500 with Bluetooth interface
						BSMDD_BT	= 10,			// Bodystat 1500MDD with Bluetooth interface
						BSQuadScan_BT	= 11,		// Bodystat QuadScan 4000 with Bluetooth interface
						BSEquistatPro_BT	= 12,	// Equistat Pro with Bluetooth interface (not supported by this SDK)
						BSEquistatLite_BT	= 13,	// Equistat Lite with Bluetooth interface (not supported by this SDK)
						BSQuadScanTouch		= 14,	// Bodystat QuadScan 4000 Touch with Wifi/Bluetooth interface
						BSMultiScanTouch		= 15	// Bodystat Multiscan with Wifi/Bluetooth interface
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// BSDeviceFamily: Enumerated values that group each device / model variant into a given product family.
/// Devices within a given product family share broad capabilities and features. For details regarding capabilities and features refer to the technical documentation for that product family (http://www.bodystat.com)
/// </summary>
///
/// <remarks>	Note that not all families are supported by this SDK. Some are listed for historic reference only. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
enum BSDeviceFamily{ 	BSUnknown_Family	= 0,		// Unknown product family
						BS1500_Family		=-1,		// Bodystat 1500 family
						BSMDD_Family	=-2,			// Bodystat MDD family
						BSDualScan_Family	=-3,		// Bodystat DualScan family (legacy)
						BSQuadScan_Family	=-4,		// Bodystat QuadScan family
						BSMultiScan_Family	=-5,		// Bodystat Multiscan family
						BSEquistatLite_Family	= -6,	// Equistat Lite family (not supported by this SDK)
						BSEquistatPro_Family	=-7		// Equistat Pro family (not supported by this SDK)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	BSError: Bodystat Error codes. A list of Bodystat specific error codes. </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
enum BSError{
		NoError					=	0,		// No error occurred
		InvalidDeviceModel		=	-1,		// Invalid model specified
		InvalidDeviceFamily		=	-2,		// Invalid family specified
		InvalidDeviceMode		=	-3,		// Invalid analysis mode
		InvalidGender			=	-4,		// Invalid BSGender specified
		InvalidAge				=	-5,		// Invalid age specified
		InvalidHeight			=	-6,		// Invalid height measurement specified
		InvalidWeight			=	-7,		// Invalid weight measurement specified
		InvalidActivity			=	-8,		// Invalid activity level specified
		InvalidWaist			=	-9,		// Invalid waist measurement specified
		InvalidHip				=	-10,	// Invalid hip measurement specified
		InvalidImpedanceZ5		=	-11,	// Invalid impedance measurement specified
		InvalidImpedanceZ50		=	-12,	// Invalid impedance measurement specified
		InvalidImpedanceZ100	=	-13,	// Invalid impedance measurement specified
		InvalidImpedanceZ200	=	-14,	// Invalid impedance measurement specified
		InvalidResistanceR50	=	-15,	// Invalid resistance measurement specified
		InvalidReactanceX50		=	-16,	// Invalid reactance measurement specified
		InvalidPhaseAnglePA50	=	-17,	// Invalid phase angle measurement specified
		InvalidParamSupplied	=	-18,	// Invalid parameter supplied
		ComErrorOpeningPort		=	-50,	// Error opening the com port
		ComErrorConfiguringPort	=	-51,	// Error configuring the com port parameters (required baud rate, buffers, stop bits, etc)
		ComErrorConnecting		=	-52,	// Error connecting to the device
		ComErrorUnsupportedCommand	=	-53,	// The requested command is not supported by the model being asked to perform it
		ComErrorProcessingCommand	=	-54,	// Error occurred whilst processing the requested command
		ComErrorReading			= -55,		// Error occurred whilst reading data from the com port
		ComErrorWriting			= -56,		// Error occurred whilst writing data to the com port
		ComErrorUserAborted		= -57		// The user aborted the process

};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// <para>BSAnalysisMode: Analysis results are available in several formats:</para>
/// 	<para><paramref>BSAnalysisModeBC</paramref> = Body composition analysis </para>
///		<para><paramref>BSAnalysisModeHN</paramref> = Hydration analysis </para>
///		<para><paramref>BSAnalysisModeBoth</paramref> = Combined body composition and hydration analysis (default) </para>
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
enum BSAnalysisMode
{
	BSAnalysisModeNone = 0,			// No analysis mode specified (raw data only)
	BSAnalysisModeBC = 1,			// Body composition enabled
	BSAnalysisModeHN = 2,			// Hydration enabled
	BSAnalysisModeBoth = 3			// Both body composition and hydration (default)
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
///	Represents one frequency measurement
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct ImpData
{
	public:

	float fFrequency;    /// Frequency in kHz
	float fImpedance;	 /// Absolute value of impedance measured at given frequency (result in ohms)
	float fPhaseAngle;	 /// Phase angle (result in degrees)

    /// <summary>
    /// Real part of impedance, also resistance
    /// Re Z = |Z|*cos(Phase)
    /// </summary>
	float ReZ() const
	{
		return fImpedance * cos(fPhaseAngle * M_PI / 180);
	}
    /// <summary>
    /// Imaginary part of impedance, also reactance
    /// Im Z = |Z|*sin(Phase)
    /// </summary>
	float ImZ() const
	{
		return fImpedance * sin(fPhaseAngle * M_PI / 180);
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// BSMeasurement: Measurement structure. Each test measurement recorded in the device is
/// stored one of these structures. Holds the user inputted information about the subject,
/// together with bio-impedance readings measured by the device (raw electrical readings only,
/// not full results). 
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct BSMeasurement
{
	BSDeviceModel 	iDeviceModel;	// Device model which performed the measurement
	ULONG	ulDeviceSerialNumber;	// Unique serial number of the device which performed the measurement
	__time64_t	tTestDate;	// Date & time the test measurement was performed (Windows 64-bit time structure) (MDD/Quad only)

	BSGender	iGender;	// Inputted gender of the subject
	int     iAge;       	// Inputted age of the subject (years)
	int     iHeight;     	// Inputted height of the subject (centimeters)
	float   fWeight;     	// Inputted weight of the subject (kilograms)
	int     iActivity;   	// Inputted physical activity level of the subject (range 1 to 5: 1=very low 2=low/medium 3=medium 4=medium/high 5=very high)
	int     iWaist;      	// Inputted waist size of the subject (centimeters)
	int     iHip;        	// Inputted hip size of the subject (centimeters)

	int     iZ_5kHz;     	// Impedance measured at 5 kHz (result in ohms) (MDD/Quad only) 
	int     iZ_50kHz;    	// Impedance measured at 50 kHz (result in ohms)
	int    	iZ_100kHz;		// Impedance measured at 100 kHz (result in ohms) (Quad only)
	int    	iZ_200kHz;		// Impedance measured at 200 kHz (result in ohms) (Quad only)
	int		iR_50kHz;		// Resistance measured at 50 kHz (result in ohms) (MDD/Quad only)
	float	fX_50kHz;		// Reactance measured at 50 kHz (result in ohms) (MDD/Quad only)
	float	fPA_50kHz;		// Phase angle measured at 50 kHz (result in degrees) (MDD/Quad only)

	// Multiscan only
	int		iFrequencies;	// number of frequencies used 11/50
	ImpData* pMultifreqData; // pointer to ImpData array
};


// Number of measurement records BSRawData structure should reserved space for (currently fixed)
const int BS_RAWDATA_ARRAYSIZE = 100;
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// BSRawData: Bodystat Raw Data structure. Used when downloading test measurements from the
/// device. Contains a fixed array of measurement records together with information about the
/// number of records occupied within the array and test record starting number. 
/// </summary>
/// <remarks>	Most models index 1000 records and store the last 100 at any given time. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct BSRawData
{
	int iRecordArraySize /*= BS_RAWDATA_ARRAYSIZE*/;	// Maximum number of records this structure has reserved space for (currently fixed)
	BSMeasurement record[BS_RAWDATA_ARRAYSIZE];		// Array of test measurement data

	int	iTotalNumRecs;				// Number of populated records in the array
	int	ulFirstTestNum;				// Test number of the first record stored in the array.
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// BSResults: Bodystat Results structure. Holds the calculated results for any given test
/// measurement. 
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct BSResults
{
	float	fFatPerc;		// Fat percentage
	float   fFatKg;      	// Fat (in kg)
	float   fLeanPerc;      // Lean percentage
	float   fLeanKg;        // Lean (in kg)
	float   fTotalWeight;   // Total Weight (in kg)
	float   fDryLW;         // Dry Lean Weight (in kg)
	float   fTBWPerc;       // Water percentage or Total Body Water percentage
	float   fTBW;           // Water (in litres) or Total Body Water (in litres) 

	float  	fECWPerc;		// Extra Cellular Water percentage	(MDD/Quad only)
	float  	fECW;			// Extra Cellular Water (in litres)	(MDD/Quad only)
	float  	fICWPerc;		// Intra Cellular Water percentage	(MDD/Quad only)
	float  	fICW;			// Intra Cellular Water (in litres)	(MDD/Quad only)
	float  	fBCM;			// Body cell mass 		(Quad only)
	float  	fThirdSpace;	// 3rd space water (in litres) (Quad only)
	float  	fNutrition;		// Nutrition index 		(Quad only)
	float  	fIllness;		// Prediction Marker (TM) - formerly known as Illness Marker (TM)	(Quad only)

	float   fBMR;           // Basal Metabolic Rate (in kcal)
	float   fBMRkg;         // Basal Metabolic Rate per kilogram in (kcal/kg)
	float   fEstAvg;        // Estimated Average Requirement (in kcal)
	float   fBMI;           // Body Mass Index
	float   fBFMI;			// Body Fat Mass Index 	(MDD/Quad only)
	float   fFFMI;      	// Fat Free Mass Index 	(MDD/Quad only)
	float   fWaistHip;   	// Waist/Hip ratio
	float   fWellness;   	// Wellness Marker (TM)	(MDD only)

	// Cole calculated values (Multiscan only)
	float fECW_Legacy;		// Legacy ECW calculation (QuanScan mode)
	float fTBW_Legacy;
	float fOHY;				// Over hydration
	float fSkMuscle;		// Skeletal muscle mass
	float fCm;				// Cell membrane capacitance
	float fRext;			// R extracellular
	float fRint;			// R intracellular
	float fFc;				// Characteristic frequency
	float fAlpha;			// Alpha angle
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// BSNormals: Bodystat Normals structure. Holds the normal values or normal ranges for any given
/// test measurement. 
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct BSNormals
{
	int		iFatPerc_L;				// Normal range for fat percentage - (low end)
	int		iFatPerc_H;				// Normal range for fat percentage - (high end)
	int	    iFatKg_L;				// Normal range for fat (in kg) - (low end)
	int  	iFatKg_H;				// Normal range for fat (in kg) - (high end)
	int  	iLeanPerc_L;			// Normal range for lean percentage - (low end)
	int 	iLeanPerc_H;			// Normal range for lean percentage - (high end)
	int     iLeanKg_L;				// Normal range for lean (in kg) - (low end)
	int 	iLeanKg_H;				// Normal range for lean (in kg) - (high end)
	int  	iTotalWeight_L;			// Normal range for Total Weight (in kg) - (low end)
	int 	iTotalWeight_H;			// Normal range for Total Weight (in kg) - (high end)
	int     iTotalWeightMethod;   	// Method used when calculating Total Weight normal range (0 = Composition Method, 1 = BMI Method) 
	int 	iTBWPerc_L;				// Normal range for Total Body Water percentage - (low end)
	int 	iTBWPerc_H;				// Normal range for Total Body Water percentage - (high end)
	int 	iTBW_L;					// Normal range for Total Body Water (in litres) - (low end)
	int 	iTBW_H;					// Normal range for Total Body Water (in litres) - (high end)
	int 	iECWPerc_Norm;			// Normal value for ECW Percentage (Quad only)
	int		iICWPerc_Norm;			// Normal value for ICW Percentage (Quad only)
	int    	iBFMI_L;				// Normal range for Body Fat Mass Index (MDD/Quad only) - (low end)
	int    	iBFMI_H;				// Normal range for Body Fat Mass Index (MDD/Quad only) - (high end)
	int    	iFFMI_L;				// Normal range for Fat Free Mass Index (MDD/Quad only) - (low end)
	int    	iFFMI_H;				// Normal range for Fat Free Mass Index (MDD/Quad only) - (high end)
	float  	fNutrition_Norm;		// Normal value for Nutrition Index (Quad only)
	float	fIllness_L;				// Normal range for Prediction Marker (TM) - formerly known as Illness Marker (TM) - (Quad only) - (low end)
	float	fIllness_H;				// Normal range for Prediction Marker (TM) - formerly known as Illness Marker (TM) - (Quad only) - (high end)
	int     iBMI_L;					// Normal range for Body Mass Index - (low end)
	int     iBMI_H;					// Normal range for Body Mass Index - (high end)
	float   fWaistHip_Norm;			// Normal value for Waist/Hip ratio
	float	fWellness_L;			// Normal range for Wellness Marker (TM) (MDD only) - (low end)
	float	fWellness_H;			// Normal range for Wellness Marker (TM) (MDD only) - (high end)

};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// ESMeasurement: Equistat Measurement structure. Each test measurement recorded in the device is
/// stored one of these structures. Holds the user inputted information about the horse,
/// together with bio-impedance readings measured by the device (raw electrical readings only,
/// not full results). 
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct ESMeasurement
{
	BSDeviceModel 	iDeviceModel;	// Device model which performed the measurement
	ULONG	ulDeviceSerialNumber;	// Unique serial number of the device which performed the measurement
	__time64_t	tTestDate;	// Date & time the test measurement was performed (Windows 64-bit time structure) (ES Pro only)

	int     iHeight;     	// Inputted height of the subject (centimeters)
	int		iBCScore;		// Inputted BC score

	int     iZ_5kHz;     	// Impedance measured at 5 kHz (result in ohms)
	int     iZ_16kHz;    	// Impedance measured at 16 kHz (result in ohms)
	int     iZ_24kHz;    	// Impedance measured at 24 kHz (result in ohms)
	int     iZ_50kHz;    	// Impedance measured at 50 kHz (result in ohms)
	int    	iZ_140kHz;		// Impedance measured at 140 kHz (result in ohms)
	int    	iZ_200kHz;		// Impedance measured at 200 kHz (result in ohms)
	int    	iZ_280kHz;		// Impedance measured at 280 kHz (result in ohms)
	float	fPA_50kHz;		// Phase angle measured at 50 kHz (result in degrees) (ES Pro only)
};


// Number of measurement records ESRawData structure should reserved space for (currently fixed)
const int ES_RAWDATA_ARRAYSIZE = 100;
////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// ESRawData: Equistat Raw Data structure. Used when downloading test measurements from the
/// device. Contains a fixed array of measurement records together with information about the
/// number of records occupied within the array and test record starting number. 
/// </summary>
/// <remarks>	Most models index 1000 records and store the last 100 at any given time. </remarks>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct ESRawData
{
	int iRecordArraySize /*= ES_RAWDATA_ARRAYSIZE*/;	// Maximum number of records this structure has reserved space for (currently fixed)
	ESMeasurement record[ES_RAWDATA_ARRAYSIZE];		// Array of test measurement data

	int	iTotalNumRecs;				// Number of populated records in the array
	int	ulFirstTestNum;				// Test number of the first record stored in the array.
};


////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// ESResults: Equistat Results structure. Holds the calculated results for any given test
/// measurement. 
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct ESResults
{
	float   fFatKg;      	// Fat (in kg)
	float	fPBM;			// PBM
	float	fIBM;			// IBM
	float	fFatKg_PBMPerc;	// Fat Kg PBM percentage
	float	fTFV;			// TFV
	float	fTFVPerc;		// TFV Percentage
	float	fECFV;			// ECFV
	float	fECFV_PBM;		// ECFV PBM
	float	fECFV_TFVPerc;	// ECFV TFV percentage
	float	fICFV;			// ICFV
	float	fICFV_PBM;		// ICFV PBM
	float	fICFV_TFVPerc;	// ICFV TFV percentage
	float	fPV;			// PV
	float	fPV_ECFVPerc;	// PV ECFV percentage
	float	fDehydration;	// Dehydration
};

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	
/// ESNormals: Equistat Normals structure. Holds the normal values or normal ranges for any given
/// test measurement. 
/// </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
struct ESNormals
{
	int	    iFatKg_L;				// Normal range for fat (in kg) - (low end)
	int  	iFatKg_H;				// Normal range for fat (in kg) - (high end)
	int		iFatKg_PBMPerc_L;		// Normal range for fat kg pbm percentage - (low end)
	int		iFatKg_PBMPerc_H;		// Normal range for fat kg pbm percentage - (high end)

	int		iTFV_L;					// Normal range for TFV - (low end)
	int		iTFV_H; 				// Normal range for TFV - (high end)
	int		iTFVPerc_L;				// Normal range for TFV percentage - (low end)
	int		iTFVPerc_H;				// Normal range for TFV percentage - (high end)

	int		iECFV_L;				// Normal range for ECFV - (low end)
	int		iECFV_H;				// Normal range for ECFV - (high end)
	int		iECFV_PBM_L;			// Normal range for ECFV PBM - (low end)
	int		iECFV_PBM_H;			// Normal range for ECFV PBM - (high end)
	int		iECFV_TFVPerc_L;		// Normal range for ECFV TFV percentage - (low end)
	int		iECFV_TFVPerc_H;		// Normal range for ECFV TFV percentage - (high end)

	int		iICFV_L;				// Normal range for ICFV - (low end)
	int		iICFV_H;				// Normal range for ICFV - (high end)
	int		iICFV_PBM_L;			// Normal range for ICFV PBM - (low end)
	int		iICFV_PBM_H;			// Normal range for ICFV PBM - (high end)
	int		iICFV_TFVPerc_L;		// Normal range for ICFV TFV percentage - (low end)
	int		iICFV_TFVPerc_H;		// Normal range for ICFV TFV percentage - (high end)

	int		iPV_L;					// Normal range for PV - (low end)
	int		iPV_H;					// Normal range for PV - (high end)
	int		iPV_ECFVPerc_L;			// Normal range for PV ECFV percentage - (low end)
	int		iPV_ECFVPerc_H;			// Normal range for PV ECFV percentage - (high end)
};

/**************************************************************************************************/

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Determine the Bodystat SDK library (DLL) version. </summary>
///
/// <param name="pMajorSdkVer">	[out] Receives the major version number of the Bodystat SDK DLL. </param>
/// <param name="pMinorSdkVer">	[out] Receives the minor version number of the Bodystat SDK DLL. </param>
///
/// <remarks>	Caller should check the version number of the DLL if utilising functionality noted
///				only as being available in later revisions of the SDK. Or, alternatively, ensure the
///				SDK DLL is updated appropriately during installation of your application. </remarks>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSGetSdkLibraryVersion(DWORD *pMajorSdkVer, DWORD *pMinorSdkVer);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Determine the device family of a specific model. </summary>
///
/// <param name="iModel">	The desired model of interest. </param>
///
/// <returns>	The device family the model belongs to. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSDeviceFamily BSGetDeviceFamily(BSDeviceModel iModel);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Determine the full product name of a specific model. </summary>
///
/// <param name="iModel">		The desired model of interest. </param>
/// <param name="lpBuffer">		[out] String buffer to receive the name. </param>
/// <param name="iBufferSize">	Size of the buffer. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API	BSError	BSGetDeviceModelName(BSDeviceModel iModel, LPTSTR lpBuffer, int iBufferSize);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Determine the short product name of a specific model. </summary>
///
/// <param name="iModel">		The desired model of interest. </param>
/// <param name="lpBuffer">		[out] String buffer to receive the name. </param>
/// <param name="iBufferSize">	Size of the buffer. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API	BSError	BSGetDeviceModelNameShort(BSDeviceModel iModel, LPTSTR lpBuffer, int iBufferSize);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Check if a supported BT radio is available on this computer.
///				Checks for presence of USB Bluetooth dongles and inbuilt Bluetooth modules in the PC.
///				No communication with Bodystat devices takes place during this query. </summary>
///
///	<remarks>	<para>Note: Only supported BT radios can be queried (presently those compatible with the
///				Microsoft Bluetooth APIs and some Widdcomm models).</para>
///				<para>Also note, Bluetooth must be enabled on the PC by the user to permit detection.
///				Some PCs, laptops particularly, have physical switches to enable bluetooth/wireless
///				communication.</para>	</remarks>
///
/// <returns>	Returns true if supported radio is available and enabled. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BOOL 	BSIsBTAvailable();

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Check if a device/driver is currently being installed by windows. </summary>
///
/// <param name="dwTimeout">		Duration to wait for installation to finish in milliseconds. 0=No wait, Windows INFINITE=forever</param>
///
///	<remarks>	<para>When used with a timeout this is a blocking call.</para></remarks>
///
/// <returns>	Returns true if a device is currently being installed. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BOOL BSIsDeviceInstallInProgress(DWORD dwTimeout = 0);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Retrieve information about the Bluetooth stack. Useful for diagnostics. </summary>
///
/// <param name="lpBuffer">		[out] String buffer to receive the information. </param>
/// <param name="iBufferSize">	Size of the buffer. </param>
///
///	<remarks>	Note: Information can only be provided for supported BT radios. </remarks> 
///
/// <returns>	true if it succeeds, false if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BOOL 	BSGetBTStackInfo(LPTSTR lpBuffer, int iBufferSize);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	<para>Automatic Bluetooth setup. Automatically searches available Bluetooth devices,
///				exchanges passkeys with Bodystat device and enables serial port service required for
///				communication with the device. If multiple Bodystat devices are detected the user is
///				prompted to chose the desired device (model and BT BDA address shown). </para>
///				<para>This function is typically called as a one time setup for the device (e.g. after
///				first installation, or from the hardware configuration page of your application's
///				settings, or when the user obtains a replacement device (upgrades/replacement/etc).</para>
///				<para>Typically, once setup you need only store the device com port returned.
///				You can then subsequently communicate with the device knowing only the com port.
///				It is not necessary to setup the device in this way before each use.</para>
///				<para>New non-paired units will only be found if switched on, in range and ready for
///				communication (on main startup screen). It is advisable to instruct the user to 
///				ensure this is the case before calling.</para> </summary>
///
///	<remarks>	<para>Note this process can be time consuming to complete and executes synchronously.
///				Either call from a threaded function or illustrate operation in progress to the user
///				e.g. by means of an indefinite progress bar or busy mouse cursor, until the task
///				completes or timesout. </para>
///				<para>Errors during the process can be optionally shown/hidden. However, a completely
///				silent approach is not possible using this function (instead use BSSearchBTDevices
///				and BSGetBTBodystatDevice or iterate radio handles manually. Then pass desired handle
///				to BSAuthenticateBTDevice for pairing).</para>
///				</para>Finally be aware this function is only available for supported locales. Otherwise
///				English messages may be displayed to the user. Adopt silent approach discussed
///				previously if you are targeting a non-supported locale. </para>	</remarks>
///
/// <param name="lpComPort">		[out] String buffer to receive the device port the device is assigned to. </param>
/// <param name="iSize">			The size of the buffer. </param>
/// <param name="bReportErrors">	TRUE to report errors to the user (shown as message boxes, locale constraints apply). FALSE to hide errors from the user (still not completely silent). </param>
/// <param name="hWndParent">		Handle of the parent window. </param>
///
/// <returns>	TRUE if it succeeds, FALSE if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BOOL 	BSAutoSetupBT(LPTSTR lpComPort, int iSize, BOOL bReportErrors, HWND hWndParent = NULL);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Search BT radio for any Bodystat devices (paired or otherwise).
///				Existing paired devices will be counted even if they are switched off or out of range.
///				New non-paired units will only be counted if switched on, in range and ready for
///				communication (on main startup screen). </summary>
///
/// <remarks>	Note this process can be time consuming to complete and executes synchronously.
///				Either call from a threaded function or illustrate operation in progress to the user
///				e.g. by means of an indefinite progress bar or busy mouse cursor, until the task
///				completes or timesout. </remark>
///
/// <param name="iNewDevices">				[out] The number of new Bodystat devices found (not paired). </param>
/// <param name="iAuthenticatedDevices">	[out] The number of authenticated Bodystat devices (paired). </param>
/// <param name="bReportErrors">			TRUE to report errors to the user (shown as message boxes, locale constraints apply). FALSE to hide errors from the user (completely silent). </param>
/// <param name="hWndParent">				Handle of the parent window. </param>
/// <param name="iTimeout">					Timeout multiplier supplied to the Bluetooth radio search API. Controls the amount of time to spend searching for the device. This function will block for this duration so is better called from a thread. Each multiplier increment equates to about 1.28 seconds. Thus a timeout value of 10 = 12.8s. Maximum time permitted by the API is a multiplier of 45 (just under 1 minute), values higher than this will be capped at 45. Default value is 7 (about 10 seconds).</param>
///
/// <returns>	TRUE if it succeeds, FALSE if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BOOL 	BSSearchBTDevices(int &iNewDevices, int &iAuthenticatedDevices, BOOL bReportErrors = TRUE, HWND hWndParent = NULL, unsigned short iTimeout = 7);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Used to get information about any Bodystat device found after a previous call to BSSearchBTDevices. </summary>
///
/// <param name="lpDeviceName">				[out] String buffer to receive the product name of the Bodystat device. </param>
/// <param name="iDeviceNameBufferSize">	Size of the device name buffer. </param>
/// <param name="lpBDA">					[out] String buffer to receive the Bluetooth hexadecimal address (known as the BDA - unique to each BT module in a device, like a MAC address). </param>
/// <param name="iBDABufferSize">			Size of the BDA buffer. </param>
/// <param name="lpComPort">				[out] String buffer to receive device/port the unit is assigned to.</param>
/// <param name="iComBufferSize">			Size of the com port buffer. </param>
/// <param name="iTimeout">					Timeout multiplier supplied to the Bluetooth radio search API. Controls the amount of time to spend searching for the device. This function will block for this duration so is better called from a thread. Each multiplier increment equates to about 1.28 seconds. Thus a timeout value of 10 = 12.8s. Maximum time permitted by the API is a multiplier of 45 (just under 1 minute), values higher than this will be capped at 45. Default value is 7 (about 10 seconds).</param>
///
/// <returns>	TRUE if it succeeds, FALSE if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BOOL	BSGetBTBodystatDevice(LPTSTR lpDeviceName, int iDeviceNameBufferSize, LPTSTR lpBDA, int iBDABufferSize, LPTSTR lpComPort, int iComBufferSize, unsigned short iTimeout = 7);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Authenticate (pair) a Bodystat device found during a previous call to BSSearchBTDevices.
///				Completely silent implementation. </summary>
///
///	<remarks>	Note this process can be time consuming to complete and executes synchronously.
///				Either call from a threaded function or illustrate operation in progress to the user
///				e.g. by means of an indefinite progress bar or busy mouse cursor, until the task
///				completes or timesout. </remarks>
///
/// <param name="hWndParent">	Handle of the parent window. </param>
/// <param name="iTimeout">					Timeout multiplier supplied to the Bluetooth radio search API. Controls the amount of time to spend searching for the device. This function will block for this duration so is better called from a thread. Each multiplier increment equates to about 1.28 seconds. Thus a timeout value of 10 = 12.8s. Maximum time permitted by the API is a multiplier of 45 (just under 1 minute), values higher than this will be capped at 45. Default value is 7 (about 10 seconds).</param>
///
/// <returns>	TRUE if it succeeds, FALSE if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BOOL 	BSAuthenticateBTDevice(HWND hWndParent = NULL, unsigned short iTimeout = 7);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Unauthenticate (unpair) ALL Bodystat devices from this PC. </summary>
///
///	<remarks>	Note this process can be time consuming to complete and executes synchronously.
///				Either call from a threaded function or illustrate operation in progress to the user
///				e.g. by means of an indefinite progress bar or busy mouse cursor, until the task
///				completes or timesout. </remarks>
///
/// <param name="bReportErrors">	TRUE to report errors to the user (shown as message boxes, locale constraints apply). FALSE to hide errors from the user. </param>
/// <param name="hWndParent">		Handle of the parent window. </param>
/// <param name="iTimeout">			Timeout multiplier supplied to the Bluetooth radio search API. Controls the amount of time to spend searching for the device. This function will block for this duration so is better called from a thread. Each multiplier increment equates to about 1.28 seconds. Thus a timeout value of 10 = 12.8s. Maximum time permitted by the API is a multiplier of 45 (just under 1 minute), values higher than this will be capped at 45. Default value is 7 (about 10 seconds).</param>
///
/// <returns>	TRUE if it succeeds, FALSE if it fails. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BOOL 	BSUnAuthenticateBTDevices(BOOL bReportErrors = TRUE, HWND hWndParent = NULL, unsigned short iTimeout = 7);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Calculate complete result set for a given bio-impedance measurement recorded by the
///				Bodystat device. </summary>
///
///	<remarks>	Results vary by subject attributes and measured bio-impedance values.	</remarks>
///
/// <param name="pM">				The measurement details downloaded from the device (includes model, user inputted parameters and bio-impedance measurement readings).</param>
/// <param name="pR">				[out] Receives the complete calculated results for this measurement. </param>
/// <param name="iAnalysisMode">	The desired analysis mode (see BSAnalysisMode for more information). </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSCalculateResults(const BSMeasurement *pM, BSResults *pR, BSAnalysisMode iAnalysisMode);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Calculate complete result set for a given bio-impedance measurement recorded by the
///				Equistat device. </summary>
///
///	<remarks>	Results vary by input attributes and measured bio-impedance values.	</remarks>
///
/// <param name="pM">				The measurement details downloaded from the device (includes model, user inputted parameters and bio-impedance measurement readings).</param>
/// <param name="pR">				[out] Receives the complete calculated results for this measurement. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError ESCalculateResults(const ESMeasurement *pM, ESResults *pR);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Calculate normal values and normal ranges for a given subject and their bio-impedance
///				measurement together with the matching results structure for that measurement.
///				You must supply a populated results structure which pertains to the measurement being
///				supplied (obtained from BSCalculateResults). </summary>
///
///	<remarks>	Normals vary by subject attributes, measured bio-impedance values and calculated results. </remarks>
///
/// <param name="pM">	The measurement details downloaded from the device (includes model, user inputted parameters and bio-impedance measurement readings). </param>
/// <param name="pR">	The results calculated for this measurement previously. </param>
/// <param name="pN">	[out] Receives the normal values and normal ranges for this measurement. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSCalculateNormals(const BSMeasurement *pM, const BSResults *pR, BSNormals *pN);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Calculate normal values and normal ranges for a given animal and their bio-impedance
///				measurement together with the matching results structure for that measurement.
///				You must supply a populated results structure which pertains to the measurement being
///				supplied (obtained from ESCalculateResults). </summary>
///
///	<remarks>	Normals vary by input attributes, measured bio-impedance values and calculated results. </remarks>
///
/// <param name="pM">	The measurement details downloaded from the device (includes model, user inputted parameters and bio-impedance measurement readings). </param>
/// <param name="pR">	The results calculated for this measurement previously. </param>
/// <param name="pN">	[out] Receives the normal values and normal ranges for this measurement. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError ESCalculateNormals(const ESMeasurement *pM, const ESResults *pR, ESNormals *pN);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Open com port to the device ready for communication. </summary>
///
/// <param name="lpComPort">	String buffer containing the device/port to be opened. </param>
/// <param name="iSize">		The size of the buffer. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSOpenComport(LPCTSTR lpComPort, int iSize);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Close com port. </summary>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API void	BSCloseComport();

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Connect to the Bodystat device and ensure the device is responding.
///
///	<remarks>	You must have opened the com port by calling BSOpenComPort previously. </remarks>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSConnect();

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Read device model and firmware version of the connected Bodystat device. </summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously. </remarks>
///
/// <param name="pModel">			[out] Receives the device model. </param>
/// <param name="pMajorVersion">	[out] Receives the major version of the main firmware in the device. </param>
/// <param name="pMinorVersion">	[out] Receives the minor version of the main firmware in the device. </param>
/// <param name="pPsoc2Version">	[out] Receives the version of Psoc2 firmware in the device. </param>
/// <param name="pEepromVersion">	[out] Receives the version of the EEprom firmware in the device. </param>
/// <param name="pBluetoothInfo">	[out] Receives the version of the Bluetooth module in the device. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSReadModelVersion(BSDeviceModel *pModel, BYTE *pMajorVersion, BYTE *pMinorVersion, BYTE *pPsoc2Version, BYTE *pEepromVersion, BYTE *pBluetoothInfo);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Read protocol information from the connected device. Contains version numbers relating
///				to communication protocols in use, data structures and auxiliary information. </summary>
///
///	<remarks>	Generally not required for the majority of SDK users as these details are abstracted
///				by the SDK. </remarks>
///
/// <param name="pProtocolVersion">	[out] Receives the communication protocol version. </param>
/// <param name="pDataVersion">		[out] Receives the data structure version. </param>
/// <param name="pAuxInfo">			[out] Receives auxiliary information. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSReadProtocolInfo(BYTE *pProtocolVersion, BYTE *pDataVersion, BYTE *pAuxInfo);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Read the unique serial number of the connected Bodystat device. </summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously. </remarks>
///
/// <param name="pSerialNumber">	[out] Receives the serial number of the device. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSReadSerialNumber(ULONG *pSerialNumber);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Read the current time from the internal clock of the connected device.
///				Note not all device models support this function (not all have an internal clock).
/// </summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously. </remarks>
///
/// <param name="pCurrentTime">	[out] Receives the current time of the device's internal clock. </param>
/// <param name="iDST">			Daylight Saving Time handling (as per Microsoft time functions)
///								Zero (0) to indicate that standard time is in effect.
///								A value greater than 0 to indicate that daylight saving time is in effect.
///								A value less than zero to have the C run-time library code compute whether standard time or daylight saving time is in effect. (default)
///	</param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSReadCurrentTime(__time64_t *pCurrentTime, int iDST = -1);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Read the calibration date from the connected device (when the unit was last calibrated).
///				Only the date element of this value should be shown. Exact time value is not relevant. </summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously. </remarks>
///
/// <param name="pCalibrationTime">	[out] Receives the date the device was last calibrated. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSReadCalibrationTime(__time64_t *pCalibrationTime);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Read the printer address the connected device is paired with (for direct printing).
///				Not all device models support this function (not all support direct printing). </summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously. </remarks>
///
/// <param name="lpPrinterAddress">	[out] String buffer which receives the printer address. </param>
/// <param name="iPrinterAddressBufferSize">		Size of the buffer. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSReadPrinterAddress(LPTSTR lpPrinterAddress, int iPrinterAddressBufferSize);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	<para>Download test data from the connected device. Retrieves the last 100 test
///				measurements (records) stored in the memory of the device. Downloading data
///				does not affect the results stored in the memory - they remain unchanged. </para>
///				<para>Note: you should store downloaded data locally if it is required permanently.
///				Most devices store only the last 100 test records before overwriting the oldest
///				records automatically. </para> </summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously.
///				Caller must check they are working with a Bodystat (rather than Equistat model,
///				Equistat models will respond without error - but with garbage results). </remarks>
///
/// <param name="pRawData">	[out] Pointer to a structure to receive the downloaded data. Caller responsible for allocation and disposing of the structure.</param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSReadStoredTestData(BSRawData *pRawData);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	<para>Download test data from the connected device. Retrieves the last 100 test
///				measurements (records) stored in the memory of the device. Downloading data
///				does not affect the results stored in the memory - they remain unchanged. </para>
///				<para>Note: you should store downloaded data locally if it is required permanently.
///				Most devices store only the last 100 test records before overwriting the oldest
///				records automatically. </para> </summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously.
///				Caller must check they are working with an Equistat (rather than Bodystat model,
///				Bodystat models will respond without error - but with garbage results). </remarks>
///
/// <param name="pRawData">	[out] Pointer to a structure to receive the downloaded data. Caller responsible for allocation and disposing of the structure.</param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError ESReadStoredTestData(ESRawData *pRawData);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	<para>Perform a quick bio-impedance test measurement on the connected bodystat device.
///				Normal test process is skipped (user is not prompted to enter any subject information).
///				Normal test protocol is disregarded (measurement proceeds regardless of lead status).
///				Test measurement is not stored in device memory.</para>
///				<para>May give wildly erratic readings if leads are not connected properly. Caller should
///				sanity check results to detect for such scenarios. Results are intentionally not
///				sanity checked to provide a true raw reading and provide caller with total discretion. </para>
///				<para>Useful for diagnostics or performing measurements instigated by software. </para>
///	</summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously. 
///				Caller must check they are working with a Bodystat (rather than Equistat model,
///				Equistat models will respond without error - but with garbage results). </remarks>
///
/// <param name="pZ5">		[out] Receives the impedance measured at 5 kHz (result in ohms). </param>
/// <param name="pZ50">		[out] Receives the impedance measured at 50 kHz (result in ohms). </param>
/// <param name="pZ100">	[out] Receives the impedance measured at 100 kHz (result in ohms). </param>
/// <param name="pZ200">	[out] Receives the impedance measured at 200 kHz (result in ohms). </param>
/// <param name="pR50">		[out] Receives the resistance measured at 50 kHz (result in ohms). </param>
/// <param name="pX50">		[out] Receives the reactance measured at 50 kHz (result in ohms). </param>
/// <param name="pPA50">	[out] Receives the phase angle measured at 50 kHz (result in degrees). </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSReadTestBodystat(UINT *pZ5, UINT *pZ50, UINT *pZ100, UINT *pZ200, UINT *pR50, float *pX50, float *pPA50 );

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	<para>Perform a quick bio-impedance test measurement on the connected equistat device.
///				Normal test process is skipped (user is not prompted to enter any horse information).
///				Normal test protocol is disregarded (measurement proceeds regardless of lead status).
///				Test measurement is not stored in device memory.</para>
///				<para>May give wildly erratic readings if leads are not connected properly. Caller should
///				sanity check results to detect for such scenarios. Results are intentionally not
///				sanity checked to provide a true raw reading and provide caller with total discretion. </para>
///				<para>Useful for diagnostics or performing measurements instigated by software. </para>
///	</summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously.
///				Caller must check they are working with an Equistat (rather than Bodystat model,
///				Bodystat models will respond without error - but with garbage results). </remarks>
///
/// <param name="pZ5">		[out] Receives the impedance measured at 5 kHz (result in ohms). </param>
/// <param name="pZ16">		[out] Receives the impedance measured at 16 kHz (result in ohms). </param>
/// <param name="pZ24">		[out] Receives the impedance measured at 24 kHz (result in ohms). </param>
/// <param name="pZ50">		[out] Receives the impedance measured at 50 kHz (result in ohms). </param>
/// <param name="pZ140">	[out] Receives the impedance measured at 140 kHz (result in ohms). </param>
/// <param name="pZ200">	[out] Receives the impedance measured at 200 kHz (result in ohms). </param>
/// <param name="pZ280">	[out] Receives the impedance measured at 280 kHz (result in ohms). </param>
/// <param name="pPA50">	[out] Receives the phase angle measured at 50 kHz (result in degress) (ES Pro Only).</param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError ESReadTestEquistat( UINT *pZ5, UINT *pZ16, UINT *pZ24, UINT *pZ50, UINT *pZ140, UINT *pZ200, UINT *pZ280, float *pPA50 );

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Reset the current date/time of the internal clock on the connected device.
///				Date/time is automatically set to match the current date/time of the PC </summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously. 
///				Locale Daylight Saving Time (DST) rules are observed.
///				Use sister function BSWriteCurrentTime(__time64_t CurrentTime) to set a specific
///				date/time which differs from the PC clock or override DST behaviour. </remarks>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSWriteCurrentTime();

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Reset the current date/time of the internal clock on the connected device.
///				Date/time is set to a specific value of your choosing. </summary>
///
///	<remarks>	You must have connected to the device by calling BSConnect previously.
///				Use sister function (omit date/time parameter entirely) BSWriteCurrentTime()
///				to automatically set to the current date/time of the PC. </remarks>
///
/// <param name="CurrentTime"> Date/time to apply to the internal clock of the device (should be current!). </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSWriteCurrentTimeAs(__time64_t CurrentTime);

////////////////////////////////////////////////////////////////////////////////////////////////////
/// <summary>	Set the address of the printer the connected device should use for direct printing.
///				Programmatic implementation of the inbuilt printer pairing function in the device. </summary>
///
///	<remarks>	Note not all device models support this function (not all support direct printing). </remarks>
///
/// <param name="lpPrinterAddress">	String buffer containing the Bluetooth address (BDA) of the printer. </param>
/// <param name="iBufferSize">		Size of the buffer. </param>
///
/// <returns>	Returns BSError::NoError if successful. Specific error code otherwise. </returns>
////////////////////////////////////////////////////////////////////////////////////////////////////
BODYSTATSDK_API BSError BSWritePrinterAddress(LPCTSTR lpPrinterAddress, int iBufferSize);

};
