#ifndef _CAMUSER_H_
#define _CAMUSER_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define MAX_ADC_DAC_VALUE               ((1 << ADC_DAC_SIZE) - 1 )
#define ADC_DAC_SIZE                    14
#define DEFAULT_SYMBOL_COLOR            SYMBOLS_WHITE_BLACK
#define DEFAULT_SPOT_METER_MODE         SPOT_METER_ON_FAHRENHEIT
#define DEFAULT_SPOT_METER_DISPLAY      SPOT_MASK_DIGITAL
#define DEFAULT_ISOTHERM_MODE           ISOTHERM_ON

/*!
 * Represents the different gain modes the camera supports.
 */
typedef enum GainMode
{
    AUTO_GAIN_MODE   = 0,  /*!< Camera can switch between different gain tables automatically */
    LOW_GAIN_MODE    = 1,  /*!< Camera is always in the low gain table */
    HIGH_GAIN_MODE   = 2,  /*!< Camera is always in the high gain tables */
    MANUAL_GAIN_MODE = 3
} CAM_GAIN_MODE;


/*!
 * Represents the different flat field correction (FFC) modes the camera supports.
 */
typedef enum FFCMode
{
    MANUAL_FFC   = 0,   /*!< Camera does not perform flat field corrections based on a frame interval or temperature change */
    AUTO_FFC     = 1,   /*!< Camera will automatically perform flat field corrections based on a frame interval and temperature change*/
    EXTERNAL_FFC = 2    /*!< Camera will perform a manual flat field corrections based on an external black body and not the flag*/
} CAM_FFC_MODE;

/*!
 * Represents the different video modes the camera supports. 
 * Combinations of different video modes can be combined using the logical or operator
 * with the exception of VIDEO_REAL_TIME and VIDEO_FROZEN which are mutually exclusive. 
 */
typedef enum VideoMode
{
    VIDEO_REAL_TIME = 0,  /*!< Real time video */
    VIDEO_ENABLED   = 0,  /*!< Enables analog video, use only with Set/GetAnalaoVideoOnOff function */
    VIDEO_UNZOOM    = 0,  /*!< Unzooms the analog video, use only with Set/GetZoomMode function */
    VIDEO_FROZEN    = 1,  /*!< Frozen video */
    VIDEO_DISABLED  = 2,  /*!< Disabled video */
    VIDEO_ZOOM      = 4,  /*!< 2x zoomed video */
    VIDEO_4XZOOM    = 8,  /*!< 4x zoomed video */    
    VIDEO_8XZOOM    = 16, /*!< 8x zoomed video */    
    VIDEO_TOGGLE    = 256 /*!< Special command to toggle through zoom modes */    
} CAM_VIDEO_MODE;


/*
 * Defines for controlling the averager module
 */
typedef enum AveragerMode
{
    GET_AVERAGER_BYPASS     = 0,
    SET_AVERAGER_BYPASS     = 1,
    SET_AVERAGER_BYPASS_OFF = 0,
    SET_AVERAGER_BYPASS_ON  = 1,
} CAM_AVERAGER_MODE;

/*!
 * Represents the Video color modes
 */
typedef enum VideoColor
{
    VIDEO_COLOR_OFF = 0,     /*!< Video color turned off*/
    VIDEO_COLOR_ON  = 1,     /*!< Video color turned on and user LUT not used*/
    VIDEO_COLOR_OFF_LUT = 2  /*!< Video color turned off and user LUT used. Used for gamma correction*/ 
} CAM_VIDEO_COLOR;

/*!
 * Represents the different video standards the camera supports.
 */
typedef enum VideoStandard
{
    VIDEO_RS_170  = 0,  /*!< NTSC */
    VIDEO_STD_PAL = 1,  /*!< PAL */
    // Above definitions left in for 
	VIDEO_NTSC_AVG_ENABLED_30HZ     = 0,  // Averager enabled, fields averaged
	VIDEO_PAL_AVG_ENABLED_25HZ      = 1,  // Averager enabled, fields averaged
	VIDEO_NTSC_AVG_DISABLED_30HZ    = 2,  // Averager disabled, fields replicated
	VIDEO_PAL_AVG_DISABLED_25HZ     = 3,  // Averager disabled, fields replicated
	VIDEO_NTSC_AVG_BYPASSED_60HZ    = 4,  // Averager bypassed, 60Hz
	VIDEO_PAL_AVG_BYPASSED_50HZ     = 5,  // Averager bypassed, 50Hz
} CAM_VIDEO_STANDARD;

/*!
 * Represents the different image orientations the camera supports.
 */
typedef enum ImageOrientation
{
    IMAGE_UNKNOWN       = -1, /*!< Unknown image orientation */
    IMAGE_NORMAL        = 0,  /*!< Normal image orientation */
    IMAGE_INVERT        = 1,  /*!< Image is inverted on the x axis */
    IMAGE_REVERT        = 2,  /*!< Image is reverted on the y axis */
    IMAGE_INVERT_REVERT = 3   /*!< Image is both inverted and reverted */
} CAM_IMAGE_ORIENTATION;

/*!
 * Represents the different automatic gain correction (AGC) algorithms the camera supports.
 */
typedef enum AGCAlgorithm
{
    PLATEAU_AGC     = 0,  /*!< Plateau AGC Algorithm */
    ONCE_BRIGHT_AGC = 1,  /*!< Once Bright AGC Algorithm */
    AUTO_BRIGHT_AGC = 2,  /*!< Automatic Bright AGC Algorithm */
    MANUAL_AGC      = 3,  /*!< Full Manual AGC Algorithm */
    PSEUDO_GAIN_AGC = 4,
    AUTO_LINEAR_AGC = 5,  /*!< Automatic Linear AGC Algorithm */
    LOG_AGC         = 6,  /*!< Logarithmic AGC Algorithm */
    HIST_SPEC_AGC   = 7   /*!< Histogram Specification AGC Algorithm */
} CAM_AGC_ALGORITHM;

/*!
 * Represents the different test patterns the camera supports.
 * The video mode cannot be VIDEO_ZOOM for the test patterns to be displayed properly.
 */
typedef enum TestPattern
{
    NO_TEST_PATTERN             = 0,  /*!< No test pattern */
    ASCENDING_RAMP_TEST_PATTERN = 1,  /*!< A ramp test pattern that displays horizontal bars */
    VERT_SHADE_TEST_PATTERN     = 2,  /*!< A ramp test pattern that displays vertical bars */
    BIG_VERT_SHADE_TEST_PATTERN = 3,  /*!< A ramp test pattern that displays vertical bars of a wide width */
    HORZ_LINE_TEST_PATTERN      = 4,  /*!< A ramp test pattern that displays thin horizontal bars  */
    NO_SMOOTHING_TEST_PATTERN   = 5,  /*!< Only availavle in Omega cameras */
    COLOR_TEST_PATTERN          = 6,  /*!< A test pattern that displays the current lut table */
#if defined(_HONDA) || defined(_NV3_HONDA)
	ALPS_TEST_PATTERN           = 7,
#endif
    STEPS_TEST_PATTERN          = 8,
    GET_RAMP_PARAMS             = 256

} CAM_TEST_PATTERN;

/*!
 * Represents the different test digital output modes the camera supports.
 */
typedef enum DigitalOut
{
    DIGITAL_14BIT            = 0,  /*!< 14 bit digital data  */ 
    DIGITAL_8BIT             = 1,  /*!< 8 bit digital data */ 
    DIGITAL_OFF              = 2,  /*!< Digital data off */
    DIGITAL_14BIT_UNFILTERED = 3,  /*!< 14 bit unfiltered digital data */
    DIGITAL_8BIT_INV             = 4, /*!< 8 bit digital data inverted */   
    DIGITAL_14BIT_INV            = 5, /*!< 16 bit digital data inverted */   
    DIGITAL_14BIT_INV_UNFILTERED = 6, /*!< 14 bit unfiltered digital data inverted */
    DIGITAL_GET_WINDOW           = 256, /*!< window size sub command */
    DIGITAL_FPA_DIMENSIONS       = 257,  /*!< fpa size sub command */
    GET_XPBUS_MODE               = 0x200,
    SET_XPBUS_MODE               = 0x300,
    GET_LVDS_MODE                = 0x400,
    SET_LVDS_MODE                = 0x500,
    SET_CMOS_MODE_BIT_DEPTH      = 0x600,
    SET_LVDS_MODE_BIT_DEPTH      = 0x700,
    GET_CMOS_MODE_BIT_DEPTH      = 0x800,
    GET_LVDS_MODE_BIT_DEPTH      = 0x900,
} CAM_DIGITAL_OUT;

/*!
 * Represents the different external video sync modes the camera supports.
 */
typedef enum ExtSyncMode
{
    EXT_SYNC_DISABLED = 0,  /*!< External synchronization disabled */
    EXT_SYNC_SLAVE    = 1,  /*!< Slave mode external synchronization */
    EXT_SYNC_MASTER   = 2   /*!< Master mode external synchronization */
} CAM_EXT_SYNC_MODE;

/*!
 * Represents the different spot meter modes the camera supports.
 */
typedef enum SpotMeterMode
{
    SPOT_METER_OFF           = 0,  /*!< Spot meter off */
    SPOT_METER_ON_FAHRENHEIT = 1,  /*!< Spot meter on, fahrenheit mode */
    SPOT_METER_ON_CELSIUS    = 2   /*!< Spot meter on, celsius mode */
} CAM_SPOT_METER_MODE;

/*!
 * Represents the different spot display modes the camera supports.
 */
typedef enum SpotDisplay
{
    SPOT_DISPLAY_OFF      = 0,  /*!< Spot display off */
    SPOT_MASK_DIGITAL     = 1,  /*!< Spot display digital */
    SPOT_MASK_THERMOMETER = 2,  /*!< Spot display thermometer */
    SPOT_MASK_DIGI_THERM  = 3   /*!< Spot display digital and thermometer */
} CAM_SPOT_DISPLAY;

/*!
 * Represents the different spot isotherm modes the camera supports.
 */
typedef enum IsothermMode
{
    ISOTHERM_OFF = 0,  /*!< Isotherms off */
    ISOTHERM_ON  = 1   /*!< Isotherms on */
} CAM_ISOTHERM_MODE;

/*!
 * Represents the different types that can be used to set the isotherm thresholds for the camera.
 */
typedef enum IsothermThresholdType
{
    ISOTHERM_PERCENTAGE = 0,  /*!< Isotherm thresholds in percentage */
    ISOTHERM_CELSIUS    = 1   /*!< Isotherm thresholds in degrees celsius */
} CAM_ISOTHERM_THRESHOLD_TYPE;

/*!
 * Represents the different color LUTS the camera supports.
 */
typedef enum ColorLut
{
    WHITE_HOT_LUT   = 0,    /*!< White hot color lut */
    BLACK_HOT_LUT   = 1,    /*!< Black hot color lut */
#ifdef _PHOTON
    FUSION_LUT      = 2,    /*!< Fusion color lut (Photon only) */
    RAINBOW_LUT     = 3,    /*!< Rainbow color lut (Photon only) */
    GLOBOW_LUT      = 4,    /*!< Glowbow color lut (Photon only) */
    IRONBOW1_LUT    = 5,    /*!< Ironbow 1 color lut (Photon only) */
    IRONBOW2_LUT    = 6,    /*!< Ironbow 2 color lut (Photon only) */
    SEPIA_LUT       = 7,    /*!< Sepia color lut (Photon only) */
    COLOR1_LUT      = 8,    /*!< Color 1 color lut (Photon only) */
    COLOR2_LUT      = 9,    /*!< Color 2 color lut (Photon only) */
    ICEFIRE_LUT     = 10,   /*!< Icefire color lut (Photon only) */
    RAIN_LUT        = 11,   /*!< Rain color lut (Photon only) */
    COLOR12_LUT     = 12,   /*!< Placeholder for additional color lut */
    COLOR13_LUT     = 13,   /*!< Placeholder for additional color lut */
    COLOR14_LUT     = 14,   /*!< Placeholder for additional color lut */
    COLOR15_LUT     = 15,   /*!< Placeholder for additional color lut */
#endif
    IMAGE_LUTS      = 16,   /*!< Number of imaging LUTs */
    SPLASH_LUT      = 31,   /*!< LUT table used by splash screen */
    NUM_COLOR_LUTS             /*!< Total number of color LUTs */
} CAM_COLOR_LUT;

#define VIDEO_LUT_TOGGLE 256 /*!< Special command to Toggle the Video LUTs */

                                /*!
 * Represents the different camera products
 */
typedef enum ProductId
{
    PRODUCT_PHOTON    = 1,  /*< Photon */
    PRODUCT_PHOTON640 = 6,  /*< Photon 640 */
    PRODUCT_SPECTARE  = 7,  /*< Spectare */
    PRODUCT_TAU = 10,       /*<TargMon>*/
    PRODUCT_TARGMON = 11,   /*<TargMon>*/
    PRODUCT_TAU2 = 15,      /*<TargMon>*/
    PRODUCT_T2CC = 16,      /*< Tau 2cc >*/
    PRODUCT_BOOTMON = 2822  /*<BootMon>*/
} CAM_PRODUCT_ID;

typedef enum FlashError
{
    FLASH_ERASE_ERROR = -1,
    FLASH_WRITE_ERROR = -2
} CAM_FLASH_ERROR;

/*!
 * Represents the different camera reset types
 */
typedef enum ResetType
{
    NORMAL_RESET = 0,
    SOFTWARE_RESET = 1,
    FORCE_WATCH_DOG = 2,
    FORCE_ILLEGAL_OPCODE = 3,
    FORCE_ILLEGAL_ADDR = 4,
    FORCE_DIVIDE_BY_0 = 5
} CAM_RESET_TYPE;

/*!
 * Represents the different camera lock modes/levels
 */
typedef enum LockLevel
{
    CAL_MODE = -1,
    RUN_MODE = 1,
    EXTENDED_MODE = 2,
    FACTORY_MODE = 3,
	INIT_MODE = 4,
#ifdef _NV3_HONDA
	HONDA_MODE = 5,
#endif

    RUN_MASK = 1 << RUN_MODE,
    EXTENDED_MASK = 1 << EXTENDED_MODE,
    FACTORY_MASK = 1 << FACTORY_MODE,
#ifdef _NV3_HONDA
	HONDA_MASK = 1 << HONDA_MODE,
#endif
    ALL_MASK = (int)~0U

} CAM_LOCK_LEVEL;

/* Extended commands for Supplemental Offset */
typedef enum cam_extoffset
{
    EXTOFFSET_FACTORY_MODE      = 0,
    EXTOFFSET_FIELD_MODE        = 1,
    
    SET_EXTOFFSET_MODE          = (1 << 8),
    GET_EXTOFFSET_MODE          = (2 << 8),
    SET_EXTOFF_MONITOR_PERIOD   = (3 << 8),
    GET_EXTOFF_MONITOR_PERIOD   = (4 << 8),
    GET_EXTOFF_DELTA_TEMPS      = (5 << 8)
} CAM_EXTOFFSET;

/*!
 * Represents the different command prototypes used by the camera.
 */
typedef enum proto_command
{
    NO_OP                   = 0,
    SET_DEFAULTS            = 1,
    CAMERA_RESET            = 2,
    RESET_FACTORY_DEFAULTS  = 3,
    SERIAL_NUMBER           = 4,
    GET_REVISION            = 5,
    STATUS_REQUEST          = 6,
    BAUD_RATE               = 7,
    IGNORE_CRC              = 8,
    GAIN_MODE               = 10,
    FFC_MODE_SELECT         = 11,
    DO_FFC                  = 12,
    FFC_PERIOD              = 13,
    FFC_TEMP_DELTA          = 14,
    VIDEO_MODE              = 15,
    VIDEO_LUT               = 16,
    VIDEO_ORIENTATION       = 17,
    DIGITAL_OUTPUT_MODE     = 18,
    AGC_TYPE                = 19,
    CONTRAST                = 20,
    BRIGHTNESS              = 21,
    BRIGHTNESS_BIAS         = 24,
    LENS_NUMBER             = 30,
    SPOT_METER_MODE         = 31,
    READ_SENSOR             = 32,
    EXTERNAL_SYNC           = 33,
    ISOTHERM                = 34,
    ISOTHERM_THRESHOLDS     = 35,
    GET_ISOTHERM_THRESHOLDS = 36,
    TEST_PATTERN            = 37,
    VIDEO_COLOR_MODE        = 38,
    GET_LENS_ID             = 40,
    GET_CAMERA_OPTIONS      = 41,
    GET_SPOT_METER          = 42,
    SPOT_DISPLAY            = 43,
    DDE_GAIN                = 44,
    GET_VIDEO_RATE          = 45,
    HEATER_CONTROL          = 46,
    SYMBOL_CONTROL          = 47,
    DISCRETE_CONTROL        = 48,
    SPLASH_CONTROL          = 49,
    FFC_WARN_TIME           = 60,
    AGC_FILTER              = 62,
    PLATEAU_LEVEL           = 63,
    GET_SPOT_METER_DATA     = 67,
    FFC_MEAN_VALUE          = 68,
    AUX_SENSOR              = 71,
    AGC_ROI                 = 76,
    ITT_MIDPOINT            = 85,
    USER_INPUT              = 90,
    CAMERA_PART             = 102,
    READ_ARRAY_AVERAGE      = 104,
    MAX_AGC_GAIN            = 106,
    VIDEO_ARRAY_OFFSET      = 112,
    VIDEO_STANDARD          = 114,
    SHUTTER_POSITION        = 121,
    TRANSFER_FRAME          = 130,
    CALC_EXTOFFSET          = 132,
    CORRECTION_MASK         = 177,
    FLASH_STATUS            = 196,
    WRITE_EXT_OFFSET_TABLE  = 197,
    WRITE_NVFFC_OFFSET_TABLE= 198,
    GAIN_SWITCH_PARAMS      = 219,
    DDE_THRESHOLD           = 226,
    SPATIAL_THRESHOLD       = 227,
    LENS_CONTROL            = 235,
    GET_FLASH_TYPE          = 236,
    COOLED_CORE_COMMAND     = 237
} CAM_USER_COMMAND;

/*!
 * Represents the different modes used by the camera to represent temperature.
 */
typedef enum FPATempMode
{
    FPA_TENTHS_DEG_C = 0,  /*!< Tenths of degrees celsius */
    FPA_RAW_COUNTS   = 1   /*!< Raw counts */
} CAM_FPA_TEMP_MODE;

/*!
 * Represents the different result codes the camera can return.
 */
typedef enum Result
{
    CAM_OK                            = 0,     /*!< Camera ok */
    CAM_COMM_OK                       = CAM_OK,/*!< Camera comm ok (same as CAM_OK) */
#ifdef _SDK
    /* Camera Errors (negative on SDK/host side) */
    CAM_ERROR                         = -1,    /*!< Camera error */
    CAM_NOT_READY                     = -2,    /*!< Camera not ready */
    CAM_RANGE_ERROR                   = -3,    /*!< Camera range error */
    CAM_CHECKSUM_ERROR                = -4,    /*!< Camera checksum eror */
    CAM_UNDEFINED_PROCESS_ERROR       = -5,    /*!< Camera undefined process error */
    CAM_UNDEFINED_FUNCTION_ERROR      = -6,    /*!< Camera undefined function error */
    CAM_BYTE_COUNT_ERROR              = -9,    /*!< Camera byte count error */
    CAM_FEATURE_NOT_ENABLED           = -10,   /*!< Camera feature not enabled */

    /* Comm Errors */
    CAM_COMM_PORT_NOT_OPEN            = -256,  /*!< Comm port not open */
    CAM_COMM_RANGE_ERROR              = -257,  /*!< Comm port range error */
    CAM_ERROR_CREATING_COMM           = -258,  /*!< Error creating comm */
    CAM_ERROR_STARTING_COMM           = -259,  /*!< Error starting comm */
    CAM_ERROR_CLOSING_COMM            = -260,  /*!< Error closing comm */
    CAM_COMM_CHECKSUM_ERROR           = -261,  /*!< Comm checksum error */
    CAM_COMM_NO_DEV                   = -262,  /*!< No comm device */
    CAM_COMM_TIMEOUT_ERROR            = -263,  /*!< Comm timeout error */
    CAM_COMM_ERROR_WRITING_COMM       = -264,  /*!< Error writing comm */
    CAM_COMM_ERROR_READING_COMM       = -265,  /*!< Error reading comm */
    CAM_COMM_ECHO_ERROR               = -267,  /*!< Comm echo error */
    CAM_COMM_COUNT_ERROR              = -268,  /*!< Comm byte count error */

    /* Other Errors */
    CAM_BAD_BITMAP_FILE               = -512,  /*!< Bad bitmap file error */
    CAM_BAD_CONFIG_FILE               = -513,  /*!< Bad configuration file error */
    CAM_ERROR_LOADING_FILE            = -514,  /*!< Error loading file */
    CAM_OPERATION_CANCELED            = -515,  /*!< Camera operation canceled */
    CAM_UNDEFINED_ERROR_CODE          = -516   /*!< Undefined error */
#else
    /* Camera Errors (must be positive to fit in status byte) */
    CAM_ERROR                         = 1,     /*!< Camera error */
    CAM_NOT_READY                     = 2,     /*!< Camera not ready */
    CAM_RANGE_ERROR                   = 3,     /*!< Camera range error */
    CAM_CHECKSUM_ERROR                = 4,     /*!< Camera checksum eror */
    CAM_UNDEFINED_PROCESS_ERROR       = 5,     /*!< Camera undefined process error */
    CAM_UNDEFINED_FUNCTION_ERROR      = 6,     /*!< Camera undefined function error */
    CAM_BYTE_COUNT_ERROR              = 9,     /*!< Camera byte count error */
    CAM_FEATURE_NOT_ENABLED           = 10     /*!< Camera feature not enabled */
#endif
} CAM_RESULT;

/*!
 * Represents the different shutter positions of the camera.
 */
typedef enum ShutterPosition
{
   SHUTTER_PROFILE = -32768,
   SHUTTER_UNKNOWN = -1, /*!< Shutter unknown */
   SHUTTER_OPEN   = 0,   /*!< Shutter open */
   SHUTTER_CLOSED = 1    /*!< Shuttern closed */
} CAM_SHUTTER_POSITION;

/*!
 * Represents the different options of the camera in a bit vector.
 */
typedef enum Options
{
    OPT_MASK_EXTENDED_TEMP   = 1,    /*!< Extended temperature */
    OPT_MASK_AUTO_GAIN       = 2,    /*!< Automatic gain */
    OPT_MASK_DIGITAL_OUT     = 4,    /*!< Digital output */
    OPT_MASK_SPOTMETER       = 8,    /*!< Spotmeter */
    OPT_MASK_ISOTHERM        = 16,   /*!< Isotherms */
    OPT_MASK_TORSION_SHUTTER = 32,   /*!< Torsion shutter */
    OPT_MASK_HEATER_CONTROL  = 64,   /*!< Heater control */
    OPT_MASK_HIDE_LOGO       = 128,  /*!< Hide Logo */
    OPT_MASK_LOCK_ZOOM       = 256,  /*!< Lock Zoom */
    OPT_MASK_LOCK_AGC        = 512,  /*!< Lock AGC */
    OPT_MASK_LIMIT_AGC       = 1024, /*!< Limit AGC */
    OPT_MASK_SNAPSHOT        = 2048, /*!< Snapshot */
    OPT_MASK_LOCK_SPLASH     = 4096, /*!< Lock Splash */
    OPT_MASK_UNIFIED_OFFSET  = 8192, /*!< Unified Offset */
    OPT_MASK_TERMINATION     = 16384, /*!< End of bit mask */
} CAM_OPTIONS;

/*!
 * Represents the different host side timeout values.
 */
typedef enum
{
    /* Timeout in milliseconds */
    CAM_LONG_TIMEOUT                   = 5000,  /*!<  */
    CAM_WRITE_TIMEOUT                  = 1000,  /*!<  */
    CAM_NORMAL_TIMEOUT                 = 500    /*!<  */
} CAM_TIMEOUTS;

typedef short CAM_TEMP;          /* temperature in .1° C */ 

typedef struct GainSwitchParams
{
   short HiLoThresh;
   short HiLoPOP;
   short LoHiThresh;
   short LoHiPOP;
} CAM_GAIN_SWITCH_PARAMS;


typedef struct TauGainSwitchParams
{
   short HiLoThresh;
   short HiLoPOP;
   short LoHiThresh;
   short LoHiPOP;
   short MedThresh;
   short MedPOP;
	   
} TAU_GAIN_SWITCH_PARAMS;

typedef struct CamRect
{
    short left;                     /* [R/W] range: (-319..+319) */
    short top;                      /* [R/W] range: (-255..+255) */
    short right;                    /* [R/W] range: (-319..+319) */
    short bottom;                   /* [R/W] range: (-255..+255) */
} CAM_RECT;

typedef enum Correction
{
    OFFSET_CORRECTION_MASK   = 1,
    GAIN_CORRECTION_MASK     = 2,
    LAGRANGE_CORRECTION_MASK = 4,
    PIXEL_REPLACE_MASK       = 8,
    NOISE_FILTER_MASK        = 16,
    COLUMN_CORRECTION_MASK   = 32,
    EXTFFC_OFFSET_MASK       = 64,
    ROW_CORRECTION_MASK      = 128,
    BCNR_CORRECTION_MASK     = 256,
    AVERAGER_CORRECTION_MASK = 512,
    DDE_CORRECTION_MASK      = 1024,
#ifdef _NV3
    FULL_CORRECTION          = (OFFSET_CORRECTION_MASK | GAIN_CORRECTION_MASK | PIXEL_REPLACE_MASK | LAGRANGE_CORRECTION_MASK | NOISE_FILTER_MASK | COLUMN_CORRECTION_MASK | ROW_CORRECTION_MASK),
#else
    FULL_CORRECTION          = (OFFSET_CORRECTION_MASK | GAIN_CORRECTION_MASK | PIXEL_REPLACE_MASK | LAGRANGE_CORRECTION_MASK | NOISE_FILTER_MASK | COLUMN_CORRECTION_MASK | ROW_CORRECTION_MASK | BCNR_CORRECTION_MASK),
#endif
    FULL_CORRECTION_640      = (OFFSET_CORRECTION_MASK | GAIN_CORRECTION_MASK | PIXEL_REPLACE_MASK | LAGRANGE_CORRECTION_MASK | NOISE_FILTER_MASK | COLUMN_CORRECTION_MASK | EXTFFC_OFFSET_MASK | ROW_CORRECTION_MASK),
    NO_CORRECTION            = 0
} CAM_CORRECTION;

typedef enum ExtOffsetState
{
    EXTOFFSET_OFF = 0,
    EXTOFFSET_ON = 1
} CAM_OFFSETSTATE;


typedef enum PortId
{
    UART_0        = 0,
#ifdef _CAL
    UART_1        = 1,
    USRT_2_LEGACY = 10,
    USRT_2        = 101,
    USRT_4        = 102,
    USRT_8        = 103,
    USRT_16       = 104,
    USRT_32       = 105,
    USRT_64       = 106,
    USRT_128      = 107,
    USRT_256      = 108,
#endif
    USRT_END
} CAM_PORTID;

typedef enum ThermalThrottleButtonState
{
    BULLARD_TT_UP_PRESSED  = 0,
    BULLARD_TT_UP_RELEASED = 1,

    BULLARD_TT_DOWN_PRESSED  = 2,
    BULLARD_TT_DOWN_RELEASED = 3

} CAM_BUTTON_STATE;

/*
 *  Index types for GET_PROGRAM_ADDRESS command
 */
#if defined(_MEP ) || defined(_PHOTON640) || defined(_SPECTARE)

typedef enum CamProgramType
{
    FLASH_SOFTWARE      = 0,    // Incompatible with Omega/AutoCam/Photon
    FLASH_FIRMWARE      = 1,    // Incompatible with Omega/AutoCam/Photon
    FLASH_STATIC_HDR    = 2,    // Should not be used: see NUC_STATIC_HEADER
    FLASH_FACTORY_HDR   = 3,    // Should not be used: see NUC_STATIC_HEADER
    FLASH_DYNAMIC_HDR   = 4,    // Should not be used: see NUC_DYNAMIC_HEADER
    FLASH_SPLASH1       = 5,
    FLASH_SPLASH2       = 6,
    FLASH_SYMBOLOGY     = 7,
    FLASH_FACTORY_BPM   = 8
} CAM_PROGRAM_TYPE;

#else

typedef enum CamProgramType
{
    DRAM_RANGE           = -2,
    FLASH_BLOCK_BASE     = -1,
    FLASH_BOOTLOAD       = 0,
    SOFTWARE_EXECUTION   = 0,
    FLASH_SOFTWARE       = 1,
    FLASH_PRI_FIRMWARE   = 2,
    FLASH_SEC_FIRMWARE   = 3,
    FLASH_RESERVED1      = 4,
    FLASH_SPLASH1        = 5,   // Added for _TAU and later 
    FLASH_SPLASH2        = 6,   // Added for _TAU and later 
    FLASH_SYMBOLOGY      = 7,   // Added for _TAU and later 
    FLASH_RESERVED2      = 8,
    FLASH_PALETTE        = 9,   // Added for _TAU and later 
    FLASH_FONTS          = 10,  // Added for _TAU and later 
    FLASH_DISCRETE       = 11,  // Added for _TAU and later 
    FLASH_SCRATCHPAD     = 12,  // Added for _TAU and later 
    FLASH_SPLASH_HEADER1 = 13,  // Added for _TAU and later 
    FLASH_SPLASH_HEADER2 = 14,  // Added for _TAU and later 
    FLASH_PALETTE_TITLES = 15,  // Added for _TAU and later 
    FLASH_NVFFC_MAP      = 16   // Added for _TAU and later 
} CAM_PROGRAM_TYPE;

#endif

typedef enum SymbolTableFunctionIds
{
   SYMBOL_UNFREEZE   = 0,
   SYMBOL_FREEZE     = 1,
   SYMBOL_PAINT      = 2,
   SYMBOL_WRITE      = 3
}  CAM_SYMBOL_TABLE_COMMANDS;


typedef enum SymbolFunctionIds
{
    SYMBOL_NOP                               = 0,
    SYMBOL_RECT                              = 1,
    SYMBOL_TEXT                              = 2,
    SYMBOL_BITMAP                            = 3,
    SYMBOL_OUTLINERECT                       = 4,
    SYMBOL_BATTERY_VOLTAGE_THRESHHOLDS       = 5
} CAM_SYMBOL_COMMANDS;

/*
 *  Index types for GET_NUC_ADDRESS command
 */
typedef enum NucDataType
{
    NUC_HEADER              = 0,
    NUC_ONCHIP              = 1,
    NUC_GAIN                = 2,
    NUC_LG0_COEFF           = 3,
    NUC_LG1_COEFF           = 4,
    NUC_LG2_COEFF           = 5,
    NUC_LG3_COEFF           = 6,
    NUC_RADIOMETRY          = 7,
    NUC_STATIC_HEADER       = 8,
    NUC_DYNAMIC_HEADER      = 9,
    NUC_FACTORY_HEADER      = 10,
    NUC_CAPTURE_BUFFER      = 11,
    DRAM_VIDEO_BUFFER       = 12,
    DRAM_ONCHIP_BUFFER      = 13,
    DRAM_LAGRANGE_BUFFER    = 14,
    DRAM_GAIN_BUFFER        = 15,
    DRAM_OFFSET_BUFFER      = 16,
    NUC_EXT_OFFSET          = 17,
    DRAM_EXT_OFFSET_BUFFER  = 18,
    FLASH_SNAPSHOT          = 19,
    NUC_NVFFC_OFFSET        = 20,
    NUC_LENS_SHAPE          = 21,
    FLASH_FACTORY_PIXELS    = 22,
    DRAM_LENS_SHAPE         = 23,
} CAM_NUC_DATA_TYPE;

#define USER_SYMBOLS        100

/*
 * Struct for Splash Screen header
 */
typedef struct
{
    unsigned short headerVersion;
    unsigned short delay;
    char filename[64];
    unsigned short pad[30];
} SPLASHSCREENHEADER;

typedef enum HistogramDebugCmds
{
    SET_HIST_DEBUG      = 0x100,
    CLEAR_HIST_DEBUG    = 0x200
} HISTOGRAMDEBUG;

typedef enum LensCmds
{
    LOAD_LENS_CMD       = 0x0000,
    SELECT_LENS_CMD     = 0x0100
} LENSCMDS;

typedef enum CalDestinationId
{
	CAMERA_DEST         = 1,
	BASKETBOARD_DEST	= 2,
	DEFAULT_DEST        = 3
}  CAL_DESTID;

typedef enum CamBaudRates
{
    CAM_BAUD_AUTO       = 0,
    CAM_BAUD_9600       = 1,
    CAM_BAUD_19200      = 2,
    CAM_BAUD_28800      = 3,
    CAM_BAUD_57600      = 4,
    CAM_BAUD_115200     = 5,
    CAM_BAUD_460800     = 6,
    CAM_BAUD_921600     = 7,
    CAM_BAUD_DEFAULT    = CAM_BAUD_AUTO,
} CAM_BAUD_RATES;

#ifdef __cplusplus
}
#endif

#endif /*_CAMUSER_H_*/
